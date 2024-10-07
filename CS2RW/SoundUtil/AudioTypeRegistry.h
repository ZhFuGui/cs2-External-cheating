#pragma once
#include <Windows.h>
struct STone {
	const int frequency = 2000; // 频率
	const int duration = 500;         // 持续的时间
	STone(int a, int b) : frequency(a), duration(b) {};
}a(23,4);