@echo off
setlocal

set PROJ_DIR=%~dp0..
call %PROJ_DIR%\tools\load.bat

if exist "%PROJ_DIR%\build" (
    call %PROJ_DIR%\tools\clean.bat
)

call %PROJ_DIR%\tools\cmake_config.bat
call %PROJ_DIR%\tools\cmake_build.bat

cd %PROJ_DIR%\bin\
.\%PROJ_NAME%.exe

endlocal