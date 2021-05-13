
#pragma once

namespace Awkernel {
    typedef unsigned char byte;
    typedef unsigned long word;
    typedef unsigned char uint8_t;
    typedef unsigned short uint16_t;
    typedef unsigned long uint32_t;
    typedef unsigned long long uint64_t;
    
    template<class T> class List {
    public:
        void Add(T obj) {
            buffer[bufferindex] = obj;
            bufferindex++;
        }
        void AddRange(T obj[]) {
            for(int i = 0; i < sizeof(obj); i++)
                Add(obj[i]);
        }
        T& operator[](int index) {
            return buffer[index];
        }
        
    private:
        int bufferindex = 0;
        T *buffer;
    };
}
