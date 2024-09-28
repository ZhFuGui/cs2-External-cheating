//ÐÞ¸Ä»ã±àÖ¸Áî
#pragma once
#include <windows.h>
#include "../Define/Definition.h"
void Show_Xray(LPVOID ClientModuleAddress, HANDLE hProcess) {
	byte i = NOP;
	WriteProcessMemory(hProcess, (void*)((long long)ClientModuleAddress + Xray_Offset), &i, 1, 0);
	WriteProcessMemory(hProcess, (void*)((long long)ClientModuleAddress + Xray_Offset + 0x1), &i, 1, 0);
};

void UnShow_Xray(LPVOID ClientModuleAddress, HANDLE hProcess) {
	byte i = XOR;
	byte j = AL_AL;
	WriteProcessMemory(hProcess, (void*)((long long)ClientModuleAddress + Xray_Offset), &i, 1, 0);
	WriteProcessMemory(hProcess, (void*)((long long)ClientModuleAddress + Xray_Offset + 0x1), &j, 1, 0);
};
