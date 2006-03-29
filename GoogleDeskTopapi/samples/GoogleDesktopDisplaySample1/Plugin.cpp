// SamplePlugin.cpp : Implementation of CSamplePlugin

#include "stdafx.h"
#include "Plugin.h"
#include <atlcomtime.h>

extern HINSTANCE ghInstance;

// local defines
const int kItemRotateMax = 6;
const int kItemRotateTimeMs = 25000;
const int kItemRotateTimerId = 1;

enum {
  MenuOffsetPause = 0,
  MenuSeparator1,
  MenuOffsetLayoutSingleLine,
  MenuOffsetLayoutNews,
  MenuOffsetLayoutEmail,
  MenuSeparator2,
  MenuOffsetShowImages
};

//------ CSamplePluginMsgOnlyWindow: Used for handling messages since the plugin could be
//------ a windowless control

bool CSamplePluginMsgOnlyWindow::Init(CSamplePlugin *plugin) {
  // create a message-only window
  if (Create(HWND_MESSAGE) == NULL)
    return false;

  m_plugin = plugin;
  // set a timer to keep rotating the displayed items
  SetTimer(kItemRotateTimerId, kItemRotateTimeMs, NULL);
  return true;
}

LRESULT CSamplePluginMsgOnlyWindow::OnTimer(UINT , WPARAM wp, LPARAM , BOOL& ) {
  if (static_cast<int>(wp) == kItemRotateTimerId && m_plugin->m_paused == VARIANT_FALSE)
    m_plugin->ChangeItems(false); // call the plugin to rotate displayed items
  return 0;
}

//------ CSamplePluginContentItem members

STDMETHODIMP CSamplePluginContentItem::OpenItem() {
  CComBSTR heading;
  CComQIPtr<IGoogleDesktopDisplayContentItemHelper> helper(m_contentItemHelper);
  ATLVERIFY(SUCCEEDED(helper->get_heading(&heading)));

  CString str(_T("Clicked: "));
  str += heading;
  MessageBox(NULL, str, _T(""), MB_OK);
  return S_OK;
}

STDMETHODIMP CSamplePluginContentItem::GetIsTooltipRequired(
    GoogleDesktopDisplayTarget target, HDC dc, const RECT *bounds,
    VARIANT_BOOL *is_required) {
  return E_NOTIMPL;   // let the ContentItemHelper object do the default stuff
}

STDMETHODIMP CSamplePluginContentItem::DrawItem(
    GoogleDesktopDisplayTarget target, HDC dc, const RECT *bounds) {
  return E_NOTIMPL;   // let the ContentItemHelper object do the default drawing
}

STDMETHODIMP CSamplePluginContentItem::GetHeight(
    GoogleDesktopDisplayTarget target, HDC dc, long width, long *height) {
  return E_NOTIMPL;   // let the ContentItemHelper object do the default drawing
}

STDMETHODIMP CSamplePluginContentItem::ToggleItemPinnedState() {
  return E_NOTIMPL;   // let the ContentItemHelper object do the default action
}

STDMETHODIMP CSamplePluginContentItem::OnDetailsView(BSTR* title,
                                          GoogleDesktopDisplayDetailsViewFlags* flags,
                                          IUnknown** details_control,
                                          VARIANT_BOOL* cancel) {
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
  HRESULT hr = details.CoCreateInstance(CLSID_GoogleDesktopDisplayDetailsViewHelper);
  if (SUCCEEDED(hr)) {
    GoogleDesktopDisplayContentItemLayout layout;
    ATLVERIFY(SUCCEEDED(helper->get_layout(&layout)));
    CComBSTR detailsSource;
    ATLVERIFY(SUCCEEDED(helper->get_source(&detailsSource)));
    DATE timeCreated;
    ATLVERIFY(SUCCEEDED(helper->get_time_created(&timeCreated)));
    ATLVERIFY(SUCCEEDED(helper->get_heading(title)));

    CComBSTR detailsText(L"Some sample text\r\n\r\nwithout formatting\r\nhttp://www.google.com");
    details->SetContent(detailsSource, timeCreated, detailsText, FALSE, layout);

    *details_control = details.Detach();
    *flags = static_cast<GoogleDesktopDisplayDetailsViewFlags>(
              GDD_DETAILS_VIEW_FLAG_TOOLBAR_OPEN | GDD_DETAILS_VIEW_FLAG_NEGATIVE_FEEDBACK);
  }

  return hr;
}

