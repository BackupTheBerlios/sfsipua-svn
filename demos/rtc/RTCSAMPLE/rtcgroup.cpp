// rtcgroup.cpp
//

#include "stdafx.h"

/////////////////////////////////////////////
//
// CRTCGroup::CRTCGroup
// 

CRTCGroup::CRTCGroup()
{
    m_hWnd = NULL;
    m_hGroupList = NULL;
    m_pClient = NULL;
}

/////////////////////////////////////////////
//
// CRTCGroup::~CRTCGroup
// 

CRTCGroup::~CRTCGroup()
{
}

/////////////////////////////////////////////
//
// CRTCGroup::RegisterClass
//

HRESULT CRTCGroup::RegisterClass()
{
    // Register the window class
    WNDCLASS wc;
    ATOM atom;

    ZeroMemory(&wc, sizeof(WNDCLASS));

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)CRTCGroup::WindowProc;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.hIcon         = NULL;
    wc.hCursor       =
        LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = 
        GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU_GROUPS);
    wc.lpszClassName = GRP_CLASS;

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
// CRTCGroup::UpdateGroupList
//

HRESULT CRTCGroup::UpdateGroupList(IRTCBuddyGroup * pGroup)
{
    HRESULT hr;

	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates getting group name and updating the group list UI
	//
	////////////

    if (pGroup == NULL)
    {
        return S_OK;
    }

    // Get the group name
    BSTR bstrName = NULL;

    hr = pGroup->get_Name(&bstrName);

    if (FAILED(hr))
    {
        // get_Name failed
        DEBUG_PRINT(("get_Name failed %x", hr ));
        return hr;
    }
    
    // Is the group in the list?
    LVFINDINFO lvfi;    
    ZeroMemory(&lvfi, sizeof(LVFINDINFO));

    lvfi.flags = LVFI_PARAM;
    lvfi.lParam = (LPARAM)pGroup;

    int iRes = ListView_FindItem(m_hGroupList, -1, &lvfi);

    if (iRes == -1)
    {
        // Group is not in the list
        // Add the group to the list  
        LVITEM lvi;
        ZeroMemory(&lvi, sizeof(LVITEM));

        lvi.mask = LVIF_TEXT | LVIF_PARAM;
        lvi.pszText = bstrName;
        lvi.lParam = (LPARAM)pGroup;

        iRes = ListView_InsertItem(m_hGroupList, &lvi);

        if (iRes == -1)
        {
            // ListView_InsertItem failed
            DEBUG_PRINT(("ListView_InsertItem failed %x",
                HRESULT_FROM_WIN32(GetLastError()) ));
            SAFE_FREE_STRING(bstrName);
            return E_FAIL;
        }

        // An RTC group reference will be kept by the list
        // Add the reference here
        pGroup->AddRef();

		////////////
		//
		// End RTC Functionality Code
		//
		////////////
    }

    else
    {
        // Group is in the list
        // Update the list entry
        LVITEM lvi;
        ZeroMemory(&lvi, sizeof(LVITEM));

        lvi.mask = LVIF_TEXT;
        lvi.pszText = bstrName;
        lvi.iItem = iRes;

        iRes = ListView_SetItem(m_hGroupList, &lvi);

        if (iRes == -1)
        {
            // ListView_SetItem failed 
            DEBUG_PRINT(("ListView_SetItem failed %x",
                HRESULT_FROM_WIN32(GetLastError()) ));
            SAFE_FREE_STRING(bstrName);
            return E_FAIL;
        }
    }

    SAFE_FREE_STRING(bstrName);

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCGroup::ClearGroupList
//

HRESULT CRTCGroup::ClearGroupList(IRTCBuddyGroup * pGroup)
{
    HRESULT hr = S_OK;

    if (pGroup == NULL)
    {
        return S_OK;
    }
    
    // Is the group in the list?
    LVFINDINFO lvfi;    
    ZeroMemory(&lvfi, sizeof(LVFINDINFO));

    lvfi.flags = LVFI_PARAM;
    lvfi.lParam = (LPARAM)pGroup;

    int iRes = ListView_FindItem(m_hGroupList, -1, &lvfi);

    if (iRes != -1)
    {       
        // Group is in the list
        // Remove the list entry
        ListView_DeleteItem(m_hGroupList, iRes);

	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates releasing IRTCBuddyGroup references
	//
	////////////

        // Release the group reference
        SAFE_RELEASE(pGroup);

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
// CRTCGroup::ClearGroupList
// 

HRESULT CRTCGroup::ClearGroupList()
{
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(LVITEM));
    
    lvi.mask = LVIF_PARAM;

    // Iterate through the list and remove each item
    while (ListView_GetItem(m_hGroupList, &lvi))
    {
        IRTCBuddyGroup * pGroup = (IRTCBuddyGroup *)(lvi.lParam);

        // Remove the list entry
        ListView_DeleteItem(m_hGroupList, 0);

        // Release the group reference
        SAFE_RELEASE(pGroup);        
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCGroup::PopulateGroupList
// 

HRESULT CRTCGroup::PopulateGroupList()
{
    HRESULT hr;
	
	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates enumerating groups and populating UI.
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
        DEBUG_PRINT(("QueryInterface failed %x", hr ));
        return hr;
    }

    // Enumerate groups and populate list
    IRTCEnumGroups * pEnum = NULL;
    IRTCBuddyGroup * pGroup = NULL;

    hr = pPresence->EnumerateGroups(&pEnum);

    SAFE_RELEASE(pPresence);

    if (FAILED(hr))
    {
        // Enumerate groups failed
        DEBUG_PRINT(("EnumerateGroups failed %x", hr ));
        return hr;
    }

    while (pEnum->Next(1, &pGroup, NULL) == S_OK)
    {
        // Update the group list entry
        UpdateGroupList(pGroup);

        SAFE_RELEASE(pGroup);
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
// CRTCGroup::DoAddGroup
// 

HRESULT CRTCGroup::DoAddGroup(BSTR bstrName)
{
    HRESULT hr;

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates Adding a group
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

    // Add the group
    IRTCBuddyGroup * pGroup = NULL;

    hr = pPresence->AddGroup(
            bstrName,
            NULL,           
            NULL,
            0,
            &pGroup);

    SAFE_RELEASE(pPresence);

    if (FAILED(hr))
    {
        // AddGroup failed 
        DEBUG_PRINT(("AddGroup failed %x", hr ));
        return hr;
    }

    if (pGroup)
    {
        // Update the group list entry
        UpdateGroupList(pGroup);
        SAFE_RELEASE(pGroup);
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
// CRTCGroup::DoRemoveGroup
// 

HRESULT CRTCGroup::DoRemoveGroup(IRTCBuddyGroup *pGroup)
{
    HRESULT hr;

	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates Removing a buddy from a group
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
        DEBUG_PRINT(("QueryInterface failed %x", hr ));
        return hr;
    }

    // Remove the group
    hr = pPresence->RemoveGroup(pGroup);

    SAFE_RELEASE(pPresence);

    if (FAILED(hr))
    {
        // RemoveGroup failed
        DEBUG_PRINT(("RemoveGroup failed %x", hr ));
        return hr;
    }

	////////////
	//
	// End RTC Functionality Code
	//
	////////////

    return S_OK;
}

HRESULT CRTCGroup::DoAddBuddyToGroup(BSTR bstrBuddyURI, IRTCBuddyGroup *pGroup)
{
    HRESULT hr;

	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates Adding a buddy to a group
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
        DEBUG_PRINT(("QueryInterface failed %x", hr ));
        return hr;
    }

    // Find The Buddy
    IRTCBuddy *pBuddy = NULL;

    hr = pPresence->get_Buddy(bstrBuddyURI, &pBuddy);
    if (FAILED(hr))
    {
        // get_Buddy failed
        DEBUG_PRINT(("get_Buddy failed %x", hr ));
		SAFE_RELEASE(pPresence);
        return hr;
    }

    pGroup->AddBuddy(pBuddy);
    if (FAILED(hr))
    {
        // the remove failed
        DEBUG_PRINT(("AddBuddy failed %x", hr ));
		SAFE_RELEASE(pPresence);
		SAFE_RELEASE(pBuddy);
        return hr;
    }

    SAFE_RELEASE(pBuddy);
    SAFE_RELEASE(pPresence);

	////////////
	//
	// End RTC Functionality Code
	//
	////////////

    return S_OK;
}

HRESULT CRTCGroup::DoRemoveBuddyFromGroup(BSTR bstrBuddyURI, IRTCBuddyGroup *pGroup)
{
HRESULT hr;

	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates Removing a group
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
        DEBUG_PRINT(("QueryInterface failed %x", hr ));
        return hr;
    }

    // Find The Buddy
    IRTCBuddy *pBuddy = NULL;

    hr = pPresence->get_Buddy(bstrBuddyURI, &pBuddy);
	if (FAILED(hr))
    {
        // get_Buddy failed
        DEBUG_PRINT(("get_Buddy failed %x", hr ));
		SAFE_RELEASE(pPresence);
        return hr;
    }

    pGroup->RemoveBuddy(pBuddy);
    if (FAILED(hr))
    {
        // the remove failed
        DEBUG_PRINT(("RemoveBuddy failed %x", hr ));
		SAFE_RELEASE(pPresence);
		SAFE_RELEASE(pBuddy);
        return hr;
    }

    SAFE_RELEASE(pBuddy);
    SAFE_RELEASE(pPresence);

	////////////
	//
	// End RTC Functionality Code
	//
	////////////

    return S_OK;;
}



/////////////////////////////////////////////
//
// CRTCGroup::WindowProc
// 

LRESULT CALLBACK CRTCGroup::WindowProc(
  HWND hWnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
    CRTCGroup * me = NULL;
    LRESULT  lr = 0;

    if ( uMsg == WM_CREATE )
    {
        // Create an instance of the class
        me = new CRTCGroup;
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
        me = (CRTCGroup *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

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
            me->PopulateGroupList();
            break;
      
        default:
            lr = DefWindowProc( hWnd, uMsg, wParam, lParam );
        }
    }

    return lr;
}

/////////////////////////////////////////////
//
// CRTCGroup::OnCreate
// 

LRESULT CRTCGroup::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	// These formal parameters arent being used by RTC:
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(uMsg);

	// Create the group list
    m_hGroupList = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"SysListView32",
        NULL,
        WS_CHILD | WS_VISIBLE |
        LVS_SINGLESEL | LVS_SORTASCENDING |
        LVS_AUTOARRANGE | LVS_SMALLICON,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_GROUPLIST,
        GetModuleHandle(NULL),
        NULL);

    if ( !m_hGroupList )
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
// CRTCGroup::OnDestroy
// 

LRESULT CRTCGroup::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam)
{  
	// These formal parameters arent being used by RTC:
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(uMsg);

	// Cleanup the group list
    ClearGroupList();

    // Release the RTC client
    SAFE_RELEASE(m_pClient);

    if (m_pWin)
    {
        // Remove the window from the group list
        m_pWin->RemoveGroups(this);
    }

    return 0;
}

/////////////////////////////////////////////
//
// CRTCGroup::OnClose
// 

LRESULT CRTCGroup::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// These formal parameters arent being used by RTC:
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(uMsg);

	DestroyWindow(m_hWnd);

    return 0;
}

/////////////////////////////////////////////
//
// CRTCGroup::OnSize
// 

LRESULT CRTCGroup::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// These formal parameters arent being used by RTC:
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(uMsg);

	RECT rcWnd, rcGroupList;

    const int SIZE_EDGE = 5;

    GetClientRect(m_hWnd, &rcWnd);

    // Resize the group list
    rcGroupList.bottom = rcWnd.bottom - SIZE_EDGE;
    rcGroupList.top = rcWnd.top + SIZE_EDGE;
    rcGroupList.right = rcWnd.right - SIZE_EDGE;
    rcGroupList.left = rcWnd.left + SIZE_EDGE;
    
    MoveWindow(
        m_hGroupList,
        rcGroupList.left,
        rcGroupList.top,
        (rcGroupList.right - rcGroupList.left),
        (rcGroupList.bottom - rcGroupList.top),
        TRUE);

    SendMessage(m_hGroupList, LVM_SETCOLUMNWIDTH,
        (WPARAM)0, MAKELPARAM(rcGroupList.right - rcGroupList.left,0));

    return 0;
}

