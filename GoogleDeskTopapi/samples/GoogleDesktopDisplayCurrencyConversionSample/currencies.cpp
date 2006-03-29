// Copyright 2005 Google Inc
// All rights reserved
// 
// Currencies.h : Implementation of Internet exchange rate retrival

#include "stdafx.h"
#include "currencies.h"

#ifdef _DEBUG
static const int kTimeOut = 30*1000; // 30 seconds in in milliseconds
#else
static const int kTimeOut = 10*60*1000; // 10 minutes in in milliseconds
#endif

static const char* kHost = "www.google.com";

Currencies::Currencies(HWND wnd) : hwnd_(wnd), quit_(false), 
    request_handle_(NULL) {
  InitializeCriticalSection(&critical_section_);
  event_ = CreateEvent(NULL, false, false, NULL);
  ATLVERIFY(event_ != NULL);
  DWORD id = 0;
  thread_ = CreateThread(NULL, 0, ThreadProc, this, 0, &id);
  ATLVERIFY(thread_ != NULL);
}

Currencies::~Currencies() {
  quit_ = true;
  // avoid racing in calling InternetCloseHandle
  HINTERNET handle = reinterpret_cast<HINTERNET>(
    InterlockedExchangePointer((void**)&request_handle_, NULL));
  if (handle != NULL) {
    // will terminate pending HttpSendRequest or InternetReadFile
    InternetCloseHandle(handle);
    handle = NULL;
  }
  SetEvent(event_);
  WaitForSingleObject(thread_, INFINITE); // wait termination
  CloseHandle(event_);  event_ = NULL;
  CloseHandle(thread_); thread_ = NULL;
  DeleteCriticalSection(&critical_section_);
}

double Currencies::GetExchangeRate(const TCHAR* acode) {
  for (int i = 0; currencies[i].acode_ != NULL; i++) {
    if (wcscmp(acode, currencies[i].acode_) == 0) {
      EnterCriticalSection(&critical_section_);
      double r = currencies[i].last_rate;
      LeaveCriticalSection(&critical_section_);
      return r;
    }
  }
  ATLASSERT(false && "Invalid currency acode");
  return 0.0;
}

void Currencies::SetExchangeRate(const TCHAR* acode, double rate) {
  ATLASSERT(rate > 0.0);
  for (int i = 0; currencies[i].acode_ != NULL; i++) {
    if (wcscmp(acode, currencies[i].acode_) == 0) {
      EnterCriticalSection(&critical_section_);
      currencies[i].last_rate = rate;
      LeaveCriticalSection(&critical_section_);
    }
  }
}

void Currencies::Request(const TCHAR* acode) {
  for (int i = 0; currencies[i].acode_ != NULL; i++) {
    if (wcscmp(acode, currencies[i].acode_) == 0) {
      EnterCriticalSection(&critical_section_);
      currencies[i].time = 1;
      LeaveCriticalSection(&critical_section_);
      return;
    }
  }
}

void Currencies::KickRequests() {
  if (event_ != NULL) SetEvent(event_);
}

CString Currencies::GetCountries(const TCHAR* acode) {
  CString countries = L"";
  for (int i = 0; currencies[i].acode_ != NULL; i++) {
    if (wcscmp(acode, currencies[i].acode_) == 0) {
      if (countries.GetLength() > 0) countries += _T(", ");
      countries += currencies[i].country_;
    }
  }
  ATLASSERT(countries.GetLength() > 0 && "Invalid currency acode");
  return countries;
}

const TCHAR* Currencies::GetCurrencyName(const TCHAR* acode) {
  for (int i = 0; currencies[i].acode_ != NULL; i++) {
    if (wcscmp(acode, currencies[i].acode_) == 0)
      return currencies[i].currency_;
  }
  ATLASSERT(false && "Invalid currency acode");
  return _T("");
}

static const char * g_pi = "3.14159265358979323846";

/** FindSubstring
    searches string `s` for the `substring` and returns
    pointer to the _next_(!) byte after substring or NULL
    if substring is not found.
    Nor `s` neighter `substring` can be NULL.
    Substring cannot be empty string.
*/

static char * FindSubstring(const char * s, const char* substring) {
  ATLASSERT(s != NULL);
  ATLASSERT(substring != NULL);
  size_t n = lstrlenA(substring);
  ATLASSERT(n > 0);
  char * p = strstr(s, substring);
  return p == NULL ? NULL : p + n;
}

