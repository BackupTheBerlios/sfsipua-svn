// AVDConfDlg.h : header file
//

#if !defined(AFX_AVDCONFDLG_H__8AA2F9CB_82AD_4A1F_B960_5727AC5C12EE__INCLUDED_)
#define AFX_AVDCONFDLG_H__8AA2F9CB_82AD_4A1F_B960_5727AC5C12EE__INCLUDED_

#include "RTCEvents.h"	// Added by ClassView
#include "AVDlg.h"	// Added by ClassView
#include "MessageDlg.h"	// Added by ClassView
#include "systeminfo.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAVDConfDlg dialog

class CAVDConfDlg : public CDialog
{
// Construction
public:
	CToolTipCtrl m_cTooltip;
	CAVDConfDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAVDConfDlg)
	enum { IDD = IDD_AVDCONF_DIALOG };
	CButton	m_cRemoveBuddy;
	CListCtrl	m_cBuddyList;
	CButton	m_cAddbuddy;
	CButton	m_cLogOff;
	CButton	m_cLogin;
	CStatic	m_cPresLabel;
	CComboBox	m_cPresStatus;
	CProgressCtrl	m_ctrCPU1Progress;
	CProgressCtrl	m_ctrCPU2Progress;
	CStatic	m_ctrCPU2Percent;
	CStatic	m_ctrCPU2Label;
	CButton	m_btnSysInfo;
	CButton	m_cWhiteboard;
	CButton	m_cMessaging;
	CButton	m_cTuning;
	CButton	m_cMakeCall;
	CButton	m_cAppCall;
	CString	m_csLocalIP;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAVDConfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAVDConfDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMakecall();
	afx_msg void OnAppcall();
	afx_msg void OnTuning();
	afx_msg void OnMessaging();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAboutbox();
	afx_msg void OnWhiteboard();
	afx_msg void OnSysteminfo();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLogin();
	afx_msg void OnAddbuddy();
	afx_msg void OnRemovebuddy();
	afx_msg void OnLogoff();
	afx_msg void OnSelchangePresencestatus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HRESULT SetPresence ( int iStatus );
	BOOL m_bIMInProgress;
	HRESULT SIPAuthentication(BSTR bstrURI, BSTR bstrAccount, BSTR bstrPassword);
	HRESULT OnLoggedOff();
	HRESULT GetUserURIFromList (int Id, BSTR *bstrURI);
	HRESULT DoAddBuddy (BSTR bstrName, BSTR bstrURI);
	HRESULT DoLogOff();
	HRESULT ClearBuddyList();
	HRESULT UpdateBuddyList(IRTCBuddy * pBuddy);
	HRESULT OnLoggedOn();
	void OnLoggingOff();
	void OnLoggingOn();
	void UpdateStatus ( LPSTR szStatus );
	BOOL m_bPresenceEnabled;
	HRESULT EnablePresence (BOOL bEnable);
	HRESULT DoSIPLogoff ();
	IRTCProfile * m_pProfile;
	HRESULT DoSIPLogin ( BSTR bXMLObj );
	void OnRTCParticipantStateChangeEvent(IRTCParticipantStateChangeEvent *pEvent);
	void OnRTCBuddyEvent(IRTCBuddyEvent *pEvent);
	void OnRTCWatcherEvent(IRTCWatcherEvent *pEvent);
	void OnRTCRegistrationStateChangeEvent(IRTCRegistrationStateChangeEvent *pEvent);
	DWORD m_dwCPUMax;
	bool m_bPerfCtrInit;
	void GetSysInfo();
	HRESULT OnRTCMessagingEvent (IRTCMessagingEvent *pEvent);
	
	CMessageDlg m_cMessageDlg;
	CSystemInfo	m_SysInfo;
	CAVDlg m_AVDlg;
	HRESULT AddSession(IRTCSession *pSession, RTC_SESSION_TYPE enType);
	IRTCParticipant * m_Participant;
	HRESULT MakeCall(RTC_SESSION_TYPE enType, BSTR bstrURI);
	void OnRTCClientEvent(IRTCClientEvent *pEvent);
	void OnRTCIntensityEvent(IRTCIntensityEvent *pEvent);
	void OnRTCMediaEvent(IRTCMediaEvent *pEvent);
	void OnRTCSessionStateChangeEvent(IRTCSessionStateChangeEvent *pEvent);
	HRESULT OnRTCEvent (UINT message, WPARAM wParam, LPARAM lParam);
	CRTCEvents * m_pEvents;
	IRTCClient * m_pClient;
	HRESULT InitRTCClient();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVDCONFDLG_H__8AA2F9CB_82AD_4A1F_B960_5727AC5C12EE__INCLUDED_)
