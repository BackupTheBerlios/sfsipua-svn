// Skin.cpp: implementation of the CSkin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CNIcq.h"
#include "Skin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define COLOR_WHITE	RGB(255,255,255)
#define COLOR_BLACK	RGB(0,0,0)
#define NCOLORSHADES	128		// this many shades in gradient

static void PaintRect(CDC* pDC, int x, int y, int w, int h, COLORREF color)
{
	CBrush brush(color);
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	pDC->PatBlt(x, y, w, h, PATCOPY);
	pDC->SelectObject(pOldBrush);
	brush.DeleteObject();
}

void PaintGradiantRect(CDC *pDC, const RECT &rect,
	COLORREF clrFrom, COLORREF clrTo, BOOL hori, BOOL ascend)
{
	int cxCap = rect.right - rect.left;
	int cyCap = rect.bottom - rect.top;

	// Get the intensity values for the ending color
	int r1 = GetRValue(clrTo); // red
	int g1 = GetGValue(clrTo); // green
	int b1 = GetBValue(clrTo); // blue
	
	// Get the intensity values for the begining color
	int r2 = GetRValue(clrFrom); // red
	int g2 = GetGValue(clrFrom); // green
	int b2 = GetBValue(clrFrom); // blue

	int r, g, b;

	if(hori) //paint horizontal rect;
	{
		int x = cxCap;	
		int w = x;							// width of area to shade
		int xDelta= max(w/NCOLORSHADES,1);	// width of one shade band


		while (x >= xDelta) {
			x -= xDelta;
			if (r1 > r2)
				r = r1 - (r1-r2)*(w-x)/w;
			else
				r = r1 + (r2-r1)*(w-x)/w;

			if (g1 > g2)
				g = g1 - (g1-g2)*(w-x)/w;
			else
				g = g1 + (g2-g1)*(w-x)/w;

			if (b1 > b2)
				b = b1 - (b1-b2)*(w-x)/w;
			else
				b = b1 + (b2-b1)*(w-x)/w;

			if(ascend) // Paint from  left to right;
				PaintRect(pDC, rect.left+x, rect.top, xDelta, cyCap, RGB(r, g, b));
			else               // Paint from  right to left;
				PaintRect(pDC, rect.right-x-xDelta, rect.top, xDelta, cyCap, RGB(r, g, b));
		}
	}
	else    //paint vertical rect;
	{
		int y = cyCap;	
		int w = y;							// height of area to shade
		int yDelta= max(w/NCOLORSHADES,1);	// height of one shade band


		//while (y >= yDelta) {
		while (y > 0) {
			y -= yDelta;
			if (r1 > r2)
				r = r1 - (r1-r2)*(w-y)/w;
			else
				r = r1 + (r2-r1)*(w-y)/w;

			if (g1 > g2)
				g = g1 - (g1-g2)*(w-y)/w;
			else
				g = g1 + (g2-g1)*(w-y)/w;

			if (b1 > b2)
				b = b1 - (b1-b2)*(w-y)/w;
			else
				b = b1 + (b2-b1)*(w-y)/w;
		    
			if(ascend) // Paint from  top to bottom;
				PaintRect(pDC, rect.left, rect.top+y, cxCap, yDelta, RGB(r, g, b));
			else       // Paint from  bottom to top;
				PaintRect(pDC, rect.left, rect.bottom-y-yDelta, cxCap, yDelta, RGB(r, g, b));
		}
	}
}

