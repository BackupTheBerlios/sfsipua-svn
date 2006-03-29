// Copyright 2005 Google Inc
// All rights reserved
// 
// CurrencyConversionSamplePlugin.cpp : Implementation 

#include "stdafx.h"
#include <atlcomtime.h>
#include "Plugin.h"
#include "Currencies.h"
#include "../common/utils.h"

enum {
  MenuOffsetInvert = 0,
};

enum {
  kTitleRotate = 7 * 1000, // 7 seconds
};

const BSTR kDefaultItems = _T("GBP,0.0,EUR,0.0");

// CCurrencyConversionSamplePluginMsgOnlyWindow: Used for handling 
//       messages since the plugin could be a windowless control

bool MsgOnlyWindow::Init(CCurrencyConversionSamplePlugin *plugin) {
  m_plugin = plugin;
  ATLVERIFY(Create(HWND_MESSAGE) != NULL);
  SetTimer(0xFFFF, kTitleRotate); // will be killed by Destroy Window
  return true;
}

LRESULT MsgOnlyWindow::OnInitPlugin(UINT, WPARAM, LPARAM, BOOL& bHandled) {
  bHandled = true;
  m_plugin->InitFromSavedLastCurrencies();
  HRESULT hr = m_plugin->StartDisplayingItems();
  ATLVERIFY(SUCCEEDED(hr));
  return 0;
}

LRESULT MsgOnlyWindow::OnCurrencyRate(UINT, WPARAM, LPARAM lp, BOOL& bHandled) {
  bHandled = true;
  CString acode = reinterpret_cast<WCHAR*>(lp);
  double rate = m_plugin->m_currencies->GetExchangeRate(acode);
  CString message;
  message.Format(_T("%s %.6f\n"), acode, rate);
  m_plugin->ChangeItems(acode);
  return 0;
}

LRESULT MsgOnlyWindow::OnTimer(UINT, WPARAM, LPARAM, BOOL& bHandled) {
  bHandled = true;
  m_plugin->UpdateTitle(true);
  return 0;
}

// CCurrencyConversionSamplePluginContentItem members

// OpenItem is called when user double clicks on the item.
// Something more intelegent may be done here in future.

STDMETHODIMP CCurrencyConversionSamplePluginContentItem::OpenItem() {
  CComBSTR heading;
  CComQIPtr<IGoogleDesktopDisplayContentItemHelper> helper(m_contentItemHelper);
  ATLVERIFY(SUCCEEDED(helper->get_heading(&heading)));
  MessageBox(NULL, heading, _T("Currency Exchange Rate"), MB_OK);
  return S_OK;
}

STDMETHODIMP CCurrencyConversionSamplePluginContentItem::GetIsTooltipRequired(
    GoogleDesktopDisplayTarget /*target*/, HDC /*dc*/, const RECT* /*bounds*/,
    VARIANT_BOOL* /*is_required*/) {
  return E_NOTIMPL; // let the ContentItemHelper object do the default stuff
}

STDMETHODIMP CCurrencyConversionSamplePluginContentItem::DrawItem(
    GoogleDesktopDisplayTarget /*target*/, HDC /*dc*/, const RECT* /*bounds*/) {
  return E_NOTIMPL; // let the ContentItemHelper object do the default drawing
}

STDMETHODIMP CCurrencyConversionSamplePluginContentItem::GetHeight(
    GoogleDesktopDisplayTarget /*target*/, HDC /*dc*/, 
    long /*width*/, long * /*height*/) {
  return E_NOTIMPL; // let the ContentItemHelper object do the default drawing
}

STDMETHODIMP CCurrencyConversionSamplePluginContentItem::
    ToggleItemPinnedState() {
  return E_NOTIMPL; // let the ContentItemHelper object do the default action
}

