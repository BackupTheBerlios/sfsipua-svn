#include "StdAfx.h"
#include "ef_registration.h"

#define CONSOLE_PLUGIN_GUID       L"{D93681F6-1B5D-4963-B2D2-43037BFB6A3F}"
#define SAMPLES_CONFIG_KEY        _T("Software\\GDSamples")
#define CONSOLE_CONFIG_KEY_NAME   _T("ConsoleEvent")
#define CONSOLE_CONFIG_KEY        SAMPLES_CONFIG_KEY _T("\\") CONSOLE_CONFIG_KEY_NAME
#define COOKIE_VALUE              _T("EventCookie")

HRESULT StoreRegistrationCookie(long cookie) {
  CRegKey key;
  LONG res = key.Create(HKEY_CURRENT_USER, CONSOLE_CONFIG_KEY);
  if (res != ERROR_SUCCESS)
    return AtlHresultFromWin32(res);

  res = key.SetDWORDValue(COOKIE_VALUE, cookie);
  ATLASSERT(res == ERROR_SUCCESS);
  return AtlHresultFromWin32(res);
}

/**
* Once registered, this is a simple way to retrieve our 
* event framework cookie.
*/
HRESULT RetrieveRegistrationCookie(long* cookie) {
  ATLASSERT(cookie != NULL);
  CRegKey key;
  LONG res = key.Open(HKEY_CURRENT_USER, CONSOLE_CONFIG_KEY, KEY_READ);
  if (res != ERROR_SUCCESS)
    return AtlHresultFromWin32(res);

  res = key.QueryDWORDValue(COOKIE_VALUE,
                            *reinterpret_cast<DWORD*>(cookie));
  ATLASSERT(res == ERROR_SUCCESS);
  return AtlHresultFromWin32(res);
}

HRESULT DeleteRegistrationCookie() {
  CRegKey key;
  LONG res = key.Open(HKEY_CURRENT_USER, SAMPLES_CONFIG_KEY);
  if (res != ERROR_SUCCESS)
    return AtlHresultFromWin32(res);

  res = key.DeleteSubKey(CONSOLE_CONFIG_KEY_NAME);
  return AtlHresultFromWin32(res);
}

HRESULT UnregisterFromGDEventFramework() {
  CComPtr<IGoogleDesktopRegistrar> registrar;
  HRESULT hr = registrar.CoCreateInstance(L"GoogleDesktop.Registrar");

  if (SUCCEEDED(hr)) {
    CComBSTR our_guid(CONSOLE_PLUGIN_GUID);
    hr = registrar->UnregisterComponent(our_guid);
    // If we have a stale registration, then we'll get E_INVALIDARG
    // since the guid hasn't been registered.  In that case, we'll
    // delete the cookie we have in the registry and return the
    // result of the registry operation
    if (SUCCEEDED(hr) || hr == E_INVALIDARG) {
      hr = DeleteRegistrationCookie();
    }
  }

  return hr;
}

void SafeStrCat(TCHAR *dest, const TCHAR *src, int dest_buffer_len) {
  if (!src || !dest)
    return;

  int current_len = lstrlen(dest);
  if (current_len >= (dest_buffer_len-1)) 
    return;
  int max_len = dest_buffer_len - 1 - current_len;
  lstrcpyn(dest+current_len, src, max_len+1);  // lstrcpyn inserts the NULL
}

HRESULT RegisterWithGDEventFramework() {
  CComPtr<IGoogleDesktopRegistrar> registrar;
  HRESULT hr = registrar.CoCreateInstance(L"GoogleDesktop.Registrar");

  if (SUCCEEDED(hr)) {
    CComBSTR our_guid(CONSOLE_PLUGIN_GUID);

    WCHAR icon_path[_MAX_PATH + 1] = {0};
    ATLVERIFY(::GetModuleFileNameW(NULL, icon_path, _MAX_PATH - 2) != 0);
    SafeStrCat(icon_path, L"@0", _MAX_PATH+1);

    CComSafeArray<VARIANT> description;
    ATLVERIFY(SUCCEEDED(description.Create(8)));
    VARIANT* props = reinterpret_cast<VARIANT*>(description.m_psa->pvData);

    for (DWORD i = 0; i < description.GetCount(); ++i) {
      props[i].vt = VT_BSTR;
    }

    props[0].bstrVal = ::SysAllocString(L"Title");
    props[1].bstrVal = ::SysAllocString(L"Console Events");
    props[2].bstrVal = ::SysAllocString(L"Description");
    props[3].bstrVal = ::SysAllocString(L"Outputs events from Google Desktop to the console");
    props[4].bstrVal = ::SysAllocString(L"Icon");
    props[5].bstrVal = ::SysAllocString(icon_path);
    props[6].bstrVal = ::SysAllocString(L"Homepage");
    props[7].bstrVal = ::SysAllocString(L"http://desktop.google.com");

    VARIANT desc;
    desc.vt = VT_ARRAY | VT_VARIANT;
    desc.parray = description;

    hr = registrar->StartComponentRegistration(our_guid, desc);

    if (SUCCEEDED(hr)) {
      CComPtr<IUnknown> unknown;
      hr = registrar->GetRegistrationInterface(CComBSTR(L"GoogleDesktop.EventRegistration"),
                                               &unknown);
      ATLASSERT(SUCCEEDED(hr));

      CComQIPtr<IGoogleDesktopRegisterEventPlugin> event_registration(unknown);
      if (event_registration != NULL) {
        long cookie = 0;
        hr = event_registration->RegisterPlugin(our_guid, &cookie);
        if (SUCCEEDED(hr)) {
          hr = registrar->FinishComponentRegistration();

          if (SUCCEEDED(hr)) {
            hr = StoreRegistrationCookie(cookie);
          }
        }
      }
    }
  }

  return hr;
}

HRESULT EnsureRegistered(long* cookie) {
  HRESULT hr = RetrieveRegistrationCookie(cookie);
  if (FAILED(hr)) {
    hr = RegisterWithGDEventFramework();
    if (SUCCEEDED(hr))
      hr = RetrieveRegistrationCookie(cookie);
  }

  return hr;
}