void DrawColorCube(CDC* pDC, CRect& rect, 
	COLORREF colorFrom, COLORREF colorTo /*= RGB(255,255,255)*/, 
	BOOL IsHori /*= true*/)
{
	CRect       newRect;
	COLORREF    color;
	CPen*       oldPen;
	CBrush*     oldBr;    

	/*
	*  If value as 0, draw a line here;
	*/
	if(rect.Width()<=0 )
	        rect.right = rect.left +2;
	else if(rect.Height() <=0)
		rect.top-=2;

	BOOL backHori = IsHori;
	IsHori = true;

	/* 
	* draw first 1/3 part;
	*/
	if(IsHori)
	{
		newRect.SetRect(rect.left,rect.top,(rect.right - rect.left)/3+rect.left,rect.bottom);
		PaintGradiantRect(pDC,newRect,colorFrom, colorTo);
	}
	else
	{
		newRect.SetRect(rect.left,rect.bottom - (rect.bottom-rect.top)/3,rect.right,rect.bottom);
		PaintGradiantRect(pDC,newRect,colorFrom, colorTo, IsHori, false);
	}

	/*
	* then left 2/3 part;
	*/
	if(IsHori)
	{
		newRect.SetRect((rect.right - rect.left)/3+rect.left,rect.top,rect.right,rect.bottom);
		PaintGradiantRect(pDC,newRect,colorFrom, colorTo, IsHori, false);
	}
	else
	{
	        newRect.SetRect(rect.left,rect.top, rect.right, rect.bottom - (rect.bottom-rect.top)/3);
		PaintGradiantRect(pDC,newRect,colorFrom, colorTo, IsHori, true);
	}

	/*
	* Frame the rect with colorFrom, with look better;
	*/
	CPen pen(PS_SOLID,2,colorFrom);
	oldPen  = (CPen*)pDC->SelectObject(&pen);
	oldBr   = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(&rect);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBr);
	pen.DeleteObject();

	/*
	*   Draw Shadow next;
	*/
	if(backHori)//hori
	{
		color = RGB(170,170,170);
		CPen pen1(PS_SOLID,2,color);
		oldPen = (CPen*)pDC->SelectObject(&pen1);
		pDC->MoveTo(rect.left, rect.bottom+1);
		pDC->LineTo(rect.right+1, rect.bottom+1);
		pDC->LineTo(rect.right+1, rect.top);

		color = RGB(190,190,190);
		CPen pen2(PS_SOLID,2,color);
		pDC->SelectObject(&pen2);
		pDC->MoveTo(rect.left+1, rect.bottom+2);
		pDC->LineTo(rect.right+2, rect.bottom+2);
		pDC->LineTo(rect.right+2, rect.top+1);

		pDC->SelectObject(oldPen);
		pen1.DeleteObject();
		pen2.DeleteObject();
	}
	else//vert
	{
#if 0
		color = RGB(170,170,170);
		CPen pen1(PS_SOLID,1,color);
		oldPen = (CPen*)pDC->SelectObject(&pen1);
		pDC->MoveTo(rect.left, rect.top-2);
		pDC->LineTo(rect.right+1, rect.top-2);
		pDC->LineTo(rect.right+1, rect.bottom);

		color = RGB(190,190,190);
		CPen pen2(PS_SOLID,1,color);
		pDC->SelectObject(&pen2);
		pDC->MoveTo(rect.left+1, rect.top-3);
		pDC->LineTo(rect.right+1, rect.top-3);
		pDC->LineTo(rect.right+1, rect.bottom-1);

		pDC->SelectObject(oldPen);
		pen1.DeleteObject();
		pen2.DeleteObject();
#endif
	}
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkin::CSkin()
{
	MainIcon	= NULL;
	MainBkImg	= NULL;
	MainStatus	= NULL;
	SmallStatus	= NULL;
	TabBkPhoto	= NULL;
	Corner		= NULL;
	ShortCutMenuIcon= NULL;
	DragMenuPhoto	= NULL;
	NotifyUserAnimate= NULL;
	MsgWndIcon	= NULL;
	Tab2Bmp		= NULL;
	TrayMenuIcon	= NULL;
	ChatSmallPhoto	= NULL;
	ULBmp		= NULL;
	ULMaskBmp	= NULL;
}

CSkin::~CSkin()
{
	DeleteAllObject();	//清除内存
}

