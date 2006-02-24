// ACM.cpp: implementation of the CACM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "acmtest.h"
#include "ACM.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CACM::CACM()
{
	hDriver=NULL;
	hadid=NULL;
	//
	hEncStream=NULL;
	hDecStream=NULL;
	//
	pwfxSrc=NULL;
	pwfxDest=NULL;
	iWaveMetrics=GetWaveMetrics();
	memset(&di,0,sizeof(di));
}

CACM::~CACM()
{
	if(pwfxSrc){
		delete []pwfxSrc;
		pwfxSrc=NULL;
	}
	if(pwfxDest){
		delete []pwfxDest;
		pwfxDest=NULL;
	}
	//
	if(hEncStream){
		::acmStreamClose(hEncStream,0);
		hEncStream=NULL;
	}
	if(hDecStream){
		::acmStreamClose(hDecStream,0);
		hDecStream=NULL;
	}
	//
	if(hDriver){
		::acmDriverClose(hDriver,0);
		hDriver=NULL;
	}
}

int CACM::GetWaveMetrics()
{
	int iSize=0;
	//
	MMRESULT mmr=::acmMetrics(NULL,ACM_METRIC_MAX_SIZE_FORMAT,&iSize);
	//
	pwfxSrc=(LPWAVEFORMATEX) new BYTE[iSize];
	pwfxDest=(LPWAVEFORMATEX) new BYTE[iSize];
	//
	return iSize;
}

void CACM::SetWaveFormat(LPWAVEFORMATEX pSrc,LPWAVEFORMATEX pDest)
{
	memcpy(pwfxSrc,pSrc,(pSrc->cbSize+sizeof(WAVEFORMATEX)));
	memcpy(pwfxDest,pDest,(pDest->cbSize+sizeof(WAVEFORMATEX)));
}

BOOL CACM::Start(HACMDRIVERID hid)
{
	hDriver=NULL;
	hadid=hid;
	//
	if(::acmDriverOpen(&hDriver,hadid,0)){
		AfxMessageBox("acmDriverOpen error!");
		return false;
	}
	//
	if(!OpenEncStream(pwfxSrc,pwfxDest))
		return false;
	//
	if(!OpenDecStream(pwfxDest,pwfxSrc))
		return false;
	//
	return true;
}

BOOL CACM::FindDriver(HACMDRIVERID *phDid,WORD wFormatTag,WORD wIndex,LPWAVEFORMATEX pwfx,int iFormatSize)
{
	di.bFind =false;
	di.hadid =NULL;
	di.wFormatTag =wFormatTag;
	di.wIndex =wIndex;
	di.pwfx =pwfx;
	di.iFormatSize =iFormatSize;
	//
	MMRESULT mmr=::acmDriverEnum(FindDriverEnum,(DWORD)(VOID*)&di,0);
	if(mmr){
		return false;
	}
	*phDid=di.hadid;
	//
	return di.bFind;
}

BOOL CALLBACK CACM::FindDriverEnum(HACMDRIVERID hadid, DWORD dwInstance, DWORD fdwSupport)
{
	DRIVER_INFO* pdi=(DRIVER_INFO*)dwInstance;
	//
	ACMDRIVERDETAILS dd;
	memset(&dd,0,sizeof(dd));
	dd.cbStruct=sizeof(dd);
	//
	MMRESULT mmr=0;
	HACMDRIVER had=NULL;
	//
	mmr=::acmDriverOpen(&had,hadid,0);
	if(mmr){
		return false;
	}
	pdi->hDriver=had;
	//
	DWORD dwSize=0;
	mmr=::acmMetrics(NULL,ACM_METRIC_MAX_SIZE_FORMAT,&dwSize);
	if(dwSize < sizeof(WAVEFORMATEX))
		dwSize=sizeof(WAVEFORMATEX);
	WAVEFORMATEX *pwf=(WAVEFORMATEX *)new BYTE[dwSize];
	memset(pwf,0,dwSize);
	// pwf->cbSize=LOWORD(dwSize)-sizeof(WAVEFORMATEX);
	// pwf->wFormatTag=WAVE_FORMAT_UNKNOWN;
	//
	ACMFORMATDETAILS fd;
	memset(&fd,0,sizeof(fd));
	fd.cbStruct=sizeof(fd);
	fd.pwfx = pwf;
	fd.cbwfx = dwSize;
	fd.dwFormatTag =WAVE_FORMAT_UNKNOWN;
	//
	mmr=::acmFormatEnum(had,&fd,ACMFormatEnumProc,(DWORD)pdi,0);
	delete []pwf;
	//
	mmr=::acmDriverClose(had,0);
	//
	return true;
}

BOOL CALLBACK CACM::ACMFormatEnumProc(HACMDRIVERID hadid,LPACMFORMATDETAILS pafd,DWORD dwInstance,DWORD fdwSupport)
{
	DRIVER_INFO* pdi=(DRIVER_INFO*)dwInstance;
	//
	MMRESULT mmr=0;
	if( (pafd->dwFormatTag)==(pdi->wFormatTag) &&
		(pafd->dwFormatIndex)==(pdi->wIndex) ){
		pdi->hadid=hadid;
		pdi->bFind=true;
		//
		ACMFORMATDETAILS afd;
		memset(&afd,0,sizeof(afd));
		//
		DWORD dwMaxSize=50;
		WAVEFORMATEX *pwf =(WAVEFORMATEX *)new BYTE[dwMaxSize];
		afd.cbStruct = sizeof(afd);
		afd.dwFormatTag = pdi->wFormatTag;
		afd.dwFormatIndex= pdi->wIndex;
		afd.pwfx = pwf;
		afd.cbwfx = dwMaxSize;
		afd.pwfx->wFormatTag=pdi->wFormatTag;
		mmr=::acmFormatDetails(pdi->hDriver,&afd,ACM_FORMATDETAILSF_INDEX);
		if(mmr){
			delete []pwf;
			return false;
		}
		memcpy(pdi->pwfx,afd.pwfx,(sizeof(WAVEFORMATEX)+afd.pwfx->cbSize));
		delete []pwf;
		//
		return false;
	}
	//
	return true;
}

