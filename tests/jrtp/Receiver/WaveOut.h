/*------------------------------------------------------------------------------*\
 [ģ������]
	CWaveOut

 [�ļ�����]
	CWaveOut.h

 [����ļ�]
	CWaveOut.cpp

 [Ŀ��]
 
     ������Ƶ����
     	  
 [����]
		
	��װ waveout api
	ֻʹ���� pcm ��ʽ
	
 [ע��]

	PLAY_DELAY 10	//����ʱ����ӳ٣���������˵����PLAY_DELAY����û�в�����ɣ�����İ���Ӧ�ٲ���

 [������]
	
	 Winmm.lib 
 
 [��Ȩ]
 
   2002.12 hb  ��Ȩ����

 [�޸ļ�¼]
 
  �汾:    1.01.01
  ����:    02-12-16  ~  02-12-17   
  ����:    hb
  Mial:		sendh@21cn.com
  ��ע:
                                               
\*------------------------------------------------------------------------------*/

#ifndef _WAVEOUT_H_
#define _WAVEOUT_H_

#define WOSA_POOR	8000
#define WOSA_LOW	11025
#define WOSA_NORMAL	22050
#define WOSA_HIGH	44100

#define PLAY_DELAY 10

#include <mmsystem.h>
#include <afxmt.h>
class CWaveOut  
{
public:
	static DWORD WINAPI AudioOutThreadProc(LPVOID lpParameter);
public:
	BOOL SetFormatByFile(CString file);
	BOOL Play(char* buf,UINT uSize);

	BOOL StartPlay();
	BOOL StopPlay();	

	inline int GetBufferNum();
	inline void BufferSub();
	inline void BufferAdd();

	inline DWORD GetInstance();
	inline WORD GetBit();
	inline DWORD GetSample();
	inline WORD GetChannel();

	inline void SetBit(WORD wBit);
	inline void SetSample(DWORD dwSample);
	inline void SetChannel(WORD wChannel);

	inline MMRESULT GetLastMMError();
	CString GetLastErrorString();

	CWaveOut();
	virtual ~CWaveOut();
protected:
	BOOL OpenDev();
	BOOL CloseDev();

	BOOL StopThread();
	BOOL StartThread();
protected:
	static DWORD s_dwInstance;
protected:
	WORD m_wChannel;
	DWORD m_dwSample;
	WORD m_wBit;
protected:
	MMRESULT m_mmr;
	HWAVEOUT m_hOut;
	HANDLE m_hAudioOut;
	DWORD m_dwAudioOutId;

	int m_iBufferNum;
	CCriticalSection m_csLock;

	BOOL m_bThreadStart;
	BOOL m_bDevOpen;
	friend DWORD WINAPI AudioOutThreadProc(LPVOID lpParameter);
};

#endif
