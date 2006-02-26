#if !defined(AFX_IMTREE_H__79262109_23F6_490D_8E5B_69D599DEACA0__INCLUDED_)
#define AFX_IMTREE_H__79262109_23F6_490D_8E5B_69D599DEACA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IMTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIMTree window
#define   DRAG_DELAY   60

class CIMTree : public CTreeCtrl
{
// Construction
public:
	CIMTree();

// Attributes
public:
	COLORREF BgColor;
	COLORREF FontColor;
private:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIMTree)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIMTree();

	void SetBgStretch(BOOL Flag);
	BOOL SetBkImage(HBITMAP hBmp);
	BOOL SetBkImage(UINT nIDResource);
	BOOL SetBkImage(LPCTSTR lpszResourceName);

	// Generated message map functions
protected:
	virtual void DrawItemText(CDC* pDC, CString text, CRect rect,int nFormat);

	CPalette	m_pal;
	CBitmap		m_bitmap;
	int		m_cxBitmap;
	int		m_cyBitmap;
	
	//{{AFX_MSG(CIMTree)
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bBgStretch;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMTREE_H__79262109_23F6_490D_8E5B_69D599DEACA0__INCLUDED_)
