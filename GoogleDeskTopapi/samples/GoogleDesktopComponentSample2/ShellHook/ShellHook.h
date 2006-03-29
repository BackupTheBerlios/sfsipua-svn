// Copyright 2004 Google Inc
// All rights reserved
// 

#ifndef _SHELLHOOK_H
#define _SHELLHOOK_H

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SHELLHOOK_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SHELLHOOK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SHELLHOOK_EXPORTS
#define SHELLHOOK_API __declspec(dllexport)
#else
#define SHELLHOOK_API __declspec(dllimport)
#endif

// Start window open/close notifications
SHELLHOOK_API int StartShellHook(void);

// Stop window open/close notifications
SHELLHOOK_API void StopShellHook(void);

#endif  // _SHELLHOOK_H
