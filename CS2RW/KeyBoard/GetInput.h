#pragma once
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <string>


struct KeyInfo {
    int virtualKey;
    std::string description;
    bool isEnabled;
};

// 初始化按键列表
std::vector<KeyInfo> keysToMonitor = {
    {VK_F1, "F1 Key", false},

};

void toggleFeature(KeyInfo& keyInfo) {
    keyInfo.isEnabled = !keyInfo.isEnabled;
    SendMessageW(GameProcessInfo.g_HWND, WM_KEYUP + keyInfo.isEnabled, keyInfo.virtualKey, 0);
    if (keyInfo.isEnabled) {
        playEnableSound();
    }
    else {
        playDisableSound();
    }
}

std::unordered_map<int, bool> wasKeyPressed;

DWORD WINAPI GetKeyBoardInput() {

    for (const auto& keyInfo : keysToMonitor) {
        wasKeyPressed[keyInfo.virtualKey] = false;
    }

    while (true) {
        for (auto& keyInfo : keysToMonitor) {
            int key = keyInfo.virtualKey;

            SHORT keyState = GetAsyncKeyState(key);


            if (keyState & 0x8000) {  
                if (!wasKeyPressed[key]) {   
                    wasKeyPressed[key] = true;
                }
            }
            else {
                if (wasKeyPressed[key]) {   
                    toggleFeature(keyInfo);  
                    wasKeyPressed[key] = false;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return 0;
}

    