// rtcim.cpp
//

#include "stdafx.h"

#if UP_LEVEL <= 0
HRESULT DoDisplayMessageDnl(HWND m_hDisplay,HWND m_hWnd,HWND m_hEdit,PWSTR szUser, PWSTR szMessage);
#endif

// Font definition
static CHARFORMAT cfDefault =
{
    sizeof(CHARFORMAT),
    CFM_EFFECTS | CFM_PROTECTED | CFM_SIZE | CFM_OFFSET | CFM_COLOR | CFM_CHARSET | CFM_FACE,
    CFE_AUTOCOLOR,      // effects
    200,                // height, 200 twips == 10 points
    0,                  // offset
    0,                  // color (not used since CFE_AUTOCOLOR is specified)
    DEFAULT_CHARSET,
    FF_SWISS,           // pitch and family
    _T("Microsoft Sans Serif") // face name
};

/////////////////////////////////////////////
//
// CRTCIMSession::CRTCIMSession
// 

CRTCIMSession::CRTCIMSession() : CRTCSession()
{
    m_hDisplay = NULL;
    m_hEdit = NULL;
    m_hSend = NULL;
    m_fTyping = FALSE;
    m_wpOrigEditProc = NULL;
}

/////////////////////////////////////////////
//
// CRTCIMSession::~CRTCIMSession
// 

CRTCIMSession::~CRTCIMSession()
{
}

/////////////////////////////////////////////
//
// CRTCIMSession::RegisterClass
//

HRESULT CRTCIMSession::RegisterClass()
{
    // Register the window class
    WNDCLASS wc;
    ATOM atom;

    ZeroMemory(&wc, sizeof(WNDCLASS));

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)CRTCIMSession::WindowProc;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.hIcon         = NULL;
    wc.hCursor       =
        LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = 
        GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU_IM);
    wc.lpszClassName = IM_CLASS;

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
// CRTCIMSession::WindowProc
// 

LRESULT CALLBACK CRTCIMSession::WindowProc(
  HWND hWnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
    CRTCIMSession * me = NULL;
    LRESULT  lr = 0;

    if ( uMsg == WM_CREATE )
    {
        // Create an instance of the class
        me = new CRTCIMSession;
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
        me = (CRTCIMSession *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

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

        default:
            lr = DefWindowProc( hWnd, uMsg, wParam, lParam );
        }
    }

    return lr;
}

/////////////////////////////////////////////
//
// CRTCIMSession::EditSubclassProc
// 

