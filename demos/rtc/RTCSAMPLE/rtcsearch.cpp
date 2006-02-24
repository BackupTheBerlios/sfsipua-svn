// rtcsearch.cpp
//

#include "stdafx.h"

/////////////////////////////////////////////
//
// CRTCSearch::CRTCSearch
// 

CRTCSearch::CRTCSearch()
{
    m_hWnd = NULL;
    m_pProfile = NULL;
    m_pUserSearch = NULL;
    m_lCookie = -1;
    m_hFirstName = NULL;
	m_hLastName = NULL;
	m_hEmail = NULL;
    m_hSearch = NULL;
    m_hResultList = NULL;
	m_hfnLabel = NULL;\
	m_hlnLabel = NULL;
	m_hmLabel = NULL;
    m_wpOrigFNProc = NULL;
	m_wpOrigLNProc = NULL;
	m_wpOrigMProc = NULL;
}

/////////////////////////////////////////////
//
// CRTCSearch::~CRTCSearch
// 

CRTCSearch::~CRTCSearch()
{
}

/////////////////////////////////////////////
//
// CRTCSearch::RegisterClass
//

HRESULT CRTCSearch::RegisterClass()
{
    // Register the window class
    WNDCLASS wc;
    ATOM atom;

    ZeroMemory(&wc, sizeof(WNDCLASS));

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)CRTCSearch::WindowProc;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.hIcon         = NULL;
    wc.hCursor       =
        LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = 
        GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = US_CLASS;

    atom = ::RegisterClass( &wc );

    if ( !atom )
    {
        // RegisterClass failed
        return E_FAIL;
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCSearch::WindowProc
// 

LRESULT CALLBACK CRTCSearch::WindowProc(
  HWND hWnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
    CRTCSearch * me = NULL;
    LRESULT  lr = 0;

    if ( uMsg == WM_CREATE )
    {
        // Create an instance of the class
        me = new CRTCSearch;
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
        me = (CRTCSearch *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

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

        default:
            lr = DefWindowProc( hWnd, uMsg, wParam, lParam );
        }
    }

    return lr;
}

/////////////////////////////////////////////
//
// CRTCSearch::FNSubclassProc
// 

LRESULT CALLBACK CRTCSearch::FNSubclassProc(
  HWND hWnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
    CRTCSearch * me = NULL;
    me = (CRTCSearch *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    if ( uMsg == WM_KEYDOWN )
    {
        // Intercept the return key from the First Name box
        // and press the search button
        if ( (wParam == VK_RETURN) &&
             !(GetKeyState(VK_CONTROL) & 0x8000))
        {
            SendMessage(me->m_hWnd, WM_COMMAND,
                MAKEWPARAM(IDC_US_SEARCH, BN_CLICKED),
                (LPARAM)me->m_hSearch);

            return 0;
        }
    }
    else if ( uMsg == WM_CHAR )
    {
        // Intercept the return key from the First Name box
        if (wParam == VK_RETURN)
        {           
            return 0;
        }
    }

    // Call the original First Name window procedure
    return CallWindowProc(
        me->m_wpOrigFNProc,
        hWnd, uMsg, wParam, lParam);
}

/////////////////////////////////////////////
//
// CRTCSearch::LNSubclassProc
// 

LRESULT CALLBACK CRTCSearch::LNSubclassProc(
  HWND hWnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
    CRTCSearch * me = NULL;
    me = (CRTCSearch *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    if ( uMsg == WM_KEYDOWN )
    {
        // Intercept the return key from the Last Name box
        // and press the search button
        if ( (wParam == VK_RETURN) &&
             !(GetKeyState(VK_CONTROL) & 0x8000))
        {
            SendMessage(me->m_hWnd, WM_COMMAND,
                MAKEWPARAM(IDC_US_SEARCH, BN_CLICKED),
                (LPARAM)me->m_hSearch);

            return 0;
        }
    }
    else if ( uMsg == WM_CHAR )
    {
        // Intercept the return key from the Last Name box
        if (wParam == VK_RETURN)
        {           
            return 0;
        }
    }

    // Call the original Last Name window procedure
    return CallWindowProc(
        me->m_wpOrigLNProc,
        hWnd, uMsg, wParam, lParam);
}

/////////////////////////////////////////////
//
// CRTCSearch::MSubclassProc
// 

LRESULT CALLBACK CRTCSearch::MSubclassProc(
  HWND hWnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
    CRTCSearch * me = NULL;
    me = (CRTCSearch *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    if ( uMsg == WM_KEYDOWN )
    {
        // Intercept the return key from the Email box
        // and press the search button
        if ( (wParam == VK_RETURN) &&
             !(GetKeyState(VK_CONTROL) & 0x8000))
        {
            SendMessage(me->m_hWnd, WM_COMMAND,
                MAKEWPARAM(IDC_US_SEARCH, BN_CLICKED),
                (LPARAM)me->m_hSearch);

            return 0;
        }
    }
    else if ( uMsg == WM_CHAR )
    {
        // Intercept the return key from the Email box
        if (wParam == VK_RETURN)
        {           
            return 0;
        }
    }

    // Call the original Email window procedure
    return CallWindowProc(
        me->m_wpOrigMProc,
        hWnd, uMsg, wParam, lParam);
}

/////////////////////////////////////////////
//
// CRTCSearch::ShowMessageBox
//

void CRTCSearch::ShowMessageBox(PWSTR szText)
{
    MessageBoxW(m_hWnd, szText, APP_TITLE, MB_OK);
}

/////////////////////////////////////////////
//
// CRTCSearch::SetStatusText
//

void CRTCSearch::SetStatusText(PWSTR szText)
{
    SetWindowTextW(m_hStatusBar, szText);
    InvalidateRect(m_hStatusBar, NULL, FALSE);
}

/////////////////////////////////////////////
//
// CRTCSearch::UpdateResultList
//

HRESULT CRTCSearch::UpdateResultList(IRTCUserSearchResult * pResult)
{
    HRESULT hr;
      
    // Add the result to the list  
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(LVITEM));

    lvi.mask = LVIF_PARAM;
    lvi.lParam = (LPARAM)pResult;

    int iItem = ListView_InsertItem(m_hResultList, &lvi);

    if (iItem == -1)
    {
        // ListView_InsertItem failed
        return E_FAIL;
    }
	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates getting usersearch results and updating UI
	//
	////////////

    // A result reference will be kept by the list
    // Add the reference here
    pResult->AddRef();

    // Fill in the result values
    BSTR bstrValue = NULL;

    hr = pResult->get_Value(RTCUSC_DISPLAYNAME, &bstrValue);

    if (SUCCEEDED(hr))
    {
        ListView_SetItemText(m_hResultList, iItem, 0, bstrValue);
        SAFE_FREE_STRING(bstrValue);
    }

    hr = pResult->get_Value(RTCUSC_URI, &bstrValue);

    if (SUCCEEDED(hr))
    {
        ListView_SetItemText(m_hResultList, iItem, 1, bstrValue);
        SAFE_FREE_STRING(bstrValue);
    }

    hr = pResult->get_Value(RTCUSC_EMAIL, &bstrValue);

    if (SUCCEEDED(hr))
    {
        ListView_SetItemText(m_hResultList, iItem, 2, bstrValue);
        SAFE_FREE_STRING(bstrValue);
    }

	hr = pResult->get_Value(RTCUSC_PHONE, &bstrValue);

    if (SUCCEEDED(hr))
    {
        ListView_SetItemText(m_hResultList, iItem, 3, bstrValue);
        SAFE_FREE_STRING(bstrValue);
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
// CRTCSearch::ClearResultList
// 

HRESULT CRTCSearch::ClearResultList()
{
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(LVITEM));
    
    lvi.mask = LVIF_PARAM;

	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates releasing IRTCUserSearchResult references
	//
	////////////

    // Iterate through the list and remove each item
    while (ListView_GetItem(m_hResultList, &lvi))
    {
        IRTCUserSearchResult * pResult = (IRTCUserSearchResult *)(lvi.lParam);

        // Release the result reference
        SAFE_RELEASE(pResult);

        ListView_DeleteItem(m_hResultList, 0);
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
// CRTCSearch::DoSearch
//

HRESULT CRTCSearch::DoSearch()
{
    LONG lFNLength;
	LONG lLNLength;
	LONG lMLength;
    BSTR bstrFirstName = NULL;
	BSTR bstrLastName = NULL;
	BSTR bstrEmail = NULL;
    BSTR bstrgiveName = NULL;
	BSTR bstrSN = NULL;
	BSTR bstrmsRTCMail = NULL;
    HRESULT hr;

	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates Creating a query, setting search term, setting search 
	// preferences and searching based on first/last name or email for user search 
	//
	////////////

	// Create the search query
    IRTCUserSearchQuery * pQuery = NULL;

    hr = m_pUserSearch->CreateQuery(&pQuery);

    if (FAILED(hr))
    {
        // CreateQuery failed
        return hr;
    }

    // Determine the lengths of the various search terms
    lFNLength = (LONG) SendMessageW(m_hFirstName, WM_GETTEXTLENGTH, 0, 0);
	lLNLength = (LONG) SendMessageW(m_hLastName, WM_GETTEXTLENGTH, 0, 0);
	lMLength  = (LONG) SendMessageW(m_hEmail, WM_GETTEXTLENGTH, 0, 0);

	// If the user entered a First Name search string ...
    if (lFNLength > 0)
    {
        // Allocate a buffer for the search term
        bstrFirstName = SysAllocStringLen(NULL, lFNLength);

        if (bstrFirstName == NULL)
        {
            // SysAllocStringLen failed
            return E_OUTOFMEMORY;
        }

        // Get the search from the First Name box
        if (lFNLength != SendMessageW(m_hFirstName, WM_GETTEXT, lFNLength+1, (LPARAM)bstrFirstName))
        {
            // SendMessageW failed
            SAFE_FREE_STRING(bstrFirstName);
            return E_FAIL;
        }  

		// Allocate a buffer for the search attribute givenName
		bstrgiveName = SysAllocString(L"givenName");
	
		if (!bstrgiveName)
		{
			// out of memory
			SAFE_FREE_STRING(bstrFirstName);
			return E_OUTOFMEMORY;
		}

		// Set search term
		hr = pQuery->put_SearchTerm(bstrgiveName, bstrFirstName);
		if (FAILED(hr))
		{
			DEBUG_PRINT(("put_SearchTerm First Name Failed 0x%8x", hr));
		}

		SAFE_FREE_STRING(bstrFirstName);
		SAFE_FREE_STRING(bstrgiveName);
    }

	// If the user entered a Last Name search string ...
	if (lLNLength > 0)
    {
        // Allocate a buffer for the search term
        bstrLastName = SysAllocStringLen(NULL, lLNLength);

        if (bstrLastName == NULL)
        {
            // SysAllocStringLen failed
            return E_OUTOFMEMORY;
        }

        // Get the search from the Last Name box
        if (lLNLength != SendMessageW(m_hLastName, WM_GETTEXT, lLNLength+1, (LPARAM)bstrLastName))
        {
            // SendMessageW failed
            SAFE_FREE_STRING(bstrLastName);
            return E_FAIL;
        }  

		// Allocate a buffer for the search attribute sn
		bstrSN = SysAllocString(L"sn");
	
		if (!bstrSN)
		{
	        // out of memory
			SAFE_FREE_STRING(bstrLastName);
			return E_OUTOFMEMORY;
		}

		// Set search term
		hr = pQuery->put_SearchTerm(bstrSN, bstrLastName);
		if (FAILED(hr))
		{
			DEBUG_PRINT(("put_SearchTerm Last Name Failed 0x%8x", hr));
		}

		SAFE_FREE_STRING(bstrLastName);
		SAFE_FREE_STRING(bstrSN);
    }

	// If the user entered a Email search string ...
	if (lMLength > 0)
    {
        // Allocate a buffer for the search term
        bstrEmail = SysAllocStringLen(NULL, lMLength);

        if (bstrEmail == NULL)
        {
            // SysAllocStringLen failed
            return E_OUTOFMEMORY;
        }

        // Get the search from the Email box
        if (lMLength != SendMessageW(m_hEmail, WM_GETTEXT, lMLength+1, (LPARAM)bstrEmail))
        {
            // SendMessageW failed
            SAFE_FREE_STRING(bstrEmail);
            return E_FAIL;
        }  

		// Allocate a buffer for the search attribute msRTCMail
		bstrmsRTCMail = SysAllocString(L"msRTCMail");

		if (!bstrmsRTCMail)
		{
	        // out of memory
			SAFE_FREE_STRING(bstrEmail);
			return E_OUTOFMEMORY;
		}

		// Set search term
		hr = pQuery->put_SearchTerm(bstrmsRTCMail, bstrEmail);
		if (FAILED(hr))
		{
			DEBUG_PRINT(("put_SearchTerm E-mail Failed 0x%8x", hr));
		}

		SAFE_FREE_STRING(bstrEmail);
		SAFE_FREE_STRING(bstrmsRTCMail);
    }

    // Set max number of results to 100
    hr = pQuery->put_SearchPreference(RTCUSP_MAX_MATCHES, 100);
    if (FAILED(hr))
    {
        // put_SearchPreference failed
		DEBUG_PRINT(("put_SearchPreference Failed 0x%8x", hr));
        SAFE_RELEASE(pQuery);
        return hr;
    } 
        
    // Get a cookie
    m_lCookie = m_pWin->GetCookie();

    // Execute the user search
    hr = m_pUserSearch->ExecuteSearch(
        pQuery, m_pProfile, m_lCookie);

    SAFE_RELEASE(pQuery);

	////////////
	//
	// End RTC Functionality Code
	//
	////////////

    if (FAILED(hr))
    {
        // ExecuteSearch failed
		DEBUG_PRINT(("ExecuteQuery Failed 0x%8x", hr));
        return hr;
    }  
        
    // Set status bar text
    SetStatusText(L"Searching...");

    // Disable search button until search completes
    EnableWindow(m_hSearch, FALSE);

    // Clear current result list
    ClearResultList();

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCSearch::OnCreate
// 

LRESULT CRTCSearch::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)    
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
        return -1;
    }

	// Create the First Name Label control
    m_hfnLabel = CreateWindowEx(
        WS_EX_LEFT,
        L"STATIC",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_US_FNLABEL,
        GetModuleHandle(NULL),
        NULL);
    
    if ( !m_hfnLabel )
    {
        // CreateWindowEx failed
        return -1;
    }

	// Create the First Name control
    m_hFirstName = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_US_FIRSTNAME,
        GetModuleHandle(NULL),
        NULL);
    
    if ( !m_hFirstName )
    {
        // CreateWindowEx failed
        return -1;
    }

    // Subclass the FirstName window
    m_wpOrigFNProc = (WNDPROC)SetWindowLongPtr(m_hFirstName,
        GWLP_WNDPROC, (LONG_PTR)CRTCSearch::FNSubclassProc);
    SetWindowLongPtr(m_hFirstName, GWLP_USERDATA, (LONG_PTR)this);

	// Create the Last Name Label control
    m_hlnLabel = CreateWindowEx(
        WS_EX_LEFT,
        L"STATIC",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_US_LNLABEL,
        GetModuleHandle(NULL),
        NULL);
    
    if ( !m_hlnLabel )
    {
        // CreateWindowEx failed
        return -1;
    }

	// Create the Last Name control
    m_hLastName = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_US_LASTNAME,
        GetModuleHandle(NULL),
        NULL);
    
    if ( !m_hLastName )
    {
        // CreateWindowEx failed
        return -1;
    }

    // Subclass the Last Name window
    m_wpOrigLNProc = (WNDPROC)SetWindowLongPtr(m_hLastName,
        GWLP_WNDPROC, (LONG_PTR)CRTCSearch::LNSubclassProc);
    SetWindowLongPtr(m_hLastName, GWLP_USERDATA, (LONG_PTR)this);

	// Create the Email Label control
    m_hmLabel = CreateWindowEx(
        WS_EX_LEFT,
        L"STATIC",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_US_MLABEL,
        GetModuleHandle(NULL),
        NULL);
    
    if ( !m_hmLabel )
    {
        // CreateWindowEx failed
        return -1;
    }

	// Create the Email control
    m_hEmail = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_US_EMAIL,
        GetModuleHandle(NULL),
        NULL);
    
    if ( !m_hEmail )
    {
        // CreateWindowEx failed
        return -1;
    }

    // Subclass the Last Name window
    m_wpOrigMProc = (WNDPROC)SetWindowLongPtr(m_hEmail,
        GWLP_WNDPROC, (LONG_PTR)CRTCSearch::MSubclassProc);
    SetWindowLongPtr(m_hEmail, GWLP_USERDATA, (LONG_PTR)this);

    // Create the search button
    m_hSearch = CreateWindowExW(
        0,
        L"BUTTON",
        L"Search",
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | BS_PUSHBUTTON,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_US_SEARCH,
        GetModuleHandle(NULL),
        NULL);
    
    if ( !m_hSearch )
    {
        // CreateWindowExW failed
        return -1;
    }

    // Create the result control
    m_hResultList = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"SysListView32",
        NULL,
        WS_CHILD | WS_VISIBLE |
        LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_SORTASCENDING |
        LVS_AUTOARRANGE | LVS_REPORT,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_US_RESULTLIST,
        GetModuleHandle(NULL),
        NULL);

    if ( !m_hResultList )
    {
        // CreateWindowExW failed
        return -1;
    }

    LVCOLUMN    lvColumn;
    ZeroMemory(&lvColumn, sizeof(lvColumn));

    lvColumn.mask = LVCF_TEXT;
    lvColumn.pszText = L"Name";  
    ListView_InsertColumn(m_hResultList, 0, &lvColumn);

    lvColumn.pszText = L"URI";  
    ListView_InsertColumn(m_hResultList, 1, &lvColumn);

    lvColumn.pszText = L"Email";  
    ListView_InsertColumn(m_hResultList, 2, &lvColumn);

	lvColumn.pszText = L"Phone";  
    ListView_InsertColumn(m_hResultList, 3, &lvColumn);

    // Set focus to the edit window
    SetFocus(m_hFirstName);

    return 0;
}

