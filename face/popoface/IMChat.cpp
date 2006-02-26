// IMChat.cpp : implementation file
//

#include "stdafx.h"
#include "cnicq.h"
#include "IMChat.h"
#include "ImageDataObject.h"
#include "ImageSelector.h"
#include "CNPopupMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CHECK_WND(x)	if (!::IsWindow(x.m_hWnd)) return;
#define CHECK_WND_P(x)	if (!::IsWindow(x->m_hWnd)) return;
#define CHECK_WND_P0(x) if (!::IsWindow(x->m_hWnd)) return 0;
#define CHECK_WND0(x)	if (!::IsWindow(x.m_hWnd)) return 0;


/////////////////////////////////////////////////////////////////////////////
// CIMChat dialog

static UINT auIDStatusBar[] = {
	ID_SEPARATOR
};

CIMChat::CIMChat(CWnd* pParent /*=NULL*/)
	: CDialog(CIMChat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIMChat)
	//}}AFX_DATA_INIT
	m_crLink = AfxGetApp()->LoadIcon( IDC_HAND ) ;


	VERIFY(FontBold.CreateFont(
		12,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		FALSE,                     // cStrikeOut
		DEFAULT_CHARSET,            // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("宋体")));              // lpszFacename
	
	VERIFY(FontNormal.CreateFont(
		12,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		FALSE,                     // cStrikeOut
		DEFAULT_CHARSET,            // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("宋体")));              // lpszFacename


	m_SplitterPos = 0;
	m_bShowToolWin = true;
}


void CIMChat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIMChat)
	DDX_Control(pDX, IDC_BTN_TOOLWIN, m_btnToolWin);
	DDX_Control(pDX, IDC_BTN_FASTREPLY, m_btnReply);
	DDX_Control(pDX, IDC_MESSAGE, m_btnMessage);
	DDX_Control(pDX, IDC_EMOTONS, m_btnEmotons);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIMChat, CDialog)
	//{{AFX_MSG_MAP(CIMChat)
	ON_WM_SIZE()
	ON_NOTIFY( EN_LINK, IDC_EDIT_SHOWMSG, OnRichEditExLink )
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT_SENDMSG, OnChangeSendmsg)
	ON_BN_CLICKED(IDC_BTN_CHAT_SEND, OnBtnChatSend)
	ON_BN_CLICKED(IDC_MESSAGE, OnBtnMessage)
	ON_BN_CLICKED(IDC_EMOTONS, OnBtnEmotons)
	ON_BN_CLICKED(IDC_BTN_FASTREPLY, OnBtnFastreply)
	ON_BN_CLICKED(IDC_BTN_TOOLWIN, OnBtnToolwin)
	ON_COMMAND_RANGE(ID_IMAGE0, ID_IMAGE0 + NR_EMOTIONS, OnEmotionPick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIMChat message handlers


BOOL CIMChat::OnInitDialog() 
{

	CDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());
	
	CRect rcClientRect;
	CRect rcEmptyRect;

	GetClientRect(rcClientRect);

	rcEmptyRect.SetRectEmpty();

	SetFont(&FontNormal);

	//取应用程序的Skin对象
	m_pSkin = &(((CCNIcqApp *)AfxGetApp())->m_IMSkin);

	//创建工具窗口
	m_ToolWin.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcEmptyRect,this,IDC_TOOLWIN);
	m_ToolWin.SetImageList(&(m_pSkin->m_pILSendMsgIcon));

	m_ToolWin.AddFolder("我想...",10);
	m_ToolWin.AddFolder("语音聊天...",10);
	
	//创建显示消息编辑框
	m_ShowMsgEdit.Create(WS_CHILD | WS_VISIBLE |
		//ES_AUTOHSCROLL | 
		ES_AUTOVSCROLL | ES_NOHIDESEL |
		WS_CLIPCHILDREN |
		ES_MULTILINE | ES_WANTRETURN,
		CRect(0,0,0,0),
		this,
		IDC_EDIT_SHOWMSG);

	m_ShowMsgEdit.SetEventMask(m_ShowMsgEdit.GetEventMask() | ENM_LINK ) ; 
	m_ShowMsgEdit.AutoURLDetect( TRUE ) ;
	m_ShowMsgEdit.ReadOnly();
	m_ShowMsgEdit.SetFont(&FontNormal);
	//m_ShowMsgEdit.ShowScrollBar(SB_VERT);

	m_pRichEditOle = m_ShowMsgEdit.GetIRichEditOle();

	//创建发送消息输入框
	m_SendEdit.Create(WS_CHILD | WS_VISIBLE |
		//ES_AUTOHSCROLL | 
		ES_AUTOVSCROLL | 
		WS_CLIPCHILDREN |
		ES_MULTILINE | ES_WANTRETURN,
		CRect(0,0,0,0),
		this,
		IDC_EDIT_SENDMSG);

	m_SendEdit.SetEventMask(m_SendEdit.GetEventMask() | ENM_CHANGE | ENM_LINK ) ; 
	m_SendEdit.SetFont(&FontNormal);
	m_SendEdit.LimitText(500);


	//创建状态栏
	if (m_statusBar.Create(this))
	{
		m_statusBar.SetIndicators(auIDStatusBar, sizeof(auIDStatusBar) / sizeof(unsigned int));
		m_statusBar.SetPaneInfo(0, m_statusBar.GetItemID(0),SBPS_STRETCH, NULL );
	}
	//创建移动条
	m_Splitter.Create(NULL, WS_CHILD | SS_NOTIFY, rcEmptyRect, this, IDC_STATIC);
	m_Splitter.ShowWindow(SW_SHOW);
	m_Splitter.SetBkColor(m_pSkin->MsgWndEdgeClr);
	m_SplitterPos = 120;

	//修改发送按钮风格
	m_SendButton.SubclassDlgItem(IDC_BTN_CHAT_SEND, this);
	m_SendButton.SetTextAlignment(CMSNButton::AlignCenter);
	m_SendButton.SetFont(&FontNormal);
	m_SendButton.EnableWindow(FALSE);
	m_SendButton.SetCornerColor(RGB(255, 255, 255));
	m_SendButton.ShowWindow(TRUE);
	m_SendButton.DrawFocus(FALSE);

	HBITMAP hBmp;
	COLORREF crToolBarBkColor;
	CImageList &m_IIFormatBarImage = m_pSkin->m_pILSendMsgIcon;

	crToolBarBkColor = m_pSkin->MsgWndToolBarBGClr;

	//消息按钮
	m_btnMessage.SetFont(&FontNormal);
	hBmp = m_pSkin->GetImage(m_IIFormatBarImage,0);
	m_btnMessage.SetBitmaps(hBmp,RGB(255,0,0));
	m_btnMessage.SetColor(CNButton::BTNST_COLOR_BK_IN,crToolBarBkColor);
	m_btnMessage.SetColor(CNButton::BTNST_COLOR_BK_OUT,crToolBarBkColor);
	m_btnMessage.SetColor(CNButton::BTNST_COLOR_BK_FOCUS,crToolBarBkColor);

	//表情按钮
	m_btnEmotons.SetFont(&FontNormal);
	hBmp = m_pSkin->GetImage(m_IIFormatBarImage,2);
	m_btnEmotons.SetBitmaps(hBmp,RGB(255,0,0));
	m_btnEmotons.SetColor(CNButton::BTNST_COLOR_BK_IN,crToolBarBkColor);
	m_btnEmotons.SetColor(CNButton::BTNST_COLOR_BK_OUT,crToolBarBkColor);
	m_btnEmotons.SetColor(CNButton::BTNST_COLOR_BK_FOCUS,crToolBarBkColor);

	//快捷回复
	m_btnReply.SetFont(&FontNormal);
	hBmp = m_pSkin->GetImage(m_IIFormatBarImage,4);
	m_btnReply.SetBitmaps(hBmp,RGB(255,0,0));
	m_btnReply.SetColor(CNButton::BTNST_COLOR_BK_IN,crToolBarBkColor);
	m_btnReply.SetColor(CNButton::BTNST_COLOR_BK_OUT,crToolBarBkColor);
	m_btnReply.SetColor(CNButton::BTNST_COLOR_BK_FOCUS,crToolBarBkColor);

	//显示/隐藏右边窗口
	m_btnToolWin.SetFont(&FontNormal);
	hBmp = m_pSkin->GetImage(m_IIFormatBarImage,5);
	m_btnToolWin.SetBitmaps(hBmp,RGB(255,0,0));
	m_btnToolWin.SetColor(CNButton::BTNST_COLOR_BK_IN,crToolBarBkColor);
	m_btnToolWin.SetColor(CNButton::BTNST_COLOR_BK_OUT,crToolBarBkColor);
	m_btnToolWin.SetColor(CNButton::BTNST_COLOR_BK_FOCUS,crToolBarBkColor);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIMChat::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	UpdateSizes();
}

