#pragma once
#include <iostream>
#include <cmath>

namespace AutoAim {
    struct TargetCoor
    {
        float x;
        float y;
        float z;
        TargetCoor() {
            this->x = -1.1111;
            this->y = -1.1111;
            this->z = -1.1111;
        };
    };
    struct SelfVeiwAngleTarget
    {
        double HorizontalAngle;
        double VerticalAngle;
        SelfVeiwAngleTarget() {
            this->HorizontalAngle = -1.1111;
            this->VerticalAngle = -1.1111;
        };
    };

    float dX, dY, dZ, dL = 0; double TargetHorizontalAngle, dHorizontalAngle, TargetVerticalAngle = 0;
    void UpAngleData(SelfVeiwAngleTarget& IniSelfVeiwAngleTarget, float &SelfHorizontalAngle, float &SelfVerticalAngle, float &X_Self_Head, float &Y_Self_Head, float &Z_Self_Head, float X_Target, float Y_Target, float Z_Target)  {

        dX = X_Target - X_Self_Head; dY = Y_Target - Y_Self_Head; dZ = Z_Self_Head - Z_Target; dL = pow((pow(dX, 2) + pow(dY, 2)), 0.5);

        TargetHorizontalAngle = (std::atan2(dY, dX) * 180.0 / 3.14);dHorizontalAngle = SelfHorizontalAngle - TargetHorizontalAngle;if (dHorizontalAngle > 180) { dHorizontalAngle -= 360; }else if (dHorizontalAngle < -180) { dHorizontalAngle += 360; };

        IniSelfVeiwAngleTarget.HorizontalAngle = dHorizontalAngle;

        TargetVerticalAngle = (std::atan2(dZ, dL) * 180.0 / 3.14);

        IniSelfVeiwAngleTarget.VerticalAngle=  TargetVerticalAngle- SelfVerticalAngle;
    };
};
AutoAim::TargetCoor IniTargetCoor;
AutoAim::SelfVeiwAngleTarget IniSelfVeiwAngleTarget;