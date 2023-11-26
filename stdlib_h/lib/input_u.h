
#include <stdio.h>

typedef union mbchar {
    unsigned long base;
    char buf8[sizeof(long)];
    short buf16[sizeof(long) / 2];
} mbchar;

int getchar_u8(char* str) {
    mbchar _buf;
    register int len = 0;
    register char c = getchar();

    // switch (c = getchar())
    // {
    
    // case (0x80): return 0; break;
    // case (0x80 | 0x40): len = 1; break;
    // case (0x80 | 0x40 | 0x20): len = 2; break;
    // case (0x80 | 0x40 | 0x20 |0x10): len = 3; break;
    // case (0x80 | 0x40 | 0x20 | 0x10 | 0x08): len = 4; break;
    
    // default: if(c >= 0) {_buf.buf[0] = c; return 1;}
    //     break;
    // }

    // ASCII single byte
    if ((c & 0x80) == 0) {*str = c; return 0;}

    // length check
    while (c & (0x40 >> len)) len++;
    

    for (int i = 0; i < len ; i++) {
        c = getchar();

        // bitflag 10xxxxxx check
        if ( (c & (0x80 | 0x40)) != 0x80 ) return (_buf.base = 0);

        _buf.buf[i] = c;
    }
    
    
};