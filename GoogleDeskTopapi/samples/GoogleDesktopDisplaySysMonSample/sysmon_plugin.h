// Copyright 2005 Google Inc. All Rights Reserved.
//
// SysMonPlugin.h : Declaration of the SysMonPlugin
//
// SysMonPlugin is an in-place windowless ActiveX control plugin
// for Google Desktop Sidebar. It captures the system performance
// data at given interval and shows it to user.
//
// The periodically system performance gathering is driven by
// WM_TIMER messsage. PluginMsgOnlyWindow is the message only
// window that is used to provide this timer message and trigger
// SysMonPlugin to fetch data and refresh its UI.

#ifndef SYSMON_PLUGIN_H__
#define SYSMON_PLUGIN_H__

#include "../common/GoogleDesktopDisplayAPI.h"

#include "Resource.h"
#include "GoogleDesktopDisplaySysMonSample.h"

// These constants are share:
// In SysMonPlugin for the property defaults;
// In SysMonPluginPropPage for default variable initialization;
// In MonitorItem for default chart scale;
const int kDefaultMaxDiskRWInChart = 100000;
const int kDefaultMaxNetIOInChart = 100000;
const int kDefaultAutoAdjustChartMax = 1;

// MsgOnlyWindowForTimers is for WM_TIMER message and trigger
// performance data gathering. It is here because SysMonPlugin could
// be windowless.
//
// The only instance of this calss would be msg_wnd_ in SysMonPlugin.
class MsgOnlyWindowForTimers
  : public CWindowImpl<MsgOnlyWindowForTimers> {
 public:
  // Init will create the underlying window and setup a timer
  // according to the value of owner_'s referesh_interval_
  int Init(SysMonPlugin *pOwner);

  // Uninit will clear the timer and destroy the underlying window
  void Uninit();

  // Resets the timer to the given interval
  int SetRefreshInterval(int interval);    // ms

  // message map
  BEGIN_MSG_MAP(CSamplePluginMsgOnlyWindow)
    MESSAGE_HANDLER(WM_TIMER, OnTimer);
  END_MSG_MAP()

  LRESULT OnTimer(UINT, WPARAM, LPARAM, BOOL&);
 private:
  SysMonPlugin *owner_;
};

