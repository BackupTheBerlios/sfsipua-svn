// IndexShortcut.h : Declaration of the CIndexShortcut

#pragma once
#include "resource.h"       // main symbols

#include "GoogleDesktopComponentSample1.h"

// CIndexShortcut

class ATL_NO_VTABLE CIndexShortcut : 
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CIndexShortcut, &CLSID_IndexShortcut>,
  public ISupportErrorInfo,
  public IDispatchImpl<IIndexShortcut, &IID_IIndexShortcut, &LIBID_sampleLib, /*wMajor =*/ 1, /*wMinor =*/ 0> {
public:
  CIndexShortcut() {}

  DECLARE_REGISTRY_RESOURCEID(IDR_INDEXSHORTCUT)

  BEGIN_COM_MAP(CIndexShortcut)
    COM_INTERFACE_ENTRY(IIndexShortcut)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
  END_COM_MAP()

  // ISupportsErrorInfo
  STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct() {
    return S_OK;
  }
  
  void FinalRelease() {
  }

public:
  // IIndexShortcut implementation
  STDMETHOD(HandleFile)(BSTR full_path_to_file, IDispatch *event_factory);
};

OBJECT_ENTRY_AUTO(__uuidof(IndexShortcut), CIndexShortcut)
