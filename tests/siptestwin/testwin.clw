; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestwinDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "testwin.h"

ClassCount=3
Class1=CTestwinApp
Class2=CTestwinDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TESTWIN_DIALOG

[CLS:CTestwinApp]
Type=0
HeaderFile=testwin.h
ImplementationFile=testwin.cpp
Filter=N

[CLS:CTestwinDlg]
Type=0
HeaderFile=testwinDlg.h
ImplementationFile=testwinDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CTestwinDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=testwinDlg.h
ImplementationFile=testwinDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TESTWIN_DIALOG]
Type=1
Class=CTestwinDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_CALL,button,1342242816

