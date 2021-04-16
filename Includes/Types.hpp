#pragma once

typedef signed char int8_t;
typedef short int16_t;
typedef long int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
typedef uint8_t byte;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;

class string {
    public:
        // initialize string value
        string() : str(""){}
        string(char* s) : str(s){}
        string(const char* s) : str((char*)s){}

        const char* Value(){return str;}

        // returns the first index of the specified string. if it doesn't contain said string, returns -1.
        int IndexOf(char* value){

            auto text = value;

            for(int i = 0; str[i] != '\0'; i++){
                if(str[i] == text[0]){
                    bool DoesMatch = false;
                    for(int j = 0, x = i; text[j] != '\0'; j++){
                        if(text[j+1] != '\0' && str[x] == text[j] || str[x+1] != '\0' && str[x] == text[j])
                            DoesMatch = true;
                        else if(text[j] != str[x]){
                            DoesMatch = false;
                            break;
                        }
                        x++;
                    }
                    if(DoesMatch){
                        return i;
                    }
                }
            }
            return -1;
        }
        char* Replace(char* old, char* newtext){
            char* ed = "";
            
            if(this->Contains(old)){
                int StartIndex = IndexOf(old);
                for(int i = 0; str[i] != '\0'; i++){
                    if(i == StartIndex){
                        for(int x = 0; newtext[x] != '\0'; x++){
                            ed[i] = newtext[x];
                            i++;
                        }
                    } else {
                        ed[i] = str[i];
                    }
                    
                }
                
            }
            return (char*)this->str;
        }
        int Length(){
            int i = 0;
            for(; str[i] != '\0'; i++);
            return i;
        }
        bool Contains(char* text){
            for(int i = 0; str[i] != '\0'; i++){
                if(str[i] == text[0]){
                    bool DoesMatch = false;
                    for(int j = 0, x = i; text[j] != '\0'; j++){
                        if(text[j+1] != '\0' && str[x] == text[j] || str[x+1] != '\0' && str[x] == text[j])
                            DoesMatch = true;
                        else if(text[j] != str[x]){
                            DoesMatch = false;
                            break;
                        }
                        x++;
                    }
                    if(DoesMatch) return true;
                }
            }
            return false;
        }
    private:
        char* str;
};
template<class T> class List {
    public:
        List(){
            Len = 0;
        }
        List(auto obj[]){
            Len = 0;
            AddRange(obj);
        }
        void Add(T object){
            ARR[Len] = object;
            Len++;
        }
        void AddRange(T object[]){
            int i = 0;
            while(true){
                Add(object[i]);
                i++;
            }
        }
        T operator[](int index) {
            return this->ARR[index];
        }
        
    private:
        
        int Len;
        T * ARR;
};