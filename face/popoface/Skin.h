// Skin.h: interface for the CSkin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKIN_H__F795F6DF_EBE1_4FD7_A0D7_8A37E95E6D06__INCLUDED_)
#define AFX_SKIN_H__F795F6DF_EBE1_4FD7_A0D7_8A37E95E6D06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
void PaintGradiantRect(CDC *pDC, const RECT &rect,
	COLORREF clrFrom, COLORREF clrTo =RGB(255,255,255), 
	BOOL hori = true, BOOL ascend = true);

void DrawColorCube(CDC* pDC, CRect& rect, 
	COLORREF colorFrom, COLORREF colorTo /*= RGB(255,255,255)*/, 
	BOOL IsHori /*= true*/);


class CSkin  
{
public:
	CString Title;			//MSN���;   		�������Ʋ��ܳ���256���ַ�(128�����ĺ��֣�256��Ӣ����ĸ��
	COLORREF MainBk;		//1,72,178;       	������RGBɫ��ɫ���м��á�,���ָ�
	COLORREF MainBorder;   		//1,72,178;        	�������߿�RGBɫ��ɫ���м��á�,���ָ�
	COLORREF TreeGroupColor;	//192,192,192;		���ؼ������������ɫ
	HBITMAP  MainIcon; 		//MainIcon.bmp;         �������ϵ�����Iconͼ��16��16����9��
	HBITMAP  MainBkImg;     	//MainBk.bmp;           �������ϵı���ͼ
	HBITMAP  MainStatus;		//BigStatus.bmp;	״̬ͼ��һ���ļ�����3�飬ÿ��״̬��7��ͼ, 32*32
	HBITMAP  SmallStatus;		//smallIcon.bmp;	С��״̬ͼ��һ���ļ�����������, 16 * 16��ǰ����ÿ��7��
					//			;��һ�鹲5����Ϊ����״̬��Maskͼ��
	HBITMAP  TabBkPhoto;   		//TabBk.bmp;          	Tab�İ�ť�ı���ͼ��һ���ļ���������, ��Ϊ����ͷǼ���״̬							;ǰ������Ϊ����/�Ǽ���״̬�ı���ͼ������3���ǵڶ���Tab��3��״̬��ÿ��39 * 69
	HBITMAP  Corner;		//conner.bmp;		//�߽�ͼ�������飬8��ͼ��ÿ��ͼ��8��8
	COLORREF MaxMinBarColor;	//140,170,230;      	�����롱������ɫ
	COLORREF ShortCutBkColor;   	//241,239,231;       	��������ڵı�����ɫ
	HBITMAP  ShortCutMenuIcon;	//ShortMenu.bmp;         ������Ĳ˵�ͼ�� 16*16����5��

	COLORREF DragWndFirstLine[3]; 	//156, 207, 156;	//�ҵ�״̬���ڵ�һ���ߵĵ�һ����ɫ���������ߣ�ÿ����������ɫ��
	COLORREF DragWndSecLine[3]; 	//49, 154, 206;		//�ҵ�״̬���ڵڶ����ߵĵ�һ����ɫ���������ߣ�ÿ����������ɫ��
	COLORREF DragWndThrLine[3]; 	//247, 162, 16;		//�ҵ�״̬���ڵ������ߵĵ�һ����ɫ���������ߣ�ÿ����������ɫ��
	COLORREF DragWndFourLine[3]; 	//255, 255, 49;		//�ҵ�״̬���ڵ�4���ߵĵ�һ����ɫ���������ߣ�ÿ����������ɫ��

	HBITMAP  DragMenuPhoto;		//Ntes.bmp;		//�ҵ�״̬�����ϵġ����ס�ͼƬ�� 88��30
	HBITMAP  NotifyUserAnimate;	//Animate.bmp;		//��������ʱ�Ķ���ÿ��16 * 16�������飬5����ʹ�ñ�׼��16ɫ
					//			;ǰ3����ʾ�������ߵĶ������������ǵ�¼����
	COLORREF MsgWndEdgeClr;		//1,72,178;		//��Ϣ���ڱ�����ɫ
	COLORREF MsgWndPropTextIMClr; 	//179,200,232;		//��Ϣ������ʾ�ı�����ʾIM��Ϣ����ɫ
	COLORREF MsgWndPropTextSMSClr; 	//179,200,232;		//��Ϣ������ʾ�ı�����ʾSMS��Ϣ����ɫ
	COLORREF MsgWndToolBarBGClr;	//214,223,247;		//��Ϣ����ˮƽ����������ɫ
	COLORREF MsgWndSpaceTopLeftClr;	//139,169,229;		//��Ϣ�������½ǿհ��������Ͻ���ɫ
	COLORREF MsgWndSpaceBottomRightClr;//100,135,220; 	//��Ϣ�������½ǿհ��������½���ɫ
	COLORREF MsgWndVertBarClr;	//241,239,231;		//��Ϣ���ڲ��������������ɫ
	HBITMAP  MsgWndIcon; 		//SendMsgIcon.bmp;	//��Ϣ����ͼ�꣬��11��,16*16
	COLORREF TreeBkColor;		//255,255,255;		//���ؼ��ı�����ɫ

	HBITMAP  Tab2Bmp;		//tab2.bmp;		//�ڶ�����ǩ��ͼ��32*32,����,����Tab3��ͼ��
	HBITMAP  TrayMenuIcon;		//TrayMenuIcon.bmp;	//�Ҽ��˵���ͼ���б�
	int TabIconTop;  		//8;			//��ǩ��ͼ��Ķ�����㣨�����һ��Tabҳ��39 * 69))	
	int TabIconLeft;		//3;			//��ǩ��ͼ�������㣨�����һ��Tabҳ��39 * 69))	
	COLORREF MsgIWantColor;		//100,135,220;		//��Ϣ���ڵ�"����"����ɫ
	COLORREF TreeUserNameColor;	//0,0,0;		//���ϵ��û�������ɫ����	
	COLORREF EmailColor;		//140,170,230;		//"�ʼ�"����ɫ
	int IMTabSpace;			//22;			//Tab�ؼ���ҳ��ļ��
	int IMTabTopEdge;		//3;			//Tab�ؼ���һҳ�Ķ�Ӧ��������ԭ��ľ���

	HBITMAP  ChatSmallPhoto;	//ChatSmallPhoto.bmp;	//�����Ҵ��ڵ�Сͼ��
	COLORREF ChatGrpColor;		//0, 0, 0;		//�����ҵ�����ɫ	
	COLORREF ChatRoomColor;		//0, 0, 0;		//�����ҵ���ɫ
	COLORREF ChatFocusColor;	//255, 0, 0;		//�����Ҿ۽�ʱ����ɫ


	COLORREF MsgWndToolTextClr;	//0,0,0;		//��Ϣ���ڹ�����������ɫ
	COLORREF MsgWndVertBannerTextClr;	//255,255,255;		//��Ϣ���ڲ����banner������ɫ������...��
	COLORREF MsgWndVertBannerFlyByClr;//1,72,178;		//��Ϣ���ڲ����banner������ɫ���������������ʾ����ɫ��
	COLORREF MsgWndVertToolTextClr;	//0,0,0;		//��Ϣ���ڲ����tool������ɫ������չ�������ص���һ���֣�
	COLORREF MsgWndVertToolFlyByClr;//255,132,0;		//��Ϣ���ڲ����tool������ɫ���������������ʾ����ɫ��
	COLORREF ChatWndVertListTextClr;//255,255,255;		//���촰�������б��������ɫ

	COLORREF ChatIWantBarColor;	//140,170,230;		//������ҳ������״̬������ɫ
	COLORREF ChatShortCutBk;	//241,239,231;		//������ҳ���ݲ����ı���ɫ


	HBITMAP  ULBmp;			//UL.bmp;		//���IM��Ϣ������	tabͼƬ		ULΪUsers List�ļ�д
	COLORREF ULImTextClr;		//16,56,188;		//���IM��Ϣ������	tab������ɫ
	COLORREF ULImPropTextClr;	//255,255,255;		//���IM��Ϣ������	��ʾ��������ɫ
	COLORREF ULImPropBGClr;		//140,170,230;		//���IM��Ϣ������	��ʾ������ɫ
	COLORREF ULImListTextClr;	//0,0,0;		//���IM��Ϣ������	�б�������ɫ
	COLORREF ULImListBGClr;		//255,255,255;		//���IM��Ϣ������	�б���ɫ

