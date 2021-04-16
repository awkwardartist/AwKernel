#pragma once

#include "Types.hpp"
#include "text.hpp"
using namespace Awkernel::Graphics;

class VirtualCPU {
    public:
        VirtualCPU(){
            VirtualRegister x[8] {
                VirtualRegister("RAX"), VirtualRegister("RBX"),
                VirtualRegister("RCX"), VirtualRegister("RDX"),
                VirtualRegister("RBP"), VirtualRegister("RSP"),
                VirtualRegister("RDI"), VirtualRegister("RSI"),
            };
            for(int i = 0; i < 8; i++){
                regs[i] = x[i];
            }
        }

    private:
        class VirtualRegister {
            public:
                char* Identifier;

                void SetReg(byte b[]){
                    for(int i = 0; i < 64; i++){
                        if(i < sizeof(b)){
                            Data[i] = b[i];
                        } else
                            Data[i] = 0x00;
                    }
                }
                void Set32(byte b[]){
                    for(int i = 0; i < 32; i++){
                        if(i < sizeof(b)){
                            Data[i] = b[i];
                        } else
                            Data[i] = 0x00;
                    }
                }
                void Setlow16(byte b[]){
                    for(int i = 0; i < 16; i++){
                        if(i < sizeof(b)){
                            Data[i] = b[i];
                        } else
                            Data[i] = 0x00;
                    }
                }
                void Sethigh16(byte b[]){
                    for(int i = 15; i < 16; i++){
                        if(i < sizeof(b)){
                            Data[i] = b[i];
                        } else
                            Data[i] = 0x00;
                    }
                } VirtualRegister(){
                    VirtualRegister("RAX");
                }
                VirtualRegister(char* Identifier){
                    this->Identifier = Identifier;
                    for(int i = 0; i < 64; i++)
                        Data[i] = 0x00;
                }
            private:
                byte* Data;
        };
    public:
        VirtualRegister regs[8];
};
