#include "stdafx.h"
#include "SortData.h"
#include "head.h"
#include "AudioCode.h"
#include "WaveOut.h"

extern CAudioCode g_ACode;
extern CWaveOut *g_pOut;
CSortData::CSortData()
{
	for (int i = 0;i<NUM_BUFFER;i++)
	{
		m_pBuffer[i] = new char[60];
		m_iFill[i] = 0;
	}
	m_iLast = 0;
}

CSortData::~CSortData()
{
	for (int i = 0;i<NUM_BUFFER;i++)
	{
		delete []m_pBuffer[i];
	}
}

void CSortData::ReceiveData(char *pBuffer, int iLen)
{
	struct Frame *m_pFrame;
	m_pFrame = (struct Frame *)pBuffer;

	TRACE("Rece %d %d .\n",iLen,m_pFrame->iIndex );
	if (m_pFrame->iIndex < m_iLast + 1)
	{
		TRACE("Lost %d.\n",m_pFrame->iIndex);
	}

	if (m_pFrame->iIndex == m_iLast + 1)
	{
		unsigned __int32 iTemp;
		///play  //it is right next data in buffer 
		Play(pBuffer + sizeof(struct Frame),60);
		m_iLast = m_pFrame->iIndex ;
		TRACE("Receive and paly %d.\n",m_iLast);
		
		iTemp = m_pFrame->iIndex;
		int iNext;
		for (iNext= 0;iNext < DELAY_BUFFER;iNext ++)
		{
			if (m_iFill[iNext] != iTemp + 1)
				break;
			iTemp = m_iFill[iNext];
		}

		if (iNext != 0)
		{
			//paly right
			for (iTemp =0;iTemp < (unsigned int)iNext;iTemp ++)
			{
				Play(m_pBuffer[iTemp],60);
				TRACE("Play %d.\n",m_iFill[iTemp]);
				m_iFill[iTemp] = 0;
			}
			//move back
			int iHead;
			iHead = 0;
			for (iTemp = iNext;iTemp < DELAY_BUFFER;iTemp ++)
			{
				if (m_iFill[iTemp] != 0)
				{
					m_iFill[iHead] = m_iFill[iTemp];
					memcpy(m_pBuffer[iHead],m_pBuffer[iTemp],60);
					m_iFill[iTemp] = 0;
					iHead = 0;
				}
				else
				{
					break;
				}
			}
		}
	}

	int iNow;
	int iEnd;
	int iMove;
	for (iNow = 0;iNow < DELAY_BUFFER ;iNow++)
	{
		if (m_iFill[iNow] != 0)
		{
			//insert 
			if (m_iFill[iNow] > m_pFrame->iIndex)
			{
				for (iEnd = iNow;iEnd < DELAY_BUFFER;iEnd ++)
				{
					if (m_iFill[iEnd] == 0)
					{
						break;
					}
				}
				for (iMove = iEnd;iMove > iNow;iMove --)
				{
					m_iFill[iMove] = m_iFill[iMove - 1];
					memcpy(m_pBuffer[iMove],m_pBuffer[iMove - 1],60);
				}
				memcpy(m_pBuffer[iNow],pBuffer + sizeof(struct Frame),60);
				m_iFill[iNow] = m_pFrame->iIndex;
				break;
			}
		}//append
		else
		{
			memcpy(m_pBuffer[iNow],pBuffer + sizeof(struct Frame),60);
			m_iFill[iNow] = m_pFrame->iIndex;
			break;
		}
	}//buffer full 
	if (m_iFill[DELAY_BUFFER - 1] != 0)
	{
		m_iLast = m_iFill[DELAY_BUFFER - 1];
		for (iNow = 0;iNow < DELAY_BUFFER ;iNow++)
		{
			//paly all;
			Play(m_pBuffer[iNow],60);
			TRACE("Play %d.\n",m_iFill[iNow]);
			m_iFill[iNow] = 0;
		}
	}
}

void CSortData::Play(char *pBuffer, int iLen)
{
	int iOut;
	iOut = sizeof(m_cOut);
	g_ACode.DecodeAudioData (pBuffer,iLen,m_cOut,&iOut);
	g_pOut->Play (m_cOut,iOut);
}
