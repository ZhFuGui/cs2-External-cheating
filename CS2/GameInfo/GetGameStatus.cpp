#include "GetGameStatus.h"

long long NextAddress;

long long NextNextAddress;


struct GameStatusInfo GetBasicGameStatus(GameStatusInfo GameStatusInfoS, HMODULE ClientModuleAddress, HANDLE hProcess) {

	char c; std::string ALL_Game_Info;
	for (int i = 0; i < LENGTH_GameStatusInfo; i++) {
		ReadProcessMemory(hProcess, (void*)((long long)ClientModuleAddress + GameModel_Offset + i), &c, 1, 0);
		ALL_Game_Info += c;
	}
	//偏移是否失效
	if (ALL_Game_Info.find("Playing CS:GO") == std::string::npos && ALL_Game_Info.find("Deathmatch") == std::string::npos && ALL_Game_Info.find("Offline") == std::string::npos && ALL_Game_Info.find("Competitive") == std::string::npos && ALL_Game_Info.find("Wingman") == std::string::npos && ALL_Game_Info.find("Casual") == std::string::npos && ALL_Game_Info.find("Arms Race") == std::string::npos) { GameStatusInfoS.OffsetUseful = FALSE; }
	else { GameStatusInfoS.OffsetUseful = TRUE; };

	//是否开始游戏
	if (ALL_Game_Info.find("Playing CS:GO") != std::string::npos) {
		GameStatusInfoS.InGameChess = FALSE;
		GameStatusInfoS.OnlineStatus = FALSE;
		GameStatusInfoS.GameModel = NULL;
		GameStatusInfoS.MapStatus = NULL;
		GameStatusInfoS.ScoreStatus[0] = NULL;
		GameStatusInfoS.ScoreStatus[1] = NULL;
		return GameStatusInfoS;
	}
	else {
		GameStatusInfoS.InGameChess = TRUE;
	}

	//如果是开始了游戏那么就开始写入信息
	if (GameStatusInfoS.InGameChess) {
		//是否在线
		if (ALL_Game_Info.find("Offline") != std::string::npos) {
			GameStatusInfoS.OnlineStatus = FALSE;
		}
		else if (ALL_Game_Info.find("Online") != std::string::npos) {
			GameStatusInfoS.OnlineStatus = TRUE;
		}
		else {
			GameStatusInfoS.OnlineStatus = FALSE;
		}

		//游戏模式
		if (ALL_Game_Info.find("Competitive") != std::string::npos) {
			GameStatusInfoS.GameModel = Competitive;
		}
		else if (ALL_Game_Info.find("Wingman") != std::string::npos) {
			GameStatusInfoS.GameModel = Wingman;
		}
		else if (ALL_Game_Info.find("Casual") != std::string::npos) {
			GameStatusInfoS.GameModel = Casual;
		}
		else if (ALL_Game_Info.find("Deathmatch") != std::string::npos) {
			GameStatusInfoS.GameModel = Deathmatch;
		}
		else if (ALL_Game_Info.find("Arms Race") != std::string::npos) {
			GameStatusInfoS.GameModel = ArmsRace;
		}
		else {
			GameStatusInfoS.GameModel = UNKNOWN;
		}

		//地图
		if (ALL_Game_Info.find("Dust II") != std::string::npos) {
			GameStatusInfoS.MapStatus = DustII;
		}
		else if (ALL_Game_Info.find("Mirage") != std::string::npos) {
			GameStatusInfoS.MapStatus = Mirage;
		}
		else if (ALL_Game_Info.find("Vertigo") != std::string::npos) {
			GameStatusInfoS.MapStatus = Vertigo;
		}
		else if (ALL_Game_Info.find("Ancient") != std::string::npos) {
			GameStatusInfoS.MapStatus = Ancient;
		}
		else if (ALL_Game_Info.find("Inferno") != std::string::npos) {
			GameStatusInfoS.MapStatus = Inferno;
		}
		else if (ALL_Game_Info.find("Nuke") != std::string::npos) {
			GameStatusInfoS.MapStatus = Nuke;
		}
		else if (ALL_Game_Info.find("Anubis") != std::string::npos) {
			GameStatusInfoS.MapStatus = Anubis;
		}
		else if (ALL_Game_Info.find("Overpass") != std::string::npos) {
			GameStatusInfoS.MapStatus = Overpass;
		}
		else if (ALL_Game_Info.find("Thera") != std::string::npos) {
			GameStatusInfoS.MapStatus = Thera;
		}
		else if (ALL_Game_Info.find("Mills") != std::string::npos) {
			GameStatusInfoS.MapStatus = Mills;
		}
		else if (ALL_Game_Info.find("Office") != std::string::npos) {
			GameStatusInfoS.MapStatus = Office;
		}
		else if (ALL_Game_Info.find("Italy") != std::string::npos) {
			GameStatusInfoS.MapStatus = DustII;
		}
		else if (ALL_Game_Info.find("Assembly") != std::string::npos) {
			GameStatusInfoS.MapStatus = Assembly;
		}
		else if (ALL_Game_Info.find("Memento") != std::string::npos) {
			GameStatusInfoS.MapStatus = Memento;
		}
		else if (ALL_Game_Info.find("Baggage") != std::string::npos) {
			GameStatusInfoS.MapStatus = Baggage;
		}
		else if (ALL_Game_Info.find("Shoots") != std::string::npos) {
			GameStatusInfoS.MapStatus = Shoots;
		}
		else if (ALL_Game_Info.find("Pool Day") != std::string::npos) {
			GameStatusInfoS.MapStatus = PoolDay;
		}
		else {
			GameStatusInfoS.MapStatus = UNKNOWN;
		}

		//比分状态
		size_t openBracket = ALL_Game_Info.find('[');
		size_t closeBracket = ALL_Game_Info.find(']');
		DWORD FirstScoreD = 404; DWORD SecondScoreD = 404;
		if (openBracket && closeBracket) {
			std::string FirstScoreS; std::string SecondScoreS;

			if (openBracket != std::string::npos && closeBracket != std::string::npos) {
				std::string innerString = ALL_Game_Info.substr(openBracket + 1, closeBracket - openBracket - 1);
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
		GameStatusInfoS.ScoreStatus[0] = FirstScoreD;
		GameStatusInfoS.ScoreStatus[1] = SecondScoreD;
	}

	return GameStatusInfoS;
}


struct GameStatusInfo IfGameScreen(GameStatusInfo GameStatusInfoS, HMODULE SDL3ModuleAddress, HANDLE hProcess) {
	byte i = 1;
	ReadProcessMemory(hProcess, (void*)((long long)SDL3ModuleAddress + IfGmaeView), &i, 1, 0);
	if (i == 0) { GameStatusInfoS.InGameScreen = TRUE; }
	else { GameStatusInfoS.InGameScreen = FALSE; };
	return GameStatusInfoS;
};

long long NextAddress_RatioOfC2CT;

struct GameStatusInfo GetRatioOfC2CT(GameStatusInfo GameStatusInfoS, HMODULE ServerModuleAddress, HANDLE hProcess)
{
	//人数比
	ReadProcessMemory(hProcess, (void*)((long long)ServerModuleAddress + RatioOfC2CT_First_Offset), &NextAddress_RatioOfC2CT, 8, 0);
	ReadProcessMemory(hProcess, (void*)(NextAddress_RatioOfC2CT + RatioOfC2CT_Second_Offset), &GameStatusInfoS.CNum, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextAddress_RatioOfC2CT + RatioOfC2CT_Second_Offset+0x4), &GameStatusInfoS.CTNum, 4, 0);

	return GameStatusInfoS;
};