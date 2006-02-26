#if !defined(AFX_IMAGETABWND_H__B82892D8_3E79_4C59_B540_699F8D6F8333__INCLUDED_)
#define AFX_IMAGETABWND_H__B82892D8_3E79_4C59_B540_699F8D6F8333__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageTabWnd.h : header file
//
#include <afxtempl.h>

#define MAX_DIALOG			100
#define TITLE_HEIGHT		40
#define DIALOG_MARGIN		3


/////////////////////////////////////////////////////////////////////////////
// CImageTabWnd window

class CImageTabWnd : public CWnd
{
// Construction
public:
	CImageTabWnd();

// Attributes
public:

// Operations
public:
	void SetTabCount(int nCount);
	int  GetTabCount() { return m_nTabCount ;}
	int	 GetCurrentTab() { return m_nCurrentIndex; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageTabWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetToolTip(int nIndex, CString strTips);
	void SetTabWnd(int nIndex, CDialog *pDlg);
	void SetAdImage(UINT nID);
	void SetAdImage(CString strName);
	void SetTabRect(int nIndex, CRect rc);
	void SetBkImage(UINT nID);
	void SetBkImage(CString strName);
	void SetRightImage(UINT nID);
	void SetRightImage(CString strName);
	void SetLeftImage(UINT nID);
	void SetLeftImage(CString strName);
	void SetBottomImage(UINT nID);
	void SetBottomImage(CString strName);
	void SetTopImage(UINT nID);
	void SetTopImage(CString strName);
	void SetTabImage(int nIndex, UINT nID);
	void SetTabImage(int nIndex, CString strName);
	virtual ~CImageTabWnd();

	// Generated message map functions
protected:
	CBitmap *m_pBitmapTab;
	CRect	*m_pRectTab;
	
	CBitmap m_BitmapBk;
	CSize	m_szBitmapBk;
	CBitmap m_BitmapTop;
	CSize	m_szBitmapTop;
	CBitmap m_BitmapBottom;
	CSize	m_szBitmapBottom;
	CBitmap m_BitmapLeft;
	CSize	m_szBitmapLeft;
	CBitmap m_BitmapRight;
	CSize	m_szBitmapRight;
	CBitmap m_BitmapAd;
	CSize	m_szBitmapAd;

	int		m_nTabCount;
	int		m_nCurrentIndex;

	CRect	m_rcDialog;
	CDialog	*m_pTabDialog[MAX_DIALOG];

	CToolTipCtrl m_ToolTip;
	//{{AFX_MSG(CImageTabWnd)
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void UpdateTabWnd();
	void ShowDialog();
	void SetImageSize(CBitmap *pBitmap, CSize &sz);
	void DrawPosImage(CBitmap *pBitmap, CDC *pDC, CPoint pt);
	void DrawRangeImage(CBitmap *pBitmap, CDC *pDC, CRect rc);
	void SetImage(CBitmap &bitmap, UINT nID);
	void SetImage(CBitmap &bitmap, CString strName);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGETABWND_H__B82892D8_3E79_4C59_B540_699F8D6F8333__INCLUDED_)
