// Copyright 2004 Google Inc
// All rights reserved
// 
#include <windows.h>
#include <tchar.h>
#include "ShellHook.h"
#include "..\GoogleDesktopComponentSample2.h"

// globals
HINSTANCE g_dll_module_handle;
HHOOK g_shell_hook;

// This hook procedure is called by windows whenever there is a shell event. We are only interested in window created/destroyed
// events and we handle them here.
LRESULT CALLBACK SampleShellProc(int code, WPARAM wp, LPARAM lp) {
  if (code == HSHELL_WINDOWCREATED || code == HSHELL_WINDOWDESTROYED) {
    // find the GDS Sample Component window
    HWND app_wnd = FindWindow(kAppTitle, kAppTitle);
    if (app_wnd != NULL) {
      HWND wnd = (HWND)wp;
      TCHAR msg_buffer[MAX_PATH*2];
      int pathLen, titleLen;
      pathLen = GetModuleFileName(NULL, msg_buffer, MAX_PATH-1);    // get the process path
      msg_buffer[pathLen] = 0;
      titleLen = GetWindowText(wnd, msg_buffer+pathLen+1, MAX_PATH-1);  // get the window title
      msg_buffer[pathLen+1+titleLen] = 0;

      COPYDATASTRUCT cds;
      cds.cbData = sizeof(TCHAR)*(pathLen+1+titleLen+1);
      cds.lpData = msg_buffer;
      cds.dwData = (code == HSHELL_WINDOWCREATED)?0:1;        // flag indicating if the window was opened or closed
      SendMessage(app_wnd, WM_COPYDATA, NULL, (LPARAM)&cds);      // send to the sample component which posts the event to GDS
    }
  }
  return CallNextHookEx(g_shell_hook, code, wp, lp);
}

// Start window open/close notifications
SHELLHOOK_API int StartShellHook(void) {
  g_shell_hook = SetWindowsHookEx(WH_SHELL, (HOOKPROC)SampleShellProc, g_dll_module_handle, NULL);
  return (g_shell_hook != NULL);
}

// Stop window open/close notifications
SHELLHOOK_API void StopShellHook(void) {
  UnhookWindowsHookEx(g_shell_hook);
}

// Main entry point.
BOOL APIENTRY DllMain( HANDLE module, 
                       DWORD  ul_reason_for_call, 
                       LPVOID reserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
      g_dll_module_handle = (HINSTANCE)module;
      break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      g_dll_module_handle = NULL;
      break;
  }
    return TRUE;
}
