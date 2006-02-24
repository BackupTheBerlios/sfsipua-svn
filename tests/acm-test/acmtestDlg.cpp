// acmtestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "acmtest.h"
#include "acmtestDlg.h"
#include "Acmcodec.h"
#include "assert.h"
#include "ACM.h"
#include "./jrtp/rtpsession.h"
#include "./jrtp/rtppacket.h"
#pragma comment(lib,"./jrtplib-2.6.lib")
#pragma comment(lib,"ws2_32")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "WavInOut.h"

#define bufsize 960
#define PACKSIZE 960+50

RTPSession sessnd;
RTPSession sessrec;

int nPT,nTSTAMP;
BOOL Mark=true;

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
// CAcmtestDlg dialog

CAcmtestDlg::CAcmtestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAcmtestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAcmtestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAcmtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAcmtestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAcmtestDlg, CDialog)
	//{{AFX_MSG_MAP(CAcmtestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAcmtestDlg message handlers

BOOL CAcmtestDlg::OnInitDialog()
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
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2,0),&wsadata);
	int i=sessrec.Create(6900);
	i=sessrec.JoinMulticastGroup(ntohl(inet_addr("127.0.0.1")));
	i=sessrec.SetMaxPacketSize(PACKSIZE);
	i=sessnd.Create(5800);
	i=sessnd.SetMulticastTTL(1);	//設定multicast封包TTL
	i=sessnd.AddDestination(ntohl(inet_addr("127.0.0.1")),6900);	//指定傳送目的端
	
	// TODO: Add your control notification handler code here
	

	//sess.AddDestination(ntohl(inet_addr("192.168.25.79")),6900);
	//	if(t!=0)AfxMessageBox("can't add destination");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAcmtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAcmtestDlg::OnPaint() 
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
HCURSOR CAcmtestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CAcmtestDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	//	DWORD dwACMVer = acmGetVersion();
	//	printf("ACM version %u.%.02u build %u",
	//			HIWORD(dwACMVer) >> 8,
	//			HIWORD(dwACMVer) & 0x00FF,
	//			LOWORD(dwACMVer));
	//	if (LOWORD(dwACMVer) == 0) printf(" (Retail)");
	//	printf("\n");
	//
	//	// show some ACM metrics
	//	printf("ACM metrics:\n");
	//
	//	DWORD dwCodecs = 0;
	//	MMRESULT mmr = acmMetrics(NULL, ACM_METRIC_COUNT_CODECS, &dwCodecs);
	//	if (mmr) {
	//		
	//	} else {
	//		printf("%lu codecs installed\n", dwCodecs);
	//	}

	CAcmcodec acm;
	char strv[20];
	DWORD v=acm.GetVer(strv);
	acm.ChkCodec();
	BOOL l=acm.bG711;

}
#define MP3_BLOCK_SIZE 522

