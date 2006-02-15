// Interface.h: interface for the CInterface class.
//
//////////////////////////////////////////////////////////////////////
/*------------------------------------------------------------------------------*\
 [模块名称]
	Interface

 [文件名称]
	Interface.h

 [相关文件]
	Interface.cpp

 [目的]
 
     dll的接口  
     	  
 [描述]
	你应该重载此类

	下面的函数表示有这样的事件
	virtual void TalkBeClose();				//通话被关闭了
	virtual void TalkStart(CString ip);		//通话开始了，语音也成功传送
	virtual BOOL IsConnect(CString ip);		//对方发起连接，你同意连接吗
	virtual void TalkOnConnect(BOOL bRe);	//连接成功了吗

	BOOL Ini();						//初始化
	BOOL End();						//结束通话
	BOOL Start(CString ip);			//开始通话
	
 [注意]
	
 
 [版权]
 
   2002.12 hb  版权所有 

 [修改记录]
 
  版本:    1.01.01
  日期:    02-12-10 ~ 02-12-20      
  作者:    hb
  Mial:	   sendh@21cn.com
  备注:
                                               
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
