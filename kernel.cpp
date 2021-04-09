#include "Includes/registers.hpp"
#include "Includes/Types.hpp"
#include "Includes/IO.hpp"
#include "Includes/text.hpp"
#include "Includes/keyboard.hpp"


// using:
using namespace Awkernel;
using namespace Graphics;
using namespace Keyboard;
Console console;

// exec: 
void kmain(){
    Graphics::GraphicsFunctions::ClearScreen(80, 25, 0x00);
    while (true)
        console.WriteChar(console.ReadKey());
}