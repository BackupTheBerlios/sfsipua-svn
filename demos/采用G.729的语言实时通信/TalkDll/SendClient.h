#if !defined(AFX_SENDCLIENT_H__210219AA_0227_422B_8E1C_2458AEF6CAE1__INCLUDED_)
#define AFX_SENDCLIENT_H__210219AA_0227_422B_8E1C_2458AEF6CAE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendClient.h : header file
//

#include "MyWaveIn.h"
#include "Interface.h"
/////////////////////////////////////////////////////////////////////////////
// CSendClient command target

class CSendClient : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CSendClient(CMyWaveIn *pIn,CInterface *pInterface);
	virtual ~CSendClient();

// Overrides
public:
	BOOL m_bConnect;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendClient)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSendClient)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	char *m_pBuffer;
	CMyWaveIn *m_pIn;
	CInterface *m_pInterFace;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDCLIENT_H__210219AA_0227_422B_8E1C_2458AEF6CAE1__INCLUDED_)
