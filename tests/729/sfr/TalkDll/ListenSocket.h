#if !defined(AFX_LISTENSOCKET_H__6C2A38AF_7ACD_4506_94C4_58D728B79D7B__INCLUDED_)
#define AFX_LISTENSOCKET_H__6C2A38AF_7ACD_4506_94C4_58D728B79D7B__INCLUDED_

#include "ClientSocket.h"	// Added by ClassView
#include "Interface.h"
#include "MyWaveIn.h"
#include "UdpSocket.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

class CListenSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CListenSocket(CInterface *pTemp,CMyWaveIn *pIn,CUdpSocket *pUdp);
	virtual ~CListenSocket();

// Overrides
public:
	void CloseClient();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CClientSocket *m_sopClient;
	CInterface *m_pInterface;
	CMyWaveIn *m_pIn;
	CUdpSocket *m_pUdp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__6C2A38AF_7ACD_4506_94C4_58D728B79D7B__INCLUDED_)
