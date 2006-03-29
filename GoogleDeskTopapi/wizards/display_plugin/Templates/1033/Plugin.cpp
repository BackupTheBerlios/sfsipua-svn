// Plugin.cpp : Implementation of C[!output PROJECT_NAME]Plugin

#include "stdafx.h"
#include "Plugin.h"
#include <atlcomtime.h>

extern HINSTANCE ghInstance;

// local defines
const int kItemUpdateTimeMs = 25000;
const int kItemUpdateTimerId = 1;

[!if CUSTOM_MENU_ITEMS]
enum {
  MenuOffsetItem1 = 0,
  MenuOffsetItem2
};
[!endif]

//------ C[!output PROJECT_NAME]PluginContentItem members

STDMETHODIMP C[!output PROJECT_NAME]PluginContentItem::GetIsTooltipRequired(
    GoogleDesktopDisplayTarget target, HDC dc, const RECT *bounds,
    VARIANT_BOOL *is_required) {
  return E_NOTIMPL;   // let the ContentItemHelper object do the default stuff
}

STDMETHODIMP C[!output PROJECT_NAME]PluginContentItem::DrawItem(
    GoogleDesktopDisplayTarget target, HDC dc, const RECT *bounds) {
  return E_NOTIMPL;   // let the ContentItemHelper object do the default drawing
}

STDMETHODIMP C[!output PROJECT_NAME]PluginContentItem::GetHeight(
    GoogleDesktopDisplayTarget target, HDC dc, long width, long *height) {
  return E_NOTIMPL;   // let the ContentItemHelper object do the default drawing
}

STDMETHODIMP C[!output PROJECT_NAME]PluginContentItem::ToggleItemPinnedState() {
  return E_NOTIMPL;   // let the ContentItemHelper object do the default action
}

STDMETHODIMP C[!output PROJECT_NAME]PluginContentItem::OpenItem() {
  CComQIPtr<IGoogleDesktopDisplayContentItemHelper> helper(m_contentItemHelper);

  // TODO: Replace this with plugin specific code.
  CComBSTR heading;
  ATLVERIFY(SUCCEEDED(helper->get_heading(&heading)));
  CString str(_T("Clicked: "));
  str += heading;
  MessageBox(NULL, str, _T(""), MB_OK);

  return S_OK;
}

STDMETHODIMP C[!output PROJECT_NAME]PluginContentItem::OnDetailsView(BSTR* title,
                                          GoogleDesktopDisplayDetailsViewFlags* flags,
                                          IUnknown** details_control,
                                          VARIANT_BOOL* cancel) {
[!if CUSTOM_DETAILS_VIEW]
  // Get the item to be displayed
  CComQIPtr<IGoogleDesktopDisplayContentItemHelper> helper(m_contentItemHelper);
  ATLASSERT(helper != NULL);
  if (!helper)
    return E_INVALIDARG;

  // Here we can create any ActiveX control for displaying the details, and 
  // return it via the details_control parameter. We use our 
  // C[!output PROJECT_NAME]PluginDetailsView control to draw the details view content.
  CComPtr<I[!output PROJECT_NAME]PluginDetailsView> details;
  HRESULT hr = details.CoCreateInstance(CLSID_[!output PROJECT_NAME]PluginDetailsView);
  if (SUCCEEDED(hr)) {
    // get the item's snippet and show it in the details view
    CComBSTR detailsText;
    ATLVERIFY(SUCCEEDED(helper->get_snippet(&detailsText)));

    details->SetContent(detailsText);

    ATLVERIFY(SUCCEEDED(helper->get_heading(title)));
    *details_control = details.Detach();  // return the object to the sidebar for display
    *flags = static_cast<GoogleDesktopDisplayDetailsViewFlags>(
      GDD_DETAILS_VIEW_FLAG_TOOLBAR_OPEN);
  }

  return hr;
[!else]
  // let default processing happen, which will show a details view window with the data in
  // this item.
  return E_NOTIMPL;
[!endif]
}

STDMETHODIMP C[!output PROJECT_NAME]PluginContentItem::ProcessDetailsViewFeedback(
    GoogleDesktopDisplayDetailsViewFlags dv_flags) {
  // This function is called when the user clicks on any buttons in the details view
  if (dv_flags & GDD_DETAILS_VIEW_FLAG_NEGATIVE_FEEDBACK) {
    // let the ContentItemHelper object do the default, which is typically removing the item.
    // Add code here to perform plugin specific processing for the negative feedback command.
    // Returning E_NOTIMPL will let the default happen, which is to remove the item.
  }
  if (dv_flags & GDD_DETAILS_VIEW_FLAG_TOOLBAR_OPEN) {
    return OpenItem();
  }
  return E_NOTIMPL; // let default processing happen
}

