# Microsoft Developer Studio Project File - Name="oRTP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=oRTP - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "oRTP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "oRTP.mak" CFG="oRTP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "oRTP - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "oRTP - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "oRTP - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "oRTP - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "oRTP - Win32 Release"
# Name "oRTP - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"

# Begin Source File

SOURCE=..\..\..\..\src\payloadtype.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\avprofile.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\ortp.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\ortpdlkm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\port_fct.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\posixtimer.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\rtpmod.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\rtpparse.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\rtpsession.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\rtpsignaltable.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\rtptimer.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\scheduler.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\sessionset.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\str_utils.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\telephonyevents.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\..\acconfig.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\src\errno-win32.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\src\ortp-config-win32.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\ortp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\payloadtype.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\port_fct.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\rtp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\rtpmod.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\rtpport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\rtpsession.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\rtpsignaltable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\rtptimer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\scheduler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\sessionset.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\str_utils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\telephonyevents.h
# End Source File
# End Group
# End Target
# End Project
