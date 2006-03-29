// Copyright 2005 Google Inc
// All rights reserved
// 
// PropertyPage.cpp

#include "stdafx.h"
#include "PropertyPage.h"

// CCurrencyConversionSamplePluginPropertyPage implement very simple dialog
// box with 2 multiselection listboxes and Add/Remove buttons.
// On Apply/OK notification it serializes the 

LRESULT CCurrencyConversionSamplePluginPropertyPage::OnInitDialog(
  UINT, WPARAM, LPARAM, BOOL& bHandled) {
  bHandled = true;
  lbxKnown.Attach(GetDlgItem(IDC_KNOWN));
  lbxDisplay.Attach(GetDlgItem(IDC_LIST));
  // get the variables required to fill up the property page
  CComQIPtr<ICurrencyConversionSamplePlugin> plugin(m_ppUnk[0]);
  CComBSTR currencies;
  if (plugin == NULL) return 0;
  ATLVERIFY(SUCCEEDED(plugin->get_Currencies(&currencies)));
  CStringArray tokens;
  Currencies::Tokenize(CString(currencies), &tokens);
  size_t i = 0;
  for (i = 0; Currencies::knownCurrencies[i] != NULL; i++) {
    lbxKnown.AddString(Currencies::knownCurrencies[i]); 
  }
  for (i = 0; i < tokens.GetCount(); i+=2) {
    CString s = tokens.GetAt(i);
    lbxDisplay.AddString(s); 
    int k = lbxKnown.FindString(s);
    if (k >= 0) lbxKnown.DeleteItem(k);
  }
  UpdateButtonsState();
  return 0;
}

// This method is called by the helper code when user presses OK button

STDMETHODIMP CCurrencyConversionSamplePluginPropertyPage::Apply() {
  CString csv; // coma separated values
  int n = lbxDisplay.GetItemCount();
  for (int i = 0; i < n; i++) {
    int len = lbxDisplay.GetItemTextLen(i);
    if (len > 0) {
      csv += lbxDisplay.GetItemText(i);
      csv += i < n - 1 ? L",0.0," : L",0.0";
    }
  }
  CComBSTR currencies = csv;
  // get the data entered by the user
  for (UINT i = 0; i < m_nObjects; i++) {
    CComQIPtr<ICurrencyConversionSamplePlugin> plugin(m_ppUnk[i]);
    if (plugin != NULL)
      ATLVERIFY(SUCCEEDED(plugin->put_Currencies(currencies)));
  }
  m_bDirty = FALSE;
  SetDirty(TRUE);
  return S_OK;
}

// move the elements from the "from" list to the "to" list

static void MoveItems(CListBox& from, CListBox& to) {
  CIntArray selected;
  int n = from.GetSelectedItems(&selected);
  for (int i = n - 1; i >= 0; i--) {
    int item = selected.GetAt(i);
    CString s = from.GetItemText(item);
    from.DeleteItem(item);
    int k = to.FindString(s);
    if (k < 0) {
      to.AddString(s);
      k = to.FindString(s);
    }
    ATLASSERT(k >= 0);
    to.SelectItemRange(k, k);
  }
}
  
// Updtaes state of Add/Remove buttons according to the selections

void CCurrencyConversionSamplePluginPropertyPage::UpdateButtonsState() {
  GetDlgItem(IDC_ADD).EnableWindow(lbxKnown.GetSelectedCount() > 0);
  GetDlgItem(IDC_REMOVE).EnableWindow(lbxDisplay.GetSelectedCount() > 0);
  CString acode;
  int anchor = -1;
  if (GetFocus() == lbxKnown && lbxKnown.GetItemCount() > 0 && 
      (anchor = lbxKnown.GetAnchorIndex()) >= 0) {
    acode = lbxKnown.GetItemText(anchor);
  } else if (GetFocus() == lbxDisplay && lbxDisplay.GetItemCount() > 0 && 
      (anchor = lbxDisplay.GetAnchorIndex()) >= 0) {
    acode = lbxDisplay.GetItemText(anchor);
  }
  CString status;
  if (acode.GetLength() > 0) {
    status = Currencies::GetCurrencyName(acode);
    status += _T(" - currency of ");
    status += Currencies::GetCountries(acode);
  }
  else {
    status = _T("Use Shift/Ctrl + click to select multiple currencies ") 
        _T(" you are interested in displaying...");
  }
  GetDlgItem(IDC_STATUS).SetWindowText(status);
}

// this method is called when user presses Add button

LRESULT CCurrencyConversionSamplePluginPropertyPage::OnAdd(WORD, WORD, HWND, 
    BOOL& bHandled) {
  bHandled = true;
  MoveItems(lbxKnown, lbxDisplay);
  UpdateButtonsState();
  return 0;
}

// this method is called when user presses Remove button

LRESULT CCurrencyConversionSamplePluginPropertyPage::OnRemove(WORD, WORD, HWND, 
    BOOL& bHandled) {
  bHandled = true;
  MoveItems(lbxDisplay, lbxKnown);
  UpdateButtonsState();
  return 0;
}

// this method is called when selection is changed in any of two listboxes

LRESULT CCurrencyConversionSamplePluginPropertyPage::OnSelectionChange(WORD, 
    WORD, HWND, BOOL& bHandled) {
  bHandled = true;
  UpdateButtonsState();
  return 0;
}

// this method is called when user double clicks on the item in either listbox

LRESULT CCurrencyConversionSamplePluginPropertyPage::OnListBoxDoubleClick(WORD, 
    WORD wID, HWND, BOOL& bHandled){
  bHandled = true;
  if (wID == IDC_KNOWN) OnAdd(0, 0, NULL, bHandled);
  else if (wID == IDC_LIST) OnRemove(0, 0, NULL, bHandled);
  return 0;
}
