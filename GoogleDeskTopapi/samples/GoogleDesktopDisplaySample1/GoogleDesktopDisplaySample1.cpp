// GDSBSample1.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "GoogleDesktopDisplaySample1.h"
#include "GoogleDesktopDisplaySample1_i.c"
#include "../common/GoogleDesktopComponentRegistration.h"
#include "Plugin.h"

class CSampleModule : public CAtlDllModuleT<CSampleModule> {
public :
  DECLARE_LIBID(LIBID_SampleLib)
};

CSampleModule _AtlModule;
HINSTANCE ghInstance;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
  ghInstance = hInstance;
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

// DllRegisterServer - registers object, typelib and all interfaces in typelib
STDAPI DllRegisterServer(void) {
  // registers object, typelib and all interfaces in typelib
  HRESULT hr = _AtlModule.DllRegisterServer();

  if (SUCCEEDED(hr)) {
      // Create our icon path 
      CStringW module_name;
      CStringW icon_name;
      ::GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), 
        CStrBufW(module_name, 1024), 1023);
      icon_name.Format(L"%ls,%d", module_name, IDI_PLUGIN);

      // set this to true if your plugin shows notifications, either by explicitly
      // using IGoogleDesktopDisplayNotifier or implicitly using
      // IGoogleDesktopDisplayPluginHelper::AddContentItem
      bool shows_notifications = false;

      // register our module
      hr = RegisterDisplayComponentHelper(__uuidof(SamplePlugin), 
                                          L"Sample Plugin", 
                                          L"Sample Display Plugin", 
                                          icon_name,
                                          shows_notifications);
  }

  return hr;
}

// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void) {
  HRESULT hr = UnregisterComponentHelper(__uuidof(SamplePlugin));
  // ignore error...

  return _AtlModule.DllUnregisterServer();
}
