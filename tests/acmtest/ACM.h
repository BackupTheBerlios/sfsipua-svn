// ACM.h: interface for the CACM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACM_H__08D6FB76_BA9A_4E43_AB3F_C123D150C4FD__INCLUDED_)
#define AFX_ACM_H__08D6FB76_BA9A_4E43_AB3F_C123D150C4FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
#include <mmsystem.h>
#include <mmreg.h>
#include <Msacm.h>
//
typedef struct { BOOL bFind;
HACMDRIVER hDriver;
HACMDRIVERID hadid;
WORD wFormatTag;
WORD wIndex;
LPWAVEFORMATEX pwfx;
int iFormatSize;
}DRIVER_INFO;
//
class CACM
{
public:
	BOOL Decode(BYTE *pSrcEnc, DWORD dwSrcEncBufSize,DWORD dwSrcEncSize, BYTE *pDecData, DWORD *pdwDecSize);
	BOOL Encode(BYTE *pSrcWave, DWORD dwSrcBufSize, DWORD dwSrcRecSize, BYTE *pEncData, DWORD *pdwEncSize);
	//
	BOOL Start(HACMDRIVERID hid);
	BOOL OpenDecStream(LPWAVEFORMATEX pwfxSrc,LPWAVEFORMATEX pwfxDest);
	BOOL OpenEncStream(LPWAVEFORMATEX pwfxSrc,LPWAVEFORMATEX pwfxDest);
	void SetWaveFormat(LPWAVEFORMATEX pSrc,LPWAVEFORMATEX pDest);
	//
	static BOOL CALLBACK FindDriverEnum(HACMDRIVERID hadid, DWORD dwInstance, DWORD fdwSupport);
	static BOOL CALLBACK ACMFormatEnumProc(HACMDRIVERID hadid,LPACMFORMATDETAILS pafd,DWORD dwInstance,DWORD fdwSupport);
	BOOL FindDriver(HACMDRIVERID *phDid,WORD wFormatTag,WORD wIndex,LPWAVEFORMATEX pwfx,int iFormatSize);
	//
	int GetWaveMetrics();
	//
	CACM();
	virtual ~CACM();
	//
private:
	HACMDRIVER hDriver;
	HACMDRIVERID hadid;
	HACMSTREAM hEncStream,hDecStream;
	//
	int iWaveMetrics;
	LPWAVEFORMATEX pwfxSrc,pwfxDest;
	//
	DRIVER_INFO di;
	ACMSTREAMHEADER stEncStreamHead,stDecStreamHead;
};

//使用方法(略)
/*
WAVEFORMATEX *pwfxSrc,*pwfxDest;
int iWaveMetrics;
//
pCODEC=NULL;
pCODEC=(CACM *)new CACM();
iWaveMetrics=pCODEC->GetWaveMetrics();
SetWaveFormat(iWaveMetrics);
//
HACMDRIVERID hadid=NULL;
// BOOL bb=pCODEC->FindDriver(&hadid,WAVE_FORMAT_GSM610,0,pwfxDest,iWaveMetrics);
BOOL bb=pCODEC->FindDriver(&hadid,WAVE_FORMAT_DSPGROUP_TRUESPEECH,0,pwfxDest,iWaveMetrics);
if(bb){
pCODEC->SetWaveFormat(pwfxSrc,pwfxDest);
pCODEC->Start(hadid);
}

//
void CVoiceDlg::SetWaveFormat(int iMetrics)
{
pwfxSrc=(WAVEFORMATEX *)new BYTE[iMetrics];
memset(pwfxSrc,0,iMetrics);
pwfxDest=(WAVEFORMATEX *)new BYTE[iMetrics];
memset(pwfxDest,0,iMetrics);
//
pwfxSrc->cbSize = 0;
pwfxSrc->wFormatTag = WAVE_FORMAT_PCM;
pwfxSrc->nChannels = 1;
pwfxSrc->nSamplesPerSec = 8000;
pwfxSrc->wBitsPerSample = 16;
pwfxSrc->nBlockAlign = (pwfxSrc->nChannels * pwfxSrc->wBitsPerSample) / 8;
pwfxSrc->nAvgBytesPerSec= (pwfxSrc->nSamplesPerSec * pwfxSrc->nChannels * pwfxSrc->wBitsPerSample) / 8; 

  */
#endif // !defined(AFX_ACM_H__08D6FB76_BA9A_4E43_AB3F_C123D150C4FD__INCLUDED_)
