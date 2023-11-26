#ifndef _STRING_H
#define _STRING_H

#include "src_info.h"
#include "std_constants.h"
#include "mem_ex.h"

typedef char* string;
typedef unsigned char* string_u;

CORE_H STD_AVAILABLE int strlen_h(register const unsigned char *str);
CORE_H STD_AVAILABLE int strcmp_h(register const unsigned char *str, register const unsigned char *str2);
CORE_H STD_AVAILABLE int strncmp_h(register const unsigned char *str, register const unsigned char *str2, register unsigned int len);

DEFCON_BETA int strmov(register char* from, register char* to);
DEFCON_BETA int strmov_s(register char* from, register char* to, register unsigned int len);
STD_AVAILABLE int strcpy_h(register const unsigned char *from, register unsigned char *to);
STD_AVAILABLE int strcpy_sh(register const unsigned char *from, register unsigned char *to, register unsigned int len);

STD_AVAILABLE int strcat_h(register char *str, register char *str2);
STD_AVAILABLE int strcat_sh(register char *str, register char *str2, unsigned int size);
STD_AVAILABLE int strcat_lh(register char *str, register char *str2, unsigned int len);


int cfind(register const char* str, register const char c);
int cfind_s(register const char* str, register unsigned int len, register const char c);

// return the string length excluding NULL_TERMINATOR '\0'
STD_AVAILABLE int strlen_h(register const unsigned char *str) {
    register const unsigned char* start = str;    /* store the initial string position */
    while (*str != STRING_TERMINATOR) { str++; }    /* loop until string terminator '\0' (0) [FALSE]*/
    return (str - start);    
}

// plain user defined string compare
STD_AVAILABLE int strcmp_h(register const unsigned char *str, register const unsigned char *str2) {
    while (*str == *str2) {
        if (*str2 == STRING_TERMINATOR) return BOOL_E;
        str++; str2++;
    }
    return (*str > *str2) ? BOOL_P : BOOL_N;
}

STD_AVAILABLE int strncmp_h(register const unsigned char *str, register const unsigned char *str2, register unsigned int len){
    
    while (TRUE) {
        if (len == 0) return BOOL_0;
        if (*str != *str2) break;
        if (*str2 == STRING_TERMINATOR) return BOOL_E;
        str++; str2++;
    }
    return (*str > *str2) ? BOOL_P : BOOL_N;    
}

STD_AVAILABLE int strcat_h(register char *str, register char *str2) {
    str += strlen_h(str);
    for (int i = 0; TRUE ; i++, str2++, str++) {
        *str = *str2;
        if (*str2 == STRING_TERMINATOR) return i;
    }
}

// size - size of str buffer
STD_AVAILABLE int strcat_sh(register char *str, register char *str2, register unsigned int size) {
    int i = 0;
    int str_len = strlen_h(str);

    if (str_len >= size) return ERR_INVALID;
    size -= str_len + 1; /* compensate for STRING_TERMINATOR '\0' */
    str  += str_len;
    return strcat_lh(str, str2, size);
}

// len - allowed amount of second string concatenation
STD_AVAILABLE int strcat_lh(register char *str, register char *str2, register unsigned int len) {
    int i = 0;
    str += strlen_h(str);

    for ( ; len != 0; i++, len--) {
        if(*str2 == STRING_TERMINATOR) break;
        *str = *str2;

        str++;
        str2++;
    }
    *str = STRING_TERMINATOR;
    return i;
}

// String move, reset the string in "from" to 0 for safety reason (this is move not copy)
DEFCON_BETA int strmov(register char* from, register char* to) {
    
    char* baseFrom = from;
    for (; TRUE ; ) {
        if ((*to = *from) == STRING_TERMINATOR) break;
        *from = 0;      /* reset the initial data for safety reason */
        from++; to++;   /* assume it's incremented on BYTE level */
    }
    return (from - baseFrom);
}

DEFCON_BETA int strmov_s(register char* from, register char* to, register unsigned int len) {
    char* baseFrom = from;
    for (; len != 0 ; len--) {
        if ((*to = *from) == STRING_TERMINATOR) break;
        *from = 0;      /* reset the initial data for safety reason */
        from++; to++;   /* assume it's incremented on BYTE level */
    }
    return (from - baseFrom);
}

STD_AVAILABLE int strcpy_h(register const unsigned char *from, register unsigned char *to) {
    register unsigned char c;
    byte* init = from;
    for ( ; TRUE ; ) {
        *to = c = *from;
        if (c == STRING_TERMINATOR) break;
        to++; from++;
    }
    return (from - init);
}

STD_AVAILABLE int strcpy_sh(register const unsigned char *from, register unsigned char *to, register unsigned int len) {
    register unsigned char c;
    int i = 0;
    for ( ; len != 0 ; len--, i++) {
        *to = c = *from;
        if (c == STRING_TERMINATOR) break;
        to++; from++;
    }
    return i;
}


// Find nearest ASCII character in a string and returns the postition (returns -1 if FALSE)
int cfind(register const char* str, register const char c) {
    if (str == NULL) return -1; 
    for (register int i = 0; TRUE ; i++, str++) {
        if (*str == c) return i;
        if (*str == STRING_TERMINATOR) return -1;
    }
}

// cfind with safety check (returns -1 if FALSE)
int cfind_s(register const char* str, register unsigned int len, register const char c) {
    if (str == NULL) return -1; 
    int i = len;
    for ( ; len != 0 ; str++, len--) {
        if (*str == c) return (i - len);
        if (*str == STRING_TERMINATOR) break;
    }
    return -1;
}


#endif