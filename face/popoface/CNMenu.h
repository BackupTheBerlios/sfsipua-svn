/**********************************************************************
//				类Office XP、OICQ外观的菜单类
//						-- 抽取自 临风程序界面类库CNdows.lib
//
//作者：临风        整理：cicn
//
//版本：0.1
//
//声明：  本类库可以自由使用而不须对作者作出任何回报，但作者希望能得到
//		  你的鼓励和支持。你可以对类库源码作出修改和改进，但希望你能在
//		  修改的同时给作者一份同样的副本。
//		  本类库不得用于任何商业用途，如确实需要，请与作者联系。
//
//e-mail:cicn@163.com
//
//原文件名：rcm.h
//
//说明：CNmenu 类定义文件
//
**********************************************************************/


#ifndef _INC_CNDOWAPP
#define _INC_CNDOWAPP


// 通用函数声明
void Errmsg(LPSTR format,...);
LPVOID New(DWORD dwSize);
LPVOID Del(LPVOID lpv);


class CNCoolMenu;

typedef struct _tagCNMenuStyle
{
	HICON hIcon;
	CNCoolMenu* pMenu;
	UINT uID;
}CNMENUSTYLE,*LPCNMENUSTYLE;


#define MENURECT_UP		BDR_RAISEDINNER
#define MENURECT_DOWN		BDR_SUNKENOUTER

#define MENUMARKER_EXT		24		//标记图案中扩展图案高度，该扩展图案是为MENU高度>标记图案时
						//绘制剩余部分而设，该扩展图案必须位于标记图案顶部并高度为该数值
						//资源文件中的标记图案必须符合上述规则
#define MENUSEP_HEIGHT	  	6		//菜单分割线所占菜单项高度
#define MENUCHECK_CHECKBOX	0		//Menu Check图案是CHECKBOX
#define MENUCHECK_RADIO		12		//Menu Check图案是RADIO


typedef struct _tagCNMenuGlobalStyle
{
	HBITMAP hbmBkg;					//背景图象
	HBRUSH hbrBkg;					//背景颜色
	HBITMAP hbmHilight;				//选中菜单图案
	HBRUSH hbrHilight;				//选中菜单的颜色
	HPEN hPen;					//留用
	COLORREF crText;				//选中菜单的文字颜色
	COLORREF crTextDef;				//未选中菜单颜色（默认颜色）
	UINT uSelectRect;				//选中菜单是凸起或凹下，MENURECT_UP 或 MENURECT_DOWN

	//以下标记图案（即类似OICQ菜单左边的一条图案）信息
	HBITMAP hbmMarker;				//标记图案
	UINT uMarkerX,uMarkerY;				//标记图案宽，高
	UINT uBkgY;					//背景高度
	int nMenuHeight;				//菜单总高度
}MENUGLOBALSTYLE,*LPMENUGLOBALSTYLE;


#define BY_COMMAND 		MF_BYCOMMAND	//插入菜单位置指定方式
#define BY_POSITION 		MF_BYPOSITION

#define MAX_MENUTEXT		81			//菜单最多显示字数
#define MENU_PER_INSERT		20			//每次增加菜单项数量(CNCoolMenu用)

#define COLOR_TRANSPARENT	0xffffffff		//透明色（以下定义菜单用）
#define COLOR_DEF		0xfffffffe		//默认色
#define COLOR_PREV		0xfffffffd		//上一次的颜色（用于SetColor()中不想改变的颜色）


typedef void (*FUNC_COOLMENU_DRAWITEM)(CNCoolMenu*,LPDRAWITEMSTRUCT);
//定义结束


extern "C"
{
   void CNCoolMenu_DrawItem_def(CNCoolMenu* rm,LPDRAWITEMSTRUCT lps);
   void CNCoolMenu_DrawItem_XP(CNCoolMenu* rm,LPDRAWITEMSTRUCT lps);	//Office XP 类型菜单选中项的绘制
}


class CNMenu
{
public:
	CNMenu(HINSTANCE hInst);
	CNMenu(HINSTANCE hInst, LPCTSTR lpMenuname);
	virtual ~CNMenu();

	BOOL Create();
	BOOL CreatePopup();
	void Destroy(){DestroyMenu(m_hMenu);};

	virtual BOOL Load(LPCTSTR lpMenuname);
	virtual BOOL LoadPopup(LPCTSTR lpMenuname,UINT nIndex = 0);
	virtual BOOL Attach(HMENU hMenu);
	virtual HMENU Detach();
	BOOL Popup(HWND hWnd,int x=-999,int y=-999);			//使用默认值则在鼠标当前位置弹出

	inline HMENU GetMenu(){return m_hMenu;};
	inline HMENU GetPopup(){return m_hCurrMenu;};
	int GetItemIndex(UINT uIndex);
	int GetItemId(UINT uIndex);
	HMENU GetItem(UINT uIndex);