/** GetCurrentTimeIn100ns
    Returns time elapsed since January 1, 1601 00:00:00.000 (UTC).
*/

static ulonglong GetCurrentTimeIn100ns() {
  FILETIME ft = {0};
  GetSystemTimeAsFileTime(&ft);
  return *(ulonglong*)&ft;
}

/** ProcessResult implements page scrapping for the absence of better 
    alternative at the time of implementation.
    Sample response:
    "...<td nowrap><font size=+1><b>
     3.1415 U.S. dollars = 1<font size=-2> </font>714.3434 Chilean pesos
     </b></td>..."
*/

void Currencies::ProcessResult(int ix, const char* buf) {
  const WCHAR* acode = currencies[ix].acode_;
  const char * p = buf;
  while ((p = FindSubstring(p, " = ")) != NULL) {
    if (p > buf + 128) {
      char * q = FindSubstring(p - 128, "<td nowrap><font size=+1><b>");
      if (q != NULL && q < p) {
          char * r = strstr(p, "</b></td>");
          if (r != NULL && r > p && r - q < 1024 && strstr(p, g_pi)) {
            char line[1024] = {0};
            memcpy(line, q, r - q);
            // GWS inserts "small space" between thousands and number:
            const char * small_space = "<font size=-2> </font>";
            char * space = strstr(line, small_space);
            if (space != NULL) {
              int k = int(space - line);
              StringCchCopyA(space, sizeof(line) - k, 
                  space + lstrlenA(small_space));
            }
            char * r = strstr(line, " = ");
            ATLASSERT(r != NULL);
            float test = 0;
            ATLASSERT(sscanf(r + 3, "%g", &test) == 1);
            unused(test);
            SetExchangeRate(currencies[ix].acode_, atof(r + 3) / atof(g_pi));
            break;
        }
      }
    }
    p++;
  }
  PostMessage(hwnd_, WM_CURRENCY_RATE, 0, reinterpret_cast<LPARAM>(acode));
}

/** ThreadProc
    Once in 10 minutes attempts to open internet connection and
    perform all outstanding queries.
    send requests to GWS calculator and parses results.
    Sample request URL:
    http://www.google.com/search?hl=en&q=3.1415+usd+in+euro&spell=1
    Sample response:
    "...<td nowrap><font size=+1><b>
     3.1415 U.S. dollars = 1<font size=-2> </font>714.3434 Chilean pesos
     </b></td>..."
*/

