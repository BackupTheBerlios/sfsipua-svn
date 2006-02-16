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
// MakeCallDlg.cpp : Handles the user input dialog to make a call.
//

#include "stdafx.h"
#include "AVDConf.h"
#include "MakeCallDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	BSTR	g_bstrAddr;

/////////////////////////////////////////////////////////////////////////////
// MakeCallDlg dialog


MakeCallDlg::MakeCallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MakeCallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MakeCallDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MakeCallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MakeCallDlg)
	DDX_Control(pDX, IDC_DESTIP, m_cIPAddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MakeCallDlg, CDialog)
	//{{AFX_MSG_MAP(MakeCallDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MakeCallDlg message handlers

void MakeCallDlg::OnOK() 
{
	WCHAR	wszIPBuf[MAX_XML_STRING];
	DWORD	dwIPAddr = 0;

	if (m_cIPAddr.IsBlank())
	{ // No IP Address entered
		MessageBox ( "Please Enter an IP Address." );
		return;
	}
	// Get the destination address.
	m_cIPAddr.GetAddress ( dwIPAddr );

    if (dwIPAddr == 0)
	{	// Quick sanity check to make sure IP address is not 0.0.0.0
		MessageBox ( "Please Enter a valid IP Address." );
		return;
	}
	
	// Convert DWORD IP address to WCHAR format
	_snwprintf( wszIPBuf, MAX_XML_STRING, 
		L"%d.%d.%d.%d", 
		(dwIPAddr >> 24) & 0xff,
		(dwIPAddr >> 16) & 0xff, 
		(dwIPAddr >> 8) & 0xff,
		dwIPAddr & 0xff);

	g_bstrAddr = SysAllocString ( _T(wszIPBuf) );
	
	CDialog::OnOK();
}
