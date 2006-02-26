// CNIcqDlg.h : header file
//

#if !defined(AFX_CNICQDLG_H__8ED18B9F_FCB0_4597_ADC7_A80A2BA0CA98__INCLUDED_)
#define AFX_CNICQDLG_H__8ED18B9F_FCB0_4597_ADC7_A80A2BA0CA98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Gif89A.h"
#include "CNButton.h"
#include "IMTab.h"
#include "IMTree.h"
#include "SystemTray.h"

/////////////////////////////////////////////////////////////////////////////
// CCNIcqDlg dialog

class CCNIcqDlg : public CDialog
{
// Construction
public:
//	void GetTadkList(CListBox&list);
	CCNIcqDlg(CWnd* pParent = NULL);	// standard constructor
	~CCNIcqDlg();
// Dialog Data
	//{{AFX_DATA(CCNIcqDlg)
	enum { IDD = IDD_CNICQ_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCNIcqDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
private:
	CGif89a*	m_pGif;
	CIMTab		m_ImTab;
	CSystemTray	m_TrayIcon;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCNIcqDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFileExit();
	afx_msg void OnHelpAbout();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNICQDLG_H__8ED18B9F_FCB0_4597_ADC7_A80A2BA0CA98__INCLUDED_)
