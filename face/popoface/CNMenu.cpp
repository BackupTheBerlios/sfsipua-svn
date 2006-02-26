/**********************************************************************
//				类Office XP、OICQ外观的菜单类
//						-- 抽取自 临风程序界面类库CNdows.lib
//
//作者：临风        整理：YZ
//
//版本：0.1
//
//声明：  本类库可以自由使用而不须对作者作出任何回报，但作者希望能得到
//		  你的鼓励和支持。你可以对类库源码作出修改和改进，但希望你能在
//		  修改的同时给作者一份同样的副本。
//		  本类库不得用于任何商业用途，如确实需要，请与作者联系。
//
//e-mail:CNphone@sina.com
//
//原文件名：rcm.cpp
//
//说明：CNmenu 类定义文件
//
**********************************************************************/


//#define OEMRESOURCE		// 此定义应加到stdafx.h中的首部

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include "CNMenu.h"

CNMenu::CNMenu(HINSTANCE hInst)
{
	m_hMenu = NULL;
	m_hCurrMenu = NULL;
	m_hInst = hInst;
}

CNMenu::CNMenu(HINSTANCE hInst, LPCTSTR lpMenuname)
{
	m_hMenu = NULL;
	m_hCurrMenu = NULL;
	m_hInst = hInst;
	Load(lpMenuname);
}

CNMenu::~CNMenu()
{
	m_hCurrMenu = NULL;
	if(m_hMenu != NULL)
		DestroyMenu(m_hMenu);
}

