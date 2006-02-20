// MyWaveIn.cpp: implementation of the CMyWaveIn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyWaveIn.h"
#include "AudioCode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CAudioCode g_ACode;
CMyWaveIn::CMyWaveIn(CUdpSocket *pTemp):
	m_bSend(FALSE)
{
	m_pUdp = pTemp;
}

CMyWaveIn::~CMyWaveIn()
{
}

void CMyWaveIn::GetData(char *pBuffer,int iLen)
{
	m_soLock.Lock ();
	//	if (m_bSend)
	{
		int iOut = sizeof(m_cBufOut);
		g_ACode.EncodeAudioData (pBuffer,iLen,m_cBufOut,&iOut);
		m_pUdp->Send (m_cBufOut,iOut);
	}
	m_soLock.Unlock ();

	CWaveIn::GetData (pBuffer,iLen);
}

void CMyWaveIn::EnableSend(BOOL bSend)
{
	m_soLock.Lock ();
	m_bSend = bSend;
	m_soLock.Unlock ();
}
