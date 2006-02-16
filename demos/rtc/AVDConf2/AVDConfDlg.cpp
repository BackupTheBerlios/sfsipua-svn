// ------------------------------------------------------------------------------------
// Copyright ©2002 Intel Corporation
// All Rights Reserved
// 
// Permission is granted to use, copy, distribute and prepare derivative works of this 
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  This software is provided "AS IS." 
//
// Intel specifically disclaims all warranties, express or implied, and all liability,
// including consequential and other indirect damages, for the use of this software, 
// including liability for infringement of any proprietary rights, and including the 
// warranties of merchantability and fitness for a particular purpose.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.
// ------------------------------------------------------------------------------------
//
// AVDConfDlg.cpp : implementation file
//
// Purpose: Main Dialog dialog handler module to handle all dialog messages.
//

#include "stdafx.h"
#include "rtccore.h"
#include "rtcerr.h"

#include "AVDConf.h"
#include "systeminfo.h"
#include "AVDConfDlg.h"
#include "MakeCallDlg.h"
#include "incomingdlg.h"
#include "addbuddydlg.h"
#include "buddyrequestdlg.h"
#include "siplogin.h"
#include "authdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Global variable used to store destination SIP
BSTR	g_bstrAddr;

// Global variable used to store XML schema
BSTR	g_bstrXMLBuffer;


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVDConfDlg dialog

