// Acmcodec.cpp: implementation of the CAcmcodec class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "acmtest.h"
#include "Acmcodec.h"
#include "assert.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
BOOL CAcmcodec::bG711 =FALSE;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAcmcodec::CAcmcodec()
{
	
}

CAcmcodec::~CAcmcodec()
{
	
}

DWORD CAcmcodec::GetVer(char strver[20])
{
	DWORD dwACMVer = acmGetVersion();
	sprintf(strver,"%u.%.02u_%u",
		HIWORD(dwACMVer) >> 8,
		HIWORD(dwACMVer) & 0x00FF,
		LOWORD(dwACMVer));
    if (LOWORD(dwACMVer) == 0) printf(" (Retail)");
	
    return dwACMVer;
}



BOOL CALLBACK acmDriverEnumCallback( HACMDRIVERID hadid, DWORD dwInstance, DWORD fdwSupport )
{
	if( fdwSupport & ACMDRIVERDETAILS_SUPPORTF_CODEC ) 
	{
		MMRESULT mmr;
		
		ACMDRIVERDETAILS details;
		details.cbStruct = sizeof(ACMDRIVERDETAILS);
		mmr = acmDriverDetails( hadid, &details, 0 );
		if (mmr==MMSYSERR_NOERROR)
		{
			HACMDRIVER driver;
			mmr = acmDriverOpen( &driver, hadid, 0 );
			DWORD i;
			for(i = 0; i < details.cFormatTags; i++ )
			{
				ACMFORMATTAGDETAILS fmtDetails;
				ZeroMemory( &fmtDetails, sizeof(fmtDetails) );
				fmtDetails.cbStruct = sizeof(ACMFORMATTAGDETAILS);
				fmtDetails.dwFormatTagIndex = i;
				mmr = acmFormatTagDetails( driver, &fmtDetails, ACM_FORMATTAGDETAILSF_INDEX );
				TRACE("uuuuuuu %u \r\n",fmtDetails.dwFormatTag);
				if( fmtDetails.dwFormatTag == WAVE_FORMAT_ALAW   )
				{
					TRACE("11111111\r\n");
				}
			}
			mmr = acmDriverClose( driver, 0 );
			
		}
		return TRUE;
	}
	return TRUE;
}
	
DWORD	CAcmcodec::ChkCodec()
{
	CAcmcodec::bG711=FALSE;
	MMRESULT mmr=acmDriverEnum(acmDriverEnumCallback, 0, 0 );
	return mmr;
}