STDMETHODIMP CCurrencyConversionSamplePluginContentItem::OnDetailsView(
    BSTR* title, GoogleDesktopDisplayDetailsViewFlags* flags,
    IUnknown** details_control, VARIANT_BOOL* /*cancel*/) {
  // Get the item to be displayed
  CComQIPtr<IGoogleDesktopDisplayContentItemHelper> helper(m_contentItemHelper);
  ATLASSERT(helper != NULL);
  if (!helper)
    return E_INVALIDARG;

  // Here we can create any ActiveX control for displaying the details, and 
  // return it via the details_control parameter.  We choose the 
  // 'GoogleDesktopDisplayDetailsViewHelper' control that will give us a 
  // UI that's inline with how the sidebar looks.
  CComPtr<IGoogleDesktopDisplayDetailsViewHelper> details;
  HRESULT hr = details.CoCreateInstance(
      CLSID_GoogleDesktopDisplayDetailsViewHelper);
  if (SUCCEEDED(hr)) {
    GoogleDesktopDisplayContentItemLayout layout;
    ATLVERIFY(SUCCEEDED(helper->get_layout(&layout)));
    CComBSTR detailsSource;
    ATLVERIFY(SUCCEEDED(helper->get_source(&detailsSource)));
    DATE timeCreated;
    ATLVERIFY(SUCCEEDED(helper->get_time_created(&timeCreated)));
    ATLVERIFY(SUCCEEDED(helper->get_heading(title)));

    CComBSTR detailsText(L"XXX Details");
    details->SetContent(detailsSource, timeCreated, detailsText, FALSE, layout);

    *details_control = details.Detach();
    *flags = static_cast<GoogleDesktopDisplayDetailsViewFlags>(
              GDD_DETAILS_VIEW_FLAG_TOOLBAR_OPEN | 
              GDD_DETAILS_VIEW_FLAG_NEGATIVE_FEEDBACK);
  }

  return hr;
}

STDMETHODIMP CCurrencyConversionSamplePluginContentItem::
    ProcessDetailsViewFeedback(GoogleDesktopDisplayDetailsViewFlags dv_flags) {
  if (dv_flags & GDD_DETAILS_VIEW_FLAG_NEGATIVE_FEEDBACK) {
    CComQIPtr<IGoogleDesktopDisplayContentItemHelper> helper(m_contentItemHelper);
    CComBSTR heading;
    ATLVERIFY(SUCCEEDED(helper->get_heading(&heading)));

    CString str(_T("Not interesting: "));
    str += heading;
    MessageBox(NULL, str, L"", MB_OK);
  }
  if (dv_flags & GDD_DETAILS_VIEW_FLAG_TOOLBAR_OPEN) {
    OpenItem();
  }
  return S_OK;
}

//------ CCurrencyConversionSamplePlugin: the actual plugin class

CCurrencyConversionSamplePlugin::CCurrencyConversionSamplePlugin() :
  m_invert(VARIANT_FALSE), m_firstTime(true), m_currencies(NULL) {
  ATLVERIFY(m_msgOnlyWindow.Init(this));
  m_currencies = new Currencies(m_msgOnlyWindow.m_hWnd);
  m_bstrCurrencies = SysAllocString(kDefaultItems);
}

HRESULT CCurrencyConversionSamplePlugin::FinalConstruct() {
  return S_OK;
}

void CCurrencyConversionSamplePlugin::FinalRelease() {
  delete m_currencies;
  if (m_msgOnlyWindow.IsWindow())
    m_msgOnlyWindow.DestroyWindow();
  m_pluginHelper.Release();
  SysFreeString(m_bstrCurrencies);
}

CString CCurrencyConversionSamplePlugin::GetCurrencies() {
  CString s = m_bstrCurrencies;
  return s;
}

extern HINSTANCE ghInstance; // see GoogleDesktopCurrencyConversionSample.cpp

// initialization

