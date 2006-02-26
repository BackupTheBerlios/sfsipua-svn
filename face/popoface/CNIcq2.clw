; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNButton
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CNIcq.h"

ClassCount=11
Class1=CCNIcqApp
Class2=CCNIcqDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_CNICQ_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CXPanel
Class5=CIMTree
Class6=CIMTab
Class7=CIMTreeView
Class8=CIMainHeader
Class9=CIMainPanel
Class10=CIMShortcutTool
Class11=CNButton
Resource4=IDR_MAIN_MENU

[CLS:CCNIcqApp]
Type=0
HeaderFile=CNIcq.h
ImplementationFile=CNIcq.cpp
Filter=N

[CLS:CCNIcqDlg]
Type=0
HeaderFile=CNIcqDlg.h
ImplementationFile=CNIcqDlg.cpp
Filter=D
LastObject=CCNIcqDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=CNIcqDlg.h
ImplementationFile=CNIcqDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDOK

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

[MNU:IDR_MAIN_MENU]
Type=1
Class=CCNIcqDlg
Command1=ID_FILE_SW_USER
Command2=ID_FILE_STATUS_ONLINE
Command3=ID_FILE_STATUS_HIDE
Command4=ID_FILE_STATUS_OFFLINE
Command5=ID_FILE_LOGIN
Command6=ID_FILE_LOGOUT
Command7=ID_FILE_EXIT
Command8=ID_MENUITEM32778
Command9=ID_MENUITEM32779
Command10=ID_HELP_ABOUT
CommandCount=10

[CLS:CXPanel]
Type=0
HeaderFile=XPanel.h
ImplementationFile=XPanel.cpp
BaseClass=CWnd
Filter=T
LastObject=CXPanel
VirtualFilter=WC

[CLS:CIMTree]
Type=0
HeaderFile=IMTree.h
ImplementationFile=IMTree.cpp
BaseClass=CTreeCtrl
Filter=W
VirtualFilter=GWC
LastObject=CIMTree

[CLS:CIMTab]
Type=0
HeaderFile=IMTab.h
ImplementationFile=IMTab.cpp
BaseClass=CTabCtrl
Filter=W
VirtualFilter=UWC
LastObject=CIMTab

[CLS:CIMTreeView]
Type=0
HeaderFile=IMTreeView.h
ImplementationFile=IMTreeView.cpp
BaseClass=CTreeView
Filter=C
LastObject=CIMTreeView

[CLS:CIMainHeader]
Type=0
HeaderFile=IMainHeader.h
ImplementationFile=IMainHeader.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

[CLS:CIMainPanel]
Type=0
HeaderFile=IMainPanel.h
ImplementationFile=IMainPanel.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CIMainPanel

[CLS:CIMShortcutTool]
Type=0
HeaderFile=IMShortcutTool.h
ImplementationFile=IMShortcutTool.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CIMShortcutTool

[CLS:CNButton]
Type=0
HeaderFile=CNButton.h
ImplementationFile=CNButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=WC
LastObject=CNButton

