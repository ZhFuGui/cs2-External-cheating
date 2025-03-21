/*
CS2Assist /
├── headers / # 头文件目录，简洁命名
│   ├── core / # 核心模块
│   │   ├── Config.h            # 配置（偏移量、键位等）
│   │   └── ProcessUtil.h       # 进程操作（PID、内存控制）
│   ├── entity / # 实体模块
│   │   └── EntityMgr.h         # 实体管理和数据结构（人物）
│   ├── features / # 功能模块
│   │   ├── GlowEsp.h           # 发光透视功能
│   │   ├── AimAssist.h         # 自瞄功能
│   │   └── AntiUtils.h			 # 防道具功能的头文件
│   ├── system / # 游戏系统管理模块（新增）
│   │   └── GameSystemMgr.h     # 游戏系统管理和数据结构
│   ├── utils / # 工具模块
│   │   ├── KeyInput.h          # 按键控制
│   │   └── MiscUtil.h          # 杂项工具（声音、一些辅助函数）
│   └── AssistMain.h            # 主程序接口

├── source / # 源代码目录
│   ├── core / # 核心模块实现
│   │   ├── Config.cpp          # 配置实现
│   │   └── ProcessUtil.cpp     # 进程操作实现
│   ├── entity / # 实体模块实现
│   │   └── EntityMgr.cpp       # 实体管理实现（含线程）
│   ├── features / # 功能模块实现
│   │   ├── GlowEsp.cpp         # 发光透视实现（单独线程）
│   │   ├── AimAssist.cpp       # 自瞄实现（单独线程）
│   │   └── AntiUtils.cpp		 # 防道具功能的实现
│   ├── system / # 游戏系统管理模块实现（新增）
│   │   └── GameSystemMgr.cpp   # 游戏系统管理实现
│   ├── utils / # 工具模块实现
│   │   ├── ConstsUtil.h        # 存放特征码和各种定义常数
│   │   ├── KeyInput.cpp        # 按键控制实现
│   │   └── MiscUtil.cpp        # 杂项工具实现
│   └── AssistMain.cpp          # 主程序实现
*/
#include <Windows.h>
#include <iostream>
#include "..\headers\AssistMain.h"
#include "..\output\offsets.hpp"
#include "..\output\client_dll.hpp"
#include "..\headers\core\ProcessUtil.h"
#include "..\headers\entity\EntityMgr.h"
#include "..\headers\utils\MiscUtil.h"
#include "..\headers\features\AimAssist.h"
#include "..\headers\AssistMain.h"
#include <thread>



int main() {

    DWORD Pid = CS2Assist::ProcessUtil::GetProcessPid(L"cs2.exe");

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);

    HMODULE ClientModule = CS2Assist::ProcessUtil::GetModuleHandle(hProcess, "client.dll");

    CS2Assist::EntityMgr entityMgr(hProcess, ClientModule);

    CS2Assist::Entity entityList[64];

    CS2Assist::Entity local;

    CS2Assist::AimAssist aimAssist(hProcess, ClientModule, entityList, local);

	SetConsoleOutputCP(CP_UTF8);

	entityMgr.StartEntityUpdateThread(entityList, local);

	//aimAssist.SilentAim();
    aimAssist.testThread();

    CS2Assist::Sleep_Ms(2000);
    if (!ClientModule) {
        std::cout << "无法找到 client.dll!" << std::endl;
        CloseHandle(hProcess);
        return 1;
    }

    uint64_t resultAddr = 0;

    CS2Assist::ProcessUtil::ScanSignature(hProcess, ClientModule, CS2Assist::Consts::SignCode::BlueXray, resultAddr);
    std::cout << "找到特征码地址: 0x" << std::hex << resultAddr << std::endl;
    while (1) {
        for (int i = 0; i < 64; ++i) {
            if (entityList[i].isValid) {
                std::cout << entityList[i].name << std::endl;
                std::cout << entityList[i].pawnAddr << std::endl;
                std::cout << entityList[i].isSpotted << std::endl;
                std::cout << entityList[i].SpottedByMask << std::endl;
                if ((local.SpottedByMask & (DWORD64(1) << (i-1)))) {
                    std::cout << i << "can look me" << entityList[i].name << std::endl;
                }
            }
        }
        CS2Assist::Sleep_Ms(200);
        system("cls");
    }


	system("pause");

	return 0;
}