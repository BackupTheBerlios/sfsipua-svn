// gvi_plugin.cpp : Implementation of CGIVPlugin

#include "stdafx.h"
#include <atlstr.h>
#include <map>
#include <string>
#include "../common/GoogleDesktopAPI.h"
#include "gvi_plugin.h"
#include "gvi_parser.h"

using std::string;

// CGIVPlugin

STDMETHODIMP CGIVPlugin::InterfaceSupportsErrorInfo(REFIID riid) {
  static const IID* arr[] = 
  {
	&IID_Igvi_plugin
  };

  for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++) {
	if (InlineIsEqualGUID(*arr[i],riid))
	  return S_OK;
  }
  return S_FALSE;
}

STDMETHODIMP CGIVPlugin::HandleFile(BSTR full_path_to_file, 
									IDispatch* event_factory) {
  CComPtr<IGoogleDesktopEventFactory> spEventFactory;
  CComPtr<IDispatch> spEventDisp;  
  HRESULT hr;

  hr  = event_factory->QueryInterface(&spEventFactory);
  if (FAILED(hr))
	return Error(L"No event factory", IID_Igvi_plugin, hr);

  hr = spEventFactory->CreateEvent(CComBSTR(CLSID_gvi_plugin), CComBSTR(L"Google.Desktop.MediaFile"), &spEventDisp);
  if (FAILED(hr))
	return Error(L"Unable to create event", IID_Igvi_plugin, hr);

  CComQIPtr<IGoogleDesktopEvent> spEvent(spEventDisp);

  ATLASSERT(spEventDisp && spEvent);
  if (spEvent == NULL) {
	return Error(L"Event does not implement IGoogleDesktopEvent", IID_Igvi_plugin, E_UNEXPECTED);
  }

  hr = spEvent->AddProperty(CComBSTR(L"uri"), CComVariant(full_path_to_file));
  WIN32_FIND_DATA wfd;
  CComBSTR path2(full_path_to_file);
  char path3[2048];
  wcstombs(path3, path2, 2048);
  if (!GetFileAttributesEx(path3, GetFileExInfoStandard, &wfd)) {
	return HRESULT_FROM_WIN32(::GetLastError());
  }
  SYSTEMTIME systemTime;
  FileTimeToSystemTime(&wfd.ftCreationTime, &systemTime);

  // convert the date to the variant format
  double varDate;
  SystemTimeToVariantTime(&systemTime, &varDate);
  if (SUCCEEDED(hr))
	hr = spEvent->AddProperty(CComBSTR(L"last_modified_time"), CComVariant(varDate, VT_DATE));
  GVIParser parser;
  std::map<string, string> metadata;
  std::map<string, string>::iterator metadata_iter;
  parser.ParseMetadata(path3, &metadata);
  string title = "";
  metadata_iter = metadata.find("title");
  if (metadata_iter != metadata.end()) {
	title = (*metadata_iter).second;
	hr = spEvent->AddProperty(CComBSTR(L"title"), CComVariant(title.c_str()));
  } else {
  }
  hr = spEvent->AddProperty(CComBSTR(L"format"), CComVariant(L"text/plain"));

  metadata_iter = metadata.find("description");
  if (metadata_iter != metadata.end()) {
	string descr = (*metadata_iter).second;
	hr = spEvent->AddProperty(CComBSTR(L"content"), CComVariant(CStringW(descr.c_str())));
  } else {
  }
  if (FAILED(hr))
	return Error(L"AddProperty failed", IID_Igvi_plugin, hr);
  // also do: native_size, title, author?, width?, height? 
  hr = spEvent->Send(EventFlagIndexable);
  if (FAILED(hr))
	return Error(L"Send failed", IID_Igvi_plugin, hr);

  return hr;
}