	COLORREF ULSmsTextClr;		//16,56,188;		//���SMS��Ϣ������	tab������ɫ
	COLORREF ULSmsPropTextClr;	//255,255,255;		//���SMS��Ϣ������	��ʾ��������ɫ
	COLORREF ULSmsPropBGClr;	//140,170,230; 		//���SMS��Ϣ������	��ʾ������ɫ
	COLORREF ULSmsListTextClr;	//0,0,0;		//���SMS��Ϣ������	�б�������ɫ
	COLORREF ULSmsListBGClr;	//241,239,231;		//���SMS��Ϣ������	�б���ɫ


	COLORREF ULChatTextClr;		//16,56,188;		//����������	tab������ɫ
	COLORREF ULChatPropTextClr;	//255,255,255;		//����������	��ʾ��������ɫ
	COLORREF ULChatPropBGClr;	//140,170,230; 		//����������	��ʾ������ɫ
	COLORREF ULChatListTextClr;	//0,0,0;		//����������	�б�������ɫ
	COLORREF ULChatListBGClr;	//241,239,231;		//����������	�б���ɫ

	COLORREF ULImLineClr;		//140,170,230;		//���IM��Ϣ������	��������ɫ
	COLORREF ULSmsLineClr;		//140,170,230;		//���IM��Ϣ������	��������ɫ
	COLORREF ULChatLineClr;		//140,170,230;		//����������	��������ɫ

	HBITMAP  ULMaskBmp;		// ULMask.bmp;		//���IM��Ϣ������ sms������ ����������	tab maskͼƬ		ULΪUsers List�ļ�д

	COLORREF ShortCutIWantTxtClr;	//255, 255, 255;	//"������������ͨ״̬������ɫ
	COLORREF ShortCutIWantFocusClr;	//1, 72, 178;		//"���������ľ۽�ʱ��������ɫ	
	COLORREF ShortCutNormalTextClr;	//0, 0, 0;		//"�������ͨ����ͨ״̬������ɫ
	COLORREF ShortCutFocusTextClr;	//255, 128, 0;		//"�������ͨ���۽�״̬������ɫ

	//����ͼƬ
	CBitmap MainIconBmp;	//�������ϵ�����Iconͼ��16��16
	CBitmap LogoBmp;	//���Ͻ�Logo
	CBitmap TabBmp;		//��ǩ����ͼ
	CBitmap TabStatusBmp;	//��ǩ״̬ͼ
	CBitmap MsgWndIconBmp;	//��Ϣ����ͼ�꣬��11��,16*16
	CBitmap MainStatusBmp;	//��������״̬ͼ
	CBitmap CornerBmp;	//�߽�ͼ
	CBitmap TrayMenuIconBmp;//�Ҽ��˵���ͼ���б�
	CBitmap ShortCutMenuIconBmp;//������Ĳ˵�ͼ�� 16*16
	CBitmap SmallStatusBmp;	//С��״̬ͼ

	CImageList m_pILMainIcon;	
	CImageList m_pILSmallState;	
	CImageList m_pILEmotions;	//�������
	CImageList m_pILSendMsgIcon;	//
public:
	void CopyImage(CImageList &srcIL,CImageList &dstIL,int  nSrcImage);
	void DrawTransparent(CDC *pDC,CPoint dpt,CBitmap &bmp,CPoint spt,CSize sz,COLORREF crColour);

	HBITMAP LoadBmpFile(CString Path,CString SkinName,CString IdStr);
	//��API����BMP�ļ�
	BOOL LoadBMPImage(LPCTSTR sBMPFile,CBitmap& Bitmap, CPalette* pPal);

	HBITMAP GetImage(CImageList& list, int num,COLORREF clrBkColor=RGB(255,0,0));

	BOOL LoadSkin(CString SkinName);
	CSkin();
	virtual ~CSkin();

private:
	virtual void CreateAppImageList();
	virtual int GetIntValue(CString Path, CString SkinName, CString IdStr);
	virtual COLORREF CreateColor(CString strColor);
	COLORREF GetColorValue(CString Path,CString SkinName,CString IdStr);
	CString GetValue(LPCSTR Str);
protected:
	virtual void AttachAllBitmap();
	virtual void DeleteAllObject();
};

#endif // !defined(AFX_SKIN_H__F795F6DF_EBE1_4FD7_A0D7_8A37E95E6D06__INCLUDED_)
