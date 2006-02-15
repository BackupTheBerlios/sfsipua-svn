// Interface.h: interface for the CInterface class.
//
//////////////////////////////////////////////////////////////////////
/*------------------------------------------------------------------------------*\
 [ģ������]
	Interface

 [�ļ�����]
	Interface.h

 [����ļ�]
	Interface.cpp

 [Ŀ��]
 
     dll�Ľӿ�  
     	  
 [����]
	��Ӧ�����ش���

	����ĺ�����ʾ���������¼�
	virtual void TalkBeClose();				//ͨ�����ر���
	virtual void TalkStart(CString ip);		//ͨ����ʼ�ˣ�����Ҳ�ɹ�����
	virtual BOOL IsConnect(CString ip);		//�Է��������ӣ���ͬ��������
	virtual void TalkOnConnect(BOOL bRe);	//���ӳɹ�����

	BOOL Ini();						//��ʼ��
	BOOL End();						//����ͨ��
	BOOL Start(CString ip);			//��ʼͨ��
	
 [ע��]
	
 
 [��Ȩ]
 
   2002.12 hb  ��Ȩ���� 

 [�޸ļ�¼]
 
  �汾:    1.01.01
  ����:    02-12-10 ~ 02-12-20      
  ����:    hb
  Mial:	   sendh@21cn.com
  ��ע:
                                               
\*------------------------------------------------------------------------------*/


#if !defined(AFX_INTERFACE_H__DEB6C49D_7068_4289_9538_44E531D90376__INCLUDED_)
#define AFX_INTERFACE_H__DEB6C49D_7068_4289_9538_44E531D90376__INCLUDED_

class CMyWaveIn;
class CWaveOut;
class CListenSocket;
class CSendClient;
class CUdpSocket;
class CRecSocket;

class AFX_EXT_CLASS CInterface
{
public:
	virtual void TalkBeClose();
	virtual void TalkStart(CString ip);
	virtual BOOL IsConnect(CString ip);
	virtual void TalkOnConnect(BOOL bRe);

	BOOL Ini();
	BOOL End();
	BOOL Start(CString ip);

	CInterface();
	virtual ~CInterface();
protected:
	void BeClose();
	void ConnectResult(int nErrorCode);
protected:
	BOOL m_bIni;
	BOOL m_bWork;
	CString m_sIp;

	CMyWaveIn *m_pIn;
	CListenSocket *m_sopListen;
	CSendClient *m_sopSend;
	CUdpSocket *m_pUdp;
	CRecSocket *m_pRec;
	friend class CSendClient;
	friend class CClientSocket;
};

#endif // !defined(AFX_INTERFACE_H__DEB6C49D_7068_4289_9538_44E531D90376__INCLUDED_)