STDMETHODIMP CSamplePluginContentItem::ProcessDetailsViewFeedback(
  GoogleDesktopDisplayDetailsViewFlags dv_flags) {
  if (dv_flags & GDD_DETAILS_VIEW_FLAG_TOOLBAR_OPEN) {
    OpenItem();
    return S_OK;
  }
  if (dv_flags & GDD_DETAILS_VIEW_FLAG_NEGATIVE_FEEDBACK) {
    CComQIPtr<IGoogleDesktopDisplayContentItemHelper> helper(m_contentItemHelper);
    CComBSTR heading;
    ATLVERIFY(SUCCEEDED(helper->get_heading(&heading)));

    CString str(_T("Not interesting: "));
    str += heading;
    MessageBox(NULL, str, L"", MB_OK);
  }
  return E_NOTIMPL; // let default processing happen for details view commands
}

//------ CSamplePlugin: the actual plugin class

CSamplePlugin::CSamplePlugin() :
  m_itemRotate(kItemRotateMax - 2),
  m_contentLayout(GDD_CONTENT_ITEM_LAYOUT_EMAIL),
  m_showImages(VARIANT_TRUE),
  m_paused(VARIANT_TRUE),
  m_totalItemsCreatedCount(0),
  m_firstTime(true) {
}

HRESULT CSamplePlugin::FinalConstruct() {
  return S_OK;
}

void CSamplePlugin::FinalRelease() {
  if (m_msgOnlyWindow.IsWindow())
    m_msgOnlyWindow.DestroyWindow();
  m_pluginHelper.Release();
}

HRESULT CSamplePlugin::StartDisplayingItems() {
  if (!m_msgOnlyWindow.Init(this))
    return E_FAIL;

  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(m_pluginHelper);
  if (m_pluginHelper == NULL)
    return E_FAIL;

  // Load and add the icons that we use to the helper object
  PICTDESC desc;
  desc.cbSizeofstruct = sizeof(desc);
  desc.picType = PICTYPE_ICON;

  HRESULT hr;
  desc.icon.hicon = static_cast<HICON>(LoadImage(
    ghInstance, MAKEINTRESOURCE(IDI_PLUGIN), IMAGE_ICON,
    GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR));
  hr = OleCreatePictureIndirect(&desc, IID_IPicture, FALSE, (LPVOID *)&m_smallIcon);
  if (FAILED(hr))
    return hr;

  desc.icon.hicon = static_cast<HICON>(LoadImage(
    ghInstance, MAKEINTRESOURCE(IDI_PLUGIN), IMAGE_ICON,
    GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR));
  hr = OleCreatePictureIndirect(&desc, IID_IPicture, FALSE, (LPVOID *)&m_largeIcon);
  if (FAILED(hr))
    return hr;

  desc.icon.hicon = (HICON)LoadImage(ghInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON,
    0, 0, LR_DEFAULTCOLOR);
  hr = OleCreatePictureIndirect(&desc, IID_IPicture, FALSE, (LPVOID *)&m_contentIcon1);
  if (FAILED(hr))
    return hr;

  desc.icon.hicon = (HICON)LoadImage(ghInstance, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON,
    0, 0, LR_DEFAULTCOLOR);
  hr = OleCreatePictureIndirect(&desc, IID_IPicture, FALSE, (LPVOID *)&m_contentIcon2);
  if (FAILED(hr))
    return hr;

  // now do other one-time init stuff.
  ATLVERIFY(SUCCEEDED(helper->SetIcons(m_smallIcon, m_largeIcon)));
  CComBSTR aboutText;
  aboutText.LoadString(IDS_COPYRIGHT);
  ATLVERIFY(SUCCEEDED(helper->put_about_text(aboutText)));
  UpdateTitle();

  // display the first set of items
  SetContentLayout();
  ChangeItems(false);
  return S_OK;
}

