/* 
 * Copyright (C) 2000-2001 Computer & Communications Research Laboratories,
 *			   Industrial Technology Research Institute
 */
/*
 * WavInOut.cpp
 *
 * $Id: WavInOut.cpp,v 1.3 2001/06/21 01:31:35 hchsu Exp $
 */
#include "stdafx.h"

#include "WavInOut.h"

WavInOut *WavInOut::pWavInOut = 0;
CRITICAL_SECTION wavio_cs;

WavInOut::WavInOut()
{
	InitializeCriticalSection(&wavio_cs);
	isWavInOpen = FALSE;
	isWavOutOpen = FALSE;
};


WavInOut::~WavInOut()
{
	stopPlaySound();

	stopRecording();
	stopPlaying();
	wavOutClose();
	wavInClose();

	DeleteCriticalSection(&wavio_cs);

	WavInOut::pWavInOut = 0;
};

void WavInOut::init(int (*cbBufferWrite)(char*,int), int (*cbBufferRead)(char*,int) )
{
	__try {
		EnterCriticalSection(&wavio_cs);

		CBBufferWrite = cbBufferWrite;
		CBBufferRead = cbBufferRead;

		pWavInOut->wavin_buflen = 0;
		pWavInOut->wavout_buflen = 0;

		wavIn_devID = WAVE_MAPPER;
		wavOut_devID = WAVE_MAPPER;

		StopRecording = 0;
		StopPlaying = 0;

		hthreadRecord = 0;
		hthreadPlay = 0;

		handle_wi = 0;
		handle_wo = 0;
	}
	__finally {
		LeaveCriticalSection(&wavio_cs);
	}
};


void CALLBACK WavInOut::waveInProc(
  HWAVEIN hwi,       
  UINT uMsg,         
  DWORD dwInstance,  
  DWORD dwParam1,    
  DWORD dwParam2     
)
{
	LPWAVEHDR hdr;
	int len;

	switch(uMsg) {
	case WIM_DATA:
		hdr = (LPWAVEHDR)dwParam1;
		len = pWavInOut->CBBufferWrite(hdr->lpData,hdr->dwBytesRecorded);
		break;
	case WIM_CLOSE:
		pWavInOut->isWavInOpen = FALSE;
		break;
	case WIM_OPEN:
		pWavInOut->isWavInOpen = TRUE;
		break;
	default:
		break;
	}
}

int WavInOut::wavInOpen(WAV_FORMATE Format, WORD BitsPerSample, DWORD SamplesPerSec, WORD Channels, UINT PacketizePeriod)
{
	GSM610WAVEFORMAT gsm;
	if(handle_wi!=0)
		return -1;

	__try {
		EnterCriticalSection(&wavio_cs);

		if( Format==WAV_GSM ) {
			gsm.wSamplesPerBlock = 320;
			gsm.wfx.cbSize = 2;
			gsm.wfx.nAvgBytesPerSec = 1625;
			gsm.wfx.nBlockAlign = 65;
			gsm.wfx.nChannels = 1;
			gsm.wfx.nSamplesPerSec = 8000;
			gsm.wfx.wBitsPerSample = 0;
			gsm.wfx.wFormatTag = WAVE_FORMAT_GSM610;
		}
		else if ( Format==WAV_PCMU || Format==WAV_PCMA ) {
			format_wavIn.cbSize = 0;
			format_wavIn.nAvgBytesPerSec = (BitsPerSample/8)*SamplesPerSec;
			format_wavIn.nBlockAlign = Channels*BitsPerSample/8;
			format_wavIn.nChannels = Channels;
			format_wavIn.nSamplesPerSec = SamplesPerSec;
			format_wavIn.wBitsPerSample = BitsPerSample;
			format_wavIn.wFormatTag = ((Format==WAV_PCMU)?WAVE_FORMAT_MULAW:WAVE_FORMAT_ALAW);
		}
		else
			return -1;


		this->wavin_buflen = (Format!=WAV_GSM)?
			PacketizePeriod*format_wavIn.nAvgBytesPerSec/1000:
			320;

		
		if( Format!=WAV_GSM ) 
			ret = waveInOpen(&handle_wi,wavIn_devID,&format_wavIn,(unsigned int)WavInOut::waveInProc,0L,CALLBACK_FUNCTION );
		else
			ret = waveInOpen(&handle_wi,(UINT)WAVE_MAPPER,(WAVEFORMATEX*)&(gsm.wfx),(unsigned int)WavInOut::waveInProc,0L,CALLBACK_FUNCTION );
		if( ret != MMSYSERR_NOERROR ) {
			return -1;
		}

		int waitCounter = 0;
		while(!isWavInOpen) {
			if(waitCounter>100)
				return -1;
			Sleep(10);
			waitCounter++;
		}
	}
	__finally {
		LeaveCriticalSection(&wavio_cs);
	}

	return 0;
};


