#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <stdarg.h>
#include "mem_ex.h"
#include "_stream.h"

#define NULLSTR ""
#define STRING_TERMINATOR '\0'

#define PAGESIZE 0x1000


int _printstr(FILE* _stream, char* str, ...);

const char* cloneCh_c(register const char c, unsigned int n);
int cloneCh(register char* _buf, register const char c, int n);
int cloneCh_s(register char* _buf, int _bufsize, register const char c, int n);
int cloneChf(register FILE* _stream, register const char c, int n);
    int _cloneCh(register char* _buf, register const char c, int n);


int _printstr(FILE* _stream, char* str, ...) {
    va_list __args; va_start(__args, str);
    char* cur_str = str;
    int len = 0;

    for (int i = 0; cur_str != NULL ; i++) {
        len += fprintf(_stream, cur_str);
        cur_str = va_arg(__args, char*);
    }
    va_end(__args);
    return len;
}


#ifndef CLONE_CHAR
int cloneCh(register char* _buf, register const char c, int n) {
    int i;
    for(i = 0 ; i < n ; i++, _buf++) { *_buf = c; }
    *_buf = STRING_TERMINATOR;

    return i;
}

int cloneCh_s(register char* _buf, int _bufsize, register const char c, int n) {
    register char* _endbuf = _buf + _bufsize;
    int i;
    for(i = 0 ; i < n ; i++, _buf++){
        if (_buf >= _endbuf) return -1;
        *_buf = c;
    }
    return i;
}

const char* cloneCh_c(register const char c, unsigned int n) {
    if (n >= PAGESIZE) return NULLSTR;

    register char* ptr = (char*) _getOStream(n);
    cloneCh(ptr, c, n);
    return ptr;
}

int cloneChf(register FILE* _stream, register const char c, int n) {
    if(_stream == NULL) return -1;

    int i = 0;
    if(n > sizeof(__mainOBuf)) {
        for ( ; i < n ; i++) putc(c, _stream);
    }
    else {
        i = cloneCh(__mainOBuf, c, n);
        fwrite(__mainOBuf, sizeof(c), n, _stream);
    }

    return i;
}
#endif



#endif