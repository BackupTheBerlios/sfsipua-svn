// Copyright 2005 Google Inc. All Rights Reserved.
//
// MonitorItem collects performance data and renders it.
// These classes is intends for the internal work of SysMonContentItem.
#ifndef SYSMON_MONITOR_ITEM_H__
#define SYSMON_MONITOR_ITEM_H__

#include "circular_buffer.h"
#include "utils.h"

// MonitorItem defines the interface between SysMonContentItem and
// its derivation classes that do the real job. It also provide some
// utility functions such as FormatBytes.
class MonitorItem {
 public:
  MonitorItem() : owner_(NULL), render_in_popout_view_(false) {
  }
  virtual ~MonitorItem() {
    Uninit();
  }

  // owner will stored in owner_ for later use.
  virtual HRESULT Init(SysMonContentItem *owner);

  // Uninitialization work goes here.
  virtual HRESULT Uninit();

  // Collects performance data.
  // Called from SysMonContentItem's OnPerfSampleArrive.
  virtual HRESULT CollectData() = 0;

  // Gets the height as a content item.
  virtual HRESULT GetItemHeight(HDC hdc, long width, long *height) = 0;

  // Gets the height of an item in pop out view
  virtual HRESULT GetItemDetailsHeight(HDC hdc, long width, long *height) = 0;

  // Renders the data inside the sidebar as a content item.
  virtual HRESULT RenderItem(HDC hdc, const RECT *bounds) = 0;

  // Renders the data in pop out view
  virtual HRESULT RenderItemDetails(HDC hdc, const RECT *bounds) = 0;

  // Gets title for minimized plugin.
  virtual HRESULT GetMinimizedTitle(CString *title) const = 0;

  void SetChartScale(int max_disk_rw, int max_net_io);
  void SetChartAutoMax(int auto_adjust);

  // Formats the num_of_bytes in G, M, or K
  CString FormatBytes(uint64 num_of_bytes) const;
  CString FormatBytesShort(uint64 num_of_bytes) const;

  // Draws the percentage bar. percentage value of 10000 represents 100%.
  void DrawPercentageBar(HDC dc, const RECT &bounds, int percentage);

  // Chains the call to SysMonContentItem
  void DrawString(HDC hdc, CString *text, RECT *bounds, UINT flags) {
    DrawText(hdc, *text, text->GetLength(), bounds, flags);

    SIZE text_size; 
    GetTextExtentPoint32(hdc, *text, text->GetLength(), &text_size);
    bounds->right = bounds->left + text_size.cx;
 }

  // Draws the history chart in given bounds
  void DrawHistoryChart(HDC hdc,
    const CircularBuffer<uint32> &history, uint32 scale,
    const RECT &bounds);


 protected:
  // Calcs the geometry params.
  virtual void CalcLayout(int width);

  void DrawCaptionAndHistoryChart(
    HDC hdc, const TCHAR *caption, const TCHAR *text,
    const CircularBuffer<uint32> &history, uint32 scale,
    const RECT &bounds);

  // Renders monitor item in panel
  void RenderPencentageShort(HDC hdc,
                             const RECT *bounds,
                             const TCHAR *caption_text,
                             const TCHAR *percentage_text,
                             int percentage);
  void RenderHistoryShort(HDC hdc,
                             const RECT *bounds,
                             const CircularBuffer<uint32> &history,
                             uint32 scale,
                             const TCHAR *caption_text,
                             const TCHAR *extra_text);

  // Geometry parames
  // Two layout for the monitor items:
  // 1. Percentage bar layout that has a caption, a pencetage bar and a text
  //    description.
  // 2. History chart layout that has a caption and a text description on top
  //    and a history line chart at the bottom.
  // These params are shared among all MonitorItem derivatives.
  static int per_bar_caption_end_;
  static int per_bar_percentage_info_start_, per_bar_percentage_info_end_;
  static int per_bar_width_, per_bar_desired_width_;
  static int per_bar_text_and_chart_gap_;
  static int per_bar_caption_width_,
             per_bar_percentage_width_, per_bar_text_width_;

  static int history_chart_text_and_chart_gap_;
  static int history_chart_chart_gap_;
  static int history_chart_height_;

  // Max value for history chart
  static uint32 disk_read_max_;
  static uint32 disk_write_max_;
  static uint32 net_in_max_;
  static uint32 net_out_max_;

  static int auto_adjust_chart_max_;

  // Theme
  static COLORREF per_bar_background_color_, per_bar_highlight_color_;
  static COLORREF history_chart_line_color_;
  static COLORREF history_chart_background_color_;

  // Since we are contained by SysMonContentItem and will be destroyed
  // when SysMonContentItem is released. We did not AddRef here.
  SysMonContentItem *owner_;

  bool render_in_popout_view_;
};

