// Copyright 2004-2005 Google Inc
// All Rights Reserved
// 
// Sample crawler capture component. This component registers for .lnk files
// 

#include "stdafx.h"
#include <atlstr.h>
#include <atlsafe.h>
#include <shobjidl.h>
#include <shlguid.h>
#include "IndexShortcut.h"
#include "../common/GoogleDesktopAPI.h"

// CIndexShortcut

STDMETHODIMP CIndexShortcut::InterfaceSupportsErrorInfo(REFIID riid)
{
  static const IID* arr[] = 
  {
    &IID_IIndexShortcut
  };

  for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
  {
    if (InlineIsEqualGUID(*arr[i],riid))
      return S_OK;
  }
  return S_FALSE;
}

STDMETHODIMP CIndexShortcut::HandleFile(BSTR full_path_to_file, IDispatch *event_factory) {
  CComPtr<IGoogleDesktopEventFactory> spEventFactory;
  CComPtr<IDispatch> spEventDisp;  
  HRESULT hr;
  
  hr  = event_factory->QueryInterface(&spEventFactory);
  if (FAILED(hr))
    return Error(L"No event factory", IID_IIndexShortcut, hr);

  hr = spEventFactory->CreateEvent(CComBSTR(CLSID_IndexShortcut), CComBSTR(L"Google.Desktop.File"), &spEventDisp);
  if (FAILED(hr))
    return Error(L"Unable to create event", IID_IIndexShortcut, hr);
    
  CComQIPtr<IGoogleDesktopEvent> spEvent(spEventDisp);
  
  ATLASSERT(spEventDisp && spEvent);
  if (spEvent == NULL)
    return Error(L"Event does not implement IGoogleDesktopEvent", IID_IIndexShortcut, E_UNEXPECTED);

  // create the link object    
  CComPtr<IShellLink> spLink;    
  hr = spLink.CoCreateInstance(CLSID_ShellLink);
  if (FAILED(hr))
    return Error(L"Unable to create shell link", IID_IIndexShortcut, hr);

  CComPtr<IPersistFile> spLinkPersistFile;
  
  hr = spLink.QueryInterface(&spLinkPersistFile);
  if (FAILED(hr))
    return Error(L"Shell link does not implement IPersistFile", IID_IIndexShortcut, hr);
  
  // and load it
  hr = spLinkPersistFile->Load(full_path_to_file, STGM_READ);
  if (FAILED(hr))
    return Error(L"Invalid shortcut file", IID_IIndexShortcut, hr);
    
  CStringW strOriginal;
  
  // get the file pointed to by the link
  hr = spLink->GetPath(CStrBufW(strOriginal, 1024), 1024, NULL, 0);
  if (SUCCEEDED(hr)) {
    WIN32_FIND_DATA wfd;
    if (!GetFileAttributesEx(strOriginal, GetFileExInfoStandard, &wfd))
      return HRESULT_FROM_WIN32(::GetLastError());

    SYSTEMTIME systemTime;
    FileTimeToSystemTime(&wfd.ftCreationTime, &systemTime);

    // convert the date to the variant format
    double varDate;
    SystemTimeToVariantTime(&systemTime, &varDate);
    
    hr = spEvent->AddProperty(CComBSTR(L"uri"), CComVariant(full_path_to_file));
    if (SUCCEEDED(hr))
      hr = spEvent->AddProperty(CComBSTR(L"last_modified_time"), CComVariant(varDate, VT_DATE));
    
    CStringW content;
    content.Format(L"Shortcut to %s", strOriginal);
    
    if (SUCCEEDED(hr))
      hr = spEvent->AddProperty(CComBSTR(L"format"), CComVariant("text/plain"));
    if (SUCCEEDED(hr))
      hr = spEvent->AddProperty(CComBSTR(L"content"), CComVariant(content));

    if (FAILED(hr))
      return Error(L"AddProperty failed", IID_IIndexShortcut, hr);

    hr = spEvent->Send(EventFlagIndexable);
    if (FAILED(hr))
      return Error(L"Send failed", IID_IIndexShortcut, hr);
  }
   
  return hr;
}
