// RecSocket.cpp : implementation file
//

#include "stdafx.h"
#include "RecSocket.h"
#include "head.h"
#include "AudioCode.h"
#include "WaveOut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecSocket

extern CAudioCode g_ACode;
extern CWaveOut *g_pOut;
CRecSocket::CRecSocket()
{
	m_bIni = FALSE;
	m_pFrame = (struct Frame *)m_cBuffer;
}

CRecSocket::~CRecSocket()
{

}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CRecSocket, CSocket)
	//{{AFX_MSG_MAP(CRecSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CRecSocket member functions

BOOL CRecSocket::Ini()
{
	if (m_bIni)
		return FALSE;

	//	if (!Create (TALK_REC_PORT,SOCK_DGRAM))
	//		return FALSE;
	m_bIni = TRUE;
	return TRUE;
}

void CRecSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	m_iLen = sizeof(m_cBuffer);
	m_iLen = this->Receive (m_pFrame,m_iLen);
	m_sort .ReceiveData ((char *)m_pFrame,m_iLen);
	//paly now
//	Play(m_cBuffer + sizeof(struct Frame),60);

	static int i = 0;
	i++;

	CSocket::OnReceive(nErrorCode);
}

BOOL CRecSocket::CloseSocket()
{
	if (!m_bIni)
		return FALSE;
	m_bIni = FALSE;
	CSocket::Close ();
	return TRUE;
}


void CRecSocket::Play(char *pBuffer, int iLen)
{
	int iOut;
	iOut = sizeof(m_cOut);
	g_ACode.DecodeAudioData (pBuffer,iLen,m_cOut,&iOut);
	g_pOut->Play (m_cOut,iOut);
}

