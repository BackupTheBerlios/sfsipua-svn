/*------------------------------------------------------------------------------*\
 [模块名称]
	CMixOut

 [文件名称]
	MixOut.h

 [相关文件]
	MixOut.cpp

 [目的]
 
    控制混音输出
     	  
 [描述]
		
	封装 mixer api

 [注意]

	你只应该使用本类一次，是由于窗口消息引起的
	设置，获取音量没有做
	数据质量为 1 channel,16bit,8000 sample

 [依赖性]

	winmm.lib
 
 [版权]
 
   2002.12 胡斌  版权所有

 [修改记录]
 
  版本:    1.01.01
  日期:    02-12-20 
  作者:    胡斌
  Mial:		sendh@21cn.com
  备注:
                                               
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
