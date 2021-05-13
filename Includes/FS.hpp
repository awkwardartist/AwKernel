#pragma once
#include "registers.hpp"
#include "IO.hpp"
#include "Types.hpp"

using namespace Awkernel;
namespace Awkernel::Files {
    class Drive {
    public:
        static List<Drive> FindDrives() {
            List<Drive> drives = List<Drive>();
            byte ls[] {
                inb(0x1F2), inb(0x1F3), inb(0x1F4), inb(0x1F5),
            };
            bool PacketDevice = false;
            if(ls[0] == 0x01 && ls[1] == 0x01 && ls[2] == 0x00 && ls[3] == 0x00) 
                PacketDevice = false;
            else PacketDevice = true;


        }
    };
}