// SysMonPlugin implements a system performance monitor plugin for
// Google Desktop Sidebar.
// The purpose of this class is to demonstrate how to make an ActiveX
// control that can be hosted by the Sidebar.
class ATL_NO_VTABLE SysMonPlugin :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<SysMonPlugin, &CLSID_SysMonPlugin>,
  public IObjectWithSiteImpl<SysMonPlugin>,
  public IPersistStreamInitImpl<SysMonPlugin>,
  public ISpecifyPropertyPagesImpl<SysMonPlugin>,
  public IGoogleDesktopDisplayPluginHandler,
  public IDispatchImpl<IGoogleDesktopSysMonPlugin,
    &IID_IGoogleDesktopSysMonPlugin,
    &LIBID_GoogleDesktopDisplaySysMonSampleLib,
    /*wMajor =*/ 1, /*wMinor =*/ 0> {
  friend class MsgOnlyWindowForTimers;
 public:
  SysMonPlugin()
    : caption_font_(NULL),
      text_font_(NULL),
      hot_item_index_(0),
      popout_stat_(false) {
  }

  DECLARE_REGISTRY_RESOURCEID(IDR_SYSMONPLUGIN)

  BEGIN_COM_MAP(SysMonPlugin)
    COM_INTERFACE_ENTRY(IGoogleDesktopSysMonPlugin)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IPersistStreamInit)
    COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
    COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
    COM_INTERFACE_ENTRY(IObjectWithSite)
    COM_INTERFACE_ENTRY(IGoogleDesktopDisplayPluginHandler)

    // the next statement makes the plugin to be aggregated from the
    // 'PluginHelper' object that is exposed by the sidebar. The variable
    // helper_ will hold the helper object.
    COM_INTERFACE_ENTRY_AUTOAGGREGATE_BLIND(helper_.p,
      CLSID_GoogleDesktopDisplayPluginHelper)
  END_COM_MAP()

  BEGIN_PROP_MAP(SysMonPlugin)
    PROP_DATA_ENTRY("refresh_interval", refresh_interval_, VT_UI4)
    PROP_DATA_ENTRY("active_monitors", active_monitors_, VT_UI4)
    // property pages, used by ISpecifyPropertyPagesImpl
    PROP_PAGE(CLSID_SysMonPluginPropPage)
  END_PROP_MAP()

  DECLARE_GET_CONTROLLING_UNKNOWN()
  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct();
  void FinalRelease();

  STDMETHOD(get_refresh_interval)(int *interval);
  STDMETHOD(put_refresh_interval)(int new_interval);

  STDMETHOD(get_active_monitors)(int *monitors);
  STDMETHOD(put_active_monitors)(int new_monitors);

  STDMETHOD(get_max_disk_rw_in_chart)(int *max_disk_rw);
  STDMETHOD(put_max_disk_rw_in_chart)(int max_disk_rw);

  STDMETHOD(get_max_net_io_in_chart)(int *max_net_io);
  STDMETHOD(put_max_net_io_in_chart)(int max_net_io);

  STDMETHOD(get_auto_adjust_chart_max)(int *auto_adjust_chart_max);
  STDMETHOD(put_auto_adjust_chart_max)(int auto_adjust_chart_max);

  // IPersistStreamInit
  STDMETHOD(InitNew)();
  STDMETHOD(Load)(IStream *stream);
  STDMETHOD(Save)(IN OUT IStream *stream, IN BOOL clear_dirty);

  // IObjectWithSite
  STDMETHOD(SetSite)(IUnknown* site);

   // IGoogleDesktopSidebarPlugin
  STDMETHOD(OnCommand)(GoogleDesktopDisplayPluginCommand command);
  STDMETHOD(OnDisplayStateChange)(
    GoogleDesktopDisplayTileDisplayState display_state);
  STDMETHOD(GetInfo)(GoogleDesktopDisplayTileInfo *tile_info);

  void SetDirty(BOOL is_dirty) {
    m_bRequiresSave = is_dirty;
  }

  BOOL m_bRequiresSave;   // For IPersistStreamInitImpl

  bool get_popout_stat() const {
    return popout_stat_;
  }

 private:
  // one time init function
  HRESULT StartDisplayingItems();

  // Syncs the content item (active monitor display) with active_monitors.
  // (first time or from property page)
  void ChangeItems();

  // Updates the plugin title.
  void UpdateTitle();

  // Triggers collection of performance data.
  void RefreshPerfSamples();

  // Heartbeating...
  LRESULT TimerCallback(UINT timer_id);

  // Enumeration callback.
  //   Returns 0 to continue; Returns 1 to stop enumeration;
  typedef int (*EnumContentItemCallback)(SysMonPlugin *self, IUnknown *item);

  // Enumerates every monitor item.
  void EnumContentItem(EnumContentItemCallback callback);

  static int NotifyPerfSample(SysMonPlugin *self, IUnknown *item);
  static int NotifyFont(SysMonPlugin *self, IUnknown *item);
  static int NotifyChartScale(SysMonPlugin *self, IUnknown *item);
  static int NotifyChartAutoMax(SysMonPlugin *self, IUnknown *item);

  int active_monitors_;
  int refresh_interval_;  // in seconds
  int max_disk_rw_in_chart_; // in bytes/s
  int max_net_io_in_chart_;  // in bytes/s
  int auto_adjust_chart_max_;

  HFONT caption_font_, text_font_;

  CComPtr<IUnknown> helper_;

  MsgOnlyWindowForTimers msg_wnd_;

  bool popout_stat_;  // true for pop out view and false for in sidebar

  // Current minimized title item index
  int hot_item_index_;
};

OBJECT_ENTRY_AUTO(__uuidof(SysMonPlugin), SysMonPlugin)

#endif  // SYSMON_PLUGIN_H__
