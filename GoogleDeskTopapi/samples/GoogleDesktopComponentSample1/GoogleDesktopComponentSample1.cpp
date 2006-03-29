// GoogleDesktopComponentSample1.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include <atlstr.h>
#include "resource.h"
#include "GoogleDesktopComponentSample1.h"

#include <initguid.h>
#include "GoogleDesktopComponentSample1_i.c"

class CGoogleDesktopComponentSample1Module : public CAtlDllModuleT< CGoogleDesktopComponentSample1Module >
{
public :
  DECLARE_LIBID(LIBID_sampleLib)
  DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SAMPLE, "{1CC8E0A6-B570-44B3-BED0-FAF9823C839D}")
};

CGoogleDesktopComponentSample1Module _AtlModule;


// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
  hInstance;
  return _AtlModule.DllMain(dwReason, lpReserved); 
}


// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
  return _AtlModule.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
  return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
  // registers object, typelib and all interfaces in typelib
  HRESULT hr = _AtlModule.DllRegisterServer();

  if (SUCCEEDED(hr))
  {
      // Create our icon path 
      CStringW module_name;
      CStringW icon_name;
      ::GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), CStrBufW(module_name, 1024), 1023);
      icon_name.Format(L"%ls,%d", module_name, IDI_REGISTRATIONICON);

      // register our module
      const wchar_t *suffixes[] = { L"lnk" };
      hr = RegisterIndexingComponentHelper(CLSID_IndexShortcut, 
                    L"Shortcut Crawler", 
                    L"Indexes shortcut files", 
                    icon_name, 1, suffixes);
  }

  return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
  HRESULT hr = UnregisterComponentHelper(CLSID_IndexShortcut);
  // ignore error...
  
  hr = _AtlModule.DllUnregisterServer();

  return hr;
}