void CSamplePlugin::SetContentLayout() {
  // reset everything and start fresh with new layout
  m_firstTime = true;
  m_itemRotate = kItemRotateMax - 2;

  // some flags to test things out
  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(m_pluginHelper);
  UINT content_flags = 0;
  if (m_contentLayout == GDD_CONTENT_ITEM_LAYOUT_NOWRAP_ITEMS)
    content_flags |= GDD_CONTENT_FLAG_PINNABLE;
  else
    content_flags |= GDD_CONTENT_FLAG_HAVE_DETAILS;
  UINT plugin_flags = GDD_PLUGIN_FLAG_NONE;
  helper->SetFlags(
    static_cast<GoogleDesktopDisplayPluginFlags>(plugin_flags),
    static_cast<GoogleDesktopDisplayContentFlags>(content_flags));
}

void CSamplePlugin::UpdateTitle() {
  // In minimized mode no items are displayed by the plugin so we make use of the 
  // title to show some useful information. An email plugin for eg. can show the
  // number of unread mails, a weather plugin can show the local temperature etc.

  // check if we are in minimized mode. "m_spUnkSite" member comes from IObjectWithSiteImpl
  GoogleDesktopDisplayTileDisplayState display_state = GDD_TILE_DISPLAY_STATE_RESTORED;
  CComQIPtr<IGoogleDesktopDisplaySite> sidebar_site(m_spUnkSite);
  if (sidebar_site != NULL) { // will be null during init time
    ATLVERIFY(SUCCEEDED(sidebar_site->get_display_state(&display_state)));
  }

  // format the title string to show (with number of items if we are in minimized mode)
  CString str, name;
  name.LoadString(IDS_SAMPLEPLUGIN);
  if (display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED)
    str.Format(_T(" (%d)"), m_totalItemsCreatedCount);
  str = name + str;

  // set the title
  CComBSTR title(str);
  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(m_pluginHelper);
  ATLASSERT(helper != NULL);
  ATLVERIFY(SUCCEEDED(helper->put_title(title)));
}

