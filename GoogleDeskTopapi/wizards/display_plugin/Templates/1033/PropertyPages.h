// PropertyPages.h : Declaration of the property pages

#ifndef PROPERTY_PAGES_H
#define PROPERTY_PAGES_H

#include "resource.h"       // main symbols

[!if USE_PROPERTY_PAGE1]
// C[!output PROJECT_NAME]PluginPropertyPage : Property Page

class ATL_NO_VTABLE C[!output PROJECT_NAME]PluginPropertyPage :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<C[!output PROJECT_NAME]PluginPropertyPage, &CLSID_[!output PROJECT_NAME]PluginPropertyPage>,
  public IPropertyPageImpl<C[!output PROJECT_NAME]PluginPropertyPage>,
  public CDialogImpl<C[!output PROJECT_NAME]PluginPropertyPage> {
public:
  C[!output PROJECT_NAME]PluginPropertyPage() {
    m_dwTitleID = IDS_PROPERTYPAGE_TITLE;
    m_dwHelpFileID = 0;
    m_dwDocStringID = 0;
  }

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct() {
    return S_OK;
  }
  
  void FinalRelease() {
  }

  enum {IDD = IDD_PROPERTYPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_PROPERTYPAGE_RGS)

BEGIN_COM_MAP(C[!output PROJECT_NAME]PluginPropertyPage) 
  COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(C[!output PROJECT_NAME]PluginPropertyPage)
  MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
  COMMAND_HANDLER(IDC_VALUE1, EN_CHANGE, OnValue1Change)
  CHAIN_MSG_MAP(IPropertyPageImpl<C[!output PROJECT_NAME]PluginPropertyPage>)
END_MSG_MAP()

  // message handlers
  LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnValue1Change(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

  STDMETHOD(Apply)(void);
};

[!endif]
[!if USE_PROPERTY_PAGE2]
// C[!output PROJECT_NAME]PluginPropertyPage2 : Property Page 2

class ATL_NO_VTABLE C[!output PROJECT_NAME]PluginPropertyPage2 :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<C[!output PROJECT_NAME]PluginPropertyPage2, &CLSID_[!output PROJECT_NAME]PluginPropertyPage2>,
  public IPropertyPageImpl<C[!output PROJECT_NAME]PluginPropertyPage2>,
  public CDialogImpl<C[!output PROJECT_NAME]PluginPropertyPage2> {
public:
  C[!output PROJECT_NAME]PluginPropertyPage2() {
    m_dwTitleID = IDS_PROPERTYPAGE2_TITLE;
    m_dwHelpFileID = 0;
    m_dwDocStringID = 0;
  }

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct() {
    return S_OK;
  }

  void FinalRelease() {
  }

  enum {IDD = IDD_PROPERTYPAGE2};

  DECLARE_REGISTRY_RESOURCEID(IDR_PROPERTYPAGE2_RGS)

  BEGIN_COM_MAP(C[!output PROJECT_NAME]PluginPropertyPage2) 
    COM_INTERFACE_ENTRY(IPropertyPage)
  END_COM_MAP()

  BEGIN_MSG_MAP(C[!output PROJECT_NAME]PluginPropertyPage2)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_HANDLER(IDC_VALUE2, EN_CHANGE, OnValue2Change)
    CHAIN_MSG_MAP(IPropertyPageImpl<C[!output PROJECT_NAME]PluginPropertyPage2>)
  END_MSG_MAP()

  // message handlers
  LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnValue2Change(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

  STDMETHOD(Apply)(void);
};

[!endif]
[!if USE_PROPERTY_PAGE3]
// C[!output PROJECT_NAME]PluginPropertyPage3 : Property Page 3

class ATL_NO_VTABLE C[!output PROJECT_NAME]PluginPropertyPage3 :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<C[!output PROJECT_NAME]PluginPropertyPage3, &CLSID_[!output PROJECT_NAME]PluginPropertyPage3>,
  public IPropertyPageImpl<C[!output PROJECT_NAME]PluginPropertyPage3>,
  public CDialogImpl<C[!output PROJECT_NAME]PluginPropertyPage3> {
public:
  C[!output PROJECT_NAME]PluginPropertyPage3() {
    m_dwTitleID = IDS_PROPERTYPAGE3_TITLE;
    m_dwHelpFileID = 0;
    m_dwDocStringID = 0;
  }

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct() {
    return S_OK;
  }

  void FinalRelease() {
  }

  enum {IDD = IDD_PROPERTYPAGE3};

  DECLARE_REGISTRY_RESOURCEID(IDR_PROPERTYPAGE3_RGS)

  BEGIN_COM_MAP(C[!output PROJECT_NAME]PluginPropertyPage3) 
    COM_INTERFACE_ENTRY(IPropertyPage)
  END_COM_MAP()

  BEGIN_MSG_MAP(C[!output PROJECT_NAME]PluginPropertyPage3)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_HANDLER(IDC_VALUE3, EN_CHANGE, OnValue3Change)
    CHAIN_MSG_MAP(IPropertyPageImpl<C[!output PROJECT_NAME]PluginPropertyPage3>)
  END_MSG_MAP()

  // message handlers
  LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnValue3Change(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

  STDMETHOD(Apply)(void);
};

[!endif]
[!if USE_PROPERTY_PAGE1]
OBJECT_ENTRY_AUTO(__uuidof([!output PROJECT_NAME]PluginPropertyPage), C[!output PROJECT_NAME]PluginPropertyPage)
[!endif]
[!if USE_PROPERTY_PAGE2]
OBJECT_ENTRY_AUTO(__uuidof([!output PROJECT_NAME]PluginPropertyPage2), C[!output PROJECT_NAME]PluginPropertyPage2)
[!endif]
[!if USE_PROPERTY_PAGE3]
OBJECT_ENTRY_AUTO(__uuidof([!output PROJECT_NAME]PluginPropertyPage3), C[!output PROJECT_NAME]PluginPropertyPage3)
[!endif]

#endif    // PROPERTY_PAGES_H
