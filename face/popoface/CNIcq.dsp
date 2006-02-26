# Microsoft Developer Studio Project File - Name="CNIcq" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CNIcq - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CNIcq.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CNIcq.mak" CFG="CNIcq - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CNIcq - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CNIcq - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CNIcq - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"CNIcq.exe"

!ELSEIF  "$(CFG)" == "CNIcq - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"CNIcq.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CNIcq - Win32 Release"
# Name "CNIcq - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CNButton.cpp
# End Source File
# Begin Source File

SOURCE=.\CNIcq.cpp
# End Source File
# Begin Source File

SOURCE=.\CNIcq.rc
# End Source File
# Begin Source File

SOURCE=.\CNIcqDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CNPopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\Gif89a.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.CPP
# End Source File
# Begin Source File

SOURCE=.\ImageDataObject.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageSelector.cpp
# End Source File
# Begin Source File

SOURCE=.\IMainHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\IMainPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\IMChat.cpp
# End Source File
# Begin Source File

SOURCE=.\IMShortcutTool.cpp
# End Source File
# Begin Source File

SOURCE=.\IMTab.cpp
# End Source File
# Begin Source File

SOURCE=.\IMToolWin.cpp
# End Source File
# Begin Source File

SOURCE=.\IMTree.cpp
# End Source File
# Begin Source File

SOURCE=.\MSNButton.cpp
# End Source File
# Begin Source File

SOURCE=.\RichEditCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Skin.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemTray.CPP
# End Source File
# Begin Source File

SOURCE=.\TaskbarNotifier.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CNButton.h
# End Source File
# Begin Source File

SOURCE=.\CNIcq.h
# End Source File
# Begin Source File

SOURCE=.\CNIcqDlg.h
# End Source File
# Begin Source File

SOURCE=.\CNPopupMenu.h
# End Source File
# Begin Source File

SOURCE=.\Gif89a.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.H
# End Source File
# Begin Source File

SOURCE=.\ImageDataObject.h
# End Source File
# Begin Source File

SOURCE=.\ImageSelector.h
# End Source File
# Begin Source File

SOURCE=.\IMainHeader.h
# End Source File
# Begin Source File

SOURCE=.\IMainPanel.h
# End Source File
# Begin Source File

SOURCE=.\IMChat.h
# End Source File
# Begin Source File

SOURCE=.\IMShortcutTool.h
# End Source File
# Begin Source File

SOURCE=.\IMTab.h
# End Source File
# Begin Source File

SOURCE=.\IMToolWin.h
# End Source File
# Begin Source File

SOURCE=.\IMTree.h
# End Source File
# Begin Source File

SOURCE=.\MSNButton.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RichEditCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\Skin.h
# End Source File
# Begin Source File

SOURCE=.\StaticSplitter.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemTray.H
# End Source File
# Begin Source File

SOURCE=.\TaskbarNotifier.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\CNIcq.ico
# End Source File
# Begin Source File

SOURCE=.\res\CNIcq.rc2
# End Source File
# Begin Source File

SOURCE=.\res\drag.cur
# End Source File
# Begin Source File

SOURCE=.\res\emotions.bmp
# End Source File
# Begin Source File

SOURCE=.\res\font.bmp
# End Source File
# Begin Source File

SOURCE=.\res\forbidden.cur
# End Source File
# Begin Source File

SOURCE=.\res\format.bmp
# End Source File
# Begin Source File

SOURCE=.\res\formatba.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hand.cur
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
