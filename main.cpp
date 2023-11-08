#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>

#define IDR_RT_MANIFEST1 1

#define PATH_LENGTH 512
#define MHW_EXE_NAME "MonsterHunterWorld.exe" //MHW exe name
#define MHW_STEAM_CMD "start steam://run/582010" //steam command for launching MHW
#define RESHADE_DLL_NAME_MHW "dxgi.dll" //dll name reshade installer creates
#define RESHADE_DLL_NAME "ReShade64.dll" //dll name for reshade

using namespace std;
using namespace std::filesystem;

void pause() {
	cout << "Press Enter to continue...";
	getchar();
}

int main(){
	// get executable path
	TCHAR cExePath[PATH_LENGTH];
	memset(cExePath, 0, PATH_LENGTH);
	GetModuleFileName(NULL, cExePath, PATH_LENGTH);
	path pExePath(cExePath);
	path pExeDir = pExePath.parent_path();
	// cout << pExeDir << endl;
	path pMhwExe = pExeDir / MHW_EXE_NAME;
	// DLL Injector path
	path pInjectorPath = pExeDir / "inject.exe";
	// cout << pInjectorPath << endl;
	path pDllReshadeNew = pExeDir / RESHADE_DLL_NAME_MHW;
	// cout << pDllReshadeNew << endl;
	path pDllReshade = pExeDir / RESHADE_DLL_NAME;
	// Injector command
	string sInjectorCmd = "start \"ReShade Injector\" \"" + pInjectorPath.string() + "\" " + MHW_EXE_NAME;
	// cout << sInjectorCmd << endl;
	// check if required files exist
	if (!exists(pMhwExe)) {
		cout << "MHW game exe not found!" << endl;
		cout << "Put '" << "MHW-ReShadeInjector++.exe" << "' in MHW's game directory (where 'MonsterHunterWorld.exe' located)!" << endl;
		pause();
		return 1;
	}
	if (!exists(pInjectorPath)) {
		cout << "'inject.exe' not found!" << endl;
		cout << "Put '" << "inject.exe" << "' in MHW's game directory (where 'MonsterHunterWorld.exe' located)!" << endl;
		pause();
		return 2;
	}
	if (exists(pDllReshadeNew)) { // check if new reshade dll exists
		cout << "New ReShade dll found, updating..." << endl;
		if (exists(pDllReshade)) remove(pDllReshade);
		Sleep(1);
		rename(pDllReshadeNew, pDllReshade);
		Sleep(1);
		cout << "ReShade dll updated!" << endl;
		Sleep(500);
	} else if (!exists(pDllReshade)) { // check if old reshade dll exists
		cout << "'ReShade64.dll' not found!" << endl;
		cout << "Put '" << "ReShade64.dll" << "' in MHW's game directory (where 'MonsterHunterWorld.exe' located)!" << endl;
		pause();
		return 3;
	}
	// inject
	system(sInjectorCmd.c_str());
	cout << "Injector Started!" << endl;
	Sleep(1000);
	cout << "Starting MHW..." << endl;
	system(MHW_STEAM_CMD);
	Sleep(50);
	return 0;
}