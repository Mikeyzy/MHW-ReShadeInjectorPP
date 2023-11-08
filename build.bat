@echo off
@call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64 %*

rc program.rc
cl /utf-8 /std:c++17 /MD /Os main.cpp /link program.res /MANIFEST:EMBED /MANIFESTUAC:"level='requireAdministrator' uiAccess='false'" -out:MHW-ReShadeInjector++.exe