int WavInOut::wavInClose()
{
	if(handle_wi==0)
		return -1;

	__try {
		EnterCriticalSection(&wavio_cs);
		ret = waveInClose(handle_wi);
		if( ret != MMSYSERR_NOERROR ) 
			return -1;
		
		handle_wi = 0;
	}
	__finally {
		LeaveCriticalSection(&wavio_cs);
	}

	return 0;
};

void CALLBACK WavInOut::waveOutProc(
  HWAVEIN hwi,       
  UINT uMsg,         
  DWORD dwInstance,  
  DWORD dwParam1,    
  DWORD dwParam2     
)
{
//	LPWAVEHDR hdr;
//	int len;

	switch(uMsg) {
	case WOM_DONE:	
		break;
	case WOM_CLOSE:
		pWavInOut->isWavOutOpen = FALSE;
		break;
	case WOM_OPEN:
		pWavInOut->isWavOutOpen = TRUE;
		break;
	default:
		break;
	}
}

int WavInOut::wavOutOpen(WAV_FORMATE Format, WORD BitsPerSample, DWORD SamplesPerSec, WORD Channels, UINT PacketizePeriod)
{
	GSM610WAVEFORMAT gsm;

	if(handle_wo!=0)
		return -1;

	__try {
		EnterCriticalSection(&wavio_cs);
	
		if( Format==WAV_GSM ) {
			gsm.wSamplesPerBlock = 320;
			gsm.wfx.cbSize = 2;
			gsm.wfx.nAvgBytesPerSec = 1625;
			gsm.wfx.nBlockAlign = 65;
			gsm.wfx.nChannels = 1;
			gsm.wfx.nSamplesPerSec = 8000;
			gsm.wfx.wBitsPerSample = 0;
			gsm.wfx.wFormatTag = WAVE_FORMAT_GSM610;
		}
		else if ( Format==WAV_PCMU || Format==WAV_PCMA ) {
			format_wavOut.cbSize = 0;
			format_wavOut.nAvgBytesPerSec = (BitsPerSample/8)*SamplesPerSec;
			format_wavOut.nBlockAlign = Channels*BitsPerSample/8;
			format_wavOut.nChannels = Channels;
			format_wavOut.nSamplesPerSec = SamplesPerSec;
			format_wavOut.wBitsPerSample = BitsPerSample;
			format_wavOut.wFormatTag = ((Format==WAV_PCMU)?WAVE_FORMAT_MULAW:WAVE_FORMAT_ALAW);
		}
		else
			return -1;

		this->wavout_buflen = (Format!=WAV_GSM)?
			PacketizePeriod*format_wavOut.nAvgBytesPerSec/1000:
			320;

		if( Format!=WAV_GSM ) 
			ret = waveOutOpen(&handle_wo,wavOut_devID,&format_wavOut,(unsigned int)WavInOut::waveOutProc,0L,CALLBACK_FUNCTION  );
		else
			ret = waveOutOpen(&handle_wo,(UINT)WAVE_MAPPER,&(gsm.wfx),(unsigned int)WavInOut::waveOutProc,0L,CALLBACK_FUNCTION );
		if( ret != MMSYSERR_NOERROR ) {
			return -1;
		}

		int waitCounter = 0;
		while(!isWavOutOpen) {
			if(waitCounter>100)
				return -1;
			Sleep(10);
			waitCounter++;
		}
	}
	__finally {
		LeaveCriticalSection(&wavio_cs);
	}

	return 0;
};


int WavInOut::wavOutClose()
{
	if(handle_wo==0)
		return -1;

	__try {
		EnterCriticalSection(&wavio_cs);
		ret = waveOutClose(handle_wo);
		if( ret != MMSYSERR_NOERROR ) 
			return -1;
		
		handle_wo = 0;
	}
	__finally {
		LeaveCriticalSection(&wavio_cs);
	}

	return 0;
};


