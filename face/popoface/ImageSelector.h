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

#if !defined(AFX_IMAGESELECTOR_H__19DA647E_9A74_4184_9D6A_1F181EF616FA__INCLUDED_)
#define AFX_IMAGESELECTOR_H__19DA647E_9A74_4184_9D6A_1F181EF616FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageSelector.h : header file
//

#define ID_IMAGE0	10000

/////////////////////////////////////////////////////////////////////////////
// ImageSelector window

class ImageSelector : public CWnd
{
// Construction
public:
	ImageSelector(CImageList *il, const char *tips[], int x, int y, int cols, CWnd *parent);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ImageSelector)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ImageSelector();

private:
	void drawButton(CDC *pDC, int row, int col, BOOL erase);

	CImageList *imageList;
	CToolTipCtrl toolTip;
	int nrColumns;
	CSize buttonSize;
	int lastSelectRow, lastSelectCol;

	// Generated message map functions
protected:
	//{{AFX_MSG(ImageSelector)
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESELECTOR_H__19DA647E_9A74_4184_9D6A_1F181EF616FA__INCLUDED_)
