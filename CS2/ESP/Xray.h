//ÐÞ¸Ä»ã±àÖ¸Áî
#pragma once
#include <windows.h>
#include "../Define/Definition.h"
void Show_Xray(LPVOID ClientModuleAddress, HANDLE hProcess) noexcept{
	byte i = NOP;
	WriteProcessMemory(hProcess, (LPVOID)((uintptr_t)ClientModuleAddress + Offset::ClientDLL::Xray::Address), &i, 1, 0);
	WriteProcessMemory(hProcess, (LPVOID)((uintptr_t)ClientModuleAddress + Offset::ClientDLL::Xray::Address + 0x1), &i, 1, 0);
};

void UnShow_Xray(LPVOID ClientModuleAddress, HANDLE hProcess) noexcept{
	byte i = XOR;
	byte j = AL_AL;
	WriteProcessMemory(hProcess, (LPVOID)((uintptr_t)ClientModuleAddress + Offset::ClientDLL::Xray::Address), &i, 1, 0);
	WriteProcessMemory(hProcess, (LPVOID)((uintptr_t)ClientModuleAddress + Offset::ClientDLL::Xray::Address + 0x1), &j, 1, 0);
};