HRESULT CCurrencyConversionSamplePlugin::StartDisplayingItems() {
  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(m_pluginHelper);
  if (m_pluginHelper == NULL)
    return E_FAIL;

  // set flags
  GoogleDesktopDisplayPluginFlags plugin_flags = GDD_PLUGIN_FLAG_NONE;
  GoogleDesktopDisplayContentFlags content_flags = GDD_CONTENT_FLAG_NONE;
  ATLVERIFY(SUCCEEDED(helper->SetFlags(plugin_flags, content_flags)));

  // set about text
  CComBSTR about_text;
  about_text.LoadString(IDS_COPYRIGHT);
  ATLVERIFY(SUCCEEDED(helper->put_about_text(about_text)));

  // set icons
  CComPtr<IPicture> title_icon, about_icon;
  ATLVERIFY(SUCCEEDED(::LoadPictureFromResource(ghInstance,
    MAKEINTRESOURCE(IDR_GIF_CURRENCY_ICON_SMALL), L"GIF",
    &title_icon)));
  ATLVERIFY(SUCCEEDED(::LoadPictureFromResource(ghInstance,
    MAKEINTRESOURCE(IDR_GIF_CURRENCY_ICON_LARGE), L"GIF",
    &about_icon)));
  ATLVERIFY(SUCCEEDED(helper->SetIcons(title_icon, about_icon)));

  UpdateTitle(false);

  // display the first set of items
  SetContentLayout();
  ChangeItems(NULL);
  return S_OK;
}

// reset everything and start fresh with new layout

void CCurrencyConversionSamplePlugin::SetContentLayout() {
  m_firstTime = true;
  // some flags to test things out
  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(m_pluginHelper);
  UINT content_flags = 0;
  content_flags |= GDD_CONTENT_FLAG_PINNABLE;
  helper->SetFlags(
    static_cast<GoogleDesktopDisplayPluginFlags>(GDD_PLUGIN_FLAG_NONE),
    static_cast<GoogleDesktopDisplayContentFlags>(content_flags));
}

// In minimized mode no items are displayed by the plugin so we make use of 
// the title to show some useful information. 
// check if we are in minimized mode. 
// "m_spUnkSite" member comes from IObjectWithSiteImpl

void CCurrencyConversionSamplePlugin::UpdateTitle(bool onlyIfMinimized) {
  GoogleDesktopDisplayTileDisplayState display_state = 
    GDD_TILE_DISPLAY_STATE_RESTORED;
  CComQIPtr<IGoogleDesktopDisplaySite> sidebar_site(m_spUnkSite);
  if (sidebar_site != NULL) { // will be null during init time
    ATLVERIFY(SUCCEEDED(sidebar_site->get_display_state(&display_state)));
  }
  // format the title string to show (with number of items if we are minimized)
  CString name;
  name.LoadString(IDS_CURRENCYCONVERSIONSAMPLEPLUGIN);
  CString str = name;
  if (display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED) {
    CStringArray tokens;
    Currencies::Tokenize(GetCurrencies(), &tokens);
    ATLVERIFY(tokens.GetCount() % 2 == 0);
    CString acode;
    double rate = 0;
    for (int i = 0; i < (int)tokens.GetCount() * 2; i++) {
      int r = rand() * ((int)tokens.GetCount() - 1)/ RAND_MAX;
      ATLASSERT(0 <= r && r < (int)tokens.GetCount());
      acode = tokens.GetAt(r & ~0x1);
      rate = m_currencies->GetExchangeRate(acode);
      if (rate > 0) break;
    }
    if (rate > 0) {
      if (m_invert != VARIANT_FALSE)
        str.Format(_T("1 %s = %.5f USD"), acode, rate);
      else
        str.Format(_T("1 USD = %.5f %s"), rate, acode);
    }
  } else if (onlyIfMinimized) {
    return;
  }
  // set the title
  CComBSTR title(str);
  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(m_pluginHelper);
  ATLASSERT(helper != NULL);
  ATLVERIFY(SUCCEEDED(helper->put_title(title)));
}

// initializes the list of currencies from the saved string

