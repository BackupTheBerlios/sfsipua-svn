// rtcwin.h
//

#include "stdafx.h"
#include <assert.h>

#define MAX_COMPUTER_NAME_LENGTH 300

/////////////////////////////////////////////
//
// CRTCWin::CRTCWin
// 


CRTCWin::CRTCWin()
{
    m_hWnd = NULL;
    m_hStatusBar = NULL;
	m_hBuddyTree = NULL;
	m_hOfflineParent = NULL;
	m_hOnlineParent = NULL;
    m_pClient = NULL;
    m_pProfile = NULL;
    m_pEvents = NULL;
    m_enState = RTCRS_NOT_REGISTERED;
    m_fPresenceEnabled = FALSE;
    m_lCookie = 0;
	m_nLogonAttemptCount = 0;

	ZeroMemory((void *)&m_OD, sizeof(OPTIONS_DATA));

}

/////////////////////////////////////////////
//
// CRTCWin::~CRTCWin
// 

CRTCWin::~CRTCWin()
{

	if(m_OD.bstrAppName) 
		SysFreeString(m_OD.bstrAppName);

	if(m_OD.bstrAppVer)
		SysFreeString(m_OD.bstrAppVer);

}

/////////////////////////////////////////////
//
// CRTCWin::RegisterClass
//

HRESULT CRTCWin::RegisterClass()
{
    // Register the window class
    WNDCLASS wc;
    ATOM atom;

    ZeroMemory(&wc, sizeof(WNDCLASS));

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)CRTCWin::WindowProc;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.hIcon         = NULL;
    wc.hCursor       =
        LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = 
        GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU_APP);
    wc.lpszClassName = APP_CLASS;

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
// CRTCWin::AddSession
//

