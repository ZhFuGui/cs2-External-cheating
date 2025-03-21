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
            Sleep(20); // 简单延迟，模拟测试
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
            Sleep(10); // 简单延迟，模拟测试
        }
    }

    void AimAssist::SilentAim(TargetMode mode , const TargetScope& scope) {
        // 分配远程进程内存，用于存放 shellcode 和角度数据
        LPVOID shellcodeAddr = VirtualAllocEx(hProcess, NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (!shellcodeAddr) return;
        std::cout << shellcodeAddr << std::endl;
        // 复制 shellcode 并更新偏移和返回地址
        BYTE shellcode[Consts::SilentAim::ShellcodeSize];
        memcpy(shellcode, Consts::SilentAim::Shellcode, Consts::SilentAim::ShellcodeSize);

        // 数据存储位置
        uintptr_t pitchAddr = reinterpret_cast<uintptr_t>(shellcodeAddr) + 0x500; // pitch 值存储地址
        uintptr_t yawAddr = pitchAddr + 4;                                        // yaw 值存储地址 (偏移 4 字节)

        // 计算 rip 相对偏移 (用于 movss 指令的内存寻址)
        int pitchOffset = 0x500 - 36; // rip = shellcodeAddr + 36 (movss xmm0 指令后的地址)
        int yawOffset = 0x504 - 44;   // rip = shellcodeAddr + 44 (movss xmm1 指令后的地址)
        memcpy(shellcode + Consts::SilentAim::PitchOffsetPos, &pitchOffset, 4); // 更新 pitch 偏移
        memcpy(shellcode + Consts::SilentAim::YawOffsetPos, &yawOffset, 4);     // 更新 yaw 偏移

        // 获取注入点和返回地址
        uint64_t targetAddr = 0;
        ProcessUtil::ScanSignature(hProcess, reinterpret_cast<HMODULE>(ClientModuleAddress),
            Consts::SignCode::ServerShotAngle, targetAddr);
        std::cout << targetAddr << std::endl;
        uintptr_t returnAddr = targetAddr + Consts::SilentAim::JmpPatchSize; // 返回地址，覆盖 jmpPatch 长度后返回
        memcpy(shellcode + Consts::SilentAim::ReturnAddrPos, &returnAddr, sizeof(uintptr_t)); // 更新返回地址

        // 写入 shellcode 到远程进程
        SIZE_T bytesWritten;
        if (!WriteProcessMemory(hProcess, shellcodeAddr, shellcode, Consts::SilentAim::ShellcodeSize, &bytesWritten)) {
            VirtualFreeEx(hProcess, shellcodeAddr, 0, MEM_RELEASE);
            return;
        }

        // 复制 jmpPatch 并更新 shellcode 地址
        BYTE jmpPatch[Consts::SilentAim::JmpPatchSize];
        memcpy(jmpPatch, Consts::SilentAim::JmpPatch, Consts::SilentAim::JmpPatchSize);
        memcpy(jmpPatch + Consts::SilentAim::ShellcodeAddrPos, &shellcodeAddr, sizeof(uintptr_t)); // 更新 shellcode 地址
        if (!WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(targetAddr), jmpPatch, Consts::SilentAim::JmpPatchSize, &bytesWritten)) {
            VirtualFreeEx(hProcess, shellcodeAddr, 0, MEM_RELEASE);
            return;
        }
        std::cout << shellcodeAddr << std::endl;
        std::cout << targetAddr << std::endl;
        // 主循环：更新目标角度
        while (true) {
            Entity target = SelectTarget(mode, scope);
            if (!target.isValid || target.health <= 0) continue;

            Angle correction = Target2Me(local.cameraPosition, PosCalibrated(target.cameraPosition, Angle2Arc(target.eyeAngle)));
            WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(pitchAddr), &correction.yaw, sizeof(float), nullptr);
            WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(yawAddr), &correction.pitch, sizeof(float), nullptr);
            //Sleep(10); // 简单延迟，模拟测试
        }

        // 注意：此函数中的 while(true) 循环会阻止函数返回，因此以下释放代码不可达
        // VirtualFreeEx(hProcess, shellcodeAddr, 0, MEM_RELEASE);
    };

    Entity AimAssist::SelectTarget(TargetMode mode, const TargetScope& scope) const {
        Entity bestTarget;
        float bestMetric = FLT_MAX; // 用于比较的指标（距离、角度等）

        for (int i = 0; i < 64; ++i) {
            const Entity& entity = entityList[i];
            if (!entity.isValid || entity.health <= 0 || entity.controllerAddr == local.controllerAddr) continue;

            // 检查目标类型
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

            // 检查视角范围
            if (!IsInFov(entity, scope.horizontalFov, scope.verticalFov)) continue;

            // 根据索敌模式计算指标
            float metric = 0.0f;
            switch (mode) {
            case TargetMode::ClosestDistance:
                metric = local.cameraPosition.DistanceXY(entity.cameraPosition);
                break;
            case TargetMode::WithinCrosshair: {
                Angle targetAngle = Target2Me(local.cameraPosition, entity.cameraPosition);
                Angle diff = CalcAimAngle(targetAngle, local.eyeAngle);
                metric = std::sqrt(diff.pitch * diff.pitch + diff.yaw * diff.yaw); // 角度距离
                break;
            }
            case TargetMode::VisibleEntity:
                if (!IsVisible(entity)) continue;
                //看到我的优先 我看到的 最近距离
                metric = local.cameraPosition.DistanceXY(entity.cameraPosition);
                break;
            case TargetMode::SpecificName:
                // 需要额外参数指定名称，这里假设跳过
                continue;
            case TargetMode::LowestHealth:
                metric = static_cast<float>(entity.health);
                bestMetric = -FLT_MAX; // 血量越低越好，调整比较逻辑
                break;
            case TargetMode::KnifeOrTaser:
                // 需要检查武器类型，这里假设跳过
                continue;
            }

            // 更新最佳目标
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
        // 待实现：射线追踪或掩体检测逻辑
        if ((local.SpottedByMask & (DWORD64(1) << (entity.ID - 1)))) {
            return true;
        };
        if (entity.isSpotted) {
            return true;
        };
        return false; // 占位
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