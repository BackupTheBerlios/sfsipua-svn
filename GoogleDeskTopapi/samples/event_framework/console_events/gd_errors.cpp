#include "StdAfx.h"
#include "gd_errors.h"

const TCHAR* GDErrorToString(HRESULT hr) {
  switch (hr) {
    case E_EXTENSION_REGISTERED:
      return _T("A component tried to register for an already handled extension");

    case E_COMPONENT_NOT_REGISTERED:
      return _T("The component must register before performing any operations");

    case E_NO_SUCH_SCHEMA:
      return _T("Schema name not found");

    case E_NO_SUCH_PROPERTY:
      return _T("Property name not found");

    case E_COMPONENT_DISABLED:
      return _T("The component has been disabled by the user");

    case E_COMPONENT_ALREADY_REGISTERED:
      return _T("The component is already registered");

    case S_INDEXING_PAUSED:
      return _T("Indexing is paused and any sent events will be ignored");

    case E_EVENT_TOO_LARGE:
      return _T("The event was rejected because of data size limits");

    case E_SERVICE_NOT_RUNNING:
      return _T("Google Desktop is not running");

    case E_INVALID_EVENT_FLAGS:
      return _T("An event has invalid flags");

    case E_COMPONENT_PROHIBITED:
      return _T("The component is prohibited by the user's group policy");

    case E_SEND_DELAYED:
      return _T("The historical event sent could not be delivered immediately. A delay is recommended before sending again");

    case S_PROPERTY_TRUNCATED:
      return _T("The provided property has been truncated due to size limits");

    case E_PROPERTY_TOO_LARGE:
      return _T("The provided property is too large and cannot be accepted");

    case E_PROPERTY_NOT_SET:
      return _T("Property has not been set");

    case E_SERVICE_IS_EXITING:
      return _T("Google Destop is exiting");

    case E_APPLICATION_IS_EXITING:
      return _T("The application that made the call is exiting");

    case E_RETRY_SEND:
      return _T("The event could not be delivered and a re-send is required");
  }

  return _T("<unknown error>");
}
