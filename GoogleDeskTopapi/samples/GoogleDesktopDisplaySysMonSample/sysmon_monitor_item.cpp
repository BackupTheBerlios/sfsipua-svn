// Copyright 2005 Google Inc. All Rights Reserved.
//
// MonitorItem is the class that does the real job of collecting performance
// data and renders it.
//
// MonitorItem is base class that
//   1. defines the common interface between SysMonContentItem and MonitorItem;
//   2. defines utility functions such as FormatBytes;
// It has the following derivatives :
//   MonitorItem_CPU,
//   MonitorItem_Mem,
//   MonitorItem_Disk,
//   MonitorItem_Net
//
// If we want to add new performance monitor types, we need to update the
// follownig places:
//   1. Add a enum constants for the new monitor types in sysmon.idl,
//      (e.g ACTIVE_MON_TR_PROCESS_TIME)
//   2. Derive your monitor item from MonitorItem, providing customized Init,
//      CollectData, etc. (e.g. MonitorItem_TR_ProcessTime)
//   3. Add an entry MonitorItemsMap for your new monitor item;
//      (e.g.
//        { ACTIVE_MON_TR_PROCESS_TIME,
//          MonItemClassFactory<MonitorItem_TR_ProcessTime>::CreateInstance })
// And that's it.
#include "stdafx.h"

#include <iphlpapi.h>
#include <atltypes.h>  // For CRect

#include "sysmon_plugin.h"  // For the constants only
#include "sysmon_content_item.h"
#include "sysmon_monitor_item.h"

namespace {
  const TCHAR *kMinimizedTitleFormat = NOTRANSL(L"%s : %s");

  const int kMinValueForAutoChartMax = 10240;

  // After collecting this number of samples less than the auto max,
  // do a degrade for the auto max value.
  const int kAutoMaxDegradeCounter = PERF_SAMPLE_HISTORY_SIZE;
};

//////////////////////////////////////////////////////////////////////////////
// MonitorItem
int MonitorItem::per_bar_caption_end_ = 60;
int MonitorItem::per_bar_percentage_info_start_ = 120;
int MonitorItem::per_bar_percentage_info_end_ = 160;
int MonitorItem::per_bar_width_ = 60;
int MonitorItem::per_bar_text_and_chart_gap_ = 4;

int MonitorItem::per_bar_desired_width_ = 60;
int MonitorItem::per_bar_caption_width_ = 40,
    MonitorItem::per_bar_percentage_width_ = 42,
    MonitorItem::per_bar_text_width_ = 100;

int MonitorItem::history_chart_text_and_chart_gap_ = 2;
int MonitorItem::history_chart_chart_gap_ = 4;
int MonitorItem::history_chart_height_ = 16;

COLORREF MonitorItem::per_bar_background_color_ = RGB(204, 204, 204);
COLORREF MonitorItem::per_bar_highlight_color_ = RGB(51, 102, 204);
COLORREF MonitorItem::history_chart_line_color_ = RGB(51, 102, 204);
COLORREF MonitorItem::history_chart_background_color_ = RGB(229, 229, 229);

uint32 MonitorItem::disk_read_max_ = kDefaultMaxDiskRWInChart;
uint32 MonitorItem::disk_write_max_ = kDefaultMaxDiskRWInChart;
uint32 MonitorItem::net_in_max_ = kDefaultMaxNetIOInChart;
uint32 MonitorItem::net_out_max_ = kDefaultMaxNetIOInChart;

int MonitorItem::auto_adjust_chart_max_ = kDefaultAutoAdjustChartMax;

HRESULT MonitorItem::Init(SysMonContentItem *owner) {
  owner_ = owner;

  return S_OK;
}

HRESULT MonitorItem::Uninit() {
  return S_OK;
}

void MonitorItem::SetChartScale(int max_disk_rw, int max_net_io) {
  disk_read_max_ = disk_write_max_ = max_disk_rw;
  net_in_max_ = net_out_max_ = max_net_io;
}

void MonitorItem::SetChartAutoMax(int auto_adjust) {
  auto_adjust_chart_max_ = auto_adjust;
}

CString MonitorItem::FormatBytes(uint64 num_of_bytes) const {
  CString str;
  const uint64 kGiga = 1073741824i64;
  const uint64 kMega = 1048576L;
  const uint64 kKilo = 1024;

  if (num_of_bytes > kGiga) {
    str.Format(NOTRANSL(L"%d.%02d G"),
      static_cast<int>(num_of_bytes / kGiga),
      static_cast<int>((num_of_bytes % kGiga) * 100 / kGiga));
  } else if (num_of_bytes > kMega) {
    str.Format(NOTRANSL(L"%d.%02d M"),
      static_cast<int>(num_of_bytes / kMega),
      static_cast<int>((num_of_bytes % kMega) * 100 / kMega));
  } else if (num_of_bytes > kKilo) {
    str.Format(NOTRANSL(L"%d.%02d K"),
      static_cast<int>(num_of_bytes / kKilo),
      static_cast<int>((num_of_bytes % kKilo) * 100 / kKilo));
  } else {
    str.Format(NOTRANSL(L"%d "), num_of_bytes);
  }

  return str;
}

