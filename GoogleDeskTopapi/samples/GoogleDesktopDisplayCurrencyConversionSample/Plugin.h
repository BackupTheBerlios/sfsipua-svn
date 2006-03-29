// Copyright 2005 Google Inc
// All rights reserved
// 
// Plugin.h : Declaration of the CCurrencyConversionSamplePlugin

#ifndef PLUGIN_H
#define PLUGIN_H

#include "resource.h"
#include "GoogleDesktopCurrencyConversionSample.h"
#include <shlobj.h>
#include <shlguid.h>
#include "currencies.h"

class CCurrencyConversionSamplePlugin;

class MsgOnlyWindow : 
  public CWindowImpl<MsgOnlyWindow> {
public:
  static const int WM_INIT_PLUGIN = WM_APP+1;

  bool Init(CCurrencyConversionSamplePlugin *plugin);

  BEGIN_MSG_MAP(MsgOnlyWindow)
    MESSAGE_HANDLER(Currencies::WM_CURRENCY_RATE, OnCurrencyRate)
    MESSAGE_HANDLER(WM_INIT_PLUGIN, OnInitPlugin)
    MESSAGE_HANDLER(WM_TIMER, OnTimer)
  END_MSG_MAP()

private:
  LRESULT OnInitPlugin(UINT msg, WPARAM wp, LPARAM lp, BOOL& bHandled);
  LRESULT OnCurrencyRate(UINT msg, WPARAM wp, LPARAM lp, BOOL& bHandled);
  LRESULT OnTimer(UINT msg, WPARAM wp, LPARAM lp, BOOL& bHandled);
  CCurrencyConversionSamplePlugin *m_plugin;
};

// This class implements one ContentItem which is displayed in the plugin's UI.
// This should suffice most simple plugins.
//
// This class aggregates from the GoogleDesktopDisplayContentItemHelper object 
// that is provided by the API. This object implements a complete content item
// and provides standard mechanism to display the content. Apart from the  
// standard interfaces required for a content item, we can choose to implement
// the contentitem handler interface which will be called when the item is 
// clicked, pinned or its details view was opened by the user...

class CCurrencyConversionSamplePluginContentItem :
    public CComObjectRootEx<CComSingleThreadModel>,
    public IDispatchImpl<IGoogleDesktopDisplayContentItemHandler,
      &IID_IGoogleDesktopDisplayContentItemHandler, 
      &LIBID_CurrencyConversionSampleLib,
      /*wMajor =*/ 1, /*wMinor =*/ 0> {
public:
  BEGIN_COM_MAP(CCurrencyConversionSamplePluginContentItem)
    COM_INTERFACE_ENTRY(IGoogleDesktopDisplayContentItemHandler)
    // the next statement causes the content item to be aggregated from the 
    // ContentItemHelper object that is exposed by the API. The variable 
    // 'm_contentItemHelper' will hold the helper object.
    COM_INTERFACE_ENTRY_AUTOAGGREGATE_BLIND(m_contentItemHelper.p,
      CLSID_GoogleDesktopDisplayContentItemHelper)
  END_COM_MAP()

public:
  DECLARE_GET_CONTROLLING_UNKNOWN()

  CCurrencyConversionSamplePluginContentItem() {
  }
  void FinalRelease() {
  }

  // IGoogleDesktopDisplayContentItemHandler
  STDMETHOD(DrawItem)(GoogleDesktopDisplayTarget target, HDC dc,  
      const RECT *bounds);
  STDMETHOD(GetHeight)(GoogleDesktopDisplayTarget target, HDC dc, 
      long width, long *height);
  STDMETHOD(OpenItem)();
  STDMETHOD(ToggleItemPinnedState)();
  STDMETHOD(GetIsTooltipRequired)(GoogleDesktopDisplayTarget target, 
    HDC dc, const RECT *bounds, VARIANT_BOOL *is_required);
  STDMETHOD(OnDetailsView)(BSTR* title,
                           GoogleDesktopDisplayDetailsViewFlags* flags,
                           IUnknown** details_control,
                           VARIANT_BOOL* cancel);
  STDMETHOD(ProcessDetailsViewFeedback)(GoogleDesktopDisplayDetailsViewFlags);
  STDMETHOD(OnRemoveItem)(VARIANT_BOOL* cancel) {
    ATLASSERT(cancel != NULL);
    unused(cancel); // in RELEASE
    return E_NOTIMPL;
  }

public:
  CComPtr<IUnknown> m_contentItemHelper; // aggregated helper object
};
typedef CComObject<CCurrencyConversionSamplePluginContentItem> 
  CCurrencyConversionSamplePluginContentItemImpl;

