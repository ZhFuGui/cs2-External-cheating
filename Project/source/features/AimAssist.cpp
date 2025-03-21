#include "../../headers/features/AimAssist.h"
#include "../../headers/core/ProcessUtil.h"
#include "../../output/offsets.hpp"
#include "../../output/client_dll.hpp"
#include <cmath>
#include <memory>
#include <iostream>
#include <thread>
namespace CS2Assist {

    AimAssist::AimAssist(HANDLE processHandle, HMODULE clientModule, Entity* entityList, Entity& local)
        : hProcess(processHandle), ClientModuleAddress((uint64_t)clientModule),
        entityList(entityList), local(local) {
    }

    AimAssist::~AimAssist() {}

    void AimAssist::MouseAim(TargetMode mode, const TargetScope& scope) {
        INPUT input{};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;

        while (true) {
            Entity target = SelectTarget(mode, scope);
            if (!target.isValid || target.health <= 0) continue;

            Angle correction = CalcAimAngle(
                Target2Me(local.cameraPosition, PosCalibrated(target.cameraPosition, Angle2Arc(target.eyeAngle))),
                local.eyeAngle
            );

            input.mi.dx = static_cast<LONG>(correction.yaw * Consts::Factor::PerAngleInFov_scalingFactor);
            input.mi.dy = static_cast<LONG>(correction.pitch * Consts::Factor::PerAngleInFov_scalingFactor);
            SendInput(1, &input, sizeof(INPUT));
            Sleep(20); // ���ӳ٣�ģ�����
        }
    }

    void AimAssist::MemoryAim(TargetMode mode, const TargetScope& scope) {
        while (true) {
            Entity target = SelectTarget(mode, scope);
            if (!target.isValid || target.health <= 0) continue;

            Angle correction = Target2Me(local.cameraPosition, PosCalibrated(target.cameraPosition, Angle2Arc(target.eyeAngle)));

            WriteProcessMemory(hProcess,
                reinterpret_cast<LPVOID>(ClientModuleAddress + cs2_dumper::offsets::client_dll::dwViewAngles),
                &correction.pitch, sizeof(float), nullptr);
            WriteProcessMemory(hProcess,
                reinterpret_cast<LPVOID>(ClientModuleAddress + cs2_dumper::offsets::client_dll::dwViewAngles + 0x4),
                &correction.yaw, sizeof(float), nullptr);
            Sleep(10); // ���ӳ٣�ģ�����
        }
    }