CString MonitorItem::FormatBytesShort(uint64 num_of_bytes) const {
  CString str;
  const uint64 kGiga = 1073741824i64;
  const uint64 kMega = 1048576L;
  const uint64 kKilo = 1024;

  if (num_of_bytes > kGiga) {
    str.Format(NOTRANSL(L"%dG"),
      static_cast<int>(num_of_bytes / kGiga));
  } else if (num_of_bytes > kMega) {
    str.Format(NOTRANSL(L"%dM"),
      static_cast<int>(num_of_bytes / kMega));
  } else if (num_of_bytes > kKilo) {
    str.Format(NOTRANSL(L"%dK"),
      static_cast<int>(num_of_bytes / kKilo));
  } else {
    str.Format(NOTRANSL(L"%d"), num_of_bytes);
  }

  return str;
}

void MonitorItem::CalcLayout(int width) {
  if ((width > 180) && render_in_popout_view_) {
    // Everything
    per_bar_caption_end_ = per_bar_caption_width_;
    per_bar_percentage_info_end_ = width - per_bar_text_width_;
    per_bar_percentage_info_start_ = per_bar_percentage_info_end_ -
      per_bar_percentage_width_;
    per_bar_width_ = width - 2 * per_bar_text_and_chart_gap_ -
      per_bar_caption_width_ - per_bar_percentage_width_ - per_bar_text_width_;

    if (per_bar_width_ < per_bar_desired_width_) {
      per_bar_width_ = per_bar_desired_width_;
      per_bar_percentage_info_start_ = per_bar_caption_end_ +
        2 * per_bar_text_and_chart_gap_ + per_bar_width_;
      per_bar_percentage_info_end_ = per_bar_percentage_info_start_ +
        per_bar_percentage_width_;
    }
  } else if (width > 140) {
    // No extra text
    per_bar_caption_end_ = per_bar_caption_width_;
    per_bar_percentage_info_end_ = width;
    per_bar_percentage_info_start_ = per_bar_percentage_info_end_ -
      per_bar_percentage_width_;
    per_bar_width_ = width - 2 * per_bar_text_and_chart_gap_ -
      per_bar_caption_end_ - per_bar_percentage_width_;
  } else if (width > 80) {
    // No pencetage info
    per_bar_caption_end_ = per_bar_caption_width_;
    per_bar_percentage_info_start_ =
    per_bar_percentage_info_end_ = width;
    per_bar_width_ = width - per_bar_text_and_chart_gap_ -
      per_bar_caption_width_;
  } else {
    // Just the bar
    per_bar_caption_end_ = 0;
    per_bar_percentage_info_start_ =
    per_bar_percentage_info_end_ = width;
    per_bar_width_ = width;
  }
}

void MonitorItem::DrawPercentageBar(HDC hdc,
                                    const RECT &bounds,
                                    int percentage) {
  int width, height, hi_part;

  width = bounds.right - bounds.left + 1;
  height = bounds.bottom - bounds.top + 1;
  hi_part = width * percentage / 10000;

  FillSolidRect(hdc,
    bounds.left, bounds.top, hi_part, height,
    per_bar_highlight_color_);

  FillSolidRect(hdc,
    bounds.left + hi_part, bounds.top, width - hi_part, height,
    per_bar_background_color_);
}

void MonitorItem::DrawHistoryChart(HDC hdc,
    const CircularBuffer<uint32> &history, uint32 scale,
    const RECT &bounds) {
  CRect chart_bounds(bounds);
  HPEN chart_pen = CreatePen(PS_SOLID, 2, history_chart_line_color_);

  COLORREF back_color = GetBkColor(hdc);
  FillSolidRect(hdc,
    chart_bounds.left, chart_bounds.top,
    chart_bounds.Width(), chart_bounds.Height(),
    history_chart_background_color_);

  if (scale) {
    // Only draws chart if scale is not zero
    HGDIOBJ old_pen = SelectObject(hdc, chart_pen);

    uint32 index = history.size();
    for (int x = chart_bounds.right - 1;
        (x >= chart_bounds.left) && (index >= 1); x -= 2, --index) {

      uint32 sample = history.at(index - 1);
      int y = chart_bounds.Height() * sample / scale;
      y = chart_bounds.bottom - y;
      if (y < chart_bounds.top) {
        y = chart_bounds.top;
      }

      if (y < chart_bounds.bottom - 1) {
        MoveToEx(hdc, x, y, NULL);
        LineTo(hdc, x, chart_bounds.bottom - 1);
      }
    }

    SelectObject(hdc, old_pen);
  }
  SetBkColor(hdc, back_color);

  DeleteObject(chart_pen);
}

