// CNIcq.h : main header file for the CNICQ application
//

#if !defined(AFX_CNICQ_H__33177D6F_9601_4E3C_9B61_766E64482788__INCLUDED_)
#define AFX_CNICQ_H__33177D6F_9601_4E3C_9B61_766E64482788__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "Skin.h"

/////////////////////////////////////////////////////////////////////////////
// CCNIcqApp:
// See CNIcq.cpp for the implementation of this class
//

class CCNIcqApp : public CWinApp
{
public:
	CSkin m_IMSkin;
	CString m_strMainPath;	//应用程序主目录

	BOOL m_bWin4;
	int m_nDefFont;
	CDC m_dcScreen;

	CString ExtractFilePath(char *FullName);
	CCNIcqApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCNIcqApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCNIcqApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNICQ_H__33177D6F_9601_4E3C_9B61_766E64482788__INCLUDED_)
