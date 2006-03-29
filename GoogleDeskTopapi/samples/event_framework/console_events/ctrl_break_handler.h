#pragma once

class CtrlBreakHandler {
public:
  CtrlBreakHandler() {
    SetConsoleCtrlHandler(PostQuit, TRUE);
  }

  ~CtrlBreakHandler() {
    SetConsoleCtrlHandler(PostQuit, FALSE);
  }

protected:
  // Callback routine for when the user presses Ctrl+C or Ctrl+break
  static BOOL WINAPI PostQuit(DWORD dwCtrlType) {
    ::PostThreadMessage(s_main_thread, WM_QUIT, 0, 0);
    return TRUE;
  }

protected:
  // Store the main thread id since Ctrl+C callbacks occur on a callback thread
  // (i.e. not the main thread)
  static DWORD s_main_thread;
};
