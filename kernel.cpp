#include "Includes/text.hpp"

extern "C" void kmain();

using namespace Awkernel;
using namespace Graphics;
void kmain(){
    Console* kconsole=new Console();
    GraphicsFunctions::ClearScreen(320, 200, 0x07);
    kconsole->WriteChar('X');
}