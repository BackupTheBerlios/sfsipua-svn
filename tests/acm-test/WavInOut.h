/* 
 * Copyright (C) 2000-2001 Computer & Communications Research Laboratories,
 *			   Industrial Technology Research Institute
 */
/* 
 * WavInOut.h
 *
 * $Id: WavInOut.h,v 1.3 2001/06/21 01:38:05 hchsu Exp $ 
 */
#if !defined(AFX_WAVEINOUT_H__9D448199_1A2F_4630_B173_51B6940A8E6F__INCLUDED_)
#define AFX_WAVEINOUT_H__9D448199_1A2F_4630_B173_51B6940A8E6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __WAVINOUT__
#define __WAVINOUT__

#include <Mmsystem.h>
#include <mmreg.h>
#include <process.h>
#pragma comment(lib,"winmm")
#define WAVIN_BUFFER_BLOCKS 50
#define WAVOUT_BUFFER_BLOCKS 50


typedef enum {
	WAV_PCMU = 0x0,
	WAV_PCMA = 0x8,
	WAV_GSM = 0x3
} WAV_FORMATE;


class WavInOut
{
private:
	MMRESULT ret;

protected:
	static WavInOut *pWavInOut;

	unsigned int wavin_buflen;
	unsigned int wavout_buflen;

	UINT wavIn_devID;
	UINT wavOut_devID;

	WAVEFORMATEX format_wavIn;
	WAVEFORMATEX format_wavOut;

	unsigned short StopRecording;
	unsigned short StopPlaying;

	HWAVEIN handle_wi;
	HWAVEOUT handle_wo;

	WAVEHDR header_wi[WAVIN_BUFFER_BLOCKS];
	WAVEHDR header_wo[WAVOUT_BUFFER_BLOCKS];

	unsigned threadRecordId;
	unsigned threadPlayId;
	HANDLE hthreadRecord;
	HANDLE hthreadPlay;

public:
	BOOL isWavInOpen;
	BOOL isWavOutOpen;

	static WavInOut *instance() {
		if (pWavInOut == 0)
			pWavInOut = new WavInOut();
		return pWavInOut;
	}

	WavInOut();
	virtual ~WavInOut();

	void init(int (*cbBufferWrite)(char*,int), int (*cbBufferRead)(char*,int) );

	int wavInOpen(WAV_FORMATE Format, WORD BitsPerSample, DWORD SamplesPerSec, WORD Channels, UINT PacketizePeriod);
	int wavInClose();

	int wavOutOpen(WAV_FORMATE Format, WORD BitsPerSample, DWORD SamplesPerSec, WORD Channels, UINT PacketizePeriod);
	int wavOutClose();

	int startRecording();
	int startPlaying();

	int stopRecording();
	int stopPlaying();

	// playSound :
	int playSound(LPCSTR lpszSound, UINT fuSound); // the same with system Waveform function [sndPlaySound]
	int stopPlaySound();

	//void operator delete(void* wavio);

protected:

	int (*CBBufferWrite)(char* buff,int len);
	int (*CBBufferRead)(char* buff,int len);

	static void CALLBACK WavInOut::waveInProc(	HWAVEIN hwi,      
												UINT uMsg,         
												DWORD dwInstance,  
												DWORD dwParam1,    
												DWORD dwParam2);

	static void CALLBACK WavInOut::waveOutProc(	HWAVEIN hwi,       
												UINT uMsg,         
												DWORD dwInstance,  
												DWORD dwParam1,    
												DWORD dwParam2);

	static unsigned _stdcall _threadRecording(void* data);
	static unsigned _stdcall _threadPlaying(void* data);

};


#endif /*__WAVINOUT__*/
#endif // !defined(AFX_WAVEINOUT_H__9D448199_1A2F_4630_B173_51B6940A8E6F__INCLUDED_)