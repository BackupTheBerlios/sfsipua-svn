// Plugin.h : Declaration of the C[!output PROJECT_NAME]Plugin

#ifndef PLUGIN_H
#define PLUGIN_H

#include "resource.h"
#include <shlobj.h>
#include <shlguid.h>

class C[!output PROJECT_NAME]Plugin;

// C[!output PROJECT_NAME]PluginMsgOnlyWindow: message-only window used for creating timers.
// You can also use this window as a message queue to post messages to your plugin.

class C[!output PROJECT_NAME]PluginMsgOnlyWindow : 
  public CWindowImpl<C[!output PROJECT_NAME]PluginMsgOnlyWindow> {
public:
  bool Init(C[!output PROJECT_NAME]Plugin *plugin);

  // message map
  BEGIN_MSG_MAP(C[!output PROJECT_NAME]PluginMsgOnlyWindow)
    MESSAGE_HANDLER(WM_TIMER, OnTimer);
  END_MSG_MAP()

  LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
private:
  C[!output PROJECT_NAME]Plugin *m_plugin;
};

// This class implements one ContentItem which is displayed in the plugin's UI.
// This should suffice most simple plugins and can be expanded to suit your needs.
//
// This class aggregates from the GoogleDesktopDisplayContentItemHelper COM object 
// that is provided by the API. This COM object implements a complete content item
// and provides standard mechanism to display the content. Apart from the standard 
// interfaces required for a content item, we can choose to implement the content
// item handler interface which will be called when the item is clicked, pinned or
// its details view was opened by the user
class C[!output PROJECT_NAME]PluginContentItem :
    public CComObjectRootEx<CComSingleThreadModel>,
    public IDispatchImpl<IGoogleDesktopDisplayContentItemHandler,
      &IID_IGoogleDesktopDisplayContentItemHandler, &LIBID_[!output PROJECT_NAME]Lib,
      /*wMajor =*/ 1, /*wMinor =*/ 0> {
public:
  BEGIN_COM_MAP(C[!output PROJECT_NAME]PluginContentItem)
    COM_INTERFACE_ENTRY(IGoogleDesktopDisplayContentItemHandler)
    // the next statement causes the content item to be aggregated from the 
    // ContentItemHelper object that is exposed by the API. The variable 
    // 'm_contentItemHelper' will hold the helper object.
    COM_INTERFACE_ENTRY_AUTOAGGREGATE_BLIND(m_contentItemHelper.p,
      CLSID_GoogleDesktopDisplayContentItemHelper)
  END_COM_MAP()

public:
  DECLARE_GET_CONTROLLING_UNKNOWN()

  C[!output PROJECT_NAME]PluginContentItem() {
  }
  void FinalRelease() {
  }

  // IGoogleDesktopDisplayContentItemHandler
  STDMETHOD(DrawItem)(GoogleDesktopDisplayTarget target, HDC dc,  const RECT *bounds);
  STDMETHOD(GetHeight)(GoogleDesktopDisplayTarget target, HDC dc, long width, long *height);
  STDMETHOD(OpenItem)();
  STDMETHOD(ToggleItemPinnedState)();
  STDMETHOD(GetIsTooltipRequired)(GoogleDesktopDisplayTarget target, 
    HDC dc, const RECT *bounds, VARIANT_BOOL *is_required);
  STDMETHOD(OnDetailsView)(BSTR* title,
                           GoogleDesktopDisplayDetailsViewFlags* flags,
                           IUnknown** details_control,
                           VARIANT_BOOL* cancel);
  STDMETHOD(ProcessDetailsViewFeedback)(GoogleDesktopDisplayDetailsViewFlags flags);
  STDMETHOD(OnRemoveItem)(VARIANT_BOOL* cancel) {
    ATLASSERT(cancel != NULL);
    return E_NOTIMPL;
  }

public:
  CComPtr<IUnknown> m_contentItemHelper; // aggregated helper object exposed by the API
};
typedef CComObject<C[!output PROJECT_NAME]PluginContentItem> C[!output PROJECT_NAME]PluginContentItemImpl;

// C[!output PROJECT_NAME]Plugin: the actual sidebar plugin. Implements a very simple ActiveX control that
// shows a list of items, each item is a string displaying a number. The items keep on rotating
// their values displaying how a typical sidebar plugin showing real time info would work.
//
// The plugin aggregates from the GoogleDesktopDisplayPluginHelper COM object that is provided
// by the sidebar. This COM object implements a complete ActiveX control and provides a standard
// mechanism to display the content of the plugin. Apart from the standard interfaces required
// for an ActiveX control, we have to implement many other interfaces given here to fully
// utilize the features provided by the sidebar and the PluginHelper object.

class ATL_NO_VTABLE C[!output PROJECT_NAME]Plugin : 
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<C[!output PROJECT_NAME]Plugin, &CLSID_[!output PROJECT_NAME]Plugin>,
  public IGoogleDesktopDisplayPluginHandler,
  public IPersistStreamInitImpl<C[!output PROJECT_NAME]Plugin>,
  public ISpecifyPropertyPagesImpl<C[!output PROJECT_NAME]Plugin>,
  public IObjectWithSiteImpl<C[!output PROJECT_NAME]Plugin>,
[!if CUSTOM_MENU_ITEMS]
  public IContextMenu,
