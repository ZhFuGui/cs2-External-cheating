#ifndef CS2ASSIST_AIM_ASSIST_H
#define CS2ASSIST_AIM_ASSIST_H

#include <Windows.h>
#include "../entity/EntityMgr.h"
#include "../utils/ConstsUtil.h"

namespace CS2Assist {

    // 索敌模式枚举
    enum class TargetMode {
        ClosestDistance,    // 最近距离
        WithinCrosshair,    // 准心范围内
        VisibleEntity,      // 可视实体（无掩体）
        SpecificName,       // 特定名称
        LowestHealth,       // 血量最低
        KnifeOrTaser        // 持刀或电击枪优先
    };

    // 索敌范围设置
    struct TargetScope {
        enum class TargetType {
            EnemiesOnly,    // 仅敌人
            TeammatesOnly,  // 仅队友
            Indiscriminate  // 无差别（除自己外）
        } type = TargetType::EnemiesOnly;

        float horizontalFov = 180.0f; // 水平视角范围 [0, 180] 度
        float verticalFov = 90.0f;    // 垂直视角范围 [0, 90] 度
    };

    class AimAssist {
    public:
        AimAssist(HANDLE processHandle, HMODULE clientModule, Entity* entityList, Entity& local);
        ~AimAssist();

        void MouseAim(TargetMode mode = TargetMode::ClosestDistance, const TargetScope& scope = TargetScope());
        void MemoryAim(TargetMode mode = TargetMode::ClosestDistance, const TargetScope& scope = TargetScope());
        void SilentAim(TargetMode mode = TargetMode::ClosestDistance, const TargetScope& scope = TargetScope());

        bool testThread();
    private:
        HANDLE hProcess;
        uint64_t ClientModuleAddress;
        Entity* entityList;
        Entity& local;

        // 目标选择函数，返回选中的目标实体（若无有效目标则返回无效实体）
        Entity SelectTarget(TargetMode mode, const TargetScope& scope) const;

        // 辅助函数：判断实体是否在视角范围内
        bool IsInFov(const Entity& entity, float horizontalFov, float verticalFov) const;

        // 辅助函数：检查实体是否可视（无掩体）
        bool IsVisible(const Entity& entity) const;

        // 现有辅助函数
        Angle Angle2Arc(const Angle& angle) const;
        Vec3 PosCalibrated(const Vec3& pos, const Angle& eyeArc) const;
        Angle CalcAimAngle(const Angle& targetAngle, const Angle& myEyeAngle) const;
        Angle Target2Me(const Vec3& myPos, const Vec3& targetPos) const;
    };

} // namespace CS2Assist

#endif // CS2ASSIST_AIM_ASSIST_H