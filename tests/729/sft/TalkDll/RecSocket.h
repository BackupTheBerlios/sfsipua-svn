#if !defined(AFX_RECSOCKET_H__456028CD_6393_4A53_BB42_40AA90A06F58__INCLUDED_)
#define AFX_RECSOCKET_H__456028CD_6393_4A53_BB42_40AA90A06F58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecSocket.h : header file
//

#include <afxsock.h>
#include "SortData.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////
// CRecSocket command target

class CRecSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CRecSocket();
	virtual ~CRecSocket();

// Overrides
public:
	void Play(char *pBuffer, int iLen);
	BOOL CloseSocket();
	BOOL Ini();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CRecSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
public:
	CSortData m_sort;
protected:
	BOOL m_bIni;
	struct Frame *m_pFrame;
	char m_cBuffer[1024];
	int m_iLen;
	char m_cOut[1024];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECSOCKET_H__456028CD_6393_4A53_BB42_40AA90A06F58__INCLUDED_)
