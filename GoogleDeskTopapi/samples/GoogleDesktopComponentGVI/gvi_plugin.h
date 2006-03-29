// gvi_plugin.h : Declaration of the CGIVPlugin

#pragma once
#include "resource.h"       // main symbols

#include "GoogleDesktopComponentGVI.h"


// CGIVPlugin

class ATL_NO_VTABLE CGIVPlugin : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CGIVPlugin, &CLSID_gvi_plugin>,
	public ISupportErrorInfo,
	public IDispatchImpl<Igvi_plugin, &IID_Igvi_plugin, &LIBID_GoogleDesktopComponentGVILib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CGIVPlugin()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_GVI_PLUGIN)


BEGIN_COM_MAP(CGIVPlugin)
	COM_INTERFACE_ENTRY(Igvi_plugin)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

  STDMETHOD(HandleFile)(BSTR full_path_to_file, IDispatch* factory_dispatch);
};

OBJECT_ENTRY_AUTO(__uuidof(gvi_plugin), CGIVPlugin)
