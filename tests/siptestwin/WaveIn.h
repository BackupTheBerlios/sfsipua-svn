/*------------------------------------------------------------------------------*\
 [ģ������]
	CWaveIn

 [�ļ�����]
	WaveIn.h

 [����ļ�]
	WaveIn.cpp

 [Ŀ��]
 
     ������Ƶ�ɼ�  
     	  
 [����]
		
	��װ wavein api
	ֻʹ���� pcm ��ʽ
	ֻʹ�� �����ص���ʽ
	���е��������Եĺ���ֻӦ��¼��ǰʹ�ã����߻����´�¼��ʱ����Ч
	Ӧ������ virtual void GetData(char *pBuffer,int iLen);
	
 [ע��]
	���� StartRecord �е�PerPareBuffer() OpenRecord()�Ǻ�Ӧ��ͬʱ���ã�
	Ҫô�Ͷ������ã���ԭ������� waveInAddBuffer ֮����� ʹ��saveInStart
	��������ܹر��豸
	SIZE_AUDIO_FRAME �� 160 ����
	SIZE_AUDIO_PACKED �� ��Ӧ����� Ϊ SIZE_AUDIO_FRAME / 160 * 10
	�رյ�ʱ��ע�⣬��closerecord���п����߳��л������ݵ��������¹رղ���ȷ�����Թرյ�ʱ��sleep(1000),��ϸԭ����Ҳ��̫���
 
 [������]
	
	 Winmm.lib 
 
 [��Ȩ]
 
   2002.12 hb  ��Ȩ���� 

 [�޸ļ�¼]
 
  �汾:    1.01.01
  ����:    02-12-13 ~ 02-12-16      
  ����:    hb
  Mial:		sendh@21cn.com
  ��ע:
                                               
\*------------------------------------------------------------------------------*/

#ifndef _WAVEIN_H_
#define _WAVEIN_H_
#define WISA_POOR	8000
#define WISA_LOW	11025
#define WISA_NORMAL	22050
#define WISA_HIGH	44100

#define NUM_BUF 10
#define SIZE_AUDIO_FRAME 960
#define SIZE_AUDIO_PACKED 60
#include <mmsystem.h>
#include <afxmt.h>
#include "M:/sips/jrtp/jrtplib-2.9/rtpsession.h"
#include "M:/sips/jrtp/jrtplib-2.9/rtppacket.h"

class CWaveIn
{
public:
	RTPSession sess;
	static DWORD WINAPI AudioInThreadProc(LPVOID lpParameter);
	int portt;
	int t;
	int nPT ;
	int nTSTAMP;
public:
	void SetPort(int port);
	virtual void GetData(char *pBuffer,int iLen);

	BOOL StartRec();
	BOOL StopRec();

	inline DWORD GetInstance();
	inline WORD GetBit();
	inline DWORD GetSample();
	inline WORD GetChannel();
	CCriticalSection m_soLock;
	char m_cBufOut[1024];
	inline void SetBit(WORD wBit);
	inline void SetSample(DWORD dwSample);
	inline void SetChannel(WORD wChannel);

	inline MMRESULT GetLastMMError();
	CString GetLastErrorString();
	
	CWaveIn();
	virtual ~CWaveIn();	
protected:
	BOOL OpenDev();
	BOOL CloseDev();

	BOOL StopThread();
	BOOL StartThread();

	BOOL PerPareBuffer();
	BOOL FreeBuffer();

	BOOL OpenRecord();
	BOOL CloseRecord();
protected:
	static DWORD s_dwInstance;
protected:
	WORD m_wChannel;
	DWORD m_dwSample;
	WORD m_wBit;

protected:
	HWAVEIN m_hIn;
	MMRESULT m_mmr;
	DWORD m_dwAudioInId;
	HANDLE m_hAudioIn;
	WAVEHDR* m_pHdr;

	BOOL m_bThreadStart;
	BOOL m_bDevOpen;
	BOOL m_bAllocBuffer;
	BOOL m_bRecord;
};

#endif