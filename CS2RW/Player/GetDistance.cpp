#include "GetDistance.h"
int GetDistance_2D_M_0(float x1, float x2, float y1, float y2) {
	int distance = (pow((pow(((x1 - x2) / 100), 2) + pow(((y1 - y2) / 100), 2)), 0.5));
	return distance;
}
float GetDistance_2D_M_4(float x1, float x2, float y1, float y2) {
	float distance = (pow((pow(((x1 - x2) / 100), 2) + pow(((y1 - y2) / 100), 2)), 0.5));
	return distance;
}
float GetDistance_3D_M_4(float x1, float x2, float y1, float y2, float z1, float z2) {
	float distance = (pow((pow(((x1 - x2) / 100), 2) + pow(((y1 - y2) / 100), 2)+ pow(((z1 - z2) / 100), 2)), 0.5));
	return distance;
}

