// PropertyPage.cpp : Implementation of C[!output PROJECT_NAME]PluginPropertyPage

#include "stdafx.h"
#include "PropertyPages.h"

[!if USE_PROPERTY_PAGE1]
// C[!output PROJECT_NAME]PluginPropertyPage

LRESULT C[!output PROJECT_NAME]PluginPropertyPage::OnInitDialog(
  UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  // get the variables required to fill up the property page
  LONG value = 0;
  CComQIPtr<I[!output PROJECT_NAME]Plugin> plugin(m_ppUnk[0]);
  if (plugin != NULL)
    ATLVERIFY(SUCCEEDED(plugin->get_Value1(&value)));

  // now fill the property page
  SetDlgItemInt(IDC_VALUE1, value, TRUE);

  SetDirty(FALSE);

  return 0;
}

LRESULT C[!output PROJECT_NAME]PluginPropertyPage::OnValue1Change(
  WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
  // user has changed the value so set the dirty flag
  SetDirty(TRUE);
  return 0;
}

STDMETHODIMP C[!output PROJECT_NAME]PluginPropertyPage::Apply(void) {
  // get the data entered by the user
  LONG value = GetDlgItemInt(IDC_VALUE1, NULL, TRUE);

  // and pass it on to the objects
  for (UINT i = 0; i < m_nObjects; i++) {
    CComQIPtr<I[!output PROJECT_NAME]Plugin> plugin(m_ppUnk[i]);
    if (plugin != NULL)
      ATLVERIFY(SUCCEEDED(plugin->put_Value1(value)));
  }

  m_bDirty = FALSE;
  return S_OK;
}

[!endif]
[!if USE_PROPERTY_PAGE2]
// C[!output PROJECT_NAME]PluginPropertyPage2

LRESULT C[!output PROJECT_NAME]PluginPropertyPage2::OnInitDialog(
  UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  // get the variables required to fill up the property page
  LONG value = 0;
  CComQIPtr<I[!output PROJECT_NAME]Plugin> plugin(m_ppUnk[0]);
  if (plugin != NULL)
    ATLVERIFY(SUCCEEDED(plugin->get_Value2(&value)));

  // now fill the property page
  SetDlgItemInt(IDC_VALUE2, value, TRUE);

  SetDirty(FALSE);

  return 0;
}

LRESULT C[!output PROJECT_NAME]PluginPropertyPage2::OnValue2Change(
  WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
  // user has changed the value so set the dirty flag
  SetDirty(TRUE);
  return 0;
}

STDMETHODIMP C[!output PROJECT_NAME]PluginPropertyPage2::Apply(void) {
  // get the data entered by the user
  LONG value = GetDlgItemInt(IDC_VALUE2, NULL, TRUE);

  // and pass it on to the objects
  for (UINT i = 0; i < m_nObjects; i++) {
    CComQIPtr<I[!output PROJECT_NAME]Plugin> plugin(m_ppUnk[i]);
    if (plugin != NULL)
      ATLVERIFY(SUCCEEDED(plugin->put_Value2(value)));
  }

  m_bDirty = FALSE;
  return S_OK;
}

[!endif]
[!if USE_PROPERTY_PAGE3]
// C[!output PROJECT_NAME]PluginPropertyPage3

LRESULT C[!output PROJECT_NAME]PluginPropertyPage3::OnInitDialog(
  UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
  // get the variables required to fill up the property page
  LONG value = 0;
  CComQIPtr<I[!output PROJECT_NAME]Plugin> plugin(m_ppUnk[0]);
  if (plugin != NULL)
    ATLVERIFY(SUCCEEDED(plugin->get_Value3(&value)));

  // now fill the property page
  SetDlgItemInt(IDC_VALUE3, value, TRUE);

  SetDirty(FALSE);

  return 0;
}

LRESULT C[!output PROJECT_NAME]PluginPropertyPage3::OnValue3Change(
  WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled) {
  // user has changed the value so set the dirty flag
  SetDirty(TRUE);
  return 0;
}

STDMETHODIMP C[!output PROJECT_NAME]PluginPropertyPage3::Apply(void) {
  // get the data entered by the user
  LONG value = GetDlgItemInt(IDC_VALUE3, NULL, TRUE);

  // and pass it on to the objects
  for (UINT i = 0; i < m_nObjects; i++) {
    CComQIPtr<I[!output PROJECT_NAME]Plugin> plugin(m_ppUnk[i]);
    if (plugin != NULL)
      ATLVERIFY(SUCCEEDED(plugin->put_Value3(value)));
  }

  m_bDirty = FALSE;
  return S_OK;
}

[!endif]
