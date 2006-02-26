// DemoDlgB.cpp : implementation file
//

#include "stdafx.h"
#include "Messenger.h"
#include "DemoDlgB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoDlgB dialog


CDemoDlgB::CDemoDlgB(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlgB::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlgB)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDemoDlgB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlgB)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDemoDlgB, CDialog)
	//{{AFX_MSG_MAP(CDemoDlgB)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlgB message handlers
