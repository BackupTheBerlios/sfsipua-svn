// ReceiverDlg.h : header file
//

#if !defined(AFX_RECEIVERDLG_H__E4AB2F37_DE6B_4F36_BD34_DDC4CD823B45__INCLUDED_)
#define AFX_RECEIVERDLG_H__E4AB2F37_DE6B_4F36_BD34_DDC4CD823B45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CReceiverDlg dialog
class RTPSession;
class CReceiverDlg : public CDialog
{
// Construction
public:
	FILE *output;
	CFile file;
	CReceiverDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CReceiverDlg)
	enum { IDD = IDD_RECEIVER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReceiverDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CReceiverDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLink();
	afx_msg void OnTest();
	afx_msg void OnClose();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECEIVERDLG_H__E4AB2F37_DE6B_4F36_BD34_DDC4CD823B45__INCLUDED_)