void MonitorItem::DrawCaptionAndHistoryChart(HDC hdc,
    const TCHAR *caption, const TCHAR *text,
    const CircularBuffer<uint32> &history, uint32 scale,
    const RECT &bounds) {
  CSize caption_size;
  CRect caption_bounds(bounds), chart_bounds(bounds), draw_bounds;
  int width = chart_bounds.Width();

  HGDIOBJ old_font = SelectObject(hdc, owner_->get_caption_font());
  GetTextExtentPoint32(hdc, 
    caption, static_cast<int>(_tcslen(caption)), &caption_size);
  caption_bounds.bottom = caption_bounds.top + caption_size.cy;

  CString str = caption;
  draw_bounds = caption_bounds;
  DrawString(hdc, &str, &draw_bounds, DT_LEFT);
  if (caption_bounds.Width() - caption_size.cx > 20) {
    CRect text_bounds(caption_bounds);

    SelectObject(hdc, owner_->get_text_font());
    text_bounds.left += caption_size.cx + 2;

    str = text;
    DrawString(hdc,
      &str, text_bounds, DT_LEFT | DT_END_ELLIPSIS);
  }

  chart_bounds.top = caption_bounds.bottom + history_chart_text_and_chart_gap_;
  DrawHistoryChart(hdc, history, scale, chart_bounds);

  SelectObject(hdc, old_font);
}

void MonitorItem::RenderPencentageShort(HDC hdc,
                                        const RECT *bounds,
                                        const TCHAR *caption_text,
                                        const TCHAR *percentage_text,
                                        int percentage) {
  CRect caption_bounds, text_bounds, chart_bounds;

  int width, height;
  CString caption(caption_text), text(percentage_text);

  int save_id = SaveDC(hdc);

  width = bounds->right - bounds->left + 1;
  height = bounds->bottom - bounds->top + 1;

  CalcLayout(width);

  if (per_bar_caption_end_) {
    SelectObject(hdc, owner_->get_caption_font());
    caption_bounds.SetRect(0, 0, per_bar_caption_end_, height);
    caption_bounds.OffsetRect(bounds->left, bounds->top);

    DrawString(hdc, &caption, caption_bounds, DT_RIGHT);
  }

  if (per_bar_percentage_info_start_ < width) {
    SelectObject(hdc, owner_->get_text_font());
    text_bounds.SetRect(
      per_bar_percentage_info_start_, 0,
      min(per_bar_percentage_info_end_, width), height);
    text_bounds.OffsetRect(bounds->left, bounds->top);

    DrawString(hdc,
      &text, text_bounds, DT_RIGHT | DT_END_ELLIPSIS);
    if (text_bounds.Width() > per_bar_percentage_width_) {
      per_bar_percentage_width_ = text_bounds.Width();
    }
  }

  chart_bounds.SetRect(
    per_bar_caption_end_ + per_bar_text_and_chart_gap_,
    2,
    per_bar_percentage_info_start_ - per_bar_text_and_chart_gap_,
    height - 2);
  if (chart_bounds.Width() > width) {
    chart_bounds.right = chart_bounds.left + width - 1;
  }
  chart_bounds.OffsetRect(bounds->left, bounds->top);
  DrawPercentageBar(hdc, chart_bounds, percentage);

  RestoreDC(hdc, save_id);
}

void MonitorItem::RenderHistoryShort(HDC hdc,
                            const RECT *bounds,
                            const CircularBuffer<uint32> &history,
                            uint32 scale,
                            const TCHAR *caption_text,
                            const TCHAR *extra_text) {
  CRect caption_bounds, text_bounds, chart_bounds;

  int width, height;
  CString caption(caption_text), text(extra_text);

  int save_id = SaveDC(hdc);

  width = bounds->right - bounds->left + 1;
  height = bounds->bottom - bounds->top + 1;

  CalcLayout(width);

  if (per_bar_caption_end_) {
    SelectObject(hdc, owner_->get_caption_font());
    caption_bounds.SetRect(0, 0, per_bar_caption_end_, height);
    caption_bounds.OffsetRect(bounds->left, bounds->top);

    DrawString(hdc, &caption, caption_bounds, DT_RIGHT);
  }

  if (per_bar_percentage_info_start_ < width) {
    SelectObject(hdc, owner_->get_text_font());
    text_bounds.SetRect(
      per_bar_percentage_info_start_, 0,
      min(per_bar_percentage_info_end_, width), height);
    text_bounds.OffsetRect(bounds->left, bounds->top);

    DrawString(hdc,
      &text, text_bounds, DT_RIGHT | DT_END_ELLIPSIS);
    if (text_bounds.Width() > per_bar_percentage_width_) {
      per_bar_percentage_width_ = text_bounds.Width();
    }
  }

  chart_bounds.SetRect(
    per_bar_caption_end_ + per_bar_text_and_chart_gap_,
    2,
    per_bar_percentage_info_start_ - per_bar_text_and_chart_gap_,
    height - 2);
  if (chart_bounds.Width() > width) {
    chart_bounds.right = chart_bounds.left + width - 1;
  }
  chart_bounds.OffsetRect(bounds->left, bounds->top);
  DrawHistoryChart(hdc, history, scale, chart_bounds);

  RestoreDC(hdc, save_id);
}

