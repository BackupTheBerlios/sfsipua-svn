#if !defined(AFX_IMAINPANEL_H__DC6D3942_144A_11D7_90A4_006008267A03__INCLUDED_)
#define AFX_IMAINPANEL_H__DC6D3942_144A_11D7_90A4_006008267A03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IMainPanel.h : header file
//
#include "IMainHeader.h"
#include "IMTree.h"
#include "Skin.h"
#include "IMShortcutTool.h"
/////////////////////////////////////////////////////////////////////////////
// CIMainPanel window

class CIMainPanel : public CWnd
{
// Construction
public:
	CIMainPanel();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIMainPanel)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIMainPanel();

	// Generated message map functions
protected:
	CSkin *m_pSkin;

	CIMainHeader *m_pIMHeader;
	CIMTree *m_pIMTree;
	CIMShortcutTool *m_pIMShortcutTool;

	//{{AFX_MSG(CIMainPanel)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnShortcutMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAINPANEL_H__DC6D3942_144A_11D7_90A4_006008267A03__INCLUDED_)
