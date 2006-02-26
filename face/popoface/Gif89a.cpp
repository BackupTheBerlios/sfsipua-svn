#include "stdafx.h"
#include "gif89a.h"

DWORD WINAPI ThreadFunc(CGif89a* ptr);
DWORD WINAPI ThreadFunc(CGif89a* ptr)
{
	ptr->Play1();
	return 0;
}

void CGif89a::Play(HWND pWnd, const CRect& position)
{
	// TODO: Add your implementation code here
	m_hWnd=pWnd;
	gifposition = position;
	HANDLE hThread;
	DWORD ThreadId;
	if(m_hWnd==0)return ;
	if(m_pcGif==0)return;
	if(m_EndRun==5)return;
	m_pcGifTrack=m_pcGif;
	m_iTotalReadByte=0;
	m_EndRun=5;
	hThread=CreateThread(NULL,0,(unsigned long(_stdcall*)(void*))ThreadFunc,this,0,&ThreadId);
	CloseHandle(hThread);
	return;
}


BOOL CGif89a::Play1(void)
{
	HDC hDC,hMemDC,hMemDC1,hPauseMemDC;
	HBITMAP hOldBitmap,hOldBitmap1,hBitmap,hPreviousBitmap,hPauseBitmap;
	DWORD systimer1,systimer2,speed;
	BOOL PauseShow=FALSE;
	hDC=::GetDC(m_hWnd);
	hMemDC=::CreateCompatibleDC(hDC);
	hMemDC1=::CreateCompatibleDC(hDC);
	hPauseMemDC=::CreateCompatibleDC(hDC);
	m_hDC=hDC;
	hPreviousBitmap=0;
	while(m_bLockBitmap);
	m_bLockBitmap=TRUE;
	if(m_hRedrawBitmap!=0)DeleteObject(m_hRedrawBitmap);
	m_hRedrawBitmap=::CreateCompatibleBitmap(hDC,m_iGifWidth,m_iGifHeight);
	hOldBitmap1=(HBITMAP)SelectObject(hMemDC1,m_hRedrawBitmap);
	hPauseBitmap=::CreateCompatibleBitmap(hDC,m_iGifWidth,m_iGifHeight);
	SelectObject(hPauseMemDC,hPauseBitmap);
	/////////////////////////���������Ƶ�hMemDC1��////////////////////////////
	::BitBlt(hMemDC1,0,0,m_iGifWidth,m_iGifHeight,hDC,m_nPosX,m_nPosY,SRCCOPY);
	SelectObject(hMemDC1,hOldBitmap1);
	m_bLockBitmap=FALSE;
	m_iDisposalMethod=DISPOSAL_NOT;
	while(m_EndRun!=1)
	{
		systimer2=systimer1=GetTickCount();
		while(m_bLockBitmap);
		m_bLockBitmap=TRUE;
		hOldBitmap1=(HBITMAP)SelectObject(hMemDC1,m_hRedrawBitmap);
		//****************************************************
		//Restore Background
		switch(m_iDisposalMethod)
		{
		case DISPOSAL_NO:
			break;
		case DISPOSAL_NOT:
			break;
		case DISPOSAL_RESTBACK:
		case DISPOSAL_RESTORE:
			hOldBitmap=(HBITMAP)SelectObject(hMemDC,hPreviousBitmap);
			::BitBlt(hMemDC1,m_iLeft,m_iTop,m_iWidth,m_iHeight,hMemDC,0,0,SRCCOPY);
			SelectObject(hMemDC,hOldBitmap);
			DeleteObject(hPreviousBitmap);
			hPreviousBitmap=0;
			break;
		}
		m_iDisposalMethod=DISPOSAL_NO;
		//***************************************************
		//Start Output Image
	//if(m_bPause) hBitmap=hPauseBitmap;
	//else
	if(!PauseShow)	
	{
		hBitmap=NextImage();

		switch(m_iDisposalMethod)
		{
		case DISPOSAL_NO:
			break;
		case DISPOSAL_NOT:
			break;
		case DISPOSAL_RESTBACK:
		case DISPOSAL_RESTORE:
			hPreviousBitmap=::CreateCompatibleBitmap(hDC,m_iWidth,m_iHeight);
			hOldBitmap=(HBITMAP)SelectObject(hMemDC,hPreviousBitmap);
			::BitBlt(hMemDC,0,0,m_iWidth,m_iHeight,hMemDC1,m_iLeft,m_iTop,SRCCOPY);     
			SelectObject(hMemDC,hOldBitmap);
			break;
		}
		hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
		if(m_bTransparentIndex)	
		{
			HBITMAP    bmAndBack, bmAndObject;
			HBITMAP    bmBackOld, bmObjectOld;
			HDC        hdcBack, hdcObject;
			COLORREF cColor;
			
			hdcBack=::CreateCompatibleDC(hDC);
			hdcObject=::CreateCompatibleDC(hDC);
			bmAndBack=CreateBitmap(m_iWidth,m_iHeight,1,1,NULL);
			bmAndObject=CreateBitmap(m_iWidth,m_iHeight,1,1,NULL);
			bmBackOld=(HBITMAP)SelectObject(hdcBack,bmAndBack);
			bmObjectOld=(HBITMAP)SelectObject(hdcObject,bmAndObject);
			cColor=SetBkColor(hMemDC,m_TransparentColor);
			::BitBlt(hdcObject,0,0,m_iWidth,m_iHeight,hMemDC,0,0,SRCCOPY);
			SetBkColor(hMemDC,cColor);
			::BitBlt(hdcBack,0,0,m_iWidth,m_iHeight,hdcObject,0,0,NOTSRCCOPY);
			::BitBlt(hMemDC1,m_iLeft,m_iTop,m_iWidth,m_iHeight,hdcObject,0,0,SRCAND);
			::BitBlt(hMemDC,0,0,m_iWidth,m_iHeight,hdcBack,0,0,SRCAND);
			::BitBlt(hMemDC1,m_iLeft,m_iTop,m_iWidth,m_iHeight,hMemDC,0,0,SRCPAINT);
			DeleteObject(SelectObject(hdcBack,bmBackOld));
			DeleteObject(SelectObject(hdcObject,bmObjectOld));
			DeleteDC(hdcBack);
			DeleteDC(hdcObject);
		}
		else 
		{
			::BitBlt(hMemDC1,m_iLeft,m_iTop,m_iWidth,m_iHeight,hMemDC,0,0,SRCCOPY);
		}
		SelectObject(hMemDC,hOldBitmap);
		DeleteObject(hBitmap);
//		::BitBlt(hDC,m_nPosX,m_nPosY,m_iGifWidth,m_iGifHeight,hMemDC1,0,0,SRCCOPY);
		::StretchBlt(hDC,gifposition.left,gifposition.top, gifposition.Width(), gifposition.Height(), hMemDC1,0, 0, m_iGifWidth, m_iGifHeight, SRCCOPY );
		::BitBlt(hPauseMemDC,0,0,m_iGifWidth,m_iGifHeight,hMemDC1,0,0,SRCCOPY);

	}
		else////��ͣʱ��Ҫ����
		
//	    ::BitBlt(hDC,m_nPosX,m_nPosY,m_iGifWidth,m_iGifHeight,hPauseMemDC,0,0,SRCCOPY);
		::StretchBlt(hDC,gifposition.left,gifposition.top, gifposition.Width(), gifposition.Height(), hPauseMemDC,0, 0, m_iGifWidth, m_iGifHeight, SRCCOPY );	
		SelectObject(hMemDC1,hOldBitmap1);
		m_bLockBitmap=FALSE;
		if(m_iDelayTime!=0)speed=m_iDelayTime*10;else speed=m_dwSpeed;
		while((m_EndRun!=1)&&(speed>systimer2-systimer1))
		{
			Sleep(10);
			systimer2=GetTickCount();
		}
		PauseShow=m_bPause;
	}	
	if(hPreviousBitmap!=0)DeleteObject(hPreviousBitmap);
	DeleteDC(hMemDC);
	DeleteDC(hMemDC1);
	DeleteDC(hDC);
	::ReleaseDC(m_hWnd,hDC);
	m_EndRun=2;
	return TRUE;
}


