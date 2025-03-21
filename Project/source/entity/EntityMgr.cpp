#include "../../headers/entity/EntityMgr.h"
#include "../../output/offsets.hpp"
#include "../../output/client_dll.hpp"

//#include "../../headers\utils\MiscUtil.h"


namespace CS2Assist {

    EntityMgr::EntityMgr(HANDLE processHandle, HMODULE clientModule)
        : hProcess(processHandle), ClientModuleAddress((uint64_t)clientModule),
        entityListBase(0), controllerBase(0) {
        ReadProcessMemory(hProcess, (LPVOID)(ClientModuleAddress + cs2_dumper::offsets::client_dll::dwEntityList),
            &entityListBase, sizeof(entityListBase), nullptr);
        ReadProcessMemory(hProcess, (LPVOID)(entityListBase + 0x10),
            &controllerBase, sizeof(controllerBase), nullptr);
    }

    bool EntityMgr::GetLocalPlayer(Entity& localEntity) {
        uint64_t localPawnAddr = 0;
        if (!ReadProcessMemory(hProcess, (LPVOID)(ClientModuleAddress + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn),
            &localPawnAddr, sizeof(localPawnAddr), nullptr) || !localPawnAddr) {
            return false;
        }

        uint64_t localControllerAddr = 0;
        if (!ReadProcessMemory(hProcess, (LPVOID)(ClientModuleAddress + cs2_dumper::offsets::client_dll::dwLocalPlayerController),
            &localControllerAddr, sizeof(localControllerAddr), nullptr) || !localControllerAddr) {
            return false;
        }

        localEntity.pawnAddr = localPawnAddr;
        localEntity.controllerAddr = localControllerAddr;

        if (!ReadEntityData(localControllerAddr, localPawnAddr, localEntity)) {
            return false;
        }

        localEntity.isValid = true;
        return true;
    }

