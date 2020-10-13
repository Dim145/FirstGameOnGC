@echo off

set PROG=WallBreak

set GBDK_N=..\gbdk-n
set CC=gbdk-n-compile.bat
set LD=gbdk-n-link.bat
set MR=gbdk-n-make-rom.bat

set repSource=../src
set repBuild=../bin

:: Clean
if "%1" == "clean" (
    del %repSource%\*.rel
    del %repSource%\*.lst
    del %repSource%\*.sym
    del %repSource%\*.asm
    del %repBuild%/%PROG%.gb
    del %repBuild%/%PROG%.ihx
    del %repBuild%/%PROG%.map
    del %repBuild%/%PROG%.sym
    del %repBuild%/%PROG%.noi
    del %repBuild%/%PROG%.lk
    goto end
)

:: Check that gbdk-n is available
rem if not exist %GBDK_N% (
rem     echo "gbdk-n folder not found at '%GBDK_N%'."
rem     pause
rem     goto end
rem )

:: Check that gbdk-n is compiled
rem if not exist %GBDK_N%\lib\gb.lib (
rem     echo "gbdk-n library is not yet compiled. Please go to the '%GBDK_N%' directory and run 'Make.bat' to build it."
rem     pause
rem     goto end
rem )

:: Compile (*.c -> *.res)
for %%A in (%repSource%\*.c) do (
    if not "%%~nxA" == "main.c" (
    if exist %repBuild%/%%~nA.rel del "%repBuild%/%%~nA.rel"
    echo Compiling: %%~nxA
    call %CC% -c %repSource%\%%~nA.c -o %repBuild%\%%~nA.rel
    if not exist %repBuild%\%%~nA.rel echo. && echo "Build failed!" && echo. && pause && goto end )
)

:: Link  (*.rel -> prog.ihx)
setlocal enabledelayedexpansion
set REL_LIST=
for %%A in (%repBuild%\*.rel) do set REL_LIST=!REL_LiST! %%A

if exist %repBuild%/%PROG%.ihx del "%repBuild%/%PROG%.ihx"
echo Linking: %PROG%.ihx
call %LD% -o %repBuild%/%PROG%.ihx %REL_LIST%
if not exist %repBuild%/%PROG%.ihx echo. && echo "Build failed!" && echo. && pause && goto end

:: Build the ROM (prog.ihx -> prog.gb)
if exist %repBuild%/%PROG%.gb del "%repBuild%/%PROG%.gb"
echo Building ROM: %PROG%.gb
call %MR% %repBuild%/%PROG%.ihx %repBuild%/%PROG%.gb
if not exist %repBuild%/%PROG%.gb echo. && echo "Build failed!" && echo. && pause && goto end

echo "Build succeded!"

:end