void CCurrencyConversionSamplePlugin::InitFromSavedLastCurrencies() {
  CStringArray tokens;
  Currencies::Tokenize(GetCurrencies(), &tokens);
  ATLVERIFY(tokens.GetCount() % 2 == 0);
  bool kick = false;
  for (int i = 0; i < (int)tokens.GetCount(); i += 2) {
    CString currency = tokens.GetAt(i);
    CString ratestr = tokens.GetAt(i + 1);
    double rate = _wtof(ratestr);
    if (rate > 0) m_currencies->SetExchangeRate(currency, rate);
    else {
      m_currencies->Request(currency);
      kick = true;
    }
  }
  if (kick) m_currencies->KickRequests();
}

// the following method recreates items in Google Desktop sidebar and
// changes thies properties. Basically this will result in items being
// repainted. Some future optimization is possible to reflect only
// single item change.

void CCurrencyConversionSamplePlugin::ChangeItems(const TCHAR* acode) {
  CComQIPtr<IGoogleDesktopDisplayPluginHelper> pluginHelper(m_pluginHelper);
  ATLVERIFY(SUCCEEDED(pluginHelper->RemoveAllContentItems()));
  unused(acode); // TODO: can be used to optimize redraw
  CString result;
  CStringArray tokens;
  Currencies::Tokenize(GetCurrencies(), &tokens);
  SYSTEMTIME systime = {0};
  GetSystemTime(&systime);
  ATLVERIFY(tokens.GetCount() % 2 == 0);
  for (int i = 0; i < (int)tokens.GetCount(); i += 2) {
    CString currency = tokens.GetAt(i);
    // create a new item
    CCurrencyConversionSamplePluginContentItemImpl *curItem = NULL;
    ATLVERIFY(SUCCEEDED(CCurrencyConversionSamplePluginContentItemImpl::
      CreateInstance(&curItem)));
    CComPtr<IGoogleDesktopDisplayContentItemHelper> itemHelper = NULL;
    curItem->GetUnknown()->QueryInterface(
      IID_IGoogleDesktopDisplayContentItemHelper,
      reinterpret_cast<void**>(&itemHelper));
    // and set it's properties
    UINT flags = GDD_CONTENT_ITEM_FLAG_TIME_ABSOLUTE;
    CString strHeading;
    double rate = m_currencies->GetExchangeRate(currency);
    {
      CString s;
      s.Format(_T("%s,%.6f,"), currency, rate);
      result += s;
    }
    if (rate != 0.0) {
      if (m_invert != VARIANT_FALSE) {
          strHeading.Format(_T("1 %s = %.5f USD"), currency, 1.0 / rate);
      } else {
        strHeading.Format(_T("1 USD = %.5f %s"), rate, currency);
      }
    }
    else
      strHeading.Format(_T("%s ..."), currency);
    CComBSTR snippet;
    snippet.Append(L"1 USD in ");
    snippet.Append(currency);
    CComBSTR source(L"www.google.com");
    CComBSTR heading(strHeading);
    CString tt;
    tt.Format(_T("%s - currency of %s"), Currencies::GetCurrencyName(currency),
        Currencies::GetCountries(currency));
    CComBSTR tooltip = tt;
    DATE timeCreated;
    SystemTimeToVariantTime(&systime, &timeCreated);
    // do the actual setting of props
    ATLVERIFY(SUCCEEDED(itemHelper->put_heading(heading)));
    ATLVERIFY(SUCCEEDED(itemHelper->put_tooltip(tooltip)));
    ATLVERIFY(SUCCEEDED(itemHelper->put_source(source)));
    ATLVERIFY(SUCCEEDED(itemHelper->put_time_created(timeCreated)));
    ATLVERIFY(SUCCEEDED(itemHelper->put_snippet(snippet)));
    ATLVERIFY(SUCCEEDED(itemHelper->put_flags(
      static_cast<GoogleDesktopDisplayContentItemFlags>(flags))));
    ATLVERIFY(SUCCEEDED(itemHelper->put_layout(
      static_cast<GoogleDesktopDisplayContentItemLayout>(
        GDD_CONTENT_ITEM_LAYOUT_NOWRAP_ITEMS))));
    CComQIPtr<IGoogleDesktopDisplayContentItem> item(itemHelper);
    // Show the item in the sidebar and optionally in the notification 
    // window if the sidebar is auto-hidden.
    GoogleDesktopContentItemDisplayOptions item_flags = 
      static_cast<GoogleDesktopContentItemDisplayOptions>(
        GDD_ITEM_DISPLAY_IN_SIDEBAR | 
        GDD_ITEM_DISPLAY_AS_NOTIFICATION_IF_SIDEBAR_HIDDEN);
    ATLVERIFY(SUCCEEDED(pluginHelper->AddContentItem(item, item_flags)));
  }
  // if we are in minimized mode, update the title with latest info.
  GoogleDesktopDisplayTileDisplayState display_state = 
      GDD_TILE_DISPLAY_STATE_RESTORED;
  CComQIPtr<IGoogleDesktopDisplaySite> sidebar_site(m_spUnkSite);
  if (sidebar_site != NULL) // will be NULL during init time
    ATLVERIFY(SUCCEEDED(sidebar_site->get_display_state(&display_state)));

  if (display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED)
    UpdateTitle(false);

  m_firstTime = false;
  int n = result.GetLength();
  if (n > 0 && result.GetAt(n - 1) == L',') {
    result = result.Left(n - 1);
  }
  SysFreeString(m_bstrCurrencies);
  m_bstrCurrencies = SysAllocString(result);
}