/////////////////////////////////////////////
//
// CRTCSearch::OnDestroy
// 

LRESULT CRTCSearch::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam)
{ 
	// WM_DESTROY has three parameters. We will pass them to our Destroy Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);

    // Unsubclass the edit window
    SetWindowLongPtr(m_hFirstName, GWLP_WNDPROC, (LONG_PTR)m_wpOrigFNProc);

	SetWindowLongPtr(m_hLastName, GWLP_WNDPROC, (LONG_PTR)m_wpOrigLNProc);

	SetWindowLongPtr(m_hEmail, GWLP_WNDPROC, (LONG_PTR)m_wpOrigMProc);

    ClearResultList( );

	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates releasing usersearch and profile references
	//
	////////////

    // Release the profile
    SAFE_RELEASE(m_pProfile);

    // Release the user search interface
    SAFE_RELEASE(m_pUserSearch);

	////////////
	//
	// End RTC Functionality Code
	//
	////////////

    if (m_pWin)
    {
        // Remove the search from the user search list
        m_pWin->RemoveUserSearch(this);
    }
    
    return 0;
}

/////////////////////////////////////////////
//
// CRTCSearch::OnClose
// 

LRESULT CRTCSearch::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
// CRTCSearch::OnSize
// 

LRESULT CRTCSearch::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam)    
{
    // Resize the status bar
    SendMessage(m_hStatusBar, uMsg, wParam, lParam);
        
    RECT rcWnd, rcStatusBar, rcfnLabel, rcFirstName, rclnLabel, rcLastName, rcmLabel, rcEmail, rcSearch, rcResultList;
    const int SIZE_EDGE = 5;
    const int SIZE_BUTTON_X = 60;
    const int SIZE_BUTTON_Y = 24;
	const int SIZE_LABEL_X = 80;
	const int SIZE_LABEL_Y = 20;
	wchar_t *fnlabeltext = L"First Name:\0";
	wchar_t *lnlabeltext = L"Last Name:\0";
	wchar_t *mlabeltext = L"Email:\0";

    GetClientRect(m_hWnd, &rcWnd);    
    GetClientRect(m_hStatusBar, &rcStatusBar);

    // Resize the search button
    rcSearch.bottom = rcWnd.top + SIZE_BUTTON_Y + SIZE_EDGE;
    rcSearch.top = rcWnd.top + SIZE_EDGE;
    rcSearch.right = rcWnd.right - SIZE_EDGE;
    rcSearch.left = rcSearch.right - SIZE_BUTTON_X; 

    MoveWindow(
        m_hSearch,
        rcSearch.left,
        rcSearch.top,
        (rcSearch.right - rcSearch.left),
        (rcSearch.bottom - rcSearch.top),
        TRUE);
	
	// Resize the FirstName Label control
    rcfnLabel.bottom = rcSearch.top + SIZE_LABEL_Y;
    rcfnLabel.top = rcSearch.top;
    rcfnLabel.right = rcWnd.left + SIZE_LABEL_X + SIZE_EDGE;
    rcfnLabel.left = rcWnd.left + SIZE_EDGE;

    MoveWindow(
        m_hfnLabel,
        rcfnLabel.left,
        rcfnLabel.top,
        (rcfnLabel.right - rcfnLabel.left),
        (rcfnLabel.bottom - rcfnLabel.top),
        TRUE);

	SendMessageW(m_hfnLabel, WM_SETTEXT, 0, (LPARAM)fnlabeltext);

    // Resize the FirstName control
    rcFirstName.bottom = rcSearch.bottom;
    rcFirstName.top = rcSearch.top;
    rcFirstName.right = rcSearch.left - SIZE_EDGE;
    rcFirstName.left = rcfnLabel.right;

    MoveWindow(
        m_hFirstName,
        rcFirstName.left,
        rcFirstName.top,
        (rcFirstName.right - rcFirstName.left),
        (rcFirstName.bottom - rcFirstName.top),
        TRUE);

	// Resize the LastName Label control
    rclnLabel.bottom = rcFirstName.bottom + SIZE_LABEL_Y + SIZE_EDGE;;
    rclnLabel.top = rcFirstName.bottom + SIZE_EDGE;
    rclnLabel.right = rcWnd.left + SIZE_LABEL_X + SIZE_EDGE;
    rclnLabel.left = rcWnd.left + SIZE_EDGE;

    MoveWindow(
        m_hlnLabel,
        rclnLabel.left,
        rclnLabel.top,
        (rclnLabel.right - rclnLabel.left),
        (rclnLabel.bottom - rclnLabel.top),
        TRUE);

	SendMessageW(m_hlnLabel, WM_SETTEXT, 0, (LPARAM)lnlabeltext);

	// Resize the LastName control
    rcLastName.bottom = rcFirstName.bottom + SIZE_BUTTON_Y + SIZE_EDGE;
    rcLastName.top = rcFirstName.bottom + SIZE_EDGE;
    rcLastName.right = rcSearch.left - SIZE_EDGE;
    rcLastName.left = rclnLabel.right;

    MoveWindow(
        m_hLastName,
        rcLastName.left,
        rcLastName.top,
        (rcLastName.right - rcLastName.left),
        (rcLastName.bottom - rcLastName.top),
        TRUE);

	// Resize the Email Label control
    rcmLabel.bottom = rcLastName.bottom + SIZE_LABEL_Y + SIZE_EDGE;;
    rcmLabel.top = rcLastName.bottom + SIZE_EDGE;
    rcmLabel.right = rcWnd.left + SIZE_LABEL_X + SIZE_EDGE;
    rcmLabel.left = rcWnd.left + SIZE_EDGE;

    MoveWindow(
        m_hmLabel,
        rcmLabel.left,
        rcmLabel.top,
        (rcmLabel.right - rcmLabel.left),
        (rcmLabel.bottom - rcmLabel.top),
        TRUE);

	SendMessageW(m_hmLabel, WM_SETTEXT, 0, (LPARAM)mlabeltext);

	// Resize the Email control
    rcEmail.bottom = rcLastName.bottom + SIZE_BUTTON_Y + SIZE_EDGE;
    rcEmail.top = rcLastName.bottom + SIZE_EDGE;
    rcEmail.right = rcSearch.left - SIZE_EDGE;
    rcEmail.left = rcmLabel.right;

    MoveWindow(
        m_hEmail,
        rcEmail.left,
        rcEmail.top,
        (rcEmail.right - rcEmail.left),
        (rcEmail.bottom - rcEmail.top),
        TRUE);

    // Resize the result control
    rcResultList.bottom = rcWnd.bottom - rcStatusBar.bottom - SIZE_EDGE;
    rcResultList.top = rcEmail.bottom + SIZE_EDGE;
    rcResultList.right = rcWnd.right - SIZE_EDGE;
    rcResultList.left = rcWnd.left + SIZE_EDGE;

    MoveWindow(
        m_hResultList,
        rcResultList.left,
        rcResultList.top,
        (rcResultList.right - rcResultList.left),
        (rcResultList.bottom - rcResultList.top),
        TRUE);

    LVCOLUMN lvColumn;
    ZeroMemory(&lvColumn, sizeof(lvColumn));
    int nWidth = (rcResultList.right - rcResultList.left - GetSystemMetrics(SM_CXVSCROLL) - 5);

    lvColumn.mask = LVCF_WIDTH;
    lvColumn.cx = nWidth*1/4;    
    ListView_SetColumn(m_hResultList, 0, &lvColumn);

    lvColumn.cx = nWidth*1/4;    
    ListView_SetColumn(m_hResultList, 1, &lvColumn);

    lvColumn.cx = nWidth*1/4;    
    ListView_SetColumn(m_hResultList, 2, &lvColumn);

	 lvColumn.cx = nWidth*1/4;    
    ListView_SetColumn(m_hResultList, 3, &lvColumn);

    return 0;
}

