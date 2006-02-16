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
// AuthDlg.cpp : implementation file
//
// Purpose: Dialog handler for SIP Server login/password authentication
//

#include "stdafx.h"
#include "avdconf.h"
#include "AuthDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SESSION_DATA	*pData = NULL;

/////////////////////////////////////////////////////////////////////////////
// CAuthDlg dialog


CAuthDlg::CAuthDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAuthDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAuthDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAuthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAuthDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAuthDlg, CDialog)
	//{{AFX_MSG_MAP(CAuthDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAuthDlg message handlers

void CAuthDlg::OnOK() 
{
	
	CDialog::OnOK();
}

BOOL CAuthDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	pData = (SESSION_DATA *)GetWindowLongPtr( ::GetWindow (m_hWnd, GW_OWNER), GWL_USERDATA);

	SetDlgItemTextW (m_hWnd, IDC_USERURI, pData->bstrURI );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
