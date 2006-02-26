/**********************************************************************
//				��Office XP��OICQ��۵Ĳ˵���
//						-- ��ȡ�� �ٷ����������CNdows.lib
//
//���ߣ��ٷ�        ����cicn
//
//�汾��0.1
//
//������  ������������ʹ�ö���������������κλر���������ϣ���ܵõ�
//		  ��Ĺ�����֧�֡�����Զ����Դ�������޸ĺ͸Ľ�����ϣ��������
//		  �޸ĵ�ͬʱ������һ��ͬ���ĸ�����
//		  ����ⲻ�������κ���ҵ��;����ȷʵ��Ҫ������������ϵ��
//
//e-mail:cicn@163.com
//
//ԭ�ļ�����rcm.h
//
//˵����CNmenu �ඨ���ļ�
//
**********************************************************************/


#ifndef _INC_CNDOWAPP
#define _INC_CNDOWAPP


// ͨ�ú�������
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

#define MENUMARKER_EXT		24		//���ͼ������չͼ���߶ȣ�����չͼ����ΪMENU�߶�>���ͼ��ʱ
						//����ʣ�ಿ�ֶ��裬����չͼ������λ�ڱ��ͼ���������߶�Ϊ����ֵ
						//��Դ�ļ��еı��ͼ�����������������
#define MENUSEP_HEIGHT	  	6		//�˵��ָ�����ռ�˵���߶�
#define MENUCHECK_CHECKBOX	0		//Menu Checkͼ����CHECKBOX
#define MENUCHECK_RADIO		12		//Menu Checkͼ����RADIO


typedef struct _tagCNMenuGlobalStyle
{
	HBITMAP hbmBkg;					//����ͼ��
	HBRUSH hbrBkg;					//������ɫ
	HBITMAP hbmHilight;				//ѡ�в˵�ͼ��
	HBRUSH hbrHilight;				//ѡ�в˵�����ɫ
	HPEN hPen;					//����
	COLORREF crText;				//ѡ�в˵���������ɫ
	COLORREF crTextDef;				//δѡ�в˵���ɫ��Ĭ����ɫ��
	UINT uSelectRect;				//ѡ�в˵���͹����£�MENURECT_UP �� MENURECT_DOWN

	//���±��ͼ����������OICQ�˵���ߵ�һ��ͼ������Ϣ
	HBITMAP hbmMarker;				//���ͼ��
	UINT uMarkerX,uMarkerY;				//���ͼ������
	UINT uBkgY;					//�����߶�
	int nMenuHeight;				//�˵��ܸ߶�
}MENUGLOBALSTYLE,*LPMENUGLOBALSTYLE;


#define BY_COMMAND 		MF_BYCOMMAND	//����˵�λ��ָ����ʽ
#define BY_POSITION 		MF_BYPOSITION

#define MAX_MENUTEXT		81			//�˵������ʾ����
#define MENU_PER_INSERT		20			//ÿ�����Ӳ˵�������(CNCoolMenu��)

#define COLOR_TRANSPARENT	0xffffffff		//͸��ɫ�����¶���˵��ã�
#define COLOR_DEF		0xfffffffe		//Ĭ��ɫ
#define COLOR_PREV		0xfffffffd		//��һ�ε���ɫ������SetColor()�в���ı����ɫ��


typedef void (*FUNC_COOLMENU_DRAWITEM)(CNCoolMenu*,LPDRAWITEMSTRUCT);
//�������


