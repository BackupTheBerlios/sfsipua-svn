#if !defined(AFX_IMTOOLWIN_H__74F305D8_437F_47DC_BA1A_3BF4BA6240B2__INCLUDED_)
#define AFX_IMTOOLWIN_H__74F305D8_437F_47DC_BA1A_3BF4BA6240B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IMToolWin.h : header file
//
#include <vector>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CIMToolWin window
class CIMToolWinItem
{
public:
	CIMToolWinItem(const char *t,int img) 
		: Title(t),Image(img) {}

	virtual ~CIMToolWinItem(){}

	CString Title;
	int	Image;
};
class CIMToolWinFolder
{
public:
	CIMToolWinFolder(const char *t,int img) : Title(t),Image(img) {}
	~CIMToolWinFolder() {}

	void AddItem(const char *t, int img);

	BOOL	Expended;
	CString Title;
	int	Image;

	vector<CIMToolWinItem *> Items;
};

#define TOOLWIN_STATUS_NORMAL		0x0000
#define TOOLWIN_STATUS_PRESSED		0x0001
#define TOOLWIN_STATUS_IN		0x0002
#define TOOLWIN_STATUS_OUT		0x0004

#define TOOLWIN_ITEM_HEIGHT		20

class CIMToolWin : public CWnd
{
	enum{	//Folder颜色定义
		TOOLWIN_COLOR_FOLDER_BK_IN	= 0,	// Background color when mouse is INside
		TOOLWIN_COLOR_FOLDER_FG_IN,		// Text color when mouse is INside
		TOOLWIN_COLOR_FOLDER_BK_OUT,		// Background color when mouse is OUTside
		TOOLWIN_COLOR_FOLDER_FG_OUT,		// Text color when mouse is OUTside

		//Item颜色定义
		TOOLWIN_COLOR_ITEM_BK_IN,		// Background color when mouse is INside
		TOOLWIN_COLOR_ITEM_FG_IN,		// Text color when mouse is INside
		TOOLWIN_COLOR_ITEM_BK_OUT,		// Background color when mouse is OUTside
		TOOLWIN_COLOR_ITEM_FG_OUT,		// Text color when mouse is OUTside

		TOOLWIN_MAX_COLORS
	};

// Construction
public:
	CIMToolWin();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIMToolWin)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetImageList(CImageList *ImageList);
	virtual ~CIMToolWin();

	int GetFolderCount();
	void AddItem(int Folder,const char *t,int img);
	int AddFolder(const char *text,int img);

	// Generated message map functions
protected:
	DWORD SetColor(BYTE byColorIndex, COLORREF crColor, BOOL bRepaint);
	virtual void DrawFolder(CDC *pDC,int Folder);
	virtual void DrawAll(CDC *pDC);

	vector<CIMToolWinFolder *> folders;

	//{{AFX_MSG(CIMToolWin)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CSkin* m_pSkin;

	CImageList *Icons;

	COLORREF StartBgColor;
	COLORREF EndBgColor;

	COLORREF FontColor;
	COLORREF FolderBgColor;
	COLORREF ItemBgColor;

	COLORREF m_crColors[TOOLWIN_MAX_COLORS];	// Colors to be used

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMTOOLWIN_H__74F305D8_437F_47DC_BA1A_3BF4BA6240B2__INCLUDED_)
