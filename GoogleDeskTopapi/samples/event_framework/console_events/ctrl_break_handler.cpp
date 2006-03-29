#include "StdAfx.h"
#include "ctrl_break_handler.h"

DWORD CtrlBreakHandler::s_main_thread = ::GetCurrentThreadId();
