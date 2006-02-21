// testwinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testwin.h"
#include "testwinDlg.h"

#include "WaveIn.h"
#include <string>

#include "eXosip/eXosip.h"
#include "eXosip/eXosip_cfg.h"



#include <fstream.h>
#include <process.h>


#include <iostream>
#include "osip2/osip_mt.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CTestwinDlg dialog

CTestwinDlg::CTestwinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestwinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestwinDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestwinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestwinDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestwinDlg, CDialog)
	//{{AFX_MSG_MAP(CTestwinDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CALL, OnCall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestwinDlg message handlers

BOOL CTestwinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestwinDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestwinDlg::OnPaint() 
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
HCURSOR CTestwinDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
class jcall ;
jcall *ca;
int    os_sound_start(jcall *ca, int port);
class jcall {
public:
	int cid;
	int did;

	char reason_phrase[50];
	int  status_code;

	char textinfo[256];
	char req_uri[256];
	char local_uri[256];
	char remote_uri[256];
	char subject[256];

	char remote_sdp_audio_ip[50];
	int  remote_sdp_audio_port;
	int  payload;
	char payload_name[50];

	int state;

	jcall() {}

	int build(eXosip_event_t *je)
	{
		jcall *ca = this;

		ca->cid = je->cid;
		ca->did = je->did;

		if (ca->did<1 && ca->cid<1)
		{

			return -1; /* not enough information for this event?? */
		}

		osip_strncpy(ca->textinfo,   je->textinfo, 255);
		osip_strncpy(ca->req_uri,    je->req_uri, 255);
		osip_strncpy(ca->local_uri,  je->local_uri, 255);
		osip_strncpy(ca->remote_uri, je->remote_uri, 255);
		osip_strncpy(ca->subject,    je->subject, 255);

		if (ca->remote_sdp_audio_ip[0]=='\0')
		{
			osip_strncpy(ca->remote_sdp_audio_ip, je->remote_sdp_audio_ip, 49);
			ca->remote_sdp_audio_port = je->remote_sdp_audio_port;
			ca->payload = je->payload;
			osip_strncpy(ca->payload_name, je->payload_name, 49);
		}

		if (je->reason_phrase[0]!='\0')
		{
			osip_strncpy(ca->reason_phrase, je->reason_phrase, 49);
			ca->status_code = je->status_code;
		}
		os_sound_start(ca, (je->remote_sdp_audio_port));
		ca->state = je->type;
		return 0;
	}

};
char server[200]="@192.168.3.190:6060";
char identity[200]="sip:";//king@sip.broadz.net";
char registrar[200]="sip:192.168.3.190:6060";
char username[100]="8552";
char password[100]="8552";
int j;
int reg_id;
char contact[200]="sip:";//king@sip.broadz.net";
int expires;
bool run = true;

void josua_printf(char* buf)
{
	
	TRACE( "\n" );
}
jcall call;

CWaveIn* m_pIn =new CWaveIn();
int portt;
void* startsound(void *_ca)
{
	//	FILE *source=fopen("c://12.wav","rb");
	//	if ( source == NULL )
	//	{
	//		cout<<"can't access the file"<<endl;
	//	}
//#ifdef win32
 	
//#endif	
	m_pIn->SetPort(portt);
	

	return NULL;
}

int os_sound_start(jcall *ca, int port)
{
		portt=port;
	   osip_thread_create(20000,startsound, ca);  
	   return 0;
}

void CTestwinDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	//	char server[200]="@192.168.3.190:6060";
	//	char identity[200]="sip:";//king@sip.broadz.net";
	//	char registrar[200]="sip:192.168.3.190:6060";
	//	char username[100]="8552";
	//	char password[100]="8552";
	//	int j;
	//	int reg_id;
	//	char contact[200]="sip:";//king@sip.broadz.net";
	//	int expires;
	//	bool run = true;
	
	int i;
	expires = 3600;
	memset( &call, 0, sizeof(call) );
	//	std::cout<<"Please Enter Your Username:";
	//	cin>>username;
	//	std::cout<<"Please Enter Your Password:";
	//	cin>>password;
	strcat(identity,username);
	strcat(identity,server);
	strcpy(contact,identity);

	std::cout << "Usage:"<< endl;
	std::cout << "a - answering call"<< endl;
	std::cout << "h - hangup"<< endl;
	std::cout << "z - zhuxiao"<< endl;
	std::cout << "c - call"<< endl;
	std::cout << "q - quit"<< endl;

	FILE* logfile = fopen( "logfile.txt", "w");

	i = eXosip_init(NULL, NULL, 6060);
	if (i!=0)
	{
		fprintf (stderr, "test: could not initialize eXosip\n");
		return;  
	}
	eXosip_sdp_negotiation_remove_audio_payloads();
	reg_id = eXosip_register_init(identity, registrar, contact);
	j = eXosip_register(reg_id, 3600);
	std::cout<<"init"<<endl;

	//	eXosip_sdp_negotiation_add_codec(osip_strdup("0"),
	//		NULL,
	//		osip_strdup("RTP/AVP"),
	//		NULL, NULL, NULL,
	//		NULL,NULL,
	//		osip_strdup("0 PCMU/8000"));
	//
	//	eXosip_sdp_negotiation_add_codec(osip_strdup("8"),
	//		NULL,
	//		osip_strdup("RTP/AVP"),
	//		NULL, NULL, NULL,
	//		NULL,NULL,
	//		osip_strdup("8 PCMA/8000"));

	//18 G729a/8000
	eXosip_sdp_negotiation_add_codec(osip_strdup("18"),
		NULL,
		osip_strdup("RTP/AVP"),
		NULL, NULL, NULL,
		NULL,NULL,
		osip_strdup("18 G729a/8000"));
	eXosip_set_mode(EVENT_MODE);

	
	std::cout << "oSIP>"<<endl;

	//	while( run )
	//	{
	//		josua_event_get();
	//
	//	}
	SetTimer(1001,0,NULL);
}

void CTestwinDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	int counter =0;
	/* use events to print some info */
	eXosip_event_t *je;
	//	for (;;)
	{
		char buf[100];
		je = eXosip_event_wait(0,1);
		if (je==NULL)
			return;
		counter++;
		if (je->type==EXOSIP_CALL_NEW)
		{
			TRACE( "<- (%i %i) INVITE from: %s",
				je->cid, je->did,
				je->remote_uri);
			josua_printf(buf);

			call.build(je);
		}
		else if (je->type==EXOSIP_CALL_ANSWERED)
		{
			TRACE( "<- (%i %i) [%i %s ANSWERED] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
			call.build(je);
		}
		else if (je->type==EXOSIP_CALL_PROCEEDING)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
			josua_printf("EXOSIP_CALL_PROCEEDING");
		}
		else if (je->type==EXOSIP_CALL_RINGING)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
			std::cout<<"EXOSIP_CALL_RINGING"<<endl;
		}
		else if (je->type==EXOSIP_CALL_CANCELLED)
		{std::cout<<"cancer";
		}
		else if (je->type==EXOSIP_CALL_REDIRECTED)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
			std::cout<<"EXOSIP_CALL_REDIRECTED"<<endl;
		}
		else if (je->type==EXOSIP_CALL_REQUESTFAILURE)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
			std::cout<<"EXOSIP_CALL_REQUESTFAILURE"<<endl;
		}
		else if (je->type==EXOSIP_CALL_SERVERFAILURE)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_CALL_GLOBALFAILURE)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_CALL_CLOSED)
		{
			TRACE( "<- (%i %i) BYE from: %s",
				je->cid, je->did, je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_CALL_HOLD)
		{
			TRACE( "<- (%i %i) INVITE (On Hold) from: %s",
				je->cid, je->did, je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_CALL_OFFHOLD)
		{
			TRACE( "<- (%i %i) INVITE (Off Hold) from: %s",
				je->cid, je->did, je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_REGISTRATION_SUCCESS)
		{
			TRACE( "<- (%i) [%i %s] %s for REGISTER_SUCCESS %s",
				je->rid,
				je->status_code,
				je->reason_phrase,
				je->remote_uri,
				je->req_uri);
			josua_printf(buf);
			std::cout<<endl;
		}
		else if (je->type==EXOSIP_REGISTRATION_REFRESHED)
		{

		}
		else if (je->type== EXOSIP_REGISTRATION_TERMINATED)
		{

		}
		else if (je->type==EXOSIP_REGISTRATION_FAILURE)
		{
			int reg_id = eXosip_register_init(identity, registrar, contact);
			if(eXosip_add_authentication_info(username, username, password, NULL, NULL)) 
			{
				exit(1);
			}
			eXosip_lock();
			j = eXosip_register(reg_id, expires);
			eXosip_unlock();
			std::cout<<"REGISTER_FAILURE";
			TRACE( "<- (%i) [%i %s] %s for REGISTER_FAILURE %s",
				je->rid,
				je->status_code,
				je->reason_phrase,
				je->remote_uri,
				je->req_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_OPTIONS_NEW)
		{
			TRACE( "<- (%i %i) OPTIONS from: %s",
				je->cid, je->did,
				je->remote_uri);
			josua_printf(buf);

		}
		else if (je->type==EXOSIP_OPTIONS_ANSWERED)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_OPTIONS_PROCEEDING)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);

		}
		else if (je->type==EXOSIP_OPTIONS_REDIRECTED)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_OPTIONS_REQUESTFAILURE)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_OPTIONS_SERVERFAILURE)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_OPTIONS_GLOBALFAILURE)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_NEW)
		{
			TRACE( "<- (%i %i) INFO from: %s",
				je->cid, je->did,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_ANSWERED)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_PROCEEDING)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_REDIRECTED)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_REQUESTFAILURE)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_SERVERFAILURE)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_GLOBALFAILURE)
		{
			TRACE( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}

		else if (je->type==EXOSIP_SUBSCRIPTION_ANSWERED)
		{
			TRACE( "<- (%i %i) [%i %s] %s for SUBSCRIBE",
				je->sid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);

			TRACE( "<- (%i %i) online=%i [status: %i reason:%i]",
				je->sid, je->did, 
				je->online_status,
				je->ss_status,
				je->ss_reason);
			josua_printf(buf);

		}
		else if (je->type==EXOSIP_SUBSCRIPTION_PROCEEDING)
		{
			TRACE( "<- (%i %i) [%i %s] %s for SUBSCRIBE",
				je->sid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);

		}
		else if (je->type==EXOSIP_SUBSCRIPTION_REDIRECTED)
		{
			TRACE( "<- (%i %i) [%i %s] %s for SUBSCRIBE",
				je->sid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_SUBSCRIPTION_REQUESTFAILURE)
		{
			TRACE( "<- (%i %i) [%i %s] %s for SUBSCRIBE",
				je->sid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_SUBSCRIPTION_SERVERFAILURE)
		{
			TRACE( "<- (%i %i) [%i %s] %s for SUBSCRIBE",
				je->sid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_SUBSCRIPTION_GLOBALFAILURE)
		{
			TRACE( "<- (%i %i) [%i %s] %s for SUBSCRIBE",
				je->sid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_SUBSCRIPTION_NOTIFY)
		{
			TRACE( "<- (%i %i) NOTIFY from: %s",
				je->sid, je->did,
				je->remote_uri);
			josua_printf(buf);

			TRACE( "<- (%i %i) online=%i [status: %i reason:%i]",
				je->sid, je->did, 
				je->online_status,
				je->ss_status,
				je->ss_reason);
			josua_printf(buf);

		}
		else if (je->type==EXOSIP_IN_SUBSCRIPTION_NEW)
		{
			TRACE( "<- (%i %i) SUBSCRIBE from: %s",
				je->nid, je->did,
				je->remote_uri);
			josua_printf(buf);

			/* search for the user to see if he has been
			previously accepted or not! */

			eXosip_notify(je->did, EXOSIP_SUBCRSTATE_PENDING, EXOSIP_NOTIFY_AWAY);
		}
		else if (je->textinfo[0]!='\0')
		{
			TRACE( "(%i %i %i %i) %s", je->cid, je->sid, je->nid, je->did, je->textinfo);
			josua_printf(buf);
		}


		eXosip_event_free(je);
	}
	if (counter>0)
		return ;

	CDialog::OnTimer(nIDEvent);
}
int portbase=10000;
char *destip="sip:983057552@192.168.3.190:6060";
int destport=80;
char ipstr[256];
int status,i;
char dummybuffer[1024];
osip_message_t *invite;

//CWaveIn* m_pIn=new CWaveIn();
void CTestwinDlg::OnCall() 
{
	// TODO: Add your control notification handler code here
	m_pIn->StartRec();
	i = eXosip_build_initial_invite(&invite,
		destip,       //±»½Ð
		identity,     //Ö÷½Ð
		NULL,
		"oSIP phone");
				if (i!=0)
				{
					fprintf (stderr, "eXosip_build_initial_invite failed\n");
					return;
				}
				eXosip_lock();
				eXosip_initiate_call(invite, NULL, NULL, "10500");
				eXosip_unlock();
}
