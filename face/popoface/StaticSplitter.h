#if !defined(AFX_STATICSPLITTER_H__617A5176_CAAA_424C_9511_9A747F765407__INCLUDED_)
#define AFX_STATICSPLITTER_H__617A5176_CAAA_424C_9511_9A747F765407__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticSplitter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticSplitter window

class CStaticSplitter : public CStatic
{
// Construction
public:
	CStaticSplitter();

// Attributes
public:

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticSplitter)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetBkColor(COLORREF crColor);
	virtual ~CStaticSplitter();

private:
	COLORREF m_crBkColor;
	HCURSOR m_SizeArrow;
	void OnMouseEnter(UINT nFlags, CPoint point);
	void OnMouseLeave(UINT nFlags, CPoint point);
	int m_InitialPos;
	bool m_LButtonDown;
	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticSplitter)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICSPLITTER_H__617A5176_CAAA_424C_9511_9A747F765407__INCLUDED_)
