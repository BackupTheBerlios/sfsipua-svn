// UdpSocket.cpp : implementation file
//

#include "stdafx.h"
#include "UdpSocket.h"
#include "head.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUdpSocket

CUdpSocket::CUdpSocket()
{
	m_pFrame = (struct Frame *)m_cBuffer;
	m_pFrame->iIndex = 0;
	m_bIni = FALSE;
}

CUdpSocket::~CUdpSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CUdpSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CUdpSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CUdpSocket member functions

BOOL CUdpSocket::Ini()
{
	if (m_bIni)
		return FALSE;

	if (!this->Create (NULL,SOCK_DGRAM))
	{
		return FALSE;
	};

	m_bIni = TRUE;
	return TRUE;
}

int CUdpSocket::Send(const void* lpBuf, int nBufLen, int nFlags)
{
	// TODO: Add your specialized code here and/or call the base class
	m_pFrame->iIndex ++;
	memcpy(m_cBuffer + sizeof(struct Frame),lpBuf,nBufLen);
	
	return CAsyncSocket::SendTo (m_pFrame, nBufLen + sizeof(struct Frame),TALK_REC_PORT,m_ip, nFlags);
}

BOOL CUdpSocket::CloseSocket()
{
	if (!m_bIni)
		return FALSE;

	CAsyncSocket::Close ();
	m_bIni = FALSE;
	return TRUE;
}

void CUdpSocket::SetIp(CString ip)
{
	m_ip = ip;
}