HRESULT CRTCWin::AddSession(IRTCSession * pSession, RTC_SESSION_TYPE enType)
{
    // Is this an audio/video session?
    BOOL fAVSession = (enType == RTCST_PC_TO_PC || enType == RTCST_PC_TO_PHONE);    

    // Create the session window
    HWND hWnd;
    HRESULT hr = S_OK;

    hWnd = CreateWindowExW(
                0,
                (fAVSession) ? AV_CLASS : IM_CLASS,
                (fAVSession) ? AV_TITLE : IM_TITLE,
                WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                CW_USEDEFAULT, CW_USEDEFAULT,
                (fAVSession) ? AV_WIDTH : IM_WIDTH,
                (fAVSession) ? AV_HEIGHT : IM_HEIGHT,
                NULL,
                NULL,
                GetModuleHandle(NULL),
                NULL);    

    if ( !hWnd )
    {  
        // CreateWindowExW failed
        DEBUG_PRINT(("CreateWindowExW failed %x",
            HRESULT_FROM_WIN32(GetLastError()) ));
        return E_FAIL;
    }

    // Initialize the window
    CRTCSession * pSessWindow = 
        (CRTCSession *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    pSessWindow->m_pSession = pSession;
    pSessWindow->m_pSession->AddRef();
    pSessWindow->m_pWin = this;

    // Make the main window visible
    ShowWindow( hWnd, SW_SHOW );
    UpdateWindow( hWnd );

    // Add window to the list
    m_SessionList.push_back(pSessWindow);

    return hr;
}

/////////////////////////////////////////////
//
// CRTCWin::RemoveSession
//

HRESULT CRTCWin::RemoveSession(CRTCSession * pSessWindow)
{
    std::vector<CRTCSession *>::iterator it;
    
    if (!m_SessionList.empty())
    {
        // Find the window
        for(it=m_SessionList.begin();
            it < m_SessionList.end();
            it++)
        {
            if (*it == pSessWindow)
            {
                // Remove the window
                m_SessionList.erase(it);
                break;
            }
        }
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::FindSession
//

HRESULT CRTCWin::FindSession(IRTCSession * pSession,
                    CRTCSession ** ppSessWindow)
{
    std::vector<CRTCSession *>::iterator it;     

    if (!m_SessionList.empty())
    {
        for(it=m_SessionList.begin();
            it < m_SessionList.end();
            it++)
        {
            if ((*it)->m_pSession == pSession)
            {
                *ppSessWindow = (*it);         
                return S_OK;
            }
        }
    }

    *ppSessWindow = NULL;
    return E_FAIL;
}

/////////////////////////////////////////////
//
// CRTCWin::CleanupSessions
//

HRESULT CRTCWin::CleanupSessions()
{
    std::vector<CRTCSession *>::iterator it;     

    if (!m_SessionList.empty())
    {
        for(it=m_SessionList.begin();
            it < m_SessionList.end();
            it++)
        {
            PostMessage((*it)->m_hWnd, WM_CLOSE, 0, 0);
        }
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::AddUserSearch
//

HRESULT CRTCWin::AddUserSearch()
{
    HRESULT hr;

    // Get the user search interface
    IRTCUserSearch * pUserSearch = NULL;

    hr = m_pClient->QueryInterface(__uuidof(IRTCUserSearch), (void **)&pUserSearch);

    if (FAILED(hr))
    {
        // QueryInterface failed
        DEBUG_PRINT(("QueryInterface failed %x", hr ));
        return hr;
    }

    // Create the search window
    HWND hWnd;

    hWnd = CreateWindowExW(
                0,
                US_CLASS,
                US_TITLE,
                WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                CW_USEDEFAULT, CW_USEDEFAULT,
                US_WIDTH,
                US_HEIGHT,
                NULL,
                NULL,
                GetModuleHandle(NULL),
                NULL);    

    if ( !hWnd )
    {  
        // CreateWindowExW failed
        DEBUG_PRINT(("CreateWindowExW failed %x",
            HRESULT_FROM_WIN32(GetLastError()) ));
        SAFE_RELEASE(pUserSearch);
        return E_FAIL;
    }

    // Initialize the window
    CRTCSearch * pSearchWindow = 
        (CRTCSearch *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    pSearchWindow->m_pProfile = m_pProfile;
    pSearchWindow->m_pProfile->AddRef();

    // Give the user search reference to the search window
    pSearchWindow->m_pUserSearch = pUserSearch;
    pSearchWindow->m_pWin = this;

    // Make the search window visible
    ShowWindow( hWnd, SW_SHOW );
    UpdateWindow( hWnd );

    // Add window to the list
    m_UserSearchList.push_back(pSearchWindow);

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::RemoveUserSearch
//

HRESULT CRTCWin::RemoveUserSearch(CRTCSearch * pSearchWindow)
{
    std::vector<CRTCSearch *>::iterator it;
    
    if (!m_UserSearchList.empty())
    {
        // Find the window
        for(it=m_UserSearchList.begin();
            it < m_UserSearchList.end();
            it++)
        {
            if (*it == pSearchWindow)
            {
                // Remove the window
                m_UserSearchList.erase(it);
                break;
            }
        }
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::FindUserSearch
//

HRESULT CRTCWin::FindUserSearch(LONG_PTR lCookie,
                    CRTCSearch ** ppSearchWindow)
{
    std::vector<CRTCSearch *>::iterator it;     

    if (!m_UserSearchList.empty())
    {
        for(it=m_UserSearchList.begin();
            it < m_UserSearchList.end();
            it++)
        {
            if ((*it)->m_lCookie == lCookie)
            {
                *ppSearchWindow = (*it);         
                return S_OK;
            }
        }
    }

    *ppSearchWindow = NULL;
    return E_FAIL;
}

/////////////////////////////////////////////
//
// CRTCWin::CleanupUserSearches
//

HRESULT CRTCWin::CleanupUserSearches()
{
    std::vector<CRTCSearch *>::iterator it;     

    if (!m_UserSearchList.empty())
    {
        for(it=m_UserSearchList.begin();
            it < m_UserSearchList.end();
            it++)
        {
            PostMessage((*it)->m_hWnd, WM_CLOSE, 0, 0);
        }
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::AddWatchers
//

HRESULT CRTCWin::AddWatchers()
{
    HRESULT hr = S_OK;

    // Create the watchers window
    HWND hWnd;

    hWnd = CreateWindowExW(
                0,
                WAT_CLASS,
                WAT_TITLE,
                WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                CW_USEDEFAULT, CW_USEDEFAULT,
                WAT_WIDTH,
                WAT_HEIGHT,
                NULL,
                NULL,
                GetModuleHandle(NULL),
                NULL);    

    if ( !hWnd )
    {  
        // CreateWindowExW failed
        DEBUG_PRINT(("CreateWindowExW failed %x",
            HRESULT_FROM_WIN32(GetLastError()) ));
        return E_FAIL;
    }

    // Initialize the window
    CRTCWatcher * pWatcherWindow = 
        (CRTCWatcher *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    pWatcherWindow->m_pClient = m_pClient;
    pWatcherWindow->m_pClient->AddRef();

    pWatcherWindow->m_pWin = this;

    // Make the watcher window visible
    ShowWindow( hWnd, SW_SHOW );
    UpdateWindow( hWnd );

    // Add window to the list
    m_WatchersList.push_back(pWatcherWindow);

    return hr;
}

/////////////////////////////////////////////
//
// CRTCWin::RemoveWatchers
//

HRESULT CRTCWin::RemoveWatchers(CRTCWatcher * pWatcherWindow)
{
    std::vector<CRTCWatcher *>::iterator it;
    
    if (!m_WatchersList.empty())
    {
        // Find the window
        for(it=m_WatchersList.begin();
            it < m_WatchersList.end();
            it++)
        {
            if (*it == pWatcherWindow)
            {
                // Remove the window
                m_WatchersList.erase(it);
                break;
            }
        }
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::CleanupWatchers
//

HRESULT CRTCWin::CleanupWatchers()
{
    std::vector<CRTCWatcher *>::iterator it;     

    if (!m_WatchersList.empty())
    {
        for(it=m_WatchersList.begin();
            it < m_WatchersList.end();
            it++)
        {
            PostMessage((*it)->m_hWnd, WM_CLOSE, 0, 0);
        }
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::AddGroups
//

HRESULT CRTCWin::AddGroups()
{
    HRESULT hr = S_OK;

    // Create the groups window
    HWND hWnd;

    hWnd = CreateWindowExW(
                0,
                GRP_CLASS,
                GRP_TITLE,
                WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                CW_USEDEFAULT, CW_USEDEFAULT,
                GRP_WIDTH,
                GRP_HEIGHT,
                NULL,
                NULL,
                GetModuleHandle(NULL),
                NULL);    

    if ( !hWnd )
    {  
        // CreateWindowExW failed
        DEBUG_PRINT(("CreateWindowExW failed %x",
            HRESULT_FROM_WIN32(GetLastError()) ));
        return E_FAIL;
    }

    // Initialize the window
    CRTCGroup * pGroupWindow = 
        (CRTCGroup *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    pGroupWindow->m_pClient = m_pClient;
    pGroupWindow->m_pClient->AddRef();

    pGroupWindow->m_pWin = this;

    // Make the group window visible
    ShowWindow( hWnd, SW_SHOW );
    UpdateWindow( hWnd );

    // Add window to the list
    m_GroupsList.push_back(pGroupWindow);

    return hr;
}

/////////////////////////////////////////////
//
// CRTCWin::RemoveGroups
//

HRESULT CRTCWin::RemoveGroups(CRTCGroup * pGroupWindow)
{
    std::vector<CRTCGroup *>::iterator it;
    
    if (!m_GroupsList.empty())
    {
        // Find the window
        for(it=m_GroupsList.begin();
            it < m_GroupsList.end();
            it++)
        {
            if (*it == pGroupWindow)
            {
                // Remove the window
                m_GroupsList.erase(it);
                break;
            }
        }
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::CleanupGroups
//

HRESULT CRTCWin::CleanupGroups()
{
    std::vector<CRTCGroup *>::iterator it;     

    if (!m_GroupsList.empty())
    {
        for(it=m_GroupsList.begin();
            it < m_GroupsList.end();
            it++)
        {
            PostMessage((*it)->m_hWnd, WM_CLOSE, 0, 0);
        }
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::ShowMessageBox
//

void CRTCWin::ShowMessageBox(PWSTR szText)
{
    MessageBoxW(m_hWnd, szText, APP_TITLE, MB_OK);
}

/////////////////////////////////////////////
//
// CRTCWin::SetStatusText
//

void CRTCWin::SetStatusText(PWSTR szText)
{
    SetWindowTextW(m_hStatusBar, szText);
    InvalidateRect(m_hStatusBar, NULL, FALSE);
}

/////////////////////////////////////////////
//
// CRTCWin::GetUserURI
//

HRESULT CRTCWin::GetUserURI(BSTR *pbstrURI)
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to query the profile or client for the local user URI
//
////////////



    HRESULT hr;

    if (m_pProfile != NULL)
    {
        // Get the user URI from the profile
        hr = m_pProfile->get_UserURI(pbstrURI);

        if (FAILED(hr))
        {
            // get_UserURI failed
            DEBUG_PRINT(("get_UserURI failed %x", hr ));
            return hr;
        }
    }
    else
    {
        // Get the user URI from the client
        hr = m_pClient->get_LocalUserURI(pbstrURI);

        if (FAILED(hr))
        {
            // get_LocalUserURI failed
            DEBUG_PRINT(("get_LocalUserURI failed %x", hr ));
            return hr;
        }
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
// CRTCWin::GetUserName
//

HRESULT CRTCWin::GetUserName(BSTR *pbstrName)
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to query the profile or client for the local user name
//
////////////

    HRESULT hr;

    if (m_pProfile != NULL)
    {
        // Get the user name from the profile
        hr = m_pProfile->get_UserName(pbstrName);

        if (FAILED(hr))
        {
            // get_UserName failed
            DEBUG_PRINT(("get_UserName failed %x", hr ));
            return hr;
        }
    }
    else
    {
        // Get the user name from the client
        hr = m_pClient->get_LocalUserName(pbstrName);

        if (FAILED(hr))
        {
            // get_LocalUserName failed
            DEBUG_PRINT(("get_LocalUserName failed %x", hr ));
            return hr;
        }
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
// CRTCWin::FindBuddyNode
//

HRESULT CRTCWin::TreeViewHelper_FindBuddyNode(IRTCBuddy * pBuddy, LPTVITEMEX pTvix, int *piTree)
{
	if (pTvix == NULL || piTree == NULL)
		return E_POINTER;


	// Make a local tvix so we don't worry about reference passing from a parameter.

	TVITEMEX tvix;
	ZeroMemory(&tvix, sizeof(TVITEMEX));
	ZeroMemory(pTvix, sizeof(TVITEMEX));

	// Start with searching the online tree

	HTREEITEM child;
	
	child = 	TreeView_GetNextItem(	m_hBuddyTree,
										m_hOnlineParent,
										TVGN_CHILD
									);

	tvix.hItem = child;
	tvix.mask = TVIF_PARAM;
	TreeView_GetItem(m_hBuddyTree, &tvix);

	while (child != NULL && tvix.lParam != (LPARAM) pBuddy)
	{
		child = 
		TreeView_GetNextItem(	m_hBuddyTree,
								child,
								TVGN_NEXT
							);

		tvix.hItem = child;
		tvix.mask = TVIF_PARAM;
		TreeView_GetItem(m_hBuddyTree, &tvix);
	}

	if (tvix.lParam == (LPARAM) pBuddy)
	{
		pTvix->hItem = child;
		pTvix->lParam = tvix.lParam;
		if (piTree)
		{
			*piTree = 1;
		}
		return S_OK;
	}

	// Not found in online tree. Search the offline tree

	child = 	TreeView_GetNextItem(	m_hBuddyTree,
										m_hOfflineParent,
										TVGN_CHILD
									);

	tvix.hItem = child;
	TreeView_GetItem(m_hBuddyTree, &tvix);

	while (child != NULL && tvix.lParam != (LPARAM) pBuddy)
	{
		child = 
		TreeView_GetNextItem(	m_hBuddyTree,
								child,
								TVGN_NEXT
							);
		tvix.hItem = child;
		tvix.mask = TVIF_PARAM;
		TreeView_GetItem(m_hBuddyTree, &tvix);
	}

	if (child != NULL && tvix.lParam == (LPARAM) pBuddy)
	{
		pTvix->hItem = child;
		pTvix->lParam = tvix.lParam;
		if (piTree)
		{
			*piTree = 0;
		}
		return S_OK;
	}

	return E_FAIL;


}

HRESULT CRTCWin::TreeViewHelper_InsertNode(IRTCBuddy * pBuddy, WCHAR * szBuddy, int enStatus)
{
	assert (pBuddy != NULL);

	if (pBuddy == NULL)
	{
		return E_POINTER;
	}

	TV_ITEM tviNewItem;
	ZeroMemory(&tviNewItem, sizeof(TV_ITEM));

	// Main item

	tviNewItem.mask = TVIF_PARAM | TVIF_TEXT;
	tviNewItem.pszText = szBuddy; 
	tviNewItem.lParam = (LPARAM)pBuddy;

	// Group into online or offline group? 

	TVINSERTSTRUCT tvis;
	ZeroMemory(&tvis, sizeof(TVINSERTSTRUCT));

	if (enStatus == (int) RTCXS_PRESENCE_OFFLINE)
	{
		tvis.hParent = (HTREEITEM) m_hOfflineParent;
	}
	else
	{
		tvis.hParent = (HTREEITEM) m_hOnlineParent;
	}


	tvis.hInsertAfter = TVI_SORT;
	tvis.item = tviNewItem;

	HTREEITEM hti = TreeView_InsertItem(m_hBuddyTree, &tvis);

    if (hti == NULL)
	{
            // TreeView_InsertItem failed
		DEBUG_PRINT(("TreeView_InsertItem failed %x",
		HRESULT_FROM_WIN32(GetLastError()) ));
		return E_FAIL;
	}

	// An RTC buddy reference will be kept by the list
    // Add the reference here
	pBuddy->AddRef();

	// Now Add all of the presence devices to the parent node if the buddy isn't offline
	if (enStatus == (int) RTCXS_PRESENCE_OFFLINE)
	{
		return S_OK;
	}


////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to enumerate the presence devices on a buddy
//
////////////


	IRTCEnumPresenceDevices* ppEnumDevices = NULL;

	IRTCBuddy2 *pBuddy2;
	pBuddy->QueryInterface(__uuidof(IRTCBuddy2), (LPVOID *)&pBuddy2);

	HRESULT hr = pBuddy2->EnumeratePresenceDevices(&ppEnumDevices);

	SAFE_RELEASE(pBuddy2);

	if (FAILED(hr))
	{
		DEBUG_PRINT(("InsertNode: pBuddy2->EnumeratePresenceDevices Failed %x",
				hr ));
		return E_FAIL;
	}
		
	ULONG celtFetched = 0;

	IRTCPresenceDevice *pDevice = NULL;
	int count = 1;

	for (; (hr = ppEnumDevices->Next(1, &pDevice, &celtFetched)) == S_OK;)
	{

		if (pDevice)
		{
			WCHAR buffer[MAX_STRING];

			RTC_PRESENCE_STATUS enDeviceStatus = RTCXS_PRESENCE_OFFLINE;
			BSTR deviceName;

			hr = pDevice->get_PresenceProperty(RTCPP_DEVICE_NAME, &deviceName);
			if (FAILED(hr))
			{
				if (RTC_E_NOT_EXIST != hr)
				{
					DEBUG_PRINT(("get device name Failed %x", hr));
				}
				WCHAR deviceNameBuffer[MAX_STRING];
				swprintf(deviceNameBuffer, L"Device # %d", count);
				deviceName = ::SysAllocString(deviceNameBuffer);
			}

			hr = pDevice->get_Status(&enDeviceStatus);
			if (FAILED(hr))
			{
				DEBUG_PRINT(("Device::get_Status Failed 0x%8x", hr));
			}
			
			switch (enDeviceStatus)
			{
				case RTCXS_PRESENCE_OFFLINE:
					_snwprintf(buffer, MAX_STRING, L"%s (Offline)", deviceName);
					break;
				case RTCXS_PRESENCE_ONLINE:
					_snwprintf(buffer, MAX_STRING, L"%s (Online)", deviceName);
					break;
				case RTCXS_PRESENCE_AWAY:
					_snwprintf(buffer, MAX_STRING, L"%s (Away)", deviceName);
					break;
				case RTCXS_PRESENCE_IDLE:
					_snwprintf(buffer, MAX_STRING, L"%s (Idle)", deviceName);
					break;
				case RTCXS_PRESENCE_BUSY:
					_snwprintf(buffer, MAX_STRING, L"%s (Busy)", deviceName);
					break;
				case RTCXS_PRESENCE_BE_RIGHT_BACK:
					_snwprintf(buffer, MAX_STRING, L"%s (Be right back)", deviceName);
					break;
				case RTCXS_PRESENCE_ON_THE_PHONE:
					_snwprintf(buffer, MAX_STRING, L"%s (On the phone)", deviceName);
					break;
				case RTCXS_PRESENCE_OUT_TO_LUNCH:
					_snwprintf(buffer, MAX_STRING, L"%s (Out to lunch)", deviceName);
					break;
				default:
					_snwprintf(buffer, MAX_STRING, L"%s ", deviceName);
					break;
			}
			
			count++;
			SAFE_RELEASE(pDevice);
			SAFE_FREE_STRING(deviceName);

			// Main item

			ZeroMemory(&tviNewItem, sizeof(TV_ITEM));
			tviNewItem.mask = TVIF_TEXT;
			tviNewItem.pszText = buffer; 

			// Insert struct

			ZeroMemory(&tvis, sizeof(TVINSERTSTRUCT));
			tvis.hParent = (HTREEITEM) hti;
			tvis.hInsertAfter = TVI_SORT;
			tvis.item = tviNewItem;

			HTREEITEM childhti = TreeView_InsertItem(m_hBuddyTree, &tvis);

			if (childhti == NULL)
			{
				// TreeView_InsertItem failed
				DEBUG_PRINT(("TreeView_InsertItem failed for child device %x",
				HRESULT_FROM_WIN32(GetLastError()) ));
			}


		}
	}

	TreeView_Expand(m_hBuddyTree, hti, TVE_EXPAND);

	SAFE_RELEASE(ppEnumDevices);

////////////
//
// End RTC Functionality Code
//
////////////


	return S_OK;
}

 

/////////////////////////////////////////////
//
// CRTCWin::UpdateBuddyList
//

HRESULT CRTCWin::UpdateBuddyList(IRTCBuddy * pBuddy)
{
    HRESULT hr;

    if (pBuddy == NULL)
    {
        return S_OK;
    }

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to read the display name, basic presence, and URI of a buddy
//
////////////

    // Get the buddy status
    RTC_PRESENCE_STATUS enStatus = RTCXS_PRESENCE_OFFLINE;

    hr = pBuddy->get_Status(&enStatus);
    if (FAILED(hr))
    {
        // get_Status failed
        DEBUG_PRINT(("Buddy::get_Status Failed 0x%8x", hr));
    }

    // Get the buddy name
    BSTR bstrName = NULL;

	IRTCBuddy2 *pBuddy2;
	pBuddy->QueryInterface(__uuidof(IRTCBuddy2), (LPVOID *)&pBuddy2);
    
    hr = pBuddy2->get_PresenceProperty(RTCPP_DISPLAYNAME, &bstrName);

	SAFE_RELEASE(pBuddy2);

    if (SUCCEEDED(hr) && !wcscmp(bstrName, L""))
    {
        // Treat an emptry string as a failure
        SAFE_FREE_STRING(bstrName);
        hr = E_FAIL;
    }

    if (FAILED(hr))
    {
        // get_Name failed, get the URI instead
        hr = pBuddy->get_PresentityURI(&bstrName);

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

    // Build a string for the main buddy node.
    WCHAR szBuddy[MAX_STRING];

    switch (enStatus)
    {
    case RTCXS_PRESENCE_OFFLINE:
        _snwprintf(szBuddy, MAX_STRING, L"%ws (Offline)", bstrName);
        break;
    case RTCXS_PRESENCE_ONLINE:
        _snwprintf(szBuddy, MAX_STRING, L"%ws (Online)", bstrName);
        break;
    case RTCXS_PRESENCE_AWAY:
        _snwprintf(szBuddy, MAX_STRING, L"%ws (Away)", bstrName);
        break;
    case RTCXS_PRESENCE_IDLE:
        _snwprintf(szBuddy, MAX_STRING, L"%ws (Idle)", bstrName);
        break;
    case RTCXS_PRESENCE_BUSY:
        _snwprintf(szBuddy, MAX_STRING, L"%ws (Busy)", bstrName);
        break;
    case RTCXS_PRESENCE_BE_RIGHT_BACK:
        _snwprintf(szBuddy, MAX_STRING, L"%ws (Be right back)", bstrName);
        break;
    case RTCXS_PRESENCE_ON_THE_PHONE:
        _snwprintf(szBuddy, MAX_STRING, L"%ws (On the phone)", bstrName);
        break;
    case RTCXS_PRESENCE_OUT_TO_LUNCH:
        _snwprintf(szBuddy, MAX_STRING, L"%ws (Out to lunch)", bstrName);
        break;
    default:
        _snwprintf(szBuddy, MAX_STRING, L"%ws", bstrName);
        break;
    }

    szBuddy[MAX_STRING-1] = L'\0';

    SAFE_FREE_STRING(bstrName);
    
	
    // Is the buddy in the tree?
	TVITEMEX tvix;
	int whichTree;

	ZeroMemory(&tvix, sizeof(TVITEMEX));

	HRESULT hFound = TreeViewHelper_FindBuddyNode(pBuddy, &tvix, &whichTree);

	if (hFound == E_FAIL)
    {
        // Buddy is not in the list
		// Create new TreeView Item

		TreeViewHelper_InsertNode(pBuddy, szBuddy, enStatus);
    }
    else
    {
		TreeView_DeleteItem(m_hBuddyTree, tvix.hItem);
		TreeViewHelper_InsertNode(pBuddy, szBuddy, enStatus);
			
		// Release the buddy reference
		SAFE_RELEASE(pBuddy);
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
// CRTCWin::ClearBuddyList
//

HRESULT CRTCWin::ClearBuddyList(IRTCBuddy * pBuddy)
{
    HRESULT hr;
    
    if (pBuddy == NULL)
    {
        return S_OK;
    }

	// Is the buddy in the tree?
	TVITEMEX tvix;
	ZeroMemory(&tvix, sizeof(TVITEMEX));
	int whichTree;

	hr = TreeViewHelper_FindBuddyNode(pBuddy, &tvix, &whichTree);

	if (hr == S_OK)
	{
		TreeView_DeleteItem(m_hBuddyTree, tvix.hItem);
		SAFE_RELEASE(pBuddy);
	}
	else
	{
		DEBUG_PRINT(("Buddy not in tree %x",
                HRESULT_FROM_WIN32(GetLastError()) ));
	}

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::ClearBuddyList
// 

HRESULT CRTCWin::ClearBuddyList()
{
	HTREEITEM child;
	TVITEMEX tvix;

	// Online Nodes

	child = TreeView_GetNextItem(m_hBuddyTree, m_hOnlineParent, TVGN_CHILD);

	while (child != NULL)
	{
		HTREEITEM temp;

		// Retrieve the item
		ZeroMemory(&tvix, sizeof(TVITEMEX));
		tvix.mask = TVIF_PARAM;
		tvix.hItem = child;
		TreeView_GetItem(m_hBuddyTree, &tvix);

		// Release the buddy
		IRTCBuddy *pBuddy = (IRTCBuddy *) tvix.lParam;
		if (pBuddy)
		{
			DEBUG_PRINT(("On: Clear Buddy Succeeded. "));
			SAFE_RELEASE(pBuddy);
		}
		else
		{
			DEBUG_PRINT(("Error, pBuddy == NULL. "));
		}

		// Delete the node and move on
		temp = TreeView_GetNextItem(m_hBuddyTree, child, TVGN_NEXT);
		TreeView_DeleteItem(m_hBuddyTree, child);
		child = temp;
	}

	child = TreeView_GetNextItem(m_hBuddyTree, m_hOfflineParent, TVGN_CHILD);

	while (child != NULL)
	{
		HTREEITEM temp;
		
		// Retrieve the item
		ZeroMemory(&tvix, sizeof(TVITEMEX));
		tvix.mask = TVIF_PARAM;
		tvix.hItem = child;
		TreeView_GetItem(m_hBuddyTree, &tvix);

		// Release the buddy
		IRTCBuddy *pBuddy = (IRTCBuddy *) tvix.lParam;
		if (pBuddy)
		{
			DEBUG_PRINT(("Off: Clear Buddy Succeeded. "));
			SAFE_RELEASE(pBuddy);
		}
		else
		{
			DEBUG_PRINT(("Error, pBuddy == NULL. "));
		}

		// Delete the node and move on
		temp = TreeView_GetNextItem(m_hBuddyTree, child, TVGN_NEXT);
		TreeView_DeleteItem(m_hBuddyTree, child);
		child = temp;
		
	}

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::PopulateBuddyList
// 

HRESULT CRTCWin::PopulateBuddyList()
{
    HRESULT hr;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to enumerate the current buddies 
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

    // Enumerate buddies and populate list
    IRTCEnumBuddies * pEnum = NULL;
    IRTCBuddy * pBuddy = NULL;

    hr = pPresence->EnumerateBuddies(&pEnum);

    SAFE_RELEASE(pPresence);

    if (FAILED(hr))
    {
        // Enumerate buddies failed
        DEBUG_PRINT(("EnumerateBuddies failed %x", hr ));
        return hr;
    }

    while (pEnum->Next(1, &pBuddy, NULL) == S_OK)
    {
        // Update the buddy list entry
        UpdateBuddyList(pBuddy);

        SAFE_RELEASE(pBuddy);
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
// CRTCWin::DoLogOn
// 

HRESULT CRTCWin::DoLogOn(BSTR bstrURI, BSTR bstrServer, BSTR bstrTransport)
{
    HRESULT hr;

    if (m_pProfile)
    {
        // Already logged on
        ShowMessageBox(L"Already logged on!");

        return S_FALSE;
    }

	m_nLogonAttemptCount = 0;

    hr = DoGetProfile(bstrURI, bstrServer, bstrTransport);

    if (FAILED(hr))
    {
        // DoGetProfile failed
        DEBUG_PRINT(("DoGetProfile failed %x", hr ));
        ShowMessageBox(L"Logon failed!");

        return hr;
    }

    SetStatusText(L"Finding server");

    // Enable/disable menu items
    HMENU hMenu = GetMenu(m_hWnd);

    EnableMenuItem(hMenu, ID_FILE_LOGON, MF_GRAYED);
    EnableMenuItem(hMenu, ID_FILE_LOGOFF, MF_GRAYED);

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::OnLoggingOn
// 

HRESULT CRTCWin::OnLoggingOn()
{
    SetStatusText(L"Logging on");

    // Enable/disable menu items
    HMENU hMenu = GetMenu(m_hWnd);

    EnableMenuItem(hMenu, ID_FILE_LOGON, MF_GRAYED);
    EnableMenuItem(hMenu, ID_FILE_LOGOFF, MF_ENABLED);

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::OnLoggedOn
// 

HRESULT CRTCWin::OnLoggedOn()
{
    HRESULT hr = S_OK;
    BSTR bstrURI = NULL;
    WCHAR szStatus[MAX_STRING];

    hr = GetUserURI(&bstrURI);

    if (FAILED(hr))
    {
        _snwprintf(szStatus, MAX_STRING, L"Logged on");
	szStatus[MAX_STRING - 1] = L'\0';
    }
    else
    {
        _snwprintf(szStatus, MAX_STRING, L"Logged on (%ws)", bstrURI);
	szStatus[MAX_STRING - 1] = L'\0';

        SAFE_FREE_STRING(bstrURI);
    }

    SetStatusText(szStatus);

    PopulateBuddyList();

    // Enable/disable menu items
    HMENU hMenu = GetMenu(m_hWnd);

    EnableMenuItem(hMenu, ID_FILE_LOGON, MF_GRAYED);
    EnableMenuItem(hMenu, ID_FILE_LOGOFF, MF_ENABLED);
    EnableMenuItem(hMenu, ID_ACTION_ADDBUDDY, MF_ENABLED);  
    EnableMenuItem(hMenu, ID_TOOLS_USERSEARCH, MF_ENABLED); 
    EnableMenuItem(hMenu, ID_TOOLS_WATCHERS, MF_ENABLED); 
    EnableMenuItem(hMenu, ID_TOOLS_GROUPS, MF_ENABLED); 

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::DoLogOff
// 

HRESULT CRTCWin::DoLogOff()
{
    HRESULT hr = S_OK;

    if (!m_pProfile)
    {
        // Already logged off
        OnLoggedOff();
        return S_OK;
    }

    // Disable profile
    DoEnableProfile(FALSE, 0, 0);

    SAFE_RELEASE(m_pProfile);

    return hr;
}

/////////////////////////////////////////////
//
// CRTCWin::OnLoggingOff
// 

HRESULT CRTCWin::OnLoggingOff()
{
    SetStatusText(L"Logging off");

    // Enable/disable menu items
    HMENU hMenu = GetMenu(m_hWnd);

    EnableMenuItem(hMenu, ID_FILE_LOGON, MF_GRAYED);
    EnableMenuItem(hMenu, ID_FILE_LOGOFF, MF_GRAYED);
    EnableMenuItem(hMenu, ID_ACTION_ADDBUDDY, MF_GRAYED);
    EnableMenuItem(hMenu, ID_TOOLS_USERSEARCH, MF_GRAYED);  
    EnableMenuItem(hMenu, ID_TOOLS_WATCHERS, MF_GRAYED); 
    EnableMenuItem(hMenu, ID_TOOLS_GROUPS, MF_GRAYED); 

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::OnLoggedOff
// 

HRESULT CRTCWin::OnLoggedOff()
{
    SetStatusText(L"Logged off");

    // Disable presence
    DoEnablePresence(FALSE);  

    // Cleanup the user search windows
    CleanupUserSearches();

    // Cleanup the watcher windows
    CleanupWatchers();

    // Cleanup the group windows
    CleanupGroups();

    // Enable/disable menu items
    HMENU hMenu = GetMenu(m_hWnd);

    EnableMenuItem(hMenu, ID_FILE_LOGON, MF_ENABLED);
    EnableMenuItem(hMenu, ID_FILE_LOGOFF, MF_GRAYED);
    EnableMenuItem(hMenu, ID_ACTION_ADDBUDDY, MF_GRAYED);
    EnableMenuItem(hMenu, ID_TOOLS_USERSEARCH, MF_GRAYED);  
    EnableMenuItem(hMenu, ID_TOOLS_WATCHERS, MF_GRAYED);
    EnableMenuItem(hMenu, ID_TOOLS_GROUPS, MF_GRAYED); 

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::DoGetProfile
// 

HRESULT CRTCWin::DoGetProfile(BSTR bstrURI, BSTR bstrServer, BSTR bstrTransport)
{
    HRESULT hr;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to get a profile based on server name, transport, account settings, and uri
//
////////////


    // Find transport 
    long lTransport = 0;

    if (bstrTransport != NULL)
    {
        if (!_wcsicmp(bstrTransport, L"UDP"))
        {
            lTransport = RTCTR_UDP;
        }
        else if (!_wcsicmp(bstrTransport, L"TCP"))
        {
            lTransport = RTCTR_TCP;
        }
        else if (!_wcsicmp(bstrTransport, L"TLS"))
        {
            lTransport = RTCTR_TLS;
        }
    }

    // Get the RTC client provisioning interface
    IRTCClientProvisioning2 * pProv = NULL;

    hr = m_pClient->QueryInterface(
            __uuidof(IRTCClientProvisioning2),
            (void **)&pProv);

    if (FAILED(hr))
    {
        // QueryInterface failed
        DEBUG_PRINT(("QueryInterface failed %x", hr ));
        return hr;
    }

    // Get the profile
    hr = pProv->GetProfile(
            NULL,           // bstrUserAccount
            NULL,           // bstrUserPassword
            bstrURI,        // bstrUserURI
            bstrServer,     // bstrServer
            lTransport,     // lTransport
            0               // lCookie
            );

    SAFE_RELEASE(pProv);

    if (FAILED(hr))
    {
        // GetProfile failed
        DEBUG_PRINT(("GetProfile failed %x", hr ));
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
// CRTCWin::DoEnableProfile
//

HRESULT CRTCWin::DoEnableProfile(BOOL fEnable, long lRegisterFlags, long lRoamingFlags)
{
    HRESULT hr;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to Enable a Profile (which you can create using GetProfile).
// This is called from DoRegister. We need to EnablePresenceEx first (which is done in DoRegister)
//
////////////


    // Get the RTC client provisioning interface
    IRTCClientProvisioning2 * pProv = NULL;

    hr = m_pClient->QueryInterface(
            __uuidof(IRTCClientProvisioning2),
            (void **)&pProv);

    if (FAILED(hr))
    {
        // QueryInterface failed
        DEBUG_PRINT(("QueryInterface failed %x", hr ));  
        return hr;
    }

    if (fEnable)
    {
        // Enable the RTC profile object
        hr = pProv->EnableProfileEx(m_pProfile, lRegisterFlags, lRoamingFlags);

        SAFE_RELEASE(pProv);

        if (FAILED(hr))
        {
            // EnableProfile failed
            DEBUG_PRINT(("EnableProfileEx failed %x", hr ));
            return hr;    
        }
    }
    else
    {
        // Disable the RTC profile object
        hr = pProv->DisableProfile(m_pProfile);

        SAFE_RELEASE(pProv);

        if (FAILED(hr))
        {
            // EnableProfile failed
            DEBUG_PRINT(("DisableProfile failed %x", hr ));
            return hr;    
        }
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
// CRTCWin::DoRegister
// 

HRESULT CRTCWin::DoRegister()
{
    HRESULT hr;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates the registration sequence. 
// We will call DoEnablePresence in order to Enable Presence on a Profile (this needs to be done in order to use presence features on the profile).
// We will then call DoEnableProfile in order to enable the profile and perform the actual registration.
//
////////////



    // Enable presence
    hr = DoEnablePresence(TRUE);

    if (FAILED(hr))
    {
        // DoEnablePresence failed
        DEBUG_PRINT(("DoEnablePresence failed %x", hr ));
        return hr;
    }

    // Enable the RTC profile object
    hr = DoEnableProfile(TRUE,
        RTCRF_REGISTER_ALL,
        RTCRMF_BUDDY_ROAMING |
        RTCRMF_WATCHER_ROAMING |
        RTCRMF_PRESENCE_ROAMING |
        RTCRMF_PROFILE_ROAMING
        );

    if (FAILED(hr))
    {
        // DoEnableProfile failed
        DEBUG_PRINT(("DoEnableProfile failed %x", hr ));
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
// CRTCWin::DoAuth
// 

HRESULT CRTCWin::DoAuth(BSTR bstrURI, BSTR bstrAccount, BSTR bstrPassword)
{
    HRESULT hr;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to set the credentials on a profile.
// This can be called from a Registration State Change event if the failure is due to invalid authentication.
//
////////////

    // Update the credentials in the profile
    hr = m_pProfile->SetCredentials(bstrURI, bstrAccount, bstrPassword);

    if (FAILED(hr))
    {
        // SetCredentials failed
        DEBUG_PRINT(("SetCredentials failed %x", hr ));
        return hr;
    }

    // Re-register
    hr = DoRegister();

    if (FAILED(hr))
    {
        // DoRegister failed
        DEBUG_PRINT(("DoRegister failed %x", hr ));
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
// CRTCWin::DoEnablePresence
// 

HRESULT CRTCWin::DoEnablePresence(BOOL fEnable)
{    

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates EnablePresenceEx on a Profile (which you can create using GetProfile).
// This is required before calling EnableProfileEx.
//
////////////

    IRTCClientPresence2 * pPresence = NULL;
    HRESULT hr;

    if (m_fPresenceEnabled == fEnable)
    {
        // Already in correct state
        return S_FALSE;
    }

    // Cleanup the buddy list
    ClearBuddyList();

    // Get the RTC client presence interface
    hr = m_pClient->QueryInterface(
            __uuidof(IRTCClientPresence2),
            (void **)&pPresence);

    if (FAILED(hr))
    {
        // QueryInterface failed
        return hr;
    }

    if (fEnable)
    {
        // Build the filename for presence storage
        // from the user URI
        VARIANT varStorage;
        VariantInit(&varStorage);
        varStorage.vt = VT_BSTR;  
        BSTR bstrURI = NULL;

        hr = m_pProfile->get_UserURI(&bstrURI);
        
        if (FAILED(hr))
        {
            // get_UserURI failed
            DEBUG_PRINT(("get_UserURI failed %x", hr ));
            SAFE_RELEASE(pPresence);
            return hr;
        }

        WCHAR * pch = bstrURI;
        size_t cch;
	cch  = wcslen(bstrURI) + wcslen(L"presence_.xml") + 1;

        while (*pch != L'\0')
        {
            // Replace all non-alphanumeric characters
            // in the URI with underscore
            if (!((*pch >= L'a') && (*pch <= L'z')) &&
                !((*pch >= L'A') && (*pch <= L'Z')) &&
                !((*pch >= L'0') && (*pch <= L'9')))
            {
                *pch = L'_';
            }

            pch++;
        }

        // Allocate space for the filename
        varStorage.bstrVal = SysAllocStringLen(NULL, (ULONG) cch);

        if (!varStorage.bstrVal)
        {
            // Out of memory
            DEBUG_PRINT(("Out of memory"));
            SAFE_RELEASE(pPresence);
            SAFE_FREE_STRING(bstrURI);
            return E_OUTOFMEMORY;
        }

        // Create the filename
        _snwprintf(varStorage.bstrVal, cch, L"presence_%ws.xml", bstrURI);
        SAFE_FREE_STRING(bstrURI);              
        
        // Enable presence
        hr = pPresence->EnablePresenceEx(m_pProfile, varStorage, 0);        
        VariantClear(&varStorage);

        if (FAILED(hr))
        {
            // EnablePresence failed
            DEBUG_PRINT(("EnablePresence failed %x", hr ));
            SAFE_RELEASE(pPresence);
            return hr;
        }

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to set a presence property for this particular device.
// We are going to set our device name to the computer name and then (RTCSampleT).
//
////////////


        // Set a presence property
        BSTR bstrPropName = SysAllocString(L"http://schemas.microsoft.com/rtc/rtcsample");
        BSTR bstrPropVal = SysAllocString(L"<name> rtcsample </rtcsample>");
        
        if (bstrPropName && bstrPropVal)
        {
		hr = pPresence->SetPresenceData(bstrPropName, bstrPropVal);

		if (FAILED(hr))
		{
			// SetPresenceData failed                        
			DEBUG_PRINT(("SetPresenceData failed %x", hr ));
		}
        }
		
	wchar_t wszCnBuffer[MAX_COMPUTER_NAME_LENGTH]; // Max computer name length is 256 I believe
	BOOL fSuccessComputerName = FALSE;
	DWORD dwLength = MAX_COMPUTER_NAME_LENGTH - 1;
	fSuccessComputerName = GetComputerNameW(wszCnBuffer, &dwLength);

	if (fSuccessComputerName)
	{
		#define SAMPLE_STR_SIZE 13
		// ( size of "(RTCSampleT)" + 1)

		int nSize = dwLength + 1 + SAMPLE_STR_SIZE + 1;
		wchar_t *wszNewDeviceName = new wchar_t[nSize];

		if (!wszNewDeviceName)
			return E_OUTOFMEMORY;

		wcscpy(wszNewDeviceName, wszCnBuffer);
		wcsncat(wszNewDeviceName, L" (RTCSampleT)", nSize - (wcslen(wszCnBuffer) + 1));

		BSTR bstrDeviceName = ::SysAllocString(wszNewDeviceName);
		delete [] wszNewDeviceName;

		hr = pPresence->put_PresenceProperty(RTCPP_DEVICE_NAME, bstrDeviceName);
		SAFE_FREE_STRING(bstrDeviceName);
	}

        SAFE_FREE_STRING(bstrPropName);
        SAFE_FREE_STRING(bstrPropVal);
        
    }
    else
    {
        // Disable presence
        hr = pPresence->DisablePresence();

        if (FAILED(hr))
        {
            // DisablePresence failed
            DEBUG_PRINT(("DisablePresence failed %x", hr ));
            SAFE_RELEASE(pPresence);
            return hr;
        }
    }

    // Set the enabled flag
    m_fPresenceEnabled = fEnable;

    SAFE_RELEASE(pPresence);

////////////
//
// End RTC Functionality Code
//
////////////

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCWin::DoAddBuddy
// 

HRESULT CRTCWin::DoAddBuddy(BSTR bstrURI, BSTR bstrName)
{
    HRESULT hr;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to Add a Buddy
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
        return hr;
    }

    // Add the buddy
    IRTCBuddy * pBuddy = NULL;

    hr = pPresence->AddBuddy(
            bstrURI,
            bstrName,
            NULL,
            VARIANT_TRUE,
            NULL,
            0,
            &pBuddy);

    SAFE_RELEASE(pPresence);

    if (FAILED(hr))
    {
        // AddBuddy failed 
        DEBUG_PRINT(("AddBuddy failed %x", hr ));
        return hr;
    }

    if (pBuddy)
    {
        // Update the buddy list entry
        UpdateBuddyList(pBuddy);
        SAFE_RELEASE(pBuddy);
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
// CRTCWin::DoRefreshBuddy
// 

HRESULT CRTCWin::DoRefreshBuddy(IRTCBuddy *pBuddy)
{
    HRESULT hr;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to refresh a buddy's presence.
//
////////////


    // Get the IRTCBuddy2 interface
    IRTCBuddy2 * pBuddy2 = NULL;

    hr = pBuddy->QueryInterface(
            __uuidof(IRTCBuddy2),
            (void **)&pBuddy2);

    if (FAILED(hr))
    {
        // QueryInterface failed
        return hr;
    }

    // Refresh the buddy
    hr = pBuddy2->Refresh();

    SAFE_RELEASE(pBuddy2);

    if (FAILED(hr))
    {
        // Refresh failed
        DEBUG_PRINT(("Refresh failed %x", hr ));
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
// CRTCWin::DoRemoveBuddy
// 

HRESULT CRTCWin::DoRemoveBuddy(IRTCBuddy *pBuddy)
{
    HRESULT hr;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to remove a buddy
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

    // Remove the buddy
    hr = pPresence->RemoveBuddy(pBuddy);

    SAFE_RELEASE(pPresence);

    if (FAILED(hr))
    {
        // RemoveBuddy failed
        DEBUG_PRINT(("RemoveBuddy failed %x", hr ));
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
// CRTCWin::DoCall
// 

HRESULT CRTCWin::DoCall(RTC_SESSION_TYPE enType, BSTR bstrURI, BSTR bstrName)
{
    HRESULT hr;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to Create a Session with another user
//
////////////

    if (enType == RTCST_PC_TO_PC || enType == RTCST_PC_TO_PHONE)
    {
        // Is there already an AV session? We can only
        // allow one at a time
        if (CRTCAVSession::m_Singleton != NULL)
        {
            ShowMessageBox(L"An audio/video call is in progress!");

            return S_FALSE;
        }

    }

    // Create the session
    IRTCSession * pSession = NULL;

    hr = m_pClient->CreateSession(
        enType,
        NULL,
        NULL,
        0,
        &pSession
        );

    if (FAILED(hr))
    {
        // CreateSession failed
        DEBUG_PRINT(("CreateSession failed %x", hr ));
        return hr;
    }


    // Add the participant to the session
    hr = pSession->AddParticipant(
        bstrURI,
        bstrName,
        NULL
        );

    if (FAILED(hr))
    {
        // AddParticipant failed
        DEBUG_PRINT(("AddParticipant failed %x", hr ));
        SAFE_RELEASE(pSession);
        return hr;
    }

    // Add the session to the session list
    // This will create the session window
    hr = AddSession(pSession, enType);
    
    SAFE_RELEASE(pSession);

    if (FAILED(hr))
    {  
        // AddSession failed   
        DEBUG_PRINT(("AddSession failed %x", hr ));
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
// CRTCWin::DoTuningWizard
// 

HRESULT CRTCWin::DoTuningWizard()
{
    HRESULT hr;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to invoke the tuning wizard
//
////////////

    // Is there already an AV session? We can only
    // allow one at a time
    if (CRTCAVSession::m_Singleton != NULL)
    {
        ShowMessageBox(L"An audio/video call is in progress!");

        return S_FALSE;
    }

    // Show the tuning wizard
    hr = m_pClient->InvokeTuningWizard((OAHWND)m_hWnd);

    if (FAILED(hr))
    {
        // InvokeTuningWizard failed
        DEBUG_PRINT(("InvokeTuningWizard failed %x", hr ));
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
// CRTCWin::DoSetPresence
// 

HRESULT CRTCWin::DoSetPresence(RTC_PRESENCE_STATUS enStatus)
{
    HRESULT hr;
    UINT id = 0;

    // Check the appropriate menu item
    switch(enStatus)
    {
    case RTCXS_PRESENCE_OFFLINE:
        id = ID_FILE_PRESENCESTATUS_OFFLINE;
        break;

    case RTCXS_PRESENCE_ONLINE:
        id = ID_FILE_PRESENCESTATUS_ONLINE;
        break;

    case RTCXS_PRESENCE_AWAY:
        id = ID_FILE_PRESENCESTATUS_AWAY;
        break;

    case RTCXS_PRESENCE_IDLE:
        id = ID_FILE_PRESENCESTATUS_IDLE;
        break;

    case RTCXS_PRESENCE_BUSY:
        id = ID_FILE_PRESENCESTATUS_BUSY;
        break;

    case RTCXS_PRESENCE_BE_RIGHT_BACK:
        id = ID_FILE_PRESENCESTATUS_BERIGHTBACK;
        break;

    case RTCXS_PRESENCE_ON_THE_PHONE:
        id = ID_FILE_PRESENCESTATUS_ONTHEPHONE;
        break;

    case RTCXS_PRESENCE_OUT_TO_LUNCH:
        id = ID_FILE_PRESENCESTATUS_OUTTOLUNCH;
        break;
    }

    CheckMenuRadioItem(
        GetMenu(m_hWnd),   // handle to menu
        ID_FILE_PRESENCESTATUS_OFFLINE,  // identifier or position of first item
        ID_FILE_PRESENCESTATUS_OUTTOLUNCH,   // identifier or position of last item
        id,  // identifier or position of menu item
        MF_BYCOMMAND    // function options
        );

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to set the presence for your device.
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

    // Set the local presence status
    hr = pPresence->SetLocalPresenceInfo(enStatus, NULL);

    SAFE_RELEASE(pPresence);

    if (FAILED(hr))
    {
        // SetLocalPresenceInfo failed
        DEBUG_PRINT(("SetLocalPresenceInfo failed %x", hr ));
        return hr;
    }

////////////
//
// End RTC Functionality Code
//
////////////

    return S_OK;
}


HRESULT CRTCWin::DoOptions()
{
	HRESULT hr = S_OK;
    LONG MaxlBW = 1000000;
    long lMediaType = 0;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to set the preferred security level, the preferred media types,
// the client name, the client version, the max bitrate, and the preferred security level.
//
////////////

	
	//Get the current security levels that are on the client.
	//We are going to display these.
	m_pClient->get_PreferredSecurityLevel(RTCSECT_AUDIO_VIDEO_MEDIA_ENCRYPTION,
										&m_OD.enAVLevel);

	m_pClient->get_PreferredSecurityLevel(RTCSECT_T120_MEDIA_ENCRYPTION,
										 &m_OD.enT120Level);


    // Get the media types from client and set the T120 option accordingly
    m_pClient->get_PreferredMediaTypes(&lMediaType);
    if ((lMediaType & RTCMT_T120_SENDRECV) == 0)
        m_OD.EnabledOptions &=  ~RTCWIN_OPTIONS_T120;
    else
        m_OD.EnabledOptions |= RTCWIN_OPTIONS_T120;


	//show the dialog box
	ShowOptionsDialog(m_hWnd, &m_OD);


	//The dialog box was displayed. Now start saving AppVersion
	m_pClient->put_ClientName(m_OD.bstrAppName);
	m_pClient->put_ClientCurVer(m_OD.bstrAppVer);


	//If the dialog box had the MaxBW option set, apply that.
	if(m_OD.EnabledOptions & RTCWIN_OPTIONS_MAXBW) {
		m_pClient->put_MaxBitrate(m_OD.lMaxBW);
    } else
		m_pClient->put_MaxBitrate(MaxlBW);

    //If the dialog box had the T120 option set, apply that.
    if(m_OD.EnabledOptions & RTCWIN_OPTIONS_T120)
        m_pClient->SetPreferredMediaTypes(lMediaType | RTCMT_T120_SENDRECV, FALSE);
    else
        m_pClient->SetPreferredMediaTypes(lMediaType & ~RTCMT_T120_SENDRECV, FALSE);
    
	
	//Apply the security levels as set in the Options dialog box
	m_pClient->put_PreferredSecurityLevel(RTCSECT_AUDIO_VIDEO_MEDIA_ENCRYPTION,
										  m_OD.enAVLevel);

	m_pClient->put_PreferredSecurityLevel(RTCSECT_T120_MEDIA_ENCRYPTION,
										  m_OD.enT120Level);

////////////
//
// End RTC Functionality Code
//
////////////
	
	return hr;
}



HRESULT	CRTCWin::DoBuddyProperties(IRTCBuddy *pBuddy)
{
	HRESULT hr = S_OK;

	IRTCBuddy2 *pBuddy2;

	pBuddy->QueryInterface(__uuidof(IRTCBuddy2),(LPVOID *)&pBuddy2);

	ShowBuddyPropertiesDialog(NULL,pBuddy2);

	SAFE_RELEASE(pBuddy2);

	return hr;

}


HRESULT CRTCWin::DoDTMFDialpad()
{

	return ShowDtmfDialpad(m_hWnd,m_pClient);

}



/////////////////////////////////////////////
//
// CRTCWin::WindowProc
// 

LRESULT CALLBACK CRTCWin::WindowProc(
  HWND hWnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
    CRTCWin * me = NULL;
    LRESULT  lr = 0;

    if ( uMsg == WM_CREATE )
    {
        // Create an instance of the class
        me = new CRTCWin;
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
        me = (CRTCWin *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

        switch( uMsg )
        {        
        case WM_DESTROY:
            lr = me->OnDestroy(uMsg, wParam, lParam);

            // Delete the object instance
            delete me;

            // Quit the application
            PostQuitMessage(0);
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

        case WM_RTC_EVENT:
            lr = me->OnRTCEvent(uMsg, wParam, lParam);
            break;
      
        default:
            lr = DefWindowProc( hWnd, uMsg, wParam, lParam );
        }
    }

    return lr;
}

/////////////////////////////////////////////
//
// CRTCWin::OnCreate
// 

LRESULT CRTCWin::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	// WM_CREATE has three parameters. We will pass them to our Create Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);


    // Create the status bar
    m_hStatusBar = CreateStatusWindow(
        WS_CHILD | WS_VISIBLE,
        NULL,
        m_hWnd,
        IDC_STATUSBAR
        );

    if ( !m_hStatusBar )
    {
        // CreateStatusWindow failed
        DEBUG_PRINT(("CreateStatusWindow failed %x",
            HRESULT_FROM_WIN32(GetLastError()) ));
        return -1;
    }

	// Create the buddy tree view
    m_hBuddyTree = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"SysTreeView32",
        NULL,
        WS_CHILD | WS_VISIBLE |
		TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_BUDDYTREE,
        GetModuleHandle(NULL),
        NULL);

    if ( !m_hBuddyTree )
    {
        // CreateWindowExW failed
        DEBUG_PRINT(("CreateWindowExW failed %x",
            HRESULT_FROM_WIN32(GetLastError()) ));
        return -1;
    }

	// Add online and offline groups

	TV_ITEM tviNewItem;
	ZeroMemory(&tviNewItem, sizeof(TV_ITEM));

	tviNewItem.mask = TVIF_TEXT;
	tviNewItem.pszText = L"Online";
	
    TVINSERTSTRUCT tvis;
	ZeroMemory(&tvis, sizeof(TVINSERTSTRUCT));

	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_ROOT;
	tvis.item = tviNewItem;

	HTREEITEM hti = TreeView_InsertItem(m_hBuddyTree, &tvis);

    if (hti == NULL)
    {
		// TreeView_InsertItem failed
		DEBUG_PRINT(("TreeView_InsertItem failed %x",
		HRESULT_FROM_WIN32(GetLastError()) ));
		return E_FAIL;
	}
	else
	{
		m_hOnlineParent = (HWND) hti;
	}

	ZeroMemory(&tviNewItem, sizeof(TV_ITEM));

	tviNewItem.mask = TVIF_TEXT;
	tviNewItem.pszText = L"Offline";
	
	ZeroMemory(&tvis, sizeof(TVINSERTSTRUCT));
    
	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_ROOT;
	tvis.item = tviNewItem;

	hti = TreeView_InsertItem(m_hBuddyTree, &tvis);

    if (hti == NULL)
    {
		// TreeView_InsertItem failed
		DEBUG_PRINT(("TreeView_InsertItem failed %x",
		HRESULT_FROM_WIN32(GetLastError()) ));
		return E_FAIL;
	}
	else
	{
		m_hOfflineParent = (HWND) hti;
	}

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to create an RTC Client object and query its version,
// Initialize the client, set its event filter for the events we are interested in,
// set the listen mode, and attach the event sink.
//
////////////


    // Create the RTC client
    HRESULT hr;

    hr = CoCreateInstance(
        __uuidof(RTCClient),
        NULL,
        CLSCTX_INPROC_SERVER,
        __uuidof(IRTCClient2),
        (LPVOID *)&m_pClient
        );

    if (FAILED(hr))
    {
        // CoCreateInstance failed
        DEBUG_PRINT(("CoCreateInstance failed %x", hr ));
        ShowMessageBox(L"RTC Client v1.1 or higher required!");
        return -1;
    }

    long lVersion;

#ifdef _PREFAST_
    // If CoCreateInstance() succeeds, m_pClient cannot be NULL
    __assume(NULL != m_pClient);
#endif //_PREFAST_

    hr = m_pClient->get_Version(&lVersion);

    if (FAILED(hr))
    {
        // get_Version failed
        DEBUG_PRINT(("get_Version failed %x", hr ));
        ShowMessageBox(L"RTC Client v1.1 or higher required!");
        return -1;
    }

    if (lVersion < 0x00010002)
    {
        // Unsupported RTCDLL version
        DEBUG_PRINT(("Unsupported RTCDLL version"));
        ShowMessageBox(L"RTC Client v1.2 or higher required!");
        return -1;
    }

    // Initialize the RTC client
    hr = m_pClient->Initialize();

    if (FAILED(hr))
    {
        // Initialize failed
        DEBUG_PRINT(("Initialize failed %x", hr ));
        SAFE_RELEASE(m_pClient);
        return -1;
    }

    // Determine the event filter
    long lFlags = RTCEF_REGISTRATION_STATE_CHANGE |
                  RTCEF_SESSION_STATE_CHANGE |
                  RTCEF_PARTICIPANT_STATE_CHANGE |
                  RTCEF_MESSAGING |
                  RTCEF_MEDIA |
                  RTCEF_INTENSITY |
                  RTCEF_CLIENT |
                  RTCEF_BUDDY |
                  RTCEF_BUDDY2 |
                  RTCEF_WATCHER |
                  RTCEF_WATCHER2 |
                  RTCEF_GROUP |
                  RTCEF_USERSEARCH |
                  RTCEF_ROAMING |
                  RTCEF_PROFILE |
                  RTCEF_PRESENCE_PROPERTY | 
                  RTCEF_PRESENCE_DATA | 
				  RTCE_MEDIA_REQUEST;

    // Set the event filter for the RTC client
    hr = m_pClient->put_EventFilter(lFlags);

    if ( FAILED(hr) )
    {
        // put_EventFilter failed
        DEBUG_PRINT(("put_EventFilter failed %x", hr ));
        SAFE_RELEASE(m_pClient);
        return -1;
    }

    // Set the listen mode for RTC client
    // RTCLM_BOTH opens the standard SIP port 5060, as well as
    // a dynamic port.
    
	hr = m_pClient->put_AllowedPorts(RTCTR_TCP, RTCLM_BOTH);
	if ( FAILED(hr) )
    {
        // put_ListenMode failed
        DEBUG_PRINT(("put_AllowedPorts (RTCTR_TCP) failed %x", hr ));
        SAFE_RELEASE(m_pClient);
        return -1;
    }

	hr = m_pClient->put_AllowedPorts(RTCTR_UDP, RTCLM_BOTH);
    if ( FAILED(hr) )
    {
        // put_ListenMode failed
        DEBUG_PRINT(("put_AllowedPorts (RTCTR_UDP) failed %x", hr ));
        SAFE_RELEASE(m_pClient);
        return -1;
    }

	// Answer Mode Calls

	hr = m_pClient->put_AnswerMode(RTCST_PC_TO_PC, RTCAM_OFFER_SESSION_EVENT);
	if ( FAILED(hr) )
	{
	        // put_AnswerMode failed
	        DEBUG_PRINT(("put_AnswerMode (RTCST_PC_TO_PC) failed %x", hr ));
	        SAFE_RELEASE(m_pClient);
	        return -1;
	}

	hr = m_pClient->put_AnswerMode(RTCST_IM, RTCAM_AUTOMATICALLY_ACCEPT);
	if ( FAILED(hr) )
	{
	        // put_AnswerMode failed
	        DEBUG_PRINT(("put_AnswerMode (RTCST_IM) failed %x", hr ));
	        SAFE_RELEASE(m_pClient);
	        return -1;
	}

	hr = m_pClient->put_AnswerMode(RTCST_MULTIPARTY_IM, RTCAM_AUTOMATICALLY_ACCEPT);
	if ( FAILED(hr) )
	{
	        // put_AnswerMode failed
	        DEBUG_PRINT(("put_AnswerMode (RTCST_MULTIPARTY_IM) failed %x", hr ));
	        SAFE_RELEASE(m_pClient);
	        return -1;
	}

	hr = m_pClient->put_AnswerMode(RTCST_APPLICATION, RTCAM_OFFER_SESSION_EVENT);
	if ( FAILED(hr) )
	{
	        // put_AnswerMode failed
	        DEBUG_PRINT(("put_AnswerMode (RTCST_APPLICATION) failed %x", hr ));
	        SAFE_RELEASE(m_pClient);
	        return -1;
	}

	hr = m_pClient->put_AnswerMode(RTCST_PC_TO_PHONE, RTCAM_AUTOMATICALLY_REJECT);
	if ( FAILED(hr) )
	{
	        // put_AnswerMode failed
	        DEBUG_PRINT(("put_AnswerMode (RTCST_PC_TO_PHONE) failed %x", hr ));
	        SAFE_RELEASE(m_pClient);
	}

	hr = m_pClient->put_AnswerMode(RTCST_PHONE_TO_PHONE, RTCAM_AUTOMATICALLY_REJECT);
	if ( FAILED(hr) )
	{
	        // put_AnswerMode failed
	        DEBUG_PRINT(("put_AnswerMode (RTCST_PHONE_TO_PHONE) failed %x", hr ));
	        SAFE_RELEASE(m_pClient);
	}


    // Create the event sink object
    m_pEvents = new CRTCEvents;

    if (!m_pEvents)
    {
        // Out of memory
        DEBUG_PRINT(("Out of memory"));
        SAFE_RELEASE(m_pClient);
        return -1;
    }

    // Advise for events from the RTC client
    hr = m_pEvents->Advise( m_pClient, m_hWnd );

    if ( FAILED(hr) )
    {
        // Advise failed
        DEBUG_PRINT(("Advise failed %x", hr ));
        SAFE_RELEASE(m_pClient);
        return -1;
    }

    // Register the client Version
    BSTR bstr = ::SysAllocString(L"RTCSample_Test_Version");
    hr = m_pClient->put_ClientName( bstr);
    ::SysFreeString(bstr);

    WCHAR p[128];

    swprintf(p,L"Built:%S.%S", __DATE__,__TIME__);

    bstr = ::SysAllocString(p);
    hr = m_pClient->put_ClientCurVer( bstr);
    ::SysFreeString(bstr);
    


    if ( FAILED(hr) )
    {
        // Advise failed
        DEBUG_PRINT(("Advise failed %x", hr ));
        SAFE_RELEASE(m_pClient);
        return -1;
    }


    // Initialize presence status
    DoSetPresence(RTCXS_PRESENCE_ONLINE);

////////////
//
// End RTC Functionality Code
//
////////////


    // Show the logon dialog
    PostMessage(m_hWnd, WM_COMMAND, MAKEWPARAM(ID_FILE_LOGON, 0), 0);

    DEBUG_PRINT(("WINDOW CREATED"));

    return 0;
}

/////////////////////////////////////////////
//
// CRTCWin::OnDestroy
// 

LRESULT CRTCWin::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam)
{  
	// WM_DESTROY has three parameters. We will pass them to our Destroy Proc for future use
	// They are not currently used.

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);

    // Release the RTC profile
    SAFE_RELEASE(m_pProfile);

    // Cleanup the buddy list
    ClearBuddyList();

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to detach the event sink and shutdown the client.
// This should be called after we receive the IRTCClientEvent of type RTCCET_ASYNC_CLEANUP_DONE.
//
////////////

	
    if (m_pClient)
    {
        if (m_pEvents)
        {
            // Unadvise for events from the RTC client
            m_pEvents->Unadvise(m_pClient);
            m_pEvents = NULL;
        }

        // Shutdown the RTC client
        m_pClient->Shutdown();

        // Release the RTC client
        SAFE_RELEASE(m_pClient);
    }

////////////
//
// End RTC Functionality Code
//
////////////

    DEBUG_PRINT(("WINDOW DESTROYED"));

    return 0;
}

/////////////////////////////////////////////
//
// CRTCWin::OnClose
// 

LRESULT CRTCWin::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// WM_CLOSE has three parameters. We will pass them to our Close Proc for future use
	// They are not currently used.

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);

    HRESULT hr = S_OK;

    DEBUG_PRINT(("WINDOW CLOSED"));

    // Cleanup the existing session windows
    CleanupSessions();

    // Cleanup the user search windows
    CleanupUserSearches();

    // Cleanup the watcher windows
    CleanupWatchers();

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to prepare the client for shutdown.
// This should be called before the Shutdown method on the client.
//
////////////


    if (m_pClient)
    {
        // Prepare the RTC client object for shutdown
        hr = m_pClient->PrepareForShutdown();
    }

    if (!m_pClient || FAILED(hr))
    {
        // The RTC client object either doesn't exist, or
        // failed to prepare for shutdown. Destroy the
        // window now
        DestroyWindow(m_hWnd);
    }
    else
    {
        // The RTC client object is preparing to shutdown.
        // We should wait for the RTCCET_ASYNC_CLEANUP_DONE
        // event before we shutdown the RTC client. For now
        // just hide the window
        ShowWindow(m_hWnd, SW_HIDE);
    }

////////////
//
// End RTC Functionality Code
//
////////////

    return 0;
}

/////////////////////////////////////////////
//
// CRTCWin::OnSize
// 

LRESULT CRTCWin::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT rcWnd, rcStatusBar, rcBuddyList;

    const int SIZE_EDGE = 5;

    GetClientRect(m_hWnd, &rcWnd);

    // Resize the status bar
    SendMessage(m_hStatusBar, uMsg, wParam, lParam);

    GetClientRect(m_hStatusBar, &rcStatusBar);

    // Resize the buddy list
    rcBuddyList.bottom = rcWnd.bottom -
        (rcStatusBar.bottom - rcStatusBar.top) -
        SIZE_EDGE;
    rcBuddyList.top = rcWnd.top + SIZE_EDGE;
    rcBuddyList.right = rcWnd.right - SIZE_EDGE;
    rcBuddyList.left = rcWnd.left + SIZE_EDGE;
    
	MoveWindow(
        m_hBuddyTree,
        rcBuddyList.left,
        rcBuddyList.top,
        (rcBuddyList.right - rcBuddyList.left),
        (rcBuddyList.bottom - rcBuddyList.top),
        TRUE);

    return 0;
}

/////////////////////////////////////////////
//
// CRTCWin::OnCommand
// 

LRESULT CRTCWin::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// WM_COMMAND has three parameters. We will pass them to our Command Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);

    HRESULT hr;

    switch(LOWORD(wParam))
    {
    case ID_FILE_LOGON:
        {
            DEBUG_PRINT(("ID_FILE_LOGON"));

            BSTR bstrURI = NULL;
            BSTR bstrServer = NULL;
            BSTR bstrTransport = NULL;

            hr = ShowLogonDialog(
                m_hWnd, &bstrURI, &bstrServer, &bstrTransport);

            if (FAILED(hr))
            {
                // ShowLogonDialog failed
                DEBUG_PRINT(("ShowLogonDialog failed %x", hr ));
                break;
            }

            DEBUG_PRINT(("URI       [%ws]", bstrURI ));
            DEBUG_PRINT(("SERVER    [%ws]", bstrServer ));
            DEBUG_PRINT(("TRANSPORT [%ws]", bstrTransport ));

            DoLogOn(bstrURI, bstrServer, bstrTransport);

            SAFE_FREE_STRING(bstrURI);
            SAFE_FREE_STRING(bstrServer);
            SAFE_FREE_STRING(bstrTransport);
        }
        break;

    case ID_FILE_LOGOFF:
        DEBUG_PRINT(("ID_FILE_LOGOFF"));
        DoLogOff();
        break;

    case ID_FILE_EXIT:
        DEBUG_PRINT(("ID_FILE_EXIT"));
        PostMessage(m_hWnd, WM_CLOSE, 0, 0);
        break;

    case ID_ACTION_ADDBUDDY:
        {
            DEBUG_PRINT(("ID_ACTION_ADDBUDDY"));
            BSTR bstrURI = NULL;
            BSTR bstrName = NULL;

            // Show the add buddy dialog
            hr = ShowAddressDialog(m_hWnd, L"Add Buddy", &bstrURI, &bstrName);

            if (FAILED(hr))
            {
                // ShowAddressDialog failed
                DEBUG_PRINT(("ShowAddressDialog failed %x", hr ));
                break;
            }
        
            // Add the buddy
            DoAddBuddy(bstrURI, bstrName);

            SAFE_FREE_STRING(bstrURI);
            SAFE_FREE_STRING(bstrName);
        }
        break;

    case ID_ACTION_CALL:
        {
            DEBUG_PRINT(("ID_ACTION_CALL"));
            BSTR bstrURI = NULL;

            // Show the call dialog
            hr = ShowAddressDialog(m_hWnd, L"Call To", &bstrURI, NULL);

            if (FAILED(hr))
            {
                // ShowAddressDialog failed
                DEBUG_PRINT(("ShowAddressDialog failed %x", hr ));
                break;
            }

            // Call the user
            DoCall(RTCST_PC_TO_PC, bstrURI, NULL);

            SAFE_FREE_STRING(bstrURI);
        }
        break;

    case ID_ACTION_MESSAGE:
        {
            DEBUG_PRINT(("ID_ACTION_MESSAGE"));
            BSTR bstrURI = NULL;

            // Show the call dialog
            hr = ShowAddressDialog(m_hWnd, L"Message To", &bstrURI, NULL);

            if (FAILED(hr))
            {
                // ShowAddressDialog failed
                DEBUG_PRINT(("ShowAddressDialog failed %x", hr ));
                break;
            }

            // Send a message to the user
            DoCall(RTCST_MULTIPARTY_IM, bstrURI, NULL);

            SAFE_FREE_STRING(bstrURI);
        }
        break;

    case ID_TOOLS_TUNINGWIZARD:
        DEBUG_PRINT(("ID_TOOLS_TUNINGWIZARD"));
        DoTuningWizard();
        break;

    case ID_TOOLS_USERSEARCH:
        DEBUG_PRINT(("ID_TOOLS_USERSEARCH"));
        AddUserSearch();
        break;

    case ID_TOOLS_WATCHERS:
        DEBUG_PRINT(("ID_TOOLS_WATCHERS"));
        AddWatchers();
        break;

    case ID_TOOLS_GROUPS:
        DEBUG_PRINT(("ID_TOOLS_GROUPS"));
        AddGroups();
        break;

	case ID_TOOLS_OPTIONS:
		DEBUG_PRINT(("ID_TOOLS_OPTIONS"));
		DoOptions();
		break;

	case ID_TOOLS_DTMFDIALPAD:
		DEBUG_PRINT(("ID_TOOLS_DTMFDIALPAD"));
		DoDTMFDialpad();
		break;

    case ID_FILE_PRESENCESTATUS_OFFLINE:
        DEBUG_PRINT(("ID_FILE_PRESENCESTATUS_OFFLINE"));
        DoSetPresence(RTCXS_PRESENCE_OFFLINE);
        break;

    case ID_FILE_PRESENCESTATUS_ONLINE:
        DEBUG_PRINT(("ID_FILE_PRESENCESTATUS_ONLINE"));
        DoSetPresence(RTCXS_PRESENCE_ONLINE);
        break;

    case ID_FILE_PRESENCESTATUS_AWAY:
        DEBUG_PRINT(("ID_FILE_PRESENCESTATUS_AWAY"));
        DoSetPresence(RTCXS_PRESENCE_AWAY);
        break;

    case ID_FILE_PRESENCESTATUS_IDLE:
        DEBUG_PRINT(("ID_FILE_PRESENCESTATUS_IDLE"));
        DoSetPresence(RTCXS_PRESENCE_IDLE);
        break;

    case ID_FILE_PRESENCESTATUS_BUSY:
        DEBUG_PRINT(("ID_FILE_PRESENCESTATUS_BUSY"));
        DoSetPresence(RTCXS_PRESENCE_BUSY);
        break;

    case ID_FILE_PRESENCESTATUS_BERIGHTBACK:
        DEBUG_PRINT(("ID_FILE_PRESENCESTATUS_BERIGHTBACK"));
        DoSetPresence(RTCXS_PRESENCE_BE_RIGHT_BACK);
        break;

    case ID_FILE_PRESENCESTATUS_ONTHEPHONE:
        DEBUG_PRINT(("ID_FILE_PRESENCESTATUS_ONTHEPHONE"));
        DoSetPresence(RTCXS_PRESENCE_ON_THE_PHONE);
        break;

    case ID_FILE_PRESENCESTATUS_OUTTOLUNCH:
        DEBUG_PRINT(("ID_FILE_PRESENCESTATUS_OUTTOLUNCH"));
        DoSetPresence(RTCXS_PRESENCE_OUT_TO_LUNCH);
        break;

	
    }

    return 0;
}

/////////////////////////////////////////////
//
// CRTCWin::OnNotify
// 

LRESULT CRTCWin::OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam)
{    
	// WM_NOTIFY has three parameters. We will pass them to our Notify Proc for future use
	// They are not currently used.

	UNREFERENCED_PARAMETER(uMsg);

    int idCtrl = (int)wParam;
    LPNMHDR pnmh = (LPNMHDR)lParam;
    HRESULT hr;

	if (pnmh->code == NM_RCLICK)
    {
		if ( idCtrl == IDC_BUDDYTREE )
        {
            // The user clicked on the buddy list
			TVHITTESTINFO tvht;

			ZeroMemory(&tvht, sizeof(TVHITTESTINFO));

            POINT pt;
            GetCursorPos(&pt);

            tvht.pt = pt;
            MapWindowPoints(NULL, pnmh->hwndFrom, &tvht.pt, 1 );
            
            HTREEITEM htriRes = TreeView_HitTest(pnmh->hwndFrom, &tvht);

            if (htriRes == NULL)
            {
                // TreeView_HitTest failed
                return 0;
            }

            if (tvht.flags & TVHT_ONITEM)
            {
                // The user clicked on a buddy
                TVITEMEX tvi;
                ZeroMemory(&tvi, sizeof(TVITEM));
    
                tvi.mask = TVIF_PARAM;
                tvi.hItem = htriRes;

                // Get the buddy item
                if (!TreeView_GetItem(m_hBuddyTree, &tvi))
                {
                    // TreeView_GetItem failed;
                    return 0;
                }

				if (tvi.lParam == NULL)
				{
					// We're on a parent, not a buddy. Return.
					return 0;
				}
                
                IRTCBuddy * pBuddy = (IRTCBuddy *)(tvi.lParam);
                
                // Get the buddy URI
                BSTR bstrURI = NULL;
                hr = pBuddy->get_PresentityURI(&bstrURI);

                if (FAILED(hr))
                {
                    // get_UserURI failed
                    return 0;
                }
                
                // Get the buddy name
                BSTR bstrName = NULL;
				IRTCBuddy2 *pBuddy2;
				pBuddy->QueryInterface(__uuidof(IRTCBuddy2), (LPVOID *)&pBuddy2);

                hr = pBuddy2->get_PresenceProperty(RTCPP_DISPLAYNAME, &bstrName);

				SAFE_RELEASE(pBuddy2);

                if (FAILED(hr) && (hr != RTC_E_NOT_EXIST))
                {
                    // get_Name failed
                    SAFE_FREE_STRING(bstrURI);
                    return 0;
                }

                // Show the buddy menu
                HMENU hMenuRes = LoadMenu( 
                    GetModuleHandle(NULL),
                    MAKEINTRESOURCE(IDR_MENU_BUDDY));

                HMENU hMenu = GetSubMenu(hMenuRes, 0);

                // Show the popup menu
                UINT uID = TrackPopupMenu(hMenu,
                    TPM_LEFTALIGN | TPM_RIGHTBUTTON |
                    TPM_NONOTIFY | TPM_RETURNCMD,
                    pt.x, pt.y, 0, m_hWnd, NULL);

                switch (uID)
                {
                case ID_BUDDY_CALL:
                    DEBUG_PRINT(("ID_BUDDY_CALL"));
                    // Call the buddy
                    DoCall(RTCST_PC_TO_PC, bstrURI, bstrName);
                    break;

                case ID_BUDDY_MESSAGE:
                    DEBUG_PRINT(("ID_BUDDY_MESSAGE"));
                    // Send a message to the buddy
                    DoCall(RTCST_MULTIPARTY_IM, bstrURI, bstrName);
                    break;

                case ID_BUDDY_REFRESH:
                    DEBUG_PRINT(("ID_BUDDY_REFRESH"));
                    // Refresh the buddy
                    DoRefreshBuddy(pBuddy);
                    break;

                case ID_BUDDY_REMOVE:
                    DEBUG_PRINT(("ID_BUDDY_REMOVE"));
                    // Remove the buddy
                    if (SUCCEEDED(DoRemoveBuddy(pBuddy)))
                    {                    
                        // Release the buddy reference
                        SAFE_RELEASE(pBuddy);

                        // Delete the buddy from the tree
						TreeView_DeleteItem(m_hBuddyTree, htriRes);
                    }
                    break;

				case ID_BUDDY_PROPERTIES:
					DEBUG_PRINT(("ID_BUDDY_PROPERTIES"));
					//Display Presence Property Dialog
					DoBuddyProperties(pBuddy);
					break;
                }

                SAFE_FREE_STRING(bstrURI);
            }
        }





    }

    return 0;
}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCEvent
// 

LRESULT CRTCWin::OnRTCEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	// WM_RTC_EVENT has three parameters. We will pass them to our Event Handler Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(uMsg);

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to receive a particular event object from the IDispatch object.
// The event object is queried based on the value of the RTC_EVENT enumeration value.
//
////////////

    IDispatch * pDisp = (IDispatch *)lParam;
    RTC_EVENT enEvent = (RTC_EVENT)wParam;
    HRESULT hr;

    // Based on the RTC_EVENT type, query for the 
    // appropriate event interface and call a helper
    // method to handle the event
    switch ( enEvent )
    {
        case RTCE_REGISTRATION_STATE_CHANGE:
            {
                IRTCRegistrationStateChangeEvent * pEvent = NULL;
                
                hr = pDisp->QueryInterface( __uuidof(IRTCRegistrationStateChangeEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCRegistrationStateChangeEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }              
            }
            break;

        case RTCE_SESSION_STATE_CHANGE:
            {
                IRTCSessionStateChangeEvent * pEvent = NULL;
                
                hr = pDisp->QueryInterface( __uuidof(IRTCSessionStateChangeEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCSessionStateChangeEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }              
            }
            break;

        case RTCE_PARTICIPANT_STATE_CHANGE:
            {
                IRTCParticipantStateChangeEvent * pEvent = NULL;
                
                hr = pDisp->QueryInterface( __uuidof(IRTCParticipantStateChangeEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCParticipantStateChangeEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }              
            }
            break;

        case RTCE_MESSAGING:
            {
                IRTCMessagingEvent * pEvent = NULL;
                
                hr = pDisp->QueryInterface( __uuidof(IRTCMessagingEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCMessagingEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }              
            }
            break;

        case RTCE_MEDIA:
            {
                IRTCMediaEvent * pEvent = NULL;

                hr = pDisp->QueryInterface( __uuidof(IRTCMediaEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCMediaEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

		case RTCE_MEDIA_REQUEST:
			{
				IRTCMediaRequestEvent *pEvent = NULL;

				hr = pDisp->QueryInterface( __uuidof(IRTCMediaRequestEvent), (void **) &pEvent);

				if (SUCCEEDED(hr))
				{
					OnRTCMediaRequestEvent(pEvent);
					SAFE_RELEASE(pEvent);

				}
			}
			break;

        case RTCE_INTENSITY:
            {
                IRTCIntensityEvent * pEvent = NULL;

                hr = pDisp->QueryInterface( __uuidof(IRTCIntensityEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCIntensityEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

        case RTCE_CLIENT:
            {
                IRTCClientEvent * pEvent = NULL;

                hr = pDisp->QueryInterface( __uuidof(IRTCClientEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCClientEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

        case RTCE_BUDDY:
            {
                IRTCBuddyEvent2 * pEvent = NULL;

                hr = pDisp->QueryInterface( __uuidof(IRTCBuddyEvent2),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCBuddyEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

        case RTCE_WATCHER:
            {
                IRTCWatcherEvent2 * pEvent = NULL;

                hr = pDisp->QueryInterface( __uuidof(IRTCWatcherEvent2),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCWatcherEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

        case RTCE_GROUP:
            {
                IRTCBuddyGroupEvent * pEvent = NULL;

                hr = pDisp->QueryInterface( __uuidof(IRTCBuddyGroupEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCBuddyGroupEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

        case RTCE_USERSEARCH:
            {
                IRTCUserSearchResultsEvent * pEvent = NULL;

                hr = pDisp->QueryInterface( __uuidof(IRTCUserSearchResultsEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCUserSearchResultsEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

        case RTCE_ROAMING:
            {
                IRTCRoamingEvent * pEvent = NULL;

                hr = pDisp->QueryInterface( __uuidof(IRTCRoamingEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCRoamingEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

        case RTCE_PROFILE:
            {
                IRTCProfileEvent2 * pEvent = NULL;

                hr = pDisp->QueryInterface( __uuidof(IRTCProfileEvent2),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCProfileEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

        case RTCE_PRESENCE_PROPERTY:
            {
                IRTCPresencePropertyEvent * pEvent = NULL;

                hr = pDisp->QueryInterface( __uuidof(IRTCPresencePropertyEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCPresencePropertyEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

        case RTCE_PRESENCE_DATA:
            {
                IRTCPresenceDataEvent * pEvent = NULL;

                hr = pDisp->QueryInterface( __uuidof(IRTCPresenceDataEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCPresenceDataEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

        case RTCE_PRESENCE_STATUS:
            {
                IRTCPresenceStatusEvent * pEvent = NULL;

                hr = pDisp->QueryInterface( __uuidof(IRTCPresenceStatusEvent),
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCPresenceStatusEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;
    }

    // Release the event
    SAFE_RELEASE(pDisp);

////////////
//
// End RTC Functionality Code
//
////////////

    return 0;
}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCRegistrationStateChangeEvent
// 

void CRTCWin::OnRTCRegistrationStateChangeEvent(
            IRTCRegistrationStateChangeEvent *pEvent
            )
{
    HRESULT hr;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Registration State Change event.
// This event occurs when our registration state has changed. For example, this may occur
// when we EnableProfileEx(), or we are successfully registered, or logged off from the server.
//
////////////

    // Get the registration state
    RTC_REGISTRATION_STATE enState;
    long lStatusCode;

    hr = pEvent->get_State(&enState);

    if (FAILED(hr))
    {
        // get_State failed
        DEBUG_PRINT(("get_State failed %x", hr));
        return;
    }

    // Get the status code
    hr = pEvent->get_StatusCode(&lStatusCode);

    if (FAILED(hr))
    {
        // get_StatusCode failed
        DEBUG_PRINT(("get_StatusCode failed %x", hr));
        return;
    }

    hr = lStatusCode;

    switch(enState)
    {
    case RTCRS_UNREGISTERING:
        DEBUG_PRINT(("RTCRS_UNREGISTERING %x", hr));
        // Logoff in progress        
        OnLoggingOff();
        break;

    case RTCRS_NOT_REGISTERED:
        DEBUG_PRINT(("RTCRS_NOT_REGISTERED %x", hr));
        // Logged off        
        OnLoggedOff();
        break;

    case RTCRS_REGISTERING:
        DEBUG_PRINT(("RTCRS_REGISTERING %x", hr));
        // Logon in progress        
        OnLoggingOn();
        break;

    case RTCRS_REGISTERED:
        DEBUG_PRINT(("RTCRS_REGISTERED %x", hr));
        // Logged on
        OnLoggedOn();
        break;

    case RTCRS_REJECTED:
    case RTCRS_ERROR:
        {
            DEBUG_PRINT(("RTCRS_REJECTED/ERROR %x", hr));
            // Logon failed. Most likely the server could no be found,
            // or the user needs to authenticate.
            
            // Check if we need to authenticate
            if (m_nLogonAttemptCount < 3 &&
				((hr == RTC_E_STATUS_CLIENT_FORBIDDEN) ||
				(hr == RTC_E_STATUS_CLIENT_UNAUTHORIZED) ||
                (hr == RTC_E_STATUS_CLIENT_PROXY_AUTHENTICATION_REQUIRED)))
            {
				m_nLogonAttemptCount++;

				BSTR bstrURI = NULL; 
                BSTR bstrAccount = NULL; 
                BSTR bstrPassword = NULL; 
                BSTR bstrRealm = NULL;
                BSTR bstrServer = NULL;
                BSTR bstrTransport = NULL;

                hr = m_pProfile->get_Realm(&bstrRealm);

                if (FAILED(hr))
                {
                    // get_Realm failed
                    DEBUG_PRINT(("get_Realm failed %x", hr));
                }

                // Display the authentication dialog  
                hr = ShowAuthDialog(m_hWnd, bstrRealm,
                    &bstrURI, &bstrAccount, &bstrPassword,
                    &bstrServer, &bstrTransport);

                DEBUG_PRINT(("URI       [%ws]", bstrURI ));
                DEBUG_PRINT(("ACCOUNT   [%ws]", bstrAccount ));
                //DEBUG_PRINT(("PASSWORD  [%ws]", bstrPassword ));
                DEBUG_PRINT(("REALM     [%ws]", bstrRealm ));
                DEBUG_PRINT(("SERVER    [%ws]", bstrServer ));
                DEBUG_PRINT(("TRANSPORT [%ws]", bstrTransport ));

                SAFE_FREE_STRING(bstrRealm);
                SAFE_FREE_STRING(bstrServer);
                SAFE_FREE_STRING(bstrTransport);

                if (FAILED(hr))
                {
                    // ShowAuthDialog failed
                    DEBUG_PRINT(("ShowAuthDialog failed %x", hr));
                    DoLogOff();
                    OnLoggedOff();

                    ShowMessageBox(L"Logon failed!");
                    return;
                }

                // Do the authentication
                hr = DoAuth(bstrURI, bstrAccount, bstrPassword);

                SAFE_FREE_STRING(bstrURI);
                SAFE_FREE_STRING(bstrAccount);
                SAFE_FREE_STRING(bstrPassword);

                if (FAILED(hr))
                {
                    // DoAuth failed
                    DEBUG_PRINT(("DoAuth failed %x", hr));
                    DoLogOff();
                    OnLoggedOff();

                    ShowMessageBox(L"Logon failed!");
                    return;
                }
            }
            else
            {
                // Logon failed
                DoLogOff();
                OnLoggedOff();

                // If we were logging on the show error
                if (m_enState == RTCRS_REGISTERING)
                {
                    ShowMessageBox(L"Logon failed!");
                }
                return;
            }
        }
        break;

    case RTCRS_LOGGED_OFF:
        DEBUG_PRINT(("RTCRS_LOGGED_OFF %x", hr));
        // The user logged on at another client
        // The user is logged off from this client
	ShowMessageBox(L"The Server has logged you off (Perhaps you logged in from another location)");
        DoLogOff();
	OnLoggedOff();
        break;

    case RTCRS_LOCAL_PA_LOGGED_OFF:
        DEBUG_PRINT(("RTCRS_LOCAL_PA_LOGGED_OFF %x", hr));
        // The user logged on at another client
        // The user's presence state is no longer sent from this client

        SetStatusText(L"Logged on (Presence disabled)");
        break;

    case RTCRS_REMOTE_PA_LOGGED_OFF:
        DEBUG_PRINT(("RTCRS_REMOTE_PA_LOGGED_OFF %x", hr));
        // The user logged off on another client that was sending his
        // presence state. We can ignore this.
        break;
    }

    m_enState = enState;

////////////
//
// End RTC Functionality Code
//
////////////

}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCSessionStateChangeEvent
// 

void CRTCWin::OnRTCSessionStateChangeEvent(
            IRTCSessionStateChangeEvent *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Session State Change event.
// This event occurs when our session state has changed. For example, this may occur
// when we AddParticipant() to a Session, or we Terminate() a session.
//
////////////

    IRTCSession * pSession = NULL;
    CRTCSession * pSessWindow = NULL;
    RTC_SESSION_STATE enState;
    HRESULT hr;

    hr = pEvent->get_State(&enState);

    if (FAILED(hr))
    {
        // get_State failed
        return;
    }

    hr = pEvent->get_Session(&pSession);

    if (FAILED(hr))
    {
        // get_Session failed
        return;
    }

    // Is this session in our session list?
    hr = FindSession(pSession, &pSessWindow);    

    if (FAILED(hr))
    {
        // FindSession failed
        if (enState == RTCSS_INCOMING)
        {
            // This is a new session
            RTC_SESSION_TYPE enType;

            hr = pSession->get_Type(&enType);

            if (FAILED(hr))
            {
                // get_Type failed
                SAFE_RELEASE(pSession);
                return;
            }            



            if (enType == RTCST_PC_TO_PC || enType == RTCST_PC_TO_PHONE)
            {

                // This is an AV call
                if (CRTCAVSession::m_Singleton != NULL)
                {
                    // If another AV call is in progress, then
                    // we are already busy.
                    pSession->Terminate(RTCTR_BUSY);

                    SAFE_RELEASE(pSession);
                    return;
                }

                // Get the participant object
                IRTCEnumParticipants * pEnum = NULL;
                IRTCParticipant * pParticipant = NULL;

                hr = pSession->EnumerateParticipants(&pEnum);

                if (FAILED(hr))
                {
                    // EnumerateParticipants failed
                    SAFE_RELEASE(pSession);
                    return;
                }

                hr = pEnum->Next(1, &pParticipant, NULL);

                SAFE_RELEASE(pEnum);

                if (hr != S_OK)
                {
                    // Next failed
                    SAFE_RELEASE(pSession);
                    return;
                }

                // Get the participant URI
                BSTR bstrURI = NULL;

                hr = pParticipant->get_UserURI(&bstrURI);

                if (FAILED(hr))
                {
                    // get_UserURI failed
                    SAFE_RELEASE(pSession);
                    SAFE_RELEASE(pParticipant);
                    return;
                }

                // Get the participant name
                BSTR bstrName = NULL;

                hr = pParticipant->get_Name(&bstrName);

                SAFE_RELEASE(pParticipant);

                if (FAILED(hr) && (hr != RTC_E_NOT_EXIST))
                {
                    // get_Name failed
                    SAFE_FREE_STRING(bstrURI);
                    SAFE_RELEASE(pSession);
                    return;
                }

                // Ring the bell
                m_pClient->PlayRing(RTCRT_PHONE, VARIANT_TRUE);

                // Show the session dialog
                BOOL fAccept;

                hr = ShowSessionDialog(m_hWnd, bstrName, bstrURI, &fAccept);    

                SAFE_FREE_STRING(bstrURI);
                SAFE_FREE_STRING(bstrName);

                if (FAILED(hr))
                {
                    // ShowSessionDialog failed                    
                    SAFE_RELEASE(pSession);
                    return;
                }

                if (fAccept)
                {
                    // Accept the session
                    hr = pSession->Answer();

                    if (FAILED(hr))
                    {
                        // Answer failed
                        SAFE_RELEASE(pSession);
                        return;
                    }
                }
                else
                {
                    // Reject the session
                    pSession->Terminate(RTCTR_REJECT);

                    SAFE_RELEASE(pSession);
                    return;
                }
            }
            else
            {
                // This is an IM call
                m_pClient->PlayRing(RTCRT_MESSAGE, VARIANT_TRUE);
            }
            // Add the session to the session list
            // This will create the session window
            hr = AddSession(pSession, enType);

            if (FAILED(hr))
            {
                // AddSession failed
                SAFE_RELEASE(pSession);
                return;
            }
        }        

        SAFE_RELEASE(pSession);

        return;
    }    

    SAFE_RELEASE(pSession);

////////////
//
// End RTC Functionality Code
//
////////////


    // Deliver the session state to the session window
    pSessWindow->DeliverSessionState(enState);
}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCParticipantStateChangeEvent
// 

void CRTCWin::OnRTCParticipantStateChangeEvent(
            IRTCParticipantStateChangeEvent *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Participant State Change event.
// This event occurs when our registration state has changed. For example, this may occur
// when we AddParticipant() or RemoveParticipant() on a Session, or a Participant leaves a Session.
//
////////////

    IRTCSession * pSession = NULL;
    CRTCSession * pSessWindow = NULL;
    IRTCParticipant * pParticipant = NULL;
    RTC_PARTICIPANT_STATE enState;
    HRESULT hr;

    hr = pEvent->get_Participant(&pParticipant);

    if (FAILED(hr))
    {
        // get_Participant failed
        return;
    }

    hr = pParticipant->get_Session(&pSession);

    if (FAILED(hr))
    {
        // get_Session failed
        SAFE_RELEASE(pParticipant);
        return;
    }
        
    hr = FindSession(pSession, &pSessWindow);

    SAFE_RELEASE(pSession);

    if (FAILED(hr))
    {
        // FindSession failed
        SAFE_RELEASE(pParticipant);
        return;
    }

    // Get the participant state
    hr = pEvent->get_State(&enState);

    if (FAILED(hr))
    {
        // get_State failed
        SAFE_RELEASE(pParticipant);
        return;
    }

    // Deliver the participant state to the session window
    pSessWindow->DeliverParticipantState(pParticipant, enState);

////////////
//
// End RTC Functionality Code
//
////////////

    SAFE_RELEASE(pParticipant);
}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCMessagingEvent
// 

void CRTCWin::OnRTCMessagingEvent(
            IRTCMessagingEvent *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Messaging Event.
// This event occurs when we receive a message. This may be a either an instant message
// or a message status message.
//
////////////

    IRTCSession * pSession = NULL;
    CRTCSession * pSessWindow = NULL;
    IRTCParticipant * pParticipant = NULL;
    RTC_MESSAGING_EVENT_TYPE enType;
    RTC_MESSAGING_USER_STATUS enStatus;
    BSTR bstrContentType = NULL;
    BSTR bstrMessage = NULL;
    HRESULT hr;

    hr = pEvent->get_Session(&pSession);

    if (FAILED(hr))
    {
        // get_Session failed
        return;
    }
    
    hr = FindSession(pSession, &pSessWindow);

    SAFE_RELEASE(pSession);

    if (FAILED(hr))
    {
        // FindSession failed
        return;
    }

    hr = pEvent->get_EventType(&enType);

    if (FAILED(hr))
    {
        // get_EventType failed
        return;
    }

    hr = pEvent->get_Participant(&pParticipant);

    if (FAILED(hr))
    {
        // get_Participant failed
        return;
    }

    if (enType == RTCMSET_MESSAGE)
    {
        hr = pEvent->get_MessageHeader(&bstrContentType);

        if (FAILED(hr))
        {
            // get_MessageHeader failed
            SAFE_RELEASE(pParticipant);
            return;
        }

        hr = pEvent->get_Message(&bstrMessage);

        if (FAILED(hr))
        {
            // get_Message failed
            SAFE_RELEASE(pParticipant);
            SAFE_FREE_STRING(bstrContentType);
            return;
        }

        // Deliver the message to the session window
        pSessWindow->DeliverMessage(pParticipant, bstrContentType, bstrMessage);

        SAFE_FREE_STRING(bstrContentType);
        SAFE_FREE_STRING(bstrMessage);
    }
    else if (enType == RTCMSET_STATUS)
    {
        hr = pEvent->get_UserStatus(&enStatus);

        if (FAILED(hr))
        {
            // get_UserStatus failed
            return;
        }

        // Deliver the user status to the session window
        pSessWindow->DeliverUserStatus(pParticipant, enStatus);
    }

    SAFE_RELEASE(pParticipant);    

////////////
//
// End RTC Functionality Code
//
////////////

}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCMediaEvent
// 

void CRTCWin::OnRTCMediaEvent(
            IRTCMediaEvent *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Media Event.
// This event occurs when our media status changes. For example, this may occur
// when we Add or Remove audio, video, or T120 streams.
//
////////////


    long lMediaType;
    RTC_MEDIA_EVENT_TYPE enType;
    RTC_MEDIA_EVENT_REASON enReason;
    HRESULT hr;

    hr = pEvent->get_MediaType(&lMediaType);

    if (FAILED(hr))
    {
        // get_MediaType failed
        return;
    }

    hr = pEvent->get_EventType(&enType);

    if (FAILED(hr))
    {
        // get_EventType failed
        return;
    }

    hr = pEvent->get_EventReason(&enReason);

    if (FAILED(hr))
    {
        // get_EventReason failed
        return;
    }

    if (CRTCAVSession::m_Singleton != NULL)
    {
        // Deliver the media state to the session window
        (CRTCAVSession::m_Singleton)->DeliverMedia(lMediaType, enType, enReason);
    }

////////////
//
// End RTC Functionality Code
//
////////////

}


/////////////////////////////////////////////
//
// CRTCWin::OnRTCMediaEvent
// 
void CRTCWin::OnRTCMediaRequestEvent(
			IRTCMediaRequestEvent *pEvent
			)
{
	long lCurMediaType;
	long lProposedMediaType;
	HRESULT hr;

	hr = pEvent->get_CurrentMedia(&lCurMediaType);
	
	if( FAILED(hr))
		return;

	hr = pEvent->get_ProposedMedia(&lProposedMediaType);
	
	if( FAILED(hr))
		return;


	//TODO: add code to prompt for Media Request Event;

	pEvent->Accept(lProposedMediaType);

	return;
}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCIntensityEvent
// 

void CRTCWin::OnRTCIntensityEvent(
            IRTCIntensityEvent *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle an Intensity Event.
// This event occurs when the volume is adjusted by Automatic Gain Control,
// or when the user changes the volume.
//
////////////

    RTC_AUDIO_DEVICE enDevice;
    long lLevel, lMin, lMax;
    HRESULT hr;

    hr = pEvent->get_Direction(&enDevice);

    if (FAILED(hr))
    {
        // get_Direction failed
        return;
    }

    hr = pEvent->get_Level(&lLevel);

    if (FAILED(hr))
    {
        // get_Level failed
        return;
    }

    hr = pEvent->get_Min(&lMin);

    if (FAILED(hr))
    {
        // get_Min failed
        return;
    }

    hr = pEvent->get_Max(&lMax);

    if (FAILED(hr))
    {
        // get_Max failed
        return;
    }

    // Normalize level to between zero and 100
    if ((lMax - lMin) == 0)
    {
        lLevel = 0;
    }
    else
    {
        lLevel = (lLevel - lMin) * 100 / (lMax - lMin);
    }

    if (CRTCAVSession::m_Singleton != NULL)
    {
        // Deliver the intensity state to the session window
        (CRTCAVSession::m_Singleton)->DeliverIntensity(enDevice, lLevel);
    }

////////////
//
// End RTC Functionality Code
//
////////////

}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCClientEvent
// 

void CRTCWin::OnRTCClientEvent(
            IRTCClientEvent *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Client Event.
// This event occurs when our IP Address changes, Network Quality Changes, or ...
//
////////////

    HRESULT hr;

    // Get the client event tyoe
    RTC_CLIENT_EVENT_TYPE enEventType;

    hr = pEvent->get_EventType(&enEventType);

    if (FAILED(hr))
    {
        // get_EventType failed
        return;
    }

    if ( enEventType == RTCCET_ASYNC_CLEANUP_DONE )
    {
        // The RTC client has finished preparing for
        // shutdown. Destroy the window now.
        DestroyWindow(m_hWnd);
    }
    else
    {
        if (CRTCAVSession::m_Singleton != NULL)
        {
            // Deliver the client state to the session window
            (CRTCAVSession::m_Singleton)->DeliverClient(enEventType);
        }
    }

////////////
//
// End RTC Functionality Code
//
////////////


}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCBuddyEvent
// 

void CRTCWin::OnRTCBuddyEvent(
            IRTCBuddyEvent2 *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Buddy Event.
// This event occurs when our buddy's state is changed, the subscription state changes,
// a buddy is added/removed, a buddy's attributes are updated, or a buddy is roamed.
//
////////////

    HRESULT hr;
    RTC_BUDDY_EVENT_TYPE enType;
    long lStatus;

    hr = pEvent->get_EventType(&enType);

    if (FAILED(hr))
    {
        // get_EventType failed
        DEBUG_PRINT(("get_EventType failed %x", hr ));
        return;
    }

    // Get the status
    hr = pEvent->get_StatusCode(&lStatus);

    if (FAILED(hr))
    {
        // get_StatusCode failed
        DEBUG_PRINT(("get_StatusCode failed %x", hr ));
        return;
    }

    // Get the buddy object
    IRTCBuddy * pBuddy = NULL;

    hr = pEvent->get_Buddy(&pBuddy);

    if (FAILED(hr))
    {
        // get_Buddy failed
        DEBUG_PRINT(("get_Buddy failed %x", hr ));
        return;
    }

    switch (enType)
    {
    case RTCBET_BUDDY_ADD:
        {
            DEBUG_PRINT(("RTCBET_BUDDY_ADD [%p] %x", pBuddy, lStatus ));  

            if (SUCCEEDED(lStatus))
            {
                // Update the buddy list entry
                UpdateBuddyList(pBuddy);
            }
            else
            {
                // Delete the buddy from the list
                ClearBuddyList(pBuddy);
            }
        }
        break;

    case RTCBET_BUDDY_REMOVE:
        {
            DEBUG_PRINT(("RTCBET_BUDDY_REMOVE [%p] %x", pBuddy, lStatus ));

            if (SUCCEEDED(lStatus))
            {
                // Delete the buddy from the list
                ClearBuddyList(pBuddy);
            }
            else
            {
                // Update the buddy list entry
                UpdateBuddyList(pBuddy);
            }
        }
        break;

    case RTCBET_BUDDY_UPDATE:
        {
            DEBUG_PRINT(("RTCBET_BUDDY_UPDATE [%p] %x", pBuddy, lStatus ));

            // Update the buddy list entry
            UpdateBuddyList(pBuddy);
        }
        break;

    case RTCBET_BUDDY_SUBSCRIBED:
	{
	    if (FAILED(lStatus))
	      UpdateBuddyList(pBuddy);
	}
	break;


    case RTCBET_BUDDY_STATE_CHANGE:
        {
            DEBUG_PRINT(("RTCBET_BUDDY_STATE_CHANGE [%p] %x", pBuddy, lStatus ));

            // Update the buddy list entry
            UpdateBuddyList(pBuddy);
        }
        break;
    }

    SAFE_RELEASE(pBuddy);


////////////
//
// End RTC Functionality Code
//
////////////


}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCWatcherEvent
// 

void CRTCWin::OnRTCWatcherEvent(
            IRTCWatcherEvent2 *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Watcher Event.
// This event occurs when our watcher's state is changed,
// a watcher is added/removed, a watcher's attributes are updated, or a watcher is roamed.
//
////////////

    HRESULT hr;
    RTC_WATCHER_EVENT_TYPE enType;
    long lStatus;

    hr = pEvent->get_EventType(&enType);

    if (FAILED(hr))
    {
        // get_EventType failed
        DEBUG_PRINT(("get_EventType failed %x", hr ));
        return;
    }

    // Get the status
    hr = pEvent->get_StatusCode(&lStatus);

    if (FAILED(hr))
    {
        // get_StatusCode failed
        DEBUG_PRINT(("get_StatusCode failed %x", hr ));
        return;
    }

    // Get the watcher object
    IRTCWatcher * pWatcher = NULL;

    hr = pEvent->get_Watcher(&pWatcher);

    if (FAILED(hr))
    {
        // get_Watcher failed
        DEBUG_PRINT(("get_Watcher failed %x", hr ));
        return;
    }

    switch (enType)
    {
    case RTCWET_WATCHER_ADD:
        DEBUG_PRINT(("RTCWET_WATCHER_ADD [%p] %x", pWatcher, lStatus ));
        break;

    case RTCWET_WATCHER_REMOVE:
        DEBUG_PRINT(("RTCWET_WATCHER_REMOVE [%p] %x", pWatcher, lStatus ));
        break;

    case RTCWET_WATCHER_UPDATE:
        DEBUG_PRINT(("RTCWET_WATCHER_UPDATE [%p] %x", pWatcher, lStatus ));
        break;

    case RTCWET_WATCHER_OFFERING:
        {
            DEBUG_PRINT(("RTCWET_WATCHER_OFFERING [%p] %x", pWatcher, lStatus ));

            // Get the watcher URI
            BSTR bstrURI = NULL;

            hr = pWatcher->get_PresentityURI(&bstrURI);

            if (FAILED(hr))
            {
                // get_PresentityURI failed
                DEBUG_PRINT(("get_PresentityURI failed %x", hr ));
                SAFE_RELEASE(pWatcher);
                return;
            }

            // Get the watcher name
            BSTR bstrName = NULL;

            hr = pWatcher->get_Name(&bstrName);

            if (FAILED(hr) && (hr != RTC_E_NOT_EXIST))
            {
                // get_Name failed
                DEBUG_PRINT(("get_Name failed %x", hr ));
                SAFE_FREE_STRING(bstrURI);
                SAFE_RELEASE(pWatcher);
                return;
            }

            // Show the incoming watcher dialog
            BOOL fAllow, fAddBuddy;

            hr = ShowWatcherDialog(m_hWnd, bstrName, bstrURI, &fAllow, &fAddBuddy);    

            if (FAILED(hr))
            {
                // ShowWatcherDialog failed
                DEBUG_PRINT(("ShowWatcherDialog failed %x", hr ));
                SAFE_FREE_STRING(bstrURI);
                SAFE_FREE_STRING(bstrName);
                SAFE_RELEASE(pWatcher);
                return;
            }

            // Set the watcher to be allowed or blocked
            hr = pWatcher->put_State(fAllow ? RTCWS_ALLOWED : RTCWS_BLOCKED);

            if (FAILED(hr))
            {
                // put_State failed
                DEBUG_PRINT(("put_State failed %x", hr ));
                SAFE_FREE_STRING(bstrURI);
                SAFE_FREE_STRING(bstrName);
                SAFE_RELEASE(pWatcher);
                return;
            }

            // Shall we add the user as a buddy?
            if (fAddBuddy)
            {
                hr = DoAddBuddy(bstrURI, bstrName);

                if (FAILED(hr))
                {
                    // DoAddBuddy failed
                    DEBUG_PRINT(("DoAddBuddy failed %x", hr ));
                    SAFE_FREE_STRING(bstrURI);
                    SAFE_FREE_STRING(bstrName);
                    SAFE_RELEASE(pWatcher);
                    return;
                }
            }

            SAFE_FREE_STRING(bstrURI);
            SAFE_FREE_STRING(bstrName);
        }
        break;
    }

    // Deliver events to the watcher windows
    std::vector<CRTCWatcher *>::iterator it;     

    if (!m_WatchersList.empty())
    {
        for(it=m_WatchersList.begin();
            it < m_WatchersList.end();
            it++)
        {
            (*it)->DeliverWatcher(pWatcher, enType, lStatus);
        }
    }

    SAFE_RELEASE(pWatcher);

////////////
//
// End RTC Functionality Code
//
////////////


}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCBuddyGroupEvent
// 

void CRTCWin::OnRTCBuddyGroupEvent(
            IRTCBuddyGroupEvent *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Buddy Group Event.
// This event occurs when a group's state is changed, a buddy is added/removed from the group,
// a group is added/removed, a group's attributes are updated, or the group is roamed.
//
////////////


    HRESULT hr;
    RTC_GROUP_EVENT_TYPE enType;
    long lStatus;

    hr = pEvent->get_EventType(&enType);

    if (FAILED(hr))
    {
        // get_EventType failed
        DEBUG_PRINT(("get_EventType failed %x", hr ));
        return;
    }

    // Get the status
    hr = pEvent->get_StatusCode(&lStatus);

    if (FAILED(hr))
    {
        // get_StatusCode failed
        DEBUG_PRINT(("get_StatusCode failed %x", hr ));
        return;
    }

    // Get the group object
    IRTCBuddyGroup * pGroup = NULL;

    hr = pEvent->get_Group(&pGroup);

    if (FAILED(hr))
    {
        // get_Group failed
        DEBUG_PRINT(("get_Group failed %x", hr ));
        return;
    }

    switch (enType)
    {
    case RTCGET_GROUP_ADD:
        DEBUG_PRINT(("RTCGET_GROUP_ADD [%p] %x", pGroup, lStatus ));
        break;

    case RTCGET_GROUP_REMOVE:
        DEBUG_PRINT(("RTCGET_GROUP_REMOVE [%p] %x", pGroup, lStatus ));
        break;

    case RTCGET_GROUP_UPDATE:
        DEBUG_PRINT(("RTCGET_GROUP_UPDATE [%p] %x", pGroup, lStatus ));
        break;
    }

    // Deliver events to the group windows
    std::vector<CRTCGroup *>::iterator it;     

    if (!m_GroupsList.empty())
    {
        for(it=m_GroupsList.begin();
            it < m_GroupsList.end();
            it++)
        {
            (*it)->DeliverGroup(pGroup, enType, lStatus);
        }
    }

    SAFE_RELEASE(pGroup);

////////////
//
// End RTC Functionality Code
//
////////////

}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCUserSearchResultsEvent
// 

void CRTCWin::OnRTCUserSearchResultsEvent(
            IRTCUserSearchResultsEvent *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a User Search Results Event.
// This event occurs when we receive results for a user search request.
//
////////////

    CRTCSearch * pSearchWindow = NULL;
    IRTCEnumUserSearchResults * pEnum = NULL;
    LONG_PTR lCookie;
    long lStatus;
    HRESULT hr;

    // Get the search cookie
    hr = pEvent->get_Cookie(&lCookie);

    if (FAILED(hr))
    {
        // get_Cookie failed
        DEBUG_PRINT(("get_Cookie failed %x", hr ));
        return;
    }
        
    // Find the search window
    hr = FindUserSearch(lCookie, &pSearchWindow);

    if (FAILED(hr))
    {
        // FindUserSearch failed
        DEBUG_PRINT(("FindUserSearch failed %x", hr ));
        return;
    }

    // Get the search status
    hr = pEvent->get_StatusCode(&lStatus);

    if (FAILED(hr))
    {
        // get_StatusCode failed
        DEBUG_PRINT(("get_StatusCode failed %x", hr ));
        return;
    }

    // Get the search results
    hr = pEvent->EnumerateResults(&pEnum);

    if (FAILED(hr))
    {
        // EnumerateResults failed
        DEBUG_PRINT(("EnumerateResults failed %x", hr ));
        return;
    }

    // Deliver the participant state to the session window
    pSearchWindow->DeliverUserSearchResults((HRESULT)lStatus, pEnum);

    SAFE_RELEASE(pEnum);

////////////
//
// End RTC Functionality Code
//
////////////


}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCRoamingEvent
// 

void CRTCWin::OnRTCRoamingEvent(
            IRTCRoamingEvent *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Roaming Event.
// This event occurs when we begin or end roaming. You may enable roaming as a flag parameter to
// the EnableProfileEx() call.
//
////////////

    HRESULT hr;
    RTC_ROAMING_EVENT_TYPE enType;
    long lStatusCode;

    hr = pEvent->get_EventType(&enType);

    if (FAILED(hr))
    {
        // get_EventType failed
        DEBUG_PRINT(("get_EventType failed %x", hr ));
        return;
    }

    hr = pEvent->get_StatusCode(&lStatusCode);

    if (FAILED(hr))
    {
        // get_StatusCode failed
        DEBUG_PRINT(("get_StatusCode failed %x", hr ));
        return;
    }

    hr = lStatusCode;

    switch (enType)
    {
    case RTCRET_BUDDY_ROAMING:
        DEBUG_PRINT(("RTCRET_BUDDY_ROAMING %x", hr ));
        break;

    case RTCRET_WATCHER_ROAMING:
        DEBUG_PRINT(("RTCRET_WATCHER_ROAMING %x", hr ));
        break;

    case RTCRET_PRESENCE_ROAMING:        
        DEBUG_PRINT(("RTCRET_PRESENCE_ROAMING %x", hr ));  
        break;

    case RTCRET_PROFILE_ROAMING:        
        DEBUG_PRINT(("RTCRET_PROFILE_ROAMING %x", hr ));  
        break;
    }

////////////
//
// End RTC Functionality Code
//
////////////

}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCProfileEvent
// 

void CRTCWin::OnRTCProfileEvent(
            IRTCProfileEvent2 *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Profile Event.
// This event occurs when our profile is created or updated.
// A profile may be created with GetProfile(). A profile may be updated from the server
// if profile roaming is requested, and the server supports the feature.
//
////////////

    HRESULT hr;
    RTC_PROFILE_EVENT_TYPE enType;
    long lStatusCode;

    hr = pEvent->get_EventType(&enType);

    if (FAILED(hr))
    {
        // get_EventType failed
        DEBUG_PRINT(("get_EventType failed %x", hr ));
        return;
    }

    hr = pEvent->get_StatusCode(&lStatusCode);

    if (FAILED(hr))
    {
        // get_StatusCode failed
        DEBUG_PRINT(("get_StatusCode failed %x", hr ));
        return;
    }

    hr = lStatusCode;

    switch (enType)
    {
    case RTCPFET_PROFILE_GET:
        {
            DEBUG_PRINT(("RTCPFET_PROFILE_GET %x", hr ));

            if (FAILED(hr))
            {
                // Provisioning failed.
                DoLogOff();
                OnLoggedOff();

                ShowMessageBox(L"Logon failed!");
                return;
            }
            else
            {
                // Provisioning was successful.
                // Get the RTC profile object from the event
                IRTCProfile *p = NULL;
 
                hr = pEvent->get_Profile(&p);
                if(p)  {
                   p->QueryInterface(__uuidof(IRTCProfile2), (void **)&m_pProfile);
                   SAFE_RELEASE(p); 
                   DEBUG_PRINT(("m_pProfile = %X", m_pProfile));
                } else
                   hr = E_NOINTERFACE;
				
                if (FAILED(hr))
                {
                    // get_Profile failed
                    DEBUG_PRINT(("get_Profile failed %x", hr ));
                    DoLogOff();
                    OnLoggedOff();

                    ShowMessageBox(L"Logon failed!");
                    return;
                }

				hr = m_pProfile->put_AllowedAuth(RTCAU_NTLM | RTCAU_KERBEROS | RTCAU_USE_LOGON_CRED);
				if (FAILED(hr))
                {
                    DEBUG_PRINT(("put_AllowedAuth failed %x", hr ));
                }

                // Register the profile
                hr = DoRegister();

                if (FAILED(hr))
                {
                    // DoEnableRoaming failed
                    DEBUG_PRINT(("DoRegister failed %x", hr ));                    
                    DoLogOff();
                    OnLoggedOff();

                    ShowMessageBox(L"Logon failed!");        
                    return;  
                }
            }
        }
        break;

    case RTCPFET_PROFILE_UPDATE:
        DEBUG_PRINT(("RTCPFET_PROFILE_UPDATE %x", hr ));
        // Ignore updates
        break;
   }


////////////
//
// End RTC Functionality Code
//
////////////



}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCPresencePropertyEvent
// 

void CRTCWin::OnRTCPresencePropertyEvent(
            IRTCPresencePropertyEvent *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Presence Property Event.
// This event occurs when one of our device's presence properties are updated.
// (the status code indicates whether the operation was successful).
//
////////////

    HRESULT hr;
    long lStatusCode;
    RTC_PRESENCE_PROPERTY enProp;
    BSTR bstrVal = NULL;

    hr = pEvent->get_StatusCode(&lStatusCode);

    if (FAILED(hr))
    {
        // get_StatusCode failed
        DEBUG_PRINT(("get_StatusCode failed %x", hr ));
        return;
    }

    hr = pEvent->get_PresenceProperty(&enProp);

    if (FAILED(hr) && (hr != RTC_E_NOT_EXIST))
    {
        // get_PresenceProperty failed
        DEBUG_PRINT(("get_PresenceProperty failed %x", hr ));
        return;
    }

    hr = pEvent->get_Value(&bstrVal);

    DEBUG_PRINT(("RTCE_PRESENCE_PROPERTY %d : %s ", enProp, bstrVal));

    SAFE_FREE_STRING(bstrVal);

////////////
//
// End RTC Functionality Code
//
////////////


}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCPresenceDataEvent
// 

void CRTCWin::OnRTCPresenceDataEvent(
            IRTCPresenceDataEvent *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Presence Data Event.
// This event occurs when our device's presence data is updated (the status code indicates whether the operation was successful).
//
////////////

    HRESULT hr;
    long lStatusCode;
    BSTR bstrNamespace = NULL;
    BSTR bstrData = NULL;

    hr = pEvent->get_StatusCode(&lStatusCode);

    if (FAILED(hr))
    {
        // get_StatusCode failed
        DEBUG_PRINT(("get_StatusCode failed %x", hr ));
        return;
    }

    hr = pEvent->GetPresenceData(&bstrNamespace, &bstrData);

    if (FAILED(hr) && (hr != RTC_E_NOT_EXIST))
    {
        // GetPresenceData failed
        DEBUG_PRINT(("GetPresenceData failed %x", hr ));
        return;
    }

    DEBUG_PRINT(("RTCE_PRESENCE_PROPERTY %s : %s ", bstrNamespace, bstrData));


    SAFE_FREE_STRING(bstrNamespace);
    SAFE_FREE_STRING(bstrData);

////////////
//
// End RTC Functionality Code
//
////////////

}

/////////////////////////////////////////////
//
// CRTCWin::OnRTCPresenceStatusEvent
// 

void CRTCWin::OnRTCPresenceStatusEvent(
            IRTCPresenceStatusEvent *pEvent
            )
{

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates how to handle a Presence Status Event.
// This event occurs when our device's presence status is updated.
// (the status code indicates whether the operation was successful).
//
////////////

    HRESULT hr;
    long lStatusCode;
    BSTR bstrNotes = NULL;
    RTC_PRESENCE_STATUS enStatus;

    hr = pEvent->get_StatusCode(&lStatusCode);

    if (FAILED(hr))
    {
        // get_StatusCode failed
        DEBUG_PRINT(("get_StatusCode failed %x", hr ));
        return;
    }

    hr = pEvent->GetLocalPresenceInfo(&enStatus, &bstrNotes);

    if (FAILED(hr) && (hr != RTC_E_NOT_EXIST))
    {
        // GetLocalPresenceInfo failed
        DEBUG_PRINT(("GetLocalPresenceInfo failed %x", hr ));
        return;
    }

    DEBUG_PRINT(("RTCE_PRESENCE_STATUS=%d Notes=%s : %s ", enStatus, bstrNotes));


    SAFE_FREE_STRING(bstrNotes);

////////////
//
// End RTC Functionality Code
//
////////////

}


