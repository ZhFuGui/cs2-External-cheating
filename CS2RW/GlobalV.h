#pragma once
#include <Windows.h>
//全局窗口句柄
HWND g_HWND = 0;
//模块地址
HMODULE ClientModuleAddress = 0;
HMODULE Engine2ModuleAddress = 0;
HMODULE MatchmakingModuleAddress = 0;
HMODULE ServerModuleAddress = 0;
HMODULE SDL3ModuleAddress = 0;
//版本信息
BOOL VersionCheck = 1;
//获取CS2.exe进程句柄
DWORD GamePid = 0;
HANDLE GameProcess = 0;
char GameFile[MAX_PATH] = "Hello, CS2!";
//我的信息
LPVOID Localplayer_Address;