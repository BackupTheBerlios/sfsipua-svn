/*------------------------------------------------------------------------------*\
 [模块名称]
	CMixIn

 [文件名称]
	MixIn.h

 [相关文件]
	MixIn.cpp

 [目的]
 
    控制混音输入
     	  
 [描述]
		
	封装 mixer api

 [注意]
	本类只打开一个合适的输入设备，在其线路上打开一个mic输入
	本类中加入了一个窗口，注意相应的处理
	你只应该使用本类一次，是由于窗口消息引起的
	设置，获取音量没有做
	数据质量为 1 channel,16bit,8000 sample
	
 [依赖性]

	winmm.lib
 
 [版权]
 
   2002.12 胡斌  版权所有

 [修改记录]
 
  版本:    1.01.01
  日期:    02-12-19 ~ 02-12-20
  作者:    胡斌
  Mial:		sendh@21cn.com
  备注:
                                               
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
