// DetailsView.h : Declaration of the C[!output PROJECT_NAME]PluginDetailsView

#ifndef DETAILS_VIEW_H
#define DETAILS_VIEW_H

// C[!output PROJECT_NAME]PluginDetailsView: custom details view for the content items
class ATL_NO_VTABLE C[!output PROJECT_NAME]PluginDetailsView : 
  public CComObjectRootEx<CComSingleThreadModel>,
  public IDispatchImpl<I[!output PROJECT_NAME]PluginDetailsView, &IID_I[!output PROJECT_NAME]PluginDetailsView,
    &LIBID_[!output PROJECT_NAME]Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
  public IOleControlImpl<C[!output PROJECT_NAME]PluginDetailsView>,
  public IOleObjectImpl<C[!output PROJECT_NAME]PluginDetailsView>,
  public IOleInPlaceActiveObjectImpl<C[!output PROJECT_NAME]PluginDetailsView>,
  public IViewObjectExImpl<C[!output PROJECT_NAME]PluginDetailsView>,
  public IOleInPlaceObjectWindowlessImpl<C[!output PROJECT_NAME]PluginDetailsView>,
  public CComCoClass<C[!output PROJECT_NAME]PluginDetailsView, &CLSID_[!output PROJECT_NAME]PluginDetailsView>,
  public CComControl<C[!output PROJECT_NAME]PluginDetailsView> {
public:

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE | 
  OLEMISC_CANTLINKINSIDE | 
  OLEMISC_INSIDEOUT | 
  OLEMISC_ACTIVATEWHENVISIBLE | 
  OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_DETAILS_VIEW_RGS)

BEGIN_COM_MAP(C[!output PROJECT_NAME]PluginDetailsView)
  COM_INTERFACE_ENTRY(I[!output PROJECT_NAME]PluginDetailsView)
  COM_INTERFACE_ENTRY(IDispatch)
  COM_INTERFACE_ENTRY(IViewObjectEx)
  COM_INTERFACE_ENTRY(IViewObject2)
  COM_INTERFACE_ENTRY(IViewObject)
  COM_INTERFACE_ENTRY(IOleInPlaceObject)
  COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
  COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
  COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
  COM_INTERFACE_ENTRY(IOleControl)
  COM_INTERFACE_ENTRY(IOleObject)
END_COM_MAP()

BEGIN_MSG_MAP(C[!output PROJECT_NAME]PluginDetailsView)
  CHAIN_MSG_MAP(CComControl<C[!output PROJECT_NAME]PluginDetailsView>)
  DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// IViewObjectEx
  DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// I[!output PROJECT_NAME]PluginDetailsView
public:
  C[!output PROJECT_NAME]PluginDetailsView();

  HRESULT OnDraw(ATL_DRAWINFO& di); // The function which displays the details view data

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct();
  void FinalRelease();

  HRESULT OnPostVerbInPlaceActivate();

  STDMETHOD(SetContent)(BSTR text);

public:
  // data given by the plugin to display
  CString text_;
};

OBJECT_ENTRY_AUTO(__uuidof([!output PROJECT_NAME]PluginDetailsView),
  C[!output PROJECT_NAME]PluginDetailsView)

#endif  // DETAILS_VIEW_H
