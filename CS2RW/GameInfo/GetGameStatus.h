#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include "../Define/Definition.h"
#include "GetGameStatus.h"
#include "../StringUtil/StringTypesFlow.h"
struct  SGameStatusInfo{
	BOOL VersionUseful;
	BOOL InGameChess;
	BOOL MapInfoLoaded;
	BOOL InGameScreen;
	BOOL OnlineStatus;
	DWORD GameModel;
	enum MAP MapStatus;
	DWORD ScoreStatus[2];
	int CNum_Alive;
	int CTNum_Alive;
	int AllPlayerNum;
	int AllPlayerNum_Alive;
	SGameStatusInfo() {
		this->VersionUseful = TRUE;
		this->InGameChess = FALSE;
		this->MapInfoLoaded = FALSE;
		this->InGameScreen = FALSE;
		this->OnlineStatus = FALSE;
		this->GameModel = NULL;
		this->MapStatus = MAP::UNKNOW;
		this->ScoreStatus[0] = NULL;
		this->ScoreStatus[1] = NULL;
		this->CNum_Alive = 0;
		this->CTNum_Alive = 0;
		this->AllPlayerNum = 0;
		this->AllPlayerNum_Alive = 0;
	};
}GameStatusInfo;

void GetBasicGameStatus(SGameStatusInfo &GameStatusInfo, HMODULE ClientModuleAddress, HANDLE hProcess) {

	char c; std::string GameChessInfo;
	for (int i = 0; i < LENGTH_GameStatusInfo; i++) {
		ReadProcessMemory(hProcess, (void*)((uintptr_t)ClientModuleAddress + Offset::ClientDLL::GameInfo::MapInfo + i), &c, 1, 0);
		GameChessInfo += c;
	};

	//是否开始游戏
	if (GameChessInfo.find("Playing CS:GO") != std::string::npos) {
		GameStatusInfo.MapInfoLoaded = FALSE;
		GameStatusInfo.OnlineStatus = FALSE;
		GameStatusInfo.GameModel = NULL;
		GameStatusInfo.MapStatus = MAP::UNKNOW;
		GameStatusInfo.ScoreStatus[0] = NULL;
		GameStatusInfo.ScoreStatus[1] = NULL;
	}
	else {
		GameStatusInfo.MapInfoLoaded = TRUE;
	}
	//如果是开始了游戏那么就开始写入信息
	if (GameStatusInfo.InGameChess) {
		//是否在线
		if (GameChessInfo.find("Offline") != std::string::npos) {
			GameStatusInfo.OnlineStatus = FALSE;
		}
		else if (GameChessInfo.find("Online") != std::string::npos) {
			GameStatusInfo.OnlineStatus = TRUE;
		}
		else {
			GameStatusInfo.OnlineStatus = FALSE;
		}

		//游戏模式
		if (GameChessInfo.find("Competitive") != std::string::npos) {
			GameStatusInfo.GameModel = Competitive;
		}
		else if (GameChessInfo.find("Wingman") != std::string::npos) {
			GameStatusInfo.GameModel = Wingman;
		}
		else if (GameChessInfo.find("Casual") != std::string::npos) {
			GameStatusInfo.GameModel = Casual;
		}
		else if (GameChessInfo.find("Deathmatch") != std::string::npos) {
			GameStatusInfo.GameModel = Deathmatch;
		}
		else if (GameChessInfo.find("Arms Race") != std::string::npos) {
			GameStatusInfo.GameModel = ArmsRace;
		}
		else {
			GameStatusInfo.GameModel = UNKNOWN;
		}

		//地图
		if (GameChessInfo.find("Dust II") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::DustII;
		}
		else if (GameChessInfo.find("Mirage") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Mirage;
		}
		else if (GameChessInfo.find("Vertigo") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Vertigo;
		}
		else if (GameChessInfo.find("Ancient") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Ancient;
		}
		else if (GameChessInfo.find("Inferno") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Inferno;
		}
		else if (GameChessInfo.find("Nuke") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Nuke;
		}
		else if (GameChessInfo.find("Anubis") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Anubis;
		}
		else if (GameChessInfo.find("Overpass") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Overpass;
		}
		else if (GameChessInfo.find("Thera") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Thera;
		}
		else if (GameChessInfo.find("Mills") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Mills;
		}
		else if (GameChessInfo.find("Office") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Office;
		}
		else if (GameChessInfo.find("Italy") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::DustII;
		}
		else if (GameChessInfo.find("Assembly") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Assembly;
		}
		else if (GameChessInfo.find("Memento") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Memento;
		}
		else if (GameChessInfo.find("Baggage") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Baggage;
		}
		else if (GameChessInfo.find("Shoots") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::Shoots;
		}
		else if (GameChessInfo.find("Pool Day") != std::string::npos) {
			GameStatusInfo.MapStatus = MAP::PoolDay;
		}
		else {
			GameStatusInfo.MapStatus = MAP::UNKNOW;
		}

		//比分状态
		size_t openBracket = GameChessInfo.find('[');
		size_t closeBracket = GameChessInfo.find(']');
		DWORD FirstScoreD = 404; DWORD SecondScoreD = 404;
		if (openBracket && closeBracket) {
			std::string FirstScoreS; std::string SecondScoreS;

			if (openBracket != std::string::npos && closeBracket != std::string::npos) {
				std::string innerString = GameChessInfo.substr(openBracket + 1, closeBracket - openBracket - 1);
				size_t colonPos = innerString.find(':');
				if (colonPos != std::string::npos) {
					FirstScoreS = innerString.substr(0, colonPos);
					SecondScoreS = innerString.substr(colonPos + 1);
					FirstScoreD = string2DWORD(FirstScoreS);
					SecondScoreD = string2DWORD(SecondScoreS);

				}
				else {
					MessageBoxW(0, L"No ':' found in the inner string.", L"错误", MB_ICONWARNING);
				}
			}
			else {
				//MessageBoxW(0, L"No valid brackets found.", L"错误", MB_ICONWARNING);
			}
		}
		GameStatusInfo.ScoreStatus[0] = FirstScoreD;
		GameStatusInfo.ScoreStatus[1] = SecondScoreD;
	}

}
void IfGameScreen(SGameStatusInfo &GameStatusInfo, HMODULE SDL3ModuleAddress, HANDLE hProcess) {
	byte i = 1;
	ReadProcessMemory(hProcess, (void*)((long long)SDL3ModuleAddress + Offset::SDL3DLL::IfInGameView::Address), &i, 1, 0);
	if (i == 0) { GameStatusInfo.InGameScreen = TRUE; }
	else { GameStatusInfo.InGameScreen = FALSE; };
};
void GetAllPlayerNum(SGameStatusInfo& GameStatusInfo, HMODULE ServerModuleAddress, HANDLE hProcess) noexcept{
	ReadProcessMemory(hProcess, (LPVOID)((uintptr_t)ServerModuleAddress + Offset::ServerDLL::GameChessInfo::AllPlayerNum), &GameStatusInfo.AllPlayerNum, 4, 0);
}
void GetInGameChess(SGameStatusInfo& GameStatusInfo, HMODULE SteamaudioModuleAddress, HANDLE hProcess) noexcept {
	ReadProcessMemory(hProcess, (LPVOID)((uintptr_t)SteamaudioModuleAddress + Offset::SteamaudioDLL::GameInfo::InGameChess), &GameStatusInfo.InGameChess, 4, 0);
};