void CSamplePlugin::ChangeItems(bool refreshOnly) {
  // create some strings to display
  int maxItems = 1;
  if (m_firstTime)
    maxItems = 3;

  if (!refreshOnly) {
    // move to next set of items
    m_itemRotate = (m_itemRotate + 1) % kItemRotateMax;
    m_totalItemsCreatedCount += maxItems;
  }

  CComQIPtr<IGoogleDesktopDisplayPluginHelper> pluginHelper(m_pluginHelper);
  for (int j = 0, i = m_itemStart + m_itemRotate; j < maxItems; j++) {
    // create a new item
    CSamplePluginContentItemImpl *curItem = NULL;
    ATLVERIFY(SUCCEEDED(CSamplePluginContentItemImpl::CreateInstance(&curItem)));

    CComPtr<IGoogleDesktopDisplayContentItemHelper> itemHelper;
    curItem->GetUnknown()->QueryInterface(IID_IGoogleDesktopDisplayContentItemHelper,
      reinterpret_cast<void**>(&itemHelper));

    // and set it's properties
    // some set of flags to test things out.
    UINT flags = 0;
    if (m_contentLayout == GDD_CONTENT_ITEM_LAYOUT_EMAIL)
      flags |= GDD_CONTENT_ITEM_FLAG_TIME_ABSOLUTE;

    bool odd_numbered_item = ((i % 2) == 1);

    // highlight odd numbered items
    if (odd_numbered_item)
      flags |= GDD_CONTENT_ITEM_FLAG_HIGHLIGHTED;

    // the strings to display, different format for odd and even numbered items
    CString strHeading;
    if (i & 1) {
      strHeading.Format(_T("Line %d line %d line %d line %d line %d ")
        _T("line %d line %d line %d"), i, i, i, i, i, i, i, i);
    } else {
      strHeading.Format(_T("Line %d line %d line %d"), i, i, i);
    }
    CComBSTR snippet(L"Google doodles with the idea to create noodles to sell on Froogle.");
    CComBSTR source(L"Google");
    CComBSTR heading(strHeading);
    CComPtr<IPicture> image;
    if (m_showImages) {
      // use different images for odd and even numbered items
      image = (odd_numbered_item) ? m_contentIcon1 : m_contentIcon2;
    }

    SYSTEMTIME systime;
    GetSystemTime(&systime);
    DATE timeCreated;
    SystemTimeToVariantTime(&systime, &timeCreated);

    // do the actual setting of props
    ATLVERIFY(SUCCEEDED(itemHelper->put_heading(heading)));
    ATLVERIFY(SUCCEEDED(itemHelper->put_tooltip(heading)));
    ATLVERIFY(SUCCEEDED(itemHelper->put_source(source)));
    ATLVERIFY(SUCCEEDED(itemHelper->put_time_created(timeCreated)));
    ATLVERIFY(SUCCEEDED(itemHelper->put_snippet(snippet)));
    ATLVERIFY(SUCCEEDED(itemHelper->put_flags(
      static_cast<GoogleDesktopDisplayContentItemFlags>(flags))));
    ATLVERIFY(SUCCEEDED(itemHelper->put_image(image)));
    ATLVERIFY(SUCCEEDED(itemHelper->put_layout(
      static_cast<GoogleDesktopDisplayContentItemLayout>(m_contentLayout))));

    CComQIPtr<IGoogleDesktopDisplayContentItem> item(itemHelper);
    // Show the item in the sidebar and optionally in the notification 
    // window if the sidebar is auto-hidden.
    GoogleDesktopContentItemDisplayOptions item_flags = 
      static_cast<GoogleDesktopContentItemDisplayOptions>(
        GDD_ITEM_DISPLAY_IN_SIDEBAR | GDD_ITEM_DISPLAY_AS_NOTIFICATION_IF_SIDEBAR_HIDDEN);
    ATLVERIFY(SUCCEEDED(pluginHelper->AddContentItem(item, item_flags)));

    i--;
    if (i < 0)
      i = m_itemStart + kItemRotateMax - 1;
  }

  // if we are in minimized mode, update the title with latest info.
  GoogleDesktopDisplayTileDisplayState display_state = GDD_TILE_DISPLAY_STATE_RESTORED;
  CComQIPtr<IGoogleDesktopDisplaySite> sidebar_site(m_spUnkSite);
  if (sidebar_site != NULL) // will be NULL during init time
    ATLVERIFY(SUCCEEDED(sidebar_site->get_display_state(&display_state)));

  if (display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED)
    UpdateTitle();

  m_firstTime = false;
}

STDMETHODIMP CSamplePlugin::get_ItemStart(ULONG* pVal) {
  if (!pVal)
    return E_POINTER;
  *pVal = m_itemStart;
  return S_OK;
}

STDMETHODIMP CSamplePlugin::put_ItemStart(ULONG newVal) {
  m_itemStart = newVal;
  // since new value has been given create new items
  m_itemRotate = 0;
  ChangeItems(true);
  return S_OK;
}

STDMETHODIMP CSamplePlugin::get_ContentLayout(LONG* pVal) {
  if (!pVal)
    return E_POINTER;
  *pVal = m_contentLayout;
  return S_OK;
}

STDMETHODIMP CSamplePlugin::put_ContentLayout(LONG newVal) {
  m_contentLayout = newVal;
  SetContentLayout();
  return S_OK;
}

//------ IPersistStreamInit: load/store our properties

STDMETHODIMP CSamplePlugin::InitNew() {
  m_itemStart = 0;
  HRESULT hr = IPersistStreamInitImpl<CSamplePlugin>::InitNew();
  if (SUCCEEDED(hr))
    hr = StartDisplayingItems();
  return hr;
}

STDMETHODIMP CSamplePlugin::Load(LPSTREAM stream) {
  HRESULT hr = IPersistStreamInitImpl<CSamplePlugin>::Load(stream);
  if (SUCCEEDED(hr))
    hr = StartDisplayingItems();
  return hr;
}

//------ Members of IGoogleDesktopDisplayPluginHandler, called by the PluginHelper object

// called when any toolbar button is clicked (back, forward etc..)
STDMETHODIMP CSamplePlugin::OnCommand(GoogleDesktopDisplayPluginCommand command) {
  if (command == GDD_CMD_ABOUT_DLG)
    return E_NOTIMPL; // let default about dialog show up

  CString str;
  str.Format(_T("Sidebar sent command %d"), command);
  MessageBox(NULL, str, _T(""), MB_OK);
  return S_OK;
}

