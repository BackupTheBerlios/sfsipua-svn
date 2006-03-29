#pragma once

/**
* Our callback class.  This class receives the event object when new events
* get indexed.
*/
class EventCallback : 
  public IDispEventSimpleImpl<1, EventCallback, &IID_IDispatch> {
public:
BEGIN_SINK_MAP(EventCallback)
  SINK_ENTRY_INFO(1, IID_IDispatch, DISPID_VALUE, OnNewEvent, &s_OnNewEventInfo)
END_SINK_MAP()

  /**
  * This function gets called by the event framework as this is the default
  * method on our class (DISPID_VALUE).
  * Alternatively, we could have a typelib and implement a function with
  * the name OnNewEvent, but this way it's simpler and more lightweight.
  */
  STDMETHOD_(void, OnNewEvent)(IDispatch* event) {
    if (event == NULL) {
      _tprintf(_T("Historical indexing has just been done.\n"));
    } else {
      CComQIPtr<IGoogleDesktopNotifyEvent> e(event);
      ATLASSERT(e != NULL);
      CComBSTR schema;
      e->get_SchemaName(&schema);

      CComVariant uri;
      e->GetProperty(CComBSTR(L"uri"), &uri);

      _tprintf(_T("%ls: %ls\n"), schema, uri.vt == VT_BSTR ? uri.bstrVal : L"?");
    }
  }

  // See ATL's documentation on IDispEventSimpleImpl for details
  static _ATL_FUNC_INFO s_OnNewEventInfo;
};