/////////////////////////////////////////////
//
// CRTCSearch::OnCommand
// 

LRESULT CRTCSearch::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// WM_COMMAND has three parameters. We will pass them to our Command Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);

    HRESULT hr = S_OK;

    switch(LOWORD(wParam))
    {
    case IDC_US_SEARCH:
        DoSearch();
        break;
    }

    return hr;
}

/////////////////////////////////////////////
//
// CRTCSearch::OnNotify
// 

LRESULT CRTCSearch::OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam)
{    
	// WM_NOTIFY has three parameters. We will pass them to our Notify Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(uMsg);

    int idCtrl = (int)wParam;
    LPNMHDR pnmh = (LPNMHDR)lParam;
    HRESULT hr;

    if ( (pnmh->code == NM_CLICK) ||
         (pnmh->code == NM_RCLICK) )
    {
        if ( idCtrl == IDC_US_RESULTLIST )
        {
            // The user clicked on the result list
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
                // The user clicked on a result
                LVITEM lvi;
                ZeroMemory(&lvi, sizeof(LVITEM));
    
                lvi.mask = LVIF_PARAM;
                lvi.iItem = iRes;

                // Get the result item
                if (!ListView_GetItem(m_hResultList, &lvi))
                {
                    // ListView_GetItem failed;
                    return 0;
                }
               
				////////////
				//
				// Begin RTC Functionality Code
				//
				// This code demonstrates obtaining user search results and updating UI.
				//
				////////////

                IRTCUserSearchResult * pResult = (IRTCUserSearchResult *)(lvi.lParam);                

                // Show the result menu
                HMENU hMenuRes = LoadMenu( 
                    GetModuleHandle(NULL),
                    MAKEINTRESOURCE(IDR_MENU_USER));

                HMENU hMenu = GetSubMenu(hMenuRes, 0);
          
                // Get result values
                BSTR bstrName = NULL;
                BSTR bstrURI = NULL;
                BSTR bstrPhone = NULL;
                
                hr = pResult->get_Value(RTCUSC_DISPLAYNAME, &bstrName);

                if (FAILED(hr))
                {
                    EnableMenuItem(hMenu, ID_USER_ADDBUDDY, MF_GRAYED);
                }

                hr = pResult->get_Value(RTCUSC_URI, &bstrURI);

                if (FAILED(hr))
                {
                    EnableMenuItem(hMenu, ID_USER_CALL, MF_GRAYED);
                    EnableMenuItem(hMenu, ID_USER_MESSAGE, MF_GRAYED);
                    EnableMenuItem(hMenu, ID_USER_ADDBUDDY, MF_GRAYED);
                }

                hr = pResult->get_Value(RTCUSC_PHONE, &bstrPhone);

                if (FAILED(hr))
                {
                    EnableMenuItem(hMenu, ID_USER_PHONE, MF_GRAYED);
                }

				////////////
				//
				// End RTC Functionality Code
				//
				////////////

                // Show the popup menu
                UINT uID = TrackPopupMenu(hMenu,
                    TPM_LEFTALIGN | TPM_RIGHTBUTTON |
                    TPM_NONOTIFY | TPM_RETURNCMD,
                    pt.x, pt.y, 0, m_hWnd, NULL);

                switch (uID)
                {
                case ID_USER_CALL:
                    DEBUG_PRINT(("ID_USER_CALL"));
                    // Call the user                   
                    m_pWin->DoCall(RTCST_PC_TO_PC, bstrURI, bstrName);
                    break;

                case ID_USER_MESSAGE:
                    DEBUG_PRINT(("ID_USER_MESSAGE"));
                    // Send a message to the user  
                    m_pWin->DoCall(RTCST_MULTIPARTY_IM, bstrURI, bstrName);
                    break;

                case ID_USER_PHONE:
                    DEBUG_PRINT(("ID_USER_PHONE"));
                    // Phone the user                      
                    m_pWin->DoCall(RTCST_PC_TO_PHONE, bstrPhone, bstrName);
                    break;

                case ID_USER_ADDBUDDY:
                    DEBUG_PRINT(("ID_USER_ADDBUDDY"));
                    // Add the user as a buddy    
                    m_pWin->DoAddBuddy(bstrURI, bstrName);
                    break;
                }

                SAFE_FREE_STRING(bstrName);
                SAFE_FREE_STRING(bstrURI);
                SAFE_FREE_STRING(bstrPhone);
            }
        }
    }

    return 0;
}

/////////////////////////////////////////////
//
// CRTCSearch::DeliverUserSearchResults
//

HRESULT CRTCSearch::DeliverUserSearchResults(HRESULT hrStatus, IRTCEnumUserSearchResults * pEnum)
{
    HRESULT hr;

    // Enable search button
    EnableWindow(m_hSearch, TRUE);

    if (FAILED(hrStatus))
    {
        // ExecuteSearch failed
        SetStatusText(L"Search failed");
    }
    else
    {
        IRTCUserSearchResult * pResult = NULL;

        while (pEnum->Next(1, &pResult, NULL) == S_OK)
        {
            hr = UpdateResultList(pResult);

            pResult->Release();

            if (FAILED(hr))
            {
                // UpdateResultList failed
            }
        }

        // Set status bar text
        SetStatusText(L"Search complete");
    }

    return S_OK;
}
