// Acmcodec.h: interface for the CAcmcodec class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACMCODEC_H__9D448199_1A2F_4630_B173_51B6940A8E6F__INCLUDED_)
#define AFX_ACMCODEC_H__9D448199_1A2F_4630_B173_51B6940A8E6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mmsystem.h"
#include "mmreg.h"
#include "msacm.h"

#pragma comment(lib,"msacm32")


class CAcmcodec  
{
public:
	DWORD	GetVer(char strver[20]);
	DWORD	ChkCodec();
	
	
	CAcmcodec();
	virtual ~CAcmcodec();
	
	BOOL	static bG711;
private:
	
	//	static BOOL CALLBACK acmDriverEnumCallback( HACMDRIVERID hadid, DWORD dwInstance, DWORD fdwSupport );
};

#endif // !defined(AFX_ACMCODEC_H__9D448199_1A2F_4630_B173_51B6940A8E6F__INCLUDED_)