// this method returns set of currencies as a coma separated list inside
// a string e.g. "USD,1.0,GBP,0.7"

STDMETHODIMP CCurrencyConversionSamplePlugin::get_Currencies(BSTR* pVal) {
  *pVal = SysAllocString(m_bstrCurrencies);
  return S_OK;
}

// this method accepts changed currencies string tokenize it and schedules
// requests for the new set of currencies

STDMETHODIMP CCurrencyConversionSamplePlugin::put_Currencies(BSTR pVal) {
  if (pVal == NULL || wcslen(pVal) == 0) {
    pVal = kDefaultItems;
  }
  SysFreeString(m_bstrCurrencies);
  m_bstrCurrencies = SysAllocString(pVal);
  CStringArray tokens;
  Currencies::Tokenize(CString(m_bstrCurrencies), &tokens);
  for (unsigned int i = 0; i < tokens.GetCount(); i+= 2) {
    CString acode = tokens.GetAt(i);
    m_currencies->Request(acode);
  }
  m_currencies->KickRequests();
  ChangeItems(NULL);
  return S_OK;
}

//------ IPersistStreamInit: load/store our properties

STDMETHODIMP CCurrencyConversionSamplePlugin::InitNew() {
  m_bstrCurrencies = SysAllocString(kDefaultItems);
  m_invert = VARIANT_FALSE;
  m_firstTime = true;
  HRESULT hr = IPersistStreamInitImpl<CCurrencyConversionSamplePlugin>::
      InitNew();
  if (SUCCEEDED(hr))
    hr = StartDisplayingItems();
  return hr;
}

