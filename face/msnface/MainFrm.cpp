// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Messenger.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	//////////////////////////////////////////////////////////////////////////
	//创建Tab
	if (!m_wndImageTab.Create(NULL, NULL, WS_CHILD|WS_VISIBLE,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))	
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	m_wndImageTab.SetBkImage(IDB_BITMAP_BACK);
	m_wndImageTab.SetLeftImage(IDB_BITMAP_LEFTMARGIN);
	m_wndImageTab.SetRightImage(IDB_BITMAP_RIGHTMARGIN);
	m_wndImageTab.SetTopImage(IDB_BITMAP_TOPMARGIN);
	m_wndImageTab.SetBottomImage(IDB_BITMAP_BOTTOMMARGIN);

	m_wndImageTab.SetTabCount(2);

	int nIndex = 0;
	m_wndImageTab.SetTabImage(nIndex, IDB_BITMAP_TAB1);
	m_wndImageTab.SetTabRect(nIndex, CRect(0, 0, 32, 42));
	m_wndImageTab.SetToolTip(nIndex, "演示对话A");
	m_wndDlgA.Create(IDD_DIALOG_PAGE1, &m_wndImageTab);
	m_wndImageTab.SetTabWnd(nIndex, &m_wndDlgA);
	nIndex++;

	m_wndImageTab.SetTabImage(nIndex, IDB_BITMAP_TAB2);
	m_wndImageTab.SetTabRect(nIndex, CRect(0, 52, 32, 94));
	m_wndImageTab.SetToolTip(nIndex, "演示对话B");
	m_wndDlgB.Create(IDD_DIALOG_PAGE2, &m_wndImageTab);
	m_wndImageTab.SetTabWnd(nIndex, &m_wndDlgB);

	CenterWindow();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cx = 300;
	cs.cy = 600;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndImageTab.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndImageTab.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

