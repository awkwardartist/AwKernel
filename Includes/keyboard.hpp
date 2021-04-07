#pragma once

extern void Write(char* toWrite);
namespace Awkernel::Keyboard {
    class KernelKeyboard {
        public:
            enum Key {
                A=0x1E, B=0x34, C=0x2E, D=0x20, E=0x12, F=0x21, 
                G=0x22, H=0x23, I=0x17, J=0x24, K=0x25,
                L=0x26, M=0x32, N=0x31, O=0x18, P=0x19, Q=0x10, R=0x13, 
                S=0x1F, T=0x14, U=0x16, V=0x2F, W=0x11, DASH=0x0C, 
                X=0x2D, Y=0x15, Z=0x2C, L_SHIFT=0x2A, R_SHIFT, num1=0x02,
                num2=0x03, num3=0x04, num4=0x05, num5=0x06, num6=0x07, 
                num7=0x08, num8=0x09, num9=0x0A, num0=0x0B, BACK=0x0E, 
                TAB=0x0F, RETURN=0x1C, EQUALS=0x0D, L_ARROW=0x4B, R_ARROW=0x4E, 
                UP_ARROW=0x48, DOWN_ARROW=0x50, ESC=0x01

            };
            static Key GetKey(){
                char old = inb(0x60);
                char newread = old;
                while(newread == old){
                    newread = inb(0x60);
                } 
                newread = inb(0x60);
                return (Key)newread;
            }
            static char GetChar(Key key){
                switch (key)
                {
                    case A:
                        return 'a';
                    case B:
                        return 'b';
                    case C:
                        return 'c';
                    case D:
                        return 'd';
                    case E:
                        return 'e';
                    case F:
                        return 'f';
                    case G:
                        return 'g';
                    case H:
                        return 'h';
                    case I:
                        return 'i';
                    case J:
                        return 'j';
                    case K:
                        return 'k';
                    case L:
                        return 'l';
                    case M:
                        return 'm';
                    case N:
                        return 'n';
                    case O:
                        return 'o';
                    case P:
                        return 'p';
                    case Q:
                        return 'q';
                    case R:
                        return 'r';
                    case S:
                        return 's';
                    case T:
                        return 't';
                    case U:
                        return 'u';
                    case V:
                        return 'v';
                    case W:
                        return 'w';
                    case X:
                        return 'x';
                    case Y:
                        return 'y';
                    case Z:
                        return 'z';
                }
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