// IMShortcutTool.cpp : implementation file
//

#include "stdafx.h"
#include "CNIcq.h"
#include "IMShortcutTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CIMShortcutTool

CIMShortcutTool::CIMShortcutTool()
{
	m_pBtnIWarnt = new CNButton;

	m_iButtonCount = 0;
	
	for(int i = 0; i < MAX_BUTTON; i++)
	{
		m_pBtn[i] = NULL;
	}
	m_bHide = FALSE;
}

CIMShortcutTool::~CIMShortcutTool()
{
	delete m_pBtnIWarnt;

	for(int i = 0; i < m_iButtonCount;i++)
	{
		if( m_pBtn[i] )	
			delete m_pBtn[i];
	}
}

BEGIN_MESSAGE_MAP(CIMShortcutTool, CWnd)
	//{{AFX_MSG_MAP(CIMShortcutTool)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_SHORTCUT_BTN1, OnBNClicked1)
	ON_BN_CLICKED(IDC_SHORTCUT_BTN2, OnBNClicked2)
	//}}AFX_MSG_MAP
	//ON_COMMAND_RANGE(IDC_SHORTCUT_BTN2,IDC_SHORTCUT_BTN8,OnBNClicked)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CIMShortcutTool message handlers

void CIMShortcutTool::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rc;
	GetClientRect(&rc);

	dc.FillSolidRect(rc,m_pSkin->ShortCutBkColor );

}

int CIMShortcutTool::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pSkin = &(((CCNIcqApp *)AfxGetApp())->m_IMSkin);

	m_ILIcon = &m_pSkin->m_pILMainIcon;

	m_pBtnIWarnt->Create("我想...",WS_CHILD | WS_VISIBLE,
		CRect(0,0,0,0),this,IDC_SHORTCUT_BTN1);

	AddButton("添加联系人",IDC_SHORTCUT_BTN3,6);
	AddButton("发送消息",IDC_SHORTCUT_BTN2,5);
	AddButton("添加组",IDC_SHORTCUT_BTN4,8);
	AddButton("其他",IDC_SHORTCUT_BTN5);

	m_pBtnIWarnt->DrawBorder(FALSE);

	if( m_ILIcon )
	{
		HBITMAP hBmp;
		hBmp = m_pSkin->GetImage(*m_ILIcon,3);
		m_pBtnIWarnt->SetBitmaps(hBmp,RGB(255,0,0));
	}

	//我想...栏颜色
	m_pBtnIWarnt->SetColor(CNButton::BTNST_COLOR_FG_OUT,m_pSkin->ShortCutIWantFocusClr);
	m_pBtnIWarnt->SetColor(CNButton::BTNST_COLOR_FG_IN,m_pSkin->ShortCutIWantTxtClr);
	m_pBtnIWarnt->SetColor(CNButton::BTNST_COLOR_FG_FOCUS,m_pSkin->ShortCutIWantFocusClr);
	m_pBtnIWarnt->SetColor(CNButton::BTNST_COLOR_BK_IN,m_pSkin->MaxMinBarColor);
	m_pBtnIWarnt->SetColor(CNButton::BTNST_COLOR_BK_OUT,m_pSkin->MaxMinBarColor);
	m_pBtnIWarnt->SetColor(CNButton::BTNST_COLOR_BK_FOCUS,m_pSkin->MaxMinBarColor);
	
	return 0;
}

void CIMShortcutTool::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_pBtnIWarnt->MoveWindow(0,0,cx,BUTTON_HEIGHT);

	if( !m_bHide )
	for(int i = 0; i < m_iButtonCount;i++)
	{
		if( m_pBtn[i] )
			m_pBtn[i]->MoveWindow(0,BUTTON_HEIGHT * (i+1),cx,BUTTON_HEIGHT);
	}
}
void CIMShortcutTool::OnBNClicked1()
{
	ShowHideButton();
}
void CIMShortcutTool::OnBNClicked2()
{
	CIMChat dlgChat;

	dlgChat.DoModal();
}

LRESULT CIMShortcutTool::OnBNClicked(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add extra validation here

	int idButton = (int) LOWORD(wParam);    

	return 0;
}

BOOL CIMShortcutTool::AddButton(CString Caption, int nID,int nImage)
{
	if( m_iButtonCount > MAX_BUTTON)
		return FALSE;

	CNButton *m_pNewBtn;

	m_pNewBtn = new CNButton;

	m_pNewBtn->Create(Caption,WS_CHILD | WS_VISIBLE,
		CRect(0,0,0,0),this,nID);

	m_pNewBtn->DrawBorder(FALSE);
	
	if( m_ILIcon && nImage != -1)
	{
		HBITMAP hBmp;
		hBmp = m_pSkin->GetImage(*m_ILIcon,nImage);

		m_pNewBtn->SetBitmaps(hBmp,RGB(255,0,0));
	}

	//前景
	m_pNewBtn->SetColor(CNButton::BTNST_COLOR_FG_OUT,m_pSkin->ShortCutNormalTextClr);
	m_pNewBtn->SetColor(CNButton::BTNST_COLOR_FG_IN,m_pSkin->ShortCutFocusTextClr);
	m_pNewBtn->SetColor(CNButton::BTNST_COLOR_FG_FOCUS,m_pSkin->ShortCutFocusTextClr);
	//背景
	m_pNewBtn->SetColor(CNButton::BTNST_COLOR_BK_IN,m_pSkin->ShortCutBkColor);
	m_pNewBtn->SetColor(CNButton::BTNST_COLOR_BK_OUT,m_pSkin->ShortCutBkColor);
	m_pNewBtn->SetColor(CNButton::BTNST_COLOR_BK_FOCUS,m_pSkin->ShortCutBkColor);

	m_pBtn[m_iButtonCount] = m_pNewBtn;

	m_iButtonCount ++;

	return TRUE;
}

int CIMShortcutTool::GetClientHeight()
{
	int iHeight = 0;

	if( !m_bHide )
		iHeight = BUTTON_HEIGHT * (m_iButtonCount + 1);
	else	iHeight = BUTTON_HEIGHT * 2;

	return iHeight;
}
/*
LRESULT CIMShortcutTool::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	// TODO: 处理用户自定义消息
	return 0;
}
*/

void CIMShortcutTool::ShowHideButton()
{
	m_bHide = !m_bHide;

	if( m_ILIcon )
	{
		HBITMAP hBmp;
		hBmp = m_pSkin->GetImage(*m_ILIcon,(m_bHide? 4 : 3 ));
		m_pBtnIWarnt->SetBitmaps(hBmp,RGB(255,0,0));
	}


	for(int i = 1; i < m_iButtonCount;i++)
	{
		if( m_pBtn[i] )
			m_pBtn[i]->ShowWindow(!m_bHide);
	}

	CRect rcParent;
	GetParent()->GetClientRect(&rcParent);
	
	WORD iHeight = rcParent.Height();
	WORD iWidth  = rcParent.Width();

	DWORD LParam = ((DWORD)iHeight) << 16 | iWidth;
	
	//使父窗口重新计算大小
	GetParent()->PostMessage(WM_SIZE,0,LParam);

	SendMessage(WM_CN_ITEMCLICK,0,IDC_SHORTCUT_BTN1);

}
