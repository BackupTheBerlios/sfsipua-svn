// Copyright 2005 Google Inc. All Rights Reserved.
//
// sysmon_plugin.cpp : Implementation of SysMonPlugin
//
// Implementation of IPersistStreamInit provided by SysMonPlugin will
// be called by GoogleDesktopSidebar to init/load/save the plugin's
// properties. After properties (only refresh_interval_ in this sample),
// is initialized in InitNew and Load, StartDisplayingItems is called
// to prepare the displaying of the content. This function captures
// the first system performance sample for displaying and prepares
// the message only window. The message only windows is disposed in
// FinalRelease.
//
// Message only window setups the timer based on SysMonPlugin's
// refresh_interval_ and receives WM_TIMER message. In OnTimer handler,
// it calls RefreshPerfSamples to refresh performance data.
//
// Property accessors are:
//   get_refresh_interval, put_refresh_interval;
//   get_active_monitors, put_active_monitors;
// In put_refresh_interval, it notifies message only window when
// refresh_interval_ is set to a new value.
// In put_active_monitors, it calls ChangeItems to sync content item
// with the active_monitors_ mask.
//
// In ChangeItems (init or active_monitors_ property change), SysMonContentItem
// will be created accordingly. In RefreshPerfSamples, SysMonContentItem is
// notified to collect new performance samples.
#include "stdafx.h"

#include <atlsafe.h>  // For CComSafeArray

#include "../common/GoogleDesktopDisplayAPI.h"

#include "sysmon_plugin.h"
#include "sysmon_content_item.h"
#include "sysmon_monitor_item.h"

extern HMODULE _my_handle;

namespace {
  // version: MSB 2 bytes for signature, LSB 2 btyes for actual version number
  // increase version number whenever persistent data changes
  const int kSysMonPluginVersion = 0x12340001;
  const TCHAR *kTitleContentSeparatorMagicString = _T("~!~");

  const TCHAR *kCustomImageResType = _T("GIF");

  const int kRefreshTimerId = 0x900910;

  const int kDefaultRefreshInterval = 1;
  const int kDefaultActiveMonitors = ACTIVE_MON_CPU |
                                     ACTIVE_MON_MEM |
                                     ACTIVE_MON_DISK |
                                     ACTIVE_MON_NET;
  const int kAdditionUpdateDelayWhenMinited = 5;
};

// MsgOnlyWindowForTimers

// Creates the message only window and setups timer.
// This initialize function is called from StartDisplayingItems
// of SysMonPlugin.
int MsgOnlyWindowForTimers::Init(SysMonPlugin *pOwner) {
  owner_ = pOwner;
  if (Create(HWND_MESSAGE) == NULL)
    return -1;

  SetTimer(kRefreshTimerId, owner_->refresh_interval_ * 1000, NULL);
  return 0;
}

// Destory the timer and the message on window.
// When SysMonPlugin enters FinalRelease,
// it calls this function to dissolve the message only window.
void MsgOnlyWindowForTimers::Uninit() {
  if (IsWindow()) {
    KillTimer(kRefreshTimerId);
    DestroyWindow();
  }
}

int MsgOnlyWindowForTimers::SetRefreshInterval(int interval) {
  KillTimer(kRefreshTimerId);
  SetTimer(kRefreshTimerId, interval, NULL);
  return 0;
}

// Message only window receives periodical timer message and
// triggers the SysMonPlugin to refresh the performance data and repaint
// itself.
LRESULT MsgOnlyWindowForTimers::OnTimer(UINT, WPARAM timer_id, LPARAM, BOOL&) {
  owner_->TimerCallback(static_cast<UINT>(timer_id));
  return 0;
}
 
// SysMonPlugin

// Initializes SysMonPlugin.
HRESULT SysMonPlugin::FinalConstruct() {
  m_bRequiresSave = true;  // Tell IPersistStreamInit we need to save data

  return S_OK;
}

// Disposes message only window.
void SysMonPlugin::FinalRelease() {
  msg_wnd_.Uninit();
}

// Initializes SysMonPlugin peroperties for the very first time it
// gets loaded by Sidebar.
STDMETHODIMP SysMonPlugin::InitNew() {
  HRESULT hr = IPersistStreamInitImpl<SysMonPlugin>::InitNew();
  ATLASSERT(SUCCEEDED(hr));

  refresh_interval_ = kDefaultRefreshInterval;
  active_monitors_ = kDefaultActiveMonitors;
  max_disk_rw_in_chart_ = kDefaultMaxDiskRWInChart;
  max_net_io_in_chart_ = kDefaultMaxNetIOInChart;
  auto_adjust_chart_max_ = kDefaultAutoAdjustChartMax;

  hr = StartDisplayingItems();
  return hr;
}

