/*------------------------------------------------------------------------------*\
 [模块名称]
	CSortData

 [文件名称]
	SortData.h

 [相关文件]
	SortData.cpp

 [目的]
 
    管理数据，调整乱序包的顺序
     	  
 [描述]
		
 [注意]

	m_iLast是上次播放的数据标号
	主要是ReceiveData中的方法
				 |-----------------------|    |----------|
				 |.检查当前是否是下一个包| -->|是，播放  |
				 |-----------------------|    |----------|
				            |                      |
							| 不是                 |  
                            |                      | 
                 |----------------------|     |--------------------————|
				 |  按小->大插入合适位置|	  |从头检查缓冲中是否是连续的  |	
				 |----------------------|     |是则播放，并前移位置,退出   |
				            |                 |----------------------------|  
							|                               
				 |----------------------|                    
                 |检查是否缓冲满，满就  |     
				 |播放，并清空缓冲      |
                 |----------------------| 
   [版权]
 
   2002.12 胡斌  版权所有

 [修改记录]
 
  版本:    1.01.01
  日期:    02-12-22
  作者:    胡斌
  Mial:		sendh@21cn.com
  备注:
                                               
\*------------------------------------------------------------------------------*/


#ifndef _SORT_H_
#define _SORT_H_

#define DELAY_BUFFER 24
#define NUM_BUFFER 32
class CSortData
{
public:
	void Play(char *pBuffer,int iLen);
	void ReceiveData(char *pBuffer,int iLen);
	CSortData();
	virtual ~CSortData();
protected:
	char *m_pBuffer[NUM_BUFFER];
	unsigned __int32 m_iFill[NUM_BUFFER];
	unsigned __int32 m_iLast;

	char m_cOut[1024];
};

#endif