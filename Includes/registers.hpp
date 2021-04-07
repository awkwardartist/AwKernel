#pragma once

extern "C" {
    void int32(unsigned char intnum, regs16_t* regs);
    void kmain();
    struct regs16_t {
        unsigned short di, si, bp, sp, bx, dx, cx, ax;
        unsigned short gs, fs, es, ds, eflags;
    } __attribute__((packed));
}
regs16_t registers;

enum HLRegister {
    bx, dx, cx, ax,
};
/*
    in ax, al = low, and ah = high, this is the same for all HL registers
*/
void SetHighAndLow(HLRegister Base_Register, unsigned short high, unsigned short low){
    unsigned short Value = (high << 8) | low;
    switch(Base_Register){
        case bx: registers.bx = Value;
        break;
        case dx: registers.dx = Value;
        break;
        case cx: registers.cx = Value;
        break;
        case ax: registers.ax = Value;
        break;
    }
}