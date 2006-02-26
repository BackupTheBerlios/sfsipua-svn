// IMTab.cpp : implementation file
//

#include "stdafx.h"
#include "CNIcq.h"
#include "IMTab.h"
#include "CNIcq.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIMTab

CIMTab::CIMTab()
{
	m_pMainPanel = new CIMainPanel;
	m_nTabIndex = 0;
	m_nMyStatus = CN_USER_STATUS_ONLINE;
	m_nMouseOnTabNo = -1;
	m_nTabWidth = 40; //3
	m_bShowTab = TRUE;
}

CIMTab::~CIMTab()
{
	delete m_pMainPanel;
}


BEGIN_MESSAGE_MAP(CIMTab, CTabCtrl)
	//{{AFX_MSG_MAP(CIMTab)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIMTab message handlers
int CIMTab::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//取应用程序的Skin对象
	m_pSkin = &(((CCNIcqApp *)AfxGetApp())->m_IMSkin);
	
	InitGraphics();

	m_pMainPanel->Create(NULL,NULL,WS_CHILD | WS_VISIBLE,
			CRect(0,0,0,0), this,1010);
	return 0;
}

void CIMTab::InitGraphics()
{
}

void CIMTab::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	DrawAll(&dc);
}

void CIMTab::DrawAll(CDC *pDC)
{
	CDC memDC;

	memDC.CreateCompatibleDC(pDC);

	CRect rc;
	GetClientRect(rc);

	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());

	CBitmap *oldBitmap = memDC.SelectObject(&bm);

	DrawBackGroud(&memDC,rc);

	//画TAB标签
	if( m_bShowTab )
	{
		DrawTabButton(&memDC);
	}
	//memDC.FillSolidRect(CRect(rc.left+2,0,rc.right-2,4), m_pSkin->MainBk);

	memDC.FillSolidRect(CRect(m_nTabWidth, 3, rc.Width()-3, rc.Height()-3),RGB(255,255,255));
//	memDC.FillSolidRect(CRect(m_nTabWidth, rc.Height()-8, rc.Width()-3, rc.Height()-3),m_pSkin->ShortCutBkColor);

	DrawCorner(&memDC);

	//画主边框
	CPen MyPen;
	MyPen.CreatePen(PS_SOLID,5,m_pSkin->MainBorder);
	CPen *OldPen = memDC.SelectObject(&MyPen);
	memDC.MoveTo(0,0);
	memDC.LineTo(rc.right,0);
	memDC.LineTo(rc.right,rc.bottom);
	memDC.LineTo(0,rc.bottom);
	memDC.LineTo(0,0);
	memDC.SelectObject(OldPen);

	//显示
	pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBitmap);
	DeleteObject(bm);
	memDC.DeleteDC();
}

void CIMTab::DrawBackGroud(CDC *pDC, CRect &rc)
{
	pDC->FillSolidRect(rc, m_pSkin->MainBk);
}

void CIMTab::OnSize(UINT nType, int cx, int cy) 
{
	CTabCtrl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_pMainPanel->MoveWindow(CRect(m_nTabWidth, 8, cx-3, cy-8),TRUE);
}


