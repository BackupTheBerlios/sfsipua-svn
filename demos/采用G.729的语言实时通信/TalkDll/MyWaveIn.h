// MyWaveIn.h: interface for the CMyWaveIn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYWAVEIN_H__D6D88534_ED10_4ADA_8340_03302FE5E649__INCLUDED_)
#define AFX_MYWAVEIN_H__D6D88534_ED10_4ADA_8340_03302FE5E649__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WaveIn.h"
#include "UdpSocket.h"

#include <afxmt.h>

class CMyWaveIn : public CWaveIn
{
public:
	void EnableSend(BOOL bSend);
	CMyWaveIn(CUdpSocket *pTemp);
	virtual ~CMyWaveIn();

	virtual void GetData(char *pBuffer,int iLen);
protected:
	CUdpSocket *m_pUdp;
	BOOL m_bSend;
	CCriticalSection m_soLock;
	char m_cBufOut[1024];
};

#endif // !defined(AFX_MYWAVEIN_H__D6D88534_ED10_4ADA_8340_03302FE5E649__INCLUDED_)