/////////////////////////////////////////////
//
// CRTCGroup::OnCommand
// 

LRESULT CRTCGroup::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// These formal parameters arent being used by RTC:
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);
	
	HRESULT hr;

    switch(LOWORD(wParam))
    {
    case ID_FILE_EXIT:
        PostMessage(m_hWnd, WM_CLOSE, 0, 0);
        break;

    case ID_ACTION_ADDGROUP:
        {
            DEBUG_PRINT(("ID_ACTION_ADDGROUP"));
            BSTR bstrName = NULL;

            // Show the add group dialog
            hr = ShowAddressDialog(m_hWnd, L"Add Group", NULL, &bstrName);

            if (FAILED(hr))
            {
                // ShowNameDialog failed
                DEBUG_PRINT(("ShowNameDialog failed %x", hr ));
                break;
            }
        
            // Add the group
            DoAddGroup(bstrName);

            SAFE_FREE_STRING(bstrName);
        }
        break;
    }

    return 0;
}

/////////////////////////////////////////////
//
// CRTCGroup::OnNotify
// 

LRESULT CRTCGroup::OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam)
{    
	// These formal parameters arent being used by RTC:
	UNREFERENCED_PARAMETER(uMsg);

	int idCtrl = (int)wParam;
    LPNMHDR pnmh = (LPNMHDR)lParam;
    HRESULT hr = S_OK;

    if ( (pnmh->code == NM_CLICK) ||
         (pnmh->code == NM_RCLICK) )
    {
        if ( idCtrl == IDC_GROUPLIST )
        {
            // The user clicked on the group list
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
                // The user clicked on a group
                LVITEM lvi;
                ZeroMemory(&lvi, sizeof(LVITEM));
    
                lvi.mask = LVIF_PARAM;
                lvi.iItem = iRes;

                // Get the group item
                if (!ListView_GetItem(m_hGroupList, &lvi))
                {
                    // ListView_GetItem failed;
                    return 0;
                }
                
                IRTCBuddyGroup * pGroup = (IRTCBuddyGroup *)(lvi.lParam);

                // Show the group menu
                HMENU hMenuRes = LoadMenu( 
                    GetModuleHandle(NULL),
                    MAKEINTRESOURCE(IDR_MENU_GROUP));

                HMENU hMenu = GetSubMenu(hMenuRes, 0);

                // Show the popup menu
                UINT uID = TrackPopupMenu(hMenu,
                    TPM_LEFTALIGN | TPM_RIGHTBUTTON |
                    TPM_NONOTIFY | TPM_RETURNCMD,
                    pt.x, pt.y, 0, m_hWnd, NULL);

                BSTR bstrBuddyRemoveURI = NULL;
                BSTR bstrBuddyAddURI = NULL;

                switch (uID)
                {         
                case ID_GROUP_REMOVE:

                    DEBUG_PRINT(("ID_GROUP_REMOVE"));

                    // Remove the group
                    if (SUCCEEDED(DoRemoveGroup(pGroup)))
                    {                    
                        // Release the group reference
                        SAFE_RELEASE(pGroup);

                        // Delete the group from the list
                        ListView_DeleteItem(m_hGroupList, iRes);
                    }
                    break;
				
                case ID_GROUP_BUDDY_REMOVE:

                    DEBUG_PRINT(("ID_GROUP_BUDDY_REMOVE"));

                    // Get the Buddy URI
                    ShowAddressDialog(m_hWnd, L"Enter Buddy URI", &bstrBuddyRemoveURI, NULL);

                    DoRemoveBuddyFromGroup(bstrBuddyRemoveURI, pGroup);
                    SAFE_FREE_STRING(bstrBuddyRemoveURI);
                    break;

                case ID_GROUP_BUDDY_ADD:

                    DEBUG_PRINT(("ID_GROUP_BUDDY_ADD"));
                    
                    // Get the Buddy URI
                    ShowAddressDialog(m_hWnd,L"Enter Buddy URI", &bstrBuddyAddURI, NULL);

                    DoAddBuddyToGroup(bstrBuddyAddURI, pGroup);
                    SAFE_FREE_STRING(bstrBuddyAddURI);
                    break;
                }
            }
        }
    }

    return hr;
}

/////////////////////////////////////////////
//
// CRTCGroup::DeliverGroup
// 

HRESULT CRTCGroup::DeliverGroup(IRTCBuddyGroup * pGroup, RTC_GROUP_EVENT_TYPE enType, LONG lStatus)
{
    switch (enType)
    {
    case RTCGET_GROUP_ADD:
        {
            if (SUCCEEDED(lStatus))
            {
                // Update the group list entry
                UpdateGroupList(pGroup);
            }
            else
            {
                // Delete the group from the list
                ClearGroupList(pGroup);
            }
        }
        break;

    case RTCGET_GROUP_REMOVE:
        {
            if (SUCCEEDED(lStatus))
            {
                // Delete the group from the list
                ClearGroupList(pGroup);
            }
            else
            {
                // Update the group list entry
                UpdateGroupList(pGroup);
            }
        }
        break;

    case RTCGET_GROUP_UPDATE:
        {
            // Update the group list entry
            UpdateGroupList(pGroup);
        }
        break;
    }

    return S_OK;
}