// CCurrencyConversionSamplePlugin: the actual sidebar plugin. 
//
// The plugin aggregates from the GoogleDesktopDisplayPluginHelper object that 
// is provided by the sidebar. This object implements a complete ActiveX control 
// and provides a standard mechanism to display the content of the plugin. 
// Apart from the standard interfaces required for an ActiveX control, 
// we have to implement many other interfaces given here to fully
// utilize the features provided by the sidebar and the PluginHelper object.

class ATL_NO_VTABLE CCurrencyConversionSamplePlugin : 
  public IDispatchImpl<ICurrencyConversionSamplePlugin, 
      &IID_ICurrencyConversionSamplePlugin, 
      &LIBID_CurrencyConversionSampleLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CCurrencyConversionSamplePlugin, 
      &CLSID_CurrencyConversionSamplePlugin>,
  public IGoogleDesktopDisplayPluginHandler,
  public IPersistStreamInitImpl<CCurrencyConversionSamplePlugin>,
  public ISpecifyPropertyPagesImpl<CCurrencyConversionSamplePlugin>,
  public IObjectWithSiteImpl<CCurrencyConversionSamplePlugin>,
  public IContextMenu {

public:
  CCurrencyConversionSamplePlugin();

DECLARE_REGISTRY_RESOURCEID(IDR_CURRENCYCONVERSIONSAMPLEPLUGIN)

BEGIN_COM_MAP(CCurrencyConversionSamplePlugin)
  COM_INTERFACE_ENTRY(ICurrencyConversionSamplePlugin)
  COM_INTERFACE_ENTRY(IDispatch)
  COM_INTERFACE_ENTRY(IObjectWithSite)
  COM_INTERFACE_ENTRY(IGoogleDesktopDisplayPluginHandler)
  COM_INTERFACE_ENTRY(IPersistStreamInit)
  COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
  COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
  COM_INTERFACE_ENTRY_IID(IID_IContextMenu, IContextMenu)
  // the next statement makes the plugin to be aggregated from the 
  // 'PluginHelper' object that is exposed by the sidebar. 
  // The variable 'm_pluginHelper' will hold the helper object.
  COM_INTERFACE_ENTRY_AUTOAGGREGATE_BLIND(m_pluginHelper.p, 
      CLSID_GoogleDesktopDisplayPluginHelper)
END_COM_MAP()

BEGIN_PROP_MAP(CCurrencyConversionSamplePlugin)
  // serializable data members, used by IPersistPropertyImpl
  PROP_DATA_ENTRY("invert", m_invert, VT_BOOL)
  PROP_DATA_ENTRY("currencies", m_bstrCurrencies, VT_BSTR)
  // property pages, used by ISpecifyPropertyPagesImpl
  PROP_PAGE(CLSID_CurrencyConversionSamplePropertyPage)
END_PROP_MAP()

  DECLARE_GET_CONTROLLING_UNKNOWN()
  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct();
  void FinalRelease();

  STDMETHOD(get_Currencies)(BSTR* pVal);
  STDMETHOD(put_Currencies)(BSTR pVal);

  // IPersistStreamInit
  STDMETHOD(InitNew)();
  STDMETHOD(Load)(LPSTREAM stream);

  // IContextMenu
  STDMETHOD(QueryContextMenu)(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, 
      UINT idCmdLast, UINT uFlags);
  STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO lpici);
  STDMETHOD(GetCommandString)(UINT_PTR idCmd, UINT uType, UINT * pwReserved, 
      LPSTR pszName, UINT cchMax);

  // IGoogleDesktopDisplayPluginHandler
  STDMETHOD(OnCommand) (GoogleDesktopDisplayPluginCommand command);
  STDMETHOD(OnDisplayStateChange)(GoogleDesktopDisplayTileDisplayState);

public: // have to be public for IPersistStreamInitImpl:
  BSTR m_bstrCurrencies;
  VARIANT_BOOL m_invert;
  BOOL m_bRequiresSave;

private:
  void InitFromSavedLastCurrencies();

  HRESULT StartDisplayingItems();

  // called each time the display has to be updated. 
  void ChangeItems(const TCHAR* acode);

  // Helper to set the content layout
  void SetContentLayout();

  // set the plugin's title as per what mode we are in
  void UpdateTitle(bool onlyIfMinimized);

  // returns csv list of currencies and rates like: "GBP,1.5,EUR,1.4"
  CString GetCurrencies();

  Currencies* m_currencies;
  bool m_firstTime;
  MsgOnlyWindow m_msgOnlyWindow;  // used for managing timers
  CComPtr<IUnknown> m_pluginHelper; // aggregated helper object
  friend MsgOnlyWindow;
};

OBJECT_ENTRY_AUTO(__uuidof(CurrencyConversionSamplePlugin), 
    CCurrencyConversionSamplePlugin)

#endif    // PLUGIN_H