LRESULT CALLBACK CRTCIMSession::EditSubclassProc(
  HWND hWnd,      // handle to window
  UINT uMsg,      // message identifier
  WPARAM wParam,  // first message parameter
  LPARAM lParam   // second message parameter
)
{
    CRTCIMSession * me = NULL;
    me = (CRTCIMSession *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    if ( uMsg == WM_KEYDOWN )
    {
        // Intercept the return key from the edit box
        // and press the send button
        if ( (wParam == VK_RETURN) &&
             !(GetKeyState(VK_CONTROL) & 0x8000))
        {
            SendMessage(me->m_hWnd, WM_COMMAND,
                MAKEWPARAM(IDC_IM_SEND, BN_CLICKED),
                (LPARAM)me->m_hSend);

            return 0;
        }
        else if ( uMsg == WM_CHAR )
        {
            // Intercept the return key from the edit box
            if (wParam == VK_RETURN)
            {           
                return 0;
            }
        }
    }

    // Call the original edit window procedure
    return CallWindowProc(
        me->m_wpOrigEditProc,
        hWnd, uMsg, wParam, lParam);
}

/////////////////////////////////////////////
//
// CRTCIMSession::UpdateParticipantList
//

HRESULT CRTCIMSession::UpdateParticipantList(IRTCParticipant * pParticipant)
{
    HRESULT hr;
////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates getting participant name and updating participant list UI
//
////////////

    // Get the name of the participant
    BSTR bstrName = NULL;

    hr = pParticipant->get_Name(&bstrName);

    if (SUCCEEDED(hr) && !wcscmp(bstrName, L""))
    {
        // Treat an emptry string as a failure
        SAFE_FREE_STRING(bstrName);
        hr = E_FAIL;
    }

    if (FAILED(hr))
    {     
        hr = pParticipant->get_UserURI(&bstrName);

        if (FAILED(hr))
        {
            // get_UserURI failed
            return hr;
        }   
    }

    // Is the participant in the list?
    LVFINDINFO lvfi;    
    ZeroMemory(&lvfi, sizeof(LVFINDINFO));

    lvfi.flags = LVFI_PARAM;
    lvfi.lParam = (LPARAM)pParticipant;

    int iItem = ListView_FindItem(m_hParticipantList, -1, &lvfi);

    if (iItem == -1)
    {
        // Participant is not in the list
        // Add the participant to the list  
        LVITEM lvi;
        ZeroMemory(&lvi, sizeof(LVITEM));

        lvi.mask = LVIF_TEXT | LVIF_PARAM;
        lvi.pszText = bstrName;
        lvi.lParam = (LPARAM)pParticipant;

        iItem = ListView_InsertItem(m_hParticipantList, &lvi);

        if (iItem == -1)
        {
            // ListView_InsertItem failed
            SAFE_FREE_STRING(bstrName);
            return E_FAIL;
        }

        // An RTC participant reference will be kept by the list
        // Add the reference here
        pParticipant->AddRef();
////////////
//
// End RTC Functionality Code
//
////////////
    }
    else
    {
        // Participant is in the list
        // Update the list entry
        LVITEM lvi;
        ZeroMemory(&lvi, sizeof(LVITEM));

        lvi.mask = LVIF_TEXT;
        lvi.pszText = bstrName;
        lvi.iItem = iItem;

        int iRes = ListView_SetItem(m_hParticipantList, &lvi);

        if (iRes == -1)
        {
            // ListView_SetItem failed 
            SAFE_FREE_STRING(bstrName);
            return E_FAIL;
        }
    }

    SAFE_FREE_STRING(bstrName);
////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates obtaining particioant state to update the UI
//
////////////

    // Get the participant state
    RTC_PARTICIPANT_STATE enState;

    hr = pParticipant->get_State(&enState);

    if (FAILED(hr))
    {
        // get_State failed
        return hr;
    }    
////////////
//
// End RTC Functionality Code
//
////////////

    // Set the text for the participant state
    switch(enState)
    {
    case RTCPS_IDLE:
        ListView_SetItemText(m_hParticipantList, iItem, 1, L"Idle");
        break;
    case RTCPS_PENDING:
        ListView_SetItemText(m_hParticipantList, iItem, 1, L"Pending");
        break;
    case RTCPS_INCOMING:
        ListView_SetItemText(m_hParticipantList, iItem, 1, L"Incoming");
        break;
    case RTCPS_ANSWERING:
        ListView_SetItemText(m_hParticipantList, iItem, 1, L"Answering");
        break;
    case RTCPS_INPROGRESS:
        ListView_SetItemText(m_hParticipantList, iItem, 1, L"Inprogress");
        break;
    case RTCPS_ALERTING:
        ListView_SetItemText(m_hParticipantList, iItem, 1, L"Alerting");
        break;
    case RTCPS_CONNECTED:
        ListView_SetItemText(m_hParticipantList, iItem, 1, L"Connected");
        break;
    case RTCPS_DISCONNECTING:
        ListView_SetItemText(m_hParticipantList, iItem, 1, L"Disconnecting");
        break;
    case RTCPS_DISCONNECTED:
        ListView_SetItemText(m_hParticipantList, iItem, 1, L"Disconnected");
        break;
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCIMSession::ClearParticipantList
// 

HRESULT CRTCIMSession::ClearParticipantList()
{
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(LVITEM));
    
    lvi.mask = LVIF_PARAM;
////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates releasing IRTCParticipant references
//
////////////

    // Iterate through the list and remove each item
    while (ListView_GetItem(m_hParticipantList, &lvi))
    {
        IRTCParticipant * pParticipant = (IRTCParticipant *)(lvi.lParam);

        // Release the participant reference
        SAFE_RELEASE(pParticipant);

        ListView_DeleteItem(m_hParticipantList, 0);
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
// CRTCIMSession::DoSendMessage
//

HRESULT CRTCIMSession::DoSendMessage()
{
    LONG cch;
    BSTR bstrMessage = NULL;
    HRESULT hr;
    
    // Determine the length of the outgoing message
    // in the edit box
    cch = (LONG) SendMessageW(m_hEdit, WM_GETTEXTLENGTH, 0, 0);

    if (cch > 0)
    {
        // Allocate a buffer for the outgoing message
        bstrMessage = SysAllocStringLen(NULL, cch);

        if (bstrMessage == NULL)
        {
            // SysAllocStringLen failed
            return E_OUTOFMEMORY;
        }

        // Get the outgoing message from the edit box
        if (cch != SendMessageW(m_hEdit, WM_GETTEXT, cch+1, (LPARAM)bstrMessage))
        {
            // SendMessageW failed
            SAFE_FREE_STRING(bstrMessage);
            return E_FAIL;
        }       

        // Get the local user name
        BSTR bstrName = NULL;

        hr = m_pWin->GetUserName(&bstrName);

        if (SUCCEEDED(hr) && !wcscmp(bstrName, L""))
        {
            // Treat an emptry string as a failure
            SAFE_FREE_STRING(bstrName);
            hr = E_FAIL;
        }

        if (FAILED(hr))
        {
            hr = m_pWin->GetUserURI(&bstrName);

            if (FAILED(hr))
            {
                // GetUserURI failed
                SAFE_FREE_STRING(bstrMessage);
                return hr;
            }
        }

        // Display the outgoing message
        DoDisplayMessage(bstrName, bstrMessage);

        SAFE_FREE_STRING(bstrName);

        // Clear the edit box
        SetWindowText(m_hEdit, L"");
		////////////
		//
		// Begin RTC Functionality Code
		//
		// This code demonstrates sending an IM
		//
		////////////

        // Send the outgoing message
        hr = m_pSession->SendMessage(NULL, bstrMessage, 0);

        SAFE_FREE_STRING(bstrMessage);

        if (FAILED(hr))
        {
            // SendMessage failed
            return hr;
        }     
    }

    return S_OK;
	////////////
	//
	// End RTC Functionality Code
	//
	////////////

}

/////////////////////////////////////////////
//
// CRTCIMSession::DoDisplayMessage
//

HRESULT CRTCIMSession::DoDisplayMessage(PWSTR szUser, PWSTR szMessage)
{

#if UP_LEVEL > 0
    // Select the end of the text in the edit control
    SendMessage(m_hDisplay, EM_SETSEL, -1, -1);

    // Set format for the user text
    CHARFORMAT cf;
    PARAFORMAT pf;

    cf.cbSize = sizeof(CHARFORMAT);
    cf.dwMask = CFM_COLOR;
    cf.dwEffects = 0;
    cf.crTextColor = RGB(0,128,128);

    SendMessage(m_hDisplay, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

    pf.cbSize = sizeof(PARAFORMAT);
    pf.dwMask = PFM_STARTINDENT;
    pf.dxStartIndent = 50;

    SendMessage(m_hDisplay, EM_SETPARAFORMAT, 0, (LPARAM)&pf);

    // Paste the user text in the edit control
    SendMessageW(m_hDisplay, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)szUser);
    SendMessageW(m_hDisplay, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)L" says:\n");

    // Set format for the message text
    cf.cbSize = sizeof(CHARFORMAT);
    cf.dwMask = CFM_COLOR;
    cf.dwEffects = CFE_AUTOCOLOR;
    cf.crTextColor = 0;

    SendMessage(m_hDisplay, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

    pf.cbSize = sizeof(PARAFORMAT);
    pf.dwMask = PFM_STARTINDENT;
    pf.dxStartIndent = 200;

    SendMessage(m_hDisplay, EM_SETPARAFORMAT, 0, (LPARAM)&pf);

    // Paste the message text in the edit control
    SendMessageW(m_hDisplay, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)szMessage);

    // Paste a new line in the edit control
    SendMessageW(m_hDisplay, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)L"\n");

    // Scroll to the bottom of the edit control
    SendMessage(m_hDisplay, WM_VSCROLL, SB_BOTTOM, 0);
#else  //UP_LEVEL > 0
    //Applicable for downlevel, especially for NT and below where the latest version of RichEditCtl is not available by default.
    DoDisplayMessageDnl(m_hDisplay,m_hWnd,m_hEdit,szUser,szMessage);
#endif //UP_LEVEL > 0

    return S_OK;
}


#if UP_LEVEL <= 0

HRESULT DoDisplayMessageDnl(HWND m_hDisplay,HWND m_hWnd,HWND m_hEdit,PWSTR szUser, PWSTR szMessage)
{
    // Select the end of the text in the edit control
    SendMessage(m_hDisplay, EM_SETSEL, (WPARAM) -1, (LPARAM) -1);

    // Set format for the user text
    CHARFORMAT cf;
    PARAFORMAT pf;

    RECT        DisplayRect;        
    TEXTMETRIC  tm;           // Structure returned by GetTextMetrics()
    SCROLLINFO  si;           // Structure returned by GetScrollInfo() 
                              // to find the scroll box position 
    long        lIMWndHeight   =0; // Window Height of the Instance Message
    long        lNoScrollLnCnt =0;  // Max. no. of lines that the IM
                                 // window can accomodate.
    
    long        lPrvLnCnt =0, // Previous line count
                lCurLnCnt =0, // Current line count
                lNewLnCnt =0; // New line count.

    ZeroMemory(&DisplayRect,sizeof(DisplayRect));
    ZeroMemory(&tm,sizeof(tm));
    ZeroMemory(&si,sizeof(si));  

    lPrvLnCnt = (LONG) SendMessage(m_hDisplay,EM_GETLINECOUNT,0,0);

    //
    // Set selection to end of the display box
    //

    int nLastChar =  (int)SendMessage(m_hDisplay, WM_GETTEXTLENGTH, 0, 0 );

    CHARRANGE charRange = {0};
    charRange.cpMin = charRange.cpMax = nLastChar + 1;

    SendMessage(m_hDisplay, EM_EXSETSEL, 0, (LPARAM)&charRange );

 
    cf.cbSize = sizeof(CHARFORMAT);
    cf.dwMask = CFM_COLOR;
    cf.dwEffects = 0;
    cf.crTextColor = RGB(0,128,128);
    SendMessage(m_hDisplay,EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
 
    SendMessageW(m_hDisplay, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)szUser);
    SendMessageW(m_hDisplay, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)L" says:\n");

    pf.cbSize = sizeof(PARAFORMAT);
    pf.dwMask = PFM_STARTINDENT;
    pf.dxStartIndent = 200;

    SendMessage(m_hDisplay, EM_SETPARAFORMAT, 0, (LPARAM)&pf);

    // Paste the message text in the edit control
    SendMessageW(m_hDisplay, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)szMessage);

    // Paste a new line in the edit control
    SendMessageW(m_hDisplay, EM_REPLACESEL, (WPARAM)FALSE, (LPARAM)L"\n");

    // Scroll to the bottom of the edit control
    // SendMessage(m_hDisplay, WM_VSCROLL, SB_BOTTOM, 0);

   
    // Getting the number of lines in the Display Window
    lCurLnCnt = (LONG) SendMessage(m_hDisplay,EM_GETLINECOUNT,0,0);

    // Gets the client rectangle.
    GetClientRect(m_hDisplay,&DisplayRect);

    // Get the window height.
    lIMWndHeight = DisplayRect.bottom - DisplayRect.top;

    // Get the number of lines the window can accomodate.
    // before the scroll bar comes up

    GetTextMetrics(GetDC(m_hDisplay),&tm); 
    lNoScrollLnCnt = ( lIMWndHeight / tm.tmHeight );

     // Check if the scroll bar has come up 
    if( lNoScrollLnCnt < lCurLnCnt )
    {
        // Number of new lines added 
        lNewLnCnt = lCurLnCnt - lPrvLnCnt;

        // Check if the current message length is very big.            
        if ( lCurLnCnt > lNoScrollLnCnt)
        {
            // Scroll appropriate number of lines in the window.
            lNewLnCnt -= lNoScrollLnCnt ;
        }

        for (int i = 1; i <= lNewLnCnt; i++)
        {
            // Scroll only the required number of lines
            SendMessage(m_hDisplay,WM_VSCROLL, SB_LINEDOWN, 0 );
        }

        
        GetScrollInfo(m_hDisplay,SB_VERT,&si);

        // Check if the IM window is the active window 
        if ( GetActiveWindow() == m_hWnd )
        {
            // Send the mouse click message
            SendMessage(m_hDisplay,WM_LBUTTONDOWN, MK_LBUTTON, si.nPos);

            SendMessage(m_hDisplay,WM_LBUTTONDOWN, MK_LBUTTON, DisplayRect.bottom);
            // Set the focus back to edit control
            SetFocus(m_hEdit);
        }
    }
    
    return S_OK;

}
#endif //UP_LEVEL <= 0

