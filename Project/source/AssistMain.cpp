/*
CS2Assist /
������ headers / # ͷ�ļ�Ŀ¼���������
��   ������ core / # ����ģ��
��   ��   ������ Config.h            # ���ã�ƫ��������λ�ȣ�
��   ��   ������ ProcessUtil.h       # ���̲�����PID���ڴ���ƣ�
��   ������ entity / # ʵ��ģ��
��   ��   ������ EntityMgr.h         # ʵ���������ݽṹ�����
��   ������ features / # ����ģ��
��   ��   ������ GlowEsp.h           # ����͸�ӹ���
��   ��   ������ AimAssist.h         # ���鹦��
��   ��   ������ AntiUtils.h			 # �����߹��ܵ�ͷ�ļ�
��   ������ system / # ��Ϸϵͳ����ģ�飨������
��   ��   ������ GameSystemMgr.h     # ��Ϸϵͳ��������ݽṹ
��   ������ utils / # ����ģ��
��   ��   ������ KeyInput.h          # ��������
��   ��   ������ MiscUtil.h          # ����ߣ�������һЩ����������
��   ������ AssistMain.h            # ������ӿ�

������ source / # Դ����Ŀ¼
��   ������ core / # ����ģ��ʵ��
��   ��   ������ Config.cpp          # ����ʵ��
��   ��   ������ ProcessUtil.cpp     # ���̲���ʵ��
��   ������ entity / # ʵ��ģ��ʵ��
��   ��   ������ EntityMgr.cpp       # ʵ�����ʵ�֣����̣߳�
��   ������ features / # ����ģ��ʵ��
��   ��   ������ GlowEsp.cpp         # ����͸��ʵ�֣������̣߳�
��   ��   ������ AimAssist.cpp       # ����ʵ�֣������̣߳�
��   ��   ������ AntiUtils.cpp		 # �����߹��ܵ�ʵ��
��   ������ system / # ��Ϸϵͳ����ģ��ʵ�֣�������
��   ��   ������ GameSystemMgr.cpp   # ��Ϸϵͳ����ʵ��
��   ������ utils / # ����ģ��ʵ��
��   ��   ������ ConstsUtil.h        # ���������͸��ֶ��峣��
��   ��   ������ KeyInput.cpp        # ��������ʵ��
��   ��   ������ MiscUtil.cpp        # �����ʵ��
��   ������ AssistMain.cpp          # ������ʵ��
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
        std::cout << "�޷��ҵ� client.dll!" << std::endl;
        CloseHandle(hProcess);
        return 1;
    }

    uint64_t resultAddr = 0;

    CS2Assist::ProcessUtil::ScanSignature(hProcess, ClientModule, CS2Assist::Consts::SignCode::BlueXray, resultAddr);
    std::cout << "�ҵ��������ַ: 0x" << std::hex << resultAddr << std::endl;
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