// SendClient.cpp : implementation file
//

#include "stdafx.h"
#include "SendClient.h"
#include "head.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendClient

CSendClient::CSendClient(CMyWaveIn *pIn,CInterface *pInterface):
	m_pIn(NULL),
	m_pInterFace(NULL)
{
	m_pBuffer = new char[1024];
	m_pIn = pIn;
	m_pInterFace = pInterface;
}

CSendClient::~CSendClient()
{
	delete [1024]m_pBuffer;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSendClient, CAsyncSocket)
	//{{AFX_MSG_MAP(CSendClient)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSendClient member functions

void CSendClient::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	struct TalkFrame *frame;
	frame = (struct TalkFrame *)m_pBuffer;
	
	int iLen = sizeof(struct TalkFrame);
	while(iLen > 0)
	{
		int i = Receive (m_pBuffer + sizeof(struct TalkFrame) - iLen,iLen);
		if (i == SOCKET_ERROR )
			return ;
		iLen -= i;
	}
	if (strcmp(frame->cFlag ,"TalkFrame") != 0)
	{
		return;
	}

	iLen = frame->iLen;
	frame->iLen;
	while (iLen > 0)
	{
		int i = Receive (
			m_pBuffer + sizeof(struct TalkFrame) + (frame->iLen - iLen),
			iLen);
		if (i == SOCKET_ERROR)
			return ;
		iLen -= i;
	}

	CString add;
	UINT port;

	switch (frame->iCom )
	{
	case TC_AGREE_TALK:
		GetPeerName (add,port);
		m_pInterFace->TalkStart (add);
		m_pIn->EnableSend (TRUE);
		m_pInterFace->m_bWork = TRUE;
		break;
	default:
		break;
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

void CSendClient::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_bConnect = FALSE;

	m_pInterFace->BeClose ();

	CAsyncSocket::OnClose(nErrorCode);
}

void CSendClient::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_pInterFace->ConnectResult(nErrorCode);
	CAsyncSocket::OnConnect(nErrorCode);
}
