#pragma once
#include <windows.h>
#include <cmath>
#include "./Define/Definition.h"

struct Player {
	int Ini_Index;
	float distance;
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
	int BulletsLeft;
	float COS_HorizontalAngle;
	float SIN_HorizontalAngle;
	float SIN_VerticalAngle;
	Player() {
		this->Ini_Index = 0;
		this->BulletsLeft = -1;
		this->distance = 1000;
		this->HP = 0;
		this->LifeState = 0;
		this->TeamTag = 0;
		this->Speed_X = 0;
		this->Speed_Y = 0;
		this->X_Feet = g_initV;
		this->Y_Feet = g_initV;
		this->Z_Feet = g_initV;
		this->ANGLE_Vertical = 0;
		this->ANGLE_Horizontal = 0;
		this->X_Head = g_initV;
		this->Y_Head = g_initV;
		this->Z_Head = g_initV;
		this->COS_HorizontalAngle = 0;
		this->SIN_HorizontalAngle = 0;
		this->SIN_VerticalAngle = 0;
	}
}TemporaryPlayer, AllPlayerArray[19];

long long NextAddress_GetEveryPlayer; long long NextNextAddress_GetEveryPlayer;
DWORD GetEveryPlayer(Player &Player, HMODULE ClientModuleAddress, HANDLE hProcess,int i) {

	Player.Ini_Index = i;
	ReadProcessMemory(hProcess, (LPVOID)((uintptr_t)ClientModuleAddress+Offset::ClientDLL::PlayerList::Address), &NextAddress_GetEveryPlayer, 8, 0);

	ReadProcessMemory(hProcess, (LPVOID)(NextAddress_GetEveryPlayer +(i*0x8)), &NextNextAddress_GetEveryPlayer, 8, 0);

	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::HP), &Player.HP, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::LifeState), &Player.LifeState, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::Speed_X), &Player.Speed_X, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::Speed_Y), &Player.Speed_Y, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::Speed_Z), &Player.Speed_Z, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::X_Feet), &Player.X_Feet, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::Y_Feet), &Player.Y_Feet, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::Z_Feet), &Player.Z_Feet, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::ANGLE_Vertical), &Player.ANGLE_Vertical, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::ANGLE_Horizontal), &Player.ANGLE_Horizontal, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::X_Head), &Player.X_Head, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::Y_Head), &Player.Y_Head, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::Z_Head), &Player.Z_Head, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::BulletsLeft), &Player.BulletsLeft, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::COS_HorizontalAngle), &Player.COS_HorizontalAngle, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::SIN_HorizontalAngle), &Player.SIN_HorizontalAngle, 4, 0);
	ReadProcessMemory(hProcess, (LPVOID)(NextNextAddress_GetEveryPlayer + Offset::ClientDLL::Player::SIN_VerticalAngle), &Player.SIN_VerticalAngle, 4, 0);

	return 0;
}