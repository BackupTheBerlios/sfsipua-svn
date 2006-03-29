// GoogleDesktopComponentGVI.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include <atlstr.h>
#include "resource.h"
#include "../common/GoogleDesktopComponentRegistration.h"
#include "google_desktop_component.h"

class CGoogleDesktopComponentGVIModule : public 
  CAtlDllModuleT< CGoogleDesktopComponentGVIModule > {
public :
  DECLARE_LIBID(LIBID_GoogleDesktopComponentGVILib)
  DECLARE_REGISTRY_APPID_RESOURCEID(IDR_GOOGLEDESKTOPCOMPONENTGVI, "{76B84A8C-AD86-43C6-963E-DC240CD7E6F6}")
};

CGoogleDesktopComponentGVIModule _AtlModule;


// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason,
							   LPVOID lpReserved) {
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

  if (SUCCEEDED(hr))
  {
	// Create our icon path 
	CStringW module_name;
	CStringW icon_name;
	::GetModuleFileNameW(_AtlBaseModule.GetModuleInstance(), CStrBufW(module_name, 1024), 1023);
	icon_name.Format(L"%ls,%d", module_name, IDI_ICON_GVI);

	// register our module
	const wchar_t *suffixes[] = { L"gvi" };
	hr = RegisterIndexingComponentHelper(CLSID_gvi_plugin, 
	  L"GVI Crawler", 
	  L"Indexes GVI files", 
	  icon_name, 1, suffixes);
  }

  return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void) {
  HRESULT hr = UnregisterComponentHelper(CLSID_gvi_plugin);
  hr = _AtlModule.DllUnregisterServer();
  return hr;
}
