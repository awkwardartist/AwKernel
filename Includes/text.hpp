namespace Awkernel::Graphics {
    static char* GraphicsBuffer = (char*)0xb8000;
    class Colour {
        public:
            unsigned int Value = 0x00;
            enum ColourCodes {
                RED, GREEN, BLUE,
                PURPLE, PINK, BLACK, WHITE
            };
            Colour(int Value){
                this->Value = Value;
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
    class Console {
        public:
            int consolePos = 0;
            Colour* consoleColour = new Colour(0x07);
            Console();
            void Write(char* toWrite){
                if(consolePos == undefint)
                    consolePos = 0;
                for(int i = 0; toWrite[i] != '\0'; i++){
                    GraphicsBuffer[consolePos] = toWrite[i];
                    consolePos++;
                    GraphicsBuffer[consolePos] = consoleColour->Value;
                    consolePos++;
                }
            }
        private:
            int undefint;
    };
}