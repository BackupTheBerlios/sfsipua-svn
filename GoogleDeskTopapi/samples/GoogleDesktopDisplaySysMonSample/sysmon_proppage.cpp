// Copyright 2005 Google Inc. All Rights Reserved.
//
// sysmon_proppage.cpp : Implementation of SysMonPluginPropPage
#include "stdafx.h"

#include "sysmon_plugin.h"  // For default value constants only
#include "sysmon_proppage.h"

// SysMonPluginPropPage
LRESULT SysMonPluginPropPage::OnInitDialog(
    UINT msg, WPARAM w, LPARAM l, BOOL &bHandled) {
  int refresh_interval = 1;
  int active_monitors = ACTIVE_MON_CPU |
                        ACTIVE_MON_MEM |
                        ACTIVE_MON_DISK |
                        ACTIVE_MON_NET;
  int max_disk_rw = kDefaultMaxDiskRWInChart;
  int max_net_io = kDefaultMaxNetIOInChart;
  int auto_adjust_chart_max = kDefaultAutoAdjustChartMax;

  CComQIPtr<IGoogleDesktopSysMonPlugin> plugin(m_ppUnk[0]);
  if (plugin) {
    ATLVERIFY(SUCCEEDED(plugin->get_refresh_interval(&refresh_interval)));
    ATLVERIFY(SUCCEEDED(plugin->get_active_monitors(&active_monitors)));
    ATLVERIFY(SUCCEEDED(plugin->get_max_disk_rw_in_chart(&max_disk_rw)));
    ATLVERIFY(SUCCEEDED(plugin->get_max_net_io_in_chart(&max_net_io)));
    ATLVERIFY(SUCCEEDED(plugin->get_auto_adjust_chart_max(&auto_adjust_chart_max)));
  }

  SetDlgItemInt(IDC_EDIT_REFRESH_INTERVAL, refresh_interval, FALSE);
  SetDlgItemInt(IDC_EDIT_MAX_DISK_RW, max_disk_rw, FALSE);
  SetDlgItemInt(IDC_EDIT_MAX_NET_IO, max_net_io, FALSE);

  if (active_monitors & ACTIVE_MON_CPU)
    ::SendMessage(GetDlgItem(IDC_CHECK_CPU), BM_SETCHECK, BST_CHECKED, 0);
  if (active_monitors & ACTIVE_MON_MEM)
    ::SendMessage(GetDlgItem(IDC_CHECK_MEM), BM_SETCHECK, BST_CHECKED, 0);
  if (active_monitors & ACTIVE_MON_DISK)
    ::SendMessage(GetDlgItem(IDC_CHECK_DISK), BM_SETCHECK, BST_CHECKED, 0);
  if (active_monitors & ACTIVE_MON_NET)
    ::SendMessage(GetDlgItem(IDC_CHECK_NET), BM_SETCHECK, BST_CHECKED, 0);

  if (auto_adjust_chart_max) {
    ::SendMessage(GetDlgItem(IDC_CHECK_AUTO_MAX), BM_SETCHECK, BST_CHECKED, 0);
  }

  ::EnableWindow(GetDlgItem(IDC_EDIT_MAX_DISK_RW), !auto_adjust_chart_max);
  ::EnableWindow(GetDlgItem(IDC_EDIT_MAX_NET_IO), !auto_adjust_chart_max);

  SetDirty(FALSE);
  return 0;
}

LRESULT SysMonPluginPropPage::OnEnChangeEditRefreshInterval(
    WORD, WORD, HWND , BOOL&) {
  SetDirty(TRUE);
  return 0;
}

LRESULT SysMonPluginPropPage::OnClickCheckActiveMonitors(
    WORD, WORD, HWND, BOOL&) {
  SetDirty(TRUE);
  return 0;
}

LRESULT SysMonPluginPropPage::OnClickAutoAdjustChartMax(
    WORD, WORD, HWND, BOOL&) {
  SetDirty(TRUE);

  int  auto_adjust_chart_max = (::SendMessage(GetDlgItem(IDC_CHECK_AUTO_MAX),
                                  BM_GETCHECK, 0, 0) == BST_CHECKED);

  ::EnableWindow(GetDlgItem(IDC_EDIT_MAX_DISK_RW), !auto_adjust_chart_max);
  ::EnableWindow(GetDlgItem(IDC_EDIT_MAX_NET_IO), !auto_adjust_chart_max);

  return 0;
}