DWORD WINAPI Currencies::ThreadProc(void* param) {
  Currencies* that = reinterpret_cast<Currencies*>(param);
  for (;;) {
    WaitForSingleObject(that->event_, kTimeOut);
    if (that->quit_) break;
    ulonglong nextTime = GetCurrentTimeIn100ns() + 
        kTimeOut * ulonglong(10000) - 1;
    BOOL b = false;
    HINTERNET internet_handle = InternetOpenA(NULL, INTERNET_OPEN_TYPE_PRECONFIG, 
      NULL, NULL, 0);
    if (internet_handle == NULL) {
      // TODO: needs proper error reporting
      OutputDebugStringA("InternetOpenA failed\n");
    } else {
      HINTERNET connection_handle = InternetConnectA(internet_handle, kHost, 80,
          NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);
      if (connection_handle == NULL) {
        // TODO: needs proper error reporting
        OutputDebugStringA("InternetConnectA failed\n");
      } else {
        for (int k = 0; currencies[k].acode_ != NULL && !that->quit_; k++) {
          EnterCriticalSection(&that->critical_section_);
          bool required = currencies[k].time != 0 && 
              (currencies[k].last_rate == 0 || 
               currencies[k].time < GetCurrentTimeIn100ns());
          LeaveCriticalSection(&that->critical_section_);
          if (required) {
            char request[1024] = {0};
            int n = ::StringCbPrintfA(request, sizeof(request) - 1,
                "search?hl=en&q=%hs+usd+in+%ls&spell=0",
                g_pi, currencies[k].acode_);
            ATLVERIFY(n < sizeof(request));
            static const int kFlags = INTERNET_FLAG_NO_UI;
            that->request_handle_ = HttpOpenRequestA(connection_handle, "GET",
                request, "HTTP/1.1", "", NULL, kFlags, 0);
            if (that->request_handle_ == NULL) {
              // TODO: needs proper error reporting
              OutputDebugStringA("HttpOpenRequestA failed\n");
            } else {
              b = HttpSendRequest(that->request_handle_, NULL, 0, NULL, 0);
              if (!b) {
                // TODO: needs proper error reporting
                OutputDebugStringA("HttpSendRequest failed\n");
              } else {
                int len = 0; // length of result including zero terminating byte
                char * result = NULL;
                char buf[2048]; // max MTU is 1500, 2K is a reasonable 
                for (;;) {
                  DWORD bytes_read = 0;
                  b = InternetReadFile(that->request_handle_, buf, sizeof(buf), 
                      &bytes_read);
                  if (!b) {
                    // TODO: needs proper error reporting
                    OutputDebugStringA("InternetReadFile failed\n");
                    break;
                  }
                  if (bytes_read == 0 || that->quit_) {
                      break; // succesfully finished reading
                  }
                  char * s = new char[len + bytes_read + 1];
                  if (len > 0) memcpy(s, result, len);
                  memcpy(s + len, buf, bytes_read);
                  s[len + bytes_read] = 0;
                  delete [] result; // delete NULL is perfectly OK
                  result = s;
                  len += bytes_read;
                }
                if (b && !that->quit_) {
                  that->ProcessResult(k, result);
                  delete [] result; result = NULL;
                  EnterCriticalSection(&that->critical_section_);
                  currencies[k].time = nextTime;
                  LeaveCriticalSection(&that->critical_section_);
                }
                HINTERNET handle = reinterpret_cast<HINTERNET>(
                    InterlockedExchangePointer(
                      (void**)&that->request_handle_, NULL));
                if (handle != NULL) {
                  b = InternetCloseHandle(handle);
                  handle = NULL;
                  // TODO: needs proper error reporting
                  ATLVERIFY(b && "InternetCloseHandle failed");
                }
              }
            }
          }
        }
        b = InternetCloseHandle(connection_handle);
        // TODO: needs proper error reporting
        ATLVERIFY(b && "InternetCloseHandle failed");
        connection_handle = NULL;
      }
      b = InternetCloseHandle(internet_handle);
      // TODO: needs proper error reporting
      ATLVERIFY(b && "InternetCloseHandle failed");
      internet_handle = NULL;
    }
  }
  return 0;
}

void Currencies::Tokenize(CString csv, CStringArray * tokens) {
  CString s = csv;
  for (;;) {
    int i = s.Find(L',', 0);
    CString currency;
    if (i > 0) {
      currency = s.Left(i);
      if (i < s.GetLength() - 1) 
        s = s.Right(s.GetLength() - i - 1);
      else
        s = L"";
    }
    else {
      currency = s;
      s = L"";
    }
    if (currency.GetLength() == 0) break;
    tokens->Add(currency);
  }
}