void  CGif89a::Stop()
{
	// TODO: Add your implementation code here
	if(m_EndRun!=5)return;
	m_EndRun=1;
	while(m_EndRun!=2);
	return;
}

CGif89a::CGif89a()
{
	m_bPause=FALSE;
	m_bAutoStart=TRUE;
	m_bAutoSize1=TRUE;
	m_bEmbed=FALSE;
	m_pcGlobalColorTable=0;
	m_pcGif=0;
	m_iGifSize=0;
	m_iGlobalColorSize=0;
	m_bTransparentIndex=FALSE;
	m_iDelayTime=0;
	m_EndRun=0;
	m_dwSpeed=50;
	m_hRedrawBitmap=0;
	m_bLockBitmap=FALSE;
	flag=0;
	m_nPosX=0;
	m_nPosY=0;
	strcpy(filename,_T(""));
	m_bRunMode=1;
	m_bGlass=FALSE;
}

CGif89a::~CGif89a(void)
{
 Stop();
 if(m_hRedrawBitmap!=0)DeleteObject(m_hRedrawBitmap);
 if(m_pcGlobalColorTable!=NULL)delete[] m_pcGlobalColorTable;
 if(m_pcGif!=NULL)delete[] m_pcGif;
}



BOOL CGif89a::Load(LPCTSTR filename)
{
	HANDLE hFile;
	DWORD size,size1,readbyte;
	BYTE temp[13];
	if(m_bEmbed)return FALSE;
//free memory from previous image
	Stop();
	if(m_pcGlobalColorTable!=NULL)delete[] m_pcGlobalColorTable;
	if(m_pcGif!=NULL)delete[] m_pcGif;
	if(m_hRedrawBitmap!=0){DeleteObject(m_hRedrawBitmap);m_hRedrawBitmap=0;};
	m_pcGlobalColorTable=m_pcGif=0;
	m_iTotalReadByte=0;
	m_iGifSize=m_iGlobalColorSize=0;
	
	hFile=CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,NULL);
	if(INVALID_HANDLE_VALUE==hFile)return FALSE;
	size=GetFileSize(hFile,&size1);
	if(size==0xFFFFFFFF){CloseHandle(hFile);return FALSE;}
	ReadFile(hFile,temp,13,&readbyte,NULL);
	if((readbyte!=13)||((temp[0]!='G')||(temp[1]!='I')||(temp[2]!='F')||(temp[3]!='8')||((temp[4]!='7')&&(temp[4]!='9'))||(temp[5]!='a')))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	m_iGifWidth=*(WORD*)(temp+6);
	m_iGifHeight=*(WORD*)(temp+8);
	m_iBackgroundColor=temp[11];
	if(temp[10]&0x80)
	{
		m_iGlobalColorSize=0x01<<((temp[10]&0x07)+1);
		m_pcGlobalColorTable=new BYTE[3*m_iGlobalColorSize];
		ReadFile(hFile,m_pcGlobalColorTable,3*m_iGlobalColorSize,&readbyte,NULL);
		if(readbyte!=(DWORD)3*m_iGlobalColorSize)
		{
			delete[] m_pcGlobalColorTable;
			m_pcGlobalColorTable=0;
			m_iGlobalColorSize=0;
			CloseHandle(hFile);
			return FALSE;
		}
	}

	m_iGifSize=size-3*m_iGlobalColorSize-12;
	m_pcGifTrack=m_pcGif=new BYTE[m_iGifSize];
	ReadFile(hFile,m_pcGif,m_iGifSize,&readbyte,NULL);
	CloseHandle(hFile);
	return TRUE;
}