//////////////////////////////////////////////////////////////////////////////
// MonitorItem_CPU
HRESULT MonitorItem_CPU::Init(SysMonContentItem *owner) {
  MonitorItem::Init(owner);

  cpu_time_ = monitor_.GetLoad();
  UpdateItem();
  return S_OK;
}

HRESULT MonitorItem_CPU::CollectData() {
  cpu_time_ = monitor_.GetLoad();

  UpdateItem();
  return S_OK;
}

HRESULT MonitorItem_CPU::GetItemHeight(HDC hdc, long width, long *height) {
  ATLASSERT(height);

  int caption_height = GetFontHeightInPixels(hdc, owner_->get_caption_font());
  int text_height = GetFontHeightInPixels(hdc, owner_->get_text_font());

  *height = max(caption_height, text_height);
  return S_OK;
}

HRESULT MonitorItem_CPU::GetItemDetailsHeight(HDC hdc,
                                              long width, long *height) {
  return GetItemHeight(hdc, width, height);
}

HRESULT MonitorItem_CPU::RenderItem(HDC hdc, const RECT *bounds) {
  CString caption, text;
  caption.LoadString(IDS_CAPTION_CPU);
  text.Format(NOTRANSL(L"%d%%"), cpu_time_ / 100);

  render_in_popout_view_ = false;
  RenderPencentageShort(hdc, bounds, caption, text, cpu_time_);
  return S_OK;
}

HRESULT MonitorItem_CPU::RenderItemDetails(HDC hdc, const RECT *bounds) {
  CString caption, text, percentage_format;
  caption.LoadString(IDS_CAPTION_CPU);
  percentage_format.LoadString(IDS_TEXT_PERCENTAGE);
  text.Format(percentage_format, cpu_time_ / 100, cpu_time_ % 100);

  render_in_popout_view_ = true;
  RenderPencentageShort(hdc, bounds, caption, text, cpu_time_);
  return S_OK;
}

void MonitorItem_CPU::UpdateItem() {
  CString str, tooltip_format, caption;

  tooltip_format.LoadString(IDS_TOOLTIP_CPU);
  str.Format(tooltip_format,
             cpu_time_ / 100,
             cpu_time_ % 100);

  caption.LoadString(IDS_CAPTION_CPU);
  owner_->put_heading(caption);
  owner_->put_tooltip(str);
}