BOOL CSkin::LoadSkin(CString SkinName)
{
	CString SkinPath;

	TCHAR exeFullPath[MAX_PATH]; 

	//取应用程序名
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);

	//取路径
	SkinPath = ((CCNIcqApp *)AfxGetApp())->ExtractFilePath(exeFullPath) + "Skin\\" + SkinName + "\\";

	DeleteAllObject();	//清除内存

	//加载位图
	MainIcon		= LoadBmpFile(SkinPath,SkinName,"MainIcon");
	MainBkImg		= LoadBmpFile(SkinPath,SkinName,"MainBkImg");
	MainStatus		= LoadBmpFile(SkinPath,SkinName,"MainStatus");
	SmallStatus		= LoadBmpFile(SkinPath,SkinName,"SmallStatus");
	TabBkPhoto		= LoadBmpFile(SkinPath,SkinName,"TabBkPhoto");
	Corner			= LoadBmpFile(SkinPath,SkinName,"Corner");
	ShortCutMenuIcon	= LoadBmpFile(SkinPath,SkinName,"ShortCutMenuIcon");
	DragMenuPhoto		= LoadBmpFile(SkinPath,SkinName,"DragMenuPhoto");
	NotifyUserAnimate	= LoadBmpFile(SkinPath,SkinName,"NotifyUserAnimate");
	MsgWndIcon		= LoadBmpFile(SkinPath,SkinName,"MsgWndIcon");
	Tab2Bmp			= LoadBmpFile(SkinPath,SkinName,"Tab2Bmp");
	TrayMenuIcon		= LoadBmpFile(SkinPath,SkinName,"TrayMenuIcon");
	ChatSmallPhoto		= LoadBmpFile(SkinPath,SkinName,"ChatSmallPhoto");
	ULBmp			= LoadBmpFile(SkinPath,SkinName,"ULBmp");
	ULMaskBmp		= LoadBmpFile(SkinPath,SkinName,"ULMaskBmp");
	
	//----------------------------------------------------------------------------
	//加载颜色
	MainBk			= GetColorValue(SkinPath,SkinName,"MainBk");
	MainBorder		= GetColorValue(SkinPath,SkinName,"MainBorder");
	TreeGroupColor		= GetColorValue(SkinPath,SkinName,"TreeGroupColor");
	MaxMinBarColor		= GetColorValue(SkinPath,SkinName,"MaxMinBarColor");
	ShortCutBkColor		= GetColorValue(SkinPath,SkinName,"ShortCutBkColor");

	//----------------------------------------------------------------------------
	DragWndFirstLine[0]	= GetColorValue(SkinPath,SkinName,"DragWndFirstLine1");
	DragWndFirstLine[1]	= GetColorValue(SkinPath,SkinName,"DragWndFirstLine2");
	DragWndFirstLine[2]	= GetColorValue(SkinPath,SkinName,"DragWndFirstLine3");

	DragWndSecLine[0]	= GetColorValue(SkinPath,SkinName,"DragWndSecLine1");
	DragWndSecLine[1]	= GetColorValue(SkinPath,SkinName,"DragWndSecLine2");
	DragWndSecLine[2]	= GetColorValue(SkinPath,SkinName,"DragWndSecLine3");

	DragWndThrLine[0]	= GetColorValue(SkinPath,SkinName,"DragWndThrLine1");
	DragWndThrLine[1]	= GetColorValue(SkinPath,SkinName,"DragWndThrLine2");
	DragWndThrLine[2]	= GetColorValue(SkinPath,SkinName,"DragWndThrLine3");

	DragWndFourLine[0]	= GetColorValue(SkinPath,SkinName,"DragWndFourLine1");
	DragWndFourLine[1]	= GetColorValue(SkinPath,SkinName,"DragWndFourLine2");
	DragWndFourLine[2]	= GetColorValue(SkinPath,SkinName,"DragWndFourLine3");
	//----------------------------------------------------------------------------

	MsgWndEdgeClr		= GetColorValue(SkinPath,SkinName,"MsgWndEdgeClr");
	MsgWndPropTextIMClr	= GetColorValue(SkinPath,SkinName,"MsgWndPropTextIMClr");
	MsgWndPropTextSMSClr	= GetColorValue(SkinPath,SkinName,"MsgWndPropTextSMSClr");
	MsgWndToolBarBGClr	= GetColorValue(SkinPath,SkinName,"MsgWndToolBarBGClr");
	MsgWndSpaceTopLeftClr	= GetColorValue(SkinPath,SkinName,"MsgWndSpaceTopLeftClr");
	MsgWndSpaceBottomRightClr= GetColorValue(SkinPath,SkinName,"MsgWndSpaceBottomRightClr");
	MsgWndVertBarClr	= GetColorValue(SkinPath,SkinName,"MsgWndVertBarClr");
	//----------------------------------------------------------------------------
	TreeBkColor		= GetColorValue(SkinPath,SkinName,"TreeBkColor");
	MsgIWantColor		= GetColorValue(SkinPath,SkinName,"MsgIWantColor");
	TreeUserNameColor	= GetColorValue(SkinPath,SkinName,"TreeUserNameColor");
	EmailColor		= GetColorValue(SkinPath,SkinName,"EmailColor");
	ChatGrpColor		= GetColorValue(SkinPath,SkinName,"ChatGrpColor");
	ChatRoomColor		= GetColorValue(SkinPath,SkinName,"ChatRoomColor");
	ChatFocusColor		= GetColorValue(SkinPath,SkinName,"ChatFocusColor");
	//----------------------------------------------------------------------------
	MsgWndToolTextClr	= GetColorValue(SkinPath,SkinName,"MsgWndToolTextClr");
	MsgWndVertBannerTextClr	= GetColorValue(SkinPath,SkinName,"MsgWndVertBannerTextClr");
	MsgWndVertBannerFlyByClr= GetColorValue(SkinPath,SkinName,"MsgWndVertBannerFlyByClr");
	MsgWndVertToolTextClr	= GetColorValue(SkinPath,SkinName,"MsgWndVertToolTextClr");
	MsgWndVertToolFlyByClr	= GetColorValue(SkinPath,SkinName,"MsgWndVertToolFlyByClr");
	ChatWndVertListTextClr	= GetColorValue(SkinPath,SkinName,"ChatWndVertListTextClr");
	ChatIWantBarColor	= GetColorValue(SkinPath,SkinName,"ChatIWantBarColor");
	ChatShortCutBk		= GetColorValue(SkinPath,SkinName,"ChatShortCutBk");

	//----------------------------------------------------------------------------
	ULImTextClr		= GetColorValue(SkinPath,SkinName,"ULImTextClr");
	ULImPropTextClr		= GetColorValue(SkinPath,SkinName,"ULImPropTextClr");
	ULImPropBGClr		= GetColorValue(SkinPath,SkinName,"ULImPropBGClr");
	ULImListTextClr		= GetColorValue(SkinPath,SkinName,"ULImListTextClr");
	ULImListBGClr		= GetColorValue(SkinPath,SkinName,"ULImListBGClr");
	//----------------------------------------------------------------------------
	ULSmsTextClr		= GetColorValue(SkinPath,SkinName,"ULSmsTextClr");
	ULSmsPropTextClr	= GetColorValue(SkinPath,SkinName,"ULSmsPropTextClr");
	ULSmsPropBGClr		= GetColorValue(SkinPath,SkinName,"ULSmsPropBGClr");
	ULSmsListTextClr	= GetColorValue(SkinPath,SkinName,"ULSmsListTextClr");
	ULSmsListBGClr		= GetColorValue(SkinPath,SkinName,"ULSmsListBGClr");
	//----------------------------------------------------------------------------
	ULChatTextClr		= GetColorValue(SkinPath,SkinName,"ULChatTextClr");
	ULChatPropTextClr	= GetColorValue(SkinPath,SkinName,"ULChatPropTextClr");
	ULChatPropBGClr		= GetColorValue(SkinPath,SkinName,"ULChatPropBGClr");
	ULChatListTextClr	= GetColorValue(SkinPath,SkinName,"ULChatListTextClr");
	ULChatListBGClr		= GetColorValue(SkinPath,SkinName,"ULChatListBGClr");
	//----------------------------------------------------------------------------
	ULImLineClr		= GetColorValue(SkinPath,SkinName,"ULImLineClr");
	ULSmsLineClr		= GetColorValue(SkinPath,SkinName,"ULSmsLineClr");
	ULChatLineClr		= GetColorValue(SkinPath,SkinName,"ULChatLineClr");

	//----------------------------------------------------------------------------
	ShortCutIWantTxtClr	= GetColorValue(SkinPath,SkinName,"ShortCutIWantTxtClr");
	ShortCutIWantFocusClr	= GetColorValue(SkinPath,SkinName,"ShortCutIWantFocusClr");
	ShortCutNormalTextClr	= GetColorValue(SkinPath,SkinName,"ShortCutNormalTextClr");
	ShortCutFocusTextClr	= GetColorValue(SkinPath,SkinName,"ShortCutFocusTextClr");

	//读取整数
	TabIconTop		= GetIntValue(SkinPath,SkinName,"TabIconTop");
	TabIconLeft		= GetIntValue(SkinPath,SkinName,"TabIconLeft");
	IMTabSpace		= GetIntValue(SkinPath,SkinName,"IMTabSpace");
	IMTabTopEdge		= GetIntValue(SkinPath,SkinName,"IMTabTopEdge");

	AttachAllBitmap();

	CreateAppImageList();

	return TRUE;
}

