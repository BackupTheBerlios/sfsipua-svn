#if !defined(AFX_IMAINHEADER_H__DC6D3941_144A_11D7_90A4_006008267A03__INCLUDED_)
#define AFX_IMAINHEADER_H__DC6D3941_144A_11D7_90A4_006008267A03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IMainHeader.h : header file
//
#include "Skin.h"
#include "CNButton.h"

/////////////////////////////////////////////////////////////////////////////
// CIMainHeader window

class CIMainHeader : public CWnd
{
// Construction
public:
	CIMainHeader();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIMainHeader)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIMainHeader();

	// Generated message map functions
protected:
	CSkin *m_pSkin;
	CNButton *m_btnEmail;

	virtual void DrawHeader(CDC *pDC, CRect rc);
	virtual void DragWndLine(CDC *pDC,int x,int Width,int Top);
	virtual void ShowBitmap(CDC *pDC,int x,int y,CBitmap &m_bitmap);
	virtual void DrawLogo(CDC *pDC, CRect &rc);

	//{{AFX_MSG(CIMainHeader)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont NormalFont;
	CFont BoldFont;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAINHEADER_H__DC6D3941_144A_11D7_90A4_006008267A03__INCLUDED_)
