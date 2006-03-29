// Copyright 2005 Google Inc. All Rights Reserved.
//
// SysMonContentItem holds a place in sidebar and also holds an instance
// of MonitorItem (or its derived class). It servs two purposes:
// 1. Receives performance data ready notificate from SysMonPlugin
//    via OnPerfSampleArrive of ISysMonContentItemInternal. SysMonPlugin
//    notifies SysMonContentItem periodically which will in chain informs
//    MonitorItem to collect performance data. Inside OnPerfSampleArrive,
//    SysMonContentItem calls MonitorItem's CollectData to collect the data.
// 2. Forwards the drawing request from sidebar to the actual MonitorItem.
//
// MonitorItem and its derived classes collects and performance data and
// renders it on screen.
#include "stdafx.h"

#include "sysmon_plugin.h"
#include "sysmon_content_item.h"
#include "sysmon_monitor_item.h"

namespace {
  struct {
    int type;
    HRESULT (*create)(MonitorItem **monitor);
  } MonitorItemsMap [] = {
    { ACTIVE_MON_CPU, MonItemClassFactory<MonitorItem_CPU>::CreateInstance },
    { ACTIVE_MON_MEM, MonItemClassFactory<MonitorItem_Mem>::CreateInstance },
    { ACTIVE_MON_DISK, MonItemClassFactory<MonitorItem_Disk>::CreateInstance },
    { ACTIVE_MON_NET, MonItemClassFactory<MonitorItem_Net>::CreateInstance },
    { ACTIVE_MON_NONE, NULL }  // End of the map
  };

};

//////////////////////////////////////////////////////////////////////////////
// SysMonContentItem
SysMonContentItem::SysMonContentItem()
  : monitor_item_(NULL),
    container_(NULL),
    caption_font_(NULL),
    text_font_(NULL) {
}

HRESULT SysMonContentItem::FinalConstruct() {
  return S_OK;
}

void SysMonContentItem::FinalRelease() {
  if (monitor_item_) {
    delete monitor_item_;
    monitor_item_ = NULL;
  }
}

STDMETHODIMP SysMonContentItem::DrawItem(GoogleDesktopDisplayTarget target,
                                         HDC dc, const RECT *bounds) {
  if (monitor_item_) {
    bool pop_out = container_->get_popout_stat();

    if (pop_out) {
      return monitor_item_->RenderItemDetails(dc, bounds);
    } else {
      return monitor_item_->RenderItem(dc, bounds);
    }
  }
  return E_NOTIMPL;
}

STDMETHODIMP SysMonContentItem::GetHeight(GoogleDesktopDisplayTarget target,
                                          HDC dc, long width, long *height){
  if (monitor_item_) {
    bool pop_out = container_->get_popout_stat();

    if (pop_out) {
      return monitor_item_->GetItemDetailsHeight(dc, width, height);
    } else {
      return monitor_item_->GetItemHeight(dc, width, height);
    }
  }
  return E_NOTIMPL;
}

STDMETHODIMP SysMonContentItem::OpenItem(){
  return E_NOTIMPL;
}

STDMETHODIMP SysMonContentItem::ToggleItemPinnedState(){
  return E_NOTIMPL;
}

STDMETHODIMP SysMonContentItem::GetIsTooltipRequired(
    GoogleDesktopDisplayTarget target,
    HDC dc, const RECT *bounds, VARIANT_BOOL *is_required){
  return E_NOTIMPL;
}

STDMETHODIMP SysMonContentItem::OnDetailsView(
    BSTR* title,
    GoogleDesktopDisplayDetailsViewFlags* flags,
    IUnknown** details_control,
    VARIANT_BOOL* cancel){

  return E_NOTIMPL;
}

STDMETHODIMP SysMonContentItem::ProcessDetailsViewFeedback(
    GoogleDesktopDisplayDetailsViewFlags flags){
  return E_NOTIMPL;
}

STDMETHODIMP SysMonContentItem::OnRemoveItem(VARIANT_BOOL* cancel) {
  ATLASSERT(cancel != NULL);
  return E_NOTIMPL;
}

STDMETHODIMP SysMonContentItem::SetMonitorItem(int monitor_item_type) {
  ATLASSERT(monitor_item_ == NULL);

  monitor_item_type_ = monitor_item_type;

  for (int i = 0; (MonitorItemsMap[i].type != ACTIVE_MON_NONE); ++i) {
    if (monitor_item_type == MonitorItemsMap[i].type) {
      HRESULT hr = MonitorItemsMap[i].create(&monitor_item_);
      ATLASSERT(monitor_item_);

      if (monitor_item_) {
        monitor_item_->Init(this);
      }
    }
  }
  return (monitor_item_ != NULL) ? S_OK : E_FAIL;
}

STDMETHODIMP SysMonContentItem::GetMonitorItemType(int *monitor_item_type) {
  ATLASSERT(monitor_item_type);
  *monitor_item_type = monitor_item_type_;
  return S_OK;
}

STDMETHODIMP SysMonContentItem::GetMonitorItem(MonitorItem **item) {
  ATLASSERT(item);
  *item = monitor_item_;
  return S_OK;
}

STDMETHODIMP SysMonContentItem::GetMimimizedTitle(CString *title) {
  ATLASSERT(title);
  title->Empty();
  if (monitor_item_) {
    monitor_item_->GetMinimizedTitle(title);
  }
  return S_OK;
}

STDMETHODIMP SysMonContentItem::SetFonts(HFONT caption_font,
                                         HFONT text_font) {
  caption_font_ = caption_font;
  text_font_ = text_font;
  return S_OK;
}

STDMETHODIMP SysMonContentItem::SetChartScale(int max_disk_rw,
                                              int max_net_io) {
  if (monitor_item_) {
    monitor_item_->SetChartScale(max_disk_rw, max_net_io);
  }

  return S_OK;

}
STDMETHODIMP SysMonContentItem::SetChartAutoMax(int auto_adjust_chart_max) {
  if (monitor_item_) {
    monitor_item_->SetChartAutoMax(auto_adjust_chart_max);
  }

  return S_OK;
}

STDMETHODIMP SysMonContentItem::OnPerfSampleArrive() {
  if (monitor_item_) {
    monitor_item_->CollectData();
  }

  return S_OK;
}

STDMETHODIMP SysMonContentItem::SetContainer(SysMonPlugin *container) {
  container_ = container;
  return S_OK;
}

void SysMonContentItem::put_heading(const TCHAR *heading) {
  CComQIPtr<IGoogleDesktopDisplayContentItemHelper> helper(helper_);
  ATLASSERT(helper);
  if (!helper)
    return;

  CComBSTR str(heading);
  ATLVERIFY(SUCCEEDED(helper->put_heading(str)));
}

void SysMonContentItem::put_tooltip(const TCHAR *tooltip) {
  CComQIPtr<IGoogleDesktopDisplayContentItemHelper> helper(helper_);
  ATLASSERT(helper);
  if (!helper)
    return;

  CComBSTR str(tooltip);
  ATLVERIFY(SUCCEEDED(helper->put_tooltip(str)));
}
