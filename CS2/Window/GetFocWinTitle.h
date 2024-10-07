#include <Windows.h>
#include <iostream>


std::string GetFocWinTitle()
{
	HWND HwndForegroundWindow = NULL;

	LPWSTR lpwstr = new wchar_t[MAX_PATH];

	HwndForegroundWindow = GetForegroundWindow();

	if (NULL == HwndForegroundWindow)
	{
		HwndForegroundWindow = GetDesktopWindow();
	}

	GetWindowTextW(HwndForegroundWindow, lpwstr, MAX_PATH / 2);

	return(LPWSTR2string(lpwstr));
}