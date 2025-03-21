#pragma once
#ifndef CS2ASSIST_GAME_SYSTEM_MGR_H
#define CS2ASSIST_GAME_SYSTEM_MGR_H

#include <string>
#include <vector>
#include <Windows.h>
namespace CS2Assist {

    // ��Ϸ״̬ö��
    enum class GameState {
        InGame,     // ��Ϸ��
        Loading,    // ������
        Lobby,      // ������
        Unknown     // δ֪״̬
    };

    // ����ʵ�壨�������ԣ�
    struct SmokeEntity {
        float x, y, z;  // λ������
        float duration; // ����ʱ�䣨�룩
    };

    // ���ⵯʵ�壨�������ԣ�
    struct FlashEntity {
        float x, y, z;  // λ������
        float explodeTime; // ��ըʱ�䣨�룩
    };

    // ǹ֧ʵ�壨�������ԣ�
    struct WeaponEntity {
        std::string type; // ǹ֧���ͣ��� "AK47"��
        int ammo;         // ��ҩ����
    };

    class GameSystemMgr {
    public:
        GameSystemMgr(HANDLE processHandle, HMODULE clientModule);
        ~GameSystemMgr();

        // ��ȡ��Ϸ������
        float GetSensitivity() const;
        // ��ȡ��Ļ���
        int GetScreenWidth() const;
        // ��ȡ��Ļ�߶�
        int GetScreenHeight() const;
        // ��ȡ��Ϸ״̬
        GameState GetGameState() const;
        // ��ȡ�Ծֱȷ֣�����1�÷�, ����2�÷֣�
        std::pair<int, int> GetScore() const;
        // ��ȡ��Ϸ��ͼ��
        std::string GetMapName() const;

        // ��ȡ�����б�
        std::vector<SmokeEntity> GetSmokeEntities() const;
        // ��ȡ���ⵯ�б�
        std::vector<FlashEntity> GetFlashEntities() const;
        // ��ȡǹ֧�б�
        std::vector<WeaponEntity> GetWeaponEntities() const;

        // ������Ϸϵͳ����
        void Update();

    private:
        HANDLE hProcess;            // ���̾��
        uint64_t ClientModuleAddress; // �ͻ���ģ���ַ
        // �ɸ�����Ҫ���������Ա����
    };

} // namespace CS2Assist

#endif // CS2ASSIST_GAME_SYSTEM_MGR_H