// MonitorItem_CPU watches CPU performance data and renders it.
class MonitorItem_CPU : public MonitorItem {
 public:
  MonitorItem_CPU() : MonitorItem(), cpu_time_(0) {
  }

  HRESULT Init(SysMonContentItem *owner);
  HRESULT CollectData();
  HRESULT GetItemHeight(HDC hdc, long width, long *height);
  HRESULT GetItemDetailsHeight(HDC hdc, long width, long *height);
  HRESULT RenderItem(HDC hdc, const RECT *bounds);
  HRESULT RenderItemDetails(HDC hdc, const RECT *bounds);
  HRESULT GetMinimizedTitle(CString *title) const;

 private:
  void UpdateItem();

  CpuMonitor monitor_;
  int cpu_time_;
};

class MonitorItem_Mem : public MonitorItem {
 public:
  MonitorItem_Mem();

  HRESULT Init(SysMonContentItem *owner);
  HRESULT CollectData();
  HRESULT GetItemHeight(HDC hdc, long width, long *height);
  HRESULT GetItemDetailsHeight(HDC hdc, long width, long *height);
  HRESULT RenderItem(HDC hdc, const RECT *bounds);
  HRESULT RenderItemDetails(HDC hdc, const RECT *bounds);
  HRESULT GetMinimizedTitle(CString *title) const;

 private:
  void UpdateItem();

  uint64 mem_total_virtual_,
         mem_commited_virtual_,
         mem_total_physical_,
         mem_used_physical_;
};

#define PERF_SAMPLE_HISTORY_SIZE  100

class MonitorItem_Disk : public MonitorItem {
 public:
  MonitorItem_Disk()
    : MonitorItem(),
      disk_read_bytes_per_second_(0),
      disk_write_bytes_per_second_(0),
      last_read_bytes_(0),
      last_write_bytes_(0),
      degrade_counter_(0),
      read_history_(PERF_SAMPLE_HISTORY_SIZE),
      write_history_(PERF_SAMPLE_HISTORY_SIZE),
      total_history_(PERF_SAMPLE_HISTORY_SIZE) {
  }

  HRESULT Init(SysMonContentItem *owner);
  HRESULT CollectData();
  HRESULT GetItemHeight(HDC hdc, long width, long *height);
  HRESULT GetItemDetailsHeight(HDC hdc, long width, long *height);
  HRESULT RenderItem(HDC hdc, const RECT *bounds);
  HRESULT RenderItemDetails(HDC hdc, const RECT *bounds);
  HRESULT GetMinimizedTitle(CString *title) const;

 private:
  void UpdateItem();

  uint32 disk_read_bytes_per_second_, disk_write_bytes_per_second_;

  uint64 last_read_bytes_, last_write_bytes_;
  DWORD last_time_;

  CircularBuffer<uint32> read_history_;
  CircularBuffer<uint32> write_history_;
  CircularBuffer<uint32> total_history_;
  int degrade_counter_;
};

class MonitorItem_Net : public MonitorItem {
 public:
  MonitorItem_Net()
    : MonitorItem(),
      net_received_bytes_per_second_(0),
      net_sent_bytes_per_second_(0),
      degrade_counter_(0),
      stat_bytes_inited_(false),
      in_history_(PERF_SAMPLE_HISTORY_SIZE),
      out_history_(PERF_SAMPLE_HISTORY_SIZE),
      total_history_(PERF_SAMPLE_HISTORY_SIZE) {
  }

  HRESULT Init(SysMonContentItem *owner);
  HRESULT CollectData();
  HRESULT GetItemHeight(HDC hdc, long width, long *height);
  HRESULT GetItemDetailsHeight(HDC hdc, long width, long *height);
  HRESULT RenderItem(HDC hdc, const RECT *bounds);
  HRESULT RenderItemDetails(HDC hdc, const RECT *bounds);
  HRESULT GetMinimizedTitle(CString *title) const;

 private:
  void UpdateItem();

  uint32 net_received_bytes_per_second_, net_sent_bytes_per_second_;
  int degrade_counter_;

  bool stat_bytes_inited_;
  struct IfStat {
    DWORD if_index;
    DWORD in_bytes;
    DWORD out_bytes;
    DWORD stat_time;
  };
  CSimpleArray<IfStat> if_stat_;

  CircularBuffer<uint32> in_history_;
  CircularBuffer<uint32> out_history_;
  CircularBuffer<uint32> total_history_;
};

// MonItemClassFactory creates MonitorItem instances
template<class T>class MonItemClassFactory {
 public:
  static HRESULT CreateInstance(MonitorItem **monitor) {
    ATLASSERT(monitor);
    *monitor = (MonitorItem *)(new T());
    ATLASSERT(*monitor);
    return S_OK;
  }
};

#endif  // SYSMON_MONITOR_ITEM_H__
