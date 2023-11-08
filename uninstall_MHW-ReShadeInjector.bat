@echo off
echo Removing MHW-ReShadeInjector++ files...
pause
::del /q inject.exe MHW-ReShadeInjector++.exe ReShade64.dll
start "" cmd /c "timeout 1 > NUL && del /q inject.exe MHW-ReShadeInjector++.exe ReShade64.dll uninstall_MHW-ReShadeInjector.bat && echo Done! && timeout 1 > NUL"
exit 0
