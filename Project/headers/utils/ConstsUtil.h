#ifndef CS2ASSIST_CONSTS_UTIL_H
#define CS2ASSIST_CONSTS_UTIL_H
#include <Windows.h>
#include <cmath>

namespace CS2Assist {
    namespace Consts {
        namespace Math {
            constexpr double PI = 3.14159265358979323846;
        }

        namespace Factor {
            constexpr float camera2head_Factor = 6.2f;
            constexpr float Fov_Angle = 95.8807f;
            constexpr float PerAngleInFov_scalingFactor = Fov_Angle * 1920 * 4 / 16200;
        }

        namespace SignCode {
            constexpr const char* BlueXray = "32 C0 48 8B B4 24 ?? 00 00 00 48 8B 9C 24 ?? 00 00 00 48 8B AC 24 ?? 00 00 00 48 81 C4 ?? 00 00 00 41 5F 41 5E 5F";
            constexpr const char* ServerShotAngle = "F3 ?? ?? ?? 10 83 49 10 01 8B 41 10 F3 0F 11 41 18 83 C8 02 F3";
        }

        namespace SilentAim {
            // Shellcode �ֽ��룺�����޸�����ǶȲ��ָ�ԭʼ״̬
            static const BYTE Shellcode[] = {
                // ����Ĵ���״̬
                0x50,                               // push rax                  ���� rax �Ĵ�����ջ��
                0x66, 0x0F, 0xD6, 0x04, 0x24,      // movdqa [rsp], xmm0        ���� xmm0 ��ջ�� (SIMD �Ĵ���)
                0x66, 0x0F, 0xD6, 0x4C, 0x24, 0x10, // movdqa [rsp+16], xmm1     ���� xmm1 ��ջ�� (ƫ�� 16 �ֽ�)
                // �޸����״̬��־ (���� rcx ָ��������ݽṹ)
                0x83, 0x49, 0x10, 0x01,            // or dword ptr [rcx+10], 1  ���ñ�־λ (bit 0)
                0x8B, 0x41, 0x10,                  // mov eax, [rcx+10]         ����־λ���ص� eax
                0x83, 0xC8, 0x02,                  // or eax, 2                 ���ñ�־λ (bit 1)
                0x89, 0x41, 0x10,                  // mov [rcx+10], eax         д�ظ��º�ı�־
                0x83, 0xC8, 0x04,                  // or eax, 4                 ���ñ�־λ (bit 2)
                // ���ز�д���µ�����Ƕ� (pitch �� yaw)
                0xF3, 0x0F, 0x10, 0x05, 0x00, 0x00, 0x00, 0x00, // movss xmm0, [rip + pitchOffset]  ���ڴ���� pitch ֵ�� xmm0
                0xF3, 0x0F, 0x10, 0x0D, 0x00, 0x00, 0x00, 0x00, // movss xmm1, [rip + yawOffset]    ���ڴ���� yaw ֵ�� xmm1
                0xF3, 0x0F, 0x11, 0x49, 0x18,      // movss [rcx+18], xmm1      �� yaw ֵд������ǶȽṹ (ƫ�� 0x18)
                0xF3, 0x0F, 0x11, 0x41, 0x1C,      // movss [rcx+1C], xmm0      �� pitch ֵд������ǶȽṹ (ƫ�� 0x1C)
                // �ָ�ԭʼ״̬
                0xF3, 0x0F, 0x10, 0x47, 0x18,      // movss xmm0, [rdi+18]      ��ԭʼ���ݻָ� xmm0 (���� rdi ָ��ԭʼ�Ƕ�)
                0x66, 0x0F, 0xD6, 0x4C, 0x24, 0x10, // movdqa xmm1, [rsp+16]     ��ջ�ָ� xmm1
                0x66, 0x0F, 0xD6, 0x04, 0x24,      // movdqa xmm0, [rsp]        ��ջ�ָ� xmm0
                0x58,                               // pop rax                   ��ջ�ָ� rax
                // ����ԭʼ������
                0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, returnAddr       �����ص�ַ���ص� rax
                0xFF, 0xE0                          // jmp rax                   ��ת��ԭʼ����
            };

            // JmpPatch �ֽ��룺���ڽ���������ת�� shellcode
            static const BYTE JmpPatch[] = {
                0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, shellcodeAddr    �� shellcode ��ַ���ص� rax
                0xFF, 0xE0,                                                 // jmp rax                   ��ת�� shellcode
                0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // nop                       ��� nop (10 ��)
                0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, // nop                       ��� nop (10 ��)
                0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90       // nop                       ��� nop (9 ��)
            };


            // Shellcode �еĹؼ�ƫ��
            static constexpr size_t PitchOffsetPos = 32; // pitch ƫ���� shellcode �е�λ��
            static constexpr size_t YawOffsetPos = 40;   // yaw ƫ���� shellcode �е�λ��
            static constexpr size_t ReturnAddrPos = 73;  // ���ص�ַ�� shellcode �е�λ��
            static constexpr size_t ShellcodeAddrPos = 2;// shellcode ��ַ�� jmpPatch �е�λ��
            static constexpr size_t ShellcodeSize = sizeof(Shellcode); // shellcode ��С
            static constexpr size_t JmpPatchSize = sizeof(JmpPatch);   // jmpPatch ��С
        }
    }
}

#endif // CS2ASSIST_CONSTS_UTIL_H