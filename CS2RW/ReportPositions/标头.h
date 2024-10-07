#pragma once
#include<Windows.h>
void SetWindowSize(HWND g_HWND, int ReportPositionWidth, int ReportPositionHeight) {
	SetWindowPos(g_HWND, NULL, 0, 0, ReportPositionWidth, ReportPositionHeight, SWP_NOZORDER | SWP_NOMOVE);
};