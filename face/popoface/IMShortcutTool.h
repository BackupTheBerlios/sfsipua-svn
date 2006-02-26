#if !defined(AFX_IMSHORTCUTTOOL_H__DC6D3943_144A_11D7_90A4_006008267A03__INCLUDED_)
#define AFX_IMSHORTCUTTOOL_H__DC6D3943_144A_11D7_90A4_006008267A03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IMShortcutTool.h : header file
//
#include "Skin.h"
#include "CNButton.h"
#include "IMChat.h"

/////////////////////////////////////////////////////////////////////////////
// CIMShortcutTool window
#define MAX_BUTTON	10
#define BUTTON_HEIGHT	18
#define WM_CN_ITEMCLICK	WM_USER+100

class CIMShortcutTool : public CWnd
{
// Construction
public:
	CIMShortcutTool();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIMShortcutTool)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual int GetClientHeight();
	BOOL m_bHide;
	virtual BOOL AddButton(CString Caption, int nID,int nImage = -1);
	virtual ~CIMShortcutTool();

	// Generated message map functions
protected:
	CSkin *m_pSkin;

	CNButton *m_pBtnIWarnt;

	CNButton *m_pBtn[MAX_BUTTON];

	CImageList *m_ILIcon;	//ÕºœÛ¡–±Ì

	//{{AFX_MSG(CIMShortcutTool)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBNClicked1();
	afx_msg void OnBNClicked2();
	//}}AFX_MSG
	afx_msg LRESULT OnBNClicked(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	void ShowHideButton();
	int m_iButtonCount;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMSHORTCUTTOOL_H__DC6D3943_144A_11D7_90A4_006008267A03__INCLUDED_)
