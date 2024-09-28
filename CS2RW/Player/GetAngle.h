#pragma once
#include <iostream>
#include <cmath>
#include <vector>
const double M_PI = 3.14159265358979323846;

float dZ; float Angle_Enemy2I; float Angle_View; float Final_dAngle; float dX; float dY; float Degree_Angle_Enemy2I; float Degree_Angle_View; float dAngle;

float GetHAngle(float angle_COS_H, float angle_SIN_H, float X_my_Head, float Y_my_Head, float X_Enemy_Head, float Y_Enemy_Head) {

	dX = X_Enemy_Head - X_my_Head;
	dY = Y_Enemy_Head - Y_my_Head;


	if (std::atan2(dY, dX) < 0) {
		Angle_Enemy2I = 2 * M_PI + std::atan2(dY, dX);
	}
	else {
		Angle_Enemy2I = std::atan2(dY, dX);
	}

	if (std::atan2(angle_SIN_H, angle_COS_H) < 0) {
		Angle_View = 2 * M_PI + std::atan2(angle_SIN_H, angle_COS_H);
	}
	else {
		Angle_View = std::atan2(angle_SIN_H, angle_COS_H);
	}

	Degree_Angle_Enemy2I = Angle_Enemy2I * 180.0 / M_PI;
	Degree_Angle_View = Angle_View * 180.0 / M_PI;

	dAngle = Degree_Angle_View - Degree_Angle_Enemy2I;

	if (dAngle > 180) {
		Final_dAngle = -360 + dAngle;
	}
	else if (dAngle < -180) {
		Final_dAngle = 360 + dAngle;
	}
	else {
		Final_dAngle = dAngle;
	}

	return Final_dAngle;
}
float dL;
float GetVAngle(float angle_COS_H, float angle_SIN_H, float angle_V, float X_my_Head, float Y_my_Head, float Z_my_Head, float X_Enemy_Head, float Y_Enemy_Head, float Z_Enemy_Head) {
	float A;

	dZ = Z_Enemy_Head - Z_my_Head;

	dX = X_Enemy_Head - X_my_Head;

	dY = Y_Enemy_Head - Y_my_Head;

	dL = pow((pow(dX, 2) + pow(dY, 2)), 0.5);

	A = std::atan2(dZ, dL);

	float Angle_Enemy2I_V = A * 180.0 / M_PI;

	return -angle_V - Angle_Enemy2I_V;
}