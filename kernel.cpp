#include "Includes/text.hpp"
#include "Includes/keyboard.hpp"

extern "C" {
    void kmain();
    void outb (unsigned char __value, unsigned short int __port);
}
// using:
using namespace Awkernel;
using namespace Graphics;
using namespace Keyboard;
Console console;
// exec: 
void kmain(){
    GraphicsFunctions::ClearScreen(320, 200, 0x07);
    Cursor::Enable(0, 15);

}