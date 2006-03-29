// Copyright 2005 Google Inc
// All rights reserved
// 
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#define WINVER 0x0500    // win2k and above

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

// #define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS  // some CString constructors will be explicit

// turns off ATL's hiding of some common and often safely ignored warning messages
#define _ATL_ALL_WARNINGS

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlstr.h>
#include <atlwin.h>
#include <atlsafe.h>
#include <atlcoll.h>
#include <wininet.h>
#include <strsafe.h>

#include "../common/GoogleDesktopDisplayAPI.h"
#include <atlctl.h>

using namespace ATL;

#define countof(a) (sizeof(a) / sizeof((a)[0]))
#define unused(expr) (void)(expr)
typedef __int64 longlong;
typedef unsigned __int64 ulonglong;

typedef CAtlArray<CString> CStringArray;
typedef CAtlArray<int> CIntArray;


#pragma warning(disable: 4995) // atl uses 'wsprintf': name was marked as #pragma deprecated
