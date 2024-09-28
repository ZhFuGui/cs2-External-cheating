#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include "../Define/Definition.h"
#include "GetGameStatus.h"
#include "../StringUtil/StringTypesFlow.h"
struct GameStatusInfo {
	BOOL OffsetUseful;
	BOOL InGameChess;
	BOOL InGameScreen;
	BOOL OnlineStatus;
	DWORD GameModel;
	DWORD MapStatus;
	DWORD ScoreStatus[2];
	int CNum;
	int CTNum;
	GameStatusInfo() {
		this->OffsetUseful = TRUE;
		this->InGameChess = FALSE;
		this->InGameScreen = FALSE;
		this->OnlineStatus = FALSE;
		this->GameModel = NULL;
		this->MapStatus = NULL;
		this->ScoreStatus[0] = NULL;
		this->ScoreStatus[1] = NULL;
		this->CNum = 0;
		this->CTNum = 0;
	};
};

struct GameStatusInfo GetBasicGameStatus(GameStatusInfo GameStatusInfoS, HMODULE ClientModuleAddress, HANDLE hProcess);

struct GameStatusInfo GetRatioOfC2CT(GameStatusInfo GameStatusInfoS, HMODULE ServerModuleAddress, HANDLE hProcess);

struct GameStatusInfo IfGameScreen(GameStatusInfo GameStatusInfoS, HMODULE SDL3ModuleAddress, HANDLE hProcess);