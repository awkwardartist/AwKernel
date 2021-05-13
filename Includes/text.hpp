#pragma once

namespace Awkernel {
    // yoinked off stack overflow :)
    // also modified a bit lol
    char* intToString(int val, int base=10) {
        bool neg = (val < 0);
        if(neg) val = -(val);
        if(val == 0) return "0";
        static char buf[32] = {0};
        int i = 30;
        for(; val && i ; --i, val /= base)
            buf[i] = "0123456789abcdef"[val % base];
        if(neg) {
            buf[i]='-';
            i--;
        }
        return &buf[i+1];
    }
}