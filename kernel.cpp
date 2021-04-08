#include "Includes/registers.hpp"
#include "Includes/Types.hpp"
#include "Includes/IO.hpp"
#include "Includes/text.hpp"
#include "Includes/keyboard.hpp"
#include "AwkFS/ATA.hpp"


// using:
using namespace Awkernel;
using namespace Graphics;
using namespace Keyboard;
Console console;

// exec: 
void kmain(){
    GraphicsFunctions::ClearScreen(25, 80, 0x00);
    if(ATA::ATA::Identify(ATA::ATA::DriveType::MASTER)){
        console.Write("master exists!");
    }
}