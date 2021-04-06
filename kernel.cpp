#include "Includes/text.hpp"

extern "C" void kmain();

using namespace Awkernel;
using namespace Graphics;
void kmain(){
    GraphicsFunctions::ClearScreen(320, 200, 0x07);
    Console console;
    console.WriteChar('H');
    console.WriteChar('e');
    console.WriteChar('l');
    console.WriteChar('l');
    console.WriteChar('o');
    console.WriteChar(' ');
    console.WriteChar('w');
    console.WriteChar('o');
    console.WriteChar('r');
    console.WriteChar('l');
    console.WriteChar('d');
}