#ifndef CS2ASSIST_ENTITY_MGR_H
#define CS2ASSIST_ENTITY_MGR_H

#include <string>
#include <windows.h>
#include <thread>
#include <cmath>
namespace CS2Assist {
    struct Vec3 {
        float x, y, z;

        float DistanceXY(const Vec3& other) const {
            float dx = other.x - x;
            float dy = other.y - y;
            return std::sqrt(dx * dx + dy * dy);
        };
        Vec3() : x(0), y(0), z(0) {}
        Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    };

    struct Angle {
        float pitch, yaw;
        Angle() : pitch(0), yaw(0) {}
        Angle(float pitch_, float yaw_) : pitch(pitch_), yaw(yaw_) {}
    };

    struct Entity {
        uint16_t ID;
        uint64_t controllerAddr;
        uint64_t pawnAddr;
        std::string name;
        Vec3 lastPosition;
        Vec3 velocity;
        Vec3 acceleration;
        Angle cameraAngle;
        Vec3 cameraPosition;
        Angle eyeAngle;
        int health;
        std::string weaponName;
        int teamId;
        bool isValid;
        bool isSpotted;
        uint32_t SpottedByMask;
        uint32_t IDEntIndex;
        Entity() :
            isSpotted(false),
            IDEntIndex(0),
            ID(0),
            name("Unknown"),
            lastPosition(),
            velocity(),
            acceleration(),
            cameraAngle(),
            eyeAngle(),
            cameraPosition(),
            health(0),
            weaponName("None"),
            teamId(0),
            controllerAddr(0),
            pawnAddr(0),
            SpottedByMask(0),
            isValid(false) {
        };
    };

    class EntityMgr {
    public:
        EntityMgr(HANDLE processHandle, HMODULE clientModule);
        bool GetLocalPlayer(Entity& localEntity);
        bool FetchEntities(Entity* entityList, int maxEntities = 64);
        bool StartEntityUpdateThread(Entity* entityList, Entity& localEntity); // ������������
    private:
        HANDLE hProcess;
        uint64_t ClientModuleAddress;
        uint64_t entityListBase;
        uint64_t controllerBase;

        bool ReadEntityData(uint64_t controllerAddr, uint64_t pawnAddr, Entity& entity);
    };
} // namespace CS2Assist

#endif // CS2ASSIST_ENTITY_MGR_H