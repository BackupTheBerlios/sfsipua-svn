; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "cnicq.h"
LastPage=0

ClassCount=14
Class1=CNButton
Class2=CCNIcqApp
Class3=CAboutDlg
Class4=CCNIcqDlg
Class5=CIMainHeader
Class6=CIMainPanel
Class7=CIMChat
Class8=CIMShortcutTool
Class9=CIMTab
Class10=CIMToolWin
Class11=CIMTree
Class12=CMainFrame
Class13=CRichEditCtrlEx
Class14=CStaticSplitter

ResourceCount=9
Resource1=IDR_POPUP_MENU
Resource2=IDR_CHAT_MENU
Resource3=IDR_MENU_REPLY
Resource4=IDD_CNICQ_DIALOG
Resource5=IDR_MAIN_MENU
Resource6=IDD_ABOUTBOX
Resource7=IDR_FORMATBAR
Resource8=IDD_CHAT_DIALOG
Resource9=IDB_FORMATBAR

[CLS:CNButton]
Type=0
BaseClass=CButton
HeaderFile=CNButton.h
ImplementationFile=CNButton.cpp

[CLS:CCNIcqApp]
Type=0
BaseClass=CWinApp
HeaderFile=CNIcq.h
ImplementationFile=CNIcq.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=CNIcqDlg.cpp
ImplementationFile=CNIcqDlg.cpp
LastObject=ID_MENUITEM32809

[CLS:CCNIcqDlg]
Type=0
BaseClass=CDialog
HeaderFile=CNIcqDlg.h
ImplementationFile=CNIcqDlg.cpp
LastObject=ID_MENU_TOOLS_SHOWTAB
Filter=D
VirtualFilter=dWC

[CLS:CIMainHeader]
Type=0
BaseClass=CWnd
HeaderFile=IMainHeader.h
ImplementationFile=IMainHeader.cpp

[CLS:CIMainPanel]
Type=0
BaseClass=CWnd
HeaderFile=IMainPanel.h
ImplementationFile=IMainPanel.cpp

[CLS:CIMChat]
Type=0
BaseClass=CDialog
HeaderFile=IMChat.h
ImplementationFile=IMChat.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_EMOTONS

[CLS:CIMShortcutTool]
Type=0
BaseClass=CWnd
HeaderFile=IMShortcutTool.h
ImplementationFile=IMShortcutTool.cpp

[CLS:CIMTab]
Type=0
BaseClass=CTabCtrl
HeaderFile=IMTab.h
ImplementationFile=IMTab.cpp

[CLS:CIMToolWin]
Type=0
BaseClass=CWnd
HeaderFile=IMToolWin.h
ImplementationFile=IMToolWin.cpp
Filter=W
VirtualFilter=WC

[CLS:CIMTree]
Type=0
BaseClass=CTreeCtrl
HeaderFile=IMTree.h
ImplementationFile=IMTree.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CRichEditCtrlEx]
Type=0
BaseClass=CRichEditCtrl
HeaderFile=RichEditCtrlEx.h
ImplementationFile=RichEditCtrlEx.cpp
Filter=W
VirtualFilter=WC
LastObject=CRichEditCtrlEx

[CLS:CStaticSplitter]
Type=0
BaseClass=CStatic
HeaderFile=StaticSplitter.h
ImplementationFile=StaticSplitter.cpp
LastObject=CStaticSplitter
Filter=W
VirtualFilter=WC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CNICQ_DIALOG]
Type=1
Class=CCNIcqDlg
ControlCount=0

[DLG:IDD_CHAT_DIALOG]
Type=1
Class=CIMChat
ControlCount=5
Control1=IDC_BTN_CHAT_SEND,button,1342242827
Control2=IDC_EMOTONS,button,1342242816
Control3=IDC_MESSAGE,button,1342242816
Control4=IDC_BTN_FASTREPLY,button,1342242816
Control5=IDC_BTN_TOOLWIN,button,1342242816

[MNU:IDR_MAIN_MENU]
Type=1
Class=CCNIcqDlg
Command1=ID_FILE_SW_USER
Command2=ID_FILE_STATUS_ONLINE
Command3=ID_FILE_STATUS_HIDE
Command4=ID_MENUITEM32781
Command5=ID_MENUITEM32782
Command6=ID_MENUITEM32783
Command7=ID_FILE_STATUS_OFFLINE
Command8=ID_MENUITEM32785
Command9=ID_MENUITEM32786
Command10=ID_FILE_LOGIN
Command11=ID_FILE_LOGOUT
Command12=ID_FILE_EXIT
Command13=ID_MENUITEM32787
Command14=ID_MENUITEM32788
Command15=ID_MENUITEM32789
Command16=ID_MENUITEM32790
Command17=ID_MENUITEM32791
Command18=ID_MENUITEM32792
Command19=ID_MENUITEM32793
Command20=ID_MENUITEM32794
Command21=ID_MENUITEM32795
Command22=ID_MENUITEM32796
Command23=ID_MENUITEM32797
Command24=ID_MENUITEM32798
Command25=ID_MENUITEM32799
Command26=ID_MENUITEM32800
Command27=ID_MENUITEM32801
Command28=ID_MENU_TOOLS_SHOWTAB
Command29=ID_MENUITEM32803
Command30=ID_MENUITEM32805
Command31=ID_MENUITEM32806
Command32=ID_MENUITEM32807
Command33=ID_MENUITEM32778
Command34=ID_MENUITEM32779
Command35=ID_HELP_ABOUT
CommandCount=35

[MNU:IDR_CHAT_MENU]
Type=1
Class=?
Command1=ID_MENU_CHAT_EXIT
CommandCount=1

[MNU:IDR_POPUP_MENU]
Type=1
Class=?
Command1=ID_MENUITEM32809
Command2=ID_MENUITEM32810
CommandCount=2

[TB:IDR_FORMATBAR]
Type=1
Command1=ID_CHAR_BOLD
Command2=ID_CHAR_ITALIC
Command3=ID_CHAR_UNDERLINE
Command4=ID_CHAR_COLOR
Command5=ID_CHAR_EMOTION
CommandCount=5

[TB:IDB_FORMATBAR]
Type=1
Class=?
Command1=ID_CHAR_BOLD
Command2=ID_CHAR_ITALIC
Command3=ID_CHAR_UNDERLINE
Command4=ID_CHAR_COLOR
Command5=ID_CHAR_EMOTION
CommandCount=5

[MNU:IDR_MENU_REPLY]
Type=1
Class=?
Command1=ID_MENUITEM32816
Command2=ID_MENUITEM32817
Command3=ID_MENUITEM32818
Command4=ID_MENUITEM32819
CommandCount=4

