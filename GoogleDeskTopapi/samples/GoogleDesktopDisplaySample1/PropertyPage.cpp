// PropertyPage.cpp : Implementation of CSamplePluginPropertyPage

#include "stdafx.h"
#include "PropertyPage.h"

// CSamplePluginPropertyPage

LRESULT CSamplePluginPropertyPage::OnInitDialog(
  UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  // get the variables required to fill up the property page
  ULONG item_start = 0;
  CComQIPtr<ISamplePlugin> plugin(m_ppUnk[0]);
  if (plugin != NULL)
    ATLVERIFY(SUCCEEDED(plugin->get_ItemStart(&item_start)));

  // now fill the property page
  SetDlgItemInt(IDC_ITEM_START, item_start, FALSE);

  SetDirty(FALSE);

  return 0;
}

LRESULT CSamplePluginPropertyPage::OnItemStartChange(
  WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
  // user has changed the value so set the dirty flag
  SetDirty(TRUE);
  return 0;
}

STDMETHODIMP CSamplePluginPropertyPage::Apply(void) {
  // get the data entered by the user
  ULONG item_start = GetDlgItemInt(IDC_ITEM_START, NULL, FALSE);

  // and pass it on to the objects
  for (UINT i = 0; i < m_nObjects; i++) {
    CComQIPtr<ISamplePlugin> plugin(m_ppUnk[i]);
    if (plugin != NULL)
      ATLVERIFY(SUCCEEDED(plugin->put_ItemStart(item_start)));
  }

  m_bDirty = FALSE;
  return S_OK;
}

