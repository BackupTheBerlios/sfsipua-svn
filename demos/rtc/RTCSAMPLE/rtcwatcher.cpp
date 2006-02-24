// rtcwatcher.cpp
//

#include "stdafx.h"
#include <assert.h>
/////////////////////////////////////////////
//
// CRTCWatcher::CRTCWatcher
// 

CRTCWatcher::CRTCWatcher()
{
    m_hWnd = NULL;
    m_hWatcherList = NULL;
    m_pClient = NULL;
}

/////////////////////////////////////////////
//
// CRTCWatcher::~CRTCWatcher
// 

CRTCWatcher::~CRTCWatcher()
{
}

/////////////////////////////////////////////
//
// CRTCWatcher::RegisterClass
//

HRESULT CRTCWatcher::RegisterClass()
{
    // Register the window class
    WNDCLASS wc;
    ATOM atom;

    ZeroMemory(&wc, sizeof(WNDCLASS));

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)CRTCWatcher::WindowProc;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.hIcon         = NULL;
    wc.hCursor       =
        LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = 
        GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU_WATCHERS);
    wc.lpszClassName = WAT_CLASS;

    atom = ::RegisterClass( &wc );

    if ( !atom )
    {
        // RegisterClass failed
        DEBUG_PRINT(("RegisterClass failed %x",
            HRESULT_FROM_WIN32(GetLastError()) ));
        return E_FAIL;
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWatcher::UpdateWatcherList
//

HRESULT CRTCWatcher::UpdateWatcherList(IRTCWatcher * pWatcher)
{
    HRESULT hr;

	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates getting watcher name, URI, watcher state 
	// and scope and populating the list box
	//
	////////////

    if (pWatcher == NULL)
    {
        return S_OK;
    }

    // Get the watcher state
    RTC_WATCHER_STATE enState;
    RTC_ACE_SCOPE     enScope;

    hr = pWatcher->get_State(&enState);

    if (FAILED(hr))
    {
        // get_State failed
        DEBUG_PRINT(("get_State failed %x", hr ));
        return hr;
    }

    IRTCWatcher2 * pWatcher2 = NULL;

    hr = pWatcher->QueryInterface(
            __uuidof(IRTCWatcher2),
            (void **)&pWatcher2);

    if (FAILED(hr))
    {
        // QueryInterface failed
        DEBUG_PRINT(("QueryInterface failed %x", hr ));
        return hr;
    }

    // Get the ACE scope (ALL, DOMAIN, USER)
    hr = pWatcher2->get_Scope(&enScope);
    
    if (FAILED(hr))
    {
        // get_Scope failed
        DEBUG_PRINT(("get_Scope failed %x", hr ));
        SAFE_RELEASE(pWatcher2);
        return hr;
    }

    // Get the watcher name
    BSTR bstrName = NULL;

    hr = pWatcher->get_Name(&bstrName);

    if (SUCCEEDED(hr) && !wcscmp(bstrName, L""))
    {
        // Treat an emptry string as a failure
        DEBUG_PRINT(("get_Name failed %x", hr ));
        SAFE_FREE_STRING(bstrName);
        hr = E_FAIL;
    }

    if (FAILED(hr))
    {
        // get_Name failed, get the URI instead
        hr = pWatcher->get_PresentityURI(&bstrName);

        if (SUCCEEDED(hr) && !wcscmp(bstrName, L""))
        {
            // Treat an emptry string as a failure
            SAFE_FREE_STRING(bstrName);
            hr = E_FAIL;
        }

        if (FAILED(hr))
        {
            // get_PresentityURI failed
            DEBUG_PRINT(("get_PresentityURI failed %x", hr ));
            return hr;
        }
    }

    // Build a string for the listbox
    WCHAR szWatcher[MAX_STRING];
    WCHAR * szScope = L"";

    switch(enScope)
    {
    case RTCAS_SCOPE_ALL:
        szScope = L"(ALL) ";
        break;

    case RTCAS_SCOPE_DOMAIN:
        szScope = L"(DOMAIN) ";
        break;
    }


    switch(enState)
    {
    case RTCWS_OFFERING:
        _snwprintf(szWatcher, MAX_STRING, L"%ws (Offering) %ws",
            bstrName, szScope);
        break;
    case RTCWS_ALLOWED:
        _snwprintf(szWatcher, MAX_STRING, L"%ws (Allowed) %ws",
            bstrName, szScope);
        break;
    case RTCWS_BLOCKED:
        _snwprintf(szWatcher, MAX_STRING, L"%ws (Blocked) %ws",
            bstrName, szScope);
        break;
    case RTCWS_DENIED:
        _snwprintf(szWatcher, MAX_STRING, L"%ws (Denied) %ws",
            bstrName, szScope);
        break;
    case RTCWS_PROMPT:
        _snwprintf(szWatcher, MAX_STRING, L"%ws (Prompt) %ws",
            bstrName, szScope);
        break;
    default:
        _snwprintf(szWatcher, MAX_STRING, L"%ws %ws",
            bstrName, szScope);
        break;
    }

    szWatcher[MAX_STRING-1] = L'\0';

    SAFE_FREE_STRING(bstrName);

    ////////////
	//
	// End RTC Functionality Code
	//
	////////////

    // Is the watcher in the list?
    LVFINDINFO lvfi;    
    ZeroMemory(&lvfi, sizeof(LVFINDINFO));

    lvfi.flags = LVFI_PARAM;
    lvfi.lParam = (LPARAM)pWatcher;

    int iRes = ListView_FindItem(m_hWatcherList, -1, &lvfi);

    if (iRes == -1)
    {
        // Watcher is not in the list
        // Add the watcher to the list  
        LVITEM lvi;
        ZeroMemory(&lvi, sizeof(LVITEM));

        lvi.mask = LVIF_TEXT | LVIF_PARAM;
        lvi.pszText = szWatcher;
        lvi.lParam = (LPARAM)pWatcher;

        iRes = ListView_InsertItem(m_hWatcherList, &lvi);

        if (iRes == -1)
        {
            // ListView_InsertItem failed
            DEBUG_PRINT(("ListView_InsertItem failed %x",
                HRESULT_FROM_WIN32(GetLastError()) ));
            return E_FAIL;
        }
		////////////
		//
		// Begin RTC Functionality Code
		//
		// This code demonstrates Addref for the watcher 
		//
		////////////


        // An RTC watcher reference will be kept by the list
        // Add the reference here
        pWatcher->AddRef();

		////////////
		//
		// End RTC Functionality Code
		//
		////////////

    }
    else
    {
        // Watcher is in the list
        // Update the list entry
        LVITEM lvi;
        ZeroMemory(&lvi, sizeof(LVITEM));

        lvi.mask = LVIF_TEXT;
        lvi.pszText = szWatcher;
        lvi.iItem = iRes;

        iRes = ListView_SetItem(m_hWatcherList, &lvi);

        if (iRes == -1)
        {
            // ListView_SetItem failed 
            DEBUG_PRINT(("ListView_SetItem failed %x",
                HRESULT_FROM_WIN32(GetLastError()) ));
            return E_FAIL;
        }
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWatcher::ClearWatcherList
//

HRESULT CRTCWatcher::ClearWatcherList(IRTCWatcher * pWatcher)
{
    HRESULT hr = S_OK;

    if (pWatcher == NULL)
    {
        return S_OK;
    }
    
    // Is the watcher in the list?
    LVFINDINFO lvfi;    
    ZeroMemory(&lvfi, sizeof(LVFINDINFO));

    lvfi.flags = LVFI_PARAM;
    lvfi.lParam = (LPARAM)pWatcher;

    int iRes = ListView_FindItem(m_hWatcherList, -1, &lvfi);

    if (iRes != -1)
    {       
        // Watcher is in the list
        // Remove the list entry
        ListView_DeleteItem(m_hWatcherList, iRes);

		////////////
		//
		// Begin RTC Functionality Code
		//
		// This code demonstrates releasing IRTCWatcher references
		//
		////////////

        // Release the watcher reference
        SAFE_RELEASE(pWatcher);        

		////////////
		//
		// End RTC Functionality Code
		//
		////////////

    }

    return hr;
}

/////////////////////////////////////////////
//
// CRTCWatcher::ClearWatcherList
// 

HRESULT CRTCWatcher::ClearWatcherList()
{
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(LVITEM));
    
    lvi.mask = LVIF_PARAM;

    // Iterate through the list and remove each item
    while (ListView_GetItem(m_hWatcherList, &lvi))
    {
        IRTCWatcher * pWatcher = (IRTCWatcher *)(lvi.lParam);

        // Remove the list entry
        ListView_DeleteItem(m_hWatcherList, 0);

        // Release the watcher reference
        SAFE_RELEASE(pWatcher);        
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWatcher::PopulateWatcherList
// 

HRESULT CRTCWatcher::PopulateWatcherList()
{
    HRESULT hr;

	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates enumerating watchers and populating UI.
	//
	////////////


    // Get the RTC client presence interface
    IRTCClientPresence * pPresence = NULL;

    hr = m_pClient->QueryInterface(
            __uuidof(IRTCClientPresence),
            (void **)&pPresence);

    if (FAILED(hr))
    {
        // QueryInterface failed
        DEBUG_PRINT(("QueryInterface failed %x", hr ));
        return hr;
    }

    // Enumerate watchers and populate list
    IRTCEnumWatchers * pEnum = NULL;
    IRTCWatcher * pWatcher = NULL;

    hr = pPresence->EnumerateWatchers(&pEnum);

    SAFE_RELEASE(pPresence);

    if (FAILED(hr))
    {
        // Enumerate watchers failed
        DEBUG_PRINT(("EnumerateWatchers failed %x", hr ));
        return hr;
    }

    while (pEnum->Next(1, &pWatcher, NULL) == S_OK)
    {
        // Update the watcher list entry
        UpdateWatcherList(pWatcher);

        SAFE_RELEASE(pWatcher);
    }

    SAFE_RELEASE(pEnum);

	////////////
	//
	// End RTC Functionality Code
	//
	////////////

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWatcher::DoAddWatcher
// 

HRESULT CRTCWatcher::DoAddWatcher(BSTR bstrURI, BSTR bstrName, RTC_WATCHER_STATE enState)
{
    HRESULT hr;

	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates Adding a watcher
	//
	////////////

    // Get the RTC client presence interface
    IRTCClientPresence2 * pPresence = NULL;

    hr = m_pClient->QueryInterface(
            __uuidof(IRTCClientPresence2),
            (void **)&pPresence);

    if (FAILED(hr))
    {
        // QueryInterface failed
        return hr;
    }

    // Add the watcher
    IRTCWatcher2 * pWatcher = NULL;

    hr = pPresence->AddWatcherEx(
            bstrURI,
            bstrName,
            NULL,
            enState,
            VARIANT_TRUE,
            RTCAS_SCOPE_USER,
            NULL,
            0,
            &pWatcher);

    SAFE_RELEASE(pPresence);

    if (FAILED(hr))
    {
        // AddWatcherEx failed 
        DEBUG_PRINT(("AddWatcherEx failed %x", hr ));
        return hr;
    }

    if (pWatcher)
    {
        // Update the watcher list entry
        UpdateWatcherList(pWatcher);
        SAFE_RELEASE(pWatcher);
    }

	////////////
	//
	// End RTC Functionality Code
	//
	////////////

	return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWatcher::DoRemoveWatcher
// 

HRESULT CRTCWatcher::DoRemoveWatcher(IRTCWatcher *pWatcher)
{
    HRESULT hr;

	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates Removing a watcher
	//
	////////////

    // Get the RTC client presence interface
    IRTCClientPresence * pPresence = NULL;

    hr = m_pClient->QueryInterface(
            __uuidof(IRTCClientPresence),
            (void **)&pPresence);

    if (FAILED(hr))
    {
        // QueryInterface failed
        DEBUG_PRINT(("QueryInterface failed %x", hr ));
        return hr;
    }

    // Remove the watcher
    hr = pPresence->RemoveWatcher(pWatcher);

    SAFE_RELEASE(pPresence);

    if (FAILED(hr))
    {
        // RemoveWatcher failed
        DEBUG_PRINT(("RemoveWatcher failed %x", hr ));
        return hr;
    }

	////////////
	//
	// End RTC Functionality Code
	//
	////////////

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWatcher::DoSetWatcherState
// 

HRESULT CRTCWatcher::DoSetWatcherState(IRTCWatcher *pWatcher, RTC_WATCHER_STATE enState)
{
    HRESULT hr;
	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates Setting a watcher's state.
	//
	////////////

	assert (pWatcher != NULL);

	if (pWatcher == NULL)
	{
		return E_POINTER;
	}

    hr = pWatcher->put_State(enState);
    
    if (FAILED(hr))
    {
        // put_State failed
        DEBUG_PRINT(("put_State failed %x", hr ));
        return hr;
    }

	////////////
	//
	// End RTC Functionality Code
	//
	////////////

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWatcher::WindowProc
// 

LRESULT CALLBACK CRTCWatcher::WindowProc(
  HWND hWnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
    CRTCWatcher * me = NULL;
    LRESULT  lr = 0;

    if ( uMsg == WM_CREATE )
    {
        // Create an instance of the class
        me = new CRTCWatcher;
        if(!me)
        {
            // Failed to create the instance
            return -1;
        }

        me->m_hWnd = hWnd;

        // Store the class instance pointer in the
        // window's user data for later retrieval
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)me);
       
        lr = me->OnCreate(uMsg, wParam, lParam);
    }
    else
    {
        // Retrieve the class instance pointer from the
        // window's user data
        me = (CRTCWatcher *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

        switch( uMsg )
        {        
        case WM_DESTROY:
            lr = me->OnDestroy(uMsg, wParam, lParam);

            // Delete the object instance
            delete me;
            break;

        case WM_CLOSE:
            lr = me->OnClose(uMsg, wParam, lParam);
            break;

        case WM_SIZE:
            lr = me->OnSize(uMsg, wParam, lParam);
            break;

        case WM_COMMAND:
            lr = me->OnCommand(uMsg, wParam, lParam);
            break;

        case WM_NOTIFY:
            lr = me->OnNotify(uMsg, wParam, lParam);
            break;

        case WM_POPULATE:
            me->PopulateWatcherList();
            break;
      
        default:
            lr = DefWindowProc( hWnd, uMsg, wParam, lParam );
        }
    }

    return lr;
}

/////////////////////////////////////////////
//
// CRTCWatcher::OnCreate
// 

LRESULT CRTCWatcher::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	// WM_CREATE has three parameters. We will pass them to our Create Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);


    // Create the watcher list
    m_hWatcherList = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"SysListView32",
        NULL,
        WS_CHILD | WS_VISIBLE |
        LVS_SINGLESEL | LVS_SORTASCENDING |
        LVS_AUTOARRANGE | LVS_SMALLICON,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_WATCHERLIST,
        GetModuleHandle(NULL),
        NULL);

    if ( !m_hWatcherList )
    {
        // CreateWindowExW failed
        DEBUG_PRINT(("CreateWindowExW failed %x",
            HRESULT_FROM_WIN32(GetLastError()) ));
        return -1;
    }

    PostMessage(m_hWnd, WM_POPULATE, 0, 0);

    return 0;
}

/////////////////////////////////////////////
//
// CRTCWatcher::OnDestroy
// 

LRESULT CRTCWatcher::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam)
{  
	// WM_DESTROY has three parameters. We will pass them to our Destroy Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);

    // Cleanup the watcher list
    ClearWatcherList();

    // Release the RTC client
    SAFE_RELEASE(m_pClient);

    if (m_pWin)
    {
        // Remove the window from the watchers list
        m_pWin->RemoveWatchers(this);
    }

    return 0;
}

/////////////////////////////////////////////
//
// CRTCWatcher::OnClose
// 

LRESULT CRTCWatcher::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// WM_CLOSE has three parameters. We will pass them to our Close Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);


    DestroyWindow(m_hWnd);

    return 0;
}

/////////////////////////////////////////////
//
// CRTCWatcher::OnSize
// 

LRESULT CRTCWatcher::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// WM_SIZE has three parameters. We will pass them to our Size Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);

    RECT rcWnd, rcWatcherList;

    const int SIZE_EDGE = 5;

    GetClientRect(m_hWnd, &rcWnd);

    // Resize the watcher list
    rcWatcherList.bottom = rcWnd.bottom - SIZE_EDGE;
    rcWatcherList.top = rcWnd.top + SIZE_EDGE;
    rcWatcherList.right = rcWnd.right - SIZE_EDGE;
    rcWatcherList.left = rcWnd.left + SIZE_EDGE;
    
    MoveWindow(
        m_hWatcherList,
        rcWatcherList.left,
        rcWatcherList.top,
        (rcWatcherList.right - rcWatcherList.left),
        (rcWatcherList.bottom - rcWatcherList.top),
        TRUE);

    SendMessage(m_hWatcherList, LVM_SETCOLUMNWIDTH,
        (WPARAM)0, MAKELPARAM(rcWatcherList.right - rcWatcherList.left,0));

    return 0;
}

/////////////////////////////////////////////
//
// CRTCWatcher::OnCommand
// 

LRESULT CRTCWatcher::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// WM_CREATE has three parameters. We will pass them to our Create Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);


    HRESULT hr = S_OK;

    switch(LOWORD(wParam))
    {
    case ID_FILE_EXIT:
        PostMessage(m_hWnd, WM_CLOSE, 0, 0);
        break;

    case ID_ACTION_ADDWATCHER:
        {
            DEBUG_PRINT(("ID_ACTION_ADDWATCHER"));
            BSTR bstrURI = NULL;
            BSTR bstrName = NULL;

            // Show the add watcher dialog
            hr = ShowAddressDialog(m_hWnd, L"Add Watcher", &bstrURI, &bstrName);

            if (FAILED(hr))
            {
                // ShowAddressDialog failed
                DEBUG_PRINT(("ShowAddressDialog failed %x", hr ));
                break;
            }
        
            // Add the watcher
            DoAddWatcher(bstrURI, bstrName, RTCWS_ALLOWED);

            SAFE_FREE_STRING(bstrURI);
            SAFE_FREE_STRING(bstrName);
        }
        break;
    }

    return hr;
}

/////////////////////////////////////////////
//
// CRTCWatcher::OnNotify
// 

LRESULT CRTCWatcher::OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam)
{    
	// WM_NOTIFY has three parameters. We will pass them to our Notify Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(uMsg);


    int idCtrl = (int)wParam;
    LPNMHDR pnmh = (LPNMHDR)lParam;
    HRESULT hr = S_OK;

    if ( (pnmh->code == NM_CLICK) ||
         (pnmh->code == NM_RCLICK) )
    {
        if ( idCtrl == IDC_WATCHERLIST )
        {
            // The user clicked on the watcher list
            LVHITTESTINFO lvht;
            ZeroMemory(&lvht, sizeof(LVHITTESTINFO));

            POINT pt;
            GetCursorPos(&pt);

            lvht.pt = pt;
            MapWindowPoints(NULL, pnmh->hwndFrom, &lvht.pt, 1 );
            
            int iRes = ListView_HitTest(pnmh->hwndFrom, &lvht);

            if (iRes == -1)
            {
                // ListView_HitTest failed
                return 0;
            }

            if (lvht.flags & LVHT_ONITEM)
            {
                // The user clicked on a watcher
                LVITEM lvi;
                ZeroMemory(&lvi, sizeof(LVITEM));
    
                lvi.mask = LVIF_PARAM;
                lvi.iItem = iRes;

                // Get the watcher item
                if (!ListView_GetItem(m_hWatcherList, &lvi))
                {
                    // ListView_GetItem failed;
                    return 0;
                }
                
                IRTCWatcher * pWatcher = (IRTCWatcher *)(lvi.lParam);

                // Show the watcher menu
                HMENU hMenuRes = LoadMenu( 
                    GetModuleHandle(NULL),
                    MAKEINTRESOURCE(IDR_MENU_WATCHER));

                HMENU hMenu = GetSubMenu(hMenuRes, 0);

                // Show the popup menu
                UINT uID = TrackPopupMenu(hMenu,
                    TPM_LEFTALIGN | TPM_RIGHTBUTTON |
                    TPM_NONOTIFY | TPM_RETURNCMD,
                    pt.x, pt.y, 0, m_hWnd, NULL);

                switch (uID)
                {
                case ID_WATCHER_ALLOW:
                    DEBUG_PRINT(("ID_WATCHER_ALLOW"));
                    // Allow the watcher
                    DoSetWatcherState(pWatcher, RTCWS_ALLOWED);
                    break;

                case ID_WATCHER_BLOCK:
                    DEBUG_PRINT(("ID_WATCHER_BLOCK"));
                    // Block the watcher
                    DoSetWatcherState(pWatcher, RTCWS_BLOCKED);
                    break;

                case ID_WATCHER_DENY:
                    DEBUG_PRINT(("ID_WATCHER_DENY"));
                    // Block the watcher
                    DoSetWatcherState(pWatcher, RTCWS_DENIED);
                    break;

                case ID_WATCHER_PROMPT:
                    DEBUG_PRINT(("ID_WATCHER_PROMPT"));
                    // Prompt the watcher
                    DoSetWatcherState(pWatcher, RTCWS_PROMPT);
                    break;

                case ID_WATCHER_REMOVE:
                    DEBUG_PRINT(("ID_WATCHER_REMOVE"));
                    // Remove the watcher
                    if (SUCCEEDED(DoRemoveWatcher(pWatcher)))
                    {                    
                        // Release the watcher reference
                        SAFE_RELEASE(pWatcher);

                        // Delete the watcher from the list
                        ListView_DeleteItem(m_hWatcherList, iRes);
                    }
                    break;
                }
            }
        }
    }

    return hr;
}

/////////////////////////////////////////////
//
// CRTCWatcher::DeliverWatcher
// 

HRESULT CRTCWatcher::DeliverWatcher(IRTCWatcher * pWatcher, RTC_WATCHER_EVENT_TYPE enType, LONG lStatus)
{
    switch (enType)
    {
    case RTCWET_WATCHER_ADD:
        {
            if (SUCCEEDED(lStatus))
            {
                // Update the watcher list entry
                UpdateWatcherList(pWatcher);
            }
            else
            {
                // Delete the watcher from the list
                ClearWatcherList(pWatcher);
            }
        }
        break;

    case RTCWET_WATCHER_REMOVE:
        {
            if (SUCCEEDED(lStatus))
            {
                // Delete the watcher from the list
                ClearWatcherList(pWatcher);
            }
            else
            {
                // Update the watcher list entry
                UpdateWatcherList(pWatcher);
            }
        }
        break;

    case RTCWET_WATCHER_UPDATE:
        {
            // Update the wathcer list entry
            UpdateWatcherList(pWatcher);
        }
        break;
    }

    return S_OK;
}