CAVDConfDlg::CAVDConfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAVDConfDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAVDConfDlg)
	m_csLocalIP = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAVDConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAVDConfDlg)
	DDX_Control(pDX, IDC_REMOVEBUDDY, m_cRemoveBuddy);
	DDX_Control(pDX, IDC_BUDDYLIST, m_cBuddyList);
	DDX_Control(pDX, IDC_ADDBUDDY, m_cAddbuddy);
	DDX_Control(pDX, IDC_LOGOFF, m_cLogOff);
	DDX_Control(pDX, IDC_LOGIN, m_cLogin);
	DDX_Control(pDX, IDC_PRESENCELABEL, m_cPresLabel);
	DDX_Control(pDX, IDC_PRESENCESTATUS, m_cPresStatus);
	DDX_Control(pDX, IDC_CPU1PROGRESS, m_ctrCPU1Progress);
	DDX_Control(pDX, IDC_CPU2PROGRESS, m_ctrCPU2Progress);
	DDX_Control(pDX, IDC_CPU2PERCENT, m_ctrCPU2Percent);
	DDX_Control(pDX, IDC_CPU2LABEL, m_ctrCPU2Label);
	DDX_Control(pDX, IDC_SYSTEMINFO, m_btnSysInfo);
	DDX_Control(pDX, IDC_WHITEBOARD, m_cWhiteboard);
	DDX_Control(pDX, IDC_MESSAGING, m_cMessaging);
	DDX_Control(pDX, IDC_TUNING, m_cTuning);
 	DDX_Control(pDX, IDC_MAKECALL, m_cMakeCall);
 	DDX_Control(pDX, IDC_APPCALL, m_cAppCall);
	DDX_Text(pDX, IDC_LOCALIP, m_csLocalIP);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAVDConfDlg, CDialog)
	//{{AFX_MSG_MAP(CAVDConfDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MAKECALL, OnMakecall)
	ON_BN_CLICKED(IDC_APPCALL, OnAppcall)
	ON_BN_CLICKED(IDC_TUNING, OnTuning)
	ON_BN_CLICKED(IDC_MESSAGING, OnMessaging)
	ON_BN_CLICKED(IDM_ABOUTBOX, OnAboutbox)
	ON_BN_CLICKED(IDC_WHITEBOARD, OnWhiteboard)
	ON_BN_CLICKED(IDC_SYSTEMINFO, OnSysteminfo)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_ADDBUDDY, OnAddbuddy)
	ON_BN_CLICKED(IDC_REMOVEBUDDY, OnRemovebuddy)
	ON_BN_CLICKED(IDC_LOGOFF, OnLogoff)
	ON_CBN_SELCHANGE(IDC_PRESENCESTATUS, OnSelchangePresencestatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVDConfDlg message handlers

/////////////////////////////////////////////////////////////////////////////
// Dialog initialization method created by the App Wizard.
// Windows Message: WM_INITDIALOG
BOOL CAVDConfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Add column to list title
	m_cBuddyList.InsertColumn (0, "Name", LVCFMT_LEFT, 200);
	
	// Get System Information
	GetSysInfo();

	// Resize the Window to hide the System Info section..
	RECT lRect;
	GetWindowRect (&lRect);
	lRect.bottom -= 129;
	MoveWindow ( &lRect, TRUE );

	// Initialize the RTC Client
	if (InitRTCClient() != S_OK)
	{
		// Disable all feature buttons if the initialization fails.
		MessageBox ( "Initialization Error" );
		m_cMakeCall.EnableWindow ( FALSE );
		m_cAppCall.EnableWindow ( FALSE );
		m_cMessaging.EnableWindow ( FALSE );
		m_cTuning.EnableWindow ( FALSE );
		m_cWhiteboard.EnableWindow ( FALSE );
	}

	UpdateStatus ( STATUS_READY );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//////////////////////////////////////////////////////////////////////////////
// Method: InitRTCClient()
// Parameter: None
// Return Value: S_OK if successful.
// Purpose: This method initiates the RTC layer.
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::InitRTCClient()
{
	// Create the RTC Client
	HRESULT hr;

	m_pClient = NULL;
	m_pProfile = NULL;
	m_pEvents = NULL;

	m_bIMInProgress = false;

	m_bPresenceEnabled = false;
	
	// Initialize the COM library in the current thread.
	hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		return hr;
	}

	// Initialize the RTC COM object
	hr = CoCreateInstance (CLSID_RTCClient, NULL,
		CLSCTX_INPROC_SERVER, IID_IRTCClient,
		(LPVOID *)&m_pClient);

	if (FAILED(hr))
	{
		// Failed to load the RTC Client Interface.
		return hr;
	}

	// Initialize the client interface
	hr = m_pClient->Initialize();

	if (FAILED(hr))
	{
		// Unable to initialize the RTC Interface
		SAFE_RELEASE(m_pClient);
		return hr;
	}

	// Set the preferred media type we want to initiate for this application.
	// RTCMT_ALL will initialize Audio, Video, and T.120 layer.
	m_pClient->SetPreferredMediaTypes ( RTCMT_ALL, VARIANT_TRUE );

    // Set the event filter to listen for.
	// Using RTCEF_ALL will set for all events
	// For the sample application, we will demonstrate how to set the event listener for
	// a limited set of events.
/*
	long lEventMask = RTCEF_SESSION_STATE_CHANGE |
					  RTCEF_MESSAGING |
					  RTCEF_MEDIA |
					  RTCEF_INTENSITY |
					  RTCEF_CLIENT;
					  */
	
	// Set all event mask on since we are going to need all the events.
	long lEventMask = RTCEF_ALL;

    // Initialize the event filter this demo application want callback.
	hr = m_pClient->put_EventFilter( lEventMask );

    if ( FAILED(hr) )
    {
        // put_EventFilter failed
        SAFE_RELEASE(m_pClient);
        return hr;
    }

    // Create the event sink object
    m_pEvents = new CRTCEvents;

    if (!m_pEvents)
    {
      // Out of memory
        SAFE_RELEASE(m_pClient);
        return hr;
    }

    // initialize the event handler
    hr = m_pEvents->Advise( m_pClient, m_hWnd );

    if ( FAILED(hr) )
    {
        // Advise failed
        SAFE_RELEASE(m_pClient);
        return hr;
    }

    // Set the listen mode for RTC client
    // RTCLM_BOTH opens the standard SIP port 5060, as well as
    // a dynamic port.
    hr = m_pClient->put_ListenForIncomingSessions(RTCLM_BOTH); 

	//m_pClient->put_MaxBitrate(1000000L);
	//m_pClient->put_TemporalSpatialTradeOff(0);

    if ( FAILED(hr) )
    {
        // put_ListenMode failed
        SAFE_RELEASE(m_pClient);
        return hr;
    }

	// Initalize the program state machine to IDLE
	if (m_AVDlg)
		m_AVDlg.SetState (RTCSS_IDLE);

	return S_OK;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CAVDConfDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAVDConfDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnMakeCall()
// Parameter: None
// Return Value: None
// Purpose: This method is called when the user clicks the AV Call button.
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnMakecall() 
{
	MakeCallDlg cDlg;
	int		iRes = -1;
	BSTR	bstrURI = NULL;

	// Check to see if a name in the Buddy list has been selected.
	if ((iRes = m_cBuddyList.GetSelectionMark()) > -1)
	{
		GetUserURIFromList(iRes, &bstrURI);
		m_cBuddyList.SetSelectionMark (-1);
	}
	else // Display the SIP dialog box.
	if (cDlg.DoModal() != IDOK)
	{
		return;
	}
	else
		bstrURI = g_bstrAddr;

	// Make a PC to PC call.
	UpdateStatus ( STATUS_DIALING );
	MakeCall (RTCST_PC_TO_PC, bstrURI);

}


//////////////////////////////////////////////////////////////////////////////
// Method: OnMessaging()
// Parameter: None
// Return Value: None
// Purpose: This method is called when the user clicks the Messenging button
//			to start a Text Chat session
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnMessaging() 
{
 	MakeCallDlg cDlg;
	int		iRes = -1;
	BSTR	bstrURI = NULL;
 
	// Check to see if a name in the Buddy list has been selected.
	if ((iRes = m_cBuddyList.GetSelectionMark()) > -1)
	{
		GetUserURIFromList(iRes, &bstrURI);
		m_cBuddyList.SetSelectionMark (-1);
	}
	else if (cDlg.DoModal() != IDOK)
 	{
		return;
	}
	else
		bstrURI = g_bstrAddr;

 	// Make a Instant Messaging Call.
	UpdateStatus ( STATUS_CHAT );
	MakeCall (RTCST_IM, bstrURI);
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnAppcall()
// Parameter: None
// Return Value: None
// Purpose: This method is called when the user clicks the App Sharing button
//			to start a Application sharing session.
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnAppcall() 
{
	HRESULT	hr;
	VARIANT_BOOL	vbool = VARIANT_FALSE;

	// Check the state of T.120 applet
	m_pClient->get_IsT120AppletRunning(RTCTA_APPSHARING, &vbool);

	if (vbool == VARIANT_FALSE)
	{ // Start T120 Applet to start application sharing
		hr = m_pClient->StartT120Applet ( RTCTA_APPSHARING );
	}
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnWhiteboard()
// Parameter: None
// Return Value: None
// Purpose: This method is called when the user clicks the Whiteboard button
//			to start a Whiteboard sharing session
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnWhiteboard() 
{
	HRESULT	hr;
	VARIANT_BOOL	vbool = VARIANT_FALSE;

	// Check the state of T.120 applet
	m_pClient->get_IsT120AppletRunning(RTCTA_WHITEBOARD, &vbool);

	if (vbool == VARIANT_FALSE)
	{ // Start T120 Applet to start Whiteboard sharing
		hr = m_pClient->StartT120Applet ( RTCTA_WHITEBOARD );
	}
}

//////////////////////////////////////////////////////////////////////////////
// Method: MakeCall()
// Parameter: enType	Type of call.  See RTCCORE.H for types of Session
//			  bstrURI	Target Address (IP, Phone number, e-mail)
// Return Value: S_OK if successful
// Purpose: This method is will initiate either an AV Conferencing call or an
//			Instant Messaging call.
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::MakeCall(RTC_SESSION_TYPE enType, BSTR bstrURI)
{    HRESULT hr;

    // Only Instant Messaging can have multiple sessions for other user participation.
	if (enType != RTCST_IM)
    {
        // Is there already an AV session? We can only
        // allow one at a time
		if ((m_AVDlg) && (m_AVDlg.GetState () != RTCSS_IDLE))
        {
			MessageBoxW (m_hWnd, L"An audio/video call is in progress!", NULL, MB_OK );
            return S_FALSE;
        }
    }

    // Create the Client session
    IRTCSession * pSession = NULL;

    hr = m_pClient->CreateSession(enType, NULL, NULL, 0, &pSession);

    if (FAILED(hr))
    {
        // CreateSession failed
        return hr;
    }

    // Add the participant to the session
	// calling AddParticipation with the target SIP will initiate the RTC
	// layer to call the participant.
    hr = pSession->AddParticipant(bstrURI, NULL, &m_Participant);

	// Free the String
	SAFE_FREE_STRING ( bstrURI );

	if (FAILED(hr))
    {
        // AddParticipant failed					
        SAFE_RELEASE(pSession);
        return hr;
    }

    
	// Add the session to the session list
    // This will create the session window
    hr = AddSession(pSession, enType);
    
    if (FAILED(hr))
    {  
        // AddSession failed        
        return hr;
    }

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: WindowProc()
// Purpose: Handles Windows procedural messages.
//////////////////////////////////////////////////////////////////////////////
LRESULT CAVDConfDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
	case WM_RTC_EVENT:
		OnRTCEvent (message, wParam, lParam);
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnRTCEvent()
// Parameter: message			Type of RTC Event to be process
//			  wParam, lParam	Extra messsage parameters
// Return Value: S_OK if successful.
// Purpose: This method process the RTC Events from the RTC layer.
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::OnRTCEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
    IDispatch * pDisp = (IDispatch *)lParam;
    RTC_EVENT enEvent = (RTC_EVENT)wParam;
    HRESULT hr;

    // Based on the RTC_EVENT type, query for the 
    // appropriate event interface and call a helper
    // method to handle the event

    switch ( wParam )
    {
        case RTCE_SESSION_STATE_CHANGE:
            {
               IRTCSessionStateChangeEvent * pEvent = NULL;
                
                // Get the event handle associated with the current session.
				hr = pDisp->QueryInterface( IID_IRTCSessionStateChangeEvent,
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCSessionStateChangeEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }              
            }
            break;

        case RTCE_MESSAGING:
            {
                IRTCMessagingEvent * pEvent = NULL;
                
                // Get the event handle associated with the current session.
                hr = pDisp->QueryInterface( IID_IRTCMessagingEvent,
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

                // Get the event handle associated with the current session.
                hr = pDisp->QueryInterface( IID_IRTCMediaEvent,
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCMediaEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

        case RTCE_INTENSITY:
            {
                IRTCIntensityEvent * pEvent = NULL;

                // Get the event handle associated with the current session.
                hr = pDisp->QueryInterface( IID_IRTCIntensityEvent,
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

                // Get the event handle associated with the current session.
                hr = pDisp->QueryInterface( IID_IRTCClientEvent,
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCClientEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
            break;

		case RTCE_REGISTRATION_STATE_CHANGE:
            {
                IRTCRegistrationStateChangeEvent * pEvent = NULL;
                
                hr = pDisp->QueryInterface( IID_IRTCRegistrationStateChangeEvent,
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCRegistrationStateChangeEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }              
            }
			break;

		case RTCE_PARTICIPANT_STATE_CHANGE:
			{
                IRTCParticipantStateChangeEvent * pEvent = NULL;
               
                hr = pDisp->QueryInterface( IID_IRTCParticipantStateChangeEvent,
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCParticipantStateChangeEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }              
			}
			break;

		case RTCE_BUDDY:
            {
                IRTCBuddyEvent * pEvent = NULL;

				hr = pDisp->QueryInterface( IID_IRTCBuddyEvent,
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
                IRTCWatcherEvent * pEvent = NULL;

                hr = pDisp->QueryInterface( IID_IRTCWatcherEvent,
                                            (void **)&pEvent );

                if (SUCCEEDED(hr))
                {
                    OnRTCWatcherEvent(pEvent);
                    SAFE_RELEASE(pEvent);
                }
            }
			break;
    }

    // Release the event
    SAFE_RELEASE(pDisp);

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnMessaging()
// Parameter: None
// Return Value: None
// Purpose: This method is called when the user clicks the Messenging button
//			to start a Text Chat session
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnTuning() 
{
	if (m_pClient)
		m_pClient->InvokeTuningWizard((OAHWND)m_hWnd);
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnRTCSessionStateChangeEvent()
// Parameter: pEvent		Pointer to the event information
// Return Value: None
// Purpose: This method handles all events that are associated to State changes
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnRTCSessionStateChangeEvent(IRTCSessionStateChangeEvent *pEvent)
{
    IRTCSession * pSession = NULL;
    RTC_SESSION_STATE enState;
    HRESULT hr;

    // Get the session state
	hr = pEvent->get_State(&enState);

    if (FAILED(hr))
    {
        // get_State failed
        return;
    }

	// Update Status bar with Session state changes
	switch (enState)
	{
    case RTCSS_IDLE:
	case RTCSS_DISCONNECTED:
		UpdateStatus ("Ready");
		break;

	case RTCSS_INCOMING:
		UpdateStatus ("Incoming Call");
		break;
		
	case RTCSS_ANSWERING:
		UpdateStatus ("Answering Call");
		break;

	case RTCSS_INPROGRESS:
		UpdateStatus ("Call Inprogress");
		break;

	case RTCSS_CONNECTED:
		UpdateStatus ("Call In Session");
		break;
	}

    // Get a pointer to the current session.
	hr = pEvent->get_Session(&pSession);

    if (FAILED(hr))
    {
        // get_Session failed
        return;
    }

    switch ( enState )
	{
	case RTCSS_INCOMING:
        {
			// Handles RTC Event for an Incoming call request.

            // This is a new session
            RTC_SESSION_TYPE enType;
            
			hr = pSession->get_Type(&enType);

            if (FAILED(hr))
            {
                // get_Type failed
                SAFE_RELEASE(pSession);
                return;
            }            

            if (enType == RTCST_IM)
            {
                // This is an IM call
                m_pClient->PlayRing(RTCRT_MESSAGE, VARIANT_TRUE);
            }
            else            
            {
                // This is an AV call
                if ((m_AVDlg) && (m_AVDlg.GetState() != RTCSS_IDLE))
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

                if (FAILED(hr))
                {
                    // get_PresentityURI failed
                    SAFE_FREE_STRING(bstrURI);
                    SAFE_RELEASE(pSession);
                    return;
                }

				UpdateStatus ( STATUS_INCOMING );

                // Play a phone ring sound to alert the participant.
                m_pClient->PlayRing(RTCRT_PHONE, VARIANT_TRUE);

                // Show the session dialog
                BOOL fAccept;
				CIncomingDlg	cDlg;	   
				SESSION_DATA	pData;
				ZeroMemory(&pData, sizeof(SESSION_DATA));

				pData.bstrName = bstrName;
				pData.bstrURI = bstrURI;

				SetWindowLong ( m_hWnd, GWL_USERDATA, (LONG)&pData);
				
				// Show the Incoming phone request dialog.
				fAccept = (cDlg.DoModal() == IDOK);

				//Free the caller string
				SAFE_FREE_STRING(bstrURI);
				SAFE_FREE_STRING(bstrName);
                    
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

					UpdateStatus ( STATUS_AVCALL );
                }
                else
                {
                    // Reject the session
                    pSession->Terminate(RTCTR_REJECT);

					UpdateStatus ( STATUS_READY );

					SAFE_RELEASE(pSession);
                    return;
                }
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
		break;

	case RTCSS_DISCONNECTED:
		{
            RTC_SESSION_TYPE enType;
            
			hr = pSession->get_Type(&enType);

			if (enType == RTCST_IM)
				m_bIMInProgress = false;
			break;
		}

	}

    // Deliver the session state to the session window
	if (m_AVDlg)
		m_AVDlg.SetState (enState);
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnRTCMediaEvent()
// Parameter: pEvent		Pointer to the event information
// Return Value: None
// Purpose: This method handles event during an Audio/Video conferencing call
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnRTCMediaEvent(IRTCMediaEvent *pEvent)
{
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

	if ((m_AVDlg) && (m_AVDlg.GetState () != RTCSS_IDLE))
    {
        // Deliver the media state to the session window
        m_AVDlg.DeliverMedia(lMediaType, enType, enReason);
    }
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnRTCIntensityEvent()
// Parameter: pEvent		Pointer to the event information
// Return Value: None
// Purpose: This method handles event during an Audio/Video conferencing call
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnRTCIntensityEvent(IRTCIntensityEvent *pEvent)
{
    RTC_AUDIO_DEVICE enDevice;
    long lLevel, lMin, lMax;
    HRESULT hr;

    // Get the type of device (MIC or Speaker) that is being adjusted.
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

	if (m_AVDlg.GetState () != RTCSS_IDLE)
    {
        // Deliver the intensity state to the session window
        m_AVDlg.DeliverIntensity(enDevice, lLevel);
    }
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnRTCClientEvent()
// Parameter: pEvent		Pointer to the event information
// Return Value: None
// Purpose: Process RTCE_CLIENT event messages.
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnRTCClientEvent(IRTCClientEvent *pEvent)
{
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
        m_pClient->Shutdown();
		SAFE_RELEASE(m_pClient);
		// The RTC client has finished preparing for
        // shutdown. Destroy the window now.
        DestroyWindow();
    }
    else
    {
        if (m_AVDlg.GetState() != RTCSS_IDLE)
        {
            // Deliver the client state to the session window
            m_AVDlg.DeliverClient(enEventType);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
// Method: AddSession()
// Parameter: pSession		Session Handle
//			  enType		Type of Session to add to session list.
// Return Value: None
// Purpose: This method adds the current call to a session list.
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::AddSession(IRTCSession *pSession, RTC_SESSION_TYPE enType)
{
    // Is this an audio/video session?
    BOOL fAVSession = (enType != RTCST_IM);

    // Show the appropriate dialog box for either an AV Call or Messaging
	// call.
	if (fAVSession)
	{
		BOOL ret = m_AVDlg.Create (IDD_AVDLG,this);
		if (!ret)
		{
			MessageBox ( "Error Creating Dialog" );
		}
		m_AVDlg.ShowWindow (SW_SHOW);
		m_AVDlg.SetParentClient (m_pClient);
		m_AVDlg.SetSession (pSession);
	}
	else
	{
		if (m_bIMInProgress == false)
		{
			BOOL ret = m_cMessageDlg.Create (IDD_MESSAGEDLG, this);
			if (!ret)
			{
				MessageBox ( "Error Creating Dialog" );
			}
			m_bIMInProgress = true;
			m_cMessageDlg.ShowWindow (SW_SHOW);
			m_cMessageDlg.SetParentClient ( m_pClient );
			m_cMessageDlg.SetSession (pSession);
		}
		else {
			MessageBox ( "This sample code is only designed to initiate\n"
				"1 Instant Message session." );
		}
	}

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
// Method: OnRTCMessagingEvent()
// Parameter: pEvent		Pointer to the event object.
// Return Value: None
// Purpose: This method processes all event messages relating to a Instant
//			Messaging event.
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::OnRTCMessagingEvent(IRTCMessagingEvent *pEvent)
{
    IRTCSession * pSession = NULL;
    //CRTCSession * pSessWindow = NULL;
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
        return S_FALSE;
    }
    
    hr = pEvent->get_EventType(&enType);

    if (FAILED(hr))
    {
        // get_EventType failed
        return S_FALSE;
    }

    hr = pEvent->get_Participant(&pParticipant);

    if (FAILED(hr))
    {
        // get_Participant failed
        return S_FALSE;
    }

    if (enType == RTCMSET_MESSAGE)
    {
        hr = pEvent->get_MessageHeader(&bstrContentType);

        if (FAILED(hr))
        {
            // get_MessageHeader failed
            SAFE_RELEASE(pParticipant);
            return S_FALSE;
        }

        hr = pEvent->get_Message(&bstrMessage);

        if (FAILED(hr))
        {
            // get_Message failed
            SAFE_RELEASE(pParticipant);
            SAFE_FREE_STRING(bstrContentType);
            return S_FALSE;
        }

        // Deliver the message to the session window
        if (m_cMessageDlg)
			m_cMessageDlg.DeliverMessage(pParticipant, bstrContentType, bstrMessage);

        SAFE_FREE_STRING(bstrContentType);
        SAFE_FREE_STRING(bstrMessage);
    }
    else if (enType == RTCMSET_STATUS)
    {
        hr = pEvent->get_UserStatus(&enStatus);

        if (FAILED(hr))
        {
            // get_UserStatus failed
            return S_FALSE;
        }

        // Deliver the user status to the session window
        m_cMessageDlg.DeliverUserStatus(pParticipant, enStatus);
    }

    SAFE_RELEASE(pParticipant); 
	
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnOK()
// Parameter: None
// Return Value: None
// Purpose: Using the OK button to handle when the user shuts down the application
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnOK() 
{
	if (m_pClient)
	{
		// log off RTC Server
		DoLogOff();

		m_pClient->StopT120Applets();

		m_pClient->PrepareForShutdown();

		if (m_pEvents)
		{
			m_pEvents->Unadvise( m_pClient);
		}
	}

	m_SysInfo.UnInitPerfCtr();


	CDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnCancel()
// Parameter: None
// Return Value: None
// Purpose: Prevents the users from hitting the ESC button, or ALT+F4 to quit
//			the program.  Just trapping the IDCANCEL event.
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnCancel ()
{	// Don't process the ESC key or Cancel button.
	MessageBox ( "Please use the shutdown\nbutton to quit." );
	return;
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnAboutbox()
// Parameter: None
// Return Value: None
// Purpose: Shows the About box
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnAboutbox() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnSysteminfo()
// Parameter: None
// Return Value: None
// Purpose: Show the System Information
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnSysteminfo() 
{
	static bool bStateVisible = false;
	RECT	lRect;

	GetWindowRect (&lRect);

	switch (bStateVisible)
	{
	case false:
		if (m_bPerfCtrInit)
		{ // Start Perf Timer for CPU Event
			// Get the system local IP Address.  This is done each time in the event the adapter has been
			// disabled and reenabled while the application is running.
			m_csLocalIP = m_SysInfo.GetLocalIP();
			SetDlgItemText ( IDC_LOCALIP, m_csLocalIP );

			m_btnSysInfo.SetWindowText ( "System Info <<" );
			lRect.bottom += 129;
			MoveWindow ( &lRect, TRUE );
			
			bStateVisible = true;
			SetTimer ( TID_CPUPERFEVENT, CPU_TIMER_TICK, NULL );
		}
		break;

	case true:
		bStateVisible = false;
		// Since the SysInfo is hidden, there's no point to continue to get the
		// CPU Utilization.
		KillTimer (TID_CPUPERFEVENT);

		m_btnSysInfo.SetWindowText ( "System Info >>" );
		lRect.bottom -= 129;
		MoveWindow ( &lRect, TRUE );
		break;
	}
	
}

//////////////////////////////////////////////////////////////////////////////
// Method: GetSysInfo()
// Parameter: None
// Return Value: None
// Purpose: Get the CPU information in regards to number of phyical and logical
//			CPU and Hyper-Thread status
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::GetSysInfo()
{
	DWORD dwPhysCPU, dwLogCPU;

	// Get the system info
	DWORD dwCPUInfo = m_SysInfo.GetCPUInfo();

	dwPhysCPU = dwCPUInfo & 0xff;
	dwLogCPU = (dwCPUInfo >> 8) & 0xff;
	// Set the Dialog info components
	SetDlgItemInt ( IDC_PHYSCPU, dwPhysCPU, false);
	SetDlgItemInt ( IDC_LOGICALCPU, dwLogCPU, false);

	if (((dwPhysCPU == 1) && (dwLogCPU == 1)) || ((dwCPUInfo >> 16) != 1))
	{
		m_ctrCPU2Label.EnableWindow (false);
		m_ctrCPU2Progress.EnableWindow (false);
		m_ctrCPU2Percent.EnableWindow (false);
	}

	switch (dwCPUInfo >> 16)
	{
		case 0:	// HT Not Capable
			SetDlgItemText ( IDC_HTCAPABLE, "Not Supported");
			break;
		case 1: // HT Enabled
			SetDlgItemText ( IDC_HTCAPABLE, "Supported");
			break;
		case 2: // HT Disabled
			SetDlgItemText ( IDC_HTCAPABLE, "Disabled");
			break;
		case 3:
			SetDlgItemText ( IDC_HTCAPABLE, "Supported but Disabled");
			break;
		case 4: // Others
			SetDlgItemText ( IDC_HTCAPABLE, "Unabled to detect!");
			break;
	}

	// Base on the CPU Counter, Initialize only the number of CPU Utilization Meter
	m_dwCPUMax = dwPhysCPU < dwLogCPU ? dwLogCPU : dwPhysCPU;
	m_bPerfCtrInit = m_SysInfo.InitPerfCounter (m_dwCPUMax) == S_OK;
}


//////////////////////////////////////////////////////////////////////////////
// Method: OnTimer()
// Parameter: nIDEvent	Timer Event
// Return Value: None
// Purpose: Timer to process CPU Utilization event and SIP Server Login timeout
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnTimer(UINT nIDEvent) 
{
	
	switch (nIDEvent)
	{
	// CPU Performance monitor event
	case  TID_CPUPERFEVENT:
		{
			long lCycle, lRet;
			char szBuf[32];

			KillTimer ( TID_CPUPERFEVENT );

			switch (m_dwCPUMax)
			{
			case 1:
				lCycle = m_SysInfo.GetCPUCycle(1);	// Get the current CPU utilization
				m_ctrCPU1Progress.SetPos ( lCycle );	// Format the string to display
				wsprintf ( szBuf, "%d%%", lCycle);
				SetDlgItemText (IDC_CPU1Percent, szBuf );
				break;

			case 2:
				lCycle = m_SysInfo.GetCPUCycle(2);	// Get the current CPU utilization
				
				// Show CPU 1 Utilization
				lRet = lCycle & 0xffff;
				m_ctrCPU1Progress.SetPos ( lRet);	// Format the string to display
				wsprintf ( szBuf, "%d%%", lRet);
				SetDlgItemText (IDC_CPU1Percent, szBuf );

				// Show CPU 2 Utilization
				lRet = lCycle >> 16;
				m_ctrCPU2Progress.SetPos ( lRet );	// Format the string to display
				wsprintf ( szBuf, "%d%%", lRet);
				SetDlgItemText (IDC_CPU2PERCENT, szBuf );
				break;

			}

			SetTimer ( TID_CPUPERFEVENT, CPU_TIMER_TICK, NULL );
		}
		break;

	// SIP Server login timeout
	case TID_SIPLOGIN:
		{
			KillTimer (TID_SIPLOGIN);
			UpdateStatus ( "Login timed out." );
			DoLogOff();
		}
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnLogin()
// Parameter: None
// Return Value: None
// Purpose: Process SIP Server login when the user press the Login button
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnLogin() 
{
	CSIPLogin	cDlg;
	
	if (cDlg.DoModal() == IDOK)
	{
		DoSIPLogin ( g_bstrXMLBuffer );
		SetPresence (1);
	}
}

//////////////////////////////////////////////////////////////////////////////
// Method: DoSIPLogin()
// Parameter: bXMLObj	XML Schema object for the SIP Server
// Return Value: S_OK if successful
// Purpose: Perform the login process to the RTC Server
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::DoSIPLogin(BSTR bXMLObj)
{
    HRESULT hr;

    UpdateStatus ( "Waiting for server response." );

	if (m_pProfile)
    {
        // Already logged on
        MessageBox("Already logged on!");

        return S_FALSE;
    }

    // Get the RTC client provisioning interface
    IRTCClientProvisioning * pProv = NULL;

    hr = m_pClient->QueryInterface(
            IID_IRTCClientProvisioning,
            (void **)&pProv);

    if (FAILED(hr))
    {
        char szErr[256];
		// QueryInterface failed
		wsprintf ( szErr, "Logon failed!\nErr = 0x%x", hr);
        MessageBox(szErr, "Interface Query");
        return hr;
    }

    // Create a RTC profile object from the XML
    // provisioning document
    hr = pProv->CreateProfile(bXMLObj, &m_pProfile);

    SAFE_FREE_STRING(bXMLObj);

    if (FAILED(hr))
    {
        // CreateProfile failed
        char szErr[256];
		wsprintf ( szErr, "Logon failed!\nErr = 0x%x", hr);
        MessageBox(szErr, "Creating Profile");

        SAFE_RELEASE(pProv);
        return hr;
    }

    // Enable the RTC profile object
    hr = pProv->EnableProfile(m_pProfile, RTCRF_REGISTER_ALL);

    SAFE_RELEASE(pProv);

    if (FAILED(hr))
    {
        // EnableProfile failed
        SAFE_RELEASE(m_pProfile);

        char szErr[256];
		wsprintf ( szErr, "Logon failed!\nErr = 0x%x", hr);
        MessageBox(szErr, "Enabling Profile");
        return hr;    
    }

    // Enable presence
    // It is best to enable presence immediately after enabling the
    // profile so that incoming watchers will not be lost.
    hr = EnablePresence(TRUE);

    if (FAILED(hr))
    {
        // DoEnablePresence failed
        DoSIPLogoff();

        char szErr[256];
		wsprintf ( szErr, "Logon failed!\nErr = 0x%x", hr);
        MessageBox(szErr);
        return hr;
    }

    // If all event passes, turn timer on.
	SetTimer (TID_SIPLOGIN, SIP_LOGIN_TIMEOUT, NULL);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: DoSIPLogoff()
// Parameter: None
// Return Value: S_OK if successful
// Purpose: Handle the process of logining off the RTC Server and disabling
//			the profile.
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::DoSIPLogoff()
{
    HRESULT hr;

    if (!m_pProfile)
    {
        // Already logged off
        return S_OK;
    }

    // Get the RTC client provisioning interface
    IRTCClientProvisioning * pProv = NULL;

    hr = m_pClient->QueryInterface(
            IID_IRTCClientProvisioning,
            (void **)&pProv);

    if (FAILED(hr))
    {
        // QueryInterface failed
        return hr;
    }

    // Disable the profile
    pProv->DisableProfile(m_pProfile);

    SAFE_RELEASE(m_pProfile);
    SAFE_RELEASE(pProv);

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnRTCRegistrationStateChangeEvent()
// Parameter: pEvent	Pointer to the interface object
// Return Value: None
// Purpose: Handles the registration state change events when the users login or
//			logoff to the RTC Server (SIP Server)
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnRTCRegistrationStateChangeEvent(IRTCRegistrationStateChangeEvent *pEvent)
{
    HRESULT hr;

    // Get the registration state
    RTC_REGISTRATION_STATE enState;
    long lStatusCode;

    hr = pEvent->get_State(&enState);

    if (FAILED(hr))
    {
        // get_State failed
        return;
    }

    // Get the status code
    hr = pEvent->get_StatusCode(&lStatusCode);

    if (FAILED(hr))
    {
        // get_StatusCode failed
        return;
    }

    switch(enState)
    {
    case RTCRS_UNREGISTERING:
        // Logoff in progress
        UpdateStatus ("Logging off");

        OnLoggingOff();
        break;

    case RTCRS_NOT_REGISTERED:
        // Logged off
        UpdateStatus("Logged off");

        OnLoggedOff();
        break;

    case RTCRS_REGISTERING:
        // Logon in progress
        UpdateStatus("Logging on");

        OnLoggingOn();
        break;

    case RTCRS_REGISTERED:
        // Logged on
        UpdateStatus("Logged on");

        OnLoggedOn();
        break;

    case RTCRS_REJECTED:
    case RTCRS_ERROR:
        {
            // Logon failed. Most likely the server could no be found,
            // or the user needs to authenticate.

            HRESULT hr = lStatusCode;
			SESSION_DATA	pData;

			ZeroMemory(&pData, sizeof(SESSION_DATA));
            // Check if we need to authenticate
            if ((hr == RTC_E_STATUS_CLIENT_UNAUTHORIZED) ||
                (hr == RTC_E_STATUS_CLIENT_PROXY_AUTHENTICATION_REQUIRED))
            {
                // Get the user URI
				HRESULT hr;
                CAuthDlg	dlg;

				UpdateStatus ("Requires and Account and Password");

				// Get the user's current profile info and populate the
				// authentication dialog.  the user can change it there if need to.
				if (m_pProfile != NULL)
				{
					// Get the user URI from the profile
					hr = m_pProfile->get_UserURI(&pData.bstrURI);

					if (FAILED(hr))
					{
						// get_UserURI failed
						return;
					}
				}
				else
				{
					// Get the user URI from the client
					hr = m_pClient->get_LocalUserURI(&pData.bstrURI);

					if (FAILED(hr))
					{
						// get_LocalUserURI failed
						return;
					}
				}

				// Get the Buddy's name and URI
				SetWindowLongPtr ( m_hWnd, GWL_USERDATA, (LPARAM)&pData);

				dlg.DoModal();
				{
					// Do the authentication
					hr = SIPAuthentication(pData.bstrURI, pData.bstrAccount, 
						pData.bstrPassword);
				}

                SAFE_FREE_STRING(pData.bstrURI);
                SAFE_FREE_STRING(pData.bstrAccount);
                SAFE_FREE_STRING(pData.bstrPassword);
            }
			else
			{
	            char szBuf[256];
				wsprintf ( szBuf, "Error Occured while logging into server. [0x%x]", hr);
				UpdateStatus (szBuf);
			}
           
            if (FAILED(hr))
            {
                DoLogOff();
                OnLoggedOff();
            }
        }
        break;

    case RTCRS_LOGGED_OFF:
        // The user logged on at another client
        // The user is logged off from this client
        UpdateStatus ("Logged off");

        DoLogOff();
        OnLoggedOff();
        break;

    case RTCRS_LOCAL_PA_LOGGED_OFF:
        // The user logged on at another client
        // The user's presence state is no longer sent from this client

        UpdateStatus ("Logged on (Presence disabled)");
        break;

    case RTCRS_REMOTE_PA_LOGGED_OFF:
        // The user logged off on another client that was sending his
        // presence state. We can ignore this.
        break;
    }
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnRTCWatcherEvent()
// Parameter: IRTCWatcherEvent	Pointer to the Watcher interface object
// Return Value: None
// Purpose: Handles the Watcher events when the other users add you to their 
//			buddy list
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnRTCWatcherEvent(IRTCWatcherEvent *pEvent)
{
    HRESULT hr;
	CBuddyRequestDlg	cDlg;
	SESSION_DATA		BuddyInfo;

	// Initialize Buddy Info data structure
    ZeroMemory(&BuddyInfo, sizeof(SESSION_DATA));


    // Get the watcher object
    IRTCWatcher * pWatcher = NULL;

    hr = pEvent->get_Watcher(&pWatcher);

    if (FAILED(hr))
    {
        // get_Watcher failed
        return;
    }

    hr = pWatcher->get_PresentityURI(&BuddyInfo.bstrURI);

    if (FAILED(hr))
    {
        // get_PresentityURI failed
        SAFE_RELEASE(pWatcher);
        return;
    }

    hr = pWatcher->get_Name(&BuddyInfo.bstrName);

    if (FAILED(hr))
    {
        // get_PresentityURI failed
        SAFE_FREE_STRING(BuddyInfo.bstrURI);
        SAFE_RELEASE(pWatcher);
        return;
    }


    // Get the Buddy's name and URI
	SetWindowLongPtr ( m_hWnd, GWL_USERDATA, (LPARAM)&BuddyInfo);

    // Set the watcher to be allowed or blocked
    hr = pWatcher->put_State(cDlg.DoModal() == IDOK ? RTCWS_ALLOWED : RTCWS_BLOCKED);

    SAFE_RELEASE(pWatcher);

    if (FAILED(hr))
    {
        // put_State failed
        SAFE_FREE_STRING(BuddyInfo.bstrURI);
        SAFE_FREE_STRING(BuddyInfo.bstrName);
        return;
    }

    // Shall we add the user as a buddy?
    if (BuddyInfo.bAutoAdd)
    {
        hr = DoAddBuddy(BuddyInfo.bstrURI, BuddyInfo.bstrName);

        if (FAILED(hr))
        {
            // DoAddBuddy failed
            SAFE_FREE_STRING(BuddyInfo.bstrURI);
            SAFE_FREE_STRING(BuddyInfo.bstrName);
            return;
        }
    }

    SAFE_FREE_STRING(BuddyInfo.bstrURI);
    SAFE_FREE_STRING(BuddyInfo.bstrName);
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnRTCBuddyEvent()
// Parameter: IRTCBuddyEvent	Pointer to the Buddy interface object
// Return Value: None
// Purpose: Handles the Buddy events when any user in your buddy list changes
//			status.
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnRTCBuddyEvent(IRTCBuddyEvent *pEvent)
{
    HRESULT hr;

    // Get the buddy object
    IRTCBuddy * pBuddy = NULL;

    hr = pEvent->get_Buddy(&pBuddy);

    if (FAILED(hr))
    {
        // get_Buddy failed
        return;
    }

    // Update the buddy list entry
    hr = UpdateBuddyList(pBuddy);

    SAFE_RELEASE(pBuddy);

    if (FAILED(hr))
    {
        // UpdateBuddyState failed
        return;
    }
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnRTCParticipantStateChangeEvent()
// Parameter: IRTCParticipantStateChangeEvent	Pointer to the Participant interface object
// Return Value: None
// Purpose: Handles the Participant State Change events.  Currently we are showing
//			you the information that can be retrieve.  For this example, we are not
//			processing any of the information.
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnRTCParticipantStateChangeEvent(IRTCParticipantStateChangeEvent *pEvent)
{
    IRTCParticipant * pParticipant = NULL;
    RTC_PARTICIPANT_STATE enState;
    HRESULT hr;

    hr = pEvent->get_Participant(&pParticipant);

    if (FAILED(hr))
    {
        // get_Participant failed
        return;
    }

	// Get the participant
	BSTR	bstrURI;
	pParticipant->get_UserURI (&bstrURI);

    // Get the participant state
    hr = pEvent->get_State(&enState);

	if (FAILED(hr))
    {
        // get_State failed
        SAFE_RELEASE(pParticipant);
        return;
    }

    SAFE_RELEASE(pParticipant);
}


//////////////////////////////////////////////////////////////////////////////
// Method: EnablePresence()
// Parameter: bEnable		Toggles the Presence state on/off
// Return Value: None
// Purpose: Enables or disables the Presence service
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::EnablePresence(BOOL bEnable)
{
    IRTCClientPresence * pPresence = NULL;
    HRESULT hr;

    // Cleanup the buddy list
    ClearBuddyList();

    // Get the RTC client presence interface
    hr = m_pClient->QueryInterface(
            IID_IRTCClientPresence,
            (void **)&pPresence);

    if (FAILED(hr))
    {
        // QueryInterface failed
        return hr;
    }

	// If disabling Presence, notify other user's you are going off-line.  This
	// is typically because you are logging off the RTC server.
	if (!bEnable)
	{
		hr = pPresence->SetLocalPresenceInfo(RTCXS_PRESENCE_OFFLINE, NULL);

		if (FAILED(hr))
		{
			// Enumerate buddies failed
			SAFE_RELEASE(pPresence);
			return hr;
		}
	}
    // Get the location of the presence storage
    VARIANT varStorage;
    VariantInit(&varStorage);
    varStorage.vt = VT_BSTR;
    varStorage.bstrVal = SysAllocString(L"presence.xml");

    // If we are disabling presence, save the latest
    // copy of the presence data
    if (!bEnable && m_bPresenceEnabled)
    {
        hr = pPresence->Export(varStorage);

        if (FAILED(hr))
        {
            // Export failed
            SAFE_RELEASE(pPresence);
            VariantClear(&varStorage);
            return hr;
        }
    }

    // Enable presence
    hr = pPresence->EnablePresence(
        bEnable ? VARIANT_TRUE : VARIANT_FALSE, varStorage);
    
    VariantClear(&varStorage);

    if (FAILED(hr))
    {
        // EnablePresence failed
        SAFE_RELEASE(pPresence);
        return hr;
    }

    // Set the enabled flag
    m_bPresenceEnabled = bEnable;

    // If we are disabling presence, cleanup the
    // presence data
    if (!bEnable)
    {
        // Cleanup buddies
        IRTCEnumBuddies * pEnumBuddy = NULL;
        IRTCBuddy * pBuddy = NULL;

		if (FAILED(hr))
		{
            // Enumerate buddies failed
            SAFE_RELEASE(pPresence);
            return hr;
		}
        
		hr = pPresence->EnumerateBuddies(&pEnumBuddy);
   
        if (FAILED(hr))
        {
            // Enumerate buddies failed
            SAFE_RELEASE(pPresence);
            return hr;
        }

        while (pEnumBuddy->Next(1, &pBuddy, NULL) == S_OK)
        {
            pPresence->RemoveBuddy(pBuddy);

            SAFE_RELEASE(pBuddy);
        }

        SAFE_RELEASE(pEnumBuddy);

        // Cleanup watchers
        IRTCEnumWatchers * pEnumWatcher = NULL;
        IRTCWatcher * pWatcher = NULL;

        hr = pPresence->EnumerateWatchers(&pEnumWatcher);
   
        if (FAILED(hr))
        {
            // Enumerate watchers failed
            SAFE_RELEASE(pPresence);
            return hr;
        }

        while (pEnumWatcher->Next(1, &pWatcher, NULL) == S_OK)
        {
            pPresence->RemoveWatcher(pWatcher);

            SAFE_RELEASE(pWatcher);
        }

        SAFE_RELEASE(pEnumWatcher);
    }

    SAFE_RELEASE(pPresence);

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: SIPAuthentication()
// Parameter:	bstrURI			Local URI
//				bstrAccount		Login name
//				bstrPassword	User password
// Return Value: S_OK if successful in sending the authentication information
// Purpose: Some RTC Server requires a login which can be passed in the XML Schema.
//			This method handles login information from servers that allows users to
//			login due to missing authentication information in the XML Schema.
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::SIPAuthentication(BSTR bstrURI, BSTR bstrAccount, BSTR bstrPassword)
{
	HRESULT hr;

    // Update the credentials in the profile
    hr = m_pProfile->SetCredentials(bstrURI, bstrAccount, bstrPassword);

    if (FAILED(hr))
    {
        // SetCredentials failed
        return hr;
    }

    // Get the RTC client provisioning interface
    IRTCClientProvisioning * pProv = NULL;

    hr = m_pClient->QueryInterface(
            IID_IRTCClientProvisioning,
            (void **)&pProv);

    if (FAILED(hr))
    {
        // QueryInterface failed
        return hr;
    }

    // Re-enable the RTC profile object
    hr = pProv->EnableProfile(m_pProfile, RTCRF_REGISTER_ALL);

    SAFE_RELEASE(pProv);

    if (FAILED(hr))
    {
        // EnableProfile failed
        return hr;    
    }

    // Re-enable presence
    hr = EnablePresence(TRUE);

    if (FAILED(hr))
    {
        // DoEnablePresence failed
        return hr;
    }

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: UpdateStatus()
// Parameter: szStatus		Current user status
// Return Value: None
// Purpose: Displays the status of the last action on the UI.
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::UpdateStatus(LPSTR szStatus)
{
	SetDlgItemText ( IDC_STATUS, szStatus );
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnLoggingOn()
// Parameter: None
// Return Value: None
// Purpose: Handles the disabling and enabling of UI features during a login action
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnLoggingOn()
{
	// We recieve ACK from the SIP Server.
	KillTimer (TID_SIPLOGIN);

	m_cLogin.EnableWindow (false);
	m_cLogOff.EnableWindow (true);
	m_cAddbuddy.EnableWindow (false);
	m_cRemoveBuddy.EnableWindow (false);
	
	m_cBuddyList.EnableWindow (false);

	// Initially enable Presence status
	m_cPresLabel.EnableWindow (true);
	m_cPresStatus.EnableWindow (true);
	m_cPresStatus.SetCurSel (1);
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnLoggingOff()
// Parameter: None
// Return Value: None
// Purpose: Handles the disabling and enabling of UI features during a logoff action
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnLoggingOff()
{
	m_cLogin.EnableWindow (false);
	m_cLogOff.EnableWindow (false);
	m_cAddbuddy.EnableWindow (false);
	m_cRemoveBuddy.EnableWindow (false);
	m_cBuddyList.EnableWindow (false);

	// disable Presence status
	m_cPresLabel.EnableWindow (false);
	m_cPresStatus.EnableWindow (false);
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnLoggedOn()
// Parameter: None
// Return Value: None
// Purpose: Handles all necessary functions after the user has been registered
//			on the RTC Server.
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::OnLoggedOn()
{
    HRESULT hr;

    // Get the RTC client presence interface
    IRTCClientPresence * pPresence = NULL;

    hr = m_pClient->QueryInterface(
            IID_IRTCClientPresence,
            (void **)&pPresence);

    if (FAILED(hr))
    {
        // QueryInterface failed
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
        return hr;
    }

    while (pEnum->Next(1, &pBuddy, NULL) == S_OK)
    {
        // Update the buddy list entry
        UpdateBuddyList(pBuddy);

        SAFE_RELEASE(pBuddy);
    }

    SAFE_RELEASE(pEnum);

    // Enable/disable menu items
    m_cLogin.EnableWindow (false);
	m_cLogOff.EnableWindow (true);
	m_cAddbuddy.EnableWindow (true);
	m_cRemoveBuddy.EnableWindow (true);

	m_cBuddyList.EnableWindow (true);

	// Initially enable Presence status
	m_cPresLabel.EnableWindow (true);
	m_cPresStatus.EnableWindow (true);
	m_cPresStatus.SetCurSel (1);

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnAddbuddy()
// Parameter: None
// Return Value: None
// Purpose: Handles the action of Adding a new Buddy to the Buddy List
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnAddbuddy() 
{
	CAddBuddyDlg	cDlg;
	SESSION_DATA	BuddyInfo;

    ZeroMemory(&BuddyInfo, sizeof(SESSION_DATA));

	// Get the Buddy's name and URI
	SetWindowLongPtr ( m_hWnd, GWL_USERDATA, (LPARAM)&BuddyInfo);

	if (cDlg.DoModal() != IDOK)
		return;

	// Get the new user added to the buddy list.
	DoAddBuddy (BuddyInfo.bstrName, BuddyInfo.bstrURI);
}

//////////////////////////////////////////////////////////////////////////////
// Method: UpdateBuddyList()
// Parameter: pBuddy	Buddy object to update in the Buddy list
// Return Value: S_OK if successful
// Purpose: Updates the users' status in the Buddy List listbox
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::UpdateBuddyList(IRTCBuddy *pBuddy)
{
    HRESULT hr;

    // Get the buddy status
    RTC_PRESENCE_STATUS enStatus;

    hr = pBuddy->get_Status(&enStatus);

    if (FAILED(hr))
    {
        // get_Status failed
        return hr;
    }

    // Get the buddy name
    BSTR bstrName = NULL;

    hr = pBuddy->get_Name(&bstrName);

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
            return hr;
        }
    }

    // Build a string for the listbox
    CHAR szBuddy[MAX_STRING], szName[MAX_STRING];

	wcstombs (szName, bstrName, MAX_STRING);
    SAFE_FREE_STRING(bstrName);
 
    switch(enStatus)
    {
    case RTCXS_PRESENCE_OFFLINE:
        wsprintf(szBuddy, "%s (Offline)", szName);
        break;
    case RTCXS_PRESENCE_ONLINE:
        wsprintf(szBuddy, "%s (Online)", szName);
        break;
    case RTCXS_PRESENCE_AWAY:
        wsprintf(szBuddy, "%s (Away)", szName);
        break;
    case RTCXS_PRESENCE_IDLE:
        wsprintf(szBuddy, "%s (Idle)", szName);
        break;
    case RTCXS_PRESENCE_BUSY:
        wsprintf(szBuddy, "%s (Busy)", szName);
        break;
    case RTCXS_PRESENCE_BE_RIGHT_BACK:
        wsprintf(szBuddy, "%s (Be right back)", szName);
        break;
    case RTCXS_PRESENCE_ON_THE_PHONE:
        wsprintf(szBuddy, "%s (On the phone)", szName);
        break;
    case RTCXS_PRESENCE_OUT_TO_LUNCH:
        wsprintf(szBuddy, "%s (Out to lunch)", szName);
        break;
    default:
        wsprintf(szBuddy, "%s", szName);
        break;
    }

    // Is the buddy in the list?
    LVFINDINFO lvfi;    
    ZeroMemory(&lvfi, sizeof(LVFINDINFO));

    lvfi.flags = LVFI_PARAM;
    lvfi.lParam = (LPARAM)pBuddy;

    int iRes = m_cBuddyList.FindItem(&lvfi, -1);

    if (iRes == -1)
    {
        // Buddy is not in the list
        // Add the buddy to the list  
        LVITEM lvi;
        ZeroMemory(&lvi, sizeof(LVITEM));

        lvi.mask = LVIF_TEXT | LVIF_PARAM;
        lvi.pszText = szBuddy;
        lvi.lParam = (LPARAM)pBuddy;

		iRes = m_cBuddyList.InsertItem(&lvi);

        if (iRes == -1)
        {
            // ListView_InsertItem failed
            return E_FAIL;
        }

        // An RTC buddy reference will be kept by the list
        // Add the reference here
        pBuddy->AddRef();
    }
    else
    {
        // Buddy is in the list
        // Update the list entry
        LVITEM lvi;
        ZeroMemory(&lvi, sizeof(LVITEM));

        lvi.mask = LVIF_TEXT;
        lvi.pszText = szBuddy;
        lvi.iItem = iRes;

        iRes = m_cBuddyList.SetItem (&lvi);

        if (iRes == -1)
        {
            // ListView_SetItem failed         
            return E_FAIL;
        }
    }

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: ClearBuddyList()
// Parameter: None
// Return Value: None
// Purpose: Removes all the users in the buddy listbox and buddy list.
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::ClearBuddyList()
{
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(LVITEM));
    
    lvi.mask = LVIF_PARAM;

    // Iterate through the list and remove each item
    while (m_cBuddyList.GetItem(&lvi))
    {
        IRTCBuddy * pBuddy = (IRTCBuddy *)(lvi.lParam);

        // Release the buddy reference
        SAFE_RELEASE(pBuddy);

        m_cBuddyList.DeleteItem(0);
    }

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnRemovebuddy()
// Parameter: None
// Return Value: None
// Purpose: Removes the selected user from the Buddy List.
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnRemovebuddy() 
{
    HRESULT hr;

    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(LVITEM));

	int iRes = m_cBuddyList.GetSelectionMark();

    lvi.mask = LVIF_PARAM;
    lvi.iItem = iRes;

    // Get the buddy item
    if (!m_cBuddyList.GetItem(&lvi))
    {
        // ListView_GetItem failed;
		MessageBox ( "Failed to get Buddy name from list." );
        return;
    }
    
    IRTCBuddy * pBuddy = (IRTCBuddy *)(lvi.lParam);
    BSTR bstrURI = NULL;

    // Get the buddy URI
    hr = pBuddy->get_PresentityURI(&bstrURI);

    if (FAILED(hr))
    {
        // get_UserURI failed
		char szBuf[256];
		wsprintf ( szBuf, "Failed to get Buddy Status.\nErr = 0x%x", hr);
		MessageBox ( szBuf );
        return;
    }

    // Get the RTC client presence interface
    IRTCClientPresence * pPresence = NULL;

    hr = m_pClient->QueryInterface(
            IID_IRTCClientPresence,
            (void **)&pPresence);

    if (FAILED(hr))
    {
        // QueryInterface failed
		char szBuf[256];
		wsprintf ( szBuf, "Failed to remove buddy.\nErr = 0x%x", hr);
		MessageBox ( szBuf );
        return;
    }

    // Remove the buddy
    hr = pPresence->RemoveBuddy(pBuddy);

    SAFE_RELEASE(pPresence);

    if (FAILED(hr))
    {
        // RemoveBuddy failed
		char szBuf[256];
		wsprintf ( szBuf, "Failed to remove buddy.\nErr = 0x%x", hr);
		MessageBox ( szBuf );
        return;
    }

	m_cBuddyList.DeleteItem (iRes);
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnLogoff()
// Parameter: None
// Return Value: None
// Purpose: Handles the LogOff button event
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnLogoff() 
{
	DoLogOff();
	ClearBuddyList();
}

//////////////////////////////////////////////////////////////////////////////
// Method: DoLogOff()
// Parameter: None
// Return Value: None
// Purpose: Handles the event to logoff the RTC Server and disabling profiling
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::DoLogOff()
{
    HRESULT hr;

    if (!m_pProfile)
    {
        // Already logged off
        return S_OK;
    }

    // Get the RTC client provisioning interface
    IRTCClientProvisioning * pProv = NULL;

    hr = m_pClient->QueryInterface(
            IID_IRTCClientProvisioning,
            (void **)&pProv);

    if (FAILED(hr))
    {
        // QueryInterface failed
        return hr;
    }

    // Disable the profile
    pProv->DisableProfile(m_pProfile);

    SAFE_RELEASE(m_pProfile);
    SAFE_RELEASE(pProv);

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnLoggedOff()
// Parameter: None
// Return Value: None
// Purpose: Enables and disables UI features from logging off event
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::OnLoggedOff()
{
    // Disable presence
    EnablePresence(FALSE);    

	m_cLogin.EnableWindow (true);
	m_cLogOff.EnableWindow (false);
	m_cAddbuddy.EnableWindow (false);
	m_cRemoveBuddy.EnableWindow (false);
	m_cBuddyList.EnableWindow (false);

	// disable Presence status
	m_cPresLabel.EnableWindow (false);
	m_cPresStatus.EnableWindow (false);

    return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
// Method: DoAddBuddy()
// Parameter: bstrName		User to add to Buddy List
//			  bstrURI		User's IP (location)
// Return Value: S_OK if successfully added to the list.
// Purpose: Add the new user to the buddy list and updates the UI
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::DoAddBuddy(BSTR bstrName, BSTR bstrURI)
{
    HRESULT hr;

    // Get the RTC client presence interface
    IRTCClientPresence * pPresence = NULL;

    hr = m_pClient->QueryInterface(
            IID_IRTCClientPresence,
            (void **)&pPresence);

    if (FAILED(hr))
    {
        // QueryInterface failed
		char szBuf[256];

		wsprintf (szBuf, "Failed to Query Presence Interface\nErr = 0x%x", hr );
		MessageBox ( szBuf );
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
        // Addbuddy failed          
        SAFE_RELEASE(pBuddy);
		char szBuf[256];

		wsprintf (szBuf, "Failed to Add Buddy to List.\nErr = 0x%x", hr );
		MessageBox ( szBuf );
        return hr;
    }

    // Update the buddy list entry
    UpdateBuddyList(pBuddy);
    SAFE_RELEASE(pBuddy);

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: OnSelchangePresencestatus()
// Parameter: None
// Return Value: None
// Purpose: Handles the Presence UI status event.
//////////////////////////////////////////////////////////////////////////////
void CAVDConfDlg::OnSelchangePresencestatus() 
{
	// Get the selected Presence status
	int iSel = m_cPresStatus.GetCurSel();

	SetPresence (iSel);
}

//////////////////////////////////////////////////////////////////////////////
// Method: SetPresence()
// Parameter: iStatus	Local user's status
// Return Value: S_OK if successfully posted to the RTC server
// Purpose: Updates the RTC server of status changes.
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::SetPresence(int iStatus)
{
    // Set the presence.
	HRESULT hr;
	RTC_PRESENCE_STATUS enStatus[] = {
			RTCXS_PRESENCE_OFFLINE,
			RTCXS_PRESENCE_ONLINE,
			RTCXS_PRESENCE_AWAY,
			RTCXS_PRESENCE_IDLE,
			RTCXS_PRESENCE_BUSY,
			RTCXS_PRESENCE_BE_RIGHT_BACK,
			RTCXS_PRESENCE_ON_THE_PHONE,
			RTCXS_PRESENCE_OUT_TO_LUNCH };

	// Get the RTC client presence interface
    IRTCClientPresence * pPresence = NULL;

    hr = m_pClient->QueryInterface(
            IID_IRTCClientPresence,
            (void **)&pPresence);

    if (FAILED(hr))
    {
        // QueryInterface failed
        return hr;
    }

    // Set the local presence status
    hr = pPresence->SetLocalPresenceInfo(enStatus[iStatus], NULL);

    SAFE_RELEASE(pPresence);

    if (FAILED(hr))
    {
        // SetLocalPresenceInfo failed
        return hr;
    }	

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////////
// Method: GetUserURIFromList()
// Parameter: Id		Buddy List selection value.
//			  bstrURI	User's location address
// Return Value: S_OK if the function successfully retrieves the user's info
// Purpose: Get the selected user's URI from the Buddy List.
//////////////////////////////////////////////////////////////////////////////
HRESULT CAVDConfDlg::GetUserURIFromList(int Id, BSTR *bstrURI)
{
	HRESULT hr;
	
	// Get Name from list
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(LVITEM));

    lvi.mask = LVIF_PARAM;
    lvi.iItem = Id;

    // Get the buddy item
    if (!m_cBuddyList.GetItem(&lvi))
    {
        // ListView_GetItem failed;
        return 0;
    }
    
    IRTCBuddy * pBuddy = (IRTCBuddy *)(lvi.lParam);

    // Get the buddy URI
    hr = pBuddy->get_PresentityURI(bstrURI);

    if (FAILED(hr))
    {
        // get_UserURI failed
        return hr;
    }

	return S_OK;
}

