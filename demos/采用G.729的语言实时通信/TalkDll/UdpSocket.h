#if !defined(AFX_UDPSOCKET_H__0A297728_20FE_4B3D_832C_0884257B0B85__INCLUDED_)
#define AFX_UDPSOCKET_H__0A297728_20FE_4B3D_832C_0884257B0B85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UdpSocket.h : header file
//

#include <afxsock.h>

/////////////////////////////////////////////////////////////////////////////
// CUdpSocket command target
class CUdpSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CUdpSocket();
	virtual ~CUdpSocket();

// Overrides
public:
	void SetIp(CString ip);
	BOOL CloseSocket();
	BOOL m_bIni;
	BOOL Ini();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUdpSocket)
	public:
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CUdpSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	struct Frame *m_pFrame;
	CString m_ip;
	char m_cBuffer[1024];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPSOCKET_H__0A297728_20FE_4B3D_832C_0884257B0B85__INCLUDED_)
