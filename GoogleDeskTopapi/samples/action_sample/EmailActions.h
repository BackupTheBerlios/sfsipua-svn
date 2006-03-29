// Copyright 2005 Google, Inc
// All Rights Reserved
//
// IMActions.h : Declaration of CEmailActions

#pragma once
#include "resource.h"       /// main symbols

#include "ActionSample.h"
#include "../common/GoogleDesktopActionAPI.h"
#include <atlstr.h>

// A sample plugin for email actions.
class ATL_NO_VTABLE CEmailActions : 
  public CComObjectRootEx<CComMultiThreadModel>,
  public CComCoClass<CEmailActions, &CLSID_EmailActions>,
  public IGoogleDesktopCustomAction
{
public:
  CEmailActions()
  {
  }

  DECLARE_REGISTRY_RESOURCEID(IDR_EMAILACTIONS)

  BEGIN_COM_MAP(CEmailActions)
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
  // IGoogleDesktopCustomAction
  // In QueryInterest, check the supplied item to see whether you want to
  // handle it, and set *handing to override or quench as appropriate.
  // If the action is being rendered into HTML, you can also override the 
  // title. 
  // You can pass a bit of state to HandleAction through the cookie, which
  // should be a short ASCII string.
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
      
      /// Override Forward always, quench reply always
      if (IsEqualGUID(action, ACTION_EMAIL_FORWARD)) {
        CString title(L"Overridden Forward");
        CString cookie(L"Email Forward ну&?+/");
        
        ATLASSERT(NULL != item);
        
        title.SetSysString(action_title);
        *action_cookie = cookie.AllocSysString();

        *handling = ACTION_HANDLING_OVERRIDE;

      } else if (IsEqualGUID(action, ACTION_EMAIL_REPLY)) {
        *handling = ACTION_HANDLING_QUENCH;
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
    // Action processing is but a message box for us, 
    // here you might want to tell an email application to open 
    // the item in question.
    CString str;
    
    str.Format(_T("Query: %ws, action: %ws"), query_string, action_cookie);
    MessageBox(NULL, str, _T("Action!"), MB_OK | MB_SERVICE_NOTIFICATION);

    return S_OK;
  }
};

OBJECT_ENTRY_AUTO(CLSID_EmailActions, CEmailActions)
