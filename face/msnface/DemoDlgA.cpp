// DemoDlgA.cpp : implementation file
//

#include "stdafx.h"
#include "Messenger.h"
#include "DemoDlgA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoDlgA dialog


CDemoDlgA::CDemoDlgA(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlgA::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlgA)
	//}}AFX_DATA_INIT
}


void CDemoDlgA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlgA)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDemoDlgA, CDialog)
	//{{AFX_MSG_MAP(CDemoDlgA)
	ON_BN_CLICKED(IDC_BUTTON1, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlgA message handlers
#include "Messenger.h"
void CDemoDlgA::OnTest() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}
