#pragma once

#include <atlbase.h>
#include <atlcom.h>
#include <atlsafe.h>
#include <stdio.h>

// Include the Google Desktop
// event framework interface definitions and constants
#include "../../common/GoogleDesktopAPI.h"
#include "../../common/GoogleDesktopComponentRegistration.h"

/// Simple class for initializing COM.
/// This class initializes the thread as single (Apartment) threaded.
class ComInit {
public:
  ComInit() {
    ATLVERIFY(SUCCEEDED(::CoInitialize(NULL)));
  }

  ~ComInit() {
    ::CoUninitialize();
  }
};
