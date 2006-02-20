/*------------------------------------------------------------------------------*\
 [模块名称]
	CAudioCode

 [文件名称]
	AudioCode.h

 [相关文件]
	AudioCode.cpp

 [目的]
 
     方便音频解压缩 
     	  
 [描述]
		
	封装 g.729 api
	
 [依赖性]
	
	 G729a.lib
 
 [版权]
 
   2002.12 hb  版权所有

 [修改记录]
 
  版本:    1.01.01
  日期:    02-12-17
  作者:    hb
  Mial:		sendh@21cn.com
  备注:
                                               
\*------------------------------------------------------------------------------*/

#ifndef _AUDIOCODE_H_
#define _AUDIOCODE_H_

#define SIZE_AUDIO_FRAME 960
#define SIZE_AUDIO_PACKED 60

class CAudioCode
{
public:
	virtual  ~CAudioCode();
	CAudioCode();

	BOOL EncodeAudioData(char *pin,int len,char* pout,int* lenr);
	BOOL DecodeAudioData(char *pin,int len,char* pout,int* lenr);
};


#endif