BOOL CIMChat::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::PreCreateWindow(cs);
}
void CIMChat::OnRichEditExLink(NMHDR* in_pNotifyHeader,LRESULT* out_pResult )
{
	ENLINK* l_pENLink = ( ENLINK* )in_pNotifyHeader ;

	*out_pResult = 0 ;

	switch( l_pENLink->msg )
	{
		case WM_SETCURSOR:
		{
			if( m_crLink != NULL )
			{
				::SetCursor( m_crLink ) ;
				*out_pResult = 1 ;
			}
		}
		break ;

		case WM_LBUTTONDOWN:
		{
			CString l_URL ;
			CHARRANGE l_CharRange ;

			m_ShowMsgEdit.GetSel( l_CharRange ) ;
			m_ShowMsgEdit.SetSel( l_pENLink->chrg ) ;
			l_URL = m_ShowMsgEdit.GetSelText() ;
			m_ShowMsgEdit.SetSel( l_CharRange ) ;

			CWaitCursor l_WaitCursor ;

			//AfxMessageBox(l_URL);
			ShellExecute( this->GetSafeHwnd(), _T( "open" ), l_URL, NULL, NULL, SW_SHOWNORMAL ) ;

			*out_pResult = 1 ;
		}
		break ;

		case WM_LBUTTONUP:
		{
			*out_pResult = 1 ;
		}
		break ;
		default:
			break ;
	}
}

