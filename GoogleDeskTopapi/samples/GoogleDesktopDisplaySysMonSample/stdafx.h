// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#define WINVER 0x0500        // win2k and above

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0500

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

// turns off ATL's hiding of some common and often safely ignored warning messages
#define _ATL_ALL_WARNINGS 

#include <atlbase.h>
#include <atlcom.h>
#include <atlstr.h>
#include <atlwin.h>
#include <atlctl.h>

#include <windows.h>
#include "../common/basic_types.h"
#include "../common/utils.h"

#define NOTRANSL(x) (x)

using namespace ATL;