HBITMAP CGif89a::FirstImage(void)
{
	m_pcGifTrack=m_pcGif;
	m_iTotalReadByte=0;
	return NextImage();
}

HBITMAP CGif89a::NextImage(void)
{
 	if(m_pcGif==NULL)return 0;
l1:	if(m_iTotalReadByte>m_iGifSize){m_pcGifTrack=m_pcGif;m_iTotalReadByte=0;return 0;}
	m_iTotalReadByte++;
	switch(*m_pcGifTrack++)
	{
	case 0x2C:
		return TakeIt();
		break;
	case 0x21:
			BYTE cSize;
			m_iTotalReadByte++;
			switch(*m_pcGifTrack++)
			{ 
			case 0xF9:
				m_pcGifTrack++;//block size
				m_iDisposalMethod=(*m_pcGifTrack)&28;
				m_bTransparentIndex=(*m_pcGifTrack++)&1;
				m_iDelayTime=*(WORD*)m_pcGifTrack;
				m_pcGifTrack+=2;
				m_iTransparentIndex=*m_pcGifTrack++;
				m_iTotalReadByte+=5;
				break;
			case 0xFE:
				while((cSize=*m_pcGifTrack)!=0){m_pcGifTrack+=cSize+1;m_iTotalReadByte+=cSize+1;if(m_iTotalReadByte>m_iGifSize)return 0;}
				break;
			case 0x01:
				m_pcGifTrack+=13;
				m_iTotalReadByte+=13;
				while((cSize=*m_pcGifTrack)!=0){m_pcGifTrack+=cSize+1;m_iTotalReadByte+=cSize+1;if(m_iTotalReadByte>m_iGifSize)return 0;}
				break;
			case 0xFF:
				m_pcGifTrack+=12;
				m_iTotalReadByte+=12;
				while((cSize=*m_pcGifTrack)!=0){m_pcGifTrack+=cSize+1;m_iTotalReadByte+=cSize+1;if(m_iTotalReadByte>m_iGifSize)return 0;}
				break;
			default:
				return FALSE;
			}
			m_pcGifTrack++;
			m_iTotalReadByte++;
			if(m_iTotalReadByte>m_iGifSize)return 0;
			goto l1;
			break;
	case 0x3B:
		m_pcGifTrack=m_pcGif;
		m_iTotalReadByte=0;
		goto l1;
	case 0:
			goto l1;
	default: 
		return FALSE;
	}
}


