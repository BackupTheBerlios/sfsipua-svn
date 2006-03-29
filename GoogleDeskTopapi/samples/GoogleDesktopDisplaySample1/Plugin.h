// Plugin.h : Declaration of the CSamplePlugin

#ifndef PLUGIN_H
#define PLUGIN_H

#include "resource.h"
#include "GoogleDesktopDisplaySample1.h"
#include <shlobj.h>
#include <shlguid.h>

class CSamplePlugin;

// CSamplePluginMsgOnlyWindow: message only window for our sample

class CSamplePluginMsgOnlyWindow : 
  public CWindowImpl<CSamplePluginMsgOnlyWindow> {
public:
  bool Init(CSamplePlugin *plugin);

  // message map
  BEGIN_MSG_MAP(CSamplePluginMsgOnlyWindow)
    MESSAGE_HANDLER(WM_TIMER, OnTimer);
  END_MSG_MAP()

  LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
private:
  CSamplePlugin *m_plugin;
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
class CSamplePluginContentItem :
    public CComObjectRootEx<CComSingleThreadModel>,
    public IDispatchImpl<IGoogleDesktopDisplayContentItemHandler,
      &IID_IGoogleDesktopDisplayContentItemHandler, &LIBID_SampleLib,
      /*wMajor =*/ 1, /*wMinor =*/ 0> {
public:
  BEGIN_COM_MAP(CSamplePluginContentItem)
    COM_INTERFACE_ENTRY(IGoogleDesktopDisplayContentItemHandler)
    // the next statement causes the content item to be aggregated from the 
    // ContentItemHelper object that is exposed by the API. The variable 
    // 'm_contentItemHelper' will hold the helper object.
    COM_INTERFACE_ENTRY_AUTOAGGREGATE_BLIND(m_contentItemHelper.p,
      CLSID_GoogleDesktopDisplayContentItemHelper)
  END_COM_MAP()

public:
  DECLARE_GET_CONTROLLING_UNKNOWN()

  CSamplePluginContentItem() {
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
typedef CComObject<CSamplePluginContentItem> CSamplePluginContentItemImpl;

// CSamplePlugin: the actual sidebar plugin. Implements a very simple ActiveX control that
// shows a list of items, each item is a string displaying a number. The items keep on rotating
// their values displaying how a typical sidebar plugin showing real time info would work.
//
// The plugin aggregates from the GoogleDesktopDisplayPluginHelper COM object that is provided
// by the sidebar. This COM object implements a complete ActiveX control and provides a standard
// mechanism to display the content of the plugin. Apart from the standard interfaces required
// for an ActiveX control, we have to implement many other interfaces given here to fully
// utilize the features provided by the sidebar and the PluginHelper object.

class ATL_NO_VTABLE CSamplePlugin : 
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CSamplePlugin, &CLSID_SamplePlugin>,
  public IGoogleDesktopDisplayPluginHandler,
  public IPersistStreamInitImpl<CSamplePlugin>,
  public ISpecifyPropertyPagesImpl<CSamplePlugin>,
  public IObjectWithSiteImpl<CSamplePlugin>,
  public IContextMenu,
  public IDispatchImpl<ISamplePlugin, &IID_ISamplePlugin, &LIBID_SampleLib, /*wMajor =*/ 1, /*wMinor =*/ 0> {
public:
  // default constructor
  CSamplePlugin();
  // one time init function
  HRESULT StartDisplayingItems();
  // called each time the display has to be updated. If 'refreshOnly' is true the rotate
  // counter is not updated, else it is updated and moved to next value.
  void ChangeItems(bool refreshOnly);
  // Helper to set the content layout
  void SetContentLayout();
  // set the plugin's title as per what mode we are in
  void UpdateTitle();

DECLARE_REGISTRY_RESOURCEID(IDR_SAMPLEPLUGIN)

BEGIN_COM_MAP(CSamplePlugin)
  COM_INTERFACE_ENTRY(ISamplePlugin)
  COM_INTERFACE_ENTRY(IDispatch)
  COM_INTERFACE_ENTRY(IObjectWithSite)
  COM_INTERFACE_ENTRY(IGoogleDesktopDisplayPluginHandler)
  COM_INTERFACE_ENTRY(IPersistStreamInit)
  COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
  COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
  COM_INTERFACE_ENTRY_IID(IID_IContextMenu, IContextMenu)
  // the next statement makes the plugin to be aggregated from the 'PluginHelper' object that
  // is exposed by the sidebar. The variable 'm_pluginHelper' will hold the helper object.
  COM_INTERFACE_ENTRY_AUTOAGGREGATE_BLIND(m_pluginHelper.p, CLSID_GoogleDesktopDisplayPluginHelper)
END_COM_MAP()

BEGIN_PROP_MAP(CSamplePlugin)
  // serializable data members, used by IPersistPropertyImpl
  PROP_DATA_ENTRY("item_start", m_itemStart, VT_UI4)
  PROP_DATA_ENTRY("paused", m_paused, VT_BOOL)
  PROP_DATA_ENTRY("content_layout", m_contentLayout, VT_I4)
  PROP_DATA_ENTRY("show_images", m_showImages, VT_BOOL)
  // property pages, used by ISpecifyPropertyPagesImpl
  PROP_PAGE(CLSID_SamplePluginPropertyPage)
END_PROP_MAP()

  DECLARE_GET_CONTROLLING_UNKNOWN()
  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct();
  void FinalRelease();

  STDMETHOD(get_ItemStart)(ULONG* pVal);
  STDMETHOD(put_ItemStart)(ULONG newVal);
  STDMETHOD(get_ContentLayout)(LONG* pVal);
  STDMETHOD(put_ContentLayout)(LONG newVal);

  // IPersistStreamInit
  STDMETHOD(InitNew)();
  STDMETHOD(Load)(LPSTREAM stream);

  // IContextMenu
  STDMETHOD(QueryContextMenu)(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
  STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO lpici);
  STDMETHOD(GetCommandString)(UINT_PTR idCmd, UINT uType, UINT * pwReserved, LPSTR pszName, UINT cchMax);

  // IGoogleDesktopDisplayPluginHandler
  STDMETHOD(OnCommand) (GoogleDesktopDisplayPluginCommand command);
  STDMETHOD(OnDisplayStateChange)(GoogleDesktopDisplayTileDisplayState display_state);
public:
  bool m_firstTime;
  CComPtr<IPicture> m_smallIcon, m_largeIcon, m_contentIcon1, m_contentIcon2;
  UINT32 m_itemStart;               // start value for items to display, persistent property
  int m_itemRotate;                 // current rotate value for items, not persistent
  VARIANT_BOOL m_paused, m_showImages;
  LONG m_contentLayout;
  CSamplePluginMsgOnlyWindow m_msgOnlyWindow;  // used for managing timers
  BOOL m_bRequiresSave;             // used by IPersistStreamInitImpl
  CComPtr<IUnknown> m_pluginHelper; // aggregated helper object exposed by the sidebar

  int m_totalItemsCreatedCount;   // used to show in minimized mode
};

OBJECT_ENTRY_AUTO(__uuidof(SamplePlugin), CSamplePlugin)

#endif    // PLUGIN_H
