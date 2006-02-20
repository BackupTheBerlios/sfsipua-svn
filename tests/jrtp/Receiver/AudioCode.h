/*------------------------------------------------------------------------------*\
 [ģ������]
	CAudioCode

 [�ļ�����]
	AudioCode.h

 [����ļ�]
	AudioCode.cpp

 [Ŀ��]
 
     ������Ƶ��ѹ�� 
     	  
 [����]
		
	��װ g.729 api
	
 [������]
	
	 G729a.lib
 
 [��Ȩ]
 
   2002.12 hb  ��Ȩ����

 [�޸ļ�¼]
 
  �汾:    1.01.01
  ����:    02-12-17
  ����:    hb
  Mial:		sendh@21cn.com
  ��ע:
                                               
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