    void AimAssist::SilentAim(TargetMode mode , const TargetScope& scope) {
        // ����Զ�̽����ڴ棬���ڴ�� shellcode �ͽǶ�����
        LPVOID shellcodeAddr = VirtualAllocEx(hProcess, NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (!shellcodeAddr) return;
        std::cout << shellcodeAddr << std::endl;
        // ���� shellcode ������ƫ�ƺͷ��ص�ַ
        BYTE shellcode[Consts::SilentAim::ShellcodeSize];
        memcpy(shellcode, Consts::SilentAim::Shellcode, Consts::SilentAim::ShellcodeSize);

        // ���ݴ洢λ��
        uintptr_t pitchAddr = reinterpret_cast<uintptr_t>(shellcodeAddr) + 0x500; // pitch ֵ�洢��ַ
        uintptr_t yawAddr = pitchAddr + 4;                                        // yaw ֵ�洢��ַ (ƫ�� 4 �ֽ�)

        // ���� rip ���ƫ�� (���� movss ָ����ڴ�Ѱַ)
        int pitchOffset = 0x500 - 36; // rip = shellcodeAddr + 36 (movss xmm0 ָ���ĵ�ַ)
        int yawOffset = 0x504 - 44;   // rip = shellcodeAddr + 44 (movss xmm1 ָ���ĵ�ַ)
        memcpy(shellcode + Consts::SilentAim::PitchOffsetPos, &pitchOffset, 4); // ���� pitch ƫ��
        memcpy(shellcode + Consts::SilentAim::YawOffsetPos, &yawOffset, 4);     // ���� yaw ƫ��

        // ��ȡע���ͷ��ص�ַ
        uint64_t targetAddr = 0;
        ProcessUtil::ScanSignature(hProcess, reinterpret_cast<HMODULE>(ClientModuleAddress),
            Consts::SignCode::ServerShotAngle, targetAddr);
        std::cout << targetAddr << std::endl;
        uintptr_t returnAddr = targetAddr + Consts::SilentAim::JmpPatchSize; // ���ص�ַ������ jmpPatch ���Ⱥ󷵻�
        memcpy(shellcode + Consts::SilentAim::ReturnAddrPos, &returnAddr, sizeof(uintptr_t)); // ���·��ص�ַ

        // д�� shellcode ��Զ�̽���
        SIZE_T bytesWritten;
        if (!WriteProcessMemory(hProcess, shellcodeAddr, shellcode, Consts::SilentAim::ShellcodeSize, &bytesWritten)) {
            VirtualFreeEx(hProcess, shellcodeAddr, 0, MEM_RELEASE);
            return;
        }

        // ���� jmpPatch ������ shellcode ��ַ
        BYTE jmpPatch[Consts::SilentAim::JmpPatchSize];
        memcpy(jmpPatch, Consts::SilentAim::JmpPatch, Consts::SilentAim::JmpPatchSize);
        memcpy(jmpPatch + Consts::SilentAim::ShellcodeAddrPos, &shellcodeAddr, sizeof(uintptr_t)); // ���� shellcode ��ַ
        if (!WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(targetAddr), jmpPatch, Consts::SilentAim::JmpPatchSize, &bytesWritten)) {
            VirtualFreeEx(hProcess, shellcodeAddr, 0, MEM_RELEASE);
            return;
        }
        std::cout << shellcodeAddr << std::endl;
        std::cout << targetAddr << std::endl;
        // ��ѭ��������Ŀ��Ƕ�
        while (true) {
            Entity target = SelectTarget(mode, scope);
            if (!target.isValid || target.health <= 0) continue;

            Angle correction = Target2Me(local.cameraPosition, PosCalibrated(target.cameraPosition, Angle2Arc(target.eyeAngle)));
            WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(pitchAddr), &correction.yaw, sizeof(float), nullptr);
            WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(yawAddr), &correction.pitch, sizeof(float), nullptr);
            //Sleep(10); // ���ӳ٣�ģ�����
        }

        // ע�⣺�˺����е� while(true) ѭ������ֹ�������أ���������ͷŴ��벻�ɴ�
        // VirtualFreeEx(hProcess, shellcodeAddr, 0, MEM_RELEASE);
    };

    Entity AimAssist::SelectTarget(TargetMode mode, const TargetScope& scope) const {
        Entity bestTarget;
        float bestMetric = FLT_MAX; // ���ڱȽϵ�ָ�꣨���롢�Ƕȵȣ�

        for (int i = 0; i < 64; ++i) {
            const Entity& entity = entityList[i];
            if (!entity.isValid || entity.health <= 0 || entity.controllerAddr == local.controllerAddr) continue;

            // ���Ŀ������
            bool validType = false;
            switch (scope.type) {
            case TargetScope::TargetType::EnemiesOnly:
                validType = entity.teamId != local.teamId;
                break;
            case TargetScope::TargetType::TeammatesOnly:
                validType = entity.teamId == local.teamId;
                break;
            case TargetScope::TargetType::Indiscriminate:
                validType = true;
                break;
            }
            if (!validType) continue;

            // ����ӽǷ�Χ
            if (!IsInFov(entity, scope.horizontalFov, scope.verticalFov)) continue;

            // ��������ģʽ����ָ��
            float metric = 0.0f;
            switch (mode) {
            case TargetMode::ClosestDistance:
                metric = local.cameraPosition.DistanceXY(entity.cameraPosition);
                break;
            case TargetMode::WithinCrosshair: {
                Angle targetAngle = Target2Me(local.cameraPosition, entity.cameraPosition);
                Angle diff = CalcAimAngle(targetAngle, local.eyeAngle);
                metric = std::sqrt(diff.pitch * diff.pitch + diff.yaw * diff.yaw); // �ǶȾ���
                break;
            }
            case TargetMode::VisibleEntity:
                if (!IsVisible(entity)) continue;
                //�����ҵ����� �ҿ����� �������
                metric = local.cameraPosition.DistanceXY(entity.cameraPosition);
                break;
            case TargetMode::SpecificName:
                // ��Ҫ�������ָ�����ƣ������������
                continue;
            case TargetMode::LowestHealth:
                metric = static_cast<float>(entity.health);
                bestMetric = -FLT_MAX; // Ѫ��Խ��Խ�ã������Ƚ��߼�
                break;
            case TargetMode::KnifeOrTaser:
                // ��Ҫ����������ͣ������������
                continue;
            }

            // �������Ŀ��
            if ((mode == TargetMode::LowestHealth && metric > bestMetric) ||
                (mode != TargetMode::LowestHealth && metric < bestMetric)) {
                bestMetric = metric;
                bestTarget = entity;
            }
        }
        return bestTarget;
    }

    bool AimAssist::IsInFov(const Entity& entity, float horizontalFov, float verticalFov) const {
        Angle targetAngle = Target2Me(local.cameraPosition, entity.cameraPosition);
        Angle diff = CalcAimAngle(targetAngle, local.eyeAngle);
        return std::abs(diff.yaw) <= horizontalFov / 2.0f && std::abs(diff.pitch) <= verticalFov / 2.0f;
    }

    bool AimAssist::IsVisible(const Entity& entity) const {
        // ��ʵ�֣�����׷�ٻ��������߼�
        if ((local.SpottedByMask & (DWORD64(1) << (entity.ID - 1)))) {
            return true;
        };
        if (entity.isSpotted) {
            return true;
        };
        return false; // ռλ
    }

    Angle AimAssist::Angle2Arc(const Angle& angle) const {
        return Angle(
            angle.pitch * (static_cast<float>(Consts::Math::PI) / 180.0f),
            angle.yaw * (static_cast<float>(Consts::Math::PI) / 180.0f)
        );
    }

    Vec3 AimAssist::PosCalibrated(const Vec3& pos, const Angle& eyeArc) const {
        return Vec3(
            pos.x + std::cos(eyeArc.yaw) * Consts::Factor::camera2head_Factor,
            pos.y + std::sin(eyeArc.yaw) * Consts::Factor::camera2head_Factor,
            pos.z
        );
    }

    Angle AimAssist::CalcAimAngle(const Angle& targetAngle, const Angle& myEyeAngle) const {
        float dYaw = targetAngle.yaw - myEyeAngle.yaw;
        float dPitch = targetAngle.pitch - myEyeAngle.pitch;

        if (dYaw > 180.0f) dYaw -= 360.0f;
        else if (dYaw < -180.0f) dYaw += 360.0f;

        return Angle(dPitch, -dYaw);
    }

    Angle AimAssist::Target2Me(const Vec3& myPos, const Vec3& targetPos) const {
        float dX = targetPos.x - myPos.x;
        float dY = targetPos.y - myPos.y;
        float dZ = targetPos.z - myPos.z;
        float dXY = myPos.DistanceXY(targetPos);

        float yaw = std::atan2(dY, dX) * 180.0f / static_cast<float>(Consts::Math::PI);
        float pitch = std::atan2(-dZ, dXY) * 180.0f / static_cast<float>(Consts::Math::PI);
        return Angle(pitch, yaw);
    }
    bool AimAssist::testThread() {

        std::thread updateThread([this]() {
            TargetScope Scope;
            Scope.type=TargetScope::TargetType::Indiscriminate;
            SilentAim(TargetMode::VisibleEntity, Scope);
            }
        );
        updateThread.detach();
    };
        
} // namespace CS2Assist