CString CSkin::GetValue(LPCSTR Str)
{
	CString Result = "";

	int Len = strlen(Str);

	for(int i = 0; i < Len; i++)
	{
		if( Str[i] == ';') break;

		Result = Result + Str[i];
	}
	return Result;

}

HBITMAP CSkin::LoadBmpFile(CString Path, CString SkinName,CString IdStr)
{
	CString bmpFileName;
	CString SkinFileName;

	SkinFileName = Path + "skin.ini";

	::GetPrivateProfileString(SkinName,IdStr,"",bmpFileName.GetBuffer(MAX_PATH),MAX_PATH,SkinFileName);

	bmpFileName = GetValue(bmpFileName);

	if( bmpFileName.IsEmpty()) 
		return NULL;

	bmpFileName = Path + bmpFileName;

	//从文件加载bmp图象
	HBITMAP hBmp = (HBITMAP)::LoadImage(NULL,
			bmpFileName,
			IMAGE_BITMAP, 
			0,0, 
			LR_LOADFROMFILE |
			LR_CREATEDIBSECTION |
			LR_DEFAULTSIZE);
	return hBmp;	
}
BOOL CSkin::LoadBMPImage(LPCTSTR sBMPFile,CBitmap& Bitmap, CPalette* pPal)
{
	CFile file;
	if( !file.Open(sBMPFile,CFile::modeRead))
		return FALSE;
	BITMAPFILEHEADER bmfHeader;

	if( file.Read((LPSTR)&bmfHeader,sizeof(bmfHeader)) != sizeof(bmfHeader))
		return FALSE;
	if(bmfHeader.bfType != ((WORD)('M'<<8) | 'B'))
		return FALSE;
	DWORD nPackedDIBLen = file.GetLength() - sizeof(BITMAPFILEHEADER);
	HGLOBAL hDIB = ::GlobalAlloc(GMEM_FIXED,nPackedDIBLen);

	if( hDIB == 0)
		return FALSE;
	if( file.ReadHuge((LPSTR)hDIB,nPackedDIBLen) != nPackedDIBLen)
	{
		::GlobalFree(hDIB);
		return FALSE;
	}
	
	BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB;

	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB;

	int nColors = bmiHeader.biClrUsed ? bmiHeader.biClrUsed : 1 << bmiHeader.biBitCount;

	LPVOID lpDIBBits;
	if( bmInfo.bmiHeader.biBitCount > 8)
	{
		lpDIBBits = (LPVOID)((LPWORD)(bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) + ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS)? 3 :0));
	}
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors+nColors);

	if( pPal != NULL)
	{
		if( nColors <= 256)
		{
			UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) + nColors);
			LOGPALETTE *pLP = (LOGPALETTE*)new BYTE[nSize];
			pLP->palVersion = 0x300;
			pLP->palNumEntries = nColors;
			for(int i = 0; i < nColors; i++)
			{
				pLP->palPalEntry[i].peRed=bmInfo.bmiColors[i].rgbRed;
				pLP->palPalEntry[i].peGreen=bmInfo.bmiColors[i].rgbGreen;
				pLP->palPalEntry[i].peBlue=bmInfo.bmiColors[i].rgbBlue;
				pLP->palPalEntry[i].peFlags = 0;
			}
			pPal->CreatePalette(pLP);
			delete[] pLP;
		}
	}
	CClientDC dc(NULL);
	CPalette *pOldPalette = NULL;
	if( pPal)
	{
		pOldPalette = dc.SelectPalette(pPal,FALSE);
		dc.RealizePalette();
	}
	HBITMAP hBmp = CreateDIBitmap(dc.m_hDC,
		&bmiHeader,
		CBM_INIT,
		lpDIBBits,
		&bmInfo,
		DIB_RGB_COLORS);

	Bitmap.Detach();
	Bitmap.Attach(hBmp);
	if( pOldPalette)
		dc.SelectPalette(pOldPalette,FALSE);
	::GlobalFree(hDIB);
	return TRUE;
}
COLORREF CSkin::GetColorValue(CString Path, CString SkinName, CString IdStr)
{
	COLORREF clrResult;
	CString strColor;
	CString SkinFileName;

	SkinFileName = Path + "skin.ini";

	::GetPrivateProfileString(SkinName,IdStr,"",strColor.GetBuffer(MAX_PATH),MAX_PATH,SkinFileName);

	strColor = GetValue(strColor);

	clrResult = CreateColor(strColor);
	
	return clrResult;
}