HRESULT MonitorItem_CPU::GetMinimizedTitle(CString *title) const {
  CString caption, text;
  caption.LoadString(IDS_CAPTION_CPU);
  text.Format(NOTRANSL(L"%d%%"), cpu_time_ / 100);

  title->Format(kMinimizedTitleFormat, caption, text);
  return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// MonitorItem_Mem
MonitorItem_Mem::MonitorItem_Mem()
  : MonitorItem(),
    mem_total_virtual_(0),
    mem_commited_virtual_(0),
    mem_total_physical_(0),
    mem_used_physical_(0) {
}

HRESULT MonitorItem_Mem::Init(SysMonContentItem *owner) {
  HRESULT hr = MonitorItem::Init(owner);
  ATLASSERT(hr == S_OK);

  CollectData();
  return hr;
}

HRESULT MonitorItem_Mem::CollectData() {
  MEMORYSTATUSEX ms;
  ms.dwLength = sizeof(ms);
  GlobalMemoryStatusEx(&ms);
  mem_total_physical_ = ms.ullTotalPhys;
  mem_used_physical_ = mem_total_physical_- ms.ullAvailPhys;
  mem_total_virtual_ = ms.ullTotalPageFile;
  mem_commited_virtual_ = mem_total_virtual_ - ms.ullAvailPageFile;

  UpdateItem();
  return S_OK;
}

HRESULT MonitorItem_Mem::GetItemHeight(HDC dc, long width, long *height) {
  ATLASSERT(height);

  int caption_height = GetFontHeightInPixels(dc, owner_->get_caption_font());
  int text_height = GetFontHeightInPixels(dc, owner_->get_text_font());

  *height = max(caption_height, text_height);
  return S_OK;
}

HRESULT MonitorItem_Mem::GetItemDetailsHeight(HDC hdc,
                                              long width, long *height) {
  ATLASSERT(height);

  int caption_height = GetFontHeightInPixels(hdc, owner_->get_caption_font());
  int text_height = GetFontHeightInPixels(hdc, owner_->get_text_font());

  *height = max(caption_height, text_height) * 2 + 4;  // We have two lines
  return S_OK;
}

HRESULT MonitorItem_Mem::RenderItem(HDC hdc, const RECT *bounds) {
  render_in_popout_view_ = false;

  CString caption, text;
  int physical_load = 0;

  caption.LoadString(IDS_CAPTION_MEM);
  if (mem_total_physical_) {
    physical_load = static_cast<int>(
      (mem_used_physical_ * 10000) / mem_total_physical_);
  }
  text.Format(NOTRANSL(L"%d%%"), physical_load / 100);

  RenderPencentageShort(hdc, bounds, caption, text, physical_load);
  return S_OK;
}

HRESULT MonitorItem_Mem::RenderItemDetails(HDC hdc, const RECT *bounds) {
  CRect caption_bounds, text_bounds, extra_bounds, chart_bounds;

  CString percentage_text_format;
  percentage_text_format.LoadString(IDS_TEXT_PERCENTAGE);

  int width, height;
  CString caption, text, extra;
  int virtual_load = 0, physical_load = 0;

  int save_id = SaveDC(hdc);

  width = bounds->right - bounds->left + 1;
  height = bounds->bottom - bounds->top + 1;

  if (mem_total_virtual_) {
    virtual_load = static_cast<int>(
      (mem_commited_virtual_ * 10000) / mem_total_virtual_);
  }
  if (mem_total_physical_) {
    physical_load = static_cast<int>(
      (mem_used_physical_ * 10000) / mem_total_physical_);
  }

  render_in_popout_view_ = true;
  CalcLayout(width);

  if (per_bar_caption_end_) {
    SelectObject(hdc, owner_->get_caption_font());

    caption.LoadString(IDS_CAPTION_MEM_VIRTUAL);
    caption_bounds.SetRect(0, 0, per_bar_caption_end_, height / 2);
    caption_bounds.OffsetRect(bounds->left, bounds->top);
    DrawString(hdc, &caption, caption_bounds, DT_RIGHT);

    caption.LoadString(IDS_CAPTION_MEM_PHYSICAL);
    caption_bounds.SetRect(0, 0, per_bar_caption_end_, height / 2 + 2);
    caption_bounds.OffsetRect(bounds->left, bounds->top + height / 2);
    DrawString(hdc, &caption, caption_bounds, DT_RIGHT);
  }

  if (per_bar_percentage_info_start_ < width) {
    SelectObject(hdc, owner_->get_text_font());

    text.Format(percentage_text_format, virtual_load / 100, virtual_load % 100);
    text_bounds.SetRect(
      per_bar_percentage_info_start_, 0,
      min(per_bar_percentage_info_end_, width), height / 2);
    text_bounds.OffsetRect(bounds->left, bounds->top);
    CRect draw_bounds(text_bounds);
    DrawString(hdc,
      &text, draw_bounds, DT_RIGHT | DT_END_ELLIPSIS);

    text.Format(percentage_text_format, physical_load / 100, physical_load % 100);
    text_bounds.OffsetRect(0, height / 2 + 2);
    DrawString(hdc,
      &text, text_bounds, DT_RIGHT | DT_END_ELLIPSIS);
  }

  if (per_bar_percentage_info_end_ < width) {
    SelectObject(hdc, owner_->get_text_font());

    CSize extra_size;
    CString mem_text_format;
    mem_text_format.LoadString(IDS_TEXT_MEM);

    extra.Format(mem_text_format,
      FormatBytes(mem_commited_virtual_),
      FormatBytes(mem_total_virtual_));
    GetTextExtentPoint32(hdc, extra, extra.GetLength(), &extra_size);
    if (extra_size.cx > per_bar_text_width_) {
      per_bar_text_width_ = extra_size.cx + 2;
    }
    extra_bounds.SetRect(
      per_bar_percentage_info_end_ + 2, 0,
      width, height / 2);
    extra_bounds.OffsetRect(bounds->left, bounds->top);
    CRect draw_bounds(extra_bounds);
    DrawString(hdc,
      &extra, draw_bounds, DT_RIGHT | DT_END_ELLIPSIS);

    extra.Format(mem_text_format,
      FormatBytes(mem_used_physical_),
      FormatBytes(mem_total_physical_));
    GetTextExtentPoint32(hdc, extra, extra.GetLength(), &extra_size);
    if (extra_size.cx > per_bar_text_width_) {
      per_bar_text_width_ = extra_size.cx + 2;
    }
    extra_bounds.OffsetRect(0, height / 2 + 2);
    DrawString(hdc,
      &extra, extra_bounds, DT_RIGHT | DT_END_ELLIPSIS);
  }

  chart_bounds.SetRect(
    per_bar_caption_end_ + per_bar_text_and_chart_gap_,
    2,
    per_bar_percentage_info_start_ - per_bar_text_and_chart_gap_,
    height / 2 - 2);
  if (chart_bounds.Width() > width) {
    chart_bounds.right = chart_bounds.left + width - 1;
  }
  chart_bounds.OffsetRect(bounds->left, bounds->top);
  DrawPercentageBar(hdc, chart_bounds, virtual_load);

  chart_bounds.OffsetRect(0, height / 2 + 2);
  DrawPercentageBar(hdc, chart_bounds, physical_load);

  RestoreDC(hdc, save_id);
  return S_OK;
}

void MonitorItem_Mem::UpdateItem() {
  CString str, tooltip_format, caption;

  tooltip_format.LoadString(IDS_TOOLTIP_MEM);

  str.Format(tooltip_format,
            FormatBytes(mem_commited_virtual_),
            FormatBytes(mem_total_virtual_),
            FormatBytes(mem_used_physical_),
            FormatBytes(mem_total_physical_));

  caption.LoadString(IDS_CAPTION_MEM);
  owner_->put_heading(caption);
  owner_->put_tooltip(str);
}

HRESULT MonitorItem_Mem::GetMinimizedTitle(CString *title) const {
  CString caption, text;
  caption.LoadString(IDS_CAPTION_MEM);

  int physical_load = 0;  
  if (mem_total_physical_) {
    physical_load = static_cast<int>(
      (mem_used_physical_ * 10000) / mem_total_physical_);
  }
  text.Format(NOTRANSL(L"%d%%"), physical_load / 100);

  title->Format(kMinimizedTitleFormat, caption, text);
  return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// MonitorItem_Disk
HRESULT MonitorItem_Disk::Init(SysMonContentItem *owner) {
  HRESULT hr = MonitorItem::Init(owner);
  ATLASSERT(hr == S_OK);

  GetDiskActivityCounters(NULL, NULL, &last_read_bytes_, &last_write_bytes_);
  last_time_ = GetTickCount();
  return hr;
}

HRESULT MonitorItem_Disk::CollectData(){
  disk_read_bytes_per_second_ = 0;
  disk_write_bytes_per_second_ = 0;

  DWORD now = GetTickCount();
  uint64 read_bytes, write_bytes;
  GetDiskActivityCounters(NULL, NULL, &read_bytes, &write_bytes);

  DWORD elapsed = now - last_time_;
  if (elapsed) {
    disk_read_bytes_per_second_ =
      static_cast<uint32>((read_bytes - last_read_bytes_) * 1000 / elapsed);
    disk_write_bytes_per_second_ =
      static_cast<uint32>((write_bytes - last_write_bytes_) * 1000 / elapsed);

    last_read_bytes_ = read_bytes;
    last_write_bytes_ = write_bytes;
    last_time_ = now;
  }

  read_history_.add(disk_read_bytes_per_second_);
  write_history_.add(disk_write_bytes_per_second_);
  total_history_.add(disk_read_bytes_per_second_ +
                     disk_write_bytes_per_second_);

  if (auto_adjust_chart_max_) {
    ++degrade_counter_;
    if (disk_read_bytes_per_second_ > disk_read_max_) {
      disk_read_max_ = disk_read_bytes_per_second_;
      degrade_counter_ = 0;
    }

    if (disk_write_bytes_per_second_ > disk_write_max_) {
      disk_write_max_ = disk_write_bytes_per_second_;
      degrade_counter_ = 0;
    }

    if (degrade_counter_ > kAutoMaxDegradeCounter) {
      degrade_counter_ = 0;

      disk_read_max_ >>= 1;
      if (disk_read_max_ < kAutoMaxDegradeCounter) {
        disk_read_max_ = kAutoMaxDegradeCounter;
      }

      disk_write_max_ >>= 1;
      if (disk_write_max_ < kAutoMaxDegradeCounter) {
        disk_write_max_ = kAutoMaxDegradeCounter;
      }
    }
  }

  UpdateItem();
  return S_OK;
}

HRESULT MonitorItem_Disk::GetItemHeight(HDC hdc, long width, long *height) {
  ATLASSERT(height);

  int caption_height = GetFontHeightInPixels(hdc, owner_->get_caption_font());
  int text_height = GetFontHeightInPixels(hdc, owner_->get_text_font());

  *height = max(caption_height, text_height);
  return S_OK;
}

HRESULT MonitorItem_Disk::GetItemDetailsHeight(HDC hdc,
                                              long width, long *height) {
  ATLASSERT(height);

  int caption_height = GetFontHeightInPixels(hdc, owner_->get_caption_font());
  int text_height = GetFontHeightInPixels(hdc, owner_->get_text_font());

  *height = max(caption_height, text_height) +
    history_chart_text_and_chart_gap_ + history_chart_height_;
  return S_OK;
}

HRESULT MonitorItem_Disk::RenderItem(HDC hdc, const RECT *bounds) {
  render_in_popout_view_ = false;
  CString caption, text;

  caption.LoadString(IDS_CAPTION_DISK);
  text.Format(NOTRANSL(L"%sB/s"),
              FormatBytesShort(disk_read_bytes_per_second_ +
                               disk_write_bytes_per_second_));
  RenderHistoryShort(hdc,
    bounds, total_history_, disk_read_max_ + disk_write_max_, caption, text);
  return S_OK;
}

HRESULT MonitorItem_Disk::RenderItemDetails(HDC hdc, const RECT *bounds) {
  render_in_popout_view_ = true;

  CRect item_bounds(bounds);
  int width = item_bounds.Width();

  CString caption, text;

  CString throughput_text_format;
  throughput_text_format.LoadString(IDS_TEXT_THROUGHPUT);

  item_bounds.right = item_bounds.left +
    (width - history_chart_chart_gap_) / 2;

  caption.LoadString(IDS_CAPTION_DISK_READ);
  text.Format(throughput_text_format, FormatBytes(disk_read_bytes_per_second_));
  DrawCaptionAndHistoryChart(hdc,
    caption, text, read_history_, disk_read_max_, item_bounds);

  item_bounds.OffsetRect(width / 2, 0);
  caption.LoadString(IDS_CAPTION_DISK_WRITE);
  text.Format(throughput_text_format, FormatBytes(disk_write_bytes_per_second_));
  DrawCaptionAndHistoryChart(hdc,
    caption, text, write_history_, disk_write_max_, item_bounds);

  return S_OK;
}

void MonitorItem_Disk::UpdateItem() {
  CString str, tooltip_format, caption;

  tooltip_format.LoadString(IDS_TOOLTIP_DISK);
  str.Format(tooltip_format,
             FormatBytes(disk_read_bytes_per_second_),
             FormatBytes(disk_write_bytes_per_second_));

  caption.LoadString(IDS_CAPTION_DISK);
  owner_->put_heading(caption);
  owner_->put_tooltip(str);
}

HRESULT MonitorItem_Disk::GetMinimizedTitle(CString *title) const {
  CString caption, text;
  caption.LoadString(IDS_CAPTION_DISK);
  text.Format(NOTRANSL(L"%sB/s"), 
              FormatBytesShort(disk_read_bytes_per_second_ + 
                               disk_write_bytes_per_second_));

  title->Format(kMinimizedTitleFormat, caption, text);
  return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// MonitorItem_Net
HRESULT MonitorItem_Net::Init(SysMonContentItem *owner) {
  HRESULT hr = MonitorItem::Init(owner);
  ATLASSERT(hr == S_OK);

  DWORD size = 0;

  MIB_IFTABLE *if_table = NULL;
  if (GetIfTable(NULL, &size, FALSE) == ERROR_INSUFFICIENT_BUFFER) {
    if_table = reinterpret_cast<MIB_IFTABLE *>(new BYTE[size]);
    ATLASSERT(if_table);
    if (!if_table) {
      return E_OUTOFMEMORY;
    }
  }
  
  if (GetIfTable(if_table, &size, FALSE) != NO_ERROR) {
    // We should never get here.
    ATLASSERT(false);
    return E_FAIL;
  }

  // Enumerates all interfaces and starts stat on them.
  if_stat_.RemoveAll();
  for (uint32 i = 0; i < if_table->dwNumEntries; ++i) {
    MIB_IFROW *if_row;

    if_row = &(if_table->table[i]);
    if (if_row->dwType != MIB_IF_TYPE_LOOPBACK) {
      IfStat stat;

      stat.if_index = if_row->dwIndex;
      stat.in_bytes = if_row->dwInOctets;
      stat.out_bytes = if_row->dwOutOctets;
      stat.stat_time = GetTickCount();

      if_stat_.Add(stat);
    }
  }

  stat_bytes_inited_ = true;
  return hr;
}

HRESULT MonitorItem_Net::CollectData() {

  net_received_bytes_per_second_ = 0;
  net_sent_bytes_per_second_ = 0;

  // Collect stat info from interface.
  for (int i = 0; i < if_stat_.GetSize(); ++i) {
    MIB_IFROW if_row;
    IfStat &stat = if_stat_[i];
    if_row.dwIndex = stat.if_index;
    DWORD now = GetTickCount();
    if (GetIfEntry(&if_row) == NO_ERROR) {
      DWORD elapsed = now - stat.stat_time;
      if (elapsed) {
        DWORD num_bytes = if_row.dwInOctets - stat.in_bytes;
        net_received_bytes_per_second_ += (num_bytes) * 1000 / elapsed;

        num_bytes = if_row.dwOutOctets - stat.out_bytes;
        net_sent_bytes_per_second_ += (num_bytes) * 1000 / elapsed;

        stat.in_bytes = if_row.dwInOctets;
        stat.out_bytes = if_row.dwOutOctets;
        stat.stat_time = now;
      }
    }
  }

  in_history_.add(net_received_bytes_per_second_);
  out_history_.add(net_sent_bytes_per_second_);
  total_history_.add(net_received_bytes_per_second_ +
                     net_sent_bytes_per_second_);

  if (auto_adjust_chart_max_) {
    ++degrade_counter_;
    if (net_received_bytes_per_second_ > net_in_max_) {
      net_in_max_ = net_received_bytes_per_second_;
      degrade_counter_ = 0;
    }

    if (net_sent_bytes_per_second_ > net_out_max_) {
      net_out_max_ = net_sent_bytes_per_second_;
      degrade_counter_ = 0;
    }

    if (degrade_counter_ > kAutoMaxDegradeCounter) {
      degrade_counter_ = 0;

      net_in_max_ >>= 1;
      if (net_in_max_ < kAutoMaxDegradeCounter) {
        net_in_max_ = kAutoMaxDegradeCounter;
      }

      net_out_max_ >>= 1;
      if (net_out_max_ < kAutoMaxDegradeCounter) {
        net_out_max_ = kAutoMaxDegradeCounter;
      }
    }
  }

  UpdateItem();
  return S_OK;
}

HRESULT MonitorItem_Net::GetItemHeight(HDC hdc, long width, long *height) {
  ATLASSERT(height);

  int caption_height = GetFontHeightInPixels(hdc, owner_->get_caption_font());
  int text_height = GetFontHeightInPixels(hdc, owner_->get_text_font());

  *height = max(caption_height, text_height);
  return S_OK;
}

HRESULT MonitorItem_Net::GetItemDetailsHeight(HDC hdc,
                                              long width, long *height) {
  ATLASSERT(height);

  int caption_height = GetFontHeightInPixels(hdc, owner_->get_caption_font());
  int text_height = GetFontHeightInPixels(hdc, owner_->get_text_font());

  *height = max(caption_height, text_height) +
    history_chart_text_and_chart_gap_ + history_chart_height_;
  return S_OK;
}

HRESULT MonitorItem_Net::RenderItem(HDC hdc, const RECT *bounds) {
  render_in_popout_view_ = false;
  CString caption, text;

  caption.LoadString(IDS_CAPTION_NET);
  text.Format(NOTRANSL(L"%sB/s"),
              FormatBytesShort(net_received_bytes_per_second_ +
                                net_sent_bytes_per_second_));
  RenderHistoryShort(hdc,
    bounds, total_history_, net_in_max_ + net_out_max_, caption, text);
  return S_OK;
}

HRESULT MonitorItem_Net::RenderItemDetails(HDC hdc, const RECT *bounds) {
  render_in_popout_view_ = true;

  CRect item_bounds(bounds);
  int width = item_bounds.Width();

  CString caption, text;

  CString throughput_text_format;
  throughput_text_format.LoadString(IDS_TEXT_THROUGHPUT);

  item_bounds.right = item_bounds.left +
    (width - history_chart_chart_gap_) / 2;

  caption.LoadString(IDS_CAPTION_NET_IN);
  text.Format(throughput_text_format,
              FormatBytes(net_received_bytes_per_second_));
  DrawCaptionAndHistoryChart(hdc,
    caption, text, in_history_, net_in_max_, item_bounds);

  item_bounds.OffsetRect(width / 2, 0);
  caption.LoadString(IDS_CAPTION_NET_OUT);
  text.Format(throughput_text_format, FormatBytes(net_sent_bytes_per_second_));
  DrawCaptionAndHistoryChart(hdc,
    caption, text, out_history_, net_out_max_, item_bounds);

  return S_OK;
}

void MonitorItem_Net::UpdateItem() {
  CString str, tooltip_format, caption;

  tooltip_format.LoadString(IDS_TOOLTIP_NET);
  str.Format(tooltip_format,
            FormatBytes(net_received_bytes_per_second_),
            FormatBytes(net_sent_bytes_per_second_));

  caption.LoadString(IDS_CAPTION_NET);
  owner_->put_heading(caption);
  owner_->put_tooltip(str);
}

HRESULT MonitorItem_Net::GetMinimizedTitle(CString *title) const {
  CString caption, text;
  caption.LoadString(IDS_CAPTION_NET);
  text.Format(NOTRANSL(L"%sB/s"), 
              FormatBytesShort(net_received_bytes_per_second_ + 
                               net_sent_bytes_per_second_));

  title->Format(kMinimizedTitleFormat, caption, text);
  return S_OK;
}
