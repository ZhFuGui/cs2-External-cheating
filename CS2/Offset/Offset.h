#pragma once
//变化偏移值

namespace Offset {
	namespace ClientDLL {
		namespace Xray {
			constexpr uintptr_t Address = 0x842EA0;
		}
		namespace GameOptions{
			constexpr uintptr_t BasicOffset = 0x40;
			namespace Radar {
				constexpr uintptr_t MapScalingFactor = 0x019BD3B8;
				constexpr uintptr_t HUDSize = 0x019B95F8;
				constexpr uintptr_t isRotate = 0x019BD3A8;
				constexpr uintptr_t	isPlayerCentered = 0x019BD3D8;
			}
			namespace Mouse {
				constexpr uintptr_t Sensitivitydefault = 0x019B2B38;
				constexpr uintptr_t SensitivityZoomed = 0x019ACEF0;
			}
		};
		namespace Player
		{
			constexpr uintptr_t  MaxHP = 0x340;
			constexpr uintptr_t  HP = 0x344;
			constexpr uintptr_t  LifeState = 0X348;
			constexpr uintptr_t  TeamTag = 0x3E3;
			constexpr uintptr_t  Speed_X = 0x3F0;
			constexpr uintptr_t  Speed_Y = 0x3F4;
			constexpr uintptr_t  Speed_Z = 0x3F8;
			constexpr uintptr_t JUMP = 0x450;
			constexpr uintptr_t C4beingPlanted = 0xB44;
			constexpr uintptr_t  Slope = 0XD54;
			constexpr uintptr_t  X_Feet = 0XD58;
			constexpr uintptr_t  Y_Feet = 0XD5C;
			constexpr uintptr_t  Z_Feet = 0XD60;
			constexpr uintptr_t ANGLE_Vertical = 0X119C;
			constexpr uintptr_t ANGLE_Horizontal = 0X11A0;
			constexpr uintptr_t  X_Head = 0x12D4;
			constexpr uintptr_t  Y_Head = 0x12D8;
			constexpr uintptr_t  Z_Head = 0x12DC;
			constexpr uintptr_t COS_HorizontalAngle = 0X12E0;
			constexpr uintptr_t SIN_HorizontalAngle = 0X12E4;
			constexpr uintptr_t SIN_VerticalAngle = 0X12E8;
			constexpr uintptr_t  SquatDown = 0X1BD0;
			constexpr uintptr_t BulletsLeft = 0x44F8;
			constexpr uintptr_t IsPlayerTag1 = 0x460;//256
			constexpr uintptr_t IsPlayerTag2 = 0x52C;//65536
			constexpr uintptr_t IsPlayerTag3 = 0xB14;//8
			constexpr uintptr_t IsPlayerTag4 = 0xD8C;//521
		};
		namespace LocalPlayer{
			constexpr uintptr_t Address = 0x18220C8;
		};
		namespace PlayerList{
			constexpr uintptr_t Address = 0x017CEAE8;
		};
		namespace ViewAngles
		{
			constexpr uintptr_t VerticalAngle = 0x19C5958;
			constexpr uintptr_t HorizontalAngle = 0x19C595C;
		};
		namespace GameInfo {
			constexpr uintptr_t MapInfo = 0x17727B8;
		}
	};
	namespace ServerDLL {
		namespace GameChessInfo
		{
			constexpr uintptr_t AllPlayerNum = 0x138FE54;
		};
	};
	namespace Engine2DLL {//正统视角
		namespace ViewAngles
		{
			constexpr uintptr_t VerticalAngle = 0x5F1408;
			constexpr uintptr_t HorizontalAngle = 0x5F140C;
		};
	};
	namespace SDL3DLL {
		namespace IfInGameView
		{
			constexpr uintptr_t Address = 0x01E6F88;
		};
	};
	namespace MatchmakingDLL {
		namespace Player
		{
			constexpr int a = 0;
		};
	};
	namespace SteamaudioDLL {
		namespace GameInfo
		{
			constexpr uintptr_t InGameChess = 0x213F48;
		};
	};
};