STDMETHODIMP CCurrencyConversionSamplePlugin::Load(LPSTREAM stream) {
  HRESULT hr = IPersistStreamInitImpl<CCurrencyConversionSamplePlugin>::
      Load(stream);
  if (SUCCEEDED(hr)) {
    // All cuurency acodes are TLA. Coma ',' has to follow first TLA.
    // At least on TLA has to be present. If any conditions above are not
    // true - reinitialize to default.
    if (m_bstrCurrencies == NULL || m_bstrCurrencies[0] == 0 || 
        wcslen(m_bstrCurrencies) < 6 || m_bstrCurrencies[3] != L',') {
      // TODO: needs proper error reporting
      OutputDebugStringA("CCurrencyConversionSamplePlugin::Load: strange ...");
      OutputDebugString(m_bstrCurrencies);
      OutputDebugStringA("\n");
      if (m_bstrCurrencies != NULL) SysFreeString(m_bstrCurrencies);
      m_bstrCurrencies = SysAllocString(kDefaultItems);
    }
  }
  else {
      m_bstrCurrencies = SysAllocString(kDefaultItems);
  }
  ATLASSERT(m_msgOnlyWindow.IsWindow());
  // delay init because ::Load can be called on a different thread
  // that can create a racing with m_currencies initialization.
  m_msgOnlyWindow.PostMessage(MsgOnlyWindow::WM_INIT_PLUGIN, 0, 0);
  return hr;
}

// Members of IGoogleDesktopDisplayPluginHandler, called by the PluginHelper

// called when any toolbar button is clicked (back, forward etc..)
STDMETHODIMP CCurrencyConversionSamplePlugin::OnCommand(
    GoogleDesktopDisplayPluginCommand command) {
  if (command == GDD_CMD_ABOUT_DLG)
    return E_NOTIMPL; // let default about dialog show up
  return S_OK;
}

// called when the plugin tile's display state changes
STDMETHODIMP CCurrencyConversionSamplePlugin::OnDisplayStateChange(
    GoogleDesktopDisplayTileDisplayState display_state) {
  if (display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED || 
      display_state == GDD_TILE_DISPLAY_STATE_RESTORED) {
    // switching between minimized and normal mode, so update the title
    UpdateTitle(false);
  }
  return S_OK;
}

// Members of IContextMenu: Implement IContextMenu if your plugin wants to add 
// menu items to the plugin's context menu

int GetMenuItemPosition(HMENU menu, UINT id) {
  for (int i = 0; i < GetMenuItemCount(menu); i++) {
    MENUITEMINFO info = { 0 };
    info.cbSize = sizeof(info);
    info.fMask = MIIM_ID;
    GetMenuItemInfo(menu, i, TRUE, &info);
    if (info.wID == id)
      return i;
  }
  ATLASSERT(FALSE);
  return -1;
}

// Add menu items to the plugin's context menu in the sidebar
STDMETHODIMP CCurrencyConversionSamplePlugin::QueryContextMenu(
  HMENU dst, UINT /*indexMenu*/, UINT idCmdFirst, UINT /*idCmdLast*/,
  UINT /*uFlags*/) {
  // Add items to the menu
  CString str;
  str.LoadString(IDS_PAUSE);
  AppendMenu(dst, MF_STRING, idCmdFirst + MenuOffsetInvert, str);
  // check the relavent items
  if (m_invert != VARIANT_FALSE)
    CheckMenuItem(dst, idCmdFirst + MenuOffsetInvert, MF_BYCOMMAND | MF_CHECKED);
  return S_OK;
}

// Not used by the sidebar but required by ActiveX convention.
STDMETHODIMP CCurrencyConversionSamplePlugin::GetCommandString(
    UINT_PTR /*idCmd*/, UINT /*uType*/, UINT* /*pwReserved*/, LPSTR /*pszName*/, 
    UINT /*cchMax*/) {
  ATLTRACENOTIMPL("GetCommandString");
}

// Called when one of the plugin's context menu item is clicked.

STDMETHODIMP CCurrencyConversionSamplePlugin::InvokeCommand(
    LPCMINVOKECOMMANDINFO lpici) {
  switch (static_cast<int>(__int64(lpici->lpVerb))) {
    case MenuOffsetInvert:
      m_invert = (m_invert != VARIANT_FALSE) ? VARIANT_FALSE : VARIANT_TRUE;
      ChangeItems(NULL);
      UpdateTitle(true);
      break;
    default:
      ATLASSERT(FALSE);
      break;
  }
  return S_OK;
}
