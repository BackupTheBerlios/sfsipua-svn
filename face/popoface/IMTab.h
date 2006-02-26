#if !defined(AFX_IMTAB_H__9B024C11_8200_4F37_B3E3_5F0BFF60B361__INCLUDED_)
#define AFX_IMTAB_H__9B024C11_8200_4F37_B3E3_5F0BFF60B361__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IMTab.h : header file
//
#include "IMTree.h"
#include "Skin.h"
#include "IMainPanel.h"
#include "CNButton.h"

/////////////////////////////////////////////////////////////////////////////
// CIMTab window
#define	MAX_TAB_WIDTH	40
#define MIN_TAB_WIDTH	3

#define	MAX_TAB		3

class CIMTab : public CTabCtrl
{
// Construction
	enum{
		CN_USER_STATUS_ONLINE = 0,
		CN_USER_STATUS_HIDE,
		CN_USER_STATUS_BUSY,
		CN_USER_STATUS_OUTEAT,
		CN_USER_STATUS_PHONE,
		CN_USER_STATUS_OFFLINE,
		CN_USER_STATUS_CUSTOM
	};
public:
	CIMTab();

// Attributes
public:
	CIMainPanel *m_pMainPanel;

	CSkin *m_pSkin;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIMTab)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetActivePage(int NewPage);
	void SetShowTab(BOOL Show);
	virtual ~CIMTab();

	// Generated message map functions
protected:
	int m_nMouseOnTabNo;
	int m_nMyStatus;
	int m_nTabIndex;

	virtual void PageChanged(int NewPage);
	virtual void DrawCorner(CDC *pDC);
	virtual void UpdateTab();

	virtual BOOL DrawTabButton(CDC *pDC);
	virtual void InitGraphics();
	virtual void DrawBackGroud(CDC *pDC, CRect &rc);

	void DrawAll(CDC *pDC);
	//{{AFX_MSG(CIMTab)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
private:
	int m_nTabWidth;
	BOOL m_bShowTab;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMTAB_H__9B024C11_8200_4F37_B3E3_5F0BFF60B361__INCLUDED_)
