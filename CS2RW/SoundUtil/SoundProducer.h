#pragma once 
#include <windows.h>  // Windows API
#include <iostream>
#include <thread>
#include <chrono>     // 处理音符之间的时间间隔

// 播放功能开启提示音 (叮咚, 模拟一种轻快的提示音)
void playEnableSound() {
    // 使用两个高频音来模拟“叮咚”
    Beep(1200, 150); // 1200 Hz, 150ms (叮)
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 间隔
    Beep(1400, 150); // 1400 Hz, 150ms (咚)
}

// 播放功能关闭提示音 (咕咚, 模拟一种低沉的提示音)
void playDisableSound() {
    // 使用两个较低频音调来模拟“咕咚”
    Beep(900, 200); // 900 Hz, 200ms (咕)
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 间隔
    Beep(700, 200); // 700 Hz, 200ms (咚)
}

void genTone(STone& Tone) {
	Beep(Tone.frequency, Tone.duration);
};