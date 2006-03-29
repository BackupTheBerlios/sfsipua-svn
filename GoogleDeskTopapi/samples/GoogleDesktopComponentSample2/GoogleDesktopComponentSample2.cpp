// Copyright 2004-2005 Google Inc
// All rights reserved
// 
#include "stdafx.h"
#include "GoogleDesktopComponentSample2.h"
#include "ShellHook/ShellHook.h"

#define IDC_EDIT 100

// Global Variables:
CComQIPtr<IGoogleDesktopEventFactory> g_event_factory;
HWND g_hwnd_edit;
HINSTANCE g_instance;
const CLSID CLSID_WindowNotifier = {0x9A62EDAE,0x198D,0x4283,0xA6,0x61,0x66,0x63,0xDE,0xA1,0x69,0xDB};

void ShowError(LPCTSTR msg) {
  // format the message strings with a prefix for easy identification
  CString str;
  str.Format(_T("---->> %s\r\n"), msg);
  SendMessage(g_hwnd_edit, EM_REPLACESEL, FALSE, (LPARAM)(LPCTSTR)str);
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
LRESULT CALLBACK WndProc(HWND wnd, UINT message, WPARAM wparam, LPARAM lparam) {
  HRESULT hr;
  switch (message) {
    case WM_COPYDATA:
      // Got notification from our shell hook.
      {
        COPYDATASTRUCT *cds = (COPYDATASTRUCT*)lparam;
        LPCTSTR str_notify = (LPCTSTR)cds->lpData;

        // the shell notifier sends the app path and window title as two null terminated strings back to back in the lpData pointer.
        // it also sets the dwData field to 0 if the window is opened, 1 if the window is closed.
        LPCTSTR full_path_to_file = str_notify;
        LPCTSTR window_title = str_notify+_tcslen((LPCTSTR)str_notify)+1;
        LPCTSTR window_state = (cds->dwData == 0) ? _T("Opened") : _T("Closed");

        // this is not exactly the time at which the event happened, but is sufficient for this sample to demonstrate how to use the
        // time field.
        SYSTEMTIME system_time;
        double var_time;
        GetSystemTime(&system_time);
        SystemTimeToVariantTime(&system_time, &var_time);    // convert the time to the variant format

        // display the event data in our window
        CString str;
        str.Format(_T("App: %s, Window Title: %s, Event: %s\r\n"), full_path_to_file, window_title, window_state);
        SendMessage(g_hwnd_edit, EM_REPLACESEL, FALSE, (LPARAM)(LPCTSTR)str);

        // and also send the event to GDS

        // create an event object
        CComPtr<IDispatch> event_disp;  
        hr = g_event_factory->CreateEvent(CComBSTR(CLSID_WindowNotifier), CComBSTR(L"Google.Desktop.File"), &event_disp);
        if (FAILED(hr)) {
          ShowError(_T("Unable to create event"));
          break;
        }
        CComQIPtr<IGoogleDesktopEvent> event(event_disp);
        if (event == NULL) {
          ShowError(_T("Event does not implement IGoogleDesktopEvent"));
          break;
        }

        // create the content to display in the GDS search index. If this is a proper file, the content would be the text
        // in the file. But we create the content ourselves here since this is a window open/close notification.
        CStringW content(L"Window \"");
        content += window_title;
        content += L"\" was ";
        content += window_state;
        content.AppendFormat(L" at time: %d:%d:%d:%d", system_time.wHour, system_time.wMinute, 
                                          system_time.wSecond, system_time.wMilliseconds);

        // now add the relavent properties for the event (uri, access_time, native_format and native_content)
        // these fields are relavent for the 'File' schema. For using other schema consult the header files.
        hr = event->AddProperty(CComBSTR(L"uri"), CComVariant(full_path_to_file));
        if (SUCCEEDED(hr))
          hr = event->AddProperty(CComBSTR(L"last_modified_time"), CComVariant(var_time, VT_DATE));
        if (SUCCEEDED(hr))
          hr = event->AddProperty(CComBSTR(L"format"), CComVariant(L"text/plain"));
        if (SUCCEEDED(hr))
          hr = event->AddProperty(CComBSTR(L"content"), CComVariant(content));
        if (SUCCEEDED(hr))
          hr = event->AddProperty(CComBSTR(L"title"), CComVariant(window_title));

        if (FAILED(hr)) {
          ShowError(_T("AddProperty failed"));
          break;
        }

        // and send...
        hr = event->Send(EventFlagIndexable);
        if (FAILED(hr)) {
          ShowError(_T("Send failed"));
          break;
        }
      }
      break;
    case WM_COMMAND:
      // Process the menu commands
      if (HIWORD(wparam) == 0) {
        switch (LOWORD(wparam)) {
          case ID_FILE_REGISTERCOMPONENTWITHGDS:
            {
              // Create our icon path 
              CStringW module_name;
              CStringW icon_name;
              ::GetModuleFileNameW(g_instance, CStrBufW(module_name, 1024), 1023);
              icon_name.Format(L"%ls,%d", module_name, IDI_GOOGLEDESKTOPCOMPONENTSAMPLE2);

              // register our module
              hr = RegisterIndexingComponentHelper(CLSID_WindowNotifier, 
                                     L"Window create/destroy notifier",
                                     L"Gathers information on all top level windows created/destroyed by applications.", 
                                     icon_name, 0, NULL);
              if (SUCCEEDED(hr))
                ShowError(_T("Component registration succeeded"));
              else
                ShowError(_T("Component registration failed or component already registered"));
            }
            break;
          case ID_FILE_DEREGISTERCOMPONENTFROMGDS:
            hr = UnregisterComponentHelper(CLSID_WindowNotifier);
            if (SUCCEEDED(hr))
              ShowError(_T("Component deregister succeeded"));
            else
              ShowError(_T("Component deregister failed"));
            break;
          case IDM_EXIT:
            DestroyWindow(wnd);
            break;
          default:
            return DefWindowProc(wnd, message, wparam, lparam);
        }
      }
      break;
    case WM_SIZE:
      {
        // resize our edit control to fit the window
        RECT rc;
        GetClientRect(wnd, &rc);
        MoveWindow(g_hwnd_edit, 0, 0, rc.right, rc.bottom, TRUE);
      }
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return DefWindowProc(wnd, message, wparam, lparam);
  }
  return 0;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE instance) {
  WNDCLASSEX wcex;
  ZeroMemory(&wcex, sizeof(wcex));
  wcex.cbSize = sizeof(WNDCLASSEX); 
  wcex.style      = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc  = (WNDPROC)WndProc;
  wcex.hInstance    = instance;
  wcex.hIcon      = LoadIcon(instance, (LPCTSTR)IDI_GOOGLEDESKTOPCOMPONENTSAMPLE2);
  wcex.hCursor    = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
  wcex.lpszMenuName  = (LPCTSTR)IDC_GOOGLEDESKTOPCOMPONENTSAMPLE2;
  wcex.lpszClassName  = kAppTitle;
  return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we create and display the main program window.
//
BOOL InitInstance(HINSTANCE instance, int cmdshow) {
   HWND wnd;

   wnd = CreateWindow(kAppTitle, kAppTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, instance, NULL);

   if (!wnd)
      return FALSE;

   // create a child edit control to display the status and the messages that we want to log.
   RECT rc;
   GetClientRect(wnd, &rc);
   g_hwnd_edit = CreateWindow(_T("EDIT"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE, 0, 0, rc.right, rc.bottom,
     wnd, (HMENU)IDC_EDIT, instance, NULL);

   ShowWindow(wnd, cmdshow);
   UpdateWindow(wnd);

   return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE instance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       cmdshow) {
  if (FAILED(CoInitialize(NULL)))
    return FALSE;

  g_instance = instance;
  MyRegisterClass(instance);

  // create a GDS event factory first, this is required to create events later
  HRESULT hr = g_event_factory.CoCreateInstance(CLSID_GoogleDesktop);
  if (FAILED(hr))
    return FALSE;

  // Perform application initialization:
  if (!InitInstance (instance, cmdshow)) 
    return FALSE;

  // start our window open/close notifier. This is in a separate dll (ShellHook.dll) to which we link
  if (!StartShellHook())
    return FALSE;

  // Main message loop:
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  // cleanup
  StopShellHook();
  g_event_factory.Release();
  CoUninitialize();

  return (int) msg.wParam;
}