//------ C[!output PROJECT_NAME]PluginMsgOnlyWindow: Used for handling messages since the plugin could be
//------ a windowless control

bool C[!output PROJECT_NAME]PluginMsgOnlyWindow::Init(C[!output PROJECT_NAME]Plugin *plugin) {
  // create a message-only window
  if (Create(HWND_MESSAGE) == NULL)
    return false;

  m_plugin = plugin;
  // set a timer to keep rotating the displayed items
  SetTimer(kItemUpdateTimerId, kItemUpdateTimeMs, NULL);
  return true;
}

LRESULT C[!output PROJECT_NAME]PluginMsgOnlyWindow::OnTimer(UINT , WPARAM wp, LPARAM , BOOL& ) {
  if (static_cast<int>(wp) == kItemUpdateTimerId)
    m_plugin->ChangeItems(false); // call the plugin to update the items
  return 0;
}

//------ C[!output PROJECT_NAME]Plugin: the actual plugin class

C[!output PROJECT_NAME]Plugin::C[!output PROJECT_NAME]Plugin() {
}

HRESULT C[!output PROJECT_NAME]Plugin::FinalConstruct() {
  return S_OK;
}

void C[!output PROJECT_NAME]Plugin::FinalRelease() {
  if (m_msgOnlyWindow.IsWindow())
    m_msgOnlyWindow.DestroyWindow();
  m_pluginHelper.Release();
}

HRESULT C[!output PROJECT_NAME]Plugin::StartDisplayingItems() {
  if (!m_msgOnlyWindow.Init(this))
    return E_FAIL;

  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(GetUnknown());
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

  desc.icon.hicon = (HICON)LoadImage(ghInstance, MAKEINTRESOURCE(IDI_ITEM), IMAGE_ICON,
    0, 0, LR_DEFAULTCOLOR);
  hr = OleCreatePictureIndirect(&desc, IID_IPicture, FALSE, (LPVOID *)&m_contentIcon);
  if (FAILED(hr))
    return hr;

  // other one-time init stuff.
  ATLVERIFY(SUCCEEDED(helper->SetIcons(m_smallIcon, m_largeIcon)));
  CComBSTR aboutText;
  aboutText.LoadString(IDS_COPYRIGHT);
  ATLVERIFY(SUCCEEDED(helper->put_about_text(aboutText)));
  UpdateTitle();

  // set the layout and flags
[!if ITEMS_ACCEPT_INPUT]
  UINT content_flags = GDD_CONTENT_FLAG_HAVE_DETAILS;
[!else]
  UINT content_flags = 0;
[!endif]
  UINT plugin_flags = GDD_PLUGIN_FLAG_NONE;
  helper->SetFlags(
    static_cast<GoogleDesktopDisplayPluginFlags>(plugin_flags),
    static_cast<GoogleDesktopDisplayContentFlags>(content_flags));

  // display the first set of items
  ChangeItems(true);

  return S_OK;
}

void C[!output PROJECT_NAME]Plugin::UpdateTitle() {
  // check if we are in minimized mode. "m_spUnkSite" member comes from IObjectWithSiteImpl
  GoogleDesktopDisplayTileDisplayState display_state = GDD_TILE_DISPLAY_STATE_RESTORED;
  CComQIPtr<IGoogleDesktopDisplaySite> sidebar_site(m_spUnkSite);
  if (sidebar_site != NULL) { // will be null during init time
    ATLVERIFY(SUCCEEDED(sidebar_site->get_display_state(&display_state)));
  }

  // format the title string
  CString name;
  name.LoadString(IDS_PLUGIN_NAME);
  if (display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED) {
    // In minimized mode no items are displayed by the plugin so we can make use of the 
    // title to show some useful information. An email plugin for eg. can show the
    // number of unread mails, a weather plugin can show the local temperature etc.
    //
    // Set the variable 'name' to what you want to be displayed here.
  }

  // set the title
  CComBSTR title(name);
  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(m_pluginHelper);
  ATLASSERT(helper != NULL);
  ATLVERIFY(SUCCEEDED(helper->put_title(title)));
}

