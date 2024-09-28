#include "GetModule.h"

HMODULE GetModule(HANDLE hProcess, const char ModuleName[MAX_PATH]) {
	DWORD pro_base = NULL;
	HMODULE hModule[999] = { 0 };
	DWORD dwRet = 0;
	int num = 0;
	int bRet = EnumProcessModulesEx(hProcess, (HMODULE*)(hModule), sizeof(hModule), &dwRet, NULL);
	num = dwRet / sizeof(HMODULE);
	char lpBaseName[100];
	for (int i = 0; i < num + 1; i++) {
		GetModuleBaseNameA(hProcess, hModule[i], lpBaseName, sizeof(lpBaseName));
		if (!_stricmp(lpBaseName, ModuleName)) {
			return hModule[i];
		}
	}
	MessageBoxW(0, L"未获取到模块句柄", L"错误", 0);
	return 0;
}