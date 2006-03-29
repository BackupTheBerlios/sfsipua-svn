// Copyright 2005 Google Inc
// All rights reserved
// 
// GoogleDesktopCurrencyConversionSample.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "GoogleDesktopCurrencyConversionSample.h"
#include "GoogleDesktopCurrencyConversionSample_i.c"
#include "../common/GoogleDesktopComponentRegistration.h"
#include "Plugin.h"

#define countof(a) (sizeof(a) / sizeof((a)[0]))

class CSampleModule : public CAtlDllModuleT<CSampleModule> {
public :
  DECLARE_LIBID(LIBID_CurrencyConversionSampleLib)
};

CSampleModule _AtlModule;
HINSTANCE ghInstance;

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, 
    void* reserved) {
  ghInstance = hInstance;
  return _AtlModule.DllMain(dwReason, reserved); 
}

// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow() {
  return _AtlModule.DllCanUnloadNow();
}

// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) {
  return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - registers object, typelib and all interfaces in typelib
STDAPI DllRegisterServer() {
  // registers object, typelib and all interfaces in typelib
  HRESULT hr = _AtlModule.DllRegisterServer();
  if (SUCCEEDED(hr)) {
    // Create our icon path 
    CStringW module_name;
    CStringW icon_name;
    ::GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), 
      CStrBufW(module_name, 1024), 1023);
    icon_name.Format(L"%ls,%d", module_name, IDI_ICON);

    // set this to true if your plugin shows notifications, either by 
    // explicitly using IGoogleDesktopDisplayNotifier or implicitly using
    // IGoogleDesktopDisplayPluginHelper::AddContentItem
    bool shows_notifications = false;
    // register our module
    hr = RegisterDisplayComponentHelper(
        __uuidof(CurrencyConversionSamplePlugin), 
        L"Currency Converter", 
        L"Google Desktop Currency Conversion Display Plugin", 
        icon_name, shows_notifications);
  }
  return hr;
}

// DllUnregisterServer - removes entries from the system registry
STDAPI DllUnregisterServer(void) {
  // intentionally ignore error...
  UnregisterComponentHelper(__uuidof(CurrencyConversionSamplePlugin));
  return _AtlModule.DllUnregisterServer();
}
