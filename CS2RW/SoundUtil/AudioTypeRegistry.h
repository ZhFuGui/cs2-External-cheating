#pragma once
#include <Windows.h>
struct Sound {
	const unsigned short frequency = 2000; // 可以调整为其他值
	const DWORD duration = 500;         // 声音持续的时间
};