BOOL CIMTab::DrawTabButton(CDC *pDC)
{
	int nTabVSpace;
	int nTabTop;
	int nTabLeft;
	int nTabIconTop;
	int nTabIconLeft;

	COLORREF clrMaskColor = RGB(255,0,0);
	CSize csButtonBkSize(39,69);
	CSize csButtonSize(32,32);

	nTabLeft = 4;//m_pSkin->IMTabTopEdge;
	nTabTop = -5;
	nTabVSpace = 69-m_pSkin->IMTabSpace;//46

	nTabIconLeft= nTabTop  + m_pSkin->TabIconLeft + 4;
	nTabIconTop = nTabLeft + m_pSkin->TabIconTop - 4;

	//画标签上的图象
	int Index0,Index1,Index2;	

	//计算图象索引
	Index0 = (m_nTabIndex == 0)? m_nMyStatus : ((m_nMouseOnTabNo == 0)? m_nMyStatus + 14:m_nMyStatus + 7);
	Index1 = (m_nTabIndex == 1)? 0 : ((m_nMouseOnTabNo == 1)? 2:1);
	Index2 = (m_nTabIndex == 2)? 3 : ((m_nMouseOnTabNo == 2)? 5:4);

	CBitmap& m_bmpTabBk = m_pSkin->TabBmp;		//Tab标签背景图片
	CBitmap& m_bmpTabIcon = m_pSkin->TabStatusBmp;	//Tab标签状态图标
	CBitmap& m_bmpStatusIcon = m_pSkin->MainStatusBmp;//我的状态图片

	//画Tab标签的背景
	switch(m_nTabIndex)
	{
	case 0:
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft,nTabTop + nTabVSpace * 2),m_bmpTabBk,CPoint(csButtonBkSize.cx,0),csButtonBkSize,clrMaskColor);
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft,nTabTop + nTabVSpace),m_bmpTabBk,CPoint(csButtonBkSize.cx,0),csButtonBkSize,clrMaskColor);

		//画状态图片
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft + nTabIconLeft,nTabTop + nTabIconTop + nTabVSpace *1),m_bmpTabIcon,CPoint(32*Index1,0),csButtonSize,clrMaskColor);
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft + nTabIconLeft,nTabTop + nTabIconTop + nTabVSpace *2),m_bmpTabIcon,CPoint(32*Index2,0),csButtonSize,clrMaskColor);
		//激活页最后画出
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft,nTabTop),m_bmpTabBk,CPoint(0,0),csButtonBkSize,clrMaskColor);
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft + nTabIconLeft,nTabTop + nTabIconTop + nTabVSpace *0),m_bmpStatusIcon,CPoint(32*Index0,0),csButtonSize,clrMaskColor);
		break;
	case 1:
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft,nTabTop + nTabVSpace * 2),m_bmpTabBk,CPoint(csButtonBkSize.cx,0),csButtonBkSize,clrMaskColor);
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft,nTabTop),m_bmpTabBk,CPoint(csButtonBkSize.cx,0),csButtonBkSize,clrMaskColor);
		
		//画状态图片
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft + nTabIconLeft,nTabTop + nTabIconTop + nTabVSpace *0),m_bmpStatusIcon,CPoint(32*Index0,0),csButtonSize,clrMaskColor);
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft + nTabIconLeft,nTabTop + nTabIconTop + nTabVSpace *2),m_bmpTabIcon,CPoint(32*Index2,0),csButtonSize,clrMaskColor);
		//激活页最后画出
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft,nTabTop + nTabVSpace),m_bmpTabBk,CPoint(0,0),csButtonBkSize,clrMaskColor);
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft + nTabIconLeft,nTabTop + nTabIconTop + nTabVSpace *1),m_bmpTabIcon,CPoint(32*Index1,0),csButtonSize,clrMaskColor);
		break;
	case 2:
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft,nTabTop + nTabVSpace),m_bmpTabBk,CPoint(csButtonBkSize.cx,0),csButtonBkSize,clrMaskColor);
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft,nTabTop),m_bmpTabBk,CPoint(csButtonBkSize.cx,0),csButtonBkSize,clrMaskColor);

		//画状态图片
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft + nTabIconLeft,nTabTop + nTabIconTop + nTabVSpace *0),m_bmpStatusIcon,CPoint(32*Index0,0),csButtonSize,clrMaskColor);
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft + nTabIconLeft,nTabTop + nTabIconTop + nTabVSpace *1),m_bmpTabIcon,CPoint(32*Index1,0),csButtonSize,clrMaskColor);
		//激活页最后画出
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft,nTabTop + nTabVSpace * 2),m_bmpTabBk,CPoint(0,0),csButtonBkSize,clrMaskColor);
		m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft + nTabIconLeft,nTabTop + nTabIconTop + nTabVSpace *2),m_bmpTabIcon,CPoint(32*Index2,0),csButtonSize,clrMaskColor);

		break;
	}
