#pragma once
#include "Types.hpp"

namespace Awkernel {
    class Virtual86CPU {
    public:
        int StackMax = 0;
        enum Register {
            EAX=0, EDX=1, EBX=2, ECX=3, ESP=4,
            EBP=5, ESI=6, EDI=7
        };
        Virtual86CPU(int MaxStackSize, uint32_t InitializerValue) {
            for(int i = 0; i < 8; i++)
                regs[i] = InitializerValue;
            StackMax = MaxStackSize;
        }
        uint32_t* GetReg(Register reg) {
            return &regs[reg];
        }
    private:

        uint32_t regs[8];
    };
}