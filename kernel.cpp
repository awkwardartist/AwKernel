#include "Includes/IO.hpp"
#include "Includes/ConsoleMain.hpp"
#include "Includes/Text.hpp"
#include "Includes/Types.hpp"
#include "Includes/FS.hpp"

extern "C" void kmain();
// using:
using namespace Awkernel;
using namespace Files;

// exec: 
void kmain(){
    // Clear Screen
    for(int i = 0; i < 25; i++)
        Console.Write('\n');
    Console.CursorPos = 0;

    Console.Write("Hello, World!");
    auto drives = Drive::FindDrives();
}