extern "C"
{
   void CNCoolMenu_DrawItem_def(CNCoolMenu* rm,LPDRAWITEMSTRUCT lps);
   void CNCoolMenu_DrawItem_XP(CNCoolMenu* rm,LPDRAWITEMSTRUCT lps);	//Office XP ���Ͳ˵�ѡ����Ļ���
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
	BOOL Popup(HWND hWnd,int x=-999,int y=-999);			//ʹ��Ĭ��ֵ������굱ǰλ�õ���

	inline HMENU GetMenu(){return m_hMenu;};
	inline HMENU GetPopup(){return m_hCurrMenu;};
	int GetItemIndex(UINT uIndex);
	int GetItemId(UINT uIndex);
	HMENU GetItem(UINT uIndex);

	virtual BOOL Insert(UINT uid,UINT nIndex,LPSTR szText,UINT flag = BY_COMMAND);
	virtual BOOL InsertSep(UINT nIndex,UINT uPos=BY_COMMAND);	//����ָ���
	virtual BOOL Delete(UINT nIndex,UINT uPos=BY_COMMAND);

	virtual DWORD CheckItem(UINT uIndex,BOOL bChecked = TRUE,UINT uFlag = BY_COMMAND);
	virtual BOOL CheckRadioItem(UINT idFirst,UINT idEnd,UINT uIndex,UINT uFlag = BY_POSITION);
	void SetCheckBmp(UINT uIndex,UINT uFlag,HBITMAP hbmCheck,HBITMAP hbmUncheck = NULL);
	void EnableItem(UINT uIndex,BOOL bEnable = TRUE,UINT uFlag = BY_COMMAND);

	BOOL BindToWindow(HWND hWnd){return SetMenu(hWnd,m_hMenu);};
	void Update(HWND hWnd);

public:
	HMENU m_hMenu, m_hCurrMenu;		//m_hCurrMenu:�����POPUPMENU����ֵ��m_hMenu��submenu,����=m_hMenu
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
	void Free();				//�ͷŷ���Ĳ˵�ͼ�󣨱�����ѡ��ͼ������Ȩ���ȣ�

	BOOL Draw(LPDRAWITEMSTRUCT lps);
	BOOL MeasureItem(LPMEASUREITEMSTRUCT pmis);
	BOOL Remap();				//���ò˵��������Ӳ˵�Ϊ�Ի���ʽ��
	void Reset();				//���ò˵�Ϊ��ʼ״̬�����Ի棬�ͷŷ���Ĳ˵����ݣ�

	HICON SetItemIcon(UINT nIndex,HICON hicon);		//���ò˵���ͼ�꣨���ݲ˵����ID��
	HBITMAP SetBkg(HBITMAP hbmBkg);
	void SetColor(COLORREF crBkg,COLORREF crHilight,COLORREF crBkgText = COLOR_TRANSPARENT,COLORREF crSelText = COLOR_TRANSPARENT);
	HBITMAP SetSelectBkg(HBITMAP hbmHilight,COLORREF crText = COLOR_TRANSPARENT);
	void SetSelectRectType(UINT uRectStyle);
	HBITMAP SetMarker(HBITMAP hbmMarker);			//���ð�Ȩ��

	DWORD CheckItem(UINT uIndex,BOOL bChecked = TRUE,UINT uFlag = BY_COMMAND);
	BOOL CheckRadioItem(UINT idFirst,UINT idEnd,UINT uIndex,UINT uFlag = BY_POSITION);

	BOOL Insert(UINT uid,UINT nIndex,LPSTR szText,UINT flag = BY_COMMAND);
	BOOL InsertSep(UINT nIndex,UINT uPos=BY_COMMAND);//����ָ���
	BOOL Delete(UINT nIndex,UINT uPos=BY_COMMAND);

	void SetItemDrawFunc(FUNC_COOLMENU_DRAWITEM drawer);	//���ò˵��Ի溯��
	CNCoolMenu* SubMenu(int i);							//�õ��Ӳ˵�

private:
	void Init();								//���ʼ��
	void InitSubMenu();							//��ʼ���Ӳ˵�
	void ResetItemData();						//���ò˵������ݣ��������Ӳ˵���˵����ݻ����������������
	BOOL SetCheckItem(UINT uIndex,int nType = MENUCHECK_CHECKBOX);

public:
	static HBITMAP m_hbmCheck,m_hbmRadio;		//Ĭ�ϲ˵���ѡ��ͼ��
	static int m_cxFont,m_cyFont;
	int m_ItemIconPos;							//�˵���ͼ��λ�ã���ѡ��ͼ��������ʾ��������ʾ��
	MENUGLOBALSTYLE m_Style;

private:
	static HFONT m_hFont;
	LPCNMENUSTYLE m_lprms;
	CNMENUSTYLE m_SepData;					//�ָ������ݣ����õ�ItemData)
	FUNC_COOLMENU_DRAWITEM m_DrawItemFunc;
	static int m_id;
	int m_nSubMenuCnt;
	CNCoolMenu** m_SubMenu;
	CNCoolMenu* m_Popup;
	BOOL m_bInited;						//�Ƿ��ѳ�ʼ��
	int m_nItemCnt;						//�˵�����(��ʵ������������DATA��)
};
#endif
