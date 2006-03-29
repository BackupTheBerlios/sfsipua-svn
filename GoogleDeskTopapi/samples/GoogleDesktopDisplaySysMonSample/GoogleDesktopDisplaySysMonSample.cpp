// Copyright 2005 Google Inc. All Rights Reserved.
//
// GoogleDesktopDisplaySysMonSample.cpp : Implementation of DLL Exports.
#include "stdafx.h"

#include <windows.h>
#include <atlbase.h>
#include <atlstr.h>

#include "GoogleDesktopDisplaySysMonSample.h"
#include "GoogleDesktopDisplaySysMonSample_i.c"
#include "resource.h"

#include "../common/GoogleDesktopComponentRegistration.h"

class CGoogleDesktopDisplaySysMonSampleModule :
  public CAtlDllModuleT<CGoogleDesktopDisplaySysMonSampleModule> {
 public :
  DECLARE_LIBID(LIBID_GoogleDesktopDisplaySysMonSampleLib)
};

CGoogleDesktopDisplaySysMonSampleModule _AtlModule;
HMODULE _my_handle;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance,
                               DWORD dwReason,
                               LPVOID lpReserved) {
  _my_handle = static_cast<HMODULE>(hInstance);
  return _AtlModule.DllMain(dwReason, lpReserved);
}

// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void) {
  return _AtlModule.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) {
  return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void) {
  // registers object, typelib and all interfaces in typelib
  HRESULT hr = _AtlModule.DllRegisterServer();

  if (SUCCEEDED(hr)) {
    bool shows_notifications = false;

    CComBSTR title, desc;
    title.LoadString(IDS_SYSMON_PANEL_TITLE);
    desc.LoadString(IDS_SYSMON_PANEL_DESCRIPTION);

    // register our module
    hr = RegisterDisplayComponentHelper(__uuidof(SysMonPlugin),
                                        title,
                                        desc,
                                        _T(""),
                                        shows_notifications);
  }

  return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void) {
  HRESULT hr;

  hr = UnregisterComponentHelper(__uuidof(SysMonPlugin));
  // Ignore error...

  hr = _AtlModule.DllUnregisterServer();
  return hr;
}