//输入格式为: r,g,b 如: 232,34,223
COLORREF CSkin::CreateColor(CString strColor)
{
	COLORREF clrResult;
	CString szR,szG,szB;
	int iR,iG,iB;
	int Pos1,Pos2,Len;

	clrResult = RGB(0,0,0);

	if( strColor.IsEmpty()) 
		return clrResult;

	Pos1 = strColor.Find(',');
	Pos2 = strColor.Find(',',Pos1+1);
	Len = strColor.GetLength();

	szR = strColor.Left(Pos1);
	szG = strColor.Mid(Pos1+1,Pos2-Pos1-1);
	szB = strColor.Mid(Pos2+1,Len-Pos2-1);

	if( szR.IsEmpty() || szG.IsEmpty() || szB.IsEmpty())
		return clrResult;

	iR = atoi(szR);
	iG = atoi(szG);
	iB = atoi(szB);

	clrResult = RGB(iR,iG,iB);

	return clrResult;
}

int CSkin::GetIntValue(CString Path, CString SkinName, CString IdStr)
{
	int iResult = 0;

	CString strValue;
	CString SkinFileName;

	SkinFileName = Path + "skin.ini";

	::GetPrivateProfileString(SkinName,IdStr,"",strValue.GetBuffer(MAX_PATH),MAX_PATH,SkinFileName);

	strValue = GetValue(strValue);

	iResult = atoi(strValue);

	return iResult;
}

