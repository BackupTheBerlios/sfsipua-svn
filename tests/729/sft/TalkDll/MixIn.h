/*------------------------------------------------------------------------------*\
 [ģ������]
	CMixIn

 [�ļ�����]
	MixIn.h

 [����ļ�]
	MixIn.cpp

 [Ŀ��]
 
    ���ƻ�������
     	  
 [����]
		
	��װ mixer api

 [ע��]
	����ֻ��һ�����ʵ������豸��������·�ϴ�һ��mic����
	�����м�����һ�����ڣ�ע����Ӧ�Ĵ���
	��ֻӦ��ʹ�ñ���һ�Σ������ڴ�����Ϣ�����
	���ã���ȡ����û����
	��������Ϊ 1 channel,16bit,8000 sample
	
 [������]

	winmm.lib
 
 [��Ȩ]
 
   2002.12 ����  ��Ȩ����

 [�޸ļ�¼]
 
  �汾:    1.01.01
  ����:    02-12-19 ~ 02-12-20
  ����:    ����
  Mial:		sendh@21cn.com
  ��ע:
                                               
\*------------------------------------------------------------------------------*/

#ifndef _MIXIN_H_
#define _MIXIN_H_

#include <mmsystem.h>

class CMixIn  
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

	CMixIn();
	virtual ~CMixIn();
protected:
	BOOL OpenMixer();
	BOOL CloseMixer();
	BOOL Initialize(UINT uLineIndex);
	BOOL EnumerateInputLines(int &iUserValue);
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
