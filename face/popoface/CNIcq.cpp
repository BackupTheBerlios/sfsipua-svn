// CNIcq.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CNIcq.h"
#include "CNIcqDlg.h"
#include "IMChat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCNIcqApp

BEGIN_MESSAGE_MAP(CCNIcqApp, CWinApp)
	//{{AFX_MSG_MAP(CCNIcqApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCNIcqApp construction

CCNIcqApp::CCNIcqApp()
{
	DWORD dwVersion = ::GetVersion();
	m_bWin4 = (BYTE)dwVersion >= 4;

	m_nDefFont = (m_bWin4) ? DEFAULT_GUI_FONT : ANSI_VAR_FONT;

	m_dcScreen.Attach(::GetDC(NULL));
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCNIcqApp object

CCNIcqApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCNIcqApp initialization
CString CCNIcqApp::ExtractFilePath(char *FullName)
{
        int len;
        int i,j;
	char Path[MAX_PATH];
	CString strPath;

        len = strlen(FullName);
        for(i = len - 1; i >= 0; i --)
        {
                if( FullName[i] == '\\') break;
        }
        for(j = 0; j < i; j ++)
        {
                Path[j] = FullName[j];
        }
        Path[j] = '\0';

	strPath = Path;
	strPath = strPath + "\\";

	return strPath;
}
BOOL CCNIcqApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();		// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	TCHAR exeFullPath[MAX_PATH]; 

	//取应用程序名
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);

	//取路径
	m_strMainPath = ExtractFilePath(exeFullPath);

	m_IMSkin.LoadSkin("标准");
//	m_IMSkin.LoadSkin("MSN风格");
//	m_IMSkin.LoadSkin("海洋");

	CCNIcqDlg dlg;
	//CIMChat dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
