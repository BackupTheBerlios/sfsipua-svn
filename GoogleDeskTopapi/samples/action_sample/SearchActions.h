// Copyright 2005 Google, Inc
// All Rights Reserved
//
// SearchActions.h : Declaration of CSearchActions

#pragma once
#include "resource.h"       /// main symbols

#include "ActionSample.h"
#include "../common/GoogleDesktopActionAPI.h"
#include "../common/GoogleDesktopAPI.h"
#include <atlstr.h>


// A sample action plugin to handle actions on search result pages
class ATL_NO_VTABLE CSearchActions : 
  public CComObjectRootEx<CComMultiThreadModel>,
  public CComCoClass<CSearchActions, &CLSID_SearchActions>,
  public IGoogleDesktopCustomAction
{
public:
  CSearchActions()
  {
  }

  DECLARE_REGISTRY_RESOURCEID(IDR_SEARCHACTIONS)

  BEGIN_COM_MAP(CSearchActions)
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
      
      // for this demo, we modify the title of any 
      // search result that contains "foo" in title, and quench
      // the action on any result that contains "bar".
      // Note that you would more usually make decisions about how
      // to handle an action by looking at properties of item,
      // which'll be an IGoogleDesktopNotifyEvent.
      if (IsEqualGUID(action, ACTION_OPEN_SEARCH_RESULT)) {
        CComQIPtr<IGoogleDesktopNotifyEvent> result(item);
        if (wcsstr(*action_title, L"foo")) {
          if (item) {
            CString title(*action_title);
            CComVariant var_title;
            result->GetProperty(CComBSTR("title"), &var_title);
            
            if (V_VT(&var_title) & VT_BSTR)
              title.Format(_T("Event Title: \"%ws\""), V_BSTR(&var_title));

            // let's not leak the original string
            ::SysFreeString(*action_title);
            *action_title = title.AllocSysString();

            *handling = ACTION_HANDLING_OVERRIDE;
          } else {
            *handling = ACTION_HANDLING_QUENCH;
          }
        } else if (wcsstr(*action_title, L"bar")) {
          *action_title = CComBSTR(L"Title contained bar - so I overrode it");
          *action_cookie = CComBSTR(L"Chocolate Chip");
          *handling = ACTION_HANDLING_OVERRIDE;
        } else {
          *handling = ACTION_HANDLING_DEFAULT;
        }
      } else {
        ATLASSERT(false && "Unregistered action in QueryInterest");
        /// unknown 
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

OBJECT_ENTRY_AUTO(CLSID_SearchActions, CSearchActions)
