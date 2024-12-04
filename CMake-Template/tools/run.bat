@echo off
setlocal

set PROJ_DIR=%~dp0..
call %PROJ_DIR%\tools\load.bat


if not exist "%PROJ_DIR%\bin\" (
	goto :eof
)

:: 判断文件夹是否存在
if not exist "%PROJ_DIR%\bin\%PROJ_NAME%.exe" (
	call %PROJ_DIR%\tools\cmake_build.bat
)

cd %PROJ_DIR%\bin\
.\%PROJ_NAME%.exe

endlocal