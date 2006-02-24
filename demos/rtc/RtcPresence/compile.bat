@echo off

rem *************************************************************************
rem Build file for RTCPresence sample
rem Microsoft Real Time Communications Client API SDK 
rem (c) Copyright 2003 Microsoft Corporation. All rights reserved.
rem *************************************************************************

rem Usage
if "%1" == "/?" goto usage
if "%1" == "/-" goto usage

rem Output directory
set OUTDIR=bin
if not exist "%OUTDIR%" mkdir "%OUTDIR%"

rem Interop.RTCCore.dll reference
set INTEROP=Interop.RTCCore.dll
if not exist ".\%INTEROP%" goto NeedInterop
goto RunCSC

:RunCSC
rem Detect csc
if "%FRAMEWORKDIR%" == "" goto SetFrameworkDir
if not exist "%FRAMEWORKDIR%\csc.exe" goto NeedFramework
goto Build

:SetFrameworkDir
if exist "%WINDIR%\Microsoft.NET\Framework\v1.1.4322\csc.exe" (set FRAMEWORKDIR="%WINDIR%\Microsoft.NET\Framework\v1.1.4322"& goto Build)
if exist "%WINDIR%\Microsoft.NET\Framework\v1.0.3705\csc.exe" (set FRAMEWORKDIR="%WINDIR%\Microsoft.NET\Framework\v1.0.3705"& goto Build)

:Build
rem Project files
set FILES=RTCPresence.cs IRTCPresenceUI.cs RTCPresenceCore.cs RTCPresenceHelp.cs RTCPresenceAuthDialog.cs RTCPresenceLogonDialog.cs  RTCPresenceAddressDialog.cs RTCPresenceTreeNode.cs RTCPresencePollDialog.cs RTCPresenceConst.cs RTCPresenceAuthData.cs
set CSCFLAGS=/nowarn:1595 /target:winexe /debug:pdbonly /out:%OUTDIR%\RTCPresence.exe
set REFERENCES=/reference:".\Interop.RTCCore.dll",%FRAMEWORKDIR%\System.dll,%FRAMEWORKDIR%\System.Drawing.dll,%FRAMEWORKDIR%\System.Windows.Forms.dll

rem Build RTCPresence
echo Now building RTCPresence (csc.exe was found at %FRAMEWORKDIR%). 
echo Output directory is %OUTDIR%

%FRAMEWORKDIR%\csc.exe %CSCFLAGS% %REFERENCES% %FILES%

if exist %OUTDIR%\RTCPresence.exe (echo Built successfully & goto PrintHelpStuff)
goto done

:PrintHelpStuff
echo In order to run the sample:
echo - Copy Interop.RTCCore.dll to the executable directory
echo - Copy RTCPresence.exe.manifest to the executable directory
goto done

:NeedInterop
echo The file Interop.RTCCore.dll was not locatable.
echo Please copy the file to the current directory and retry.
goto done

:NeedFramework
echo The framework path could not be located.
echo Please set the .NET framework path in the environment variable FRAMEWORKDIR and retry.
goto done

:usage
echo Launch Compile.bat to compile RTCPresence
echo Please copy the Interop.RTCCore.dll file to the current directory if needed
echo If the .NET framework is not installed in the default location, give its path in FRAMEWORKDIR variable

:done