void CSkin::CreateAppImageList()
{
	COLORREF crMask;

	crMask = RGB(255,0,0);
	//主窗口图象列表
	m_pILMainIcon.Create(16, 16, ILC_MASK | ILC_COLOR32, 0, 0);
	m_pILMainIcon.Add(&MainIconBmp,crMask);
	MainIconBmp.Detach();
	DeleteObject(MainIcon);
	MainIcon = NULL;

	//小图标
	m_pILSmallState.Create(16, 16, ILC_MASK | ILC_COLOR32, 0, 0);

	//添加主图标里的第一和第二个到状态列表里
	CopyImage(m_pILMainIcon,m_pILSmallState,1);
	CopyImage(m_pILMainIcon,m_pILSmallState,2);

	m_pILSmallState.Add(&SmallStatusBmp,crMask);
	SmallStatusBmp.Detach();
	DeleteObject(SmallStatus);
	MainIcon = NULL;

	//表情符号
	CBitmap bm;
	bm.LoadBitmap(IDB_EMOTIONS);
	m_pILEmotions.Create(20, 20, ILC_COLOR8 | ILC_MASK, 50, 0);
	m_pILEmotions.Add(&bm, RGB(0, 128, 128));

	//SendMsgIcon	
	m_pILSendMsgIcon.Create(16, 16, ILC_COLOR8 | ILC_MASK, 50, 0);
	m_pILSendMsgIcon.Add(&MsgWndIconBmp,crMask);
	MsgWndIconBmp.Detach();
	DeleteObject(MsgWndIcon);
}
void CSkin::DrawTransparent(CDC *pDC,CPoint dpt, 
	CBitmap &bmp,CPoint spt,CSize sz,COLORREF crColour)
{ 
	COLORREF crOldBack=pDC->SetBkColor(RGB(255,255,255)); 
	COLORREF crOldText=pDC->SetTextColor(RGB(0,0,0)); 

	CDC dcImage, dcMask; 

	//为图像及mask各创建一个DC 
	dcImage.CreateCompatibleDC(pDC); 
	dcMask.CreateCompatibleDC(pDC); 

	//把图像装入image DC 
	CBitmap* pOldBitmapImage=dcImage.SelectObject(&bmp); 
	//为“掩码”位图创建一个单色bitmap 
	CBitmap bitmapMask; 
	bitmapMask.CreateBitmap(sz.cx, sz.cy, 1, 1, NULL); //把mask位图装入mask DC 

	CBitmap* pOldBitmapMask = dcMask.SelectObject(&bitmapMask); //用透明色创建“掩码”位图 

	dcImage.SetBkColor(crColour);//crColor是位图中的透明色 
	dcMask.BitBlt(0, 0, sz.cx, sz.cy, &dcImage, spt.x, spt.y, SRCCOPY);//分3步进行实际的绘制 

	pDC->BitBlt(dpt.x, dpt.y, sz.cx, sz.cy, &dcImage,spt.x, spt.y, SRCINVERT); 

	pDC->BitBlt(dpt.x, dpt.y, sz.cx, sz.cy, &dcMask, 0, 0, SRCAND); 

	pDC->BitBlt(dpt.x, dpt.y, sz.cx, sz.cy, &dcImage,spt.x, spt.y, SRCINVERT); //恢复原先设置 

	dcImage.SelectObject(pOldBitmapImage); 
	dcMask.SelectObject(pOldBitmapMask); 

	bitmapMask.DeleteObject();

	dcImage.DeleteDC();
	dcMask.DeleteDC();

	pDC->SetBkColor(crOldBack); 
	pDC->SetTextColor(crOldText);
} 

