@echo off

rem Author    KMS - Martin Dubois, P. Eng
rem Copyright (C) 2026 KMS
rem License   http://www.apache.org/licenses/LICENSE-2.0
rem Product   TLBoDP
rem File      TestComputer.cmd

echo Executing  Scripts/TestComputer.cmd %1 %2 %3 ...

rem ===== Configuration =====================================================

set FILTER=255
set HOST_PORT=50000

rem ===== Verification ======================================================

if "" == "%2" (
    echo USER ERROR  Invalid command line
    echo Usage  TestComputer.cmd {HostIP} {Key} [BusParams]
    pause
    exit 10
)

rem ===== Brief =============================================================

set HOST_IP=%1
set KEY=%2
set BUS_PARAMS=%3

echo Host IP     %HOST_IP%
echo Host Port   %HOST_PORT%
echo Key         %KEY%

if not "" == "%BUS_PARAMS%" (
    echo Bus Params  %BUS_PARAMS%
)

pause

rem ===== Execution =========================================================

echo Configuring the kernel debugger...

bcdedit /dbgsettings net hostip:%HOST_IP% port:%HOST_PORT% key:%KEY%
if ERRORLEVEL 1 (
    echo ERROR  bcdedit /dbgsettings net hostip:%HOST_IP% port:%HOST_PORT% key:...  failed - %ERRORLEVEL%
    echo The script must be run as an administrator
    pause
    exit /B 20
)

echo The kernel debugger is configured

echo Enabling the kernel debugger...

bcdedit /debug on
if ERRORLEVEL 1 (
    echo ERROR  bcdedit /debug on  failed - %ERRORLEVEL%
    pause
    exit /B 30
)

echo The kernel debugger is enabled

echo Enabling the test signing...

bcdedit /set testsigning on
if ERRORLEVEL 1 (
    echo ERROR  bcdedit /set testsigning on  failed - %ERRORLEVEL%
    pause
    exit /B 40
)

echo The test signing is enabled

if not "" == "%BUS_PARAMS%" (
    bcdedit /set "{dbgsettings}" busparams %BUS_PARAMS%
)

if ERRORLEVEL 1 (
    echo ERROR  bcdedit /set "{dbgsettings}" busparams %BUS_PARAMS%  failed - %ERRORLEVEL%
    pause
    exit /B 50
)

echo Configuring the debug trace filter...

reg.exe ADD "HKLM\System\CurrentControlSet\Control\Session Manager\Debug Print Filter" /v IHVDRIVER /t REG_DWORD /d %FILTER%
if ERRORLEVEL 1 (
    echo ERROR  reg.exe ADD "HKLM\System\CurrentControlSet\Control\Session Manager\Debug Print Filter" /v IHVDRIVER /t REG_DWORD /d %FILTER%  failed - %ERRORLEVEL%
    pause
    echo /B 60
)

echo The debug trace filter is configured

echo Restarting the computer...

pause

shutdown /r /t 1

echo The computer is restarting

rem ===== End ===============================================================

echo OK