/////////////////////////////////////////////
//
// CRTCIMSession::DoSendTyping
//

HRESULT CRTCIMSession::DoSendTyping()
{
    BOOL fTyping;
    HRESULT hr;

    // Is the edit box empty?
    fTyping = (SendMessage(m_hEdit, WM_GETTEXTLENGTH, 0, 0) > 0);

    if (m_fTyping != fTyping)
    {
        // Typing status has changed
        m_fTyping = fTyping;

        hr = m_pSession->SendMessageStatus(
            m_fTyping ? RTCMUS_TYPING : RTCMUS_IDLE,
            0);

        if (FAILED(hr))
        {
            // SendMessageStatus failed
            return hr;
        }
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCIMSession::DoDisplayTyping
//

HRESULT CRTCIMSession::DoDisplayTyping(PWSTR szUser, BOOL fTyping)
{
    if (fTyping)
    {
        // Display typing status in the status bar.
        WCHAR szTyping[MAX_STRING];
        _snwprintf(szTyping, MAX_STRING, L"%s is typing.", szUser);
        szTyping[MAX_STRING-1] = L'\0';


        SetStatusText(szTyping);
    }
    else
    {
        // User is not longer typing. Display the session
        // state in the status bar.
        DeliverSessionState(m_enState);
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCIMSession::DoAddParticipant
//

HRESULT CRTCIMSession::DoAddParticipant(BSTR bstrURI)
{
    HRESULT hr;
	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates Adding a participant to a session
	//
	////////////

    // Add the participant to the session
    hr = m_pSession->AddParticipant(
        bstrURI,
        NULL,
        NULL
        );

    if (FAILED(hr))
    {
        // AddParticipant failed
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
// CRTCIMSession::DoRemoveParticipant
//

HRESULT CRTCIMSession::DoRemoveParticipant(IRTCParticipant * pParticipant)
{
    // Is the participant in the list?
    LVFINDINFO lvfi;    
    ZeroMemory(&lvfi, sizeof(LVFINDINFO));

    lvfi.flags = LVFI_PARAM;
    lvfi.lParam = (LPARAM)pParticipant;

    int iItem = ListView_FindItem(m_hParticipantList, -1, &lvfi);
	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates releasing IRTCParticipant references
	//
	////////////

    if (iItem >= 0)
    {
        // Participant is in the list
        // Remove the list entry
        SAFE_RELEASE(pParticipant);
        ListView_DeleteItem(m_hParticipantList, iItem);
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
// CRTCIMSession::OnCreate
// 

LRESULT CRTCIMSession::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)    
{
    // Call the base class
    CRTCSession::OnCreate(uMsg, wParam, lParam);

    // Create the display control
    m_hDisplay = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        RICHEDIT_CLASS,
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL |
        ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_IM_DISPLAY,
        GetModuleHandle(NULL),
        NULL);
    
    if ( !m_hDisplay )
    {
        // CreateWindowEx failed
        return -1;
    }

    SendMessage(m_hDisplay, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cfDefault); 

    // Create the edit control
    m_hEdit = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        RICHEDIT_CLASS,
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL |
        ES_MULTILINE | ES_AUTOVSCROLL,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_IM_EDIT,
        GetModuleHandle(NULL),
        NULL);
    
    if ( !m_hEdit )
    {
        // CreateWindowEx failed
        return -1;
    }

    SendMessage(m_hEdit, EM_SETEVENTMASK, 0, ENM_CHANGE);
    SendMessage(m_hEdit, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cfDefault); 
    
    // Subclass the edit window
    m_wpOrigEditProc = (WNDPROC)SetWindowLongPtr(m_hEdit,
        GWLP_WNDPROC, (LONG_PTR)CRTCIMSession::EditSubclassProc);
    SetWindowLongPtr(m_hEdit, GWLP_USERDATA, (LONG_PTR)this);

    // Create the send button
    m_hSend = CreateWindowExW(
        0,
        L"BUTTON",
        L"Send",
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | BS_PUSHBUTTON,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_IM_SEND,
        GetModuleHandle(NULL),
        NULL);
    
    if ( !m_hSend )
    {
        // CreateWindowExW failed
        return -1;
    }

    // Create the participant control
    m_hParticipantList = CreateWindowExW(
        WS_EX_CLIENTEDGE,
        L"SysListView32",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS |
        LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_SORTASCENDING |
        LVS_AUTOARRANGE | LVS_REPORT,
        0, 0,
        0, 0,
        m_hWnd,
        (HMENU)IDC_IM_PARTLIST,
        GetModuleHandle(NULL),
        NULL);

    if ( !m_hParticipantList )
    {
        // CreateWindowExW failed
        return -1;
    }

    LVCOLUMN    lvColumn;
    ZeroMemory(&lvColumn, sizeof(lvColumn));

    lvColumn.mask = LVCF_TEXT;
    lvColumn.pszText = L"Participant";  
    ListView_InsertColumn(m_hParticipantList, 0, &lvColumn);

    lvColumn.pszText = L"Status";  
    ListView_InsertColumn(m_hParticipantList, 1, &lvColumn);

    // Set focus to the edit window
    SetFocus(m_hEdit);

    return 0;
}

/////////////////////////////////////////////
//
// CRTCIMSession::OnDestroy
// 

LRESULT CRTCIMSession::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam)
{ 
    // Clear participant list
    ClearParticipantList();

    // Call the base class
    CRTCSession::OnDestroy(uMsg, wParam, lParam);

    // Unsubclass the edit window
    SetWindowLongPtr(m_hEdit, GWLP_WNDPROC, (LONG_PTR)m_wpOrigEditProc);

    return 0;
}

/////////////////////////////////////////////
//
// CRTCIMSession::OnSize
// 

LRESULT CRTCIMSession::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam)    
{
    // Call the base class
    CRTCSession::OnSize(uMsg, wParam, lParam);
        
    RECT rcWnd, rcStatusBar, rcDisplay, rcEdit, rcSend, rcPartList;
    const int SIZE_EDGE = 5;
    const int SIZE_BUTTON = 60;
    const int SIZE_PART_LIST = 70;

    GetClientRect(m_hWnd, &rcWnd);    
    GetClientRect(m_hStatusBar, &rcStatusBar);

    // Resize the send button
    rcSend.bottom = rcWnd.bottom -
        (rcStatusBar.bottom - rcStatusBar.top) -
        SIZE_EDGE;
    rcSend.top = rcSend.bottom - SIZE_BUTTON;
    rcSend.right = rcWnd.right - SIZE_EDGE;
    rcSend.left = rcSend.right - SIZE_BUTTON; 

    MoveWindow(
        m_hSend,
        rcSend.left,
        rcSend.top,
        (rcSend.right - rcSend.left),
        (rcSend.bottom - rcSend.top),
        TRUE);

    // Resize the edit control
    rcEdit.bottom = rcSend.bottom;
    rcEdit.top = rcSend.top;
    rcEdit.right = rcSend.left - SIZE_EDGE;
    rcEdit.left = rcWnd.left + SIZE_EDGE;

    MoveWindow(
        m_hEdit,
        rcEdit.left,
        rcEdit.top,
        (rcEdit.right - rcEdit.left),
        (rcEdit.bottom - rcEdit.top),
        TRUE);

    // Resize the participant control
    rcPartList.bottom = rcWnd.top + SIZE_EDGE + SIZE_PART_LIST;
    rcPartList.top = rcWnd.top + SIZE_EDGE;
    rcPartList.right = rcWnd.right - SIZE_EDGE;
    rcPartList.left = rcWnd.left + SIZE_EDGE;

    MoveWindow(
        m_hParticipantList,
        rcPartList.left,
        rcPartList.top,
        (rcPartList.right - rcPartList.left),
        (rcPartList.bottom - rcPartList.top),
        TRUE);

    LVCOLUMN lvColumn;
    ZeroMemory(&lvColumn, sizeof(lvColumn));
    int nWidth = (rcPartList.right - rcPartList.left - GetSystemMetrics(SM_CXVSCROLL) - 5);

    lvColumn.mask = LVCF_WIDTH;
    lvColumn.cx = nWidth*3/5;    
    ListView_SetColumn(m_hParticipantList, 0, &lvColumn);

    lvColumn.cx = nWidth*2/5;    
    ListView_SetColumn(m_hParticipantList, 1, &lvColumn);

    // Resize the display control
    rcDisplay.bottom = rcEdit.top - SIZE_EDGE;
    rcDisplay.top = rcPartList.bottom + SIZE_EDGE;
    rcDisplay.right = rcWnd.right - SIZE_EDGE;
    rcDisplay.left = rcWnd.left + SIZE_EDGE;
    
    MoveWindow(
        m_hDisplay,
        rcDisplay.left,
        rcDisplay.top,
        (rcDisplay.right - rcDisplay.left),
        (rcDisplay.bottom - rcDisplay.top),
        TRUE);

    return 0;
}

/////////////////////////////////////////////
//
// CRTCIMSession::OnCommand
// 

LRESULT CRTCIMSession::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// WM_COMMAND has three parameters. We will pass them to our Command Proc for future use
	// They are not all currently used.

	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(uMsg);

    HRESULT hr;

    if (HIWORD(wParam) == EN_CHANGE)
    {
        switch(LOWORD(wParam))
        {
        case IDC_IM_EDIT:
            DoSendTyping();
            break;
        }
    }
    else
    {
        switch(LOWORD(wParam))
        {
        case ID_FILE_EXIT:
            PostMessage(m_hWnd, WM_CLOSE, 0, 0);
            break;

        case IDC_IM_SEND:
            DoSendMessage();
            break;

        case ID_ACTION_ADDPARTICIPANT:
            {
                BSTR bstrURI = NULL;

                // Show the call dialog
                hr = ShowAddressDialog(m_hWnd, L"Add Participant", &bstrURI, NULL);

                if (FAILED(hr))
                {
                    // ShowAddressDialog failed
                    break;
                }

                // Add a participant
                DoAddParticipant(bstrURI);

                SAFE_FREE_STRING(bstrURI);
            }
            break;
        }
    }

    return 0;
}

/////////////////////////////////////////////
//
// CRTCIMSession::DeliverSessionState
//

HRESULT CRTCIMSession::DeliverSessionState(RTC_SESSION_STATE enState)
{
    // Call the base class
    CRTCSession::DeliverSessionState(enState);

    // Can participants be added?
    HMENU hMenu = GetMenu(m_hWnd);
    VARIANT_BOOL fCanAdd;
    HRESULT hr;
	////////////
	//
	// Begin RTC Functionality Code
	//
	// This code demonstrates Calling RTC to see if a participant can be added.
	//
	////////////

    hr = m_pSession->get_CanAddParticipants(&fCanAdd);

    if (FAILED(hr))
    {
        // get_CanAddParticipants failed
        EnableMenuItem(hMenu, ID_ACTION_ADDPARTICIPANT, MF_GRAYED);
    }
    else
    {
        EnableMenuItem(hMenu, ID_ACTION_ADDPARTICIPANT, fCanAdd ? MF_ENABLED : MF_GRAYED);
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
// CRTCIMSession::DeliverParticipantState
//

HRESULT CRTCIMSession::DeliverParticipantState(IRTCParticipant * pParticipant, RTC_PARTICIPANT_STATE enState)
{
    HRESULT hr;

    hr = UpdateParticipantList(pParticipant);

    if (FAILED(hr))
    {
        // UpdateParticipantList failed
        return hr;
    }

    if (enState == RTCPS_DISCONNECTED)
    {
        hr = DoRemoveParticipant(pParticipant);

        if (FAILED(hr))
        {
            // DoRemoveParticipant failed
            return hr;
        }
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCIMSession::DeliverMessage
//

HRESULT CRTCIMSession::DeliverMessage(IRTCParticipant * pParticipant, BSTR bstrContentType, BSTR bstrMessage)
{
    HRESULT hr = S_OK;
    BSTR bstrName = NULL;

    UNREFERENCED_PARAMETER(bstrContentType);

    // Get the name of the incoming user
    hr = pParticipant->get_Name(&bstrName);

    if (SUCCEEDED(hr) && !wcscmp(bstrName, L""))
    {
        // Treat an emptry string as a failure
        SAFE_FREE_STRING(bstrName);
        hr = E_FAIL;
    }

    if (FAILED(hr))
    {
        // Get the URI of the incoming user
        hr = pParticipant->get_UserURI(&bstrName);

        if (FAILED(hr))
        {
            // get_UserURI failed
            return hr;
        }
    }

    // Display the incoming message
    hr = DoDisplayMessage(bstrName, bstrMessage);

    if (FAILED(hr))
    {
        // DoDisplayMessage failed
        SAFE_FREE_STRING(bstrName);
        return hr;
    }

    // Set the incoming user's typing status to idle
    hr = DoDisplayTyping(bstrName, RTCMUS_IDLE);

    SAFE_FREE_STRING(bstrName);

    if (FAILED(hr))
    {
        // DoDisplayTyping failed
        return hr;
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CRTCIMSession::DeliverUserStatus
//

HRESULT CRTCIMSession::DeliverUserStatus(IRTCParticipant * pParticipant, RTC_MESSAGING_USER_STATUS enStatus)
{
    HRESULT hr;
    BSTR bstrName = NULL;

    // Get the name of the incoming user
    hr = pParticipant->get_Name(&bstrName);

    if (SUCCEEDED(hr) && !wcscmp(bstrName, L""))
    {
        // Treat an emptry string as a failure
        SAFE_FREE_STRING(bstrName);
        hr = E_FAIL;
    }

    if (FAILED(hr))
    {
        // Get the URI of the incoming user
        hr = pParticipant->get_UserURI(&bstrName);

        if (FAILED(hr))
        {
            // get_UserURI failed
            return hr;
        }
    }

    // Display the typing status of the incoming user
    hr = DoDisplayTyping(bstrName, (enStatus == RTCMUS_TYPING));

    SAFE_FREE_STRING(bstrName);

    if (FAILED(hr))
    {
        // DoDisplayTyping failed
        return hr;
    }

    return S_OK;
}
