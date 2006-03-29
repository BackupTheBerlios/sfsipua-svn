// Copyright 2005 Google Inc
// All rights reserved
// 
#ifndef CURRENCIES_H
#define CURRENCIES_H

#pragma warning(push)
#pragma warning(disable: 4510) // default constructor could not be generated
#pragma warning(disable: 4610) // struct 'Currency' can never be instantiated

struct Currency {
  const TCHAR * country_; // country where the currency is used
  const TCHAR * currency_; // name of the currency
  const TCHAR * acode_; // TLA aka "alpha code"
  const int ncode_; // numeric code of the currency (not used)
  ulonglong time;   // FILETIME in 100ns for the next refresh request
  double last_rate; // last currency exhange rate to U$D
};

#pragma warning(pop)

// Currencies provides list of known currencies, some of their properties and
// methods that request and update the currency rates.

class Currencies {
public:
  // message that will be posted everytime we receive new currency exhange
  // rate from the Internet
  static const int WM_CURRENCY_RATE = 0xC145;

  // List of currencies currenty supported by Google Calulator
  static const TCHAR* knownCurrencies[]; // NULL terminated

  // Constructor - starts query thread
  Currencies(HWND wnd); 
  // Destructor - stops query thread and waits until it exits
  virtual ~Currencies(); 

  // Return last exhcnage rate
  double GetExchangeRate(const TCHAR* acode);

  // Sets exchange rate (used by persistent storage Load to 
  // start with last run currency exchange rates rather than 
  // blank rates)
  void SetExchangeRate(const TCHAR* acode, double rate);

  // Request - schedules next currency request for processing.
  // Does not kick the request for processing. You may schedule multiple
  // requests and than kick them to go out and download rates by calling
  // KickRequests.
  // ThreadProc will call 
  //   PostMessage(hwnd, WM_CURRENCY_RATE, 0, (LPARAM)const TCHAR* acode)
  // every time currency exchange rate is changed
  void Request(const TCHAR* acode);

  // Kicks all scheduled requests
  void KickRequests();

  // Return list of countries where the acode currency is used
  static CString GetCountries(const TCHAR* acode);
  
  // Return human readable currency name in English
  static const TCHAR* GetCurrencyName(const TCHAR* acode);
  
  // Tokenize comma separated list of currencies in a form "USD,1.0,EUR,0.89"
  static void Tokenize(CString s, CStringArray * tokens);

private:
  static Currency currencies[]; // all we know about currencies
  static DWORD WINAPI ThreadProc(void* param); // request processor
  void ProcessResult(int ix, const char* buf); 
  CRITICAL_SECTION critical_section_;
  HANDLE event_;
  HANDLE thread_;
  volatile HINTERNET request_handle_;
  HWND hwnd_;
  bool quit_;
};

#endif // CURRENCIES_H
