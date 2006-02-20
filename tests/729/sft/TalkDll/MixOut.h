/*------------------------------------------------------------------------------*\
 [ģ������]
	CMixOut

 [�ļ�����]
	MixOut.h

 [����ļ�]
	MixOut.cpp

 [Ŀ��]
 
    ���ƻ������
     	  
 [����]
		
	��װ mixer api

 [ע��]

	��ֻӦ��ʹ�ñ���һ�Σ������ڴ�����Ϣ�����
	���ã���ȡ����û����
	��������Ϊ 1 channel,16bit,8000 sample

 [������]

	winmm.lib
 
 [��Ȩ]
 
   2002.12 ����  ��Ȩ����

 [�޸ļ�¼]
 
  �汾:    1.01.01
  ����:    02-12-20 
  ����:    ����
  Mial:		sendh@21cn.com
  ��ע:
                                               
\*------------------------------------------------------------------------------*/

#ifndef _MIXOUT_H_
#define _MIXOUT_H_

#include <mmsystem.h>

class CMixOut  
{
public:
	virtual void OnControlChanged(int iValue);
	BOOL UnIni();
	BOOL Ini();

	virtual DWORD	GetMinimalVolume();
	virtual DWORD	GetMaximalVolume();
	virtual DWORD	GetCurrentVolume();
	virtual void	SetCurrentVolume( DWORD dwValue );

	inline MMRESULT GetLastMMError();
	CString GetLastErrorString();

	CMixOut();
	virtual ~CMixOut();
protected:
	BOOL CloseMixer();
	BOOL OpenMixer();
	BOOL Initialize();
	static	LRESULT CALLBACK MixerWndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
protected:
	int m_iDevNum;
	HMIXER m_hMixer;
	UINT m_uiMixerId;

	DWORD	m_dwMinimalVolume;
	DWORD	m_dwMaximalVolume;

	BOOL m_bIni;
	MMRESULT m_mmr;
	HWND	m_hWnd;
};

#endif
