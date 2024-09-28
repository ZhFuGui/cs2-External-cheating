#pragma once
#include <windows.h>
#include <cmath>
#include "./Define/Definition.h"
#include "GetAngle.h"
struct SLocalPlayer {
	float Sensitivity_Mouse;
	float Angle_H;
	float Angle_V;
	float Foot_x;
	float Foot_y;
	float Foot_z;
	float Head_x;
	float Head_y;
	float Head_z;
	int Camp;
	int state;
	SLocalPlayer() {
		this->Angle_V = 0;
		this->Sensitivity_Mouse = 1;
		this->Angle_H = 0;
		this->Angle_V = 0;
		this->Foot_x = 0.1234;
		this->Foot_y = 0.1234;
		this->Foot_z = 0.1234;
		this->Head_x = 0.1234;
		this->Head_y = 0.1234;
		this->Head_z = 0.1234;
		this->Camp = 0;
		this->state = 0;
	}
};
struct Player {
	int Ini_Index;
	int BulletsLeft;
	float distance;
	float Angle_COS_H;
	float Angle_SIN_H;
	float Angle_SIN_V;
	float Angle_V;
	int HP;
	float Foot_x;
	float Foot_y;
	float Foot_z;
	float Head_x;
	float Head_y;
	float Head_z;
	float Speed_x;
	float Speed_y;
	float Speed_z;
	int Camp;
	int state;
	Player() {
		this->Ini_Index = 0;
		this->BulletsLeft = -1;
		this->distance = 1000;
		this->Angle_V = 0;
		this->Angle_COS_H = 0;
		this->Angle_SIN_H = 0;
		this->Angle_SIN_V = 0;
		this->Foot_x = -0.1234;
		this->Foot_y = -0.1234;
		this->Foot_z = -0.1234;
		this->Head_x = -0.1234;
		this->Head_y = -0.1234;
		this->Head_z = -0.1234;
		this->Speed_x = 0;
		this->Speed_y = 0;
		this->Speed_z = 0;
		this->Camp = 0;
		this->state = 0;
		this->HP = -100;
	}
};



struct Player GetEveryPlayer(Player Player, HMODULE ClientModuleAddress, HANDLE hProcess,int i) {


	long long NextAddress; long long NextNextAddress;

	ReadProcessMemory(hProcess, (void*)((long long)ClientModuleAddress+NEW_LIST_PLAYER_Offset), &NextAddress, 8, 0);

	ReadProcessMemory(hProcess, (void*)(NextAddress+(i*0x8)), &NextNextAddress, 8, 0);

	ReadProcessMemory(hProcess, (void*)(NextNextAddress + ANGLE_COS_Horizontal_Offset), &Player.Angle_COS_H, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + ANGLE_SIN_Horizontal_Offset), &Player.Angle_SIN_H, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + ANGLE_SIN_Vertical_Offset), &Player.Angle_SIN_V, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + ANGLE_Vertical_Offset), &Player.Angle_V, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + STATE_LIFE_Offset), &Player.state, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + CAMP_Offset), &Player.Camp, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + X_HEAD_Offset), &Player.Head_x, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + Y_HEAD_Offset), &Player.Head_y, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + Z_HEAD_Offset), &Player.Head_z, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + X_FOOT_Offset), &Player.Foot_x, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + Y_FOOT_Offset), &Player.Foot_y, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + Z_FOOT_Offset), &Player.Foot_z, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + X_Speed_Offset), &Player.Speed_x, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + Y_Speed_Offset), &Player.Speed_y, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + Z_Speed_Offset), &Player.Speed_z, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + HP_Offset), &Player.HP, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextNextAddress + BulletsLeft_Offset), &Player.BulletsLeft, 4, 0);
	return Player;
}


struct SLocalPlayer GetLocalPlayer(SLocalPlayer LocalPlayer, LPVOID Localplayer_Address, HANDLE hProcess) {

	long long NextAddress;

	ReadProcessMemory(hProcess, (void*)(Localplayer_Address), &NextAddress, 8, 0);

