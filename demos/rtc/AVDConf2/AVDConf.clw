; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAVDConfDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "avdconf.h"
LastPage=0

ClassCount=11
Class1=CAVDConfApp
Class2=CAboutDlg
Class3=CAVDConfDlg
Class4=CAVDlg
Class5=CIncomingDlg
Class6=MakeCallDlg
Class7=CMessageDlg

ResourceCount=10
Resource1=IDD_AVDLG
Resource2=IDD_AVDCONF_DIALOG
Resource3=IDD_SIPLOGIN
Resource4=IDD_MAKE_A_CALL
Resource5=IDD_WATCHER
Class8=CSIPLogin
Resource6=IDD_MESSAGEDLG
Resource7=IDD_ABOUTBOX
Class9=CAddBuddyDlg
Resource8=IDD_ADDBUDDY
Class10=CBuddyRequestDlg
Resource9=IDD_INCOMING_CALL
Class11=CAuthDlg
Resource10=IDD_AUTHDIALOG

[CLS:CAVDConfApp]
Type=0
BaseClass=CWinApp
HeaderFile=AVDConf.h
ImplementationFile=AVDConf.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=AVDConfDlg.cpp
ImplementationFile=AVDConfDlg.cpp

[CLS:CAVDConfDlg]
Type=0
BaseClass=CDialog
HeaderFile=AVDConfDlg.h
ImplementationFile=AVDConfDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CAVDConfDlg

[CLS:CAVDlg]
Type=0
BaseClass=CDialog
HeaderFile=avdlg.h
ImplementationFile=AVDlg.cpp

[CLS:CIncomingDlg]
Type=0
BaseClass=CDialog
HeaderFile=IncomingDlg.h
ImplementationFile=IncomingDlg.cpp

[CLS:MakeCallDlg]
Type=0
BaseClass=CDialog
HeaderFile=MakeCallDlg.h
ImplementationFile=MakeCallDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_DESTIP

[CLS:CMessageDlg]
Type=0
BaseClass=CDialog
HeaderFile=MessageDlg.h
ImplementationFile=MessageDlg.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_AVDCONF_DIALOG]
Type=1
Class=CAVDConfDlg
ControlCount=35
Control1=IDC_STATIC,static,1342308352
Control2=IDC_BUDDYLIST,SysListView32,1484996757
Control3=IDC_PRESENCELABEL,static,1476526080
Control4=IDC_PRESENCESTATUS,combobox,1478557698
Control5=IDC_STATIC,button,1342177287
Control6=IDC_LOGIN,button,1342242817
Control7=IDC_LOGOFF,button,1476460544
Control8=IDC_ADDBUDDY,button,1476460544
Control9=IDC_REMOVEBUDDY,button,1476460544
Control10=IDC_MAKECALL,button,1342242816
Control11=IDC_APPCALL,button,1342242816
Control12=IDC_MESSAGING,button,1342242816
Control13=IDC_WHITEBOARD,button,1342242816
Control14=IDOK,button,1342242816
Control15=IDC_TUNING,button,1342242816
Control16=IDM_ABOUTBOX,button,1342242816
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATUS,static,1342308352
Control20=IDC_SYSTEMINFO,button,1342242816
Control21=IDC_STATIC,static,1342308352
Control22=IDC_LOCALIP,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_PHYSCPU,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_LOGICALCPU,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_HTCAPABLE,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_CPU1PROGRESS,msctls_progress32,1350565889
Control31=IDC_CPU1Percent,static,1342308352
Control32=IDC_CPU2LABEL,static,1342308352
Control33=IDC_CPU2PROGRESS,msctls_progress32,1350565889
Control34=IDC_CPU2PERCENT,static,1342308352
Control35=IDC_STATIC,button,1342177287

[DLG:IDD_AVDLG]
Type=1
Class=CAVDlg
ControlCount=9
Control1=IDC_SPEAKER_TEXT,static,1342308352
Control2=IDC_MIC_TEXT,static,1342308352
Control3=IDC_SPEAKER_BAR,msctls_progress32,1350565888
Control4=IDC_MIC_BAR,msctls_progress32,1350565888
Control5=IDC_SPEAKER_SLIDER,msctls_trackbar32,1342373912
Control6=IDC_SPEAKERMUTE,button,1342246915
Control7=IDC_MIC_SLIDER,msctls_trackbar32,1342373912
Control8=IDC_MICMUTE,button,1342246915
Control9=IDOK,button,1342242817

[DLG:IDD_INCOMING_CALL]
Type=1
Class=CIncomingDlg
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_CALLERNAME,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CALLERID,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816

[DLG:IDD_MAKE_A_CALL]
Type=1
Class=MakeCallDlg
ControlCount=5
Control1=IDC_DESTIP,SysIPAddress32,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_MESSAGEDLG]
Type=1
Class=CMessageDlg
ControlCount=6
Control1=IDC_TEXT,edit,1350631552
Control2=IDC_SENDTEXT,button,1342242817
Control3=IDOK,button,1342242816
Control4=IDC_MESSAGE,listbox,1352730883
Control5=IDC_STATUSTEXT,static,1342308352
Control6=IDC_CLEAR,button,1342242816

[DLG:IDD_SIPLOGIN]
Type=1
Class=CSIPLogin
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_USERURI,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SIPSERVERIP,SysIPAddress32,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_TRANSPORT,combobox,1344348162
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816

[CLS:CSIPLogin]
Type=0
HeaderFile=SIPLogin.h
ImplementationFile=SIPLogin.cpp
BaseClass=CDialog
Filter=D
LastObject=CSIPLogin
VirtualFilter=dWC

[DLG:IDD_ADDBUDDY]
Type=1
Class=CAddBuddyDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_BUDDYNAME,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BUDDYURI,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816

[CLS:CAddBuddyDlg]
Type=0
HeaderFile=AddBuddyDlg.h
ImplementationFile=AddBuddyDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_URI
VirtualFilter=dWC

[DLG:IDD_WATCHER]
Type=1
Class=CBuddyRequestDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_WATCHERNAME,static,1342308352
Control4=IDC_WATCHERURI,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_AUTOBUDDY,button,1342242819

[CLS:CBuddyRequestDlg]
Type=0
HeaderFile=BuddyRequestDlg.h
ImplementationFile=BuddyRequestDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CBuddyRequestDlg
VirtualFilter=dWC

[DLG:IDD_AUTHDIALOG]
Type=1
Class=CAuthDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_USERURI,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_ACCOUNT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_PASSWOD,edit,1350631584
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816

[CLS:CAuthDlg]
Type=0
HeaderFile=AuthDlg.h
ImplementationFile=AuthDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAuthDlg
VirtualFilter=dWC

