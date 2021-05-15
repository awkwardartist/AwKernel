#include "Includes/IO.hpp"
#include "Includes/ConsoleMain.hpp"
#include "Includes/Text.hpp"
#include "Includes/Types.hpp"
#include "Includes/FS.hpp"
#include "Includes/Exec.hpp"

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
    Console.Success("Buwut suwuccess\n");
    List<byte> b = List<byte>();
    b.Add(0x2A);
    b.Add(0x20);
    Program p = Program(100, b.ToArray());
    int stack = 0;
    p.Push(10);
    p.Pop((uint32_t*)&stack);
    Console.Write(stack);
}