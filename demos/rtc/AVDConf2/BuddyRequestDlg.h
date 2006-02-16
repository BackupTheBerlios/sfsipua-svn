#if !defined(AFX_BUDDYREQUESTDLG_H__83F7DC59_A45A_4135_BC51_A0EA692F5990__INCLUDED_)
#define AFX_BUDDYREQUESTDLG_H__83F7DC59_A45A_4135_BC51_A0EA692F5990__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuddyRequestDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuddyRequestDlg dialog

class CBuddyRequestDlg : public CDialog
{
// Construction
public:
	CBuddyRequestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBuddyRequestDlg)
	enum { IDD = IDD_WATCHER };
	CButton	m_cAutoAddBuddy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuddyRequestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBuddyRequestDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	SESSION_DATA *pData;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUDDYREQUESTDLG_H__83F7DC59_A45A_4135_BC51_A0EA692F5990__INCLUDED_)
