namespace Awkernel::Graphics {
    static char* GraphicsBuffer = (char*)0xb8000;
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
            void Write(char* ToWrite){
                for(int i = 0; ToWrite[i] != '\0'; i++){
                    WriteChar(ToWrite[i]);
                }
            }
            void WriteChar(char c){
                GraphicsBuffer[position] = c;
                position++;
                GraphicsBuffer[position] = consoleColour;
                position++;
            }
        private:
            unsigned char consoleColour = 0x07;
            int position = 0;
    };
}