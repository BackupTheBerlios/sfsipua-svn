#include "stdafx.h"
#include "ef_registration.h"
#include "event_callback.h"
#include "argumentcheck.h"
#include "gd_errors.h"
#include "ctrl_break_handler.h"

// We need to initialize COM
ComInit initialize_com;

/**
* Processes events until the user presses Ctrl+C
*/
HRESULT ReceiveEvents() {
  HRESULT hr = S_OK;

  CtrlBreakHandler break_handler;

  MSG msg;
  BOOL ret;
  while ((ret = GetMessage(&msg, NULL, 0, 0)) != FALSE) { 
    if (ret == -1) {
      hr = E_UNEXPECTED;
      break;
    } else {
      TranslateMessage(&msg); 
      DispatchMessage(&msg); 
    }
  }

  return hr;
}


/**
* Entry point routine.
*
* There's no argument needed for registration but to uninstall, specify the
* "-uninstall" parameter.
* 
* This routine connects to the Google Desktop event publisher and establishes
* an event subscription.  The subscription can by filtered to only deliver
* events that belong to a certain schema. To specify a schema, use the
* "-s" flag, immediately followed by the schema name.
* Example:
*   console_events -sEmail
*
* Repeating the -s flag is supported.
*/
int _tmain(int argc, TCHAR* argv[]) {
  ArgumentCheck args;
  if (!args.Check(argc, argv)) {
    args.PrintUsage();
    return -1;
  }

  long cookie = 0;
  HRESULT hr;

  if (args.IsUninstall()) {
    hr = UnregisterFromGDEventFramework();
    if (SUCCEEDED(hr))
      return 0;
  } else {
    hr = EnsureRegistered(&cookie);
  }

  if (FAILED(hr)) {
    _tprintf(_T("Unable to %s with the Google Desktop event framework - 0x%08X\n%s\n"),
      args.IsUninstall() ? _T("unregister") : _T("register"), hr, GDErrorToString(hr));
    return hr;
  }

  ATLASSERT(cookie != 0);

  //
  // Create an instance of the Google Desktop Event Publisher
  // and set up a subscription
  //
  CComPtr<IGoogleDesktopEventPublisher> publisher;
  hr = publisher.CoCreateInstance(L"GoogleDesktop.EventPublisher.1");

  // Our callback object that will receive notifications
  EventCallback callback;

  // Our subscription that controls how events are delivered to us
  CComPtr<IGoogleDesktopEventSubscription> subscription;

  if (SUCCEEDED(hr)) {
    CComPtr<IUnknown> callback_identity;
    // Use ATL's special QI method to get the identity IUnknown pointer
    // of our callback object.
    hr = callback._LocDEQueryInterface(IID_IUnknown,
                                       reinterpret_cast<void**>(&callback_identity));
    ATLASSERT(SUCCEEDED(hr) && "_LocDEQueryInterface");

    //
    // Now connect our callback object to the GD Event Framework
    // by subscribing to events, then configure the subscription
    // and eventually, turn on the event stream.
    // 
    hr = publisher->Subscribe(cookie, callback_identity, &subscription);

    if (SUCCEEDED(hr)) {
      if (argc > 1) {
        hr = args.SetUserSpecifiedSchemaFilters(subscription);
      }

      if (SUCCEEDED(hr)) {
        // This turns on the event stream
        hr = subscription->put_active(VARIANT_TRUE);
      }
    }
  }

  if (FAILED(hr)) {
    _tprintf(_T("An error occured while connecting to the Google Desktop event framework - 0x%08X\n%s\n"),
      hr, GDErrorToString(hr));
    return hr;
  }

  _tprintf(_T("Event information will show up here.  Press Ctrl+C to stop.\n"));
  hr = ReceiveEvents();

  // Now turn off the subscription and unsubscribe
  ATLVERIFY(SUCCEEDED(subscription->put_active(VARIANT_FALSE)));
  ATLVERIFY(SUCCEEDED(publisher->Unsubscribe(subscription)));

  // Print out some information on our exit status
  if (FAILED(hr)) {
    _tprintf(_T("An error occured during processing of events - 0x%08X\n%s\n"),
      hr, GDErrorToString(hr));
  } else {
    _tprintf(_T("Have a nice day!\n"));
  }

  return hr;
}