/*
	//画状态图片,最后输出效果不太好
	m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft + nTabIconLeft,nTabTop + nTabIconTop + nTabVSpace *0),m_bmpStatusIcon,CPoint(32*Index0,0),csButtonSize,clrMaskColor);
	m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft + nTabIconLeft,nTabTop + nTabIconTop + nTabVSpace *1),m_bmpTabIcon,CPoint(32*Index1,0),csButtonSize,clrMaskColor);
	m_pSkin->DrawTransparent(pDC,CPoint(nTabLeft + nTabIconLeft,nTabTop + nTabIconTop + nTabVSpace *2),m_bmpTabIcon,CPoint(32*Index2,0),csButtonSize,clrMaskColor);
*/	
	return TRUE;
}
void CIMTab::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd*			wndUnderMouse = NULL;
	TRACKMOUSEEVENT		csTME;
	int			CurOnTabNo = -1;

	CTabCtrl::OnMouseMove(nFlags, point);

	if( !m_bShowTab ) 
		return;

	// If the mouse enter the button with the left button pressed then do nothing
	if( PtInRect(CRect(4,4,40,48),point)) {
		CurOnTabNo = 0;
	}
	else if( PtInRect(CRect(4,47,40,48*2),point)) {
		CurOnTabNo = 1;
	}
	else if( PtInRect(CRect(4,91,40,48*3),point)) {
		CurOnTabNo = 2;
	}
	else	{
		m_nMouseOnTabNo = -1;
		UpdateTab();
		return;
	}

	ClientToScreen(&point);
	wndUnderMouse = WindowFromPoint(point);

	if (wndUnderMouse && wndUnderMouse->m_hWnd == m_hWnd )
	{
		if (CurOnTabNo != m_nMouseOnTabNo)
		{
			m_nMouseOnTabNo = CurOnTabNo;

			UpdateTab();

			csTME.cbSize = sizeof(csTME);
			csTME.dwFlags = TME_LEAVE;
			csTME.hwndTrack = m_hWnd;
			::_TrackMouseEvent(&csTME);
		}
	}
}

void CIMTab::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CTabCtrl::OnLButtonDown(nFlags, point);

	if( !m_bShowTab ) 
		return;

	if( PtInRect(CRect(4,4,40,48),point))
	{
		m_nTabIndex = 0;
	}
	else if( PtInRect(CRect(4,47,40,48*2),point))
	{
		m_nTabIndex = 1;
	}
	else if( PtInRect(CRect(4,91,40,48*3),point))
	{
		m_nTabIndex = 2;
	}
	UpdateTab();
	
	PageChanged(m_nTabIndex);

}

LRESULT CIMTab::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if( m_nMouseOnTabNo != -1)
	{
		m_nMouseOnTabNo = -1;
		UpdateTab();
	}

	return 0;
} // End of OnMouseLeave

void CIMTab::UpdateTab()
{
	CRect rc;
	GetClientRect(&rc);
	InvalidateRect(CRect(rc.left,rc.top,rc.left + m_nTabWidth,rc.bottom));
}


void CIMTab::DrawCorner(CDC *pDC)
{
	CRect rc;
	GetClientRect(&rc);
	COLORREF clrMaskColor = RGB(255,0,0);
	CSize czImgSize(8,8);
	
	CBitmap& m_pCornerBmp = m_pSkin->CornerBmp;

	pDC->FillSolidRect(CRect(m_nTabWidth, rc.Height()-8, rc.Width()-3, rc.Height()-3),m_pSkin->ShortCutBkColor);

	//显示标签页时不显示左上角的图片
	if(!m_bShowTab)
		m_pSkin->DrawTransparent(pDC,CPoint(0,0),m_pCornerBmp,CPoint(czImgSize.cx * 0,0),czImgSize,clrMaskColor); //左上角

	m_pSkin->DrawTransparent(pDC,CPoint(rc.right-8,0),m_pCornerBmp,CPoint(czImgSize.cx*1,0),czImgSize,clrMaskColor); //右上角
	m_pSkin->DrawTransparent(pDC,CPoint(rc.right-9,rc.bottom-8),m_pCornerBmp,CPoint(czImgSize.cx*3,0),czImgSize,clrMaskColor); //右下角
	m_pSkin->DrawTransparent(pDC,CPoint(m_nTabWidth-3,rc.bottom-8),m_pCornerBmp,CPoint(czImgSize.cx*2,0),czImgSize,clrMaskColor); //左下角
}

void CIMTab::PageChanged(int NewPage)
{
	m_pMainPanel->ShowWindow((NewPage==0));
}

void CIMTab::SetShowTab(BOOL Show)
{
	m_bShowTab = Show;

	m_nTabWidth =(m_bShowTab)? MAX_TAB_WIDTH : MIN_TAB_WIDTH;
}

void CIMTab::SetActivePage(int NewPage)
{
	if( NewPage < 0 || NewPage > MAX_TAB)
		return;
	m_nTabIndex = NewPage;

	UpdateTab();
	
	PageChanged(m_nTabIndex);
}