// Loads SysMonPlugin properties from storage
STDMETHODIMP SysMonPlugin::Load(IStream *stream) {
  ATLASSERT(stream != NULL);

  int version;

  HRESULT hr = stream->Read(&version, sizeof(version), NULL);
  if (FAILED(hr))
    return hr;
  if (version != kSysMonPluginVersion) // if version doesn't match, stop loading
    return S_FALSE;                    // S_FALSE since we don't want to ASSERT

  hr = stream->Read(&refresh_interval_, sizeof(refresh_interval_), NULL);
  ATLASSERT(SUCCEEDED(hr));
  if (!refresh_interval_) {
    refresh_interval_ = kDefaultRefreshInterval;
  }

  hr = stream->Read(&active_monitors_, sizeof(active_monitors_), NULL);
  ATLASSERT(SUCCEEDED(hr));

  hr = stream->Read(&max_disk_rw_in_chart_,
                    sizeof(max_disk_rw_in_chart_), NULL);
  ATLASSERT(SUCCEEDED(hr));
  if (!max_disk_rw_in_chart_) {
    max_disk_rw_in_chart_ = kDefaultMaxDiskRWInChart;
  }

  hr = stream->Read(&max_net_io_in_chart_, sizeof(max_net_io_in_chart_), NULL);
  ATLASSERT(SUCCEEDED(hr));
  if (!max_net_io_in_chart_) {
    max_net_io_in_chart_ = kDefaultMaxNetIOInChart;
  }

  auto_adjust_chart_max_ = kDefaultAutoAdjustChartMax;
  hr = stream->Read(&auto_adjust_chart_max_,
                    sizeof(auto_adjust_chart_max_), NULL);
  ATLASSERT(SUCCEEDED(hr));

  hr = StartDisplayingItems();
  return hr;
}

// Saves SysMonPlugin properties to storage
STDMETHODIMP SysMonPlugin::Save(IN OUT IStream *stream, IN BOOL clear_dirty) {
  ATLASSERT(stream != NULL);

  int version = kSysMonPluginVersion;
  HRESULT hr = stream->Write(&version, sizeof(version), NULL);
  if (FAILED(hr))
    return hr;

  hr = stream->Write(&refresh_interval_, sizeof(refresh_interval_), NULL);
  ATLASSERT(SUCCEEDED(hr));

  hr = stream->Write(&active_monitors_, sizeof(active_monitors_), NULL);
  ATLASSERT(SUCCEEDED(hr));

  hr = stream->Write(&max_disk_rw_in_chart_,
                    sizeof(max_disk_rw_in_chart_), NULL);
  ATLASSERT(SUCCEEDED(hr));

  hr = stream->Write(&max_net_io_in_chart_, sizeof(max_net_io_in_chart_), NULL);
  ATLASSERT(SUCCEEDED(hr));

  hr = stream->Write(&auto_adjust_chart_max_,
                    sizeof(auto_adjust_chart_max_), NULL);
  ATLASSERT(SUCCEEDED(hr));

  if (clear_dirty)
    SetDirty(FALSE);
  return S_OK;
}

STDMETHODIMP SysMonPlugin::SetSite(IUnknown* site) {
  HRESULT hr = IObjectWithSiteImpl<SysMonPlugin>::SetSite(site);
  if (site != NULL) {
    // Attach
    CComDispatchDriver sidebar_disp(m_spUnkSite);
    CComVariant sidebar_font_var;
    CComQIPtr<IFont> sidebar_font;
    HFONT font;

    sidebar_disp.GetProperty(DISPID_AMBIENT_FONT, &sidebar_font_var);

    sidebar_font = sidebar_font_var.punkVal;
    sidebar_font->get_hFont(&font);

    LOGFONT font_data = {0};
    ATLVERIFY(::GetObject(font, sizeof(font_data), &font_data));
    text_font_ = CreateFontIndirect(&font_data);
    caption_font_ = CreateFontIndirect(&font_data);

    // Notifies all content items about the new font
    EnumContentItem(NotifyFont);
  } else {
    // Detach
    if (caption_font_) {
      DeleteObject(caption_font_);
      caption_font_ = NULL;
    }
    if (text_font_) {
      DeleteObject(text_font_);
      text_font_ = NULL;
    }
  }
  return S_OK;
}

