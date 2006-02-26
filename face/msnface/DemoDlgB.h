#if !defined(AFX_DEMODLGB_H__C3A06362_B65C_4B83_AD72_2C7B060091BF__INCLUDED_)
#define AFX_DEMODLGB_H__C3A06362_B65C_4B83_AD72_2C7B060091BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DemoDlgB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDemoDlgB dialog

class CDemoDlgB : public CDialog
{
// Construction
public:
	CDemoDlgB(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDemoDlgB)
	enum { IDD = IDD_DIALOG_PAGE2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDlgB)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDemoDlgB)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODLGB_H__C3A06362_B65C_4B83_AD72_2C7B060091BF__INCLUDED_)
