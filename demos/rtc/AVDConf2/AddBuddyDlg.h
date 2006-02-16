#if !defined(AFX_ADDBUDDYDLG_H__63A3048C_E9B0_4DE1_BF1F_9C55A0F6F48B__INCLUDED_)
#define AFX_ADDBUDDYDLG_H__63A3048C_E9B0_4DE1_BF1F_9C55A0F6F48B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddBuddyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddBuddyDlg dialog

class CAddBuddyDlg : public CDialog
{
// Construction
public:
	BSTR bstrBuddyURI;
	BSTR bstrBuddyName;
	CAddBuddyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddBuddyDlg)
	enum { IDD = IDD_ADDBUDDY };
	CIPAddressCtrl	m_cBuddyURI;
	CEdit	m_cBuddyName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddBuddyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddBuddyDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDBUDDYDLG_H__63A3048C_E9B0_4DE1_BF1F_9C55A0F6F48B__INCLUDED_)