// ------ IGoogleDesktopDisplayPlugin members

// called when any toolbar button is clicked (back, forward etc..)
STDMETHODIMP SysMonPlugin::OnCommand(
    GoogleDesktopDisplayPluginCommand command) {
  return E_NOTIMPL;
}

// called when the plugin tile's display state changes
STDMETHODIMP SysMonPlugin::OnDisplayStateChange(
    GoogleDesktopDisplayTileDisplayState display_state) {
  hot_item_index_ = 0;  // Always start from item 0. Is this good?
  UpdateTitle();

  if (display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED) {
    msg_wnd_.SetRefreshInterval(
      (refresh_interval_ + kAdditionUpdateDelayWhenMinited) * 1000);
  } else if (display_state == GDD_TILE_DISPLAY_STATE_RESTORED) {
    msg_wnd_.SetRefreshInterval(refresh_interval_ * 1000);
  }

  if (display_state == GDD_TILE_DISPLAY_STATE_POPPED_OUT) {
    popout_stat_ = true;
  } else if (display_state == GDD_TILE_DISPLAY_STATE_RESTORED) {
    popout_stat_ = false;
  }

  return S_OK;
}

// Tells the tile info of us such as min size, max size
// and preferred size to our host.
STDMETHODIMP SysMonPlugin::GetInfo(GoogleDesktopDisplayTileInfo *tile_info) {
  return E_NOTIMPL;
}

// Prepares and draws the UI for the first time.
HRESULT SysMonPlugin::StartDisplayingItems() {
  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(helper_);

  GoogleDesktopDisplayPluginFlags plugin_flags = GDD_PLUGIN_FLAG_NONE;
  GoogleDesktopDisplayContentFlags content_flags = GDD_CONTENT_FLAG_NONE;

  ATLVERIFY(SUCCEEDED(helper->SetFlags(plugin_flags, content_flags)));

  CComBSTR about_text;
  about_text.LoadString(IDS_ABOUT_TEXT);
  ATLVERIFY(SUCCEEDED(helper->put_about_text(about_text)));

  CComPtr<IPicture> title_icon, about_icon;
  ATLVERIFY(SUCCEEDED(LoadPictureFromResource(_my_handle,
    MAKEINTRESOURCE(IDR_GIF_SYSMON_ICON_SMALL), kCustomImageResType,
    &title_icon)));
  ATLVERIFY(SUCCEEDED(LoadPictureFromResource(_my_handle,
    MAKEINTRESOURCE(IDR_GIF_SYSMON_ICON_LARGE), kCustomImageResType,
    &about_icon)));
  ATLVERIFY(SUCCEEDED(helper->SetIcons(title_icon, about_icon)));

  RefreshPerfSamples();
  ChangeItems();

  msg_wnd_.Init(this);
  msg_wnd_.SetRefreshInterval(refresh_interval_ * 1000);
  return S_OK;
}

void SysMonPlugin::ChangeItems() {
  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(helper_);
  ATLASSERT(helper);
  if (helper) {    
    hot_item_index_ = 0;  // Reset the title item index

    helper->RemoveAllContentItems();    

    uint32 mask = 0x80000000U, test = active_monitors_;
    for (int i = 0; test; ++i, mask >>=1) {
      if (test & mask) {
        test &= ~mask;
        SysMonContentItemImpl *item = NULL;
        ATLVERIFY(SUCCEEDED(SysMonContentItemImpl::CreateInstance(&item)));

        CComQIPtr<IGoogleDesktopDisplayContentItemHelper> item_helper =
          item->GetUnknown();

        GoogleDesktopDisplayContentItemFlags item_flags =
          GDD_CONTENT_ITEM_FLAG_STATIC;

        GoogleDesktopDisplayContentItemLayout layout_flags =
          GDD_CONTENT_ITEM_LAYOUT_NOWRAP_ITEMS;

        ATLVERIFY(SUCCEEDED(item_helper->put_flags(item_flags)));
        ATLVERIFY(SUCCEEDED(item_helper->put_layout(layout_flags)));

        GoogleDesktopContentItemDisplayOptions item_options =
          GDD_ITEM_DISPLAY_IN_SIDEBAR;

        CComQIPtr<ISysMonContentItemInternal> internal_item(item->GetUnknown());
        HRESULT hr = internal_item->SetMonitorItem(mask);
        if (hr == S_OK) {
          internal_item->SetFonts(caption_font_, text_font_);
          internal_item->SetContainer(this);

          CComQIPtr<IGoogleDesktopDisplayContentItem> content_item =
            item->GetUnknown();
          ATLVERIFY(SUCCEEDED(helper->AddContentItem(content_item,
                                                   item_options)));
        }
      }
    }
  }

  EnumContentItem(NotifyChartScale);
  EnumContentItem(NotifyChartAutoMax);
}

