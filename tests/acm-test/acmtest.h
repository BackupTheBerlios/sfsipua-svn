// acmtest.h : main header file for the ACMTEST application
//

#if !defined(AFX_ACMTEST_H__CE03D99B_C7F4_4634_A70F_13C000BBD0DF__INCLUDED_)
#define AFX_ACMTEST_H__CE03D99B_C7F4_4634_A70F_13C000BBD0DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAcmtestApp:
// See acmtest.cpp for the implementation of this class
//

class CAcmtestApp : public CWinApp
{
public:
	CAcmtestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAcmtestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAcmtestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACMTEST_H__CE03D99B_C7F4_4634_A70F_13C000BBD0DF__INCLUDED_)
