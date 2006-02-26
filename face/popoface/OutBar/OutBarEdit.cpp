// CNOutBarEdit.cpp : implementation file
//

#include "stdafx.h"
#include "OutBarEdit.h"
#include "OutBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNOutBarEdit

CNOutBarEdit::CNOutBarEdit(CNOutBarCtrl *l, int obj, int index)
: listener(l)
{
	this->obj = obj;
	this->index = index;
}

CNOutBarEdit::~CNOutBarEdit()
{
}


BEGIN_MESSAGE_MAP(CNOutBarEdit, CEdit)
	//{{AFX_MSG_MAP(CNOutBarEdit)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNOutBarEdit message handlers

void CNOutBarEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	
	listener->onEditFinished();	
}

BOOL CNOutBarEdit::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN) {
			listener->onEditFinished();
			return TRUE;
		}
		if (pMsg->wParam == VK_ESCAPE) {
			listener->onEditCanceled();
			return TRUE;
		}
	}
	return CEdit::PreTranslateMessage(pMsg);
}