// Sets the plugin's title on the GDS interface.
void SysMonPlugin::UpdateTitle() {
  // m_spUnkSite comes from IObjectWithSiteImpl
  CComQIPtr<IGoogleDesktopDisplaySite> sidebar_site(m_spUnkSite);
  ATLASSERT(sidebar_site);

  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(helper_);
  ATLASSERT(helper);

  if (sidebar_site && helper) {
    GoogleDesktopDisplayTileDisplayState display_state =
      GDD_TILE_DISPLAY_STATE_RESTORED;
    ATLVERIFY(SUCCEEDED(sidebar_site->get_display_state(&display_state)));

    CComBSTR title;
    title.LoadString(IDS_SYSMON_PANEL_TITLE);

    if ((display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED) ||
        (display_state == GDD_TILE_DISPLAY_STATE_POPPED_OUT)) {

      CComVariant array_var;
      HRESULT hr = helper->get_content_items(&array_var);
      ATLASSERT(SUCCEEDED(hr));
      if (FAILED(hr))
        return;

      ATLASSERT(array_var.vt == (VT_ARRAY | VT_VARIANT) &&
        array_var.parray != NULL);

      CComSafeArray<VARIANT> items;
      hr = items.CopyFrom(array_var.parray);
      ATLASSERT(SUCCEEDED(hr));
      if (FAILED(hr))
        return;

      int num_items = static_cast<int>(items.GetCount());
      if (hot_item_index_ < num_items) {
        CComQIPtr<ISysMonContentItemInternal> item = 
          V_UNKNOWN(&items[hot_item_index_]);
        CString caption;
        item->GetMimimizedTitle(&caption);

        CString str;
        str.Format(NOTRANSL(L"%s %s %s"),
                    title,
                    kTitleContentSeparatorMagicString,
                    caption);
        title = str;

        ++hot_item_index_;
        hot_item_index_ %= num_items;
      } else {
        hot_item_index_ = 0;
      }
    }

    ATLVERIFY(SUCCEEDED(helper->put_title(title)));
  }
}

// Triggers the performance data gathering.
void SysMonPlugin::RefreshPerfSamples() {
  EnumContentItem(NotifyPerfSample);
}

void SysMonPlugin::EnumContentItem(EnumContentItemCallback callback) {
  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(helper_);
  ATLASSERT(helper);
  if (!helper)
    return;

  CComVariant array_var;
  HRESULT hr = helper->get_content_items(&array_var);
  ATLASSERT(SUCCEEDED(hr));
  if (FAILED(hr))
    return;

  ATLASSERT(array_var.vt == (VT_ARRAY | VT_VARIANT) &&
    array_var.parray != NULL);

  CComSafeArray<VARIANT> items;
  hr = items.CopyFrom(array_var.parray);
  ATLASSERT(SUCCEEDED(hr));
  if (FAILED(hr))
    return;

  int num_items = static_cast<int>(items.GetCount());
  for (int i = 0; i < num_items; ++i) {
    if (callback(this, V_UNKNOWN(&items[i]))) {
      break;
    }
  }
}

int SysMonPlugin::NotifyPerfSample(SysMonPlugin *self, IUnknown *item) {
  CComQIPtr<ISysMonContentItemInternal> internal_item(item);
  ATLASSERT(internal_item);

  internal_item->OnPerfSampleArrive();
  return 0;
}

int SysMonPlugin::NotifyFont(SysMonPlugin *self, IUnknown *item) {
  CComQIPtr<ISysMonContentItemInternal> internal_item(item);
  ATLASSERT(internal_item);

  internal_item->SetFonts(self->caption_font_, self->text_font_);
  return 0;
}

int SysMonPlugin::NotifyChartScale(SysMonPlugin *self, IUnknown *item) {
  CComQIPtr<ISysMonContentItemInternal> internal_item(item);
  ATLASSERT(internal_item);

  internal_item->SetChartScale(self->max_disk_rw_in_chart_,
                               self->max_net_io_in_chart_);

  // Since currently chart scale are shared between all MonitorItem,
  // we don't actually need to set them in every MonitorItem.
  // Return 1 here to stop enumeration.
  return 1;
}

