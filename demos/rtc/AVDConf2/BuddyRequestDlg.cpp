// ------------------------------------------------------------------------------------
// Copyright ©2002 Intel Corporation
// All Rights Reserved
// 
// Permission is granted to use, copy, distribute and prepare derivative works of this 
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  This software is provided "AS IS." 
//
// Intel specifically disclaims all warranties, express or implied, and all liability,
// including consequential and other indirect damages, for the use of this software, 
// including liability for infringement of any proprietary rights, and including the 
// warranties of merchantability and fitness for a particular purpose.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.
// ------------------------------------------------------------------------------------
//
// BuddyRequestDlg.cpp : implementation file
//
// Purpose: Watcher dialog box.  Shows a dialog if a new user is add you to their buddy list.
//

#include "stdafx.h"
#include "avdconf.h"
#include "BuddyRequestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuddyRequestDlg dialog


CBuddyRequestDlg::CBuddyRequestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBuddyRequestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuddyRequestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBuddyRequestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuddyRequestDlg)
	DDX_Control(pDX, IDC_AUTOBUDDY, m_cAutoAddBuddy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuddyRequestDlg, CDialog)
	//{{AFX_MSG_MAP(CBuddyRequestDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuddyRequestDlg message handlers

BOOL CBuddyRequestDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Get the address location of the share memory created by the parent window.
	pData = (SESSION_DATA *)GetWindowLongPtr( ::GetWindow (m_hWnd, GW_OWNER), GWL_USERDATA);
	
	SetDlgItemTextW ( m_hWnd, IDC_WATCHERNAME, pData->bstrName );

	SetDlgItemTextW ( m_hWnd, IDC_WATCHERURI, pData->bstrURI );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBuddyRequestDlg::OnOK() 
{
	pData->bAutoAdd = ::IsDlgButtonChecked (m_hWnd, IDC_AUTOBUDDY);	
	CDialog::OnOK();
}
