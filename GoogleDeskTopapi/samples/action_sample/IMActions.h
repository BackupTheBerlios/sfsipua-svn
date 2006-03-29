// Copyright 2005 Google, Inc
// All Rights Reserved
//
// IMActions.h : Declaration of CIMActions

#pragma once
#include "resource.h"       /// main symbols

#include "ActionSample.h"
#include "../common/GoogleDesktopActionAPI.h"
#include <atlstr.h>

// Sample IM actin plugin
class ATL_NO_VTABLE CIMActions : 
  public CComObjectRootEx<CComMultiThreadModel>,
  public CComCoClass<CIMActions, &CLSID_IMActions>,
  public IGoogleDesktopCustomAction
{
public:
  CIMActions()
  {
  }

  DECLARE_REGISTRY_RESOURCEID(IDR_IMACTIONS)

  BEGIN_COM_MAP(CIMActions)
    COM_INTERFACE_ENTRY(IGoogleDesktopCustomAction)
  END_COM_MAP()

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  HRESULT FinalConstruct()
  {
    return S_OK;
  }
  
  void FinalRelease() 
  {
  }

public:
  /// IGoogleDesktopCustomAction
  STDMETHOD(QueryInterest)( 
      /* [in] */ ACTION_LOCATION location,
      /* [in] */ ACTION_ID action,
      /* [in] */ BSTR query_string,
      /* [in] */ IUnknown *item,
      /* [out][in] */ BSTR *action_title,
      /* [out] */ BSTR *action_cookie,
      /* [out] */ ActionHandling *handling) {
      ATLASSERT(NULL != query_string);
      ATLASSERT(NULL != action_title && NULL != *action_title);
      ATLASSERT(NULL != action_cookie && NULL == *action_cookie);
      ATLASSERT(NULL != handling);
      
      if (IsEqualGUID(action, ACTION_IM_CHAT)) {
        // We don't do anything here, but ACTION_IM_CHAT is meant
        // to open an IM conversation to the peer named in item.
      } else {
        /// unknown 
        ATLASSERT(false && "Unregistered action in QueryInterest");
        *handling = ACTION_HANDLING_DEFAULT;
      }

      return S_OK;
    }

  STDMETHOD(HandleAction)( 
      /* [in] */ ACTION_LOCATION location,
      /* [in] */ ACTION_ID action,
       /* [in] */ BSTR query_string,
      /* [in] */ IUnknown *item,
      /* [in] */ BSTR action_cookie) {
    // Action processing is but a message box for us.
    CString str;
    
    str.Format(_T("Query: %ws, action: %ws"), query_string, action_cookie);
    MessageBox(NULL, str, _T("Action!"), MB_OK | MB_SERVICE_NOTIFICATION);

    return S_OK;
  }
};

OBJECT_ENTRY_AUTO(CLSID_IMActions, CIMActions)
