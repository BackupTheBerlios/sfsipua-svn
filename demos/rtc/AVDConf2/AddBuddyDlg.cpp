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
// AddBuddyDlg.cpp : implementation file
//
// Purpose: Dialog handler to add a new buddy to the Buddy list
//

#include "stdafx.h"
#include "avdconf.h"
#include "AddBuddyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddBuddyDlg dialog


CAddBuddyDlg::CAddBuddyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddBuddyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddBuddyDlg)
	//}}AFX_DATA_INIT
}


void CAddBuddyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddBuddyDlg)
	DDX_Control(pDX, IDC_BUDDYURI, m_cBuddyURI);
	DDX_Control(pDX, IDC_BUDDYNAME, m_cBuddyName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddBuddyDlg, CDialog)
	//{{AFX_MSG_MAP(CAddBuddyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddBuddyDlg message handlers

void CAddBuddyDlg::OnOK() 
{
	WCHAR	wcStr[256];
	SESSION_DATA	*pData;
	DWORD	dwIPAddr = 0;


	if (m_cBuddyURI.IsBlank())
	{ // No IP Address entered
		MessageBox ( "Please Enter an IP Address for the buddy person." );
		return;
	}

	pData = (SESSION_DATA *)GetWindowLongPtr ( ::GetWindow (m_hWnd, GW_OWNER), GWL_USERDATA);

	GetDlgItemTextW ( m_hWnd, IDC_BUDDYNAME, wcStr, 256 );

	if (wcslen (wcStr) == 0)
	{
		MessageBox ( "Please enter the Buddy Name" );
		return;
	}

	pData->bstrName = SysAllocString(_T(wcStr));


	GetDlgItemTextW ( m_hWnd, IDC_BUDDYURI, wcStr, 256 );

	if (wcslen (wcStr) == 0)
	{
		MessageBox ( "Please enter the Buddy URI" );
		return;
	}

	pData->bstrURI = SysAllocString ( _T(wcStr) );

	CDialog::OnOK();
}

BOOL CAddBuddyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Limit text to prevent buffer overflow
	m_cBuddyName.LimitText ( 255 );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
