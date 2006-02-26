// IMainPanel.cpp : implementation file
//

#include "stdafx.h"
#include "CNIcq.h"
#include "IMainPanel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIMainPanel

CIMainPanel::CIMainPanel()
{
	m_pIMTree =new CIMTree;	
	m_pIMHeader = new CIMainHeader;
	m_pIMShortcutTool = new CIMShortcutTool;


}

CIMainPanel::~CIMainPanel()
{
	delete m_pIMShortcutTool;
	delete m_pIMHeader;
	delete m_pIMTree;
}


BEGIN_MESSAGE_MAP(CIMainPanel, CWnd)
	//{{AFX_MSG_MAP(CIMainPanel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//	ON_WM_CN_ITEMCLICK(1010,OnShortcutMessage)

/////////////////////////////////////////////////////////////////////////////
// CIMainPanel message handlers

int CIMainPanel::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	m_pSkin = &(((CCNIcqApp *)AfxGetApp())->m_IMSkin);
	
	m_pIMHeader->Create(NULL,NULL,WS_CHILD | WS_VISIBLE,
			CRect(0,0,0,0), this, 1010);

	m_pIMTree->Create(WS_CHILD | WS_VISIBLE |  
			//TVS_HASLINES| TVS_LINESATROOT| TVS_HASBUTTONS |
			TVS_SHOWSELALWAYS,
			CRect(0,0,0,0), this, 1011);

	//m_pIMTree->ModifyStyle(WS_VSCROLL,0);

	m_pIMShortcutTool->Create(NULL,NULL,WS_CHILD | WS_VISIBLE,
			CRect(0,0,0,0), this, 1012);

	//m_pIMTree->SetIndent(20);
	m_pIMTree->SetImageList(&m_pSkin->m_pILSmallState,TVSIL_NORMAL);

	m_pIMTree->SetBkColor(m_pSkin->TreeBkColor);
	m_pIMTree->SetBkImage(m_pSkin->MainBkImg);
	//m_pIMTree->SetBgStretch(TRUE);

	TV_INSERTSTRUCT TreeCtrlItem;

	HTREEITEM hItem; 

	TreeCtrlItem.hParent = TVI_ROOT;
	TreeCtrlItem.hInsertAfter = TVI_LAST; //
	TreeCtrlItem.item.iImage  = 0;//
	TreeCtrlItem.item.iSelectedImage = 0;
	TreeCtrlItem.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE| TVIF_TEXT|TVIF_CHILDREN;
	TreeCtrlItem.item.pszText =_T("在线用户"); 
	hItem = m_pIMTree->InsertItem(&TreeCtrlItem);
	
	for (int xx = 0; xx < 5; xx ++)
	{
		TreeCtrlItem.hParent = hItem;
		TreeCtrlItem.hInsertAfter = TVI_LAST; //
		TreeCtrlItem.item.iImage  = 2;//
		TreeCtrlItem.item.iSelectedImage = 2;
		TreeCtrlItem.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE| TVIF_TEXT|TVIF_CHILDREN;
		TreeCtrlItem.item.pszText =_T("用户"); 
		m_pIMTree->InsertItem(&TreeCtrlItem);
	}

	m_pIMTree->Expand(hItem,TVE_EXPAND);

	TreeCtrlItem.hParent = TVI_ROOT;
	TreeCtrlItem.hInsertAfter = TVI_LAST; //
	TreeCtrlItem.item.iImage  = 1;//
	TreeCtrlItem.item.iSelectedImage = 1;
	TreeCtrlItem.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE| TVIF_TEXT|TVIF_CHILDREN;
	TreeCtrlItem.item.pszText =_T("离线用户"); 
	hItem = m_pIMTree->InsertItem(&TreeCtrlItem);
	
	for (xx = 0; xx < 5; xx ++)
	{
		TreeCtrlItem.hParent = hItem;
		TreeCtrlItem.hInsertAfter = TVI_LAST; //
		TreeCtrlItem.item.iImage  = 2;//
		TreeCtrlItem.item.iSelectedImage = 2;
		TreeCtrlItem.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE| TVIF_TEXT|TVIF_CHILDREN;
		TreeCtrlItem.item.pszText =_T("cicn"); 
		m_pIMTree->InsertItem(&TreeCtrlItem);
	}
	

	return 0;
}

void CIMainPanel::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
	CRect rc;
	GetClientRect(&rc);
	dc.FillSolidRect(rc,RGB(255,255,255) );
}

void CIMainPanel::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	int iHeight;

	iHeight = m_pIMShortcutTool->GetClientHeight();

	m_pIMHeader->MoveWindow(CRect(0,0,cx,60),TRUE);
	m_pIMTree->MoveWindow(CRect(5, 60, cx, cy-iHeight),TRUE);
	m_pIMShortcutTool->MoveWindow(CRect(0, cy-iHeight, cx, cy),TRUE);
	
	
}
LRESULT CIMainPanel::OnShortcutMessage(WPARAM wParam, LPARAM lParam)
{
	// TODO: 处理用户自定义消息
	return 0;
}
