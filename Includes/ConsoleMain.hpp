#pragma once
#include "Text.hpp"

namespace Awkernel {
    // video memory
    char* TextBuffer = (char*)0xb8000; 

    class console {
    public:
        enum ConsoleColor {
            Brown = 0x06,
            Magenta = 0x05,
            Red = 0x04,
            Cyan = 0x03,
            Green = 0x02, 
            Blue = 0x01,
            Black = 0x00,
            Default = 0x07,
            LightGray = 0x07,
        };
        ConsoleColor TextCol = ConsoleColor::Default;
        int CursorPos = 0;
        void Success(char* msg) {
            Write("[ ", ConsoleColor::Default);
            Write("success ", ConsoleColor::Green);
            Write("] ", ConsoleColor::Default);
            Write(msg);
        }
        void Write(char* str, ConsoleColor col) {
            for(int i = 0; str[i] != '\0'; i++)
                Write(str[i], col);
        }
        void Write(char c, ConsoleColor col) {
            ConsoleColor co = TextCol;
            TextCol = col;
            Write(c);
            TextCol = co;
        }
        // write char
        void Write(char c){
            switch(c) {
                case '\n':
                    if(X == 0) 
                        Write(' '); // increment x
                    while(X != 0)
                        Write(' '); // write whole line
                    break;
                default:
                    X++;
                    if(X >= Width) {
                        X = 0;
                        Y++;
                    }
                    TextBuffer[CursorPos] = c;
                    CursorPos += 2;
                    TextBuffer[CursorPos-1] = (char)TextCol;
                    break;
            }
            
        }
        // write string
        void Write(char* c){
            for(int i = 0; c[i] != '\0'; i++)
                Write(c[i]);
            return;
        } 
        void Write(int i) {
            Write(intToString(i));
        }
        void Write(bool b) {
            if(b) Write("True");
            else Write("False");
        }
    private:
        int X = 0;
        int Y = 0;
        int Height = 25;
        int Width = 80;
    };
    console Console;
}



