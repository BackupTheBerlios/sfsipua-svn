// CMSNButton.cpp : implementation file
//

// this class is for ONE LOUSEY BUTTON. GRRRRRR...
//yep.. you got it... the SEND button.

#include "stdafx.h"
#include "MSNButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RGB_BUTTON_WHITE    (GetSysColor(COLOR_BTNHIGHLIGHT))

#define COL_OVER 	GetColor(COL_BTNOVER)
#define COL_LIGHT 	(m_bDisabled ? GetColor(COL_DISABLED) : GetColor(COL_BTNBACK))
#define COL_ACTIVE 	GetColor(COL_BTNACTIVE)
#define COL_EDGE 	GetColor(COL_LINEFRAMES)
#define COL_BLACK 	RGB(0, 0, 0)

/////////////////////////////////////////////////////////////////////////////
// CMSNButton
COLORREF GetColor(int nIndex)
{
	COLORREF crColor;

	switch(nIndex)
	{
	case COL_DISABLED:	crColor = RGB(247,247,231);break;
	case COL_LIGHTITEMS:	crColor = 16244694;break;
	case COL_LINEFRAMES:	crColor = 11880704;break;
	case COL_NOTIFYTEXT:	crColor = 15715253;break;
	case COL_NORMALTEXT:	crColor = RGB(0,0,0);break;
	case COL_DISABLEDTEXT:	crColor = RGB(127,127,127);break;
	case COL_BTNOVER:	crColor = 2927840;break;
	case COL_BTNACTIVE:	crColor = 16711680;break;
	case COL_BTNBACK:	crColor = 15793151;break;
	default: crColor=RGB(255,255,255);break;
	}
	return crColor;
}


CMSNButton::CMSNButton()
{
	m_bDrawFocus = true;
	m_bMouseCaptured = false;
	m_bLButtonDown = false;
	m_bHasFocus = false;
	m_bDisabled = false;
	m_bClickedIn = false;
	m_bKeyDown = false;
	m_TextAlign = AlignCenter;
	m_bRaised = false;
	m_crCornerColor = GetSysColor(COLOR_BTNFACE);
}

CMSNButton::~CMSNButton()
{

}


BEGIN_MESSAGE_MAP(CMSNButton, CButton)
	//{{AFX_MSG_MAP(CMSNButton)
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ENABLE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSNButton message handlers

void CMSNButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	CButton::OnMouseMove(nFlags, point);
	if (m_bKeyDown) return;
	CRect rc;
	GetClientRect(&rc);
	if (!rc.PtInRect(point))
	{
		if (!m_bMouseCaptured) return;
		OnMouseLeave(nFlags, point); 
		m_bMouseCaptured = false;
		if (!m_bClickedIn) 
		{
			ReleaseCapture();
		}
	}
	else
	{
		if (m_bMouseCaptured) return;
		SetCapture();
		m_bMouseCaptured = true;
		OnMouseEnter(nFlags, point);
	} 
}

void CMSNButton::OnKillFocus(CWnd* pNewWnd) 
{
	if (m_bKeyDown) 
		return;
	m_bHasFocus = false;
	if (!m_bMouseCaptured) m_bRaised = false;
	m_bMouseCaptured = false;
	CButton::OnKillFocus(pNewWnd);
	Invalidate();
	UpdateWindow();
}

void CMSNButton::OnSetFocus(CWnd* pOldWnd) 
{
	if (m_bKeyDown) 
		return;
	m_bHasFocus = true;
	
	if(!m_bDrawFocus) m_bHasFocus = false;

	CButton::OnSetFocus(pOldWnd);
	Invalidate();
	UpdateWindow();
}

void CMSNButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	int	 iSaveDC;
	CDC* pDC;
	CRect rc;
	CString	strTitle;
	UINT nFormat;
	UINT nFlags;
	CBitmap* pBitmap = NULL;
	
	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	VERIFY(pDC);
	rc.CopyRect(&lpDrawItemStruct->rcItem);
	GetWindowText(strTitle);
	nFormat = DT_SINGLELINE;
	iSaveDC = pDC->SaveDC();
	
	switch (m_TextAlign)
	{
		case AlignAbove: nFormat |= DT_CENTER | DT_TOP; break;	
		case AlignBelow: nFormat |= DT_CENTER | DT_BOTTOM; break;
		case AlignLeft:
		case AlignRight: nFormat |= DT_LEFT | DT_VCENTER; break;
		case AlignCenter: nFormat |= DT_CENTER | DT_VCENTER; break;
		default: ASSERT(false);
	}
	
	pDC->SetBkMode(TRANSPARENT);
	if (!m_bDisabled)
	{
		if (!m_bLButtonDown)
		{
			pDC->FillSolidRect(1, rc.bottom - 3, rc.right - 2, 1, m_bRaised ? COL_OVER : COL_ACTIVE);
			pDC->FillSolidRect(2, rc.bottom - 2, rc.right - 4, 1, m_bRaised ? COL_OVER : COL_ACTIVE);
		}
		else
		{
			pDC->FillSolidRect(1, rc.bottom - 3, rc.right - 2, 1, COL_LIGHT);
			pDC->FillSolidRect(2, rc.bottom - 2, rc.right - 4, 1, COL_LIGHT);
		}
	}
	else
	{
		pDC->FillSolidRect(1, rc.bottom - 3, rc.right - 2, 1, COL_LIGHT);
		pDC->FillSolidRect(2, rc.bottom - 2, rc.right - 4, 1, COL_LIGHT);
	}

	pDC->FillSolidRect(2, rc.bottom - 1, rc.right - 4, 1, COL_EDGE);
	pDC->FillSolidRect(0, 2, 1, rc.bottom - 4, COL_EDGE);
	pDC->FillSolidRect(2, 0, rc.right - 4, 1, COL_EDGE);
	pDC->FillSolidRect(rc.right - 1, 2, 1, rc.bottom - 4, COL_EDGE);
	pDC->FillSolidRect(0, 1, 2, 1, COL_EDGE);
	pDC->FillSolidRect(1, 0, 1, 2, COL_EDGE);
	pDC->FillSolidRect(0, rc.bottom - 2, 2, 1, COL_EDGE);
	pDC->FillSolidRect(1, rc.bottom - 2, 1, 2, COL_EDGE);
	pDC->FillSolidRect(rc.right - 2, 0, 1, 2, COL_EDGE);
	pDC->FillSolidRect(rc.right - 2, 1, 2, 1, COL_EDGE);
	pDC->FillSolidRect(rc.right - 2, rc.bottom - 2, 2, 1, COL_EDGE);
	pDC->FillSolidRect(rc.right - 2, rc.bottom - 2, 1, 2, COL_EDGE);

	DrawDot(pDC, 0, 0, m_crCornerColor);
	DrawDot(pDC, 0, rc.bottom - 1, m_crCornerColor);
	DrawDot(pDC, rc.right - 1, rc.bottom - 1, m_crCornerColor);
	DrawDot(pDC, rc.right - 1, 0, m_crCornerColor);

	if (!m_bDisabled)
	{
		DrawDot(pDC, 2, 1, COL_LIGHT);
		DrawDot(pDC, 1, 2, COL_LIGHT);
		DrawDot(pDC, rc.right - 3, 1, COL_LIGHT);
		DrawDot(pDC, rc.right - 2, 2, COL_LIGHT);
	}

	pDC->FillSolidRect(1, 3, rc.right - 2, rc.bottom - 6, COL_LIGHT);
	if (!m_bDisabled)
	{
		pDC->FillSolidRect(3, 1, rc.right - 6, 1, COL_LIGHT);
		pDC->FillSolidRect(2, 2, rc.right - 4, 1, COL_LIGHT);
	}
	else
	{
		pDC->FillSolidRect(2, 1, rc.right - 4, 1, COL_LIGHT);
		pDC->FillSolidRect(1, 2, rc.right - 2, 1, COL_LIGHT);
	}
	if (m_bHasFocus)
	{
		DrawDottedLine(pDC, 1, 2, rc.bottom - 4, true, COL_BLACK);
		DrawDottedLine(pDC, 2, 1, rc.right - 4, false, COL_BLACK);
		DrawDottedLine(pDC, 2, rc.bottom - 2, rc.right - 4, false, COL_BLACK);
		DrawDottedLine(pDC, rc.right - 2, 2, rc.bottom - 4, true, COL_BLACK);
	}
	
	rc.InflateRect(-5, -5);
	
	if (m_bHasFocus)
	{
		pBitmap = &m_bitmapFocus;
		if (!pBitmap->m_hObject) 
			pBitmap = &m_bitmap;
	}
	else
	{
		pBitmap = &m_bitmap;
	}
	
	if (m_bRaised)
	{
		pBitmap = &m_bitmapFocus;
		if (!pBitmap->m_hObject) pBitmap = &m_bitmap;
	} 
	
	if (m_bDisabled = (::GetWindowLong(m_hWnd, GWL_STYLE) & WS_DISABLED) ? true : false)
	{
		pBitmap = &m_bitmapDisabled;
	}
	else if (m_bLButtonDown) rc.OffsetRect(1, 1);
	
	CRect rcText(rc);

	if (pBitmap->m_hObject)
	{
		CRect rcBitmap(rc);
		BITMAP	bmpInfo;			
		CSize	size;

		switch (m_TextAlign)
		{
			case AlignLeft:
			{
				size = pDC->GetTextExtent(strTitle);
				rcBitmap.OffsetRect(size.cx + 5, 0);
				nFlags = DB_VCENTER;
				break;
			}
			case AlignAbove:
			{
				size = pDC->GetTextExtent(strTitle);
				rcBitmap.OffsetRect(0,size.cy + 5);
				nFlags = DB_HCENTER;
				break;
			}
			case AlignRight:
			{
				pBitmap->GetBitmap(&bmpInfo);	
				rcText.OffsetRect(bmpInfo.bmWidth + 5, 0);
				nFlags = DB_VCENTER;
				break;
			}
			case AlignBelow:
			{
				nFlags = DB_HCENTER;
				break;
			}
			default: ASSERT(false); break;
		}
		DrawBitmap(pDC, rcBitmap, nFlags, pBitmap);
	}
	
	if (m_bDisabled)
	{
		rcText.OffsetRect(1, 1);
		pDC->SetTextColor(RGB_BUTTON_WHITE);
		pDC->DrawText(strTitle, rcText, nFormat);
		rcText.OffsetRect(-1, -1);
		pDC->SetTextColor(GetColor(COL_DISABLEDTEXT));
		pDC->DrawText(strTitle, rcText, nFormat);
	} 
	else
	{
		pDC->SetTextColor(GetColor(COL_NORMALTEXT));
		pDC->DrawText(strTitle, rcText, nFormat);
	}

	pDC->RestoreDC(iSaveDC);
}