DWORD convertMP3(){
  
  MMRESULT mmr;
  
  // try to find an MP3 codec
  
  
  // find the biggest format size
  DWORD maxFormatSize = 0;
  mmr = acmMetrics( NULL, ACM_METRIC_MAX_SIZE_FORMAT, &maxFormatSize );
  
  // define desired output format
  LPWAVEFORMATEX waveFormat = (LPWAVEFORMATEX) LocalAlloc( LPTR, maxFormatSize );
  waveFormat->wFormatTag = WAVE_FORMAT_PCM;
  waveFormat->nChannels = 2; // stereo
  waveFormat->nSamplesPerSec = 44100; // 44.1kHz
  waveFormat->wBitsPerSample = 16; // 16 bits
  waveFormat->nBlockAlign = 4; // 4 bytes of data at a time are useful (1 sample)
  waveFormat->nAvgBytesPerSec = 4 * 44100; // byte-rate
  waveFormat->cbSize = 0; // no more data to follow
  
  
  // define MP3 input format
  LPMPEGLAYER3WAVEFORMAT mp3format = (LPMPEGLAYER3WAVEFORMAT) LocalAlloc( LPTR, maxFormatSize );
  mp3format->wfx.cbSize = MPEGLAYER3_WFX_EXTRA_BYTES;
  mp3format->wfx.wFormatTag = WAVE_FORMAT_MPEGLAYER3;
  mp3format->wfx.nChannels = 2;
  mp3format->wfx.nAvgBytesPerSec = 128 * (1024 / 8);  // not really used but must be one of 64, 96, 112, 128, 160kbps
  mp3format->wfx.wBitsPerSample = 0;                  // MUST BE ZERO
  mp3format->wfx.nBlockAlign = 1;                     // MUST BE ONE
  mp3format->wfx.nSamplesPerSec = 44100;              // 44.1kHz
  mp3format->fdwFlags = MPEGLAYER3_FLAG_PADDING_OFF;
  mp3format->nBlockSize = MP3_BLOCK_SIZE;             // voodoo value #1
  mp3format->nFramesPerBlock = 1;                     // MUST BE ONE
  mp3format->nCodecDelay = 1393;                      // voodoo value #2
  mp3format->wID = MPEGLAYER3_ID_MPEG;
  HACMSTREAM g_mp3stream = NULL;

  mmr = acmStreamOpen( &g_mp3stream,               // open an ACM conversion stream
  		     NULL,                       // querying all ACM drivers
  		     (LPWAVEFORMATEX) mp3format, // converting from MP3
  		     waveFormat,                 // to WAV
  		     NULL,                       // with no filter
  		     0,                          // or async callbacks
  		     0,                          // (and no data for the callback)
  		     0                           // and no flags
  		     );
  
  LocalFree( mp3format );
  LocalFree( waveFormat );
  
  switch( mmr ) {
   case MMSYSERR_NOERROR:
     break; // success!
   case MMSYSERR_INVALPARAM:
     TRACE(  "Invalid parameters passed to acmStreamOpen" );
     return E_FAIL;
   case ACMERR_NOTPOSSIBLE:
     TRACE(  "No ACM filter found capable of decoding MP3" );
     return E_FAIL;
   default:
     TRACE(  "Some error opening ACM decoding stream!" );
     return E_FAIL;
  }
  
  // MP3 stream converter opened correctly
  // now, let's open a file, read in a bunch of MP3 data, and convert it!
  
  // open file
  FILE *fpIn = fopen( "g:/afei.mp3", "rb" );
  if( fpIn == NULL ){
    TRACE(  "can't open MP3 file!" );
    return E_FAIL;
  }
  
  // find out how big the decompressed buffer will be
  unsigned long rawbufsize = 0;
  mmr = acmStreamSize( g_mp3stream, MP3_BLOCK_SIZE, &rawbufsize, ACM_STREAMSIZEF_SOURCE );
  assert( mmr == 0 );
  assert( rawbufsize > 0 );
  
  // allocate our I/O buffers
  LPBYTE mp3buf = (LPBYTE) LocalAlloc( LPTR, MP3_BLOCK_SIZE );
  LPBYTE rawbuf = (LPBYTE) LocalAlloc( LPTR, rawbufsize );
  
  // prepare the decoder
  ACMSTREAMHEADER mp3streamHead;
  ZeroMemory( &mp3streamHead, sizeof(ACMSTREAMHEADER ) );
  mp3streamHead.cbStruct = sizeof(ACMSTREAMHEADER );
  mp3streamHead.pbSrc = mp3buf;
  mp3streamHead.cbSrcLength = MP3_BLOCK_SIZE;
  mp3streamHead.pbDst = rawbuf;
  mp3streamHead.cbDstLength = rawbufsize;
  mmr = acmStreamPrepareHeader( g_mp3stream, &mp3streamHead, 0 );
  assert( mmr == 0 );
  
  // let's dump this data off to disk (for debug checking!)
  FILE *fpOut = fopen( "g:/afei.wav", "wb" );
  if( fpOut == NULL ){
    assert(  "can't output output PCM!" );
    return E_FAIL;
  }
  
  while(1) {
    // suck in some MP3 data
    int count = fread( mp3buf, 1, MP3_BLOCK_SIZE, fpIn );
    if( count != MP3_BLOCK_SIZE )
      break;
  
    // convert the data
    mmr = acmStreamConvert( g_mp3stream, &mp3streamHead, ACM_STREAMCONVERTF_BLOCKALIGN );
    assert( mmr == 0 );
  
    // write the decoded PCM to disk
    count = fwrite( rawbuf, 1, mp3streamHead.cbDstLengthUsed, fpOut );
    assert( (DWORD)count == mp3streamHead.cbDstLengthUsed );
  };
  
  // clean up after yourself like a good little boy
  fclose( fpIn );
  fclose( fpOut );
  mmr = acmStreamUnprepareHeader( g_mp3stream, &mp3streamHead, 0 );
  assert( mmr == 0 );
  LocalFree(rawbuf);
  LocalFree(mp3buf);
  mmr = acmStreamClose( g_mp3stream, 0 );
  assert( mmr == 0 );
  
  return S_OK;
}

void CAcmtestDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	convertMP3();
}



void  Pause(DWORD ms)	//瑭鏃晊奀
{
	DWORD dwtm;
	MSG	msg;
	memset(&msg,0,sizeof(MSG));
	dwtm = GetTickCount();
	while (GetTickCount() < (dwtm+ms))
	{
		if (PeekMessage(&msg, 0, 0,	0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	    }
	}
}
char recbuffer[1024];
int recllen=0;
#define BUFSIZE 960
//#define PACKSIZE BUFSIZE+50

FILE *ss=NULL;
int Wav2RTP(char* buff, int len)
{
	//	size_t bufRead  = 0;
	//
	//	
	//	sessnd.SetMulticastTTL(1);	//設定multicast封包TTL
	//	sessnd.AddDestination(ntohl(inet_addr("127.0.0.1")),6900);	//指定傳送目的端
	//	nPT=rand()%64+1;		
	//	nTSTAMP=rand()%1000+1;	
	//	int t=sessnd.SendPacket(buff,len,nPT,Mark,nTSTAMP);	
	//	Sleep(5);
	//	Mark=false;	

	if (ss==NULL) 
	{
		ss=fopen("c:/rec.wav","wb");
	}
	fwrite(buff,sizeof(BYTE),len, ss);
	return len;

	nPT=rand()%64+1;		
	nTSTAMP=rand()%1000+1;	
	sessnd.SendPacket(buff,len,nPT,Mark,nTSTAMP);	
	Sleep(5);
	Mark=false;	
	//	memcpy(recbuffer,buff,len);
	//	recllen=len;
	return len;
}


int RTP2Wav(char* buff, int len)
{
	//memcpy(buff,recbuffer,recllen);
	sessrec.PollData();
	if (sessrec.GotoFirstSourceWithData())	
	{	
			RTPPacket *pack;
			pack = sessrec.GetNextPacket();				
			memcpy(buff,pack->GetPayload(),BUFSIZE);//packet to buffer
			delete pack;
			sessrec.GotoNextSourceWithData();
	} 
	
	return BUFSIZE;
}

void CAcmtestDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	WavInOut*		m_WaveIOObj;
	m_WaveIOObj = WavInOut::instance();
	
	m_WaveIOObj->init(Wav2RTP,RTP2Wav);
	WAV_FORMATE wavetype= WAV_PCMA;

	m_WaveIOObj->stopPlaying();
	m_WaveIOObj->stopRecording();

	if(m_WaveIOObj->isWavInOpen)	m_WaveIOObj->wavInClose();
	if(m_WaveIOObj->isWavOutOpen)	m_WaveIOObj->wavOutClose();

	if(m_WaveIOObj->wavInOpen(wavetype,8,8000,1,30)!=0)
			TRACE("Open WaveIO Error!");
		else if ( m_WaveIOObj->startRecording()!=0 )
			TRACE("Record Error!");

		if(m_WaveIOObj->wavOutOpen(wavetype,8,8000,1,30)!=0)
			TRACE("Open WaveOut Error!");
		else if ( m_WaveIOObj->startPlaying()!=0 )
			TRACE("Playing Error!");
}


