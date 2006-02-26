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
	CString Title;			//MSN风格;   		主题名称不能超过256个字符(128个中文汉字，256个英文字母）
	COLORREF MainBk;		//1,72,178;       	主背景RGB色，色彩中间用”,”分隔
	COLORREF MainBorder;   		//1,72,178;        	主背景边框RGB色，色彩中间用”,”分隔
	COLORREF TreeGroupColor;	//192,192,192;		树控件的组的字体颜色
	HBITMAP  MainIcon; 		//MainIcon.bmp;         主窗口上的所有Icon图，16＊16，共9个
	HBITMAP  MainBkImg;     	//MainBk.bmp;           主窗口上的背景图
	HBITMAP  MainStatus;		//BigStatus.bmp;	状态图，一个文件，共3组，每组状态有7个图, 32*32
	HBITMAP  SmallStatus;		//smallIcon.bmp;	小的状态图，一个文件，共三两组, 16 * 16，前两组每组7个
					//			;后一组共5个，为各种状态的Mask图标
	HBITMAP  TabBkPhoto;   		//TabBk.bmp;          	Tab的按钮的背景图，一个文件，共两组, 分为激活和非激活状态							;前面两个为激活/非激活状态的背景图，后面3个是第二个Tab的3个状态，每个39 * 69
	HBITMAP  Corner;		//conner.bmp;		//边角图，共两组，8个图，每个图是8＊8
	COLORREF MaxMinBarColor;	//140,170,230;      	“我想”栏的颜色
	COLORREF ShortCutBkColor;   	//241,239,231;       	快捷栏窗口的背景颜色
	HBITMAP  ShortCutMenuIcon;	//ShortMenu.bmp;         快捷栏的菜单图标 16*16，共5个

	COLORREF DragWndFirstLine[3]; 	//156, 207, 156;	//我的状态窗口第一条线的第一种颜色（共三条线，每条线三种颜色）
	COLORREF DragWndSecLine[3]; 	//49, 154, 206;		//我的状态窗口第二条线的第一种颜色（共三条线，每条线三种颜色）
	COLORREF DragWndThrLine[3]; 	//247, 162, 16;		//我的状态窗口第三条线的第一种颜色（共三条线，每条线三种颜色）
	COLORREF DragWndFourLine[3]; 	//255, 255, 49;		//我的状态窗口第4条线的第一种颜色（共三条线，每条线三种颜色）

	HBITMAP  DragMenuPhoto;		//Ntes.bmp;		//我的状态窗口上的”网易”图片， 88＊30
	HBITMAP  NotifyUserAnimate;	//Animate.bmp;		//别人上线时的动画每幅16 * 16，共两组，5幅，使用标准的16色
					//			;前3幅表示别人上线的动画，后两幅是登录动画
	COLORREF MsgWndEdgeClr;		//1,72,178;		//消息窗口背景颜色
	COLORREF MsgWndPropTextIMClr; 	//179,200,232;		//消息窗口提示文本在显示IM消息的颜色
	COLORREF MsgWndPropTextSMSClr; 	//179,200,232;		//消息窗口提示文本在显示SMS消息的颜色
	COLORREF MsgWndToolBarBGClr;	//214,223,247;		//消息窗口水平工具栏背景色
	COLORREF MsgWndSpaceTopLeftClr;	//139,169,229;		//消息窗口右下角空白区域左上角颜色
	COLORREF MsgWndSpaceBottomRightClr;//100,135,220; 	//消息窗口右下角空白区域右下角颜色
	COLORREF MsgWndVertBarClr;	//241,239,231;		//消息窗口侧边条工具栏背景色
	HBITMAP  MsgWndIcon; 		//SendMsgIcon.bmp;	//消息窗口图标，共11个,16*16
	COLORREF TreeBkColor;		//255,255,255;		//树控件的背景颜色

	HBITMAP  Tab2Bmp;		//tab2.bmp;		//第二个标签的图像32*32,两组,包含Tab3的图像
	HBITMAP  TrayMenuIcon;		//TrayMenuIcon.bmp;	//右键菜单的图标列表
	int TabIconTop;  		//8;			//标签的图标的顶部起点（相对于一个Tab页（39 * 69))	
	int TabIconLeft;		//3;			//标签的图标的左起点（相对于一个Tab页（39 * 69))	
	COLORREF MsgIWantColor;		//100,135,220;		//消息窗口的"我想"的颜色
	COLORREF TreeUserNameColor;	//0,0,0;		//树上的用户名的颜色设置	
	COLORREF EmailColor;		//140,170,230;		//"邮件"的颜色
	int IMTabSpace;			//22;			//Tab控件两页间的间隔
	int IMTabTopEdge;		//3;			//Tab控件第一页的对应整个窗口原点的距离

	HBITMAP  ChatSmallPhoto;	//ChatSmallPhoto.bmp;	//聊天室窗口的小图标
	COLORREF ChatGrpColor;		//0, 0, 0;		//聊天室的组颜色	
	COLORREF ChatRoomColor;		//0, 0, 0;		//聊天室的颜色
	COLORREF ChatFocusColor;	//255, 0, 0;		//聊天室聚焦时的颜色


	COLORREF MsgWndToolTextClr;	//0,0,0;		//消息窗口工具栏文字颜色
	COLORREF MsgWndVertBannerTextClr;	//255,255,255;		//消息窗口侧边条banner文字颜色（我想...）
	COLORREF MsgWndVertBannerFlyByClr;//1,72,178;		//消息窗口侧边条banner文字颜色（鼠标在其上事显示的颜色）
	COLORREF MsgWndVertToolTextClr;	//0,0,0;		//消息窗口侧边条tool文字颜色（可以展开或隐藏的那一部分）
	COLORREF MsgWndVertToolFlyByClr;//255,132,0;		//消息窗口侧边条tool文字颜色（鼠标在其上事显示的颜色）
	COLORREF ChatWndVertListTextClr;//255,255,255;		//聊天窗口聊友列表的文字颜色

	COLORREF ChatIWantBarColor;	//140,170,230;		//聊天室页面我想状态条的颜色
	COLORREF ChatShortCutBk;	//241,239,231;		//聊天室页面快捷操作的背景色


	HBITMAP  ULBmp;			//UL.bmp;		//添加IM消息接收者	tab图片		UL为Users List的简写
	COLORREF ULImTextClr;		//16,56,188;		//添加IM消息接收者	tab文字颜色
	COLORREF ULImPropTextClr;	//255,255,255;		//添加IM消息接收者	提示区文字颜色
	COLORREF ULImPropBGClr;		//140,170,230;		//添加IM消息接收者	提示区背景色
	COLORREF ULImListTextClr;	//0,0,0;		//添加IM消息接收者	列表文字颜色
	COLORREF ULImListBGClr;		//255,255,255;		//添加IM消息接收者	列表背景色

	COLORREF ULSmsTextClr;		//16,56,188;		//添加SMS消息接收者	tab文字颜色
	COLORREF ULSmsPropTextClr;	//255,255,255;		//添加SMS消息接收者	提示区文字颜色
	COLORREF ULSmsPropBGClr;	//140,170,230; 		//添加SMS消息接收者	提示区背景色
	COLORREF ULSmsListTextClr;	//0,0,0;		//添加SMS消息接收者	列表文字颜色
	COLORREF ULSmsListBGClr;	//241,239,231;		//添加SMS消息接收者	列表背景色


	COLORREF ULChatTextClr;		//16,56,188;		//聊天室邀请	tab文字颜色
	COLORREF ULChatPropTextClr;	//255,255,255;		//聊天室邀请	提示区文字颜色
	COLORREF ULChatPropBGClr;	//140,170,230; 		//聊天室邀请	提示区背景色
	COLORREF ULChatListTextClr;	//0,0,0;		//聊天室邀请	列表文字颜色
	COLORREF ULChatListBGClr;	//241,239,231;		//聊天室邀请	列表背景色

	COLORREF ULImLineClr;		//140,170,230;		//添加IM消息接收者	修饰线颜色
	COLORREF ULSmsLineClr;		//140,170,230;		//添加IM消息接收者	修饰线颜色
	COLORREF ULChatLineClr;		//140,170,230;		//聊天室邀请	修饰线颜色

	HBITMAP  ULMaskBmp;		// ULMask.bmp;		//添加IM消息接收者 sms接收者 聊天室邀请	tab mask图片		UL为Users List的简写

	COLORREF ShortCutIWantTxtClr;	//255, 255, 255;	//"快捷栏我想的普通状态文字颜色
	COLORREF ShortCutIWantFocusClr;	//1, 72, 178;		//"快捷栏我想的聚焦时的文字颜色	
	COLORREF ShortCutNormalTextClr;	//0, 0, 0;		//"快捷栏普通栏普通状态文字颜色
	COLORREF ShortCutFocusTextClr;	//255, 128, 0;		//"快捷栏普通栏聚焦状态文字颜色

	//定义图片
	CBitmap MainIconBmp;	//主窗口上的所有Icon图，16＊16
	CBitmap LogoBmp;	//右上角Logo
	CBitmap TabBmp;		//标签背景图
	CBitmap TabStatusBmp;	//标签状态图
	CBitmap MsgWndIconBmp;	//消息窗口图标，共11个,16*16
	CBitmap MainStatusBmp;	//个人在线状态图
	CBitmap CornerBmp;	//边角图
	CBitmap TrayMenuIconBmp;//右键菜单的图标列表
	CBitmap ShortCutMenuIconBmp;//快捷栏的菜单图标 16*16
	CBitmap SmallStatusBmp;	//小的状态图

	CImageList m_pILMainIcon;	
	CImageList m_pILSmallState;	
	CImageList m_pILEmotions;	//表情符号
	CImageList m_pILSendMsgIcon;	//
public:
	void CopyImage(CImageList &srcIL,CImageList &dstIL,int  nSrcImage);
	void DrawTransparent(CDC *pDC,CPoint dpt,CBitmap &bmp,CPoint spt,CSize sz,COLORREF crColour);

	HBITMAP LoadBmpFile(CString Path,CString SkinName,CString IdStr);
	//用API加载BMP文件
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
