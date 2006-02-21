// testwin.h : main header file for the TESTWIN application
//

#if !defined(AFX_TESTWIN_H__E16E730B_D595_47B9_9016_FB287E264E95__INCLUDED_)
#define AFX_TESTWIN_H__E16E730B_D595_47B9_9016_FB287E264E95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestwinApp:
// See testwin.cpp for the implementation of this class
//

class CTestwinApp : public CWinApp
{
public:
	CTestwinApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestwinApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestwinApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTWIN_H__E16E730B_D595_47B9_9016_FB287E264E95__INCLUDED_)