void CSkin::DeleteAllObject()
{
	//Delete All Object
	if(MainIconBmp.m_hObject != NULL)		MainIconBmp.Detach();
	if(LogoBmp.m_hObject != NULL)			LogoBmp.Detach();
	if(TabBmp.m_hObject != NULL)			TabBmp.Detach();
	if(TabStatusBmp.m_hObject != NULL)		TabStatusBmp.Detach();
	if(MainStatusBmp.m_hObject != NULL)		MainStatusBmp.Detach();
	if(MsgWndIconBmp.m_hObject != NULL)		MsgWndIconBmp.Detach();
	if(CornerBmp.m_hObject != NULL)			CornerBmp.Detach();
	if(TrayMenuIconBmp.m_hObject != NULL)		TrayMenuIconBmp.Detach();
	if(ShortCutMenuIconBmp.m_hObject != NULL)	ShortCutMenuIconBmp.Detach();
	if(SmallStatusBmp.m_hObject != NULL)		SmallStatusBmp.Detach();

	if(MainIcon != NULL)		DeleteObject(MainIcon);
	if(DragMenuPhoto != NULL)	DeleteObject(DragMenuPhoto);
	if(TabBkPhoto != NULL)		DeleteObject(TabBkPhoto);
	if(Tab2Bmp != NULL)		DeleteObject(Tab2Bmp);
	if(MainStatus != NULL)		DeleteObject(MainStatus);
	if(MsgWndIcon != NULL)		DeleteObject(MsgWndIcon);
	if(TrayMenuIcon != NULL)	DeleteObject(TrayMenuIcon);
	if(ShortCutMenuIcon != NULL)	DeleteObject(ShortCutMenuIcon);
	if(SmallStatus != NULL)		DeleteObject(SmallStatus);
	if(Corner != NULL)		DeleteObject(Corner);
	if(MainBkImg != NULL)		DeleteObject(MainBkImg);
	if(NotifyUserAnimate != NULL)	DeleteObject(NotifyUserAnimate);
	if(ChatSmallPhoto != NULL)	DeleteObject(ChatSmallPhoto);
	if(ULBmp != NULL)		DeleteObject(ULBmp);
	if(ULMaskBmp != NULL)		DeleteObject(ULMaskBmp);

	if( m_pILMainIcon.m_hImageList != NULL)
		m_pILMainIcon.DeleteImageList();

	if( m_pILSmallState.m_hImageList != NULL)
		m_pILSmallState.DeleteImageList();

	if( m_pILEmotions.m_hImageList != NULL)
		m_pILEmotions.DeleteImageList();
	
	if( m_pILSendMsgIcon.m_hImageList != NULL)
		m_pILSendMsgIcon.DeleteImageList();
	//
	MainIcon	= NULL;
	MainBkImg	= NULL;
	MainStatus	= NULL;
	SmallStatus	= NULL;
	TabBkPhoto	= NULL;
	Corner		= NULL;
	ShortCutMenuIcon= NULL;
	DragMenuPhoto	= NULL;
	NotifyUserAnimate= NULL;
	MsgWndIcon	= NULL;
	Tab2Bmp		= NULL;
	TrayMenuIcon	= NULL;
	ChatSmallPhoto	= NULL;
	ULBmp		= NULL;
	ULMaskBmp	= NULL;
}

