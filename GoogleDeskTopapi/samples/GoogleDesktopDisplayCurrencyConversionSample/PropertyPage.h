// Copyright 2005 Google Inc
// All rights reserved
// 
// PropertyPage.h : Declaration of the CCurrencyConversionSamplePluginPropertyPage

#ifndef SAMPLE_PLUGIN_PROPERTY_PAGE_H
#define SAMPLE_PLUGIN_PROPERTY_PAGE_H

#include "resource.h"       // main symbols
#include "Plugin.h"

#include "currencies.h"
#include "listbox.h"

// CCurrencyConversionSamplePluginPropertyPage

class ATL_NO_VTABLE CCurrencyConversionSamplePluginPropertyPage :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CCurrencyConversionSamplePluginPropertyPage, 
      &CLSID_CurrencyConversionSamplePropertyPage>,
  public IPropertyPageImpl<CCurrencyConversionSamplePluginPropertyPage>,
  public CDialogImpl<CCurrencyConversionSamplePluginPropertyPage> {
public:
  CCurrencyConversionSamplePluginPropertyPage() {
    m_dwTitleID = IDS_TITLECURRENCYCONVERSIONSAMPLEPLUGINPROPERTYPAGE;
    m_dwHelpFileID = 0;
    m_dwDocStringID = 0;
  }

  DECLARE_PROTECT_FINAL_CONSTRUCT()


  HRESULT FinalConstruct() { return S_OK; }
  
  void FinalRelease() { }

  enum {IDD = IDD_CURRENCYCONVERSIONSAMPLEPLUGINPROPERTYPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_CURRENCYCONVERSIONSAMPLEPLUGINPROPERTYPAGE)

BEGIN_COM_MAP(CCurrencyConversionSamplePluginPropertyPage) 
  COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CCurrencyConversionSamplePluginPropertyPage)
  MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
  COMMAND_HANDLER(IDC_ADD, BN_CLICKED, OnAdd)
  COMMAND_HANDLER(IDC_REMOVE, BN_CLICKED, OnRemove)
  COMMAND_HANDLER(IDC_LIST, LBN_SELCHANGE, OnSelectionChange)
  COMMAND_HANDLER(IDC_KNOWN, LBN_SELCHANGE, OnSelectionChange)
  COMMAND_HANDLER(IDC_KNOWN, LBN_DBLCLK, OnListBoxDoubleClick)
  COMMAND_HANDLER(IDC_LIST, LBN_DBLCLK, OnListBoxDoubleClick)
  CHAIN_MSG_MAP(IPropertyPageImpl<CCurrencyConversionSamplePluginPropertyPage>)
END_MSG_MAP()

private:
  LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

  STDMETHOD(Apply)();
  LRESULT OnAdd(WORD, WORD, HWND, BOOL&);
  LRESULT OnRemove(WORD, WORD, HWND, BOOL&);
  LRESULT OnSelectionChange(WORD, WORD, HWND, BOOL&);
  void UpdateButtonsState();

  CListBox lbxKnown;
  CListBox lbxDisplay;

public:
  LRESULT OnListBoxDoubleClick(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  };

OBJECT_ENTRY_AUTO(__uuidof(CurrencyConversionSamplePropertyPage), 
    CCurrencyConversionSamplePluginPropertyPage)

#endif    // SAMPLE_PLUGIN_PROPERTY_PAGE_H
