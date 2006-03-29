// Copyright 2005 Google, Inc
// All Rights Reserved
//
// ActionSample.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "ActionSample.h"
#include "EmailActions.h"
#include "IMActions.h"
#include "SearchActions.h"
#include "../common/GoogleDesktopAPI.h"
#include "../common/GoogleDesktopComponentRegistration.h"
#include "ActionSample_i.c"
#include <atlsafe.h>

// {0F46C17B-39FA-4df6-BFFC-29696A531219}
static const GUID ActionSampleCanonicalName = 
{ 0xf46c17b, 0x39fa, 0x4df6, { 0xbf, 0xfc, 0x29, 0x69, 0x6a, 0x53, 0x12, 0x19 } };

// ATL module for the action sample. 
// Overridden DllregisterServer/UnregisterServer takes care of registration
class CActionSampleModule : public CAtlDllModuleT< CActionSampleModule >
{
public :
  typedef CAtlDllModuleT< CActionSampleModule > Super;
  DECLARE_LIBID(LIBID_ActionSampleLib)
  /// DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ACTIONSAMPLE, "{6F364FE1-8D4D-407A-9DD5-8013AD60ABC1}")

  HRESULT DllRegisterServer() {
    HRESULT hr = Super::DllRegisterServer();
    if (FAILED(hr))
      return hr;

    CComPtr<IGoogleDesktopRegistrar> spRegistrar;
    hr = spRegistrar.CoCreateInstance(CLSID_GoogleDesktopRegistrar);
    if (FAILED(hr))
      return hr;

    // Build the description array
    // Consists of name/value pairs at adjacent array indices
    CComSafeArray<VARIANT> descr;
    descr.Add(CComVariant(L"Title"));
    descr.Add(CComVariant(L"A sample action plugin"));

    descr.Add(CComVariant(L"Description"));
    descr.Add(CComVariant(L"Implements sample custom actions in a couple of different objects; \n"
                          L"EmailActions, IMActions, SearchActions"));

    descr.Add(CComVariant(L"Icon"));
    descr.Add(CComVariant(L",1"));

    descr.Add(CComVariant(L"Homepage"));
    descr.Add(CComVariant(L"http://www.google.com"));

    // Start the registration, nothing is committed until 
    // FinishComponentRegistration is invoked.
    hr = spRegistrar->StartComponentRegistration(CComBSTR(ActionSampleCanonicalName), CComVariant(descr));
    if (FAILED(hr))
      return hr;

    // Registering actions, so ask for that reg component.
    CComPtr<IUnknown> reg;
    hr = spRegistrar->GetRegistrationInterface(
                CComBSTR("GoogleDesktop.ActionRegistration"), &reg);
    if (FAILED(hr))
      return hr;

    // Registering and QI to the appropriate interface.
    CComPtr<IGoogleDesktopRegisterCustomAction> action_registration;
    hr = reg.QueryInterface(&action_registration);
    if (FAILED(hr))
      return hr;

    // Lists the actions we want to register and their associated CLSIDs
    struct ActionRegInfo { 
        const CLSID &object;
        const ACTION_ID &action;
    };
    static ActionRegInfo regs[] = {
      { CLSID_EmailActions, ACTION_EMAIL_FORWARD },
      { CLSID_EmailActions, ACTION_EMAIL_REPLY },
      { CLSID_IMActions, ACTION_IM_CHAT },
      { CLSID_SearchActions, ACTION_OPEN_SEARCH_RESULT },
    };

    // Do the registrations
    for(int i = 0; SUCCEEDED(hr) && i < sizeof(regs) / sizeof(*regs); i++) {
      ActionRegInfo &reg = regs[i];

      hr = action_registration->RegisterAction(CComBSTR(reg.object), 
                    CComBSTR(reg.action), CComVariant());
    }

    // aaaaaaaannd it's a wrap
    if (SUCCEEDED(hr))
      hr = spRegistrar->FinishComponentRegistration();

    return hr;
  }

  HRESULT DllUnregisterServer() {
    HRESULT hr = Super::DllUnregisterServer();
    if (FAILED(hr))
      return hr;

    CComPtr<IGoogleDesktopRegistrar> spRegistrar;
    hr = spRegistrar.CoCreateInstance(CLSID_GoogleDesktopRegistrar);
    if (FAILED(hr))
      return hr;

    /// unregister us with GDS...      
    hr = spRegistrar->UnregisterComponent(CComBSTR(ActionSampleCanonicalName));
    
    return hr;
  }
};

CActionSampleModule _AtlModule;

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
    /// registers object, typelib and all interfaces in typelib
  HRESULT hr = _AtlModule.DllRegisterServer();
  return hr;
}

// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
  HRESULT hr = _AtlModule.DllUnregisterServer();
  return hr;
}
