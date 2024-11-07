@echo off
rem This script compile code using clang++
rem First parameter $1 must be file name (use Tab for auto complete)
rem Other next parameters will be pasted as parameters for compiler

rem Variables
set ROOT_PATH=%cd%\
set BUILD_PATH=%cd%\build\

set SOURCE_FILE=%1
set EXE_PATH=%BUILD_PATH%executable.exe

@RD /S /Q %BUILD_PATH%
md %BUILD_PATH%

clang++ %SOURCE_FILE% --output=%EXE_PATH% %2 %3 %4 %5 %6 %7 %8 %9
build\executable.exe
@echo on
