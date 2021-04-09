#pragma once
#include "keyboard.hpp"

using Awkernel::Keyboard::KernelKeyboard;

namespace Awkernel::Graphics {
    static char* GraphicsBuffer = (char*)0xb8000;
    
    class Cursor {
        public:
            static int GetX(){
                return get_cursor_position() % 80;
            }
            static int GeyY(){
                return get_cursor_position() / 80;
            }
            static void Enable(int cursor_start, int cursor_end){
                outb(0x3D4, 0x0A);
	            outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
	            outb(0x3D4, 0x0B);
	            outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
            }
            static void Disable(){
                outb(0x3D4, 0x0A);
	            outb(0x3D5, 0x20);
            }
            static void Move(int x, int y){
                int size_x = 80;
                int pos = y * size_x + x;

                outb(0x3D4, 0x0F);
                outb(0x3D5, (int) (pos & 0xFF));
                outb(0x3D4, 0x0E);
                outb(0x3D5, (int) ((pos >> 8) & 0xFF));
            }
        private:
            static uint16_t get_cursor_position(void)
            {
                uint16_t pos = 0;
                outb(0x3D4, 0x0F);
                pos |= inb(0x3D5);
                outb(0x3D4, 0x0E);
                pos |= ((uint16_t)inb(0x3D5)) << 8;
                return pos;
            }
    };
    class GraphicsFunctions {
        public:
            /*
               arg1 & 2: screen size in x, y
               colour: the colour to fill in the buffer
               clears in TEXT MODE ONLY
            */
            static void ClearScreen(int x, int y, int colour){
                int max = x * y; 
                for(int i = 0; i < max; i++){
                    GraphicsBuffer[i] = ' ';
                    i++;
                    GraphicsBuffer[i] = colour;
                }
            }
    };
    // P A I N
    char* intToStr(int input){
        // colon is the ascii code after '9'
        char* ret;
        // set all to 0
        for(int i = 0; i < 10; i++) ret[i] = '0';
        for(int i = 0; i < input; i++){
            ret[9]++;
            for(int j = 0; j < 10; j++){
                if(ret[j] == ':'){
                    ret[j] = '0'; 
                    ret[j-1]++;
                }
            }
        }
        for(int i = 0; i < 10; i++){
            if(ret[i] == '0') ret[i] = ' ';
            else break;
        } char* tempc = ret;
        ret = "";
        int index = 0;

        for(int i = 0 ; i < 10; i++){
            if(tempc[i] != ' ' && (int)tempc[i] >= 48 && (int)tempc[i] <= 57){
                ret[index] = tempc[i];
                index++;
            }
        }
        return ret;
    }
    static int position = 0;
    class Console {
        public:
            enum ConsoleColour {
                BLACK = 0x0, BLUE = 0x1, GREEN = 0x2, CYAN = 0x3,
                RED = 0x4, MAGENTA = 0x5, BROWN = 0x6, DEFAULT = 0x7,
                DARK_GRAY = 0x8, LIGHT_BLUE = 0x9, LIGHT_GREEN = 0xA,
                LIGHT_CYAN = 0xB, LIGHT_RED = 0xC, PINK = 0xD, YELLOW = 0xE,
                WHITE = 0xF
            };
            int size_x = 80;
            int size_y = 25;
            int consoleColour = 0x07;

            char ReadKey(){
                char ch = keyboard.GetChar();
                if(ch == 0x0D) ch = 0x00;
                if(ch == 0x00){
                    KernelKeyboard::SpKey key =
                    (KernelKeyboard::SpKey)keyboard.LastScancode();
                    switch(key){
                        case KernelKeyboard::ENTER: return '\n';
                        case KernelKeyboard::DEL: return '\b';
                    }
                } 
                return ch;
            }
            void Write(char* ToWrite){
                for(int i = 0; ToWrite[i] != '\0'; i++){
                    WriteChar(ToWrite[i]);
                }
            }
            void WriteChar(char c){
                if(c == '\n'){
                    // size_x = 80
                    // size_y = 25

                    int xpos = Get_Col(position);
                    position += (size_x - xpos) * 2;
                    Cursor::Move(position / 2, 0);
                    return;
                } else if(c == '\b'){
                    GraphicsBuffer[position] = ' ';
                    GraphicsBuffer[position+1] = 0x07;
                    ShiftAll(position);
                    return;
                }

                GraphicsBuffer[position] = c;
                position++;
                GraphicsBuffer[position] = consoleColour;
                position++;
                Cursor::Move(position / 2, 0);
            }
            void SuccessMessage(char* message){
                consoleColour = ConsoleColour::DEFAULT;
                Write("[ ");
                consoleColour = ConsoleColour::GREEN;
                Write("success ");
                consoleColour = ConsoleColour::DEFAULT;
                Write("] ");
                Write(message + '\n');
            }
            void ErrorMessage(char* message){
                consoleColour = ConsoleColour::DEFAULT;
                Write("[ ");
                consoleColour = ConsoleColour::RED;
                Write("error");
                consoleColour = ConsoleColour::DEFAULT;
                Write("] ");
                Write(message + '\n');
            }
            void DialogueMessage(char* message){
                consoleColour = ConsoleColour::DEFAULT;
                Write("[ ");
                consoleColour = ConsoleColour::CYAN;
                Write("message");
                consoleColour = ConsoleColour::DEFAULT;
                Write("] ");
                Write(message + '\n');
            }
        private:
            void ShiftAll(int startingpos){
                int ogpos = startingpos;
                for(; startingpos < (size_x * size_y) * 2; startingpos++){
                    char temp = GraphicsBuffer[startingpos];
                    GraphicsBuffer[startingpos] = GraphicsBuffer[startingpos+1];
                    GraphicsBuffer[startingpos+1] = temp;
                }
                
                for(startingpos = ogpos; startingpos < (size_x * size_y) * 2; startingpos++){
                    char temp = GraphicsBuffer[startingpos];
                    GraphicsBuffer[startingpos] = GraphicsBuffer[startingpos+1];
                    GraphicsBuffer[startingpos+1] = temp;
                }
                GraphicsBuffer[startingpos] = ' ';
                GraphicsBuffer[startingpos+1]=0x07;
            }
            static Keyboard::KernelKeyboard keyboard;
            int Get_Offset(int x, int y){
                return 2 * (y * size_x + x);
            }
            int Get_Row(int offset){
                return offset / (2 * size_x);
            }
            int Get_Col(int offset){
                return (offset - (Get_Row(offset) * 2 * size_x)) / 2;
            }
    };
}