	ReadProcessMemory(hProcess, (void*)(NextAddress + ANGLE_Horizontal_Offset), &LocalPlayer.Angle_H, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextAddress + ANGLE_Vertical_Offset), &LocalPlayer.Angle_V, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextAddress + CAMP_Offset), &LocalPlayer.Camp, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextAddress + X_HEAD_Offset), &LocalPlayer.Head_x, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextAddress + Y_HEAD_Offset), &LocalPlayer.Head_y, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextAddress + Z_HEAD_Offset), &LocalPlayer.Head_z, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextAddress + X_FOOT_Offset), &LocalPlayer.Foot_x, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextAddress + Y_FOOT_Offset), &LocalPlayer.Foot_y, 4, 0);
	ReadProcessMemory(hProcess, (void*)(NextAddress + Z_FOOT_Offset), &LocalPlayer.Foot_z, 4, 0);

	long long NextAddress_Sensitivity_Mouse;

	ReadProcessMemory(hProcess, (void*)(Localplayer_Address), &NextAddress_Sensitivity_Mouse, 8, 0);
	ReadProcessMemory(hProcess, (void*)(NextAddress + Sensitivity_Mouse_Second_Offset), &LocalPlayer.Sensitivity_Mouse, 4, 0);

	return LocalPlayer;
}


int index_Player_LowestHP = 0; int i;
int GetPlayer_LowestHP(Player EnemyArray[], int EnemyNum) {

	if (EnemyNum > 0) {
		index_Player_LowestHP = 0;
		for (i = 0; i < EnemyNum; i++) {
			if (EnemyArray[index_Player_LowestHP].HP > EnemyArray[i].HP) {
				index_Player_LowestHP = i;
			}
		}
		return index_Player_LowestHP;
	}
	return -1;
};



long long GetEveryPlayerOffset(int i) {
	return (LIST_PLAYER_Offset + ((i) * (0x8)));
}

int index_Player_LowestDistance = 0;
int GetPlayer_LowestDistance(Player Array[], int Num, SLocalPlayer LocalPlayer,DWORD Way) {
	switch (Way)
	{
	case AimAtTheAll: {
		if (Num > 0) {
			index_Player_LowestDistance = 0;
			for (i = 0; i < Num; i++) {
				if (Array[index_Player_LowestDistance].distance > Array[i].distance) {
					index_Player_LowestDistance = i;
				}
			}
			return index_Player_LowestDistance;
		}
		break;
	}
	case AimAtTheEnemy: {
		if (Num > 0) {
			index_Player_LowestDistance = 0;
			BOOL A=0;
			int EnemyNum = 0;
			for (i = 0; i < Num; i++) {
				if (Array[i].Camp != LocalPlayer.Camp && A == FALSE) {
					A = TRUE;
					index_Player_LowestDistance = i;
				}
				if (Array[i].Camp != LocalPlayer.Camp&& Array[index_Player_LowestDistance].distance > Array[i].distance) {
					index_Player_LowestDistance = i;
				}
				if (Array[i].Camp != LocalPlayer.Camp) { EnemyNum++; };
				
			}
			IniTargetCoor.x = Array[index_Player_LowestDistance].Head_x;
			IniTargetCoor.y = Array[index_Player_LowestDistance].Head_y;
			IniTargetCoor.z = Array[index_Player_LowestDistance].Head_z;
			if (EnemyNum == 0) { index_Player_LowestDistance = -1; IniTargetCoor.x = 0; IniTargetCoor.y = 0;IniTargetCoor.z = 0;};
			
			return index_Player_LowestDistance;
		}
		break;
	}
	case AimAtTheAlly: {
		if (Num > 0) {
			index_Player_LowestDistance = 0;
			BOOL A = 0;
			int EnemyNum = -1;
			for (i = 0; i < Num; i++) {
				if (Array[i].Camp == LocalPlayer.Camp && A == FALSE) {
					A = TRUE;
					index_Player_LowestDistance = i;
				}
				if (Array[i].Camp == LocalPlayer.Camp && Array[index_Player_LowestDistance].distance > Array[i].distance) {
					index_Player_LowestDistance = i;
				}
				if (Array[i].Camp == LocalPlayer.Camp) { EnemyNum++; };

			}
			if (EnemyNum == -1) { index_Player_LowestDistance = -1; };
			return index_Player_LowestDistance;
		}
		break;
	}
	default:
		break;
	}
	return -1;
};

int index_Player_LowestAngle = 0;
Player Player_LowestAngle[19]; int Num_Player_LowestAngle = 0;
int GetPlayer_LowestAngle(Player Array[], int Num, SLocalPlayer LocalPlayer, DWORD Way) {
	switch (Way)
	{

	case AimAtTheAll: { 
		if (Num > 0) {
			index_Player_LowestAngle = 0;
			Num_Player_LowestAngle = 0;
			for (i = 0; i < Num; i++) {
				//float HANGLE = GetHAngle(LocalPlayer.Angle_COS_H, LocalPlayer.Angle_SIN_H, LocalPlayer.Head_x, LocalPlayer.Head_y, Array[i].Head_x, Array[i].Head_y);
				//float VANGLE = GetVAngle(LocalPlayer.Angle_COS_H, LocalPlayer.Angle_SIN_H, LocalPlayer.Angle_SIN_V, LocalPlayer.Head_x, LocalPlayer.Head_y, LocalPlayer.Head_z, Array[i].Head_x, Array[i].Head_y, Array[i].Head_z);
				//if (abs(std::tan((std::pow((std::pow(HANGLE, 2) + std::pow(HANGLE, 2)), 0.5)) * M_PI / 180.0)) * Array[i].distance< float(AutoAim::AutoAimSetting.Range) / 100 && abs(HANGLE) < 89) {
				//	Player_LowestAngle[Num_Player_LowestAngle] = Array[i];
				//	Player_LowestAngle[Num_Player_LowestAngle].Ini_Index = i;
				//	Num_Player_LowestAngle++;
				//}
			};
			if (Num_Player_LowestAngle > 0) { return Player_LowestAngle[GetPlayer_LowestDistance(Player_LowestAngle, Num_Player_LowestAngle, LocalPlayer, AimAtTheAll)].Ini_Index; };
		};
		return -1;
		break;
	}
	case AimAtTheEnemy: {
		if (Num > 0) {
			index_Player_LowestAngle = 0;
			int EnemyNum = 0;
			for (i = 0; i < Num; i++) {
				if (Array[i].Camp != LocalPlayer.Camp) {
					//float HANGLE = GetHAngle(LocalPlayer.Angle_COS_H, LocalPlayer.Angle_SIN_H, LocalPlayer.Head_x, LocalPlayer.Head_y, Array[i].Head_x, Array[i].Head_y);
					//float VANGLE = GetVAngle(LocalPlayer.Angle_COS_H, LocalPlayer.Angle_SIN_H, LocalPlayer.Angle_SIN_V, LocalPlayer.Head_x, LocalPlayer.Head_y, LocalPlayer.Head_z, Array[i].Head_x, Array[i].Head_y, Array[i].Head_z);
					//if (abs(std::tan((std::pow((std::pow(HANGLE, 2) + std::pow(HANGLE, 2)), 0.5))* M_PI/180.0))* Array[i].distance< float(AutoAim::AutoAimSetting.Range)/100&& abs(HANGLE)<89) {
					//	EnemyNum++;
					//	index_Player_LowestAngle = i;
					//	return index_Player_LowestAngle;
						
					//};
				};
			};
			if (EnemyNum == 0) { return -1; };
			return index_Player_LowestAngle;
		};

		break;
	};
	case AimAtTheAlly: {
		if (Num > 0) {
			index_Player_LowestAngle = 0;
			int AllyNum = 0;
			for (i = 0; i < Num; i++) {
				if (Array[i].Camp == LocalPlayer.Camp) {
					//float HANGLE = GetHAngle(LocalPlayer.Angle_COS_H, LocalPlayer.Angle_SIN_H, LocalPlayer.Head_x, LocalPlayer.Head_y, Array[i].Head_x, Array[i].Head_y);
					//float VANGLE = GetVAngle(LocalPlayer.Angle_COS_H, LocalPlayer.Angle_SIN_H, LocalPlayer.Angle_SIN_V, LocalPlayer.Head_x, LocalPlayer.Head_y, LocalPlayer.Head_z, Array[i].Head_x, Array[i].Head_y, Array[i].Head_z );
					//if (abs(std::tan((std::pow((std::pow(HANGLE, 2) + std::pow(HANGLE, 2)), 0.5)) * M_PI / 180.0)) * Array[i].distance< float(AutoAim::AutoAimSetting.Range) / 100 && abs(HANGLE) < 89) {
					//	AllyNum++;
					//	index_Player_LowestAngle = i;
						return index_Player_LowestAngle;

					//};
				};
			};
			if (AllyNum == 0) { return -1; };
			return index_Player_LowestAngle;
		};

		break;
	};
	default: {
		break;
	}	
	};
}