void C[!output PROJECT_NAME]Plugin::ChangeItems(bool startFresh) {
  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(m_pluginHelper);

[!if NUM_ITEMS_FIXED]
  // We display the same number of items at all times. In such cases we can either get the current list of
  // items by calling IGoogleDesktopDisplayPluginHelper::get_content_items() and updating each item's content
  // with the latest information, or we can remove all the existing items and add new items with latest content.
  // Here we do the second method for code reuse purposes.
  ATLVERIFY(SUCCEEDED(helper->RemoveAllContentItems()));

  int maxItems = [!output INITIAL_NUM_ITEMS];
  if (startFresh) {
[!else]
  int maxItems = 1;
  if (startFresh) {
    // remove existing items
    ATLVERIFY(SUCCEEDED(helper->RemoveAllContentItems()));
    maxItems = [!output INITIAL_NUM_ITEMS];
[!endif]
    m_itemCount = 0;
  }

  for (int i = 0; i < maxItems; ++i) {
    AddNewContentItem();
  }

  // if we are in minimized mode, update the title with latest info.
  GoogleDesktopDisplayTileDisplayState display_state = GDD_TILE_DISPLAY_STATE_RESTORED;
  CComQIPtr<IGoogleDesktopDisplaySite> sidebar_site(m_spUnkSite);
  if (sidebar_site != NULL) // will be NULL during init time
    ATLVERIFY(SUCCEEDED(sidebar_site->get_display_state(&display_state)));

  if (display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED)
    UpdateTitle();
}

void C[!output PROJECT_NAME]Plugin::AddNewContentItem() {
  CComQIPtr<IGoogleDesktopDisplayPluginHelper> pluginHelper(m_pluginHelper);

  // create a new item and get it's helper interface
  C[!output PROJECT_NAME]PluginContentItemImpl *curItem = NULL;
  ATLVERIFY(SUCCEEDED(C[!output PROJECT_NAME]PluginContentItemImpl::CreateInstance(&curItem)));

  CComPtr<IGoogleDesktopDisplayContentItemHelper> itemHelper;
  curItem->GetUnknown()->QueryInterface(IID_IGoogleDesktopDisplayContentItemHelper,
    reinterpret_cast<void**>(&itemHelper));

  // and set it's properties
[!if ITEMS_ACCEPT_INPUT]
  UINT flags = 0;   // can set to a combination of GDD_CONTENT_ITEM_FLAG_xxxx
[!else]
  UINT flags = GDD_CONTENT_ITEM_FLAG_STATIC;  // doesn't take user input
[!endif]
  GoogleDesktopDisplayContentItemLayout contentLayout = 
[!if ITEM_LAYOUT_NEWS]
    GDD_CONTENT_ITEM_LAYOUT_NEWS;
[!endif]
[!if ITEM_LAYOUT_EMAIL]
    GDD_CONTENT_ITEM_LAYOUT_EMAIL;
[!endif]
[!if ITEM_LAYOUT_NOWRAP]
    GDD_CONTENT_ITEM_LAYOUT_NOWRAP_ITEMS;
[!endif]

  // the strings to display
  CString strHeading;
  strHeading.Format(_T("Item %d"), m_itemCount + 1);
[!if USE_PROPERTY_PAGE1]
  strHeading.AppendFormat(_T(": %d"), m_Value1);
[!endif]
[!if USE_PROPERTY_PAGE2]
  strHeading.AppendFormat(L": %d", m_Value2);
[!endif]
[!if USE_PROPERTY_PAGE3]
  strHeading.AppendFormat(L": %d", m_Value3);
[!endif]

  CComBSTR snippet(L"snippet");
  CComBSTR source(L"[!output PROJECT_NAME]");
  CComBSTR heading(strHeading);

  // display the current time as the time for this item
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
  ATLVERIFY(SUCCEEDED(itemHelper->put_image(m_contentIcon)));
  ATLVERIFY(SUCCEEDED(itemHelper->put_layout(
    static_cast<GoogleDesktopDisplayContentItemLayout>(contentLayout))));

  CComQIPtr<IGoogleDesktopDisplayContentItem> item(itemHelper);
  // Show the item in the sidebar and optionally in the notification 
  // window if the sidebar is auto-hidden.
  GoogleDesktopContentItemDisplayOptions item_flags = 
    static_cast<GoogleDesktopContentItemDisplayOptions>(
      GDD_ITEM_DISPLAY_IN_SIDEBAR | GDD_ITEM_DISPLAY_AS_NOTIFICATION_IF_SIDEBAR_HIDDEN);
  ATLVERIFY(SUCCEEDED(pluginHelper->AddContentItem(item, item_flags)));

  // increment our counter.
  m_itemCount++;
}

[!if USE_PROPERTY_PAGE1]
STDMETHODIMP C[!output PROJECT_NAME]Plugin::get_Value1(LONG* pVal) {
  if (!pVal)
    return E_POINTER;
  *pVal = m_Value1;
  return S_OK;
}

STDMETHODIMP C[!output PROJECT_NAME]Plugin::put_Value1(LONG newVal) {
  m_Value1 = newVal;
  // since new value has been given create new items
  ChangeItems(true);
  return S_OK;
}

[!endif]
[!if USE_PROPERTY_PAGE2]
STDMETHODIMP C[!output PROJECT_NAME]Plugin::get_Value2(LONG* pVal) {
  if (!pVal)
    return E_POINTER;
  *pVal = m_Value2;
  return S_OK;
}

STDMETHODIMP C[!output PROJECT_NAME]Plugin::put_Value2(LONG newVal) {
  m_Value2 = newVal;
  // since new value has been given create new items
  ChangeItems(true);
  return S_OK;
}

[!endif]
[!if USE_PROPERTY_PAGE3]
STDMETHODIMP C[!output PROJECT_NAME]Plugin::get_Value3(LONG* pVal) {
  if (!pVal)
    return E_POINTER;
  *pVal = m_Value3;
  return S_OK;
}

STDMETHODIMP C[!output PROJECT_NAME]Plugin::put_Value3(LONG newVal) {
  m_Value3 = newVal;
  // since new value has been given create new items
  ChangeItems(true);
  return S_OK;
}

[!endif]
//------ IPersistStreamInit: load/store our properties

STDMETHODIMP C[!output PROJECT_NAME]Plugin::InitNew() {
  // Called when the plugin is enabled by the user for the first time. Initialize with defaults.
[!if USE_PROPERTY_PAGE1]
  m_Value1 = 0;
[!endif]
[!if USE_PROPERTY_PAGE2]
  m_Value2 = 0;
[!endif]
[!if USE_PROPERTY_PAGE3]
  m_Value3 = 0;
[!endif]
  HRESULT hr = IPersistStreamInitImpl<C[!output PROJECT_NAME]Plugin>::InitNew();
  if (SUCCEEDED(hr))
    hr = StartDisplayingItems();
  return hr;
}

STDMETHODIMP C[!output PROJECT_NAME]Plugin::Load(LPSTREAM stream) {
  // The following call will load all our variables declared inside the property map.
  HRESULT hr = IPersistStreamInitImpl<C[!output PROJECT_NAME]Plugin>::Load(stream);
  if (SUCCEEDED(hr)) {
    hr = StartDisplayingItems();
  }
  return hr;
}

STDMETHODIMP C[!output PROJECT_NAME]Plugin::Save(LPSTREAM stream, BOOL clearDirty) {
  // The following call will save all our variables declared inside the property map.
  return IPersistStreamInitImpl<C[!output PROJECT_NAME]Plugin>::Save(stream, clearDirty);
}

//------ Members of IGoogleDesktopDisplayPluginHandler, called by the PluginHelper object

// called when any toolbar button is clicked (back, forward etc..)
STDMETHODIMP C[!output PROJECT_NAME]Plugin::OnCommand(GoogleDesktopDisplayPluginCommand command) {
  if (command == GDD_CMD_ABOUT_DLG)
    return E_NOTIMPL; // let default about dialog show up

  CString str;
  str.Format(_T("Sidebar sent command %d"), command);
  MessageBox(NULL, str, _T(""), MB_OK);
  return S_OK;
}

// called when the plugin tile's display state changes
STDMETHODIMP C[!output PROJECT_NAME]Plugin::OnDisplayStateChange(
    GoogleDesktopDisplayTileDisplayState display_state) {
  if (display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED || 
      display_state == GDD_TILE_DISPLAY_STATE_RESTORED) {
    // switching between minimized and normal mode, so update the title
    UpdateTitle();
  }
  return S_OK;
}

[!if CUSTOM_MENU_ITEMS]
//------ Members of IContextMenu: Implement IContextMenu if your plugin wants to add 
//------ menu items to the plugin's context menu

// Add menu items to the plugin's context menu in the sidebar
STDMETHODIMP C[!output PROJECT_NAME]Plugin::QueryContextMenu(
    HMENU dst, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags) {
  // Add items to the menu
  CString str;
  str.LoadString(IDS_MENU_ITEM1);
  AppendMenu(dst, MF_STRING, idCmdFirst + MenuOffsetItem1, str);
  str.LoadString(IDS_MENU_ITEM2);
  AppendMenu(dst, MF_STRING, idCmdFirst + MenuOffsetItem2, str);

  return S_OK;
}

// not used by the sidebar
STDMETHODIMP C[!output PROJECT_NAME]Plugin::GetCommandString(
    UINT_PTR idCmd, UINT uType, UINT * pwReserved, LPSTR pszName, UINT cchMax) {
  ATLTRACENOTIMPL("GetCommandString");
}

// called when one of the plugin's context menu item is clicked
STDMETHODIMP C[!output PROJECT_NAME]Plugin::InvokeCommand(LPCMINVOKECOMMANDINFO lpici) {
  CString str;
  switch ((int)lpici->lpVerb) {
    case MenuOffsetItem1:
      str.LoadString(IDS_MENU_ITEM1);
      break;
    case MenuOffsetItem2:
      str.LoadString(IDS_MENU_ITEM2);
      break;
    default:
      ATLASSERT(FALSE);
      break;
  }
  ::MessageBox(NULL, str, L"[!output PROJECT_NAME]", MB_OK);
  return S_OK;
}

[!endif]