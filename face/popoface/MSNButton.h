#if !defined(AFX_BUTTONEX_H__24F3B8E1_7579_11D1_BC08_0080C825700A__INCLUDED_)
#define AFX_TRACKLOOKBUTTON_H__24F3B8E1_7579_11D1_BC08_0080C825700A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TrackLookButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TrackLookButton window

//DrawBitmap flags;
#define	DB_HCENTER	0x0001L
#define DB_VCENTER	0x0002L

#define COL_DISABLED	1
#define COL_LIGHTITEMS	2
#define COL_LINEFRAMES	3
#define COL_NOTIFYTEXT	4
#define COL_NORMALTEXT	5
#define COL_BTNOVER	6
#define COL_BTNACTIVE	7
#define COL_BTNBACK	8
#define COL_DISABLEDTEXT	9


class CMSNButton : public CButton
{
// Construction
public:
	CMSNButton();

// Attributes
public:
	typedef enum TextAlign {AlignLeft = 0, AlignRight, AlignBelow, AlignAbove, AlignCenter};
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TrackLookButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL
	void	OnMouseEnter(UINT nFlags, CPoint point);
	void	OnMouseLeave(UINT nFlags, CPoint point);

// Implementation
public:
	virtual void DrawFocus(BOOL bDrawFocus = TRUE);
	bool LoadBitmaps(LPCSTR lpszBitmap, LPCSTR lpszBitmapFocus = NULL,LPCSTR lpszBitmapDisabled = NULL);
	void SetTextAlignment(TextAlign nTextAlign);
	TextAlign GetTextAlignment() const;
	bool LoadBitmaps(UINT nBitmap, UINT nBitmapFocus=0, UINT nBitmapDisabled = 0);
	void SetCornerColor(COLORREF);
	virtual ~CMSNButton();

	// Generated message map functions
protected:
	bool m_bRaised;

	void DrawBitmap(CDC* pDC,CRect rc,UINT nFlags,CBitmap* pBitmap);

	CBitmap m_bitmap;
	CBitmap m_bitmapFocus;
	CBitmap m_bitmapDisabled;
	CBitmap m_bitmapRaised;

	COLORREF m_crCornerColor;
	
	TextAlign	m_TextAlign;
	bool		m_bDisabled;
	bool		m_bHasFocus;
	bool		m_bClickedIn;
	bool		m_bKeyDown;

	void DrawDot(CDC *pDC, int x, int y, COLORREF col);
	void DrawDottedLine(CDC *pDC, int x, int y, int len, bool vertical, COLORREF col);

	bool		m_bLButtonDown;
	bool		m_bMouseCaptured;
	//{{AFX_MSG(TrackLookButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEnable(bool bEnable);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bDrawFocus;
};

/////////////////////////////////////////////////////////////////////////////
COLORREF GetColor(int nIndex);

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONEX_H__24F3B8E1_7579_11D1_BC08_0080C825700A__INCLUDED_)
