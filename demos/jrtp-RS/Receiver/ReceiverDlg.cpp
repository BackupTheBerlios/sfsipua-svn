// ReceiverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Receiver.h"
#include "ReceiverDlg.h"
#include "M:/sips/jrtp/jrtplib-2.9/rtpsession.h"
#include "M:/sips/jrtp/jrtplib-2.9/rtppacket.h"
#include <conio.h>
#include <string.h>
#include "AudioCode.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define BUFSIZE 960
#define PACKSIZE BUFSIZE+50
#include "WaveOut.h"
/////////////////////////////////////////////////////////////////////////////
// CReceiverDlg dialog
bool bTmpFile=true;
bool fileopen=false;
bool multi=false;
RTPSession sess;
CWaveOut *g_pOut =new CWaveOut();
CReceiverDlg::CReceiverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReceiverDlg::IDD, pParent)
{	
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2,0),&wsadata);

	//{{AFX_DATA_INIT(CReceiverDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReceiverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReceiverDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReceiverDlg, CDialog)
	//{{AFX_MSG_MAP(CReceiverDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LINK, OnLink)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReceiverDlg message handlers

BOOL CReceiverDlg::OnInitDialog()
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

void CReceiverDlg::OnPaint() 
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
HCURSOR CReceiverDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void FreeMsg(MSG msg)
{
	if (PeekMessage(&msg, 0, 0,	0, PM_REMOVE))
	{
		
			TranslateMessage(&msg);
			DispatchMessage(&msg);
    }
}


void  Pause(DWORD ms)	//∫¡√Î—” ±
{
	DWORD dwtm;
	MSG	msg;
	memset(&msg,0,sizeof(MSG));
	dwtm = GetTickCount();
	while (GetTickCount() < (dwtm+ms))
		FreeMsg(msg);

}
CAudioCode g_ACode;
char m_cOut [1024];
int iOut;
void CReceiverDlg::OnLink() 
{

//	WSADATA wsadata;
//	WSAStartup(MAKEWORD(2,0),&wsadata);
//	RTPSession sess;
	int t,h;
	int g=0;
	t=sess.Create(6900);
	if(t!=0)AfxMessageBox("can't create");
	h=sess.JoinMulticastGroup(ntohl(inet_addr("127.0.0.1")));
	if(h!=0){multi=true;}
	CString tt;
	tt="D://ourt.txt";
	g_pOut->StartPlay();
	t=file.Open(tt,CFile::modeWrite|CFile::modeCreate);
//	file.Close();
	if(t!=0){fileopen=true;}
	t=sess.SetMaxPacketSize(PACKSIZE);
	if(t!=0)AfxMessageBox("can't set size");
	BYTE Filebuf[BUFSIZE];	
	do
	{
		sess.PollData();
		if (sess.GotoFirstSourceWithData())	
		{		Sleep(10);
		
		
			if(g==10)
			{	
				//				AfxMessageBox("write 10");
				g=0;
			}
		
			//			file.Open(tt,CFile::modeWrite);	
			do
				{	
					RTPPacket *pack;
					pack = sess.GetNextPacket();				
					memcpy(Filebuf,pack->GetPayload(),BUFSIZE);//packet to buffer
			//		bTmpFile=pack->IsMarked(); 
			//		if(bTmpFile)
						{		
							    
							file.Write(Filebuf,BUFSIZE);

							//g_ACode.DecodeAudioData ((char *)Filebuf,60,m_cOut,&iOut);

							//file.Write(m_cOut,iOut);
							g_pOut->Play ((char *)Filebuf,BUFSIZE);
							g=g+1;
						
							//bTmpFile=false;
						}
					delete pack;
				} while (sess.GotoNextSourceWithData());
				//			file.Close();
		}	
		Pause(100);
	}while(1);
	file.Close();
	AfxMessageBox("fail");
	WSACleanup();
}

		



void CReceiverDlg::OnClose() 
{
	if(multi)
	{sess.LeaveAllMulticastGroups();
		sess.Destroy();
		multi=false;
	}
	if(fileopen){	file.Close();}
	
	WSACleanup();
	OnOK();
}


void CReceiverDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog  dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
			"(*.*)|*.*|", NULL);
	CString m_SourceFile;
	if (dlg.DoModal() == IDOK)
	{
		m_SourceFile = dlg.GetPathName();	
	}
	FILE *source=fopen(m_SourceFile,"rb");
	if ( source == NULL )
	{
		AfxMessageBox("can't access the file");
	}
//#ifdef win32
 	
//#endif	
	size_t bufRead  = 0;
	BOOL Mark=true;
	int bufsize=102400;
	BYTE buffer[102400];
	
	g_pOut->StartPlay();
	(void) fseek( source, 0, SEEK_SET );
		while(!feof(source))
		{
			bufRead = fread(buffer, sizeof(BYTE), bufsize, source ); 
			g_pOut->Play((char *)buffer,bufRead);
			Sleep(100);
		}
		(void) fflush( source ); 
		(void) fclose( source ); 
		AfxMessageBox("send success");
	
}
