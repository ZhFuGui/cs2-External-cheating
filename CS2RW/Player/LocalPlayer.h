#pragma once
#include <Windows.h>
struct SLocalPlayer {
	unsigned int HP;
	unsigned int LifeState;
	unsigned int TeamTag;
	float Speed_X;
	float Speed_Y;
	float Speed_Z;
	float X_Feet;
	float Y_Feet;
	float Z_Feet;
	float ANGLE_Vertical;
	float ANGLE_Horizontal;
	float X_Head;
	float Y_Head;
	float Z_Head;
	enum eEnemyTeamTag { UNKNOW=1,CT_TEAM=2,C_TEAM=3 }EnemyTeamTag;
	SLocalPlayer() {
		this->EnemyTeamTag = eEnemyTeamTag::UNKNOW;
		this->HP = 0;
		this->LifeState = 0;
		this->TeamTag = 0;
		this->Speed_X = 0;
		this->Speed_Y = 0;
		this->Speed_Z = 0;
		this->X_Feet = g_initV;
		this->Y_Feet = g_initV;
		this->Z_Feet = g_initV;
		this->ANGLE_Vertical = 0;
		this->ANGLE_Horizontal = 0;
		this->X_Head = g_initV;
		this->Y_Head = g_initV;
		this->Z_Head = g_initV;
	}
}Localplayer;

long long SecondAddress_Localplayer;

void GetLocalPlayer(SLocalPlayer &LocalPlayer, HMODULE ClientModuleAddress, HANDLE hProcess) noexcept{

	ReadProcessMemory(hProcess, (LPVOID)((uintptr_t)ClientModuleAddress+Offset::ClientDLL::LocalPlayer::Address), &SecondAddress_Localplayer, 8, 0);
	 
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::HP), &LocalPlayer.HP, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::LifeState), &LocalPlayer.LifeState, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::TeamTag), &LocalPlayer.TeamTag, 4, 0); LocalPlayer.EnemyTeamTag = (LocalPlayer.TeamTag == 2) ? SLocalPlayer::eEnemyTeamTag::C_TEAM : ((LocalPlayer.TeamTag == 3) ? SLocalPlayer::eEnemyTeamTag::CT_TEAM : SLocalPlayer::eEnemyTeamTag::UNKNOW);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::Speed_X), &LocalPlayer.Speed_X, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::Speed_Y), &LocalPlayer.Speed_Y, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::Speed_Z), &LocalPlayer.Speed_Z, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::X_Feet), &LocalPlayer.X_Feet, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::Y_Feet), &LocalPlayer.Y_Feet, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::Z_Feet), &LocalPlayer.Z_Feet, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::ANGLE_Vertical), &LocalPlayer.ANGLE_Vertical, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::ANGLE_Horizontal), &LocalPlayer.ANGLE_Horizontal, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::X_Head), &LocalPlayer.X_Head, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::Y_Head), &LocalPlayer.Y_Head, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(SecondAddress_Localplayer + Offset::ClientDLL::Player::Z_Head), &LocalPlayer.Z_Head, 4, 0);
};