[!endif]
  public IDispatchImpl<I[!output PROJECT_NAME]Plugin, &IID_I[!output PROJECT_NAME]Plugin, &LIBID_[!output PROJECT_NAME]Lib, /*wMajor =*/ 1, /*wMinor =*/ 0> {
public:
  // default constructor
  C[!output PROJECT_NAME]Plugin();
  // one time init function
  HRESULT StartDisplayingItems();
  // called each time the display has to be updated.
  void ChangeItems(bool startFresh);
  // Called to add a new content item
  void AddNewContentItem();
  // set the plugin's title as per what mode we are in
  void UpdateTitle();

DECLARE_REGISTRY_RESOURCEID(IDR_PLUGIN_RGS)

BEGIN_COM_MAP(C[!output PROJECT_NAME]Plugin)
  COM_INTERFACE_ENTRY(I[!output PROJECT_NAME]Plugin)
  COM_INTERFACE_ENTRY(IDispatch)
  COM_INTERFACE_ENTRY(IObjectWithSite)
  COM_INTERFACE_ENTRY(IGoogleDesktopDisplayPluginHandler)
  COM_INTERFACE_ENTRY(IPersistStreamInit)
  COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
  COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
[!if CUSTOM_MENU_ITEMS]
  COM_INTERFACE_ENTRY_IID(IID_IContextMenu, IContextMenu)
[!endif]
  // the next statement makes the plugin to be aggregated from the 'PluginHelper' object that
  // is exposed by the sidebar. The variable 'm_pluginHelper' will hold the helper object.
  COM_INTERFACE_ENTRY_AUTOAGGREGATE_BLIND(m_pluginHelper.p, CLSID_GoogleDesktopDisplayPluginHelper)
END_COM_MAP()

BEGIN_PROP_MAP(C[!output PROJECT_NAME]Plugin)
  // serializable data members, used by IPersistPropertyImpl
[!if USE_PROPERTY_PAGE1]
  PROP_DATA_ENTRY("value1", m_Value1, VT_I4)
[!endif]
[!if USE_PROPERTY_PAGE2]
  PROP_DATA_ENTRY("value2", m_Value2, VT_I4)
[!endif]
[!if USE_PROPERTY_PAGE3]
  PROP_DATA_ENTRY("value3", m_Value3, VT_I4)
[!endif]
  // property pages, used by ISpecifyPropertyPagesImpl
[!if USE_PROPERTY_PAGE1]
  PROP_PAGE(CLSID_[!output PROJECT_NAME]PluginPropertyPage)
[!endif]
[!if USE_PROPERTY_PAGE2]
  PROP_PAGE(CLSID_[!output PROJECT_NAME]PluginPropertyPage2)
[!endif]
[!if USE_PROPERTY_PAGE3]
  PROP_PAGE(CLSID_[!output PROJECT_NAME]PluginPropertyPage3)
[!endif]
END_PROP_MAP()

  DECLARE_GET_CONTROLLING_UNKNOWN()
  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct();
  void FinalRelease();

[!if USE_PROPERTY_PAGE1]
  STDMETHOD(get_Value1)(LONG* pVal);
  STDMETHOD(put_Value1)(LONG newVal);
[!endif]
[!if USE_PROPERTY_PAGE2]
  STDMETHOD(get_Value2)(LONG* pVal);
  STDMETHOD(put_Value2)(LONG newVal);
[!endif]
[!if USE_PROPERTY_PAGE3]
  STDMETHOD(get_Value3)(LONG* pVal);
  STDMETHOD(put_Value3)(LONG newVal);
[!endif]

  // IPersistStreamInit
  STDMETHOD(InitNew)();
  STDMETHOD(Load)(LPSTREAM stream);
  STDMETHOD(Save)(LPSTREAM stream, BOOL clearDirty);

[!if CUSTOM_MENU_ITEMS]
  // IContextMenu
  STDMETHOD(QueryContextMenu)(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
  STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO lpici);
  STDMETHOD(GetCommandString)(UINT_PTR idCmd, UINT uType, UINT * pwReserved, LPSTR pszName, UINT cchMax);

[!endif]
  // IGoogleDesktopDisplayPluginHandler
  STDMETHOD(OnCommand) (GoogleDesktopDisplayPluginCommand command);
  STDMETHOD(OnDisplayStateChange)(GoogleDesktopDisplayTileDisplayState display_state);
public:
[!if USE_PROPERTY_PAGE1]
  int m_Value1;
[!endif]
[!if USE_PROPERTY_PAGE2]
  int m_Value2;
[!endif]
[!if USE_PROPERTY_PAGE3]
  int m_Value3;
[!endif]

  int m_itemCount;
  CComPtr<IPicture> m_smallIcon, m_largeIcon, m_contentIcon;
  C[!output PROJECT_NAME]PluginMsgOnlyWindow m_msgOnlyWindow;  // used for managing timers
  BOOL m_bRequiresSave;             // used by IPersistStreamInitImpl
  CComPtr<IUnknown> m_pluginHelper; // aggregated helper object exposed by the sidebar
};

OBJECT_ENTRY_AUTO(__uuidof([!output PROJECT_NAME]Plugin), C[!output PROJECT_NAME]Plugin)

#endif    // PLUGIN_H
