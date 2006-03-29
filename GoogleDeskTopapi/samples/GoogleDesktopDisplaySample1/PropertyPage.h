// PropertyPage.h : Declaration of the CSamplePluginPropertyPage

#ifndef SAMPLE_PLUGIN_PROPERTY_PAGE_H
#define SAMPLE_PLUGIN_PROPERTY_PAGE_H

#include "resource.h"       // main symbols
#include "GoogleDesktopDisplaySample1.h"

// CSamplePluginPropertyPage

class ATL_NO_VTABLE CSamplePluginPropertyPage :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CSamplePluginPropertyPage, &CLSID_SamplePluginPropertyPage>,
  public IPropertyPageImpl<CSamplePluginPropertyPage>,
  public CDialogImpl<CSamplePluginPropertyPage> {
public:
  CSamplePluginPropertyPage() {
    m_dwTitleID = IDS_TITLESamplePluginPropertyPage;
    m_dwHelpFileID = 0;
    m_dwDocStringID = 0;
  }

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct() {
    return S_OK;
  }
  
  void FinalRelease() {
  }

  enum {IDD = IDD_SAMPLEPLUGINPROPERTYPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_SAMPLEPLUGINPROPERTYPAGE)

BEGIN_COM_MAP(CSamplePluginPropertyPage) 
  COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CSamplePluginPropertyPage)
  MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
  COMMAND_HANDLER(IDC_ITEM_START, EN_CHANGE, OnItemStartChange)
  CHAIN_MSG_MAP(IPropertyPageImpl<CSamplePluginPropertyPage>)
END_MSG_MAP()

  LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnItemStartChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

  STDMETHOD(Apply)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(SamplePluginPropertyPage), CSamplePluginPropertyPage)

#endif    // SAMPLE_PLUGIN_PROPERTY_PAGE_H
