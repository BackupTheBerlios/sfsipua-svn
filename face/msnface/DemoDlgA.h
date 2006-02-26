#if !defined(AFX_DEMODLGA_H__203D5BFB_6782_4669_AC37_FB726B49C1D6__INCLUDED_)
#define AFX_DEMODLGA_H__203D5BFB_6782_4669_AC37_FB726B49C1D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DemoDlgA.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDemoDlgA dialog
#include "HyperLink.h"

class CDemoDlgA : public CDialog
{
// Construction
public:
	CDemoDlgA(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDemoDlgA)
	enum { IDD = IDD_DIALOG_PAGE1 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDlgA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDemoDlgA)
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODLGA_H__203D5BFB_6782_4669_AC37_FB726B49C1D6__INCLUDED_)
