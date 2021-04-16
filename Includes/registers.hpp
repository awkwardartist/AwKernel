#pragma once
#include "Types.hpp"
extern "C" {
    struct regs16_t {
        unsigned short di, si, bp, sp, bx, dx, cx, ax;
        unsigned short gs, fs, es, ds, eflags;
    } __attribute__((packed));
    
    void int32(unsigned char intnum, regs16_t* regs);
    void kmain();
}
regs16_t registers;

enum HLRegister {
    bx, dx, cx, ax,
};
// returns a pointer to the register
unsigned short* ToReg(HLRegister Base_Register){
    unsigned short* Reg;
    switch(Base_Register){
        case ax: Reg = &registers.ax;
        break;
        case dx: Reg = &registers.dx;
        break;
        case bx: Reg = &registers.bx;
        break;
        case cx: Reg = &registers.cx;
        break;
        default:
            Reg = &registers.ax;
            break;
    }
    return Reg;
}

/*
    in ax, al = low, and ah = high, this is the same for all HL registers
*/
void SetHighAndLow(HLRegister Base_Register, uint8_t high, uint8_t low){
    uint16_t Value = high; 
    Value >>= 8; // shift high to last 8 bits
    Value |= low; // append with low

    // set value
    *ToReg(Base_Register) = Value;
    
}