//int nRet = ::StretchDIBits( pDC->m_hDC, m_nX, m_nY, m_nWidth, m_nHeight, 0, 0, m_nWidth, m_nHeight, 
//(const void FAR *) &pTemp[sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+m_nPaletteBytes], 
//(BITMAPINFO *) pBIH, DIB_RGB_COLORS, SRCCOPY );

HBITMAP CGif89a::TakeIt(void)
{
	UINT uLocalColorTableSize;
	WORD code,oldcode,code1;
	int iFinishCode,iResetCode;
	int iPrimaryTableSize,iTableSize;
	BITMAPINFOHEADER *bitmapheader;
	BYTE *pcColorTable;
	BYTE *pcInfo;
	GIFTABLE *pcGifTable;
	HBITMAP hBitmap;
	m_iLeft=*(WORD*)m_pcGifTrack;
	m_pcGifTrack+=2;
	m_iTop=*(WORD*)m_pcGifTrack;
	m_pcGifTrack+=2;
	m_iWidth=*(WORD*)m_pcGifTrack;
	m_pcGifTrack+=2;
	m_iWidth1=((m_iWidth-1)|0x3)+1;
	m_iHeight=*(WORD*)m_pcGifTrack;
	m_pcGifTrack+=2;
	m_cPackedField=*m_pcGifTrack++;
	m_iTotalReadByte+=9;
	m_iMaxByte=m_iWidth1*m_iHeight;
	pcInfo=new BYTE[256*sizeof(RGBQUAD)+sizeof(BITMAPINFOHEADER)+m_iMaxByte+sizeof(GIFTABLE)*4096];
	//1-BITMAPINFOHEADER
	//2-COLORTABLE
	//3-Bitmap bits
	//4-GIFTABLE;
	bitmapheader=(BITMAPINFOHEADER*)pcInfo;
	pcColorTable=pcInfo+sizeof(BITMAPINFOHEADER);
	m_pcBitmap=pcColorTable+256*sizeof(RGBQUAD);
	pcGifTable=(GIFTABLE*)(m_pcBitmap+m_iMaxByte);
	for(int i=0;i<4096;i++)pcGifTable[i].previouscode=pcGifTable[i].nextcode=0;
	bitmapheader->biSize=sizeof(BITMAPINFOHEADER);
	bitmapheader->biWidth=m_iWidth;
	bitmapheader->biHeight=-m_iHeight;
	bitmapheader->biPlanes=1;
	bitmapheader->biBitCount=8;
	bitmapheader->biCompression=BI_RGB;
	bitmapheader->biSizeImage=0;
	bitmapheader->biXPelsPerMeter=0;
	bitmapheader->biYPelsPerMeter=0;
	bitmapheader->biClrUsed=256;
	bitmapheader->biClrImportant=256;

	if(m_cPackedField&0x80)
	{
		uLocalColorTableSize=1;
		uLocalColorTableSize<<=(m_cPackedField&7)+1;
		if(m_bTransparentIndex)
		{
			m_TransparentColor=RGB(m_pcGifTrack[m_iTransparentIndex*3],m_pcGifTrack[m_iTransparentIndex*3+1],m_pcGifTrack[m_iTransparentIndex*3+2]);
		}
		m_iTotalReadByte+=uLocalColorTableSize*3;
		for(UINT i=0;i<uLocalColorTableSize;i++)
		{
			pcColorTable[2]=*m_pcGifTrack++;
			pcColorTable[1]=*m_pcGifTrack++;
			pcColorTable[0]=*m_pcGifTrack++;
			pcColorTable[3]=0;
			pcColorTable+=4;
		}

	}
	else 
	{
		BYTE *pcGlobalColor=m_pcGlobalColorTable;
		if(m_bTransparentIndex)
		{
			m_TransparentColor=RGB(pcGlobalColor[m_iTransparentIndex*3],pcGlobalColor[m_iTransparentIndex*3+1],pcGlobalColor[m_iTransparentIndex*3+2]);
		}
		for(int i=0;i<m_iGlobalColorSize;i++)
		{
			pcColorTable[2]=*pcGlobalColor++;
			pcColorTable[1]=*pcGlobalColor++;
			pcColorTable[0]=*pcGlobalColor++;
			pcColorTable[3]=0;
			pcColorTable+=4;
		}
	}
	m_uPrimaryBitSize=m_uBitSize=(*m_pcGifTrack++);
	m_iTotalReadByte++;
	iPrimaryTableSize=iTableSize=(1<<m_uBitSize)+2;
	iFinishCode=iTableSize-1;
	iResetCode=iFinishCode-1;

	m_uPrimaryBitSize++;
	m_uBitSize++;
	m_uRemain=0;
	m_cCurentByte=0;
	m_uBlockSize=0;
	m_uReadByte=1;
	m_x=m_y=0;
	m_iPass=1;m_iRow=0;
	while((code=GetCode())!=iFinishCode)
	{
		if(code==iResetCode)
		{
			m_uBitSize=m_uPrimaryBitSize;
			iTableSize=iPrimaryTableSize;
			oldcode=GetCode();
			if(oldcode>iTableSize){delete[] pcInfo;return 0;}
			Output((BYTE)oldcode);
			continue;
		}
		if(code<iTableSize) //<code> exist in the string pcGifTable
		{
			code1=code;
			WORD code2=0;
			while(code1>=iPrimaryTableSize)
			{
				pcGifTable[code1].nextcode=code2;
				code2=code1;
				code1=pcGifTable[code1].previouscode;
				if(code1>=code2){delete[] pcInfo;return 0;}
			}
			Output((BYTE)code1);
			while(code2!=0)
			{
				Output(pcGifTable[code2].bit);
				code2=pcGifTable[code2].nextcode;
			}
			pcGifTable[iTableSize].bit=(BYTE)code1;
			pcGifTable[iTableSize].previouscode=oldcode;
			iTableSize++;
			if(iTableSize==(0x0001<<m_uBitSize))m_uBitSize++;
			if(m_uBitSize>12)m_uBitSize=12;
			oldcode=code;
		} 
		else    //<code> doesn't exist in the string pcGifTable
		{
			code1=oldcode;
			WORD code2=0;
			while(code1>=iPrimaryTableSize)
			{
				pcGifTable[code1].nextcode=code2;
				code2=code1;
				code1=pcGifTable[code1].previouscode;
				if(code1>=code2){delete[] pcInfo;return 0;}
			}
			Output((BYTE)code1);
			while(code2!=0)
			{
				Output(pcGifTable[code2].bit);
				code2=pcGifTable[code2].nextcode;
			}
			Output((BYTE)code1);
			pcGifTable[iTableSize].bit=(BYTE)code1;
			pcGifTable[iTableSize].previouscode=oldcode;
			iTableSize++;
			if(iTableSize==(0x0001<<m_uBitSize))m_uBitSize++;
			if(m_uBitSize>12)m_uBitSize=12;
			oldcode=code;
		}
	}

	hBitmap=CreateDIBitmap(m_hDC,bitmapheader,CBM_INIT,m_pcBitmap,(BITMAPINFO*)pcInfo,DIB_RGB_COLORS);		
	m_pcGifTrack++;
	m_iTotalReadByte++;
	delete[] pcInfo;
	return hBitmap;
}

void CGif89a::SetPosition(int x,int y)
{
	m_nPosX=x;
	m_nPosY=y;
}

void CGif89a::Pause(BOOL status)
{
	m_bPause=status;
}

int CGif89a::GetWidth()
{
	return m_iGifWidth;
}

int CGif89a::GetHeight()
{
	return m_iGifHeight;
}
