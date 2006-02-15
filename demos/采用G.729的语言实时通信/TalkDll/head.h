#ifndef _WAVE_H_
#define _WAVE_H_

#pragma pack(push, 1)
struct Frame
{
	unsigned __int32	iIndex;
	char cb[12];
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TalkFrame
{
	char cFlag[16];
	unsigned __int32 iCom;
	unsigned __int32 iLen;
};
#pragma pack(pop)

#define TALK_REC_PORT 10001
#define TALK_COM_PORT 10002

#define TC_NORMAL_TALK	0x1000
#define TC_AGREE_TALK	0x1001
#define TC_DISAGREE_TALK	0x1002
#endif