// Interface.cpp: implementation of the CInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Interface.h"
#include "head.h"
#include "MyWaveIn.h"	// Added by ClassView
#include "WaveOut.h"	// Added by ClassView
#include "ListenSocket.h"	// Added by ClassView
#include "SendClient.h"
#include "UdpSocket.h"
#include "RecSocket.h"
#include <afxmt.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CWaveOut *g_pOut;
CCriticalSection g_soLock;

CInterface::CInterface():
	m_bIni (FALSE)
{	
	m_bWork = FALSE;
	m_pUdp = new CUdpSocket();
	m_pRec = new CRecSocket();

	g_pOut = new CWaveOut();
	m_pIn = new CMyWaveIn(m_pUdp);
	m_sopListen = new CListenSocket(this,m_pIn,m_pUdp);
	m_sopSend = new CSendClient(m_pIn,this);
}

CInterface::~CInterface()
{
	if (m_bIni)
	{
		m_sopListen->Close ();
	}
	if (m_bWork)
	{
		End();
	}
	m_pIn->StopRec ();
	m_pUdp->CloseSocket ();

	m_pRec->CloseSocket ();
	g_pOut->StopPlay ();

	delete m_sopSend;
	delete m_sopListen;
	delete m_pIn;
	delete g_pOut;
	delete m_pUdp;
	delete m_pRec;
}

BOOL CInterface::Start(CString ip)
{
	char name[128];
	int iLen = 128;
	int i = 0;
	CString loip;

	BOOL bRe;
	bRe = FALSE;

	if (m_bWork)
	{
		TRACE("The talk has worked.\n");
		goto Exit;
	}
	m_sIp = ip;

	if (SOCKET_ERROR  == gethostname(name,iLen))
	{
		TRACE("I can't get the name.\n");
		goto Exit;
	}
	struct hostent *phost;
	phost = gethostbyname (name);
	if (phost == NULL)
	{
		TRACE("gethostbyname error .\n");
		goto Exit;
	}

	i = 0;


	if (!m_sopSend->Create ())
	{
		goto Exit;
	}

	m_sopSend->Connect (ip,TALK_COM_PORT);
	if (GetLastError() != WSAEWOULDBLOCK)
	{
		goto Exit1;
	}
	m_pUdp->SetIp (ip);

	bRe = TRUE;
	m_bWork = TRUE;
	goto Exit;
Exit1:
	m_sopSend->Close ();
Exit:
	return bRe;
}

BOOL CInterface::End()
{
	if (!m_bWork)
	{
		TRACE("The talk hasn't worked.\n");
		return FALSE;
	}
	
	m_pIn->EnableSend (FALSE);
	m_sopSend->Close ();
	m_sopSend->m_bConnect = FALSE;
	m_sopListen->CloseClient ();
	m_bWork = FALSE;
	return TRUE;
}

BOOL CInterface::Ini()
{
	if (m_bIni)
	{
		TRACE("You have ini the talk model.\n");
		return FALSE;
	}

	//	if (!m_sopListen->Create (TALK_COM_PORT))
	//	{
	//		goto Exit;
	//	}
	//	m_sopListen->Listen ();

	if (!m_pRec->Ini ())
	{
		goto Exit1;
	}
	if (!m_pUdp->Ini ())
	{
		goto Exit2;
	}

	if (!g_pOut->StartPlay ())
	{
		goto Exit3;
	};
	if (!m_pIn->StartRec ())
	{
		goto Exit4;
	};

	m_bIni = TRUE;
	goto Exit;
Exit4:
	g_pOut->StopPlay ();
Exit3:
	m_pUdp->CloseSocket ();
Exit2:
	m_pRec->CloseSocket ();
Exit1:
	m_sopListen->Close ();
Exit:
	return m_bIni;
}

BOOL CInterface::IsConnect(CString ip)
{
	if (IDYES ==  MessageBox(NULL,"talk?","talk",MB_YESNO))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CInterface::TalkStart(CString ip)
{
	CString temp;
	temp.Format ("Talk now ,Ip: %s.",ip);
	AfxMessageBox(temp);
}

void CInterface::TalkBeClose()
{
	AfxMessageBox("Talk be close.");
}

void CInterface::BeClose()
{
	g_soLock.Lock ();
	if (m_bWork)
	{
		m_pIn->EnableSend (FALSE);
		m_sopSend->Close ();
		m_sopSend->m_bConnect = FALSE;
		m_sopListen->CloseClient ();
		m_bWork = FALSE;
		
		TalkBeClose();
	}
	g_soLock.Unlock ();
}

void CInterface::ConnectResult(int nErrorCode)
{
	if (nErrorCode != 0)
	{
		m_bWork = FALSE;
		TalkOnConnect (FALSE);
		return ;
	}
	TalkOnConnect (TRUE);
	
	char buffer[32];
	memset(buffer,0,32);
	struct TalkFrame *frame;
	frame = (struct TalkFrame *)buffer;
	sprintf(frame->cFlag,"TalkFrame");
	
	frame->iLen = 0;
	frame->iCom = TC_NORMAL_TALK;
	m_sopSend->Send (buffer,sizeof(struct TalkFrame));
}

void CInterface::TalkOnConnect(BOOL bRe)
{
	CString t;
	t.Format ("connect %d",bRe);
	AfxMessageBox(t);
}