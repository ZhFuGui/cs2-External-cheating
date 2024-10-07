#include "Time.h"
//毫秒
void PauseMs(int milliseconds){
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
//微秒
void PauseUs(int microseconds) {
	std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
}
//获取当前时间
std::chrono::steady_clock::time_point NowTime() {
	return std::chrono::high_resolution_clock::now();
}
//求时间微秒差
std::chrono::microseconds DuringTimeUs(std::chrono::steady_clock::time_point Start, std::chrono::steady_clock::time_point End) {
	return std::chrono::duration_cast<std::chrono::microseconds>(End - Start);
}