	virtual BOOL Insert(UINT uid,UINT nIndex,LPSTR szText,UINT flag = BY_COMMAND);
	virtual BOOL InsertSep(UINT nIndex,UINT uPos=BY_COMMAND);	//插入分隔符
	virtual BOOL Delete(UINT nIndex,UINT uPos=BY_COMMAND);

	virtual DWORD CheckItem(UINT uIndex,BOOL bChecked = TRUE,UINT uFlag = BY_COMMAND);
	virtual BOOL CheckRadioItem(UINT idFirst,UINT idEnd,UINT uIndex,UINT uFlag = BY_POSITION);
	void SetCheckBmp(UINT uIndex,UINT uFlag,HBITMAP hbmCheck,HBITMAP hbmUncheck = NULL);
	void EnableItem(UINT uIndex,BOOL bEnable = TRUE,UINT uFlag = BY_COMMAND);

	BOOL BindToWindow(HWND hWnd){return SetMenu(hWnd,m_hMenu);};
	void Update(HWND hWnd);

public:
	HMENU m_hMenu, m_hCurrMenu;		//m_hCurrMenu:如果是POPUPMENU，该值是m_hMenu的submenu,否则=m_hMenu
	HINSTANCE m_hInst;
};


#define FUNC_DRAWMENU_DEF	CNCoolMenu_DrawItem_def
#define FUNC_DRAWMENU_XP	CNCoolMenu_DrawItem_XP


class CNCoolMenu:public CNMenu
{
public:
	CNCoolMenu(HINSTANCE hInst);
	CNCoolMenu(HINSTANCE hInst, LPCTSTR lpMenuname);
	CNCoolMenu(HINSTANCE hInst, HMENU hMenu,BOOL bParent = TRUE);
	~CNCoolMenu();

	BOOL Load(LPCTSTR lpMenuname);
	BOOL Attach(HMENU hMenu);
	HMENU Detach();
	BOOL LoadPopup(LPCTSTR lpMenuname,UINT nIndex = 0);
	void Free();				//释放分配的菜单图象（背景，选中图案，版权栏等）

	BOOL Draw(LPDRAWITEMSTRUCT lps);
	BOOL MeasureItem(LPMEASUREITEMSTRUCT pmis);
	BOOL Remap();				//设置菜单（包括子菜单为自绘形式）
	void Reset();				//设置菜单为初始状态（不自绘，释放分配的菜单数据）

	HICON SetItemIcon(UINT nIndex,HICON hicon);		//设置菜单项图标（根据菜单项的ID）
	HBITMAP SetBkg(HBITMAP hbmBkg);
	void SetColor(COLORREF crBkg,COLORREF crHilight,COLORREF crBkgText = COLOR_TRANSPARENT,COLORREF crSelText = COLOR_TRANSPARENT);
	HBITMAP SetSelectBkg(HBITMAP hbmHilight,COLORREF crText = COLOR_TRANSPARENT);
	void SetSelectRectType(UINT uRectStyle);
	HBITMAP SetMarker(HBITMAP hbmMarker);			//设置版权条

	DWORD CheckItem(UINT uIndex,BOOL bChecked = TRUE,UINT uFlag = BY_COMMAND);
	BOOL CheckRadioItem(UINT idFirst,UINT idEnd,UINT uIndex,UINT uFlag = BY_POSITION);

	BOOL Insert(UINT uid,UINT nIndex,LPSTR szText,UINT flag = BY_COMMAND);
	BOOL InsertSep(UINT nIndex,UINT uPos=BY_COMMAND);//插入分隔符
	BOOL Delete(UINT nIndex,UINT uPos=BY_COMMAND);

	void SetItemDrawFunc(FUNC_COOLMENU_DRAWITEM drawer);	//设置菜单自绘函数
	CNCoolMenu* SubMenu(int i);							//得到子菜单

private:
	void Init();								//类初始化
	void InitSubMenu();							//初始化子菜单
	void ResetItemData();						//重置菜单项数据（用于增加菜单项菜单数据缓冲区已满的情况）
	BOOL SetCheckItem(UINT uIndex,int nType = MENUCHECK_CHECKBOX);

public:
	static HBITMAP m_hbmCheck,m_hbmRadio;		//默认菜单项选中图案
	static int m_cxFont,m_cyFont;
	int m_ItemIconPos;							//菜单项图标位置（与选中图案并列显示或优先显示）
	MENUGLOBALSTYLE m_Style;

private:
	static HFONT m_hFont;
	LPCNMENUSTYLE m_lprms;
	CNMENUSTYLE m_SepData;					//分隔线数据（公用的ItemData)
	FUNC_COOLMENU_DRAWITEM m_DrawItemFunc;
	static int m_id;
	int m_nSubMenuCnt;
	CNCoolMenu** m_SubMenu;
	CNCoolMenu* m_Popup;
	BOOL m_bInited;						//是否已初始化
	int m_nItemCnt;						//菜单项数(非实际数量，分配DATA用)
};
#endif