// called when the plugin tile's display state changes
STDMETHODIMP CSamplePlugin::OnDisplayStateChange(
    GoogleDesktopDisplayTileDisplayState display_state) {
  if (display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED || 
      display_state == GDD_TILE_DISPLAY_STATE_RESTORED) {
    // switching between minimized and normal mode, so update the title
    UpdateTitle();
  }
  return S_OK;
}

//------ Members of IContextMenu: Implement IContextMenu if your plugin wants to add 
//------ menu items to the plugin's context menu

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
STDMETHODIMP CSamplePlugin::QueryContextMenu(
  HMENU dst, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags) {
  // Add items to the menu
  CString str;
  str.LoadString(IDS_PAUSE);
  AppendMenu(dst, MF_STRING, idCmdFirst + MenuOffsetPause, str);
  AppendMenu(dst, MF_SEPARATOR, 0, NULL);
  str.LoadString(IDS_LAYOUT_SINGLELINE);
  AppendMenu(dst, MF_STRING, idCmdFirst + MenuOffsetLayoutSingleLine, str);
  str.LoadString(IDS_LAYOUT_NEWS);
  AppendMenu(dst, MF_STRING, idCmdFirst + MenuOffsetLayoutNews, str);
  str.LoadString(IDS_LAYOUT_EMAIL);
  AppendMenu(dst, MF_STRING, idCmdFirst + MenuOffsetLayoutEmail, str);
  AppendMenu(dst, MF_SEPARATOR, 0, NULL);
  str.LoadString(IDS_SHOW_IMAGES);
  AppendMenu(dst, MF_STRING, idCmdFirst + MenuOffsetShowImages, str);

  // check the relavent items
  if (m_paused == VARIANT_TRUE)
    CheckMenuItem(dst, idCmdFirst + MenuOffsetPause, MF_BYCOMMAND | MF_CHECKED);
  if (m_showImages == VARIANT_TRUE)
    CheckMenuItem(dst, idCmdFirst + MenuOffsetShowImages, MF_BYCOMMAND | MF_CHECKED);
  CheckMenuRadioItem(dst, idCmdFirst + MenuOffsetLayoutSingleLine, idCmdFirst +
    MenuOffsetLayoutEmail, idCmdFirst + MenuOffsetLayoutSingleLine + m_contentLayout,
    MF_BYCOMMAND);

  return S_OK;
}

// not used by the sidebar
STDMETHODIMP CSamplePlugin::GetCommandString(
  UINT_PTR idCmd, UINT uType, UINT * pwReserved, LPSTR pszName, UINT cchMax) {
  ATLTRACENOTIMPL("GetCommandString");
}

// called when one of the plugin's context menu item is clicked
STDMETHODIMP CSamplePlugin::InvokeCommand(LPCMINVOKECOMMANDINFO lpici) {
  switch ((int)lpici->lpVerb) {
    case MenuOffsetPause: // Pause
      m_paused = (m_paused == VARIANT_TRUE) ? VARIANT_FALSE : VARIANT_TRUE;
      break;
    case MenuOffsetLayoutSingleLine:
      m_contentLayout = static_cast<LONG>(GDD_CONTENT_ITEM_LAYOUT_NOWRAP_ITEMS);
      SetContentLayout();
      break;
    case MenuOffsetLayoutNews:
      m_contentLayout = static_cast<LONG>(GDD_CONTENT_ITEM_LAYOUT_NEWS);
      SetContentLayout();
      break;
    case MenuOffsetLayoutEmail:
      m_contentLayout = static_cast<LONG>(GDD_CONTENT_ITEM_LAYOUT_EMAIL);
      SetContentLayout();
      break;
    case MenuOffsetShowImages:
      m_showImages = (m_showImages == VARIANT_TRUE) ? VARIANT_FALSE : VARIANT_TRUE;
      ChangeItems(true);
      break;
    default:
      ATLASSERT(FALSE);
      break;
  }
  return S_OK;
}

