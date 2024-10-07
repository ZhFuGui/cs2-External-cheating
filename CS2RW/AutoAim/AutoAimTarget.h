#pragma once
#include <iostream>
#include <cmath>
#define MATH_PI 3.141592653589793
namespace AutoAim {
    struct Target
    {
        float X_Target;
        float Y_Target;
        float Z_Target;

        float X_Self_Head;
        float Y_Self_Head;
        float Z_Self_Head;

        float SelfHorizontalAngle;
        float SelfVerticalAngle;

        double HorizontalAngle;
        double VerticalAngle;
        Target() {
            this->X_Target = 5.0316;
            this->Y_Target = -1.1111;
            this->Z_Target = -1.1111;
            this->HorizontalAngle = -1.1111;
            this->VerticalAngle = -1.1111;
        };
    };

    float dX, dY, dZ, dL = 0; double dHorizontalAngle, TargetHorizontalAngle , TargetVerticalAngle = 0; long long NextAddress_UpTargetData; long long NextNextAddress_UpTargetData;
    void UpTargetData(Target& IniTarget,  int i)  {
        
        ReadProcessMemory(GameProcessInfo.GameProcess, (LPVOID)((uintptr_t)ModuleInfo.ClientModuleAddress+Offset::ClientDLL::LocalPlayer::Address), &NextAddress_UpTargetData, 8, 0);
        ReadProcessMemory(GameProcessInfo.GameProcess, (LPVOID)(NextAddress_UpTargetData + Offset::ClientDLL::Player::X_Head), &IniTarget.X_Self_Head, 4, 0);
        ReadProcessMemory(GameProcessInfo.GameProcess, (LPVOID)(NextAddress_UpTargetData + Offset::ClientDLL::Player::Y_Head), &IniTarget.Y_Self_Head, 4, 0);
        ReadProcessMemory(GameProcessInfo.GameProcess, (LPVOID)(NextAddress_UpTargetData + Offset::ClientDLL::Player::Z_Head), &IniTarget.Z_Self_Head, 4, 0);
        ReadProcessMemory(GameProcessInfo.GameProcess, (LPVOID)((uintptr_t)ModuleInfo.Engine2ModuleAddress + Offset::Engine2DLL::ViewAngles::HorizontalAngle), &IniTarget.SelfHorizontalAngle, 4, 0);
        ReadProcessMemory(GameProcessInfo.GameProcess, (LPVOID)((uintptr_t)ModuleInfo.Engine2ModuleAddress + Offset::Engine2DLL::ViewAngles::VerticalAngle), &IniTarget.SelfVerticalAngle, 4, 0);
        ReadProcessMemory(GameProcessInfo.GameProcess, (LPVOID)((uintptr_t)ModuleInfo.ClientModuleAddress + Offset::ClientDLL::PlayerList::Address), &NextAddress_UpTargetData, 8, 0);
        ReadProcessMemory(GameProcessInfo.GameProcess, (LPVOID)(NextAddress_UpTargetData + (i * 0x8)), &NextNextAddress_UpTargetData, 8, 0);
        ReadProcessMemory(GameProcessInfo.GameProcess, (LPVOID)(NextNextAddress_UpTargetData + Offset::ClientDLL::Player::X_Head), &IniTarget.X_Target, 4, 0);
        ReadProcessMemory(GameProcessInfo.GameProcess, (LPVOID)(NextNextAddress_UpTargetData + Offset::ClientDLL::Player::Y_Head), &IniTarget.Y_Target, 4, 0);
        ReadProcessMemory(GameProcessInfo.GameProcess, (LPVOID)(NextNextAddress_UpTargetData + Offset::ClientDLL::Player::Z_Head), &IniTarget.Z_Target, 4, 0);


        dX = IniTarget.X_Target - IniTarget.X_Self_Head; dY = IniTarget.Y_Target - IniTarget.Y_Self_Head; dZ = IniTarget.Z_Self_Head - IniTarget.Z_Target; dL = pow((pow(dX, 2) + pow(dY, 2)), 0.5);

        TargetHorizontalAngle = (std::atan2(dY, dX) * 180.0 / MATH_PI);dHorizontalAngle = IniTarget.SelfHorizontalAngle - TargetHorizontalAngle;if (dHorizontalAngle > 180) { dHorizontalAngle -= 360; }else if (dHorizontalAngle < -180) { dHorizontalAngle += 360; };

        IniTarget.HorizontalAngle = dHorizontalAngle;

        TargetVerticalAngle = (std::atan2(dZ, dL) * 180.0 / MATH_PI);

        IniTarget.VerticalAngle= TargetVerticalAngle- IniTarget.SelfVerticalAngle;

    };
    
};

AutoAim::Target IniTarget;
