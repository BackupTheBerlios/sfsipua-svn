// Copyright 2005 Google Inc. All Rights Reserved.
//
// SysMonContentItem serves as bridge between the data collector/renderer
// class MonitorItem and the plugin (also the sidebar).
#ifndef SYSMON_CONTENT_ITEM_H__
#define SYSMON_CONTENT_ITEM_H__

#include "../common/GoogleDesktopDisplayAPI.h"

#include "GoogleDesktopDisplaySysMonSample.h"

// Internal class that collects data and renders it.
// Definitions are in sysmon_monitor_item.h
// Implementations are in sysmon_monitor_item.cpp
class MonitorItem;

class SysMonPlugin;

interface DECLSPEC_UUID("43C2F9E0-2788-4ad6-9FCD-01973FE74054")
DECLSPEC_NOVTABLE
ISysMonContentItemInternal : public IUnknown {
  // Creates the actual MonitoItem instance based on monitor_item_type.
  STDMETHOD(SetMonitorItem)(int monitor_item_type) = 0;

  // Gets the MonitorItem associated with SysMonContentItem
  STDMETHOD(GetMonitorItem)(MonitorItem **item) = 0;

  // Gets the active monitor type of SysMonContentItem.
  STDMETHOD(GetMonitorItemType)(int *monitor_item_type) = 0;

  // Gets the active monitor type of SysMonContentItem.
  STDMETHOD(GetMimimizedTitle)(CString *title) = 0;

  // Suggests UI font to use.
  STDMETHOD(SetFonts)(HFONT caption_font, HFONT text_font) = 0;

  // Sets the max value for history charts.
  STDMETHOD(SetChartScale)(int max_disk_rw, int max_net_io) = 0;

  // Sets the flag of auto adjust chart max.
  STDMETHOD(SetChartAutoMax)(int auto_adjust_chart_max) = 0;

  // Triggers performance data gathering.
  STDMETHOD(OnPerfSampleArrive)() = 0;

  // Sets the container of the content item.
  STDMETHOD(SetContainer)(SysMonPlugin *container);
};

class SysMonContentItem :
  public CComObjectRootEx<CComSingleThreadModel>,
  public ISysMonContentItemInternal,
  public IDispatchImpl<IGoogleDesktopDisplayContentItemHandler,
    &IID_IGoogleDesktopDisplayContentItemHandler,
    &LIBID_GoogleDesktopDisplaySysMonSampleLib,
    /*wMajor =*/ 1, /*wMinor =*/ 0> {
 public:
  SysMonContentItem();

  BEGIN_COM_MAP(SysMonContentItem)
    COM_INTERFACE_ENTRY(IGoogleDesktopDisplayContentItemHandler)
    COM_INTERFACE_ENTRY(ISysMonContentItemInternal)

    COM_INTERFACE_ENTRY_AUTOAGGREGATE_BLIND(helper_.p,
      CLSID_GoogleDesktopDisplayContentItemHelper)
  END_COM_MAP()

  DECLARE_GET_CONTROLLING_UNKNOWN()

  HRESULT FinalConstruct();
  void FinalRelease();

  STDMETHOD(SetMonitorItem)(int monitor_item_type);
  STDMETHOD(GetMonitorItemType)(int *monitor_item_type);
  STDMETHOD(GetMonitorItem)(MonitorItem **item);
  STDMETHOD(GetMimimizedTitle)(CString *title);
  STDMETHOD(SetFonts)(HFONT caption_font, HFONT text_font);
  STDMETHOD(SetChartScale)(int max_disk_rw, int max_net_io);
  STDMETHOD(SetChartAutoMax)(int auto_adjust_chart_max);
  STDMETHOD(OnPerfSampleArrive)();
  STDMETHOD(SetContainer)(SysMonPlugin *container);

  // IGoogleDesktopDisplayContentItemHandler
  STDMETHOD(DrawItem)(GoogleDesktopDisplayTarget target,
    HDC dc,  const RECT *bounds);
  STDMETHOD(GetHeight)(GoogleDesktopDisplayTarget target,
    HDC dc, long width, long *height);
  STDMETHOD(OpenItem)();
  STDMETHOD(ToggleItemPinnedState)();
  STDMETHOD(GetIsTooltipRequired)(GoogleDesktopDisplayTarget target,
    HDC dc, const RECT *bounds, VARIANT_BOOL *is_required);
  STDMETHOD(OnDetailsView)(BSTR* title,
                           GoogleDesktopDisplayDetailsViewFlags* flags,
                           IUnknown** details_control,
                           VARIANT_BOOL* cancel);
  STDMETHOD(ProcessDetailsViewFeedback)(
    GoogleDesktopDisplayDetailsViewFlags flags);
  STDMETHOD(OnRemoveItem)(VARIANT_BOOL* cancel);

  void put_heading(const TCHAR *heading);
  void put_tooltip(const TCHAR *tooltip);

  HFONT get_caption_font() const {
    return caption_font_;
  }
  HFONT get_text_font() const {
    return text_font_;
  }

 private:
  CComPtr<IUnknown> helper_;

  HFONT caption_font_, text_font_;

  int monitor_item_type_;
  MonitorItem  *monitor_item_;

  // We did not AddRef our container_.
  SysMonPlugin * container_;
};
typedef CComObject<SysMonContentItem> SysMonContentItemImpl;

#endif  // SYSMON_CONTENT_ITEM_H__
