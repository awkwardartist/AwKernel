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
    // to set ah and al, use: ax = (ah_value << 8) | al_value
    SetHighAndLow(HLRegister::ax, 0x00, 0x13);
    int32(0x10, &registers);
}