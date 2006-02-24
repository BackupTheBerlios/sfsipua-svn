// rtcsample.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

/////////////////////////////////////////////
//
// WinMain
// 

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    HRESULT hr;
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(hPrevInstance);

    DEBUG_PRINT(("STARTED"));

    // Initialize COM
    hr = CoInitialize(NULL);

    if (FAILED(hr))
    {
        // CoInitialize failed
        DEBUG_PRINT(("CoInitialize failed %x", hr));
        return 0;
    }
    
    // Initialize windows common controls
    InitCommonControls();

    // Load the rich edit library
    HMODULE hRichEdit = NULL;

    hRichEdit = LoadLibrary(L"riched20.dll");

    if (hRichEdit == NULL)
    {
        // LoadLibrary failed
        DEBUG_PRINT(("LoadLibrary failed %x",
            HRESULT_FROM_WIN32(GetLastError()) ));
        return 0;
    }

    // Register the window classes
    CRTCWin::RegisterClass();
    CRTCIMSession::RegisterClass();
    CRTCAVSession::RegisterClass();
    CRTCSearch::RegisterClass();
    CRTCWatcher::RegisterClass();
    CRTCGroup::RegisterClass();

    // Create the main window
    HWND hWnd;

    hWnd = CreateWindowExW(
                0,
                APP_CLASS,
                APP_TITLE,
                WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                CW_USEDEFAULT, CW_USEDEFAULT,
                APP_WIDTH, APP_HEIGHT,
                NULL,
                NULL,
                hInstance,
                NULL);

    if ( !hWnd )
    {  
        // CreateWindowExW failed
        DEBUG_PRINT(("CreateWindowExW failed %x",
            HRESULT_FROM_WIN32(GetLastError()) ));
        return 0;
    }

    // Make the main window visible
    ShowWindow( hWnd, nCmdShow );
    UpdateWindow( hWnd );

    // Message loop
    BOOL bRet;
    MSG msg;

    while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
    { 
        if (bRet == -1)
        {
            // GetMessage failed
            DEBUG_PRINT(("GetMessage failed %x",
                HRESULT_FROM_WIN32(GetLastError()) ));
            return 0;
        }
        else
        {
            TranslateMessage(&msg); 
            DispatchMessage(&msg); 
        }
    }

    // Free the rich edit library
    FreeLibrary(hRichEdit);

    // Shutdown COM
    CoUninitialize();

    DEBUG_PRINT(("STOPPED"));

	return (int) msg.wParam;
}
