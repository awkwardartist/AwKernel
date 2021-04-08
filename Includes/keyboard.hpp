#pragma once
#include "text.hpp"

namespace Awkernel::Keyboard {
    static regs16_t reg;
    class KernelKeyboard {
        public:
            
            // holds all keys which char code = 0x00, you can cast a scancode as this
            enum SpKey {
                RARR=0x4D, ENTER=0x1C, LARR=0x4B, UARR=0x48, DARR=0x50,
                END=0x4F, HOME=0x47, PgUp=0x49, PgDwn=0x51, DEL=0x53,
                INS=0x52, F1=0x3B, F2=0x3C, F3=0x3D, F4=0x3E, F5=0x3F, 
                F6=0x40, F7=0x41, F8=0x42, F9=0x43, F10=0x44, F11=0x85, 
                F12=0x86
            };
            // use GetChar to get a key character
            static unsigned char GetKeyPress(){
                reg.ax = 0; // set ax 0 (ah and al are 0 now)
                int32(0x16, &reg); // call the interrupt
                /*
                    char ah = (regs.ax & 0xFF00) >> 8;
                    char al = (regs.ax & 0xFF);
                */
               char ah = (reg.ax & 0xFF00) >> 8;
                return ah;
            }
            static unsigned char LastScancode(){
                return (reg.ax % 0xFF00) >> 8;
            }
            static unsigned char GetChar(){
                reg.ax = 0; // set ax 0 (ah and al are 0 now)
                int32(0x16, &reg); // call the interrupt
                /*
                    char ah = (regs.ax & 0xFF00) >> 8;
                    char al = (regs.ax & 0xFF);
                */
                char al = (reg.ax & 0xFF);
                return al; 
            }
            static void Activate(){
                while(inb(0x60) != 0xFA)
                    outb(0x60, 0xF4);
            }
            static void Deactivate(){
                while(inb(0x60) != 0xFA)
                    outb(0x60, 0xF5);
            }
            static unsigned char SendSignal(unsigned char byte){
                outb(0x60, byte);
                return inb(0x60);
            }
        
    };
}