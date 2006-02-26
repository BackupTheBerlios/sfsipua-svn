#if !defined(AFX_IMCHAT_H__D2E9BF8A_6F25_4245_9831_B6947411E2E4__INCLUDED_)
#define AFX_IMCHAT_H__D2E9BF8A_6F25_4245_9831_B6947411E2E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IMChat.h : header file
//
#include "RichEditCtrlEx.h"
#include "IMToolWin.h"
#include "StaticSplitter.h"
#include "MSNButton.h"
#include "CNButton.h"

/////////////////////////////////////////////////////////////////////////////
// CIMChat dialog

#define TOOLWIN_WIDTH	140

class CIMChat : public CDialog
{
// Construction
public:
	void SetSplitterPos(int NewPos);
	CSkin *m_pSkin;

	CIMChat(CWnd* pParent = NULL);   // standard constructor

//	CFormatBar	m_wndFormatBar;
	CStatusBarCtrl	m_StatBar;

// Dialog Data
	//{{AFX_DATA(CIMChat)
	enum { IDD = IDD_CHAT_DIALOG };
	CNButton	m_btnToolWin;
	CNButton	m_btnReply;
	CNButton	m_btnMessage;
	CNButton	m_btnEmotons;
	//}}AFX_DATA

	CRichEditCtrlEx	m_ShowMsgEdit;
	CRichEditCtrlEx	m_SendEdit;
	CStaticSplitter m_Splitter;
	CStatusBar	m_statusBar;
	CIMToolWin	m_ToolWin;
	CMSNButton	m_SendButton;

	CFont FontNormal;
	CFont FontBold;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIMChat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	afx_msg void OnEmotionPick(UINT nID);

// Implementation
protected:
	HCURSOR		m_crLink ;
	IRichEditOle*	m_pRichEditOle;

	virtual void UpdateSizes();

	// Generated message map functions
	//{{AFX_MSG(CIMChat)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRichEditExLink( NMHDR* in_pNotifyHeader, LRESULT* out_pResult );
	afx_msg void OnPaint();
	afx_msg void OnChangeSendmsg();
	afx_msg void OnBtnChatSend();
	afx_msg void OnBtnMessage();
	afx_msg void OnBtnEmotons();
	afx_msg void OnBtnFastreply();
	afx_msg void OnBtnToolwin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bShowToolWin;
	int m_SplitterPos;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMCHAT_H__D2E9BF8A_6F25_4245_9831_B6947411E2E4__INCLUDED_)
