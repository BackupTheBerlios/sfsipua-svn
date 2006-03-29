// Copyright 2005 Google Inc. All Rights Reserved.
//
// sysmon_proppage.h : Declaration of the SysMonPluginPropPage
//
// SysMonPluginPropPage provides a simple property page to
// allow user change the SysMonPlugin refresh interval and select
// interested performance monitors.

#ifndef SYSMON_PROPPAGE_H__
#define SYSMON_PROPPAGE_H__

#include "GoogleDesktopDisplaySysMonSample.h"
#include "resource.h"

// SysMonPluginPropPage provides property page for setting the refresh
// interval of SysMonPlugin
class ATL_NO_VTABLE SysMonPluginPropPage :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<SysMonPluginPropPage, &CLSID_SysMonPluginPropPage>,
  public IPropertyPageImpl<SysMonPluginPropPage>,
  public CDialogImpl<SysMonPluginPropPage> {
 public:
  SysMonPluginPropPage() {
    m_dwTitleID = IDS_TITLESysMonPluginPropPage;
    m_dwHelpFileID = IDS_HELPFILESysMonPluginPropPage;
    m_dwDocStringID = IDS_DOCSTRINGSysMonPluginPropPage;
  }

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct() {
    return S_OK;
  }

  void FinalRelease() {
  }

  enum { IDD = IDD_SYSMONPLUGINPROPPAGE };

  DECLARE_REGISTRY_RESOURCEID(IDR_SYSMONPLUGINPROPPAGE)

  DECLARE_NOT_AGGREGATABLE(SysMonPluginPropPage)

  BEGIN_COM_MAP(SysMonPluginPropPage)
    COM_INTERFACE_ENTRY(IPropertyPage)
  END_COM_MAP()

  BEGIN_MSG_MAP(SysMonPluginPropPage)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_HANDLER(IDC_EDIT_REFRESH_INTERVAL,
                    EN_CHANGE, OnEnChangeEditRefreshInterval)
    COMMAND_HANDLER(IDC_EDIT_MAX_DISK_RW,
                    EN_CHANGE, OnEnChangeEditRefreshInterval)
    COMMAND_HANDLER(IDC_EDIT_MAX_NET_IO,
                    EN_CHANGE, OnEnChangeEditRefreshInterval)
    COMMAND_HANDLER(IDC_EDIT_REFRESH_INTERVAL,
                    EN_KILLFOCUS, OnEnValidateRefreshInterval)
    COMMAND_HANDLER(IDC_EDIT_MAX_DISK_RW,
                    EN_KILLFOCUS, OnEnValidateDiskChartMax)
    COMMAND_HANDLER(IDC_EDIT_MAX_NET_IO,
                    EN_KILLFOCUS, OnEnValidateNetChartMax)
    COMMAND_HANDLER(IDC_CHECK_CPU,
                    BN_CLICKED, OnClickCheckActiveMonitors)
    COMMAND_HANDLER(IDC_CHECK_MEM,
                    BN_CLICKED, OnClickCheckActiveMonitors)
    COMMAND_HANDLER(IDC_CHECK_DISK,
                    BN_CLICKED, OnClickCheckActiveMonitors)
    COMMAND_HANDLER(IDC_CHECK_NET,
                    BN_CLICKED, OnClickCheckActiveMonitors)
    COMMAND_HANDLER(IDC_CHECK_AUTO_MAX,
                    BN_CLICKED, OnClickAutoAdjustChartMax)
    CHAIN_MSG_MAP(IPropertyPageImpl<SysMonPluginPropPage>)
  END_MSG_MAP()

  LRESULT OnInitDialog(UINT msg, WPARAM w, LPARAM l, BOOL &bHandled);
  LRESULT OnEnChangeEditRefreshInterval(WORD, WORD, HWND, BOOL&);
  LRESULT OnClickCheckActiveMonitors(WORD, WORD, HWND, BOOL&);
  LRESULT OnEnValidateRefreshInterval(WORD, WORD, HWND, BOOL&);
  LRESULT OnEnValidateDiskChartMax(WORD, WORD, HWND, BOOL&);
  LRESULT OnEnValidateNetChartMax(WORD, WORD, HWND, BOOL&);
  LRESULT OnClickAutoAdjustChartMax(WORD, WORD, HWND, BOOL&);

  STDMETHOD(Apply)(void);
};


OBJECT_ENTRY_AUTO(__uuidof(SysMonPluginPropPage), SysMonPluginPropPage)
#endif  // SYSMON_PROPPAGE_H__