int WavInOut::startRecording()
{
	if(handle_wi==0||hthreadRecord)
		return -1;

	__try {
		EnterCriticalSection(&wavio_cs);
		StopRecording = 0;

		for(int i=0; i<WAVIN_BUFFER_BLOCKS; i++)
			header_wi[i].lpData = (char*)malloc(wavin_buflen);

		hthreadRecord = (HANDLE)_beginthreadex(0, 0, _threadRecording, NULL, CREATE_SUSPENDED, &threadRecordId);
		if(hthreadRecord == INVALID_HANDLE_VALUE) 
			return -1;
		
		ResumeThread(hthreadRecord);
	}
	__finally {
		LeaveCriticalSection(&wavio_cs);
	}

	return 0;
};


int WavInOut::startPlaying()
{
	if(handle_wo==0||hthreadPlay!=0)
		return -1;

	__try {
		EnterCriticalSection(&wavio_cs);
		StopPlaying = 0;

		for(int i=0; i<WAVOUT_BUFFER_BLOCKS; i++)
			header_wo[i].lpData = (char*)malloc(wavout_buflen);

		hthreadPlay = (HANDLE)_beginthreadex(0, 0, _threadPlaying, NULL, CREATE_SUSPENDED, &threadPlayId);
		if(hthreadPlay == INVALID_HANDLE_VALUE) 
			return -1;
		
		ResumeThread(hthreadPlay);
	}
	__finally {
		LeaveCriticalSection(&wavio_cs);
	}

	return 0;
};



int WavInOut::stopRecording()
{
	if(hthreadRecord==0)
		return -1;

	__try {
		EnterCriticalSection(&wavio_cs);
		StopRecording = 1;

		if( WaitForSingleObject(hthreadRecord,INFINITE)==WAIT_TIMEOUT ) {
			TerminateThread(hthreadRecord,0);
		}
		CloseHandle(hthreadRecord);
		hthreadRecord = 0;

		waveInStop(pWavInOut->handle_wi);

		for(int i=0; i<WAVIN_BUFFER_BLOCKS; i++)
			free(header_wi[i].lpData);	
	}
	__finally {
		LeaveCriticalSection(&wavio_cs);
	}

	return 0;
};


int WavInOut::stopPlaying()
{
	if(hthreadPlay==0)
		return -1;

	__try {
		EnterCriticalSection(&wavio_cs);
		//waveOutReset(pWavInOut->handle_wo);
		StopPlaying = 1;

		if( WaitForSingleObject(hthreadPlay,INFINITE)==WAIT_TIMEOUT ) {
			TerminateThread(hthreadPlay,0);
		}
		CloseHandle(hthreadPlay);
		hthreadPlay = 0;

		for(int i=0; i<WAVOUT_BUFFER_BLOCKS; i++)
			free(header_wo[i].lpData);
	}
	__finally {
		LeaveCriticalSection(&wavio_cs);
	}

	return 0;
};

int WavInOut::playSound(LPCSTR lpszSound, UINT fuSound)
{
	return (sndPlaySound(lpszSound,fuSound))?0:-1;
};

int WavInOut::stopPlaySound()
{
	return (sndPlaySound(NULL,0))?0:-1;
};

