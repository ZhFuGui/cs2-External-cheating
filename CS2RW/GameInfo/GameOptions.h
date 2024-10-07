#pragma once
#include <Windows.h>
struct SGameOptions
{
	float Senvitivity_Mouse;
	SGameOptions() {
		this->Senvitivity_Mouse = 1;
	}
}GameOptions;

//得到游戏设置中的鼠标灵敏度
LPVOID MouseSenvitivity_Frist_Address; long long MouseSenvitivity_Second_Address; float Senvitivity_Mouse;
void GetMouseSenvitivity(SGameOptions &GameOptions,HANDLE hProcess, HMODULE ClientModuleAddress) {

	MouseSenvitivity_Frist_Address = (LPVOID)(((long long)ClientModuleAddress + Offset::ClientDLL::GameOptions::Mouse::Sensitivitydefault));

	ReadProcessMemory(hProcess, (void*)(MouseSenvitivity_Frist_Address), &MouseSenvitivity_Second_Address, 8, 0);

	ReadProcessMemory(hProcess, (void*)(MouseSenvitivity_Second_Address + Offset::ClientDLL::GameOptions::BasicOffset), &GameOptions.Senvitivity_Mouse, 4, 0);

};
