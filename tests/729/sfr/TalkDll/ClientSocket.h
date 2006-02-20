#if !defined(AFX_CLIENTSOCKET_H__A368F0CD_5331_4508_927F_317264A5C084__INCLUDED_)
#define AFX_CLIENTSOCKET_H__A368F0CD_5331_4508_927F_317264A5C084__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//
#include "Interface.h"
#include "MyWaveIn.h"
#include "UdpSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target

class CClientSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CClientSocket(CInterface *pInterFace,CMyWaveIn *pIn,CUdpSocket *pUdp);
	virtual ~CClientSocket();

// Overrides
public:
	BOOL m_bConnect;
	char *m_pBuffer;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CInterface *m_pInterface;
	CMyWaveIn *m_pIn;
	CUdpSocket *m_pUdp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__A368F0CD_5331_4508_927F_317264A5C084__INCLUDED_)