BOOL CNMenu::Load(LPCTSTR lpMenuname)
{
	if(m_hMenu != NULL)
   		return FALSE;
	else
	{
		m_hMenu = LoadMenu(m_hInst,lpMenuname);
		if(m_hMenu)
		{
			m_hCurrMenu = m_hMenu;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CNMenu::LoadPopup(LPCTSTR lpMenuname,UINT nIndex)
{
	if(!m_hMenu)
		m_hMenu = LoadMenu(m_hInst,lpMenuname);

	m_hCurrMenu = GetSubMenu(m_hMenu,nIndex);

	return (BOOL)m_hCurrMenu;
}

BOOL CNMenu::Attach(HMENU hMenu)
{
	m_hMenu = hMenu;
	return TRUE;
}

HMENU CNMenu::Detach()
{
	HMENU hTemp= m_hMenu;

	m_hMenu = NULL;
	return hTemp;
}

BOOL CNMenu::Create()
{
	if(m_hMenu != NULL)
		return FALSE;
	else
	{
		m_hMenu = CreateMenu();
		if(m_hMenu)
		{
			m_hCurrMenu = m_hMenu;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CNMenu::CreatePopup()
{
	if(m_hMenu != NULL)
		return FALSE;
	else
	{
		m_hMenu = CreatePopupMenu();
		if(m_hMenu)
		{
			m_hCurrMenu = m_hMenu;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CNMenu::Popup(HWND hWnd,int x,int y)
{
	if(m_hCurrMenu != NULL)
	{
		//以下两行语句防止菜单弹出后鼠标在菜单外点击菜单不消失
		SetForegroundWindow(hWnd);
		SetActiveWindow(hWnd);

		if(x == -999 && y == -999)
		{
			POINT pt;

			GetCursorPos(&pt);
			x = pt.x;
			y = pt.y;
		}

		TrackPopupMenuEx(m_hCurrMenu,
			TPM_LEFTALIGN | TPM_TOPALIGN |		// default values
			TPM_HORIZONTAL | TPM_LEFTBUTTON |	// equivalent to 0
			TPM_RIGHTBUTTON,					// Right selection
			x,y,
			hWnd,
			NULL);
		return TRUE;
	}
	return FALSE;
}

BOOL CNMenu::Insert(UINT uid,UINT nIndex,LPSTR szText,UINT flag)
{
	MENUITEMINFO mi;

	if(!m_hCurrMenu)
		return FALSE;


	mi.cbSize = sizeof(mi);

	mi.fMask = MIIM_TYPE | MIIM_ID;
	mi.wID = uid;
	mi.fType = MFT_STRING;
	mi.fState = MFS_DEFAULT;
	mi.dwTypeData = szText;
	mi.cch = strlen(szText);

	return InsertMenuItem(m_hCurrMenu,nIndex,flag,&mi);
}

BOOL CNMenu::InsertSep(UINT nIndex,UINT flag)
{
	MENUITEMINFO mi;

	if(!m_hCurrMenu)
		return FALSE;


	mi.cbSize=sizeof(mi);

	mi.fMask=MIIM_TYPE | MIIM_ID;
	mi.fType=MFT_SEPARATOR;
	mi.fState=MFS_DEFAULT;

	return InsertMenuItem(m_hCurrMenu,nIndex,flag,&mi);
}

BOOL CNMenu::Delete(UINT nIndex,UINT uPos)
{
	if(!m_hCurrMenu)
		return FALSE;

	return DeleteMenu(m_hCurrMenu,nIndex,uPos);
}

//根据菜单项ID得到序号
int CNMenu::GetItemIndex(UINT uIndex)
{
	MENUITEMINFO mi;

	mi.cbSize=sizeof(mi);
	mi.fMask = MIIM_ID;
	if(!GetMenuItemInfo(m_hCurrMenu,uIndex,FALSE,&mi))
		return -1;

	int nItem = GetMenuItemCount(m_hCurrMenu);
	while((--nItem)>=0)
	{
		if(mi.wID == uIndex)
			return nItem;
	}
	return nItem;
}

//根据菜单项序号得到ID
int CNMenu::GetItemId(UINT uIndex)
{
	MENUITEMINFO mi;

	mi.cbSize=sizeof(mi);
	mi.fMask = MIIM_ID;

	if(!GetMenuItemInfo(m_hCurrMenu,uIndex,TRUE,&mi))
		return -1;
	else
		return mi.wID;
}

HMENU CNMenu::GetItem(UINT uIndex)
{
	return GetSubMenu(m_hCurrMenu,uIndex);
}

void CNMenu::Update(HWND hWnd)
{
	DrawMenuBar(hWnd);
}

void CNMenu::SetCheckBmp(UINT uIndex,UINT uFlag,HBITMAP hbmCheck,HBITMAP hbmUncheck)
{
	SetMenuItemBitmaps(m_hCurrMenu,uIndex,uFlag,hbmUncheck,hbmCheck);
}

DWORD CNMenu::CheckItem(UINT uIndex,BOOL bChecked,UINT uFlag)
{
	UINT flag;

	if(bChecked)
		flag = MF_CHECKED | uFlag;
	else
		flag = MF_UNCHECKED | uFlag;

	return CheckMenuItem(m_hCurrMenu,uIndex,flag);
}

BOOL CNMenu::CheckRadioItem(UINT idFirst,UINT idEnd,UINT uIndex,UINT uFlag)
{
	return CheckMenuRadioItem(m_hCurrMenu,idFirst,idEnd,uIndex,uFlag);
}

void CNMenu::EnableItem(UINT uIndex,BOOL bEnable,UINT uFlag)
{
	UINT flag;

	if(bEnable)
		flag = MF_ENABLED | uFlag;
	else
		flag = MF_DISABLED | uFlag;

	EnableMenuItem(m_hCurrMenu,uIndex,flag);
}


///////////////////////////////////////////////////
//
//CNCoolMenu
//
//说明：
//		CNCoolMenu初始化时（当Load菜单或Attach时）会初始化所有子菜单的菜单项
//		设置菜单项为自绘形式，为每一个子菜单构造一个对象，但Load或Attach的菜单
//		的菜单项（即m_hMenu）不做设置，除非构造CNCoolMenu(hMenu,FALSE)，这是
//		因为m_hMenu可能是窗口固定菜单或弹出式菜单的父菜单，不恶意使用的话，
//		m_hMenu一定是一个Drop-down或Pop-up菜单句柄，设置自绘没有必要，所以如果
//		建立一个CNCoolMenu对象rm,所有设置都应该是调用其子对象（子菜单项）的成
//		员函数，即rm.SubMenu(n)->Func()形式，但这样使用比较麻烦，所以有一个成员
//		数据m_Popup和成员函数LoadPopup起到重定向作用，即可以先调用LoadPopup把一
//		个子菜单项指定给rm，那么以后所有的rm.Func()都会自动重定向到该子菜单。
//
//////////////////////////////////////////////////

HBITMAP CNCoolMenu::m_hbmCheck = NULL;
HBITMAP CNCoolMenu::m_hbmRadio = NULL;
int CNCoolMenu::m_id = 0;
int CNCoolMenu::m_cxFont = 0;
int CNCoolMenu::m_cyFont = 0;
HFONT CNCoolMenu::m_hFont = NULL;


CNCoolMenu::CNCoolMenu(HINSTANCE hInst) : CNMenu(hInst)
{
	Init();
}

CNCoolMenu::CNCoolMenu(HINSTANCE hInst, LPCTSTR lpMenuname) : CNMenu(hInst, lpMenuname)
{
	Init();
	Load(lpMenuname);
}

//参数bParent由InitSubMenu调用，手工调用除非有目的，否则请使用默认参数
CNCoolMenu::CNCoolMenu(HINSTANCE hInst, HMENU hMenu,BOOL bParent) : CNMenu(hInst)
{
	Init();
	Attach(hMenu);

	if(!bParent)
		Remap();
}

BOOL CNCoolMenu::Load(LPCTSTR lpMenuname)
{
	if(m_hMenu)
		return FALSE;
	else
	{
		BOOL bOK = CNMenu::Load(lpMenuname);
		InitSubMenu();
		return bOK;
	}
}

BOOL CNCoolMenu::Attach(HMENU hMenu)
{
	if(m_hMenu)
		if(m_hMenu == hMenu)
			return TRUE;
		else
			return FALSE;
	else
	{
		m_hMenu = hMenu;
		m_hCurrMenu = m_hMenu;
		InitSubMenu();
	}
	return TRUE;
}

HMENU CNCoolMenu::Detach()
{
	if(!m_hMenu)
		return NULL;

	HMENU hTemp = m_hMenu;

	Reset();

	if(m_lprms != NULL)
		m_lprms = (LPCNMENUSTYLE)Del(m_lprms);

	m_hMenu = NULL;
	m_hCurrMenu = NULL;

	return hTemp;
}

BOOL CNCoolMenu::LoadPopup(LPCTSTR lpMenuname,UINT nIndex)
{
	BOOL bOK = CNMenu::LoadPopup(lpMenuname,nIndex);

	InitSubMenu();

	if(bOK && m_SubMenu)
		for(int i=0;i<m_nSubMenuCnt;i++)
			if(m_SubMenu[i] && m_hCurrMenu == m_SubMenu[i]->m_hMenu)
			{
				m_Popup = m_SubMenu[i];
				break;
			}
	return bOK;
}

CNCoolMenu::~CNCoolMenu()
{
	if(m_Style.hbrBkg != (HBRUSH)(COLOR_MENU + 1))
		DeleteObject(m_Style.hbrBkg);

	if(m_Style.hbrHilight != (HBRUSH)(COLOR_HIGHLIGHT + 1))
		DeleteObject(m_Style.hbrHilight);

	m_Style.crText = GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_Style.crTextDef = GetSysColor(COLOR_MENUTEXT);
	m_Style.uSelectRect = 0;
	m_Style.uMarkerX = 0;
	m_Style.uMarkerY = 0;
	m_Style.uBkgY = 0;
	m_ItemIconPos = 0;

	m_Popup = NULL;
	m_bInited = FALSE;
	m_nSubMenuCnt = 0;

	if(m_lprms != NULL)
		m_lprms = (LPCNMENUSTYLE)Del(m_lprms);

	if(m_SubMenu)
	{
		for(int i=0;i<m_nSubMenuCnt;i++)
		if(m_SubMenu[i])
			delete m_SubMenu[i];
		m_SubMenu = (CNCoolMenu**)Del(m_SubMenu);
	}

	m_id --;
	if(m_id == 0)
	{
		DeleteObject(m_hbmCheck);
		DeleteObject(m_hbmRadio);
	}
}

void CNCoolMenu::Free()
{
	if(m_Style.hbmBkg != NULL)
		DeleteObject(m_Style.hbmBkg);
	if(m_Style.hbmMarker != NULL)
		DeleteObject(m_Style.hbmMarker);
	if(m_Style.hbmHilight != NULL)
		DeleteObject(m_Style.hbmHilight);
	DestroyMenu(m_hMenu);
}

void CNCoolMenu::Init()
{
	m_Popup = NULL;
	m_bInited = FALSE;
	m_Style.hbmBkg = NULL;
	m_Style.hbmMarker = NULL;
	m_Style.hbmHilight = NULL;
	m_Style.hbrBkg = (HBRUSH)(COLOR_MENU + 1);
	m_Style.hbrHilight = (HBRUSH)(COLOR_HIGHLIGHT + 1);
	m_Style.crText = GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_Style.crTextDef = GetSysColor(COLOR_MENUTEXT);
	m_Style.uSelectRect = 0;
	m_Style.uMarkerX = 0;
	m_Style.uMarkerY = 0;
	m_Style.uBkgY = 0;

	m_lprms = NULL;
	m_SubMenu = NULL;
	m_nSubMenuCnt = 0;

	//初始化菜单项默认Check图案
	if(m_id == 0)
	{
		HDC hDC = GetDC(NULL);

		m_hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		HFONT hft = (HFONT)SelectObject(hDC,m_hFont);

		SIZE s;

		GetTextExtentPoint32(hDC,"A",1,&s);
		m_cxFont = s.cx;
		m_cyFont = s.cy;
		if(m_cyFont < 20)
			m_cyFont = 20;
		SelectObject(hDC,hft);

		HBITMAP hbmCheck = LoadBitmap((HINSTANCE) NULL,(LPTSTR)OBM_CHECK);
		HBITMAP hbmRadio = LoadBitmap((HINSTANCE) NULL,(LPTSTR)OBM_BTNCORNERS);
		BITMAP bm;
		HDC hDstDC = CreateCompatibleDC(hDC);
		HDC hSrcDC = CreateCompatibleDC(hDC);
		m_hbmCheck = CreateCompatibleBitmap(hDC,m_cyFont,m_cyFont);
		m_hbmRadio = CreateCompatibleBitmap(hDC,m_cyFont,m_cyFont);

		GetObject(hbmCheck,sizeof(BITMAP),&bm);

		SelectObject(hDstDC,m_hbmCheck);
		SelectObject(hSrcDC,hbmCheck);
		BitBlt(hDstDC,0,0,m_cyFont,m_cyFont,hSrcDC,0,0,WHITENESS);
		BitBlt(hDstDC,(m_cyFont - bm.bmWidth) >> 1,(m_cyFont - bm.bmHeight) >> 1,bm.bmWidth,bm.bmHeight,hSrcDC,0,0,SRCCOPY);

		ZeroMemory(&bm,sizeof(BITMAP));
		GetObject(hbmRadio,sizeof(BITMAP),&bm);

		SelectObject(hDstDC,m_hbmRadio);
		SelectObject(hSrcDC,hbmRadio);
		BitBlt(hDstDC,0,0,m_cyFont,m_cyFont,hSrcDC,0,0,WHITENESS);
		BitBlt(hDstDC,(m_cyFont - bm.bmWidth) >> 1,(m_cyFont - bm.bmHeight) >> 1,bm.bmWidth,bm.bmHeight,hSrcDC,0,0,SRCCOPY);

		DeleteDC(hSrcDC);
		DeleteDC(hDstDC);
		DeleteObject(hbmCheck);
		DeleteObject(hbmRadio);

		ReleaseDC(NULL,hDC);
	}
	m_id ++;

	m_DrawItemFunc = CNCoolMenu_DrawItem_def;
	m_ItemIconPos = 0;
	m_SepData.hIcon = NULL;
	m_SepData.uID = 0;
	m_SepData.pMenu = this;
}

void CNCoolMenu::InitSubMenu()
{
	if(m_hMenu && !m_bInited)
	{
		int nItem = GetMenuItemCount(m_hMenu);
		int i,j;
		HMENU hTemp;

		m_bInited = TRUE;

		for(i=0;i<nItem;i++)
		{
			if(GetSubMenu(m_hMenu,i))
				m_nSubMenuCnt ++;
		}

		if(m_nSubMenuCnt > 0)
		{
			m_SubMenu = (CNCoolMenu**)New(m_nSubMenuCnt * sizeof(CNCoolMenu*));
			if(m_SubMenu)
				for(i=0,j=0;i<nItem;i++)
				{
					hTemp = GetSubMenu(m_hMenu,i);
					if(hTemp)
					{
						try
						{
							m_SubMenu[j] = new CNCoolMenu(m_hInst, hTemp,FALSE);
							j++;
						}
						catch(char *str)
						{
							abort();
						}
					}
				}
		}
	}
}

CNCoolMenu* CNCoolMenu::SubMenu(int i)
{
	if(m_SubMenu && i < m_nSubMenuCnt && i >=0)
	if(m_SubMenu[i])
		return m_SubMenu[i];

	return this;
}

BOOL CNCoolMenu::Draw(LPDRAWITEMSTRUCT lps)
{
	if(lps->CtlType == ODT_MENU && (lps->itemAction == ODA_DRAWENTIRE || lps->itemAction == ODA_SELECT))
	{
		LPCNMENUSTYLE lprms = (LPCNMENUSTYLE)lps->itemData;

		if(lprms)
		{
			if(lprms->pMenu == this || !lprms->pMenu)
				if(m_Popup)
					m_Popup->m_DrawItemFunc(m_Popup,lps);
				else
					m_DrawItemFunc(this,lps);
			else
				lprms->pMenu->m_DrawItemFunc(lprms->pMenu,lps);
		}
	}
	return TRUE;
/*/
	if(lps->hwndItem == m_hMenu)
	{
		m_DrawItemFunc(this,lps);
		return TRUE;
	}
	else
		if(m_SubMenu)
			for(int i=0;i<m_nSubMenuCnt;i++)
				if(m_SubMenu[i] && m_SubMenu[i]->Draw(lps))
					return TRUE;
	}
	return FALSE;
/*/
}

BOOL CNCoolMenu::MeasureItem(LPMEASUREITEMSTRUCT pmis)
{
	if(pmis->CtlType == ODT_MENU)
	{
		LPCNMENUSTYLE lprms;

		if(pmis->itemData)
		{
			lprms = (LPCNMENUSTYLE)pmis->itemData;

			if(lprms->pMenu != this && lprms->pMenu)
				return lprms->pMenu->MeasureItem(pmis);
		}

		MENUITEMINFO mi;

		mi.cbSize=sizeof(mi);
		mi.fMask = MIIM_TYPE;

		GetMenuItemInfo(m_hCurrMenu,pmis->itemID,FALSE,&mi);

		if((mi.fType & MFT_SEPARATOR))
		{
			pmis->itemWidth = 0;
			pmis->itemHeight = MENUSEP_HEIGHT;
		}
		else
		{
			char txt[MAX_MENUTEXT];
			txt[0] = '\0';
			GetMenuString(m_hMenu,pmis->itemID,txt,MAX_MENUTEXT,MF_BYCOMMAND);
			if(!(mi.fType & MFT_BITMAP))
			{
				pmis->itemWidth = m_cxFont * strlen(txt) + 16 + m_Style.uMarkerX + (m_cyFont << 1);
				pmis->itemHeight = m_cyFont;
			}
		}
	}
   return TRUE;
}

HICON CNCoolMenu::SetItemIcon(UINT nIndex,HICON hicon)
{
	if(m_Popup)
		return m_Popup->SetItemIcon(nIndex,hicon);

	int nItem = GetMenuItemCount(m_hCurrMenu);
	int i;
	HICON hTemp;

	if(m_lprms == NULL)
		return hicon;

	for(i=0;i<=nItem;i++)
	{
		if(m_lprms[i].uID == nIndex)
		{
			hTemp = m_lprms[i].hIcon;
			m_lprms[i].hIcon = hicon;
			m_lprms[i].uID = nIndex;
			break;
		}
	}
	return hTemp;
}

DWORD CNCoolMenu::CheckItem(UINT uIndex,BOOL bChecked,UINT uFlag)
{
	if(m_Popup)
		return m_Popup->CheckItem(uIndex,bChecked,uFlag);

	UINT id;

	if(uFlag == BY_POSITION)
		id = GetItemId(uIndex);
	else
		id = uIndex;

	SetCheckItem(id);
	m_ItemIconPos = m_cyFont;

	return CNMenu::CheckItem(uIndex,bChecked,uFlag);
}

BOOL CNCoolMenu::CheckRadioItem(UINT idFirst,UINT idEnd,UINT uIndex,UINT uFlag)
{
	if(m_Popup)
		return m_Popup->CheckRadioItem(idFirst,idEnd,uIndex,uFlag);

	MENUITEMINFO mi;

	for(UINT i=idFirst;i<=idEnd;i++)
	{
		ZeroMemory(&mi,sizeof(mi));
		mi.cbSize=sizeof(mi);
		mi.fMask = MIIM_ID | MIIM_DATA;

		GetMenuItemInfo(m_hCurrMenu,i,uFlag,&mi);

		SetCheckItem(mi.wID,MENUCHECK_RADIO);
	}

	m_ItemIconPos = m_cyFont;

	return CheckMenuRadioItem(m_hCurrMenu,idFirst,idEnd,uIndex,uFlag);
}

BOOL CNCoolMenu::SetCheckItem(UINT uIndex,int nType)
{
	MENUITEMINFO mi;

	ZeroMemory(&mi,sizeof(mi));

	mi.cbSize=sizeof(mi);
	mi.fMask = MIIM_CHECKMARKS;

	GetMenuItemInfo(m_hCurrMenu,uIndex,FALSE,&mi);

	if(!mi.hbmpChecked && !mi.hbmpUnchecked)
		if(nType == MENUCHECK_CHECKBOX)
			mi.hbmpChecked = m_hbmCheck;
		else
			mi.hbmpChecked = m_hbmRadio;

	SetMenuItemInfo(m_hCurrMenu,uIndex,FALSE,&mi);

	return TRUE;
}

HBITMAP CNCoolMenu::SetBkg(HBITMAP hbmBkg)
{
	if(m_Popup)
		return m_Popup->SetBkg(hbmBkg);

	HBITMAP hbmtemp = m_Style.hbmBkg;
	m_Style.hbmBkg = hbmBkg;

	if(hbmBkg)
	{
		BITMAP bm;
		GetObject(hbmBkg,sizeof(BITMAP),&bm);
		m_Style.uBkgY = (UINT)bm.bmHeight;
	}
	else
		m_Style.uBkgY = 0;

	return hbmtemp;
}

void CNCoolMenu::SetColor(COLORREF crBkg,COLORREF crHilight,COLORREF crBkgText,COLORREF crSelText)
{
	if(crBkg != COLOR_PREV && crBkg != COLOR_TRANSPARENT)
	{
		if(m_Style.hbrBkg != (HBRUSH)(COLOR_MENU + 1))
			DeleteObject(m_Style.hbrBkg);

		if(crBkg == COLOR_DEF)
			m_Style.hbrBkg = (HBRUSH)(COLOR_MENU + 1);
		else
			m_Style.hbrBkg = CreateSolidBrush(crBkg);
	}

	if(crHilight != COLOR_PREV)
	{
		if(m_Style.hbrHilight != (HBRUSH)(COLOR_HIGHLIGHT + 1))
			DeleteObject(m_Style.hbrHilight);

		if(crHilight == COLOR_TRANSPARENT)
			m_Style.hbrHilight = (HBRUSH)GetStockObject(NULL_BRUSH);
		else if(crHilight == COLOR_DEF)
			m_Style.hbrHilight = (HBRUSH)(COLOR_HIGHLIGHT + 1);
		else
			m_Style.hbrHilight = CreateSolidBrush(crHilight);
	}

	if(crBkgText != COLOR_TRANSPARENT && crBkgText != COLOR_PREV)
		if(crBkgText == COLOR_DEF)
			m_Style.crTextDef = GetSysColor(COLOR_MENUTEXT);
		else
			m_Style.crTextDef = crBkgText;

	if(crSelText != COLOR_TRANSPARENT && crSelText != COLOR_PREV)
		if(crSelText == COLOR_DEF)
			m_Style.crText = GetSysColor(COLOR_HIGHLIGHTTEXT);
		else
			m_Style.crText = crSelText;

	if(m_SubMenu)
		for(int i=0;i<m_nSubMenuCnt;i++)
			if(m_SubMenu[i])
				m_SubMenu[i]->SetColor(crBkg,crHilight,crBkgText,crSelText);
}

HBITMAP CNCoolMenu::SetSelectBkg(HBITMAP hbmHilight,COLORREF crText)
{
	HBITMAP hbmtemp = m_Style.hbmHilight;

	m_Style.hbmHilight = hbmHilight;

	if(crText != COLOR_TRANSPARENT && crText != COLOR_PREV)
		if(crText == COLOR_DEF)
			m_Style.crText = GetSysColor(COLOR_HIGHLIGHTTEXT);
		else
			m_Style.crText = crText;

	if(m_SubMenu)
		for(int i=0;i<m_nSubMenuCnt;i++)
			if(m_SubMenu[i])
				m_SubMenu[i]->SetSelectBkg(hbmHilight,crText);

	return hbmtemp;
}

void CNCoolMenu::SetSelectRectType(UINT uRectStyle)
{
	m_Style.uSelectRect = uRectStyle;

	if(m_SubMenu)
		for(int i=0;i<m_nSubMenuCnt;i++)
			if(m_SubMenu[i])
				m_SubMenu[i]->SetSelectRectType(uRectStyle);
}

HBITMAP CNCoolMenu::SetMarker(HBITMAP hbmMarker)
{
   if(m_Popup)
   	return m_Popup->SetMarker(hbmMarker);

   HBITMAP hbmtemp = m_Style.hbmMarker;
	m_Style.hbmMarker = hbmMarker;

   if(hbmMarker)
   {
   	BITMAP bm;
      GetObject(hbmMarker,sizeof(BITMAP),&bm);
      m_Style.uMarkerX = (UINT)bm.bmWidth;
      m_Style.uMarkerY = (UINT)bm.bmHeight;
   }
   else
   {
   	m_Style.uMarkerX = 0;
      m_Style.uMarkerY = 0;
   }
   return hbmtemp;
}

BOOL CNCoolMenu::Remap()
{
	int nItem = GetMenuItemCount(m_hCurrMenu);
   MENUITEMINFO mi;
   int i = 0;

   if(m_lprms == NULL)
   {
      m_nItemCnt = nItem + 1;
   	m_lprms = (LPCNMENUSTYLE)New(m_nItemCnt * sizeof(CNMENUSTYLE));
   	if(m_lprms == NULL)
   		return FALSE;
      for(int i=0;i<=nItem;i++)
      	m_lprms[i].uID = 0xffffffff;
   }
   else
   	return TRUE;

   m_Style.nMenuHeight = 0;

	while ((--nItem)>=0)
	{
      ZeroMemory(&mi,sizeof(mi));

   	mi.cbSize = sizeof(mi);
	   mi.fMask = MIIM_DATA | MIIM_ID | MIIM_TYPE;

		GetMenuItemInfo(m_hCurrMenu,nItem,TRUE,&mi);

      if((mi.fType & MFT_SEPARATOR))
      {
      	m_Style.nMenuHeight += MENUSEP_HEIGHT;
         mi.dwItemData = (DWORD)&m_SepData;
      }
      else
      {
      	m_Style.nMenuHeight += m_cyFont;
         mi.dwItemData = (DWORD)&m_lprms[i];
      }

     	if(!(mi.fType & MFT_OWNERDRAW) && !(mi.fType & MFT_BITMAP))
      {
         m_lprms[i].uID = mi.wID;
         m_lprms[i].pMenu = this;

         mi.fType |= MFT_OWNERDRAW;
         SetMenuItemInfo(m_hCurrMenu,nItem,TRUE,&mi);
         if(!(mi.fType & MFT_SEPARATOR))
	         i++;
		}
	}
   return TRUE;
}

void CNCoolMenu::Reset()
{
	int nItem = GetMenuItemCount(m_hCurrMenu);
   MENUITEMINFO mi;
   char txt[MAX_MENUTEXT];

   m_Style.nMenuHeight = 0;

	while ((--nItem)>=0)
	{
      ZeroMemory(&mi,sizeof(mi));

   	mi.cbSize = sizeof(mi);
	   mi.fMask = MIIM_TYPE | MIIM_DATA | MIIM_STATE | MIIM_CHECKMARKS;
      txt[0] = '\0';
		GetMenuString(m_hCurrMenu,nItem,txt,MAX_MENUTEXT,MF_BYPOSITION);

		GetMenuItemInfo(m_hCurrMenu,nItem,TRUE,&mi);

     	if((mi.fType & MFT_OWNERDRAW))
      {
         mi.fType ^= MFT_OWNERDRAW;
         mi.dwItemData = NULL;
         mi.dwTypeData = txt;
         if(mi.hbmpChecked == m_hbmCheck || mi.hbmpChecked == m_hbmRadio)
         	mi.hbmpChecked = NULL;
         SetMenuItemInfo(m_hCurrMenu,nItem,TRUE,&mi);
		}
	}

   if(m_SubMenu)
     	for(int i=0;i<m_nSubMenuCnt;i++)
        	if(m_SubMenu[i])
         	m_SubMenu[i]->Reset();
}

BOOL CNCoolMenu::Insert(UINT uid,UINT nIndex,LPSTR szText,UINT flag)
{
   if(m_Popup)
   	return m_Popup->Insert(uid,nIndex,szText,flag);

	if(!m_hMenu)
     	return FALSE;

   if(!m_lprms)
   	Remap();


   MENUITEMINFO mi;

   BOOL bOK;


   mi.cbSize = sizeof(mi);

   mi.fMask = MIIM_TYPE | MIIM_ID;
   mi.wID = uid;
   mi.fType = MFT_STRING;
   mi.fState = MFS_DEFAULT;
   mi.dwTypeData = szText;
   mi.cch = strlen(szText);

  	bOK = InsertMenuItem(m_hMenu,nIndex,flag,&mi);
   if(bOK)
   {
      int nItem = GetMenuItemCount(m_hMenu);
      int i;
      for(i=0;i<=nItem;i++)
      	if(m_lprms[i].uID == 0xffffffff)
         {
         	m_lprms[i].uID = uid;
            m_lprms[i].pMenu = this;
            break;
         }

      mi.fType |= MFT_OWNERDRAW;
      mi.fMask = MIIM_DATA | MIIM_TYPE | MIIM_ID;
      mi.dwItemData = (DWORD)&m_lprms[i];

      SetMenuItemInfo(m_hCurrMenu,nIndex,flag,&mi);
   	m_Style.nMenuHeight += m_cyFont;
      if(i >= m_nItemCnt -1)
      	ResetItemData();
   }
   return bOK;
}

BOOL CNCoolMenu::InsertSep(UINT nIndex,UINT flag)
{
   if(m_Popup)
   	return m_Popup->InsertSep(nIndex,flag);

	MENUITEMINFO mi;
   BOOL bOK;

   if(!m_hCurrMenu)
     	return FALSE;


   mi.cbSize=sizeof(mi);

   mi.fMask = MIIM_DATA | MIIM_TYPE | MIIM_ID;
   mi.fType=MFT_SEPARATOR | MFT_OWNERDRAW;
   mi.fState=MFS_DEFAULT;
   mi.dwItemData = (DWORD)&m_SepData;

  	bOK = InsertMenuItem(m_hCurrMenu,nIndex,flag,&mi);
   if(bOK)
   	m_Style.nMenuHeight += MENUSEP_HEIGHT;

   return bOK;
}

//每个菜单项绑定一个CNMENUSTYLE,当菜单项超出m_lprms长度时，
//重新调整该缓冲区，并重新设置菜单项的itemData
void CNCoolMenu::ResetItemData()
{
   int nItem = GetMenuItemCount(m_hMenu);
   int i = 0;
   m_nItemCnt += MENU_PER_INSERT + 1;
	LPCNMENUSTYLE temp = (LPCNMENUSTYLE)New(m_nItemCnt * sizeof(CNMENUSTYLE));
   LPCNMENUSTYLE temp1;

   if(temp == NULL)
  		return;

   for(int j=0;j<m_nItemCnt;j++)
   	temp[j].uID = 0xffffffff;

   MENUITEMINFO mi;
   ZeroMemory(&mi,sizeof(mi));

   mi.cbSize = sizeof(mi);
	mi.fMask = MIIM_ID | MIIM_CHECKMARKS | MIIM_STATE |MIIM_TYPE | MIIM_DATA | MIIM_SUBMENU;

   while ((--nItem)>=0)
	{
		GetMenuItemInfo(m_hMenu,nItem,TRUE,&mi);

     	if((mi.fType & MFT_OWNERDRAW) && !(mi.fType & MFT_SEPARATOR))
      {
         temp1 = (LPCNMENUSTYLE)mi.dwItemData;
         temp[i] = *temp1;
         mi.dwItemData = (DWORD)&temp[i];
         SetMenuItemInfo(m_hCurrMenu,nItem,TRUE,&mi);
         i ++;
		}
	}
   Del(m_lprms);
   m_lprms = temp;
}

BOOL CNCoolMenu::Delete(UINT nIndex,UINT uPos)
{
   if(m_Popup)
   	return m_Popup->Delete(nIndex,uPos);

	MENUITEMINFO mi;
   BOOL bOK;

   ZeroMemory(&mi,sizeof(mi));

 	mi.cbSize = sizeof(mi);
   mi.fMask = MIIM_DATA;

	GetMenuItemInfo(m_hCurrMenu,nIndex,uPos,&mi);

   bOK = CNMenu::Delete(nIndex,uPos);
   if(bOK)
   {
   	if((mi.fType & MFT_SEPARATOR))
     		m_Style.nMenuHeight -= MENUSEP_HEIGHT;
	   else
      {
     		m_Style.nMenuHeight -= m_cyFont;
      	if(mi.dwItemData)
	      {
   	   	LPCNMENUSTYLE lprms;
      	   lprms = (LPCNMENUSTYLE)mi.dwItemData;
         	lprms->hIcon = NULL;
	         lprms->uID = 0xffffffff;
   	   }
      }
   }

   return bOK;
}

void CNCoolMenu::SetItemDrawFunc(FUNC_COOLMENU_DRAWITEM drawer)
{
   if(m_Popup)
   {
   	m_Popup->SetItemDrawFunc(drawer);
      return;
   }
	if(drawer)
   	m_DrawItemFunc = drawer;
}

//默认自绘菜单函数
void CNCoolMenu_DrawItem_def(CNCoolMenu* rm,LPDRAWITEMSTRUCT lps)
{
	LPCNMENUSTYLE lprms = (LPCNMENUSTYLE)lps->itemData;

   HDC hDC = lps->hDC;
   HDC hMemDC = CreateCompatibleDC(hDC);
   RECT rc = lps->rcItem,rrc;

   char txt[MAX_MENUTEXT];
	txt[0] = '\0';
	GetMenuString(rm->m_hCurrMenu,lps->itemID,txt,MAX_MENUTEXT,MF_BYCOMMAND);
//绘制版权条
   if(rm->m_Style.hbmMarker != NULL)
   {
     	SelectObject(hMemDC,rm->m_Style.hbmMarker);
      if((rm->m_Style.nMenuHeight - rc.top) > (int)rm->m_Style.uMarkerY)
        	BitBlt(hDC,rc.left,rc.top,rm->m_Style.uMarkerX,rc.bottom - rc.top,hMemDC,0,0,SRCCOPY);
      else
	  	   BitBlt(hDC,rc.left,rc.top,rm->m_Style.uMarkerX,rc.bottom - rc.top,hMemDC,0,rm->m_Style.uMarkerY - rm->m_Style.nMenuHeight + rc.top,SRCCOPY);
   }
   rc.left += rm->m_Style.uMarkerX;
   rrc = rc;
   rrc.right = rrc.left + rm->m_cyFont;

   SetBkMode(hDC,TRANSPARENT);

   FillRect(hDC,&rc,rm->m_Style.hbrBkg);
//绘制背景图象
   if(rm->m_Style.hbmBkg)
   {
  	   SelectObject(hMemDC,rm->m_Style.hbmBkg);
      if(rc.top > (int)rm->m_Style.uBkgY)
      	BitBlt(hDC,rc.left,rc.top,rc.right - rc.left,rc.bottom - rc.top,hMemDC,0,rc.top % rm->m_Style.uBkgY,SRCCOPY);
      else
        	BitBlt(hDC,rc.left,rc.top,rc.right - rc.left,rc.bottom - rc.top,hMemDC,0,rc.top,SRCCOPY);
   }

   BOOL bSel = lps->itemState & ODS_SELECTED;

   if((rc.bottom - rc.top) == MENUSEP_HEIGHT)	//是分隔线
   {
    	rc.top += 2;
      rc.bottom -= 2;
      rc.left += 1;
      rc.right -= 1;
		DrawEdge(hDC,&rc,BDR_SUNKENOUTER,BF_RECT);
      DeleteDC(hMemDC);
      return;
   }

   if(lprms)
   {
   	BOOL bChecked = lps->itemState & ODS_CHECKED;
      if(lprms->hIcon)		//有图标，绘制图标
      {
         if(bChecked)
            DrawEdge(hDC,&rrc,BDR_SUNKENOUTER,BF_RECT);
         else if(bSel)
          	DrawEdge(hDC,&rrc,BDR_RAISEDINNER,BF_RECT);

         int ext = (rm->m_cyFont - 16) >> 1;

			DrawIconEx(hDC,rc.left + ext,rc.top + ext,lprms->hIcon,16,16,0,NULL,DI_NORMAL);
         rrc.right = rc.right;
         rrc.left += rm->m_cyFont;
      }
      else
      {
        	MENUITEMINFO mi;
		   ZeroMemory(&mi,sizeof(mi));

		   mi.cbSize=sizeof(mi);
		   mi.fMask = MIIM_CHECKMARKS;

			GetMenuItemInfo(rm->m_hCurrMenu,lps->itemID,FALSE,&mi);

         DeleteDC(hMemDC);
         hMemDC = CreateCompatibleDC(hDC);
         if(bChecked)
	         SelectObject(hMemDC,mi.hbmpChecked);
         else
           	SelectObject(hMemDC,mi.hbmpUnchecked);
	      BitBlt(hDC,rc.left,rc.top,rm->m_cyFont,rm->m_cyFont,hMemDC,0,0,SRCAND);
//绘制选中图案
         if(mi.hbmpChecked || mi.hbmpUnchecked)
         {
            if(bChecked && mi.hbmpChecked != rm->m_hbmRadio)
              	DrawEdge(hDC,&rrc,BDR_SUNKENOUTER,BF_RECT);
	         rrc.left += rm->m_cyFont;
        	}
        	rrc.right = rc.right;
      }
   }
   else
     	rrc.right = rc.right;

   rc.left += rm->m_cyFont + 2;

   if((lps->itemState & ODS_DISABLED) || (lps->itemState & ODS_GRAYED))
   {
     	SetTextColor(hDC,GetSysColor(COLOR_GRAYTEXT));
     	DrawText(hDC,txt,-1,&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
      return;
   }

   if(bSel)
   {
     	SetTextColor(hDC,rm->m_Style.crText);

      if(rm->m_Style.hbmHilight)
	   {
         SelectObject(hMemDC,rm->m_Style.hbmHilight);
	  	   BitBlt(hDC,rrc.left,rc.top,rrc.right - rrc.left,rc.bottom - rc.top,hMemDC,rrc.left,0,SRCCOPY);
      }
      else
	      FillRect(hDC,&rrc,rm->m_Style.hbrHilight);

      if(rm->m_Style.uSelectRect)
         DrawEdge(hDC,&rrc,rm->m_Style.uSelectRect,BF_RECT);
   }
   DrawText(hDC,txt,-1,&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
   DeleteDC(hMemDC);
}

void CNCoolMenu_DrawItem_XP(CNCoolMenu* rm,LPDRAWITEMSTRUCT lps)
{
	LPCNMENUSTYLE lprms;

	HDC hDC = lps->hDC;
   HDC hMemDC = CreateCompatibleDC(hDC);
   RECT rc = lps->rcItem,rrc;

   char txt[MAX_MENUTEXT];
	txt[0] = '\0';
	GetMenuString(rm->m_hCurrMenu,lps->itemID,txt,MAX_MENUTEXT,MF_BYCOMMAND);

   if(rm->m_Style.hbmMarker != NULL)
   {
     	SelectObject(hMemDC,rm->m_Style.hbmMarker);
      if((rm->m_Style.nMenuHeight - rc.top) > (int)rm->m_Style.uMarkerY)
        	BitBlt(hDC,rc.left,rc.top,rm->m_Style.uMarkerX,rc.bottom - rc.top,hMemDC,0,0,SRCCOPY);
      else
	  	   BitBlt(hDC,rc.left,rc.top,rm->m_Style.uMarkerX,rc.bottom - rc.top,hMemDC,0,rm->m_Style.uMarkerY - rm->m_Style.nMenuHeight + rc.top,SRCCOPY);
   }
   rc.left += rm->m_Style.uMarkerX;
   rrc = rc;
   rrc.right = rrc.left + rm->m_cyFont;

   SetBkMode(hDC,TRANSPARENT);

   lprms = (LPCNMENUSTYLE)lps->itemData;

   FillRect(hDC,&rc,rm->m_Style.hbrBkg);
   if(rm->m_Style.hbmBkg)
   {
  	   SelectObject(hMemDC,rm->m_Style.hbmBkg);
      if(rc.top > (int)rm->m_Style.uBkgY)
      	BitBlt(hDC,rc.left,rc.top,rc.right - rc.left,rc.bottom - rc.top,hMemDC,0,rc.top % rm->m_Style.uBkgY,SRCCOPY);
      else
        	BitBlt(hDC,rc.left,rc.top,rc.right - rc.left,rc.bottom - rc.top,hMemDC,0,rc.top,SRCCOPY);
   }

   if((rc.bottom - rc.top) == MENUSEP_HEIGHT)
   {
    	rc.top += 2;
      rc.bottom -= 2;
      rc.left += rm->m_cyFont + rm->m_ItemIconPos + 1;
      rc.right -= 1;
		DrawEdge(hDC,&rc,BDR_SUNKENOUTER,BF_RECT);
      rrc.right += rm->m_ItemIconPos;
      FillRect(hDC,&rrc,(HBRUSH)(COLOR_BTNFACE + 1));
      DeleteDC(hMemDC);
      return;
   }

   BOOL bSel = lps->itemState & ODS_SELECTED;
   if(bSel)
   {
     	SetTextColor(hDC,rm->m_Style.crText);

      if(rm->m_Style.hbmHilight)
      {
  	      SelectObject(hMemDC,rm->m_Style.hbmHilight);
     	   BitBlt(hDC,rc.left,rc.top,rc.right - rc.left,rc.bottom - rc.top,hMemDC,rc.left,0,SRCCOPY);
        	DeleteDC(hMemDC);
      }
      else
      {
       	if(!rm->m_Style.hPen)
	     		rm->m_Style.hPen = CreatePen(PS_SOLID,1,0x00ff0000);

	      SelectObject(hDC,rm->m_Style.hbrHilight);
	      SelectObject(hDC,rm->m_Style.hPen);
	      Rectangle(hDC,rc.left,rc.top,rc.right,rc.bottom);
      }
   }
   else
   {
		rrc.right += rm->m_ItemIconPos;
      FillRect(hDC,&rrc,(HBRUSH)(COLOR_BTNFACE + 1));
      rrc.right -= rm->m_ItemIconPos;
   }

   rc.left += rm->m_ItemIconPos;

   if(lprms)
   {
      BOOL bChecked = lps->itemState & ODS_CHECKED;
      if(lprms->hIcon)
      {
         int ext = (rm->m_cyFont - 16) >> 1;
         if(bSel)
	         DrawIconEx(hDC,rc.left + ext - 1,rc.top + ext - 1,lprms->hIcon,16,16,0,NULL,DI_NORMAL);
         else
          	DrawIconEx(hDC,rc.left + ext,rc.top + ext,lprms->hIcon,16,16,0,NULL,DI_NORMAL);
      }

      {
        	MENUITEMINFO mi;
		   ZeroMemory(&mi,sizeof(mi));

		   mi.cbSize=sizeof(mi);
		   mi.fMask = MIIM_CHECKMARKS;

			GetMenuItemInfo(rm->m_hCurrMenu,lps->itemID,FALSE,&mi);

         DeleteDC(hMemDC);
         hMemDC = CreateCompatibleDC(hDC);
         if(bChecked)
	  	      SelectObject(hMemDC,mi.hbmpChecked);
         else
           	SelectObject(hMemDC,mi.hbmpUnchecked);
	  	   BitBlt(hDC,rrc.left,rrc.top,rm->m_cyFont,rm->m_cyFont,hMemDC,0,0,SRCAND);

         if(mi.hbmpChecked || mi.hbmpUnchecked)
         {
            if(bChecked && mi.hbmpChecked != rm->m_hbmRadio)
              	DrawEdge(hDC,&rrc,BDR_SUNKENOUTER,BF_RECT);
        	}
      }
   }

   rc.left += rm->m_cyFont + 5;

   if((lps->itemState & ODS_DISABLED) || (lps->itemState & ODS_GRAYED))
   {
     	SetTextColor(hDC,GetSysColor(COLOR_GRAYTEXT));
     	DrawText(hDC,txt,-1,&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
      return;
   }

   DrawText(hDC,txt,-1,&rc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
   DeleteDC(hMemDC);
}


///////////////////////////////////////////////////
//
// 通用函数：
//
//////////////////////////////////////////////////

void Errmsg(LPSTR format,...)
{
	char buf[MAX_PATH];
	
	va_list ap;
	
	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);
	
	MessageBox(GetFocus(),buf,"错误",MB_OK | MB_ICONWARNING);
}


LPVOID New(DWORD dwSize)
{
	HGLOBAL hgMem;
	
	hgMem = GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,dwSize);
	if(hgMem==NULL)
	{
		Errmsg("内存分配失败,请检查虚拟内存空间");
		return NULL;
	}
	
	return (LPVOID)hgMem;
}


LPVOID Del(LPVOID lpv)
{
	if(lpv!=NULL)
		GlobalFree(lpv);
	return NULL;
}
