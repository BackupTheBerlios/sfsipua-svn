@echo off

REM ;-- Check if the destination directory exists

REM ;-- change the next line if you have Visual studio installed in a different path
set VS7INSTALLDIR=%ProgramFiles%\Microsoft Visual Studio .NET 2003

if not exist "%VS7INSTALLDIR%\Vc7\vcprojects" goto DirNotFound

REM ;-- Copy the wizard files

set GDWIZARDDST=%VS7INSTALLDIR%\Vc7\vcprojects\Google
md "%GDWIZARDDST%"
copy GDDisplayPluginWizard.* "%GDWIZARDDST%\Google Desktop Display Plugin Wizard.*"
if not ERRORLEVEL 0 goto CantCopyFiles

REM ;-- Append the current directory's path to the end of the wizard file so it can find the required files here.

echo Param="ABSOLUTE_PATH = %cd%">>"%GDWIZARDDST%\Google Desktop Display Plugin Wizard.vsz"
if not ERRORLEVEL 0 goto CantUpdateFiles

echo .
echo .
echo Successfully copied wizard files to Visual Studio directory.
goto Finish

:DirNotFound
echo .
echo .
echo Cannot find VS.NET 2003 installation directory. Please edit this batch file to give the correct path. Exiting.
goto Finish

:CantCopyFiles
echo .
echo .
echo Error when copying wizard files to Visual Studio directory. Exiting.
goto Finish

:CantUpdateFiles
echo .
echo .
echo Error when updating the wizard files in Visual Studio directory. Exiting.
goto Finish

:Finish
echo .
echo .
pause
