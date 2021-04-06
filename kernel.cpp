#include "Includes/text.hpp"

extern "C" void kmain();

using namespace Awkernel;
using namespace Graphics;
void kmain(){
    Console* kconsole;
    GraphicsFunctions::ClearScreen(320, 200, 0x07);
    kconsole->Write((char*)"hello, world!");
}