void CIMChat::UpdateSizes()
{
	CRect rcStatus;
	CRect rcShowMsgEd;
	CRect rcSendMsgEd;
	CRect rcToolWin;
	CRect rcSplitter;
	CRect rcSendButton;
	CRect rcFormatBar;
	CRect rc;

	GetClientRect(rc);
	m_statusBar.GetClientRect(rcStatus);
	rc.bottom -= rcStatus.Height();

	int nBorderWidth = 3;
	int RightSpace = 0;

	if( m_bShowToolWin ) 
	{
		RightSpace = TOOLWIN_WIDTH;
	}

	//工具窗口
	rcToolWin   = CRect(rc.right-RightSpace,0,rc.right,rc.bottom);
	//消息显示窗口
	rcShowMsgEd = CRect(nBorderWidth,50,rc.right-RightSpace-nBorderWidth,rc.bottom - m_SplitterPos - 30);
	//
	rcSplitter  = CRect(nBorderWidth,rc.bottom - m_SplitterPos,rc.right-RightSpace-nBorderWidth,rc.bottom - m_SplitterPos + 3);
	//消息输入窗口
	rcSendMsgEd = CRect(nBorderWidth,rc.bottom - m_SplitterPos + 3,rc.right-RightSpace-nBorderWidth - 60,rc.bottom-nBorderWidth-4);
	
	rcSendButton= CRect(rc.right-RightSpace-nBorderWidth - 58,rc.bottom - m_SplitterPos + 8,rc.right-RightSpace-nBorderWidth - 5,rc.bottom - m_SplitterPos + 50);

	rcFormatBar = CRect(nBorderWidth,rc.bottom - m_SplitterPos - 30,rc.right-RightSpace-nBorderWidth,rc.bottom - m_SplitterPos);
	//ScreenToClient(rcFormatBar);

	m_ShowMsgEdit.MoveWindow(rcShowMsgEd);
	m_Splitter.MoveWindow(rcSplitter);
	m_SendEdit.MoveWindow(rcSendMsgEd);
	m_ToolWin.MoveWindow(rcToolWin);
	m_SendButton.MoveWindow(rcSendButton);

	m_btnMessage.MoveWindow(rcFormatBar.left + 4,rcFormatBar.top + 3,60,25);
	m_btnEmotons.MoveWindow(rcFormatBar.left + 68,rcFormatBar.top + 3,60,25);
	m_btnReply.MoveWindow(rcFormatBar.left + 130,rcFormatBar.top + 3,80,25);
	m_btnToolWin.MoveWindow(rcFormatBar.left + 215,rcFormatBar.top + 3,80,25);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	Invalidate();
}

void CIMChat::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CRect rc;
	CRect rcStatus;

	GetClientRect(rc);
	m_statusBar.GetClientRect(rcStatus);
	rc.bottom -= rcStatus.Height();
	if( m_bShowToolWin)
	{
		rc.right  -= TOOLWIN_WIDTH;
	}

	CBitmap bm;
	bm.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	CBitmap *oldBitmap = memDC.SelectObject(&bm);
	
	//背景色
	memDC.FillSolidRect(rc, m_pSkin->MsgWndEdgeClr);

	memDC.FillSolidRect(CRect(3,45,rc.right - 3,rc.bottom - 3), RGB(255,255,255));

	//水平工具栏
	memDC.FillSolidRect(CRect(3,rc.bottom-m_SplitterPos-30,rc.right - 3,rc.bottom - m_SplitterPos), m_pSkin->MsgWndToolBarBGClr);

	//边角图片
	COLORREF clrMaskColor = RGB(255,0,0);
	CSize czImgSize(8,8);
	CBitmap& m_pCornerBmp = m_pSkin->CornerBmp;

	m_pSkin->DrawTransparent(&memDC,CPoint(0,42),m_pCornerBmp,CPoint(czImgSize.cx * 0,0),czImgSize,clrMaskColor); //左上角
	m_pSkin->DrawTransparent(&memDC,CPoint(rc.right-8,42),m_pCornerBmp,CPoint(czImgSize.cx*1,0),czImgSize,clrMaskColor); //右上角
	m_pSkin->DrawTransparent(&memDC,CPoint(rc.right-8,rc.bottom-8),m_pCornerBmp,CPoint(czImgSize.cx*7,0),czImgSize,clrMaskColor); //右下角
	m_pSkin->DrawTransparent(&memDC,CPoint(0,rc.bottom-8),m_pCornerBmp,CPoint(czImgSize.cx*6,0),czImgSize,clrMaskColor); //左下角

	//显示输出
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBitmap);

}


