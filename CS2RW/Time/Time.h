//关于时间的库
#pragma once
#include <thread>
#include <chrono>
//毫秒
void PauseMs(int milliseconds); 
//微秒
void PauseUs(int microseconds);

std::chrono::steady_clock::time_point NowTime();

std::chrono::microseconds DuringTimeUs(std::chrono::steady_clock::time_point Start, std::chrono::steady_clock::time_point End);