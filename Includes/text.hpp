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
            int size_x = 80;
            int size_y = 25;
            int position = 0;
            int consoleColour = 0x07;
            void Write(char* ToWrite){
                for(int i = 0; ToWrite[i] != '\0'; i++){
                    WriteChar(ToWrite[i]);
                }
            }
            void WriteChar(char c){
                if(c == '\n'){
                    int i = position;
                    int j = position;
                    while(i % size_x * 2)
                        i++;
                    position += i * 4;
                    position -= j + (size_x * 2);
                    return;
                } 
                GraphicsBuffer[position] = c;
                position++;
                GraphicsBuffer[position] = consoleColour;
                position++;
            }
    };
}