unsigned _stdcall WavInOut::_threadRecording(void* data)
{
	int i,j;
	MMRESULT err;
	
	for(i=0;i<WAVIN_BUFFER_BLOCKS;i++) {
		pWavInOut->header_wi[i].dwBufferLength = pWavInOut->wavin_buflen;
		pWavInOut->header_wi[i].dwFlags = 0;
		pWavInOut->header_wi[i].dwBytesRecorded = 0;
	}

	err = waveInStart(pWavInOut->handle_wi);
	if( err != MMSYSERR_NOERROR ) {
		printf("waveInStart fail!!\n");
		return -1;
	}

	i = 0; j = 0;
	while(pWavInOut->StopRecording==0) {

		err = waveInPrepareHeader(pWavInOut->handle_wi,&pWavInOut->header_wi[i],sizeof(WAVEHDR));
		if( err != MMSYSERR_NOERROR ) {
			printf("waveInPrepareHeader fail!!\n");
			return -1;
		}
		err = waveInAddBuffer(pWavInOut->handle_wi,&pWavInOut->header_wi[i],sizeof(WAVEHDR));
		if( err != MMSYSERR_NOERROR ) {
			printf("waveInAddBuffer fail!!\n");
			return -1;
		}

		i = (++i)%WAVOUT_BUFFER_BLOCKS; j++;
		if(j<WAVIN_BUFFER_BLOCKS) continue;

		while((pWavInOut->header_wi[i].dwFlags&WHDR_DONE)!=WHDR_DONE) {
			if(pWavInOut->StopRecording==0)
				Sleep(5);
			else
				goto RECORD_STOP;
		}
		err = waveInUnprepareHeader(pWavInOut->handle_wi,&pWavInOut->header_wi[i],sizeof(WAVEHDR));
		if( err != MMSYSERR_NOERROR ) {
			printf("waveInUnprepareHeader fail!!\n");
		}
		pWavInOut->header_wi[i].dwFlags = 0;
		pWavInOut->header_wi[i].dwBytesRecorded = 0;

	}

RECORD_STOP:
	if( waveInReset(pWavInOut->handle_wi)!=MMSYSERR_NOERROR )
		printf("waveInReset fail!!\n");
	for(i=0;i<WAVIN_BUFFER_BLOCKS;i++) {
		//if((pWavInOut->header_wi[i].dwFlags&WHDR_DONE)==WHDR_DONE) {
		err = waveInUnprepareHeader(pWavInOut->handle_wi,&pWavInOut->header_wi[i],sizeof(WAVEHDR));
		if( err != MMSYSERR_NOERROR ) {
			printf("waveInUnprepareHeader2 fail!!\n");
		}
		//}
	}

	return 0;
};


unsigned _stdcall WavInOut::_threadPlaying(void* data)
{
	int i,j,len,reverse = 0;
	MMRESULT err;

	for(i=0;i<WAVOUT_BUFFER_BLOCKS;i++) {
		pWavInOut->header_wo[i].dwFlags = 0;
		pWavInOut->header_wo[i].dwBufferLength = pWavInOut->wavout_buflen;
	}

	i = 1; j = 0;
	while(pWavInOut->StopPlaying==0) {	
		len = pWavInOut->CBBufferRead(pWavInOut->header_wo[i].lpData,pWavInOut->wavout_buflen);
		if(len<=0) {
			if(pWavInOut->StopPlaying==0) {
				Sleep(1);	continue;
			}
			else
				goto PLAY_STOP;
		}
		pWavInOut->header_wo[i].dwFlags = 0;

		err = waveOutPrepareHeader(pWavInOut->handle_wo,&pWavInOut->header_wo[i],sizeof(WAVEHDR));
		if( err != MMSYSERR_NOERROR ) {
			printf("waveOutPrepareHeader fail!!\n");
		}

		err = waveOutWrite(pWavInOut->handle_wo,&pWavInOut->header_wo[i],sizeof(WAVEHDR));
		if( err != MMSYSERR_NOERROR ) {
			printf("waveOutWrite fail!! i=%d\n",i);
		}

		i = (++i)%WAVOUT_BUFFER_BLOCKS; j++;
		if( j<WAVOUT_BUFFER_BLOCKS )	continue;

		// wait wile the iTH header_wo is played
		while( (pWavInOut->header_wo[i].dwFlags&WHDR_DONE)!=WHDR_DONE && pWavInOut->StopPlaying==0 )
			Sleep(1);

		err = waveOutUnprepareHeader(pWavInOut->handle_wo,&pWavInOut->header_wo[i],sizeof(WAVEHDR));
		if( err != MMSYSERR_NOERROR ) {
			printf("waveOutUnprepareHeader fail i=%d!!\n",i);
		}
	}

PLAY_STOP:
	if( waveOutReset(pWavInOut->handle_wo)!=MMSYSERR_NOERROR )
		printf("waveOutReset error!!\n");
	for(i=0;i<WAVOUT_BUFFER_BLOCKS;i++) {
		//if((pWavInOut->header_wo[i].dwFlags&WHDR_DONE)==WHDR_DONE) {
		err = waveOutUnprepareHeader(pWavInOut->handle_wo,&pWavInOut->header_wo[i],sizeof(WAVEHDR));
		if( err != MMSYSERR_NOERROR ) {
			printf("waveInUnprepareHeader2 fail!!\n");
		}
		//}
	}

	return 0;
};