int SysMonPlugin::NotifyChartAutoMax(SysMonPlugin *self, IUnknown *item) {
  CComQIPtr<ISysMonContentItemInternal> internal_item(item);
  ATLASSERT(internal_item);

  internal_item->SetChartAutoMax(self->auto_adjust_chart_max_);

  // Since currently chart scale are shared between all MonitorItem,
  // we don't actually need to set them in every MonitorItem.
  // Return 1 here to stop enumeration.
  return 1;
}

LRESULT SysMonPlugin::TimerCallback(UINT) {
  RefreshPerfSamples();

  CComQIPtr<IGoogleDesktopDisplaySite> sidebar_site(m_spUnkSite);
  GoogleDesktopDisplayTileDisplayState display_state =
    GDD_TILE_DISPLAY_STATE_RESTORED;
  ATLVERIFY(SUCCEEDED(sidebar_site->get_display_state(&display_state)));

  if ((display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED) ||
      (display_state == GDD_TILE_DISPLAY_STATE_POPPED_OUT)) {
    UpdateTitle();
  }
  return 0;
}

STDMETHODIMP SysMonPlugin::get_refresh_interval(int *interval) {
  ATLASSERT(interval);
  if (!interval)
    return E_POINTER;
  *interval = refresh_interval_;
  return S_OK;
}

STDMETHODIMP SysMonPlugin::put_refresh_interval(int new_interval) {
  refresh_interval_ = new_interval;

  CComQIPtr<IGoogleDesktopDisplaySite> sidebar_site(m_spUnkSite);
  ATLASSERT(sidebar_site);

  CComQIPtr<IGoogleDesktopDisplayPluginHelper> helper(helper_);
  ATLASSERT(helper);

  if (sidebar_site && helper) {
    GoogleDesktopDisplayTileDisplayState display_state =
      GDD_TILE_DISPLAY_STATE_RESTORED;
    ATLVERIFY(SUCCEEDED(sidebar_site->get_display_state(&display_state)));

    if (display_state == GDD_TILE_DISPLAY_STATE_MINIMIZED) {
      msg_wnd_.SetRefreshInterval(
        (refresh_interval_ + kAdditionUpdateDelayWhenMinited) * 1000);
    } else if (display_state == GDD_TILE_DISPLAY_STATE_RESTORED) {
      msg_wnd_.SetRefreshInterval(refresh_interval_ * 1000);
    }
  }
  return S_OK;
}

STDMETHODIMP SysMonPlugin::get_active_monitors(int *monitors) {
  ATLASSERT(monitors);
  if (!monitors)
    return E_POINTER;
  *monitors = active_monitors_;
  return S_OK;
}
STDMETHODIMP SysMonPlugin::put_active_monitors(int new_monitors) {
  active_monitors_ = new_monitors;
  ChangeItems();

  return S_OK;
}

STDMETHODIMP SysMonPlugin::get_max_disk_rw_in_chart(int *max_disk_rw) {
  ATLASSERT(max_disk_rw);
  if (!max_disk_rw)
    return E_POINTER;
  *max_disk_rw = max_disk_rw_in_chart_;
  return S_OK;
}
STDMETHODIMP SysMonPlugin::put_max_disk_rw_in_chart(int max_disk_rw){
  max_disk_rw_in_chart_ = max_disk_rw;
  EnumContentItem(NotifyChartScale);
  return S_OK;
}

STDMETHODIMP SysMonPlugin::get_max_net_io_in_chart(int *max_net_io) {
  ATLASSERT(max_net_io);
  if (!max_net_io)
    return E_POINTER;
  *max_net_io = max_net_io_in_chart_;
  return S_OK;
}
STDMETHODIMP SysMonPlugin::put_max_net_io_in_chart(int max_net_io) {
  max_net_io_in_chart_ = max_net_io;
  EnumContentItem(NotifyChartScale);
  return S_OK;
}

STDMETHODIMP SysMonPlugin::get_auto_adjust_chart_max(
    int *auto_adjust_chart_max) {
  ATLASSERT(auto_adjust_chart_max);
  if (!auto_adjust_chart_max)
    return E_POINTER;
  *auto_adjust_chart_max = auto_adjust_chart_max_;
  return S_OK;
}

STDMETHODIMP SysMonPlugin::put_auto_adjust_chart_max(int auto_adjust_chart_max) {
  auto_adjust_chart_max_ = auto_adjust_chart_max;

  if (!auto_adjust_chart_max) {
    EnumContentItem(NotifyChartScale);
  }
  EnumContentItem(NotifyChartAutoMax);
  return S_OK;
}
