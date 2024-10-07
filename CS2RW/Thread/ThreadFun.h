#pragma once
#include <Windows.h>
//关闭当前程序
DWORD WINAPI KillTheProsess() noexcept {//10%
	while (TRUE) {
		PauseMs(10);
		if (GetAsyncKeyState(VK_END) & 0x8000) {
			HANDLE CurrentProcess = GetCurrentProcess();
			if (CurrentProcess != NULL) {
				if (!TerminateProcess(CurrentProcess, 0)) { // 设置退出代码为0表示正常结束
					DWORD exitCode = GetLastError(); // 获取错误码
					CloseHandle(CurrentProcess);
				}
				else {
					CloseHandle(CurrentProcess);
				}
			}
		}
	}
};
//获取游戏进程状态(不停)
DWORD WINAPI GetExeStatus() noexcept{ //5%
	while (1) {
		PauseMs(10);
		GameProcessInfo.GamePid = GetProcessPidByName(L"cs2.exe"); if (!GameProcessInfo.GamePid) { ReSetVariableValue(); continue; };
		GameProcessInfo.GameProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GameProcessInfo.GamePid); if (!GameProcessInfo.GameProcess) { continue; };
		GetModuleFileNameExA(GameProcessInfo.GameProcess, NULL, GameProcessInfo.GameFile, MAX_PATH);
		if (!VersionCheckFun()) {
			GameStatusInfo.VersionUseful = FALSE;
			int result_off = MessageBoxW(0, L"当前版本已无效，待更新", L"警告", MB_HELP | MB_ICONEXCLAMATION | MB_DEFBUTTON1 | MB_APPLMODAL| MB_SETFOREGROUND);
			if (result_off == IDOK) { SendMessageW(GameProcessInfo.g_HWND, WM_COMMAND, 0x404, 0); };
		};
		PauseMs(800);
	}
};
//获取游戏必备环境（不停）
DWORD WINAPI GetGameModule() noexcept{   //13%
	while (TRUE) {
		PauseMs(10);
		if (CheckGaming()) {
			ModuleInfo.ClientModuleAddress = GetModule(GameProcessInfo.GameProcess, "client.dll");
			ModuleInfo.Engine2ModuleAddress = GetModule(GameProcessInfo.GameProcess, "engine2.dll");
			ModuleInfo.MatchmakingModuleAddress = GetModule(GameProcessInfo.GameProcess, "matchmaking.dll");
			ModuleInfo.ServerModuleAddress = GetModule(GameProcessInfo.GameProcess, "server.dll");
			ModuleInfo.SDL3ModuleAddress = GetModule(GameProcessInfo.GameProcess, "SDL3.dll");
			ModuleInfo.SteamaudioModuleAddress = GetModule(GameProcessInfo.GameProcess, "steamaudio.dll");
		}
		else {
			ModuleInfo.ClientModuleAddress = 0;
			ModuleInfo.Engine2ModuleAddress = 0;
			ModuleInfo.MatchmakingModuleAddress = 0;
			ModuleInfo.ServerModuleAddress = 0;
			ModuleInfo.SDL3ModuleAddress = 0;
			ModuleInfo.SteamaudioModuleAddress = 0;
		};
		PauseMs(200);
	};
};
//获取游戏模式状态（不停）
DWORD WINAPI GetGameModelStatus() noexcept{//跑满占5%
	while (TRUE) {
		PauseMs(10);
		if (!CheckGaming() || !CheckMoudle()) { continue; };
		GetBasicGameStatus(GameStatusInfo, ModuleInfo.ClientModuleAddress, GameProcessInfo.GameProcess);
		if (GameStatusInfo.InGameChess) { IfGameScreen(GameStatusInfo, ModuleInfo.SDL3ModuleAddress, GameProcessInfo.GameProcess); GetAllPlayerNum(GameStatusInfo, ModuleInfo.ServerModuleAddress , GameProcessInfo.GameProcess);}else {GameStatusInfo.InGameScreen = FALSE; GameStatusInfo.AllPlayerNum = 0;};
	};
};
//自瞄时机进程
DWORD WINAPI GetAutoAimTime() {//3%
	while (TRUE) {
		PauseMs(10);
		FocWinTitle = GetFocWinTitle(); if (FocWinTitle == "反恐精英：全球攻势" || FocWinTitle == "Counter-Strike 2") { IFCS2FocalPoint = TRUE; }else { IFCS2FocalPoint = FALSE; };
		if (IFCS2FocalPoint && GameStatusInfo.InGameScreen) { AimBotTime = TRUE; }else { AimBotTime = FALSE; };
	}
};
//获取自身信息
DWORD WINAPI GetLocalPlayerThread() noexcept{
	while(TRUE){
		PauseMs(10);
		//判断函数
		if (!CheckGaming() || !CheckMoudle() || !GameStatusInfo.InGameChess) { continue; };
		GetLocalPlayer(Localplayer, ModuleInfo.ClientModuleAddress, GameProcessInfo.GameProcess);
	}
}
//如果是进行游戏则获取人物队列
_ui CNum = 0; _ui CTNum = 0; _ui ListIndex=0;
DWORD WINAPI GetPlayerListThread() noexcept{
	while (TRUE) {
		PauseMs(10);
		//在游戏内才做
		if (!CheckGaming() || !CheckMoudle() || !GameStatusInfo.InGameChess) { continue; };
		ListIndex = 0; CNum = 0; CTNum = 0;
		for (int i = 0; i < GameStatusInfo.AllPlayerNum * 2; i++) {
			//获取每个Player信息
			GetEveryPlayer(TemporaryPlayer, ModuleInfo.ClientModuleAddress, GameProcessInfo.GameProcess, i);
			TemporaryPlayer.distance = GetDistance_3D_M_4(TemporaryPlayer.X_Feet, Localplayer.X_Feet, TemporaryPlayer.Y_Feet, Localplayer.Y_Feet, TemporaryPlayer.Z_Feet, Localplayer.Z_Feet);
			//如果满足条件就加入人物列表
			if (TemporaryPlayer.LifeState == 256 && TemporaryPlayer.HP > 0 && TemporaryPlayer.HP <= 100 && TemporaryPlayer.distance > 0.2) {
				AllPlayerArray[ListIndex] = TemporaryPlayer;
				ListIndex += 1;
				if (TemporaryPlayer.TeamTag == 2) { CTNum += 1; }
				else if (TemporaryPlayer.TeamTag == 3) { CNum += 1; };
			};
		};
		GameStatusInfo.CTNum_Alive = CTNum; GameStatusInfo.CNum_Alive = CNum;
	};
};
//报点进程
_ui Index_EnemyAlive=0;
DWORD WINAPI ReportPositions() {//10%
	while (1)
	{
		PauseMs(10);
		//如果开始报点且不存在容器那么创造new_WINDOWS容器
		Enemy01_ID_Static_hwnd = CreateWindowW(WC_STATICW, L"敌人1", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 60, 0, 60, 40, GameProcessInfo.g_HWND, (HMENU)0x2101, GameProcessInfo.g_HINSTANCE, 0);
		Enemy02_ID_Static_hwnd = CreateWindowW(WC_STATICW, L"敌人2", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 60, 50, 60, 40, GameProcessInfo.g_HWND, (HMENU)0x2102, GameProcessInfo.g_HINSTANCE, 0);
		Enemy03_ID_Static_hwnd = CreateWindowW(WC_STATICW, L"敌人3", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 60, 100, 60, 40, GameProcessInfo.g_HWND, (HMENU)0x2103, GameProcessInfo.g_HINSTANCE, 0);
		Enemy04_ID_Static_hwnd = CreateWindowW(WC_STATICW, L"敌人4", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 60, 150, 60, 40, GameProcessInfo.g_HWND, (HMENU)0x2104, GameProcessInfo.g_HINSTANCE, 0);
		Enemy05_ID_Static_hwnd = CreateWindowW(WC_STATICW, L"敌人5", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 60, 200, 60, 40, GameProcessInfo.g_HWND, (HMENU)0x2105, GameProcessInfo.g_HINSTANCE, 0);
		Enemy06_ID_Static_hwnd = CreateWindowW(WC_STATICW, L"敌人6", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 60, 250, 60, 40, GameProcessInfo.g_HWND, (HMENU)0x2106, GameProcessInfo.g_HINSTANCE, 0);
		Enemy07_ID_Static_hwnd = CreateWindowW(WC_STATICW, L"敌人7", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 60, 300, 60, 40, GameProcessInfo.g_HWND, (HMENU)0x2107, GameProcessInfo.g_HINSTANCE, 0);
		Enemy08_ID_Static_hwnd = CreateWindowW(WC_STATICW, L"敌人8", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 60, 350, 60, 40, GameProcessInfo.g_HWND, (HMENU)0x2108, GameProcessInfo.g_HINSTANCE, 0);
		Enemy09_ID_Static_hwnd = CreateWindowW(WC_STATICW, L"敌人9", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 60, 400, 60, 40, GameProcessInfo.g_HWND, (HMENU)0x2109, GameProcessInfo.g_HINSTANCE, 0);
		Enemy10_ID_Static_hwnd = CreateWindowW(WC_STATICW, L"敌人10", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 60, 450, 60, 40, GameProcessInfo.g_HWND, (HMENU)0x210A, GameProcessInfo.g_HINSTANCE, 0);

		Enemy01_Where_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 120, 0, 150, 40, GameProcessInfo.g_HWND, (HMENU)0x2301, GameProcessInfo.g_HINSTANCE, 0);
		Enemy02_Where_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 120, 50, 150, 40, GameProcessInfo.g_HWND, (HMENU)0x2302, GameProcessInfo.g_HINSTANCE, 0);
		Enemy03_Where_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 120, 100, 150, 40, GameProcessInfo.g_HWND, (HMENU)0x2303, GameProcessInfo.g_HINSTANCE, 0);
		Enemy04_Where_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 120, 150, 150, 40, GameProcessInfo.g_HWND, (HMENU)0x2304, GameProcessInfo.g_HINSTANCE, 0);
		Enemy05_Where_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 120, 200, 150, 40, GameProcessInfo.g_HWND, (HMENU)0x2305, GameProcessInfo.g_HINSTANCE, 0);
		Enemy06_Where_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 120, 250, 150, 40, GameProcessInfo.g_HWND, (HMENU)0x2306, GameProcessInfo.g_HINSTANCE, 0);
		Enemy07_Where_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 120, 300, 150, 40, GameProcessInfo.g_HWND, (HMENU)0x2307, GameProcessInfo.g_HINSTANCE, 0);
		Enemy08_Where_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 120, 350, 150, 40, GameProcessInfo.g_HWND, (HMENU)0x2308, GameProcessInfo.g_HINSTANCE, 0);
		Enemy09_Where_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 120, 400, 150, 40, GameProcessInfo.g_HWND, (HMENU)0x2309, GameProcessInfo.g_HINSTANCE, 0);
		Enemy10_Where_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 120, 450, 150, 40, GameProcessInfo.g_HWND, (HMENU)0x230A, GameProcessInfo.g_HINSTANCE, 0);


		Enemy01_HP_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 10, 0, 50, 40, GameProcessInfo.g_HWND, (HMENU)0x2201, GameProcessInfo.g_HINSTANCE, 0);
		Enemy02_HP_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 10, 50, 50, 40, GameProcessInfo.g_HWND, (HMENU)0x2202, GameProcessInfo.g_HINSTANCE, 0);
		Enemy03_HP_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 10, 100, 50, 40, GameProcessInfo.g_HWND, (HMENU)0x2203, GameProcessInfo.g_HINSTANCE, 0);
		Enemy04_HP_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 10, 150, 50, 40, GameProcessInfo.g_HWND, (HMENU)0x2204, GameProcessInfo.g_HINSTANCE, 0);
		Enemy05_HP_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 10, 200, 50, 40, GameProcessInfo.g_HWND, (HMENU)0x2205, GameProcessInfo.g_HINSTANCE, 0);
		Enemy06_HP_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 10, 250, 50, 40, GameProcessInfo.g_HWND, (HMENU)0x2206, GameProcessInfo.g_HINSTANCE, 0);
		Enemy07_HP_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 10, 300, 50, 40, GameProcessInfo.g_HWND, (HMENU)0x2207, GameProcessInfo.g_HINSTANCE, 0);
		Enemy08_HP_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 10, 350, 50, 40, GameProcessInfo.g_HWND, (HMENU)0x2208, GameProcessInfo.g_HINSTANCE, 0);
		Enemy09_HP_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 10, 400, 50, 40, GameProcessInfo.g_HWND, (HMENU)0x2209, GameProcessInfo.g_HINSTANCE, 0);
		Enemy10_HP_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 10, 450, 50, 40, GameProcessInfo.g_HWND, (HMENU)0x220A, GameProcessInfo.g_HINSTANCE, 0);

		Enemy01_Distance_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 270, 0, 80, 40, GameProcessInfo.g_HWND, (HMENU)0x2401, GameProcessInfo.g_HINSTANCE, 0);
		Enemy02_Distance_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 270, 50, 80, 40, GameProcessInfo.g_HWND, (HMENU)0x2402, GameProcessInfo.g_HINSTANCE, 0);
		Enemy03_Distance_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 270, 100, 80, 40, GameProcessInfo.g_HWND, (HMENU)0x2403, GameProcessInfo.g_HINSTANCE, 0);
		Enemy04_Distance_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 270, 150, 80, 40, GameProcessInfo.g_HWND, (HMENU)0x2404, GameProcessInfo.g_HINSTANCE, 0);
		Enemy05_Distance_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 270, 200, 80, 40, GameProcessInfo.g_HWND, (HMENU)0x2405, GameProcessInfo.g_HINSTANCE, 0);
		Enemy06_Distance_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 270, 250, 80, 40, GameProcessInfo.g_HWND, (HMENU)0x2406, GameProcessInfo.g_HINSTANCE, 0);
		Enemy07_Distance_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 270, 300, 80, 40, GameProcessInfo.g_HWND, (HMENU)0x2407, GameProcessInfo.g_HINSTANCE, 0);
		Enemy08_Distance_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 270, 350, 80, 40, GameProcessInfo.g_HWND, (HMENU)0x2408, GameProcessInfo.g_HINSTANCE, 0);
		Enemy09_Distance_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 270, 400, 80, 40, GameProcessInfo.g_HWND, (HMENU)0x2409, GameProcessInfo.g_HINSTANCE, 0);
		Enemy10_Distance_Edit_hwnd = CreateWindowW(WC_EDIT, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_LEFT, 270, 450, 80, 40, GameProcessInfo.g_HWND, (HMENU)0x240A, GameProcessInfo.g_HINSTANCE, 0);
		//如果关闭报点如果存在容器那么销毁new_WINDOWS容器
		DestroyWindow(Enemy01_ID_Static_hwnd);
		DestroyWindow(Enemy02_ID_Static_hwnd);
		DestroyWindow(Enemy03_ID_Static_hwnd);
		DestroyWindow(Enemy04_ID_Static_hwnd);
		DestroyWindow(Enemy05_ID_Static_hwnd);
		DestroyWindow(Enemy06_ID_Static_hwnd);
		DestroyWindow(Enemy07_ID_Static_hwnd);
		DestroyWindow(Enemy08_ID_Static_hwnd);
		DestroyWindow(Enemy09_ID_Static_hwnd);
		DestroyWindow(Enemy10_ID_Static_hwnd);


		DestroyWindow(Enemy01_Where_Edit_hwnd);
		DestroyWindow(Enemy02_Where_Edit_hwnd);
		DestroyWindow(Enemy03_Where_Edit_hwnd);
		DestroyWindow(Enemy04_Where_Edit_hwnd);
		DestroyWindow(Enemy05_Where_Edit_hwnd);
		DestroyWindow(Enemy06_Where_Edit_hwnd);
		DestroyWindow(Enemy07_Where_Edit_hwnd);
		DestroyWindow(Enemy08_Where_Edit_hwnd);
		DestroyWindow(Enemy09_Where_Edit_hwnd);
		DestroyWindow(Enemy10_Where_Edit_hwnd);

		DestroyWindow(Enemy01_HP_Edit_hwnd);
		DestroyWindow(Enemy02_HP_Edit_hwnd);
		DestroyWindow(Enemy03_HP_Edit_hwnd);
		DestroyWindow(Enemy04_HP_Edit_hwnd);
		DestroyWindow(Enemy05_HP_Edit_hwnd);
		DestroyWindow(Enemy06_HP_Edit_hwnd);
		DestroyWindow(Enemy07_HP_Edit_hwnd);
		DestroyWindow(Enemy08_HP_Edit_hwnd);
		DestroyWindow(Enemy09_HP_Edit_hwnd);
		DestroyWindow(Enemy10_HP_Edit_hwnd);

		DestroyWindow(Enemy01_Distance_Edit_hwnd);
		DestroyWindow(Enemy02_Distance_Edit_hwnd);
		DestroyWindow(Enemy03_Distance_Edit_hwnd);
		DestroyWindow(Enemy04_Distance_Edit_hwnd);
		DestroyWindow(Enemy05_Distance_Edit_hwnd);
		DestroyWindow(Enemy06_Distance_Edit_hwnd);
		DestroyWindow(Enemy07_Distance_Edit_hwnd);
		DestroyWindow(Enemy08_Distance_Edit_hwnd);
		DestroyWindow(Enemy09_Distance_Edit_hwnd);
		DestroyWindow(Enemy10_Distance_Edit_hwnd);
		//条件判断
		if (!CheckGaming() || !CheckMoudle() || !GameStatusInfo.InGameChess) { continue; };
		//将敌人信息依次放入容器
		Index_EnemyAlive = 0;
		for (int i = 0; i < GameStatusInfo.AllPlayerNum_Alive; i++) { 
			if (AllPlayerArray[i].TeamTag == Localplayer.EnemyTeamTag && AllPlayerArray[i].LifeState == 256 && AllPlayerArray[i].HP > 0 && AllPlayerArray[i].HP <= 100) {
				std::string Iswhere = GetWhere(GameStatusInfo.MapStatus, AllPlayerArray[i].X_Feet, AllPlayerArray[i].Y_Feet, AllPlayerArray[i].Z_Feet);
				std::wstring wstr_distance = std::to_wstring(AllPlayerArray[i].distance);
				wstr_distance = TakeN_DecimalPlaces(wstr_distance, 4);
				Index_EnemyAlive += 1;
				SetDlgItemTextW(GameProcessInfo.g_HWND, 0x2300 + Index_EnemyAlive, string2wstring(Iswhere).c_str());
				SetDlgItemTextW(GameProcessInfo.g_HWND, 0x2200 + Index_EnemyAlive, std::to_wstring(AllPlayerArray[i].HP).c_str());
				SetDlgItemTextW(GameProcessInfo.g_HWND, 0x2400 + Index_EnemyAlive, wstr_distance.c_str());
			}
		};
		//根据目前存活的敌人控制展示的报点窗口大小
		ReportPositionWidth = 350; ReportPositionHeight = 48 * Index_EnemyAlive;
		SetWindowSize(GameProcessInfo.g_HWND, ReportPositionWidth, ReportPositionHeight);

		

	};
};
//透视进程
DWORD WINAPI CreateESP() {
	while (true)
	{
		PauseMs(10);
		//条件判断
		if (!CheckGaming() || !CheckMoudle()) { continue; };
		//各种透视模式选择
		switch (ESPModel)
		{
		case Xray:
			break;
		case Radar:
			break;
		case D3D:
			break;
		default:
			break;
		}
	}
}
//自瞄进程
DWORD WINAPI AutoAim_GetWhoBeAimed() {
	while (true)
	{
		PauseMs(10);
		//条件判断
		if (!CheckGaming() || !CheckMoudle() || !GameStatusInfo.InGameChess) { continue; };
		//自瞄Who
		// //进入自瞄环节，这个环节有自瞄模式判定
		switch (Auto_Aim_Object) {
		case UNKNOWN: {
			PauseMs(800);
			break;
		}
		case AimAtTheEnemy: {
			switch (Auto_Aim_Model)
			{
			case AimByDistance: {
				PauseMs(10);
				if (AutoAim::AutoAimSetting.HotKey != 无自瞄热键) { if (!(GetAsyncKeyState(AutoAim::AutoAimSetting.HotKey) & 0x8000)) { continue; }; };
				index_Player_LowestDistance_InMain = GetPlayer_LowestDistance(AllPlayerArray, AllPlayerNum, Localplayer, AimAtTheEnemy); if (index_Player_LowestDistance_InMain == -1) { PauseMs(800); continue; };
				AutoAim::UpTargetData(IniTarget, index_Player_LowestDistance_InMain);
				break;
			}
			default:
				PauseMs(800);
				break;
			};
			break;
		};

		default: {
			PauseMs(800);
			break;
		}
		}
	}
}
DWORD WINAPI AutoAim_AimAction() {
	while (1) {
		PauseMs(10);
		if (GameStatus == FALSE || GameStatusInfo.MapStatus == MAP::UNKNOW || AllPlayerNum <= 0 || IFCS2FocalPoint == FALSE || GameStatusInfo.InGameScreen == FALSE|| index_Player_LowestDistance_InMain>=21|| index_Player_LowestDistance_InMain < 0) { continue; };
		if (AutoAim::AutoAimSetting.HotKey != 无自瞄热键) { if (!(GetAsyncKeyState(AutoAim::AutoAimSetting.HotKey) & 0x8000)) { continue; }; };
		mouse_event(MOUSEEVENTF_MOVE, (IniTarget.HorizontalAngle) * (20 / GameOptions.Senvitivity_Mouse), (IniTarget.VerticalAngle) * (20 / GameOptions.Senvitivity_Mouse), 0, 0);
	};
	return 0;
}