void CSkin::AttachAllBitmap()
{
	if(MainIcon != NULL)		MainIconBmp.Attach(MainIcon);
	if(DragMenuPhoto != NULL)	LogoBmp.Attach(DragMenuPhoto);
	if(TabBkPhoto != NULL)		TabBmp.Attach(TabBkPhoto);
	if(Tab2Bmp != NULL)		TabStatusBmp.Attach(Tab2Bmp);
	if(MainStatus != NULL)		MainStatusBmp.Attach(MainStatus);
	if(MsgWndIcon != NULL)		MsgWndIconBmp.Attach(MsgWndIcon);
	if(Corner != NULL)		CornerBmp.Attach(Corner);
	if(TrayMenuIcon != NULL)	TrayMenuIconBmp.Attach(TrayMenuIcon);
	if(ShortCutMenuIcon != NULL)	ShortCutMenuIconBmp.Attach(ShortCutMenuIcon);
	if(SmallStatus != NULL)		SmallStatusBmp.Attach(SmallStatus);


}

HBITMAP CSkin::GetImage(CImageList& list, int num,COLORREF clrBkColor)
{
	CBitmap dist;
	CClientDC dc(NULL);

	IMAGEINFO ii;
	list.GetImageInfo(num, &ii);

	int nWidth = ii.rcImage.right - ii.rcImage.left;
	int nHeight = ii.rcImage.bottom - ii.rcImage.top;

	dist.CreateCompatibleBitmap(&dc, nWidth, nHeight);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap* pOldBitmap = memDC.SelectObject(&dist);
	
	memDC.FillSolidRect(0, 0, nWidth, nHeight,clrBkColor);

	list.Draw(&memDC, num, CPoint(0, 0), ILD_NORMAL);

	memDC.SelectObject(pOldBitmap);

	return (HBITMAP)dist.Detach();
}

void CSkin::CopyImage(CImageList &srcIL, CImageList &dstIL, int nSrcImage)
{
	CBitmap bmpTemp;
	HBITMAP hBmp;

	hBmp = GetImage(srcIL,nSrcImage);
	bmpTemp.Attach(hBmp);
	dstIL.Add(&bmpTemp,RGB(255,0,0));
	bmpTemp.Detach();
	DeleteObject(hBmp);
}