void CAcmtestDlg::OnButton4() 
{
	
	RTPSession sess;
	int t,h;
	int g=0;
	t=sess.Create(6900);
	h=sess.JoinMulticastGroup(ntohl(inet_addr("127.0.0.1")));
	CString tt;
	t=sess.SetMaxPacketSize(PACKSIZE);
	if(t!=0)AfxMessageBox("can't set size");

	do
	{
		sess.PollData();
		if (sess.GotoFirstSourceWithData())	
		{		Sleep(10);
		
		
			if(g==10)
			{	
				g=0;
			}
			do
			{	
					RTPPacket *pack;
					pack = sess.GetNextPacket();				
					//memcpy(Filebuf,pack->GetPayload(),BUFSIZE);//packet to buffer
					memcpy(recbuffer,pack->GetPayload(),BUFSIZE);
					recllen=BUFSIZE;
					g=g+1;
					delete pack;
			} while (sess.GotoNextSourceWithData());
		}
		Pause(100);
	}while(1);
	WSACleanup();
}

void CAcmtestDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
		CFileDialog  dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
			"(*.*)|*.*|", NULL);
		CString m_SourceFile;
	if (dlg.DoModal() == IDOK)
	{
		m_SourceFile = dlg.GetPathName();	
	}
	FILE* source=fopen(m_SourceFile,"rb");
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
	
	
	t=sessrec.Create(5800);
	if(t!=0)AfxMessageBox("can't create");
	
	sessrec.SetMulticastTTL(1);	//設定multicast封包TTL
	sessrec.AddDestination(ntohl(inet_addr("127.0.0.1")),6900);	//指定傳送目的端
	//sess.AddDestination(ntohl(inet_addr("192.168.25.79")),6900);
	if(t!=0)AfxMessageBox("can't add destination");
	(void) fseek( source, 0, SEEK_SET );
		while(!feof(source))
		{
			bufRead = fread(buffer, sizeof(BYTE), bufsize, source ); 
			nPT=rand()%64+1;		
			nTSTAMP=rand()%1000+1;	

			t=sessrec.SendPacket(buffer,bufsize,nPT,Mark,nTSTAMP);	
			recllen=bufsize;
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

void CAcmtestDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	
	WAVEFORMATEX *pwfxSrc,*pwfxDest;
	int iWaveMetrics;
	//
	CACM *pCODEC=NULL;
	pCODEC=(CACM *)new CACM();
	iWaveMetrics=pCODEC->GetWaveMetrics();


	//SetWaveFormat(iWaveMetrics);
	int iMetrics=iWaveMetrics;
	pwfxSrc=(WAVEFORMATEX *)new BYTE[iMetrics];
	memset(pwfxSrc,0,iMetrics);
	pwfxDest=(WAVEFORMATEX *)new BYTE[iMetrics];
	memset(pwfxDest,0,iMetrics);
	pwfxSrc->cbSize = 0;
	pwfxSrc->wFormatTag = WAVE_FORMAT_PCM;
	pwfxSrc->nChannels = 1;
	pwfxSrc->nSamplesPerSec = 8000;
	pwfxSrc->wBitsPerSample = 16;
	pwfxSrc->nBlockAlign = (pwfxSrc->nChannels * pwfxSrc->wBitsPerSample) / 8;
	pwfxSrc->nAvgBytesPerSec= (pwfxSrc->nSamplesPerSec * pwfxSrc->nChannels * pwfxSrc->wBitsPerSample) / 8; 



	HACMDRIVERID hadid=NULL;
	// BOOL bb=pCODEC->FindDriver(&hadid,WAVE_FORMAT_GSM610,0,pwfxDest,iWaveMetrics);
	BOOL bb=pCODEC->FindDriver(&hadid,WAVE_FORMAT_DSPGROUP_TRUESPEECH,0,pwfxDest,iWaveMetrics);
	if(bb)
	{
		pCODEC->SetWaveFormat(pwfxSrc,pwfxDest);
		pCODEC->Start(hadid);
	}

//
}
