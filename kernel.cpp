#include "Includes/text.hpp"
#include "Includes/keyboard.hpp"
#include "Includes/IO.hpp"

extern "C" void kmain();

// using:
using namespace Awkernel;
using namespace Graphics;
using namespace Keyboard;
using namespace IO;

Console console;
// exec: 
void kmain(){
    GraphicsFunctions::ClearScreen(320, 200, 0x07);
    IOFunctions::inb(0x60);
    console.Write("Hello, world!\nsome newline, huh.");
}