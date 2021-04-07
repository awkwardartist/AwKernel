#include "Includes/Types.hpp"
#include "Includes/IO.hpp"
#include "Includes/text.hpp"
#include "Includes/keyboard.hpp"

extern "C" {
    void kmain();
}
// using:
using namespace Awkernel;
using namespace Graphics;
using namespace Keyboard;
Console console;
// exec: 
void kmain(){
    GraphicsFunctions::ClearScreen(320, 200, 0x07);
    console.Write("hello, world!");
}