#pragma once
#include "Types.hpp"

using namespace Awkernel;
namespace Awkernel {
   
    class Program {
    private:
        int StackIndex;
        int MaxStackSize;
        uint32_t* Stack;
        uint32_t* StackPointer;
        uint32_t* BasePointer;
        byte* Binary;
        int byteCount = 0;
    public:
        Program(int MaxStackSize, byte bin[]) {
            this->MaxStackSize = MaxStackSize;
            Stack[StackIndex] = 0;
        }
        void Push(uint32_t val) {
            if(StackIndex == MaxStackSize) return;
            Stack[StackIndex] = val;
            StackIndex++;
        }
        void Pop(uint32_t* Location) {
            *Location = Stack[StackIndex - 1];
            if(StackIndex == 0) return;
            StackIndex--;
            Stack[StackIndex] = 0;
        }
    };
}