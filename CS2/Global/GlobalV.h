#pragma once
#include <Windows.h>
//版本信息
BOOL isCurrentVersionAvailable = TRUE;
//游戏进程信息
struct 
{
	DWORD GamePid = 0;
	HANDLE GameProcess = 0;
	char GameFile[MAX_PATH] = "Hello, CS2!";
	HWND g_HWND = 0;
	HINSTANCE g_HINSTANCE = 0;

}GameProcessInfo;
//游戏模块地址
struct
{
	HMODULE ClientModuleAddress = 0;
	HMODULE Engine2ModuleAddress = 0;
	HMODULE MatchmakingModuleAddress = 0;
	HMODULE ServerModuleAddress = 0;
	HMODULE SDL3ModuleAddress = 0; 
	HMODULE SteamaudioModuleAddress = 0;

}ModuleInfo;
//功能开关
struct SFeatureFlags
{
	BOOL ESP_Flag = 0;//透视
	BOOL ReportPosition_Flag = 0;//报点
	BOOL AimBot_Flag = 0;//自瞄

}FeatureFlags;
//玩家信息

//对局信息

//自瞄时机
BOOL AimBotTime = FALSE;
