// CNIcqDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CNIcq.h"
#include "CNIcqDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	WM_ICON_NOTIFY			WM_USER+200

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
	virtual void OnOK();
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCNIcqDlg dialog

CCNIcqDlg::CCNIcqDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCNIcqDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCNIcqDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pGif = new CGif89a;

}
CCNIcqDlg::~CCNIcqDlg()
{
	delete m_pGif;
}
void CCNIcqDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCNIcqDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCNIcqDlg, CDialog)
	//{{AFX_MSG_MAP(CCNIcqDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCNIcqDlg message handlers

BOOL CCNIcqDlg::OnInitDialog()
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


	// Create the tray icon
	if (!m_TrayIcon.Create(NULL,                         // Parent window
			WM_ICON_NOTIFY,                  // Icon notify message to use
			_T("CN即时通讯"),  // tooltip
			::LoadIcon(NULL, IDI_ASTERISK),  // Icon to use
			IDR_POPUP_MENU)
	) // ID of tray icon
		return -1;

	m_TrayIcon.SetMenuDefaultItem(0, TRUE);

	//取控件对象
	//CButton *pButton = (CButton *)GetDlgItem(IDC_BUTTON1);
	//pButton->EnableWindow(FALSE);
/*
	pButton = new CButton;
	ASSERT_VALID (pButton);

	pButton->Create(_T("OK"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
		CRect(20,20,100,44),this,100);
*/
	m_pGif->Load("2.gif");
	m_pGif->Pause(TRUE);

	CRect rc;
	GetClientRect(&rc);

	m_ImTab.CreateEx(WS_EX_TRANSPARENT, NULL, NULL, WS_VISIBLE | WS_CHILD,
		CRect(0, 0, rc.Width(), rc.Height()-m_pGif->GetHeight()-5), this,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCNIcqDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCNIcqDlg::OnPaint() 
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
		CPaintDC dc(this); // device context for painting

		CDialog::OnPaint();

		CRect rect;
		GetClientRect(&rect);

		dc.FillSolidRect(rect, RGB(255,255,255));

	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCNIcqDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CCNIcqDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class

	//窗口居中
	cs.x = cs.y = 0;
	cs.cx=GetSystemMetrics(SM_CXSCREEN/2); 
	cs.cy=GetSystemMetrics(SM_CYSCREEN/2); 
	
	return CDialog::PreCreateWindow(cs);
}

void CCNIcqDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);
	//Fool dialog into thinking simeone clicked on its caption bar . 

	//点任意位置移动窗口
	PostMessage (WM_NCLBUTTONDOWN , HTCAPTION ,MAKELPARAM(point.x , point. y ));

}

/*
void CCNIcqDlg::GetTadkList(CListBox &list)
{
	CString strCaption; //Caption of window. 
	list.ResetContent (); //Clear list box. 
	//Get first Window in window list. 
	ASSERT_VALID (AfxGetMainWnd ()); 
	CWnd* pWnd=AfxGetMainWnd () ->GetWindow (GW_HWNDFIRST); 
	//Walk window list. 
	while (pWnd) 
	{ 
		// I window visible, has a caption, and does not have an owner? 
		if (pWnd ->IsWindowVisible () && 
		    pWnd ->GetWindowTextLength () &&! 
		    pWnd ->GetOwner ()) 
		{ 
			//Add caption o window to list box. 
			pWnd ->GetWindowText (strCaption); 
			list.AddString (strCaption); 
		} 
		//Get next window in window list. 
		pWnd=pWnd->GetWindow (GW_HWNDNEXT); 
	}

}
*/
void CCNIcqDlg::OnFileExit() 
{
	// TODO: Add your command handler code here
	if( MessageBox("你确定要退出系统吗?","提示",MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		EndDialog(0);	
	}
}

void CCNIcqDlg::OnHelpAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg AboutDlg;

	AboutDlg.DoModal();

}

void CCNIcqDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	
	// TODO: Add your message handler code here
	CRect rc;
	int iWidth,iHeight;

	GetClientRect(&rc);

	iWidth  = m_pGif->GetWidth();
	iHeight = m_pGif->GetHeight();


	m_pGif->Play(m_hWnd, CRect((cx-iWidth)/2,cy-iHeight-1,(cx-iWidth)/2 + iWidth,cy-1));
	m_pGif->Pause(FALSE);
	
	InvalidateRect(CRect(0,cy-iHeight-1,cx,cy-1));

	m_ImTab.MoveWindow(CRect(0, 0, rc.Width(), rc.Height()-iHeight-2),TRUE);
}


void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}


LRESULT CCNIcqDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::WindowProc(message, wParam, lParam);
}
