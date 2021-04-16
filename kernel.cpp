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
    
    List<char> ls = List<char>();
    ls.Add('h');
    ls.Add('e');
    ls.Add('l');
    ls.Reverse();
    console.WriteChar(ls[0]);
}