// SenderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sender.h"
#include "SenderDlg.h"
#include "M:/sips/jrtp/jrtplib-2.9/rtpsession.h"
#include "M:/sips/jrtp/jrtplib-2.9/rtppacket.h"
#include <fstream.h>
#include <process.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "AudioCode.h"
#define bufsize 960
/////////////////////////////////////////////////////////////////////////////
// CSenderDlg dialog
bool Mark=false;
bool sen;
RTPSession sess;
CSenderDlg::CSenderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSenderDlg::IDD, pParent)
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2,2),&wsadata);
	//{{AFX_DATA_INIT(CSenderDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSenderDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSenderDlg, CDialog)
	//{{AFX_MSG_MAP(CSenderDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSenderDlg message handlers

BOOL CSenderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSenderDlg::OnPaint() 
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
HCURSOR CSenderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
char m_cBufOut [1024];
CAudioCode g_ACode;
int iOut;
void CSenderDlg::OnSend() 
{
	CFileDialog  dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
			"(*.*)|*.*|", NULL);
	if (dlg.DoModal() == IDOK)
	{
		m_SourceFile = dlg.GetPathName();	
	}
	source=fopen(m_SourceFile,"rb");
	if ( source == NULL )
	{
		AfxMessageBox("can't access the file");
	}
//#ifdef win32
 	
//#endif	
	size_t bufRead  = 0;
	Mark=true;
	BYTE buffer[bufsize];
	int t;
	
	
	t=sess.Create(5800);
	if(t!=0)AfxMessageBox("can't create");
	if(t==0){sen=true;}
	sess.SetMulticastTTL(1);	//設定multicast封包TTL
	sess.AddDestination(ntohl(inet_addr("127.0.0.1")),6900);	//指定傳送目的端
	//sess.AddDestination(ntohl(inet_addr("192.168.25.79")),6900);
	if(t!=0)AfxMessageBox("can't add destination");
	(void) fseek( source, 0, SEEK_SET );
		while(!feof(source))
		{
			bufRead = fread(buffer, sizeof(BYTE), bufsize, source ); 
			nPT=rand()%64+1;		
			nTSTAMP=rand()%1000+1;	

			//g_ACode.EncodeAudioData ((char*)buffer,bufsize,m_cBufOut,&iOut);
			t=sess.SendPacket(buffer,bufsize,nPT,Mark,nTSTAMP);	
			//t=sess.SendPacket(buffer,bufsize,nPT,Mark,nTSTAMP);	
		    if(t!=0)AfxMessageBox("can't sending");
			Sleep(5);
			Mark=false;			
		}
		(void) fflush( source ); 
		(void) fclose( source ); 
		AfxMessageBox("send success");
	WSACleanup();
	
}

void CSenderDlg::OnClose() 
{
	if(sen)
	{sess.Destroy();
		sen=false;
	}
	WSACleanup();
	OnOK();
	
}