void CMSNButton::OnMouseEnter(UINT nFlags, CPoint point)
{
	if (m_bClickedIn) m_bLButtonDown = true;
	m_bRaised = true;
	Invalidate();
	UpdateWindow();
}

void CMSNButton::OnMouseLeave(UINT nFlags, CPoint point)
{
	if (m_bClickedIn) m_bLButtonDown = false;
	m_bRaised = false;
	Invalidate();
	UpdateWindow();
}

void CMSNButton::DrawDot(CDC *pDC, int x, int y, COLORREF col)
{
	pDC->FillSolidRect(x, y, 1, 1, col);
}

void CMSNButton::DrawDottedLine(CDC *pDC, int x, int y, int len, bool vertical, COLORREF col)
{
	int pos = 0;
	while (pos < len)
	{
		pDC->FillSolidRect(x + (vertical ? 0 : pos), y + (vertical ? pos : 0), 1, 1, col);
		pos += 2;
	}
}

void CMSNButton::SetCornerColor(COLORREF col)
{
	m_crCornerColor = col;
	Invalidate();
	UpdateWindow();
}

void CMSNButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bKeyDown) 
		return;
	
	m_bLButtonDown = true;
	m_bClickedIn = true;
	m_bRaised = false;
	if (GetFocus() != this)
	{
		SetFocus();
		return;
	}
	CButton::OnLButtonDown(nFlags, point);
	Invalidate();
	UpdateWindow();
}


void CMSNButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bKeyDown) 
		return;

	if (!m_bClickedIn) 
		return;

	if (!m_bMouseCaptured)
	{
		ReleaseCapture();
		m_bClickedIn = false;
		m_bRaised = false;
		return;
	}

	m_bClickedIn = false;

	m_bLButtonDown = false;
	m_bRaised = true;

	if (GetFocus() != this)
	SetFocus();

	else
	{
		Invalidate();
		UpdateWindow();
	}

	GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM) m_hWnd);
}

int CMSNButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_bDisabled = (lpCreateStruct->style & WS_DISABLED) ? true : false;
	return 0;
}

void CMSNButton::OnEnable(bool bEnable) 
{
	m_bDisabled =! bEnable;
	
	if (!bEnable)
	{
		m_bMouseCaptured = false;
		m_bRaised = false;
		m_bKeyDown = false;
		m_bLButtonDown = false;
		m_bClickedIn = false;
	}

	CButton::OnEnable(bEnable);
}

bool CMSNButton::LoadBitmaps(UINT nBitmap, UINT nBitmapFocus, UINT nBitmapDisabled)
{
	return LoadBitmaps(MAKEINTRESOURCE(nBitmap),
						MAKEINTRESOURCE(nBitmapFocus),
						MAKEINTRESOURCE(nBitmapDisabled));
}

CMSNButton::TextAlign CMSNButton::GetTextAlignment() const
{
	return m_TextAlign;
}

void CMSNButton::SetTextAlignment(TextAlign nTextAlign)
{
	m_TextAlign = nTextAlign;
}

void CMSNButton::DrawBitmap(CDC * pDC, CRect rc, UINT nFlags, CBitmap *pBitmap)
{
	CDC memDC;
	CBitmap* pOld = NULL;
	memDC.CreateCompatibleDC(pDC);
	BITMAP bmpInfo;
	int Width;
	int Height;
	int xSrc = 0;
	int ySrc = 0;
	int xDesired;
	int yDesired;

	ASSERT(pBitmap->m_hObject != NULL);
	pBitmap->GetBitmap(&bmpInfo);
	
	pOld = memDC.SelectObject((CBitmap*) pBitmap);
	if (pOld == NULL) return;
	
	Width = (bmpInfo.bmWidth - rc.Width()) / 2;
	Height = (bmpInfo.bmHeight - rc.Height()) / 2;
	
	if ((nFlags & DB_HCENTER))
	{
		if (Width > 0)
		{
			xDesired = rc.left;
			xSrc = abs(Width);
		}
		else xDesired = rc.left+ abs(Width);
	}
		else xDesired = rc.left;
	
	if ((nFlags & DB_VCENTER))
	{
		if (Height > 0)
		{
			yDesired = rc.top;
			ySrc = abs(Height);
		}
		else yDesired = rc.top + abs(Height);
	} else
		yDesired = rc.top;
	
	pDC->BitBlt(xDesired, yDesired, rc.Width(), rc.Height(), &memDC, xSrc, ySrc, SRCCOPY);
	
	memDC.SelectObject(pOld);	
}

bool CMSNButton::LoadBitmaps(LPCSTR lpszBitmap, LPCSTR lpszBitmapFocus, LPCSTR lpszBitmapDisabled)
{
	m_bitmap.DeleteObject();
	m_bitmapFocus.DeleteObject();
	m_bitmapDisabled.DeleteObject();
	m_bitmapRaised.DeleteObject();
	
	m_bitmap.LoadBitmap(lpszBitmap);

	BOOL bAllLoaded = true;
	if (lpszBitmapFocus)
	{
		if (!m_bitmapFocus.LoadBitmap(lpszBitmapFocus))
			return bAllLoaded = false;
	}
	
	if (lpszBitmapDisabled != NULL)
	{
		if (!m_bitmapDisabled.LoadBitmap(lpszBitmapDisabled))
			return bAllLoaded = false;
	}

	return bAllLoaded ? true : false;
}

void CMSNButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	if (nChar == 32)
	{
		if (m_bKeyDown) return;

		m_bKeyDown = true;
		m_bLButtonDown = true;
		m_bRaised = false;
		if (GetFocus() != this)
		{
			SetFocus();
			return;
		}
		Invalidate();
		UpdateWindow();
	}
   	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMSNButton::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	if (nChar == 32)
	{
		if (!m_bKeyDown) return;

		m_bKeyDown = false;
		m_bLButtonDown = false;
		m_bRaised = true;
		if (GetFocus() != this)
			SetFocus();
		else
		{
			Invalidate();
			UpdateWindow();
		}
	}
	CButton::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMSNButton::DrawFocus(BOOL bDrawFocus)
{
	m_bDrawFocus = bDrawFocus;
}
