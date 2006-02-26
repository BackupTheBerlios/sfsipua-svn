// IMToolWin.cpp : implementation file
//

#include "stdafx.h"
#include "cnicq.h"
#include "IMToolWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void CIMToolWinFolder::AddItem(const char *t, int img)
{
	CIMToolWinItem *item = new CIMToolWinItem(t, img);
	Items.push_back(item);

}

/////////////////////////////////////////////////////////////////////////////
// CIMToolWin

CIMToolWin::CIMToolWin()
{
	FolderBgColor = RGB(134,177,238);

	Icons = NULL;
}

CIMToolWin::~CIMToolWin()
{
}


BEGIN_MESSAGE_MAP(CIMToolWin, CWnd)
	//{{AFX_MSG_MAP(CIMToolWin)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CIMToolWin message handlers

void CIMToolWin::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	DrawAll(&dc);

}

int CIMToolWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//取应用程序的Skin对象
	m_pSkin = &(((CCNIcqApp *)AfxGetApp())->m_IMSkin);
	
	FolderBgColor = m_pSkin->MsgIWantColor;
	StartBgColor = m_pSkin->MsgWndSpaceTopLeftClr;
	EndBgColor = m_pSkin->MsgWndSpaceBottomRightClr;
	return 0;
}


int CIMToolWin::AddFolder(const char *text,int img)
{
	CIMToolWinFolder *f = new CIMToolWinFolder(text,img);
	folders.push_back(f);
	return folders.size() - 1;

}

void CIMToolWin::AddItem(int Folder, const char *t, int img)
{
	if (Folder >= 0 && Folder < GetFolderCount())
		folders[Folder]->AddItem(t, img);

}

int CIMToolWin::GetFolderCount()
{
	return folders.size();	
}


void CIMToolWin::DrawAll(CDC *pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CRect rcClient;
	GetClientRect(rcClient);
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());
	CBitmap *oldBitmap = memDC.SelectObject(&bm);

	//背景色
	PaintGradiantRect(&memDC,rcClient,StartBgColor,EndBgColor,false);

	int i;
	for (i = folders.size() - 1; i >= 0; i--)
		DrawFolder(&memDC, i);


	pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBitmap);

}

void CIMToolWin::DrawFolder(CDC *pDC, int Folder)
{
	CRect rc;
	CRect FolderRc;

	GetClientRect(rc);

	FolderRc = CRect(rc.left,rc.top + Folder * TOOLWIN_ITEM_HEIGHT,rc.right,rc.top + (Folder +1) * TOOLWIN_ITEM_HEIGHT);

	//背景
	pDC->FillSolidRect(FolderRc,FolderBgColor);
	

	//第一条线
	PaintGradiantRect(pDC,CRect(FolderRc.left,FolderRc.bottom,FolderRc.right,FolderRc.bottom + 1),RGB(0,0,0),FolderBgColor);
	//第二条线
	PaintGradiantRect(pDC,CRect(FolderRc.left,FolderRc.bottom+1,FolderRc.right,FolderRc.bottom + 2),RGB(255,255,255),FolderBgColor);

	//标签
	CFont *oldFont = pDC->SelectObject(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);

	if( (folders[Folder]->Image != -1) && (Icons != NULL))
	{
		//输出图标
		Icons->Draw(pDC,folders[Folder]->Image,
			CPoint(FolderRc.left + 2,FolderRc.top + 2),ILD_TRANSPARENT);
		FolderRc.OffsetRect(25,0);
	}
	else
	{
		FolderRc.OffsetRect(5,0);
	}

	//输出文字
	pDC->DrawText(folders[Folder]->Title, FolderRc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

	pDC->SetBkMode(oldBkMode);
	pDC->SelectObject(oldFont);

}

void CIMToolWin::SetImageList(CImageList *ImageList)
{
	Icons = ImageList;
}

DWORD CIMToolWin::SetColor(BYTE byColorIndex, COLORREF crColor, BOOL bRepaint)
{
	if (byColorIndex >= TOOLWIN_MAX_COLORS)	
		return -1;

	m_crColors[byColorIndex] = crColor;

	if (bRepaint)	Invalidate();

	return 0;
}

void CIMToolWin::OnMouseMove(UINT nFlags, CPoint point) 
{
	//检查落在哪个项目上

	CWnd::OnMouseMove(nFlags, point);
}
