//不变配置类型文件
#include "Define/TypeDef.h"
#include "Global/GlobalV.h"
#include "KeyBoard\VK_Value.h"
#include "SoundUtil\AudioTypeRegistry.h"
#include "SoundUtil/SoundProducer.h"
#include "KeyBoard\GetInput.h"
#include "Define/Definition.h"
#include "Offset/Offset.h"
#include "Global/CheckF.h"
#include "StringUtil/UserDocumentStr.h"
//普通文件
#include <Windows.h>
#include <iostream>
#include <CommCtrl.h>
#include "resource.h"
//工具类

#include "ReportPositions\标头.h"
#include "StringUtil/StringTypesFlow.h"
#include "StringUtil/RandomClan.h"
#include "Time/Time.h"
#include "Window/GetProcessPidByName.h"
#include "Window/GetModule.h"
#include "Window/VersionCheck.h"
#include "Window/GetFocWinTitle.h"
//优先交互

//交互类
#include "ESP/ESP.h"
#include "AutoAim/AutoAimSetting.h"
#include "AutoAim/AutoAimTarget.h"
#include "ESP/Xray.h"
#include "GameInfo/GetGameStatus.h"
#include "Player/LocalPlayer.h"
#include "Player/GetPlayerList.h"
#include "Player/GetDistance.h"
#include "Player/GetPosition.h"
#include "Player/FindOneInPlayerList.h"
#include "GameInfo/GameOptions.h"
//
#include "Main.h"
#include "Thread\ThreadFun.h"
LRESULT CALLBACK Wndproc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	GameProcessInfo.g_HWND = hwnd;

	static HINSTANCE hInstance = GetModuleHandleW(NULL);

	GameProcessInfo.g_HINSTANCE = hInstance;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		//创造强制关闭功能
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KillTheProsess, NULL, 0, 0);
		//接受输入
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GetKeyBoardInput, NULL, 0, 0);
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		PostQuitMessage(0);
		break;
	}
	case WM_HELP:
	{};
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);


		SetTextColor(hdc, RGB(255, 255, 255));


		SetBkMode(hdc, TRANSPARENT);


		DrawText(hdc, L"1.0.0.01", -1, &ps.rcPaint, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

		EndPaint(hwnd, &ps);

		break;
	}
	case WM_COMMAND:
	{
		DWORD ControlId = DWORD(wParam);
		if (ControlId == WM_VERSION_UNUSEFUL) {
			int result_off = MessageBoxW(0, L"当前版本已无效，请联系开发者更新！", L"警告", IDOK | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_APPLMODAL | MB_SETFOREGROUND);
			SendMessageW(GameProcessInfo.g_HWND, WM_CLOSE, 0, 0);
		}

		break;
	};
	case WM_KEYUP+FALSE:
	{
		switch (wParam)
		{
		case VK_INSERT: {
			if (CheckGaming()) {
				MessageBoxW(hwnd, L"当前状态：程序运行正常", L"提示", MB_APPLMODAL);
			}
			else {
				MessageBoxW(hwnd, L"未检测到进程cs2.exe", L"错误", MB_APPLMODAL);
			}
			break;
		};
		case VK_HOME: {
			MessageBoxW(0, HOME, L"欢迎使用", MB_OK | MB_ICONASTERISK);
			break;
		}
		case VK_F1: {
			UnShow_Xray(ModuleInfo.ClientModuleAddress, GameProcessInfo.GameProcess);
		}
		default:
			break;
		};
		break;
	};
	case WM_KEYUP+TRUE:
	{
		switch (wParam)
		{
		case VK_INSERT: {
			if (CheckGaming()) {
				MessageBoxW(hwnd, L"当前状态：程序运行正常", L"提示", MB_APPLMODAL);
			}
			else {
				MessageBoxW(hwnd, L"未检测到进程cs2.exe", L"错误", MB_APPLMODAL);
			}
			break;
		};
		case VK_HOME: {
			MessageBoxW(0, HOME, L"欢迎使用", MB_OK | MB_ICONASTERISK);
			break;
		}
		case VK_F1: {
			Show_Xray(ModuleInfo.ClientModuleAddress ,GameProcessInfo.GameProcess);
		}
		default:
			break;
		};
		break;
	};
	};

	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
};

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
{

	WNDCLASSW MainWndClass = { 0 };
	MainWndClass.lpszClassName = L"ReverseCsWnd";
	MainWndClass.lpfnWndProc = Wndproc;
	MainWndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);;
	MainWndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCEW(IDI_ICON1));

	RegisterClassW(&MainWndClass);

	MessageBoxW(0, Welcome, L"欢迎使用！", MB_HELP | MB_ICONASTERISK);

	HWND MyWindow = CreateWindowExW(
		WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT,
		MainWndClass.lpszClassName,
		RandomWstring(NULL, RSS_CHINESE, 6, 32).c_str(),
		WS_POPUP,
		10, 400, 5, 5,
		NULL,
		NULL,
		hInstance,
		0
	);

	SetLayeredWindowAttributes(GameProcessInfo.g_HWND, RGB(255, 255, 255), 128, LWA_ALPHA);

	ShowWindow(MyWindow, nShowCmd);

	UpdateWindow(GameProcessInfo.g_HWND);

	SetWindowPos(GameProcessInfo.g_HWND, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GetExeStatus, NULL, 0, 0);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GetGameModule, NULL, 0, 0);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GetGameModelStatus, NULL, 0, 0);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GetAutoAimTime, NULL, 0, 0);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GetLocalPlayerThread, NULL, 0, 0);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GetPlayerListThread, NULL, 0, 0);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReportPositions, NULL, 0, 0);
	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CreateESP, NULL, 0, 0);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AutoAim_GetWhoBeAimed, NULL, 0, 0);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AutoAim_AimAction, NULL, 0, 0);

	MSG msg = { 0 };

	while (GetMessageW(&msg, 0, 0, 0))
	{
		DispatchMessageW(&msg);
	};

	return 0;
};