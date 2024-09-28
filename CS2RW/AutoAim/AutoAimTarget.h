#pragma once
#include <iostream>
#include <cmath>
#define MATH_PI 3.1415926
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
            this->X_Target = -1.1111;
            this->Y_Target = -1.1111;
            this->Z_Target = -1.1111;
            this->HorizontalAngle = -1.1111;
            this->VerticalAngle = -1.1111;
        };
    };

    float dX, dY, dZ, dL = 0; double dHorizontalAngle, TargetHorizontalAngle , TargetVerticalAngle = 0; long long NextAddress; long long NextNextAddress;
    void UpTargetData(Target& IniTarget,  int i)  {

        ReadProcessMemory(GameProcess, (void*)(Localplayer_Address), &NextAddress, 8, 0);
        ReadProcessMemory(GameProcess, (void*)(NextAddress + X_HEAD_Offset), &IniTarget.X_Self_Head, 4, 0);
        ReadProcessMemory(GameProcess, (void*)(NextAddress + Y_HEAD_Offset), &IniTarget.Y_Self_Head, 4, 0);
        ReadProcessMemory(GameProcess, (void*)(NextAddress + Z_HEAD_Offset), &IniTarget.Z_Self_Head, 4, 0);
        //ReadProcessMemory(GameProcess, (void*)((long long)Engine2ModuleAddress + Engine2_View.HorizontalAngle), &IniTarget.SelfHorizontalAngle, 4, 0);
        //ReadProcessMemory(GameProcess, (void*)((long long)Engine2ModuleAddress + Engine2_View.VerticalAngle), &IniTarget.SelfVerticalAngle, 4, 0);
        if (1) {
            ReadProcessMemory(GameProcess, (void*)(NextAddress + ANGLE_Horizontal_Offset), &IniTarget.SelfHorizontalAngle, 4, 0);
            ReadProcessMemory(GameProcess, (void*)(NextAddress + ANGLE_Vertical_Offset), &IniTarget.SelfVerticalAngle, 4, 0);
        };
        ReadProcessMemory(GameProcess, (void*)((long long)ClientModuleAddress + NEW_LIST_PLAYER_Offset), &NextAddress, 8, 0);
        ReadProcessMemory(GameProcess, (void*)(NextAddress + (i * 0x8)), &NextNextAddress, 8, 0);
        ReadProcessMemory(GameProcess, (void*)(NextNextAddress + X_HEAD_Offset), &IniTarget.X_Target, 4, 0);
        ReadProcessMemory(GameProcess, (void*)(NextNextAddress + Y_HEAD_Offset), &IniTarget.Y_Target, 4, 0);
        ReadProcessMemory(GameProcess, (void*)(NextNextAddress + Z_HEAD_Offset), &IniTarget.Z_Target, 4, 0);


        dX = IniTarget.X_Target - IniTarget.X_Self_Head; dY = IniTarget.Y_Target - IniTarget.Y_Self_Head; dZ = IniTarget.Z_Self_Head - IniTarget.Z_Target; dL = pow((pow(dX, 2) + pow(dY, 2)), 0.5);

        TargetHorizontalAngle = (std::atan2(dY, dX) * 180.0 / MATH_PI);dHorizontalAngle = IniTarget.SelfHorizontalAngle - TargetHorizontalAngle;if (dHorizontalAngle > 180) { dHorizontalAngle -= 360; }else if (dHorizontalAngle < -180) { dHorizontalAngle += 360; };

        IniTarget.HorizontalAngle = dHorizontalAngle;

        TargetVerticalAngle = (std::atan2(dZ, dL) * 180.0 / MATH_PI);

        IniTarget.VerticalAngle= TargetVerticalAngle- IniTarget.SelfVerticalAngle;

    };
    
};

AutoAim::Target IniTarget;
