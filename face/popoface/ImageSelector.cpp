/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright            : (C) 2002 by Zhang Yong                         *
 *   email                : z-yong163@163.com                              *
 ***************************************************************************/

// ImageSelector.cpp : implementation file
//

#include "stdafx.h"
#include "ImageSelector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_TOOLTIP		1000

#define BUTTON_SIZE		32
#define IMAGE_OFFSET		3

/////////////////////////////////////////////////////////////////////////////
// ImageSelector

ImageSelector::ImageSelector(CImageList *il, const char *tips[], int x, int y, int cols, CWnd *parent)
{
	imageList = il;
	nrColumns = cols;

	lastSelectRow = lastSelectCol = -1;

	int n = imageList->GetImageCount();

	IMAGEINFO ii;
	imageList->GetImageInfo(0, &ii);
	CRect rc(ii.rcImage);
	buttonSize.cx = rc.Width() + IMAGE_OFFSET * 2;
	buttonSize.cy = rc.Height() + IMAGE_OFFSET * 2;

	LPCTSTR className = AfxRegisterWndClass(
		CS_DBLCLKS,
		AfxGetApp()->LoadCursor(IDC_ARROW),
		CreateSolidBrush(GetSysColor(COLOR_BTNFACE)));

	CreateEx(
		0,
		className,
		NULL,
		WS_VISIBLE | WS_CHILD | WS_POPUP | WS_BORDER,
		x,
		y,
		(n < cols ? n : cols) * buttonSize.cx,
		((n + 1) / cols) * buttonSize.cy,
		*parent,
		NULL);

	toolTip.Create(this, 0);
	toolTip.SetTipTextColor(RGB(0, 128, 128));

	for (int i = 0; i < n; ++i) {
		rc.left = (i % cols) * buttonSize.cx;
		rc.top = (i / cols) * buttonSize.cy;
		rc.right = rc.left + buttonSize.cx;
		rc.bottom = rc.top + buttonSize.cy;
		toolTip.AddTool(this, tips[i], rc, ID_TOOLTIP + i);
	}

	SetOwner(parent);
}

ImageSelector::~ImageSelector()
{
}

void ImageSelector::drawButton(CDC *pDC, int row, int col, BOOL erase)
{
	int x = col * buttonSize.cx;
	int y = row * buttonSize.cy;

	COLORREF lightColor, shadowColor;

	if (erase)
		lightColor = shadowColor = GetSysColor(COLOR_BTNFACE);
	else {
		lightColor = GetSysColor(COLOR_BTNHILIGHT);
		shadowColor = GetSysColor(COLOR_BTNSHADOW);
	}

	pDC->Draw3dRect(x, y, buttonSize.cx, buttonSize.cy, lightColor, shadowColor);
}

BEGIN_MESSAGE_MAP(ImageSelector, CWnd)
	//{{AFX_MSG_MAP(ImageSelector)
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ImageSelector message handlers

void ImageSelector::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	int n = imageList->GetImageCount();
	for (int i = 0; i < n; ++i) {
		int x = (i % nrColumns) * buttonSize.cx + IMAGE_OFFSET;
		int y = (i / nrColumns) * buttonSize.cy + IMAGE_OFFSET;
		imageList->Draw(&dc, i, CPoint(x, y), ILD_TRANSPARENT);
	}
	
	// Do not call CWnd::OnPaint() for painting messages
}

void ImageSelector::PostNcDestroy() 
{
	delete this;
}

void ImageSelector::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
	
	DestroyWindow();
}

void ImageSelector::OnMouseMove(UINT nFlags, CPoint point) 
{
	int row = point.y / buttonSize.cy;
	int col = point.x / buttonSize.cx;

	if (lastSelectRow != row || lastSelectCol != col) {
		CClientDC dc(this);

		if (lastSelectRow >= 0 && lastSelectCol >= 0)
			drawButton(&dc, lastSelectRow, lastSelectCol, TRUE);
		drawButton(&dc, row, col, FALSE);

		lastSelectRow = row;
		lastSelectCol = col;
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void ImageSelector::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (lastSelectRow >= 0 && lastSelectCol >= 0) {
		int i = lastSelectRow * nrColumns + lastSelectCol;
		GetOwner()->SendMessage(WM_COMMAND, ID_IMAGE0 + i, (LPARAM) m_hWnd);
	}

	DestroyWindow();
}

BOOL ImageSelector::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->hwnd == m_hWnd)
		toolTip.RelayEvent(pMsg);
	
	return CWnd::PreTranslateMessage(pMsg);
}
