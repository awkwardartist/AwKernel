namespace Awkernel::Graphics {
    static char* GraphicsBuffer = (char*)0xb8000;
    class Colour {
        public:
            unsigned int Value = 0x00;
            enum ColourCodes {
                RED, GREEN, BLUE,
                PURPLE, PINK, BLACK, WHITE
            };
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
}