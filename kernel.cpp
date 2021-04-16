#include "Includes/registers.hpp"
#include "Includes/Types.hpp"
#include "Includes/IO.hpp"
#include "Includes/text.hpp"
#include "Includes/keyboard.hpp"
#include "Includes/Thread.hpp"

// using:
using namespace Awkernel;
using namespace Graphics;
using namespace Keyboard;
Console console;

// exec: 
void kmain(){
    GraphicsFunctions::ClearScreen(80, 25, 0x00);
    List<string> ls = List<string>();
    ls.Add("hello, world!");
    ls.Add("hello, world dos!");
    console.Write(ls[0].Value());
    console.Write(ls[1].Value());
}