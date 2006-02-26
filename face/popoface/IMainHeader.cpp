// IMainHeader.cpp : implementation file
//

#include "stdafx.h"
#include "CNIcq.h"
#include "IMainHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIMainHeader

CIMainHeader::CIMainHeader()
{
	m_btnEmail =new CNButton;

	VERIFY(NormalFont.CreateFont(
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

	VERIFY(BoldFont.CreateFont(
		12,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,                   // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		FALSE,                     // cStrikeOut
		DEFAULT_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("宋体")));              // lpszFacename
}

CIMainHeader::~CIMainHeader()
{
	delete m_btnEmail;

	NormalFont.DeleteObject();
	BoldFont.DeleteObject();
}


BEGIN_MESSAGE_MAP(CIMainHeader, CWnd)
	//{{AFX_MSG_MAP(CIMainHeader)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CIMainHeader message handlers

int CIMainHeader::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_pSkin = &(((CCNIcqApp *)AfxGetApp())->m_IMSkin);

	CImageList &m_ILIcon  = m_pSkin->m_pILMainIcon;

	m_btnEmail->Create("你的邮箱中没有邮件",WS_CHILD | WS_VISIBLE,
		CRect(0,0,0,0),this,IDC_SHORTCUT_BTN1);

	m_btnEmail->DrawBorder(FALSE);
	m_btnEmail->SetURL("mailto:cicn@163.com");

	HBITMAP hBmp;
	hBmp = m_pSkin->GetImage(m_ILIcon,9);
	m_btnEmail->SetBitmaps(hBmp,RGB(255,0,0));


	//m_btnEmail->SetCursor(LoadCursor(NULL,(LPCTSTR)IDC_HAND));

	//我想...栏颜色
	m_btnEmail->SetColor(CNButton::BTNST_COLOR_FG_OUT,RGB(0,0,255));
	m_btnEmail->SetColor(CNButton::BTNST_COLOR_FG_IN,RGB(255,0,0));
	m_btnEmail->SetColor(CNButton::BTNST_COLOR_FG_FOCUS,RGB(0,0,255));
	m_btnEmail->SetColor(CNButton::BTNST_COLOR_BK_IN,RGB(255,255,255));
	m_btnEmail->SetColor(CNButton::BTNST_COLOR_BK_OUT,RGB(255,255,255));
	m_btnEmail->SetColor(CNButton::BTNST_COLOR_BK_FOCUS,RGB(255,255,255));

	return 0;
}

void CIMainHeader::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_btnEmail->MoveWindow(2,cy-18,cx-5,18);
}

void CIMainHeader::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CDC memDC;

	memDC.CreateCompatibleDC(&dc);

	CRect rc;
	GetClientRect(rc);

	CBitmap bm;
	bm.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());

	CBitmap *oldBitmap = memDC.SelectObject(&bm);

	memDC.FillSolidRect(rc,RGB(255,255,255) );

	DrawHeader(&memDC,CRect(0,0,rc.right,rc.bottom));

	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(oldBitmap);
	DeleteObject(bm);
	memDC.DeleteDC();

}
void CIMainHeader::DrawHeader(CDC *pDC, CRect rc)
{
	CFont *OldFont;

	OldFont = pDC->SelectObject(&NormalFont);

	COLORREF clrOld = pDC->SetTextColor(RGB(127,127,127));

	int nOldMode = pDC->SetBkMode(TRANSPARENT);
	
	pDC->TextOut(rc.left + 25, rc.top + 5,_T("我的状态:"));

	pDC->SetTextColor(clrOld);
	pDC->SelectObject(&BoldFont);

	pDC->TextOut(rc.left + 25,rc.top + 20,_T("cicn(在线)"));

	pDC->SetBkMode(nOldMode);

	pDC->SelectObject(OldFont);

	//**************************画小图标
	CBitmap bmpIcon;
	bmpIcon.Attach(m_pSkin->GetImage(m_pSkin->m_pILMainIcon,0));

	m_pSkin->DrawTransparent(pDC,CPoint(rc.left+5,rc.top+18),bmpIcon,CPoint(0,0),CSize(16,16),RGB(255,0,0));

	DeleteObject(bmpIcon.Detach());
	//**************************

	DrawLogo(pDC,CRect(rc.right - 92,rc.top + 5,88,30));
	
	DragWndLine(pDC,rc.left+5,rc.right,rc.bottom - 22);
	
}

void CIMainHeader::DragWndLine(CDC *pDC, int x, int Width, int Top)
{
	CPen NewPen;
	CPen *OldPen;
	int i;

	for(i = 0; i < 3; i++)
	{
		NewPen.CreatePen(PS_SOLID,1,m_pSkin->DragWndFirstLine[i]);
		OldPen = pDC->SelectObject(&NewPen);
		pDC->MoveTo(x + Width-25,Top + i);
		pDC->LineTo(x + Width-3,Top + i);
		pDC->SelectObject(OldPen);
		NewPen.DeleteObject();
	}

	for(i = 0; i < 3; i++)
	{
		NewPen.CreatePen(PS_SOLID,1,m_pSkin->DragWndSecLine[i]);
		OldPen = pDC->SelectObject(&NewPen);
		pDC->MoveTo(x + Width-50,Top + i);
		pDC->LineTo(x + Width-25,Top + i);
		pDC->SelectObject(OldPen);
		NewPen.DeleteObject();
	}
	for(i = 0; i < 3; i++)
	{
		NewPen.CreatePen(PS_SOLID,1,m_pSkin->DragWndThrLine[i]);
		OldPen = pDC->SelectObject(&NewPen);
		pDC->MoveTo(x + Width-75,Top + i);
		pDC->LineTo(x + Width-50,Top + i);
		pDC->SelectObject(OldPen);
		NewPen.DeleteObject();
	}
	for(i = 0; i < 3; i++)
	{
		NewPen.CreatePen(PS_SOLID,1,m_pSkin->DragWndFourLine[i]);
		OldPen = pDC->SelectObject(&NewPen);
		pDC->MoveTo(x,Top + i);
		pDC->LineTo(x + Width-75,Top + i);
		pDC->SelectObject(OldPen);
		NewPen.DeleteObject();
	}
}

void CIMainHeader::DrawLogo(CDC *pDC, CRect &rc)
{
	ShowBitmap(pDC,rc.left,rc.top,m_pSkin->LogoBmp);
}

void CIMainHeader::ShowBitmap(CDC *pDC, int x, int y, CBitmap &m_bitmap)
{
	CDC MemDc;

	MemDc.CreateCompatibleDC(pDC);
	CBitmap *OldBmp = MemDc.SelectObject(&m_bitmap);

	BITMAP bm;
	m_bitmap.GetBitmap( &bm );
	
	pDC->BitBlt(x, y,
		x + bm.bmWidth,y + bm.bmHeight,
		&MemDc, 
		0, 0, 
		SRCCOPY);
	MemDc.SelectObject(OldBmp);
	MemDc.DeleteDC();
}