void CIMChat::SetSplitterPos(int NewPos)
{

	if( NewPos < 80) return;

	m_SplitterPos = NewPos;

	this->Invalidate();
}
void CIMChat::OnChangeSendmsg() 
{
	static bool Sent = true;
	char buf[512];

	m_SendEdit.GetWindowText(buf, sizeof(buf));

	if (!stricmp(buf, ""))
	{
		m_SendButton.EnableWindow(FALSE);
	}
	else
	{
		m_SendButton.EnableWindow(TRUE);
	}
}


void CIMChat::OnBtnChatSend() 
{
	/*
	CRTFBuilder c ;
	c	<< size(25) ;
	c	<< color(RGB(255,255,255)) << "White\n" ;
	c	<< red			<< "Red\n"
		<< blue			<< "Blue\n"
		<< green		<< "Green\n"
		<< black		<< "Black\n"
		<< bold			<< "Bold\n"
		<< italic		<< "Bold&Italic\n"
		<< underline		<< "Bold&Italic&Underline\n"
		<< strike		<< "Bold&Italic&Underline&Strike\n" 
		<< push							
		<< "Settings Pushed\n";

	c	<< normal ;
	c 	<< font("Comic Sans MS" );
	c 	<< size(15) ;
	c 	<< red ;
	c 	<< "About to PUSH with these new settings\n";
	c	<< push << blue << bold << size(20) << "Some more new settings\n" 
		<< pull << "Settings PULLED\n";
	c	<< pull << "Settings PULLED again\n" ;
			
	c	<< strike(false)	<< "Bold&Italic&Underline\n"
		<< underline(false) 	<< "Bold&Italic\n"
		<< italic(false)	<< "Bold\n"
		<< bold(false)		<< "Normal\n"
		<< size(30)		<< "Bigger\n"
		<< size(40)		<< "Bigger still\n"
		<< size(50)		<< "Bigger still\n"
		<< size(60)		<< "Bigger still\n"
		<< size(70)		<< "Bigger still\n"
		<< size(25)		<< "_______________\n\n"
		<< font("Tahoma")	<< "Tahoma\n"
		<< font("Arial")	<< "Arial\n"
		<< size(50)
		<< font("宋体")		<< "宋体\n"
		<< red			<< "这是我的消息程序 http://cicn.51.net\n"
		<< font("Courier New") 	<< "Courier New\n"
		>> m_ShowMsgEdit ;
	*/

	CString Text;

	m_SendEdit.GetText(Text);

	Text = "你说:  \n\t" + Text + "\n";

	m_ShowMsgEdit.InsertText(Text);

	m_SendEdit.SetText("");
	
}

void CIMChat::OnBtnMessage() 
{
	// TODO: Add your control notification handler code here
	
}

void CIMChat::OnBtnEmotons() 
{
	CRect rc;
	m_btnEmotons.GetClientRect(rc);
	m_btnEmotons.ClientToScreen(rc);
	
	new ImageSelector(&(m_pSkin->m_pILEmotions), 
		CRichEditCtrlEx::Emotions, 
		rc.left, rc.bottom, 
		10, this);

}

void CIMChat::OnBtnFastreply() 
{
	// TODO: Add your control notification handler code here
	CNPopupMenu menu;

	CMenu tmp;
	tmp.LoadMenu(IDR_MENU_REPLY);

	menu.Attach(*tmp.GetSubMenu(0));

	//加左边的图片
	//menu.setVertBitmap(IDB_VERT);

	CRect rc;
	m_btnReply.GetClientRect(rc);
	m_btnReply.ClientToScreen(rc);
	
	menu.TrackPopupMenu(TPM_TOPALIGN,rc.left,rc.bottom,this);
}

void CIMChat::OnBtnToolwin() 
{
	/*
	m_bShowToolWin = !m_bShowToolWin;

	m_ToolWin.ShowWindow(m_bShowToolWin);

	Invalidate();
	*/
}
void CIMChat::OnEmotionPick(UINT nID)
{
	int i = nID - ID_IMAGE0;
	m_SendEdit.InsertEmotion(i);
}