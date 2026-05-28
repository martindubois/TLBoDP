@echo off

rem Author    KMS - Martin Dubois, P. Eng.
rem Copyright (C) 2026 KMS
rem Lisense   http://www.apache.org/licenses/LICENSE-2.0
rem Product   TLBoDP
rem File      UploadDocumentation.cmd

echo  Executing  UploadDocumentation.cmd  ...

rem ===== Configuration =====================================================

set FTP_FOLDER=public_html/TLBoDP

set FTP_SERVER=ftp.kms-quebec.com

set USERNAME="-ukmsquebe"

rem ===== Initialisation ====================================================

set CURL_EXE=Import\Curl\curl.exe

set CURL_OPT=--ftp-pasv

set SRC_FOLDER=doxygen_en\html

rem ===== Verification ======================================================

if not exist %CURL_EXE% (
    echo FATAL ERROR  %CURL_EXE%  does not exist
    echo Execute K:\KMS-Import.exe
    pause
    exit /B 10
)

if not exist %SRC_FOLDER% (
    echo FATAL ERROR  %SRC_FOLDER%  does not exist
    pause
    exit /B 20
)

rem  ===== Execution ========================================================

set /p PASSWORD="FTP password : "

pushd %SRC_FOLDER%

for %%F in ( *.css ) do (
    echo Uploading  %%F  ...
    ..\..\%CURL_EXE% %USERNAME%:%PASSWORD% %CURL_OPT% -T %%F ftp://%FTP_SERVER%/%FTP_FOLDER%/%%F
    if ERRORLEVEL 1 (
        popd
        echo ERROR  %CURL_EXE% %USERNAME%:... %CURL_OPT% -T %%F  failed - %ERRORLEVEL%
        pause
        exit /B 30
    )
)

for %%F in ( *.html ) do (
    echo Uploading  %%F  ...
    ..\..\%CURL_EXE% %USERNAME%:%PASSWORD% %CURL_OPT% -T %%F ftp://%FTP_SERVER%/%FTP_FOLDER%/%%F
    if ERRORLEVEL 1 (
        popd
        echo ERROR  %CURL_EXE% %USERNAME%:... %CURL_OPT% -T %%F  failed - %ERRORLEVEL%
        pause
        exit /B 40
    )
)

for %%F in ( *.js ) do (
    echo Uploading  %%F  ...
    ..\..\%CURL_EXE% %USERNAME%:%PASSWORD% %CURL_OPT% -T %%F ftp://%FTP_SERVER%/%FTP_FOLDER%/%%F
    if ERRORLEVEL 1 (
        popd
        echo ERROR  %CURL_EXE% %USERNAME%:... %CURL_OPT% -T %%F  failed - %ERRORLEVEL%
        pause
        exit /B 50
    )
)

for %%F in ( *.png ) do (
    echo Uploading  %%F  ...
    ..\..\%CURL_EXE% %USERNAME%:%PASSWORD% %CURL_OPT% -T %%F ftp://%FTP_SERVER%/%FTP_FOLDER%/%%F
    if ERRORLEVEL 1 (
        popd
        echo ERROR  %CURL_EXE% %USERNAME%:... %CURL_OPT% -T %%F  failed - %ERRORLEVEL%
        pause
        exit /B 60
    )
)

popd

rem  ===== Fin ==============================================================

echo  OK
