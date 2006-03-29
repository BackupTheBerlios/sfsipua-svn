// PluginEntry.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "[!output PROJECT_NAME]_i.c"
#include <GoogleDesktopComponentRegistration.h>
#include "Plugin.h"

class C[!output PROJECT_NAME]Module : public CAtlDllModuleT<C[!output PROJECT_NAME]Module> {
public :
  DECLARE_LIBID(LIBID_[!output PROJECT_NAME]Lib)
};

C[!output PROJECT_NAME]Module _AtlModule;
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
    // set this to true if your plugin shows notifications, either by explicitly
    // using IGoogleDesktopDisplayNotifier or implicitly using
    // IGoogleDesktopDisplayPluginHelper::AddContentItem
    bool shows_notifications = false;

    // register our module
    hr = RegisterDisplayComponentHelper(__uuidof([!output PROJECT_NAME]Plugin), 
                                        L"[!output PROJECT_NAME] Plugin", 
                                        L"[!output PLUGIN_DESCRIPTION]", 
                                        L"",  // icon path, not used for display plugins
                                        shows_notifications);
  }

  return hr;
}

// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void) {
  HRESULT hr = UnregisterComponentHelper(__uuidof([!output PROJECT_NAME]Plugin));
  // ignore error...

  return _AtlModule.DllUnregisterServer();
}