Currency Currencies::currencies[] = {
  {L"Afghanistan", L"Afghani", L"AFN", 971, 0, 0.0},
  {L"Albania", L"Lek", L"ALL", 8, 0, 0.0},
  {L"Algeria", L"Algerian Dinar", L"DZD", 12, 0, 0.0},
  {L"American Samoa", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Andorra", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Andorra", L"Andorran Peseta", L"ADP", 20, 0, 0.0},
  {L"Angola", L"Kwanza", L"AOA", 973, 0, 0.0},
  {L"Anguilla", L"East Carribbean Dollar", L"XCD", 951, 0, 0.0},
  {L"Antigua and Barbuda", L"East Carribbean Dollar", L"XCD", 951, 0, 0.0},
  {L"Argentina", L"Argentine Peso", L"ARS", 32, 0, 0.0},
  {L"Armenia", L"Armenian Dram", L"AMD", 51, 0, 0.0},
  {L"Aruba", L"Aruban Guilder", L"AWG", 533, 0, 0.0},
  {L"Australia", L"Australian Dollar", L"AUD", 36, 0, 0.0},
  {L"Austria", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Azerbaijan", L"Azerbaijanian Manat", L"AZM", 31, 0, 0.0},
  {L"Bahamas", L"Bahamian Dollar", L"BSD", 44, 0, 0.0},
  {L"Bahrain", L"Bahraini Dinar", L"BHD", 48, 0, 0.0},
  {L"Bangladesh", L"Taka", L"BDT", 50, 0, 0.0},
  {L"Barbados", L"Barbados Dollar", L"BBD", 52, 0, 0.0},
  {L"Belarus", L"Belarussian Ruble", L"BYR", 974, 0, 0.0},
  {L"Belgium", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Belize", L"Belize Dollar", L"BZD", 84, 0, 0.0},
  {L"Benin", L"CFA Franc BCEAO", L"XOF", 952, 0, 0.0},
  {L"Bermuda", L"Bermudian Dollar", L"BMD", 60, 0, 0.0},
  {L"Bhutan", L"Ngultrum", L"BTN", 64, 0, 0.0},
  {L"Bolivia", L"Boliviano", L"BOB", 68, 0, 0.0},
  {L"Bolivia", L"Mvdol", L"BOV", 984, 0, 0.0},
  {L"Bosnia and Herzegowina", L"Convertible Marks", L"BAM", 977, 0, 0.0},
  {L"Botswana", L"Pula", L"BWP", 72, 0, 0.0},
  {L"Brazil", L"Brazilian Real", L"BRL", 986, 0, 0.0},
  {L"British Indian Ocean Territory", L"US Dollar'", L"USD", 840, 0, 0.0},
  {L"Brunei Darussalam", L"Brunei Dollar", L"BND", 96, 0, 0.0},
  {L"Bulgaria", L"Lev", L"BGL", 100, 0, 0.0},
  {L"Bulgaria", L"Bulgarian Lev", L"BGN", 975, 0, 0.0},
  {L"Burkina Faso", L"CFA Franc BCEAO", L"XOF", 952, 0, 0.0},
  {L"Burundi", L"Burundi Franc", L"BIF", 108, 0, 0.0},
  {L"Cambodia", L"Riel", L"KHR", 116, 0, 0.0},
  {L"Cameroon", L"CFA Franc BEAC", L"XAF", 950, 0, 0.0},
  {L"Canada", L"Canadian Dollar", L"CAD", 124, 0, 0.0},
  {L"Cape Verde", L"Cape Verde Escudo", L"CVE", 132, 0, 0.0},
  {L"Cayman Islands", L"Cayman Islands Dollar", L"KYD", 136, 0, 0.0},
  {L"Central African Republic", L"CFA Franc BEAC", L"XAF", 950, 0, 0.0},
  {L"Chad", L"CFA Franc BEAC", L"XAF", 950, 0, 0.0},
  {L"Chile", L"Chilean Peso", L"CLP", 152, 0, 0.0},
  {L"Chile", L"Unidades de Fomento", L"CLF", 990, 0, 0.0},
  {L"China", L"Yuan Renminbi", L"CNY", 156, 0, 0.0},
  {L"Christmas Island", L"Australian Dollar", L"AUD", 36, 0, 0.0},
  {L"Cocos (Keeling) Islands", L"Australian Dollar", L"AUD", 36, 0, 0.0},
  {L"Colombia", L"Colombian Peso", L"COP", 170, 0, 0.0},
  {L"Comoros", L"Comoro Franc", L"KMF", 174, 0, 0.0},
  {L"Congo Democratic Republic", L"Franc Congolais", L"CDF", 976, 0, 0.0},
  {L"Congo Republic of", L"CFA Franc BEAC", L"XAF", 950, 0, 0.0},
  {L"Costa Rica", L"Costa Rican Colon", L"CRC", 188, 0, 0.0},
  {L"Cote D'Ivoire", L"CFA Franc BCEAO", L"XOF", 952, 0, 0.0},
  {L"Croatia/Hrvatska", L"Croatian Kuna", L"HRK", 191, 0, 0.0},
  {L"Cuba", L"Cuban Peso", L"CUP", 192, 0, 0.0},
  {L"Cyprus", L"Cyprus Pound", L"CYP", 196, 0, 0.0},
  {L"Czech Republic", L"Czech Koruna", L"CZK", 203, 0, 0.0},
  {L"Denmark", L"Danish Krone", L"DKK", 208, 0, 0.0},
  {L"Djibouti", L"Djibouti Franc", L"DJF", 262, 0, 0.0},
  {L"Dominica", L"East Caribbean Dollar", L"XCD", 951, 0, 0.0},
  {L"Dominican Republic", L"Dominican Peso", L"DOP", 214, 0, 0.0},
  {L"Ecuador", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Egypt", L"Egyptian Pound", L"EGP", 818, 0, 0.0},
  {L"El Salvador", L"El Salvador Colon", L"SVC", 222, 0, 0.0},
  {L"El Salvador", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Equatorial Guinea", L"CFA Franc BEAC", L"XAF", 950, 0, 0.0},
  {L"Eritrea", L"Nakfa", L"ERN", 232, 0, 0.0},
  {L"Estonia", L"Kroon", L"EEK", 233, 0, 0.0},
  {L"Ethiopia", L"Ethiopian Birr", L"ETB", 230, 0, 0.0},
  {L"Falkland Islands (Malvinas)", L"Falkland Islands Pound", L"FKP", 
      238, 0, 0.0},
  {L"Faroe Islands", L"Danish Krone", L"DKK", 208, 0, 0.0},
  {L"Fiji", L"Fiji Dollar", L"FJD", 242, 0, 0.0},
  {L"Finland", L"Euro", L"EUR", 978, 0, 0.0},
  {L"France", L"Euro", L"EUR", 978, 0, 0.0},
  {L"French Guiana", L"Euro", L"EUR", 978, 0, 0.0},
  {L"French Polynesia", L"CFP Franc", L"XPF", 953, 0, 0.0},
  {L"French Southern Territories", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Gabon", L"CFA Franc BEAC", L"XAF", 950, 0, 0.0},
  {L"Gambia", L"Dalasi", L"GMD", 270, 0, 0.0},
  {L"Georgia", L"Lari", L"GEL", 981, 0, 0.0},
  {L"Germany", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Ghana", L"Cedi", L"GHC", 288, 0, 0.0},
  {L"Gibraltar", L"Gibraltar Pound", L"GIP", 292, 0, 0.0},
  {L"Greece", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Greenland", L"Danish Krone", L"DKK", 208, 0, 0.0},
  {L"Grenada", L"East Caribbean Dollar", L"XCD", 951, 0, 0.0},
  {L"Guadeloupe", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Guam", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Guatemala", L"Quetzal", L"GTQ", 320, 0, 0.0},
  {L"Guinea", L"Guinea Franc", L"GNF", 324, 0, 0.0},
  {L"Guinea-Bissau", L"Guinea-Bissau Peso", L"GWP", 624, 0, 0.0},
  {L"Guinea-Bissau", L"CFA Franc BCEAO", L"XOF", 952, 0, 0.0},
  {L"Guyana", L"Guyana Dollar", L"GYD", 328, 0, 0.0},
  {L"Haiti", L"Gourde", L"HTG", 332, 0, 0.0},
  {L"Haiti", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Heard and Mc Donald Islands", L"Australian Dollar", L"AUD", 36, 0, 0.0},
  {L"Holy See", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Honduras", L"Lempira", L"HNL", 340, 0, 0.0},
  {L"Hong Kong", L"Hong Kong Dollar", L"HKD", 344, 0, 0.0},
  {L"Hungary", L"Forint", L"HUF", 348, 0, 0.0},
  {L"Iceland", L"Iceland Krona", L"ISK", 352, 0, 0.0},
  {L"India", L"Indian Rupee", L"INR", 356, 0, 0.0},
  {L"Bhutan", L"Indian Rupee", L"INR", 356, 0, 0.0},
  {L"Indonesia", L"Rupiah", L"IDR", 360, 0, 0.0},
  {L"Iran", L"Iranian Rial", L"IRR", 364, 0, 0.0},
  {L"Iraq", L"Iraqi Dinar", L"IQD", 368, 0, 0.0},
  {L"Ireland", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Israel", L"New Israeli Sheqel", L"ILS", 376, 0, 0.0},
  {L"Italy", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Jamaica", L"Jamaican Dollar", L"JMD", 388, 0, 0.0},
  {L"Japan", L"Yen", L"JPY", 392, 0, 0.0},
  {L"Jordan", L"Jordanian Dinar", L"JOD", 400, 0, 0.0},
  {L"Kazakhstan", L"Tenge", L"KZT", 398, 0, 0.0},
  {L"Kenya", L"Kenyan Shilling", L"KES", 404, 0, 0.0},
  {L"Kiribati", L"Australian Dollar", L"AUD", 36, 0, 0.0},
  {L"Korea (North Korea)", L"North Korean Won", L"KPW", 408, 0, 0.0},
  {L"Korea (South Korea)", L"Won", L"KRW", 410, 0, 0.0},
  {L"Kuwait", L"Kuwaiti Dinar", L"KWD", 414, 0, 0.0},
  {L"Kyrgyzstan", L"Som", L"KGS", 417, 0, 0.0},
  {L"Lao", L"Kip", L"LAK", 418, 0, 0.0},
  {L"Latvia", L"Latvian Lats", L"LVL", 428, 0, 0.0},
  {L"Lebanon", L"Lebanese Pound", L"LBP", 422, 0, 0.0},
  {L"Liberia", L"Liberian Dollar", L"LRD", 430, 0, 0.0},
  {L"Libyan Arab Jamahiriya", L"Lybian Dinar", L"LYD", 434, 0, 0.0},
  {L"Lithuania", L"Lithuanian Litas", L"LTL", 440, 0, 0.0},
  {L"Luxembourg", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Macau", L"Pataca", L"MOP", 446, 0, 0.0},
  {L"Macedonia", L"Denar", L"MKD", 807, 0, 0.0},
  {L"Madagascar", L"Malagasy Franc", L"MGF", 450, 0, 0.0},
  {L"Malawi", L"Kwacha", L"MWK", 454, 0, 0.0},
  {L"Malaysia", L"Malaysian Ringgit", L"MYR", 458, 0, 0.0},
  {L"Maldives", L"Rufiyaa", L"MVR", 462, 0, 0.0},
  {L"Mali", L"CFA Franc BCEAO", L"XOF", 952, 0, 0.0},
  {L"Malta", L"Maltese Lira", L"MTL", 470, 0, 0.0},
  {L"Marshall Islands", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Martinique", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Mauritania", L"Ouguiya", L"MRO", 478, 0, 0.0},
  {L"Mauritius", L"Mauritius Rupee", L"MUR", 480, 0, 0.0},
  {L"Mayotte", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Mexico", L"Mexican Peso", L"MXN", 484, 0, 0.0},
  {L"Mexico", L"Mexican Unidad de Inversion (UDI)", L"MXV", 979, 0, 0.0},
  {L"Micronesia Federal States of", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Moldova Republic of", L"Moldovan Leu", L"MDL", 498, 0, 0.0},
  {L"Monaco", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Mongolia", L"Tugrik (Tugrug)", L"MNT", 496, 0, 0.0},
  {L"Montserrat", L"East Caribbean Dollar", L"XCD", 951, 0, 0.0},
  {L"Morocco", L"Moroccan Dirham", L"MAD", 504, 0, 0.0},
  {L"Mozambique", L"Metical", L"MZM", 508, 0, 0.0},
  {L"Myanmar", L"Kyat", L"MMK", 104, 0, 0.0},
  {L"Namibia Dollar", L"Namibia Dollar", L"NAD", 516, 0, 0.0},
  {L"Nauru", L"Australian Dollar", L"AUD", 36, 0, 0.0},
  {L"Nepal", L"Nepalese Rupee", L"NPR", 524, 0, 0.0},
  {L"Netherlands", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Netherlands Antilles", L"Netherlands Antillan Guilder", L"ANG", 
      532, 0, 0.0},
  {L"New Caledonia", L"CFP Franc", L"XPF", 953, 0, 0.0},
  {L"New Zealand", L"New Zealand Dollar", L"NZD", 554, 0, 0.0},
  {L"Tokelau", L"New Zealand Dollar", L"NZD", 554, 0, 0.0},
  {L"Niue", L"New Zealand Dollar", L"NZD", 554, 0, 0.0},
  {L"Cook Islands", L"New Zealand Dollar", L"NZD", 554, 0, 0.0},
  {L"Pitcairn Island", L"New Zealand Dollar", L"NZD", 554, 0, 0.0},
  {L"Nicaragua", L"Cordoba Oro", L"NIO", 558, 0, 0.0},
  {L"Niger", L"CFA Franc BCEAO", L"XOF", 952, 0, 0.0},
  {L"Nigeria", L"Naira", L"NGN", 566, 0, 0.0},
  {L"Norfolk Island", L"Australian Dollar", L"AUD", 36, 0, 0.0},
  {L"Northern Mariana Islands", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Norway", L"Norwegian Krone", L"NOK", 578, 0, 0.0},
  {L"Bouvet Island", L"Norvegian Krone", L"NOK", 578, 0, 0.0},
  {L"Oman", L"Rial Omani", L"OMR", 512, 0, 0.0},
  {L"Pakistan", L"Pakistan Rupee", L"PKR", 586, 0, 0.0},
  {L"Palau", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Panama", L"Balboa", L"PAB", 590, 0, 0.0},
  {L"Panama", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Papua New Guinea", L"Kina", L"PGK", 598, 0, 0.0},
  {L"Paraguay", L"Guarani", L"PYG", 600, 0, 0.0},
  {L"Peru", L"Nuevo Sol", L"PEN", 604, 0, 0.0},
  {L"Philippines", L"Philippine Peso", L"PHP", 608, 0, 0.0},
  {L"Poland", L"Zloty", L"PLN", 985, 0, 0.0},
  {L"Portugal", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Puerto Rico", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Qatar", L"Qatari Rial", L"QAR", 634, 0, 0.0},
  {L"Reunion Island", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Romania", L"Leu", L"ROL", 642, 0, 0.0},
  {L"Russian Federation", L"Russian Ruble", L"RUR", 810, 0, 0.0},
  {L"Russian Federation", L"Russian Ruble", L"RUB", 643, 0, 0.0},
  {L"Rwanda", L"Rwanda Franc", L"RWF", 646, 0, 0.0},
  {L"Saint Helena", L"Saint Helena Pound", L"SHP", 654, 0, 0.0},
  {L"Saint Kitts and Nevis", L"East Caribbean Dollar", L"XCD", 951, 0, 0.0},
  {L"Saint Lucia", L"East Caribbean Dollar", L"XCD", 951, 0, 0.0},
  {L"St. Pierre and Miquelon", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Saint Vincent and the Grenadines", L"East Caribbean Dollar", L"XCD", 
      951, 0, 0.0},
  {L"Samoa", L"Tala", L"WST", 882, 0, 0.0},
  {L"San Marino", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Sao Tome and Principe", L"Dobra", L"STD", 678, 0, 0.0},
  {L"Saudi Arabia", L"Saudi Riyal", L"SAR", 682, 0, 0.0},
  {L"Senegal", L"CFA Franc BCEAO", L"XOF", 952, 0, 0.0},
  {L"Serbia and Montenegro", L"Serbian Dinar (Serbia)", L"CSD", 891, 0, 0.0},
  {L"Montenegro", L"Euro (Montenegro)", L"EUR", 978, 0, 0.0},
  {L"Seychelles", L"Seychelles Rupee", L"SCR", 690, 0, 0.0},
  {L"Sierra Leone", L"Leone", L"SLL", 694, 0, 0.0},
  {L"Singapore", L"Singapore Dollar", L"SGD", 702, 0, 0.0},
  {L"Slovakia (Slovak Republic)", L"Slovak Koruna", L"SKK", 703, 0, 0.0},
  {L"Slovenia", L"Tolar", L"SIT", 705, 0, 0.0},
  {L"Solomon Islands", L"Solomon Islands Dollar", L"SBD", 90, 0, 0.0},
  {L"Somalia", L"Somali Shilling", L"SOS", 706, 0, 0.0},
  {L"South Africa", L"Rand", L"ZAR", 710, 0, 0.0},
  {L"Namibia", L"Rand", L"ZAR", 710, 0, 0.0},
  {L"Spain", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Sri Lanka", L"Sri Lanka Rupee", L"LKR", 144, 0, 0.0},
  {L"Sudan", L"Sudanese Dinar", L"SDD", 736, 0, 0.0},
  {L"Suriname", L"Suriname Guilder", L"SRG", 740, 0, 0.0},
  {L"Svalbard and Jan Mayen Islands", L"Norwegian Krone", L"NOK", 578, 0, 0.0},
  {L"Swaziland", L"Lilangeni", L"SZL", 748, 0, 0.0},
  {L"Sweden", L"Swedish Krona", L"SEK", 752, 0, 0.0},
  {L"Switzerland", L"Swiss Franc", L"CHF", 756, 0, 0.0},
  {L"Liechtenstein", L"Swiss Franc", L"CHF", 756, 0, 0.0},
  {L"Syrian Arab Republic", L"Syrian Pound", L"SYP", 760, 0, 0.0},
  {L"Taiwan Republic of China", L"New Taiwan Dollar", L"TWD", 901, 0, 0.0},
  {L"Tajikistan", L"Somoni", L"TJS", 972, 0, 0.0},
  {L"Tanzania", L"Tanzanian Shilling", L"TZS", 834, 0, 0.0},
  {L"Thailand", L"Baht", L"THB", 764, 0, 0.0},
  {L"Timor Leste", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Togo", L"CFA Franc BCEAO", L"XOF", 952, 0, 0.0},
  {L"Tonga", L"Pa¥anga", L"TOP", 776, 0, 0.0},
  {L"Trinidad and Tobago", L"Trinidad and Tobago Dollar", L"TTD", 780, 0, 0.0},
  {L"Tunisia", L"Tunisian Dinar", L"TND", 788, 0, 0.0},
  {L"Turkey", L"Yeni Türk Liras (YTL)", L"TRY", 949, 0, 0.0},
  {L"Turkmenistan", L"Manat", L"TMM", 795, 0, 0.0},
  {L"Turks and Caicos Islands", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Tuvalu", L"Australian Dollar", L"AUD", 36, 0, 0.0},
  {L"Uganda", L"Uganda Shilling", L"UGX", 800, 0, 0.0},
  {L"Ukraine", L"Hryvnia", L"UAH", 980, 0, 0.0},
  {L"United Arab Emirates", L"UAE Dirham", L"AED", 784, 0, 0.0},
  {L"United Kingdom", L"Pound Sterling", L"GBP", 826, 0, 0.0},
  {L"United States", L"US Dollar r (Same day)", L"USS", 998, 0, 0.0},
  {L"United States (next day)", L"US Dollar r (Next day)", L"USN", 997, 0, 0.0},
  {L"U.S. Minor Outlying Islands", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Uruguay", L"Peso Uruguayo", L"UYU", 858, 0, 0.0},
  {L"Uzbekistan", L"Uzbekistan Sum", L"UZS", 860, 0, 0.0},
  {L"Vanuatu", L"Vatu", L"VUV", 548, 0, 0.0},
  {L"Vatican City State (Holy See)", L"Euro", L"EUR", 978, 0, 0.0},
  {L"Venezuela", L"Bolivar", L"VEB", 862, 0, 0.0},
  {L"Viet Nam", L"Dong", L"VND", 704, 0, 0.0},
  {L"Virgin Islands (British)", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Virgin Islands (U.S.)", L"US Dollar", L"USD", 840, 0, 0.0},
  {L"Wallis and Futuna Islands", L"CFP Franc", L"XPF", 953, 0, 0.0},
  {L"Western Sahara", L"Moroccan Dirham", L"MAD", 504, 0, 0.0},
  {L"Yemen", L"Yemeni Rial", L"YER", 886, 0, 0.0},
  {L"Yugoslavia", L"Yugoslavian Dinar", L"YUM", 891, 0, 0.0},
  {L"Zambia", L"Kwacha", L"ZMK", 894, 0, 0.0},
  {L"Zimbabwe", L"Zimbabwe Dollar", L"ZWD", 716, 0, 0.0},
  {L"Lesotho", L"Loti (plural Maloti) is equivalent to the South African Rand.", 
      L"ZAR", 710, 0, 0.0},
  {NULL, NULL, NULL, 0, 0, 0.0},
};

// major currencies known (at the time of implementation) to www.google.com
// calculator:

const WCHAR* Currencies::knownCurrencies[] = {
  L"TWD", L"EUR", L"ARS", L"AUD", L"BOB", L"NOK", L"BRL", L"BGN", L"THB",
  L"CAD", L"CLP", L"CNY", L"COP", L"NZD", L"HRK", L"CZK", L"DKK", L"EGP",
  L"EEK", L"HKD", L"HUF", L"INR", L"IDR", L"ILS", L"JPY", L"KRW", L"AED",
  L"LTL", L"MYR", L"MXN", L"MAD", L"ZAR", L"GBP", L"VEB", L"SEK", L"CHF",
  L"PKR", L"PEN", L"PHP", L"PLN", L"ROL", L"RUR", L"RUB", L"SAR", L"TRY", 
  L"CSD", L"SGD", L"SKK", L"SIT", NULL
};