LRESULT SysMonPluginPropPage::OnEnValidateRefreshInterval(
    WORD, WORD, HWND, BOOL&) {
  int refresh_interval = GetDlgItemInt(IDC_EDIT_REFRESH_INTERVAL, NULL, 0);
  if (!refresh_interval) {
    CString caption, message;
    caption.LoadString(IDS_ERROR_MESSAGE_CAPTION);
    message.LoadString(IDS_ERROR_REFRESH_INTERVAL_CANNT_BE_ZERO);
    MessageBox(message, caption, MB_OK + MB_ICONSTOP);
    ::SetFocus(GetDlgItem(IDC_EDIT_REFRESH_INTERVAL));
  }

  return 0;
}

LRESULT SysMonPluginPropPage::OnEnValidateDiskChartMax(
    WORD, WORD, HWND, BOOL&) {
  int max_disk_rw = GetDlgItemInt(IDC_EDIT_MAX_DISK_RW, NULL, 0);

  if (!max_disk_rw) {
    CString caption, message;
    caption.LoadString(IDS_ERROR_MESSAGE_CAPTION);
    message.LoadString(IDS_ERROR_DISK_CHART_MAX_CANNT_BE_ZERO);
    MessageBox(message, caption, MB_OK + MB_ICONSTOP);
    ::SetFocus(GetDlgItem(IDC_EDIT_MAX_DISK_RW));
  } 
  
  return 0;
}

LRESULT SysMonPluginPropPage::OnEnValidateNetChartMax(
    WORD, WORD, HWND, BOOL&) {
  int max_net_io = GetDlgItemInt(IDC_EDIT_MAX_NET_IO, NULL, 0);

  if (!max_net_io) {
    CString caption, message;
    caption.LoadString(IDS_ERROR_MESSAGE_CAPTION);
    message.LoadString(IDS_ERROR_NETWORK_CHART_MAX_CANNT_BE_ZERO);
    MessageBox(message, caption, MB_OK + MB_ICONSTOP);
    ::SetFocus(GetDlgItem(IDC_EDIT_MAX_NET_IO));
  }

  return 0;
}

STDMETHODIMP SysMonPluginPropPage::Apply(void) {
  int refresh_interval = GetDlgItemInt(IDC_EDIT_REFRESH_INTERVAL, NULL, 0);
  int max_disk_rw = GetDlgItemInt(IDC_EDIT_MAX_DISK_RW, NULL, 0);
  int max_net_io = GetDlgItemInt(IDC_EDIT_MAX_NET_IO, NULL, 0);
  int active_monitors = 0;
  int auto_adjust_chart_max = 1;

  if (!refresh_interval) {
    refresh_interval = 1;   // Minimum 1 seconds
  }
  if (!max_disk_rw) {
    max_disk_rw = 50000;
  }
  if (!max_net_io) {
    max_net_io = 50000;
  }

  if (::SendMessage(GetDlgItem(IDC_CHECK_CPU),
                               BM_GETCHECK, 0, 0) == BST_CHECKED) {
    active_monitors |= ACTIVE_MON_CPU;
  }
  if (::SendMessage(GetDlgItem(IDC_CHECK_MEM),
                               BM_GETCHECK, 0, 0) == BST_CHECKED) {
    active_monitors |= ACTIVE_MON_MEM;
  }
  if (::SendMessage(GetDlgItem(IDC_CHECK_DISK),
                               BM_GETCHECK, 0, 0) == BST_CHECKED) {
    active_monitors |= ACTIVE_MON_DISK;
  }
  if (::SendMessage(GetDlgItem(IDC_CHECK_NET),
                               BM_GETCHECK, 0, 0) == BST_CHECKED) {
    active_monitors |= ACTIVE_MON_NET;
  }

  auto_adjust_chart_max = (::SendMessage(GetDlgItem(IDC_CHECK_AUTO_MAX),
    BM_GETCHECK, 0, 0) == BST_CHECKED);

  for (int i = 0; i < static_cast<int>(m_nObjects); ++i) {
    CComQIPtr<IGoogleDesktopSysMonPlugin> plugin(m_ppUnk[i]);
    if (plugin) {
      ATLVERIFY(SUCCEEDED(plugin->put_refresh_interval(refresh_interval)));
      ATLVERIFY(SUCCEEDED(plugin->put_active_monitors(active_monitors)));
      ATLVERIFY(SUCCEEDED(plugin->put_max_disk_rw_in_chart(max_disk_rw)));
      ATLVERIFY(SUCCEEDED(plugin->put_max_net_io_in_chart(max_net_io)));
      ATLVERIFY(SUCCEEDED(plugin->put_auto_adjust_chart_max(
        auto_adjust_chart_max)));
    }
  }
  m_bDirty = FALSE;
  return S_OK;
}
