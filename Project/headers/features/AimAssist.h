#ifndef CS2ASSIST_AIM_ASSIST_H
#define CS2ASSIST_AIM_ASSIST_H

#include <Windows.h>
#include "../entity/EntityMgr.h"
#include "../utils/ConstsUtil.h"

namespace CS2Assist {

    // ����ģʽö��
    enum class TargetMode {
        ClosestDistance,    // �������
        WithinCrosshair,    // ׼�ķ�Χ��
        VisibleEntity,      // ����ʵ�壨�����壩
        SpecificName,       // �ض�����
        LowestHealth,       // Ѫ�����
        KnifeOrTaser        // �ֵ�����ǹ����
    };

    // ���з�Χ����
    struct TargetScope {
        enum class TargetType {
            EnemiesOnly,    // ������
            TeammatesOnly,  // ������
            Indiscriminate  // �޲�𣨳��Լ��⣩
        } type = TargetType::EnemiesOnly;

        float horizontalFov = 180.0f; // ˮƽ�ӽǷ�Χ [0, 180] ��
        float verticalFov = 90.0f;    // ��ֱ�ӽǷ�Χ [0, 90] ��
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

        // Ŀ��ѡ����������ѡ�е�Ŀ��ʵ�壨������ЧĿ���򷵻���Чʵ�壩
        Entity SelectTarget(TargetMode mode, const TargetScope& scope) const;

        // �����������ж�ʵ���Ƿ����ӽǷ�Χ��
        bool IsInFov(const Entity& entity, float horizontalFov, float verticalFov) const;

        // �������������ʵ���Ƿ���ӣ������壩
        bool IsVisible(const Entity& entity) const;

        // ���и�������
        Angle Angle2Arc(const Angle& angle) const;
        Vec3 PosCalibrated(const Vec3& pos, const Angle& eyeArc) const;
        Angle CalcAimAngle(const Angle& targetAngle, const Angle& myEyeAngle) const;
        Angle Target2Me(const Vec3& myPos, const Vec3& targetPos) const;
    };

} // namespace CS2Assist

#endif // CS2ASSIST_AIM_ASSIST_H