BOOL CACM::OpenEncStream(LPWAVEFORMATEX pwfxSrc,LPWAVEFORMATEX pwfxDest)
{
	MMRESULT mmr=0;
	mmr=::acmStreamOpen(&hEncStream,hDriver,pwfxSrc,pwfxDest,NULL,NULL,0,ACM_STREAMOPENF_NONREALTIME);
	if(mmr){
		AfxMessageBox("acmStreamOpen error!");
		return false;
	}
	return true;
}

BOOL CACM::OpenDecStream(LPWAVEFORMATEX pwfxSrc,LPWAVEFORMATEX pwfxDest)
{
	MMRESULT mmr=0;
	mmr=::acmStreamOpen(&hDecStream,hDriver,pwfxSrc,pwfxDest,NULL,NULL,0,ACM_STREAMOPENF_NONREALTIME);
	if(mmr){
		AfxMessageBox("acmStreamOpen error!");
		return false;
	}
	return true;
}

BOOL CACM::Encode(BYTE *pSrcWave, DWORD dwSrcBufSize, DWORD dwSrcRecSize, BYTE *pEncData, DWORD *pdwEncSize)
{
	//
	MMRESULT mmr=0;
	DWORD dwDestSize=1024;
	//
	mmr=::acmStreamSize(hEncStream,dwSrcRecSize,&dwDestSize,ACM_STREAMSIZEF_SOURCE);
	if(mmr){
		AfxMessageBox("acmStreamSize error!");
		return false;
	}
	//Prepare Head
	stEncStreamHead.cbStruct =sizeof(ACMSTREAMHEADER);
	stEncStreamHead.fdwStatus =0;
	stEncStreamHead.pbSrc =pSrcWave;
	stEncStreamHead.cbSrcLength =dwSrcBufSize;
	stEncStreamHead.cbSrcLengthUsed =dwSrcRecSize;
	stEncStreamHead.pbDst =pEncData;
	stEncStreamHead.cbDstLength =(DWORD)(*pdwEncSize);
	stEncStreamHead.cbDstLengthUsed =0;//dwDestSize;
	mmr=::acmStreamPrepareHeader(hEncStream,&stEncStreamHead,0);
	if(mmr){
		AfxMessageBox("acmStreamPrepareHeader error!");
		return false;
	}
	//Convert Wave Data
	mmr=::acmStreamConvert(hEncStream,&stEncStreamHead,ACM_STREAMCONVERTF_START);
	if(mmr){
		AfxMessageBox("acmStreamConvert error!");
		*pdwEncSize=0;
		return false;
	}
	*pdwEncSize=stEncStreamHead.cbDstLengthUsed;
	//Unprepare Head
	mmr=::acmStreamUnprepareHeader(hEncStream,&stEncStreamHead,0);
	if(mmr){
		AfxMessageBox("acmStreamUnprepareHeader error!");
		return false;
	}
	//
	return true;
}

BOOL CACM::Decode(BYTE *pSrcEnc, DWORD dwSrcEncBufSize,DWORD dwSrcEncSize, BYTE *pDecData, DWORD *pdwDecSize)
{
	//
	MMRESULT mmr=0;
	DWORD dwDestSize=0;
	mmr=::acmStreamSize(hDecStream,dwSrcEncSize,&dwDestSize,ACM_STREAMSIZEF_SOURCE);
	if(mmr){
		AfxMessageBox("acmStreamSize error!");
		return false;
	}
	//Prepare Head
	stDecStreamHead.cbStruct =sizeof(ACMSTREAMHEADER);
	stDecStreamHead.fdwStatus =0;
	stDecStreamHead.pbSrc =pSrcEnc;
	stDecStreamHead.cbSrcLength =dwSrcEncSize;//dwSrcEncBufSize;
	stDecStreamHead.cbSrcLengthUsed =dwSrcEncSize;
	stDecStreamHead.pbDst =pDecData;
	stDecStreamHead.cbDstLength =(DWORD)(*pdwDecSize);
	stDecStreamHead.cbDstLengthUsed =0;
	mmr=::acmStreamPrepareHeader(hDecStream,&stDecStreamHead,0);
	if(mmr){
		AfxMessageBox("acmStreamPrepareHeader error!");
		return false;
	}
	//Convert Wave Data
	mmr=::acmStreamConvert(hDecStream,&stDecStreamHead,ACM_STREAMCONVERTF_START);
	if(mmr){
		AfxMessageBox("acmStreamConvert error!");
		*pdwDecSize=0;
		return false;
	}
	*pdwDecSize=stDecStreamHead.cbDstLengthUsed;
	//Unprepare Head
	mmr=::acmStreamUnprepareHeader(hDecStream,&stDecStreamHead,0);
	if(mmr){
		AfxMessageBox("acmStreamUnprepareHeader error!");
		return false;
	}
	//
	return true;
}

