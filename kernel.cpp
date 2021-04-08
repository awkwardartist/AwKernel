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
    while (true)
        console.WriteChar(console.ReadKey());
}