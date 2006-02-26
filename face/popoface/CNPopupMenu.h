// GfxPopupMenu.h: interface for the CNPopupMenu class.
//
// Modified a lot by Zhang Yong
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GFXPOPUPMENU_H__F2CEE8B2_014D_11D2_83E4_0000B43382FE__INCLUDED_)
#define AFX_GFXPOPUPMENU_H__F2CEE8B2_014D_11D2_83E4_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>

class CNPopupMenu : public CMenu  
{
public:
	struct ToolBarData	
	{ // struct for toolbar resource; guess you already know it ;)
		WORD wVersion;
		WORD wWidth;			
		WORD wHeight;			
		WORD wItemCount;
	};
	struct SpawnItem
	{
		int		iImageIdx;
		int		iCmd;
		char	cText[128];
	};
	struct ImageItem
	{
		int		iImageIdx;
		int		iCmd;
	};

	CNPopupMenu();
	virtual ~CNPopupMenu();

	HFONT hMenuBoldFont;
	bool CreateBoldFont();

	HFONT	hMenuFont, hGuiFont;
	CSize szImage;
	int FindImageItem(const int cmd);

	SpawnItem * AddSpawnItem(const char * txt, const int cmd);
	void AddImageItem(const int idx, WORD cmd);

	void RemapMenu(CMenu * pMenu);

	CImageList ilList;
	CImageList ilOther;

	COLORREF crMenuText, crMenuTextSel;
	COLORREF cr3dFace, crMenu, crHighlight, cr3dHilight, cr3dShadow, crGrayText;
	COLORREF m_clrBtnFace, m_clrBtnHilight, m_clrBtnShadow;

	int iSpawnItem;
	SpawnItem ** pSpawnItem;

	int iImageItem;
	ImageItem * pImageItem;

	bool LoadToolBarResource(unsigned int resId);
	bool AddToolBarResource(unsigned int resId);

	void EnableMenuItems(CMenu * pMenu, CWnd * pParent);

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	// @@
	void modifyMenu(UINT id, UINT bitmap, BOOL byCmd = TRUE);
	void modifyMenu(UINT id, HICON icon);
	void appendMenu(UINT id, UINT bitmap, UINT strID);
	void appendMenu(UINT id, UINT bitmap, LPCTSTR str);
	void setVertBitmap(UINT bitmap);

private:
	void modifyMenuInternal(UINT itemId, int imageIndex, BOOL byCmd);

	CMap<UINT, UINT, int, int> imageHash;
	CMap<HICON, HICON, int, int> bitmapHash;
	CBitmap bmVert;
	BOOL vertDrawn;
};

#endif // !defined(AFX_GFXPOPUPMENU_H__F2CEE8B2_014D_11D2_83E4_0000B43382FE__INCLUDED_)