    bool EntityMgr::FetchEntities(Entity* entityList, int maxEntities) {
        if (!hProcess || !controllerBase || maxEntities <= 0 || !entityList) {
            return false;
        }

        for (int i = 0; i < maxEntities; i++) {

            entityList[i].ID = i;

            uint64_t controllerAddr = 0;
            if (!ReadProcessMemory(hProcess, (LPVOID)(controllerBase + i * 0x78),
                &controllerAddr, sizeof(controllerAddr), nullptr) || !controllerAddr) {
                entityList[i].isValid = false;
                continue;
            }
            entityList[i].controllerAddr = controllerAddr;

            uint64_t playerPawnHandle = 0;
            if (!ReadProcessMemory(hProcess, (LPVOID)(controllerAddr + cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn),
                &playerPawnHandle, sizeof(playerPawnHandle), nullptr) || !playerPawnHandle) {
                entityList[i].isValid = false;
                continue;
            }

            uint64_t entry2 = 0;
            if (!ReadProcessMemory(hProcess, (LPVOID)(entityListBase + 0x8 * ((playerPawnHandle & 0x7FFF) >> 9) + 0x10),
                &entry2, sizeof(entry2), nullptr) || !entry2) {
                entityList[i].isValid = false;
                continue;
            }

            uint64_t entityInstanceAddr = entry2 + 0x78 * (playerPawnHandle & 0x1FF);
            if (!ReadProcessMemory(hProcess, (LPVOID)entityInstanceAddr,
                &entityList[i].pawnAddr, sizeof(entityList[i].pawnAddr), nullptr) || !entityList[i].pawnAddr) {
                entityList[i].isValid = false;
                continue;
            }

            if (!ReadEntityData(controllerAddr, entityList[i].pawnAddr, entityList[i])) {
                entityList[i].isValid = false;
                continue;
            }

            entityList[i].isValid = true;
        }
        return true;
    };
    //读取实体数据
    bool EntityMgr::ReadEntityData(uint64_t controllerAddr, uint64_t pawnAddr, Entity& entity) {

        // 读取姓名 阵营ID 血量 相机位置 视角角度 相机速度 武器名称 被瞄标识

        uint64_t nameAddr = 0;  char nameBuffer[256] = { 0 };
        if (ReadProcessMemory(hProcess, (LPVOID)(controllerAddr + cs2_dumper::schemas::client_dll::CCSPlayerController::m_sSanitizedPlayerName),
            &nameAddr, sizeof(nameAddr), nullptr) && nameAddr) {
            if (ReadProcessMemory(hProcess, (LPVOID)nameAddr, nameBuffer, sizeof(nameBuffer) - 1, nullptr)) {
                entity.name = std::string(nameBuffer);
            }
        }

        if (!ReadProcessMemory(hProcess, (LPVOID)(pawnAddr + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum),
            &entity.teamId, sizeof(entity.teamId), nullptr)) {
            entity.teamId = 0;
        }

        if (!ReadProcessMemory(hProcess, (LPVOID)(pawnAddr + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth),
            &entity.health, sizeof(entity.health), nullptr)) {
            entity.health = 0;
        }

        if (!ReadProcessMemory(hProcess, (LPVOID)(pawnAddr + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_vecLastClipCameraPos),
            &entity.cameraPosition, sizeof(entity.cameraPosition), nullptr)) {
            entity.cameraPosition = Vec3();
        }

        if (!ReadProcessMemory(hProcess, (LPVOID)(pawnAddr + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_angEyeAngles),
            &entity.eyeAngle, sizeof(entity.eyeAngle), nullptr)) {
            entity.eyeAngle = Angle();
        }

        if (!ReadProcessMemory(hProcess, (LPVOID)(pawnAddr + cs2_dumper::schemas::client_dll::C_BaseEntity::m_vecVelocity),
            &entity.velocity, sizeof(entity.velocity), nullptr)) {
            entity.velocity = Vec3();
        }

        uint64_t weaponBase = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(pawnAddr + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_pClippingWeapon),
            &weaponBase, sizeof(weaponBase), nullptr) && weaponBase) {
            uint64_t weaponData = 0;
            if (ReadProcessMemory(hProcess, (LPVOID)(weaponBase + cs2_dumper::schemas::client_dll::C_BaseEntity::m_nSubclassID + 0x8),
                &weaponData, sizeof(weaponData), nullptr) && weaponData) {
                uint64_t weaponNameAddr = 0;
                if (ReadProcessMemory(hProcess, (LPVOID)(weaponData + cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_szName),
                    &weaponNameAddr, sizeof(weaponNameAddr), nullptr) && weaponNameAddr) {
                    char weaponBuffer[256] = { 0 };
                    if (ReadProcessMemory(hProcess, (LPVOID)weaponNameAddr, weaponBuffer, sizeof(weaponBuffer) - 1, nullptr)) {
                        entity.weaponName = std::string(weaponBuffer);
                    }
                    else if (entity.weaponName.empty()) {
                        entity.weaponName = "NULL";
                    }
                    else {
                        entity.weaponName = "Unknown";
                    }
                }
            }
        }
        

        if (!ReadProcessMemory(hProcess, (LPVOID)(pawnAddr + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_entitySpottedState + cs2_dumper::schemas::client_dll::EntitySpottedState_t::m_bSpotted),
            &entity.isSpotted, sizeof(entity.isSpotted), nullptr)) {
            entity.isSpotted = 0;
        };


        if (!ReadProcessMemory(hProcess, (LPVOID)(pawnAddr + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_entitySpottedState+ cs2_dumper::schemas::client_dll::EntitySpottedState_t::m_bSpottedByMask),
            &entity.SpottedByMask, sizeof(entity.SpottedByMask), nullptr)) {
            entity.SpottedByMask = 0;
        };



        if (!ReadProcessMemory(hProcess, (LPVOID)(pawnAddr + cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_iIDEntIndex),
            &entity.IDEntIndex, sizeof(entity.IDEntIndex), nullptr)) {
            entity.IDEntIndex = 0;
        };

        return true;
    }


    bool EntityMgr::StartEntityUpdateThread(Entity* entityList, Entity& localEntity) {
        std::thread updateThread([this, entityList, &localEntity]() {
            while (true) {
                FetchEntities(entityList);
                GetLocalPlayer(localEntity);
                //std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
            }
            });
        updateThread.detach(); 
    }
};