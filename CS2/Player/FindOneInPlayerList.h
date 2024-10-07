#pragma once

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





int index_Player_LowestDistance = 0;
int GetPlayer_LowestDistance(Player Array[], int Num, SLocalPlayer LocalPlayer, DWORD Way) {
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
			BOOL A = 0;
			int EnemyNum = 0;
			for (i = 0; i < Num; i++) {
				if (Array[i].TeamTag != LocalPlayer.TeamTag && A == FALSE) {
					A = TRUE;
					index_Player_LowestDistance = i;
				}
				if (Array[i].TeamTag != LocalPlayer.TeamTag && Array[index_Player_LowestDistance].distance > Array[i].distance) {
					index_Player_LowestDistance = i;
				}
				if (Array[i].TeamTag != LocalPlayer.TeamTag) { EnemyNum++; };

			}

			//AutoAim::UpAngleData(IniSelfVeiwAngleTarget, Localplayer.Angle_H, Localplayer.Angle_V, Localplayer.Head_x, Localplayer.Head_y, Localplayer.Head_z, IniTargetCoor.x, IniTargetCoor.y, IniTargetCoor.z);
			if (EnemyNum == 0) { index_Player_LowestDistance = -1; IniTarget.HorizontalAngle = 0; IniTarget.VerticalAngle = 0; };

			return Array[index_Player_LowestDistance].Ini_Index;
		}
		break;
	}
	case AimAtTheAlly: {
		if (Num > 0) {
			index_Player_LowestDistance = 0;
			BOOL A = 0;
			int EnemyNum = -1;
			for (i = 0; i < Num; i++) {
				if (Array[i].TeamTag == LocalPlayer.TeamTag && A == FALSE) {
					A = TRUE;
					index_Player_LowestDistance = i;
				}
				if (Array[i].TeamTag == LocalPlayer.TeamTag && Array[index_Player_LowestDistance].distance > Array[i].distance) {
					index_Player_LowestDistance = i;
				}
				if (Array[i].TeamTag == LocalPlayer.TeamTag) { EnemyNum++; };

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
				if (Array[i].TeamTag != LocalPlayer.TeamTag) {
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
				if (Array[i].TeamTag == LocalPlayer.TeamTag) {
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