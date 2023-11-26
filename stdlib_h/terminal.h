#ifndef TERMINAL_MANIPULATION_H
#define TERMINAL_MANIPULATION_H

#include <stdio.h>
#include <stdint.h>
#include "lib/src_info.h"
#include "test.h"

#define NULLSTR ""
const char* __nullstr__ = NULLSTR;

/* 
 * To manipulate the terminal output based on Standard Terminal Drivers (UART)
 * The ANSI escape sequences are the Select Graphic Rendition subset. 
 * All of these have the form
 * "\033[***m"  or  "\r[***m"
 * 
 * where *** is a series of semicolon-separated parameters.
    - StackOverflow
*/

// Based on Standard Terminal
#define CTERM_CSUP       'A'    /* Cursor Up */
#define CTERM_CSDOWN     'B'    /* Cursor Down */
#define CTERM_CSFW       'C'    /* Cursor Forward */
#define CTERM_CSBW       'D'    /* Cursor Backward */
#define CTERM_CSMOV      'H'    /* Cursor Move (Absolute) */
#define CTERM_CSMOV2     'f'    /* Cursor Move (Absolute) 2 */
#define CTERM_CLRSCR     'J'    /* Clear Screen */
#define CTERM_CLRLN      'K'    /* Clear Line */
#define CTERM_EFFECTS    'm'    /* Terminal Output Effects */
#define CTERM_CSSAVE     's'    /* Cursor Position Save */
#define CTERM_CSRESTORE  'u'    /* Cursor Position Restore */

#define TERMCOLOUR_DEFAULT  9
#define TERMCOLOUR_GRAY     0
#define TERMCOLOUR_RED      1
#define TERMCOLOUR_GREEN    2
#define TERMCOLOUR_YELLOW   3
#define TERMCOLOUR_BLUE     4
#define TERMCOLOUR_MAGENTA  5
#define TERMCOLOUR_CYAN     6
#define TERMCOLOUR_WHITE    7

#define RGB_DEFAULT  ((__rgb32) 0xff000000)
#define RGBT_DEFAULT ((rgb32_t) RGB_DEFAULT)

#define TERMCMD_BUFSIZE 0x200

const char* __defaultTermColour__ = "\033[39;49m";
// to support multi call function
TEMPSOL char __termbuf[TERMCMD_BUFSIZE];
TEMPSOL char __termbuf2[TERMCMD_BUFSIZE];
TEMPSOL int __cur_termbufPos = 0;
TEMPSOL signed int __remtermbuf = sizeof(__termbuf);
TEMPSOL char* __curtermbuf = __termbuf2;
TEMPSOL char* __endtermbuf = __termbuf2 + sizeof(__termbuf2);

char* setTerm(int mode, ...);
char* _termmodeGenerate(char mode, ...);

typedef uint32_t __rgb32;
typedef __rgb32 rgb32u;

typedef struct rgb32{

    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb32;

typedef union rgb32_t{
    struct rgb32;
    __rgb32 u;
} rgb32_t;

#define RGB32(r, g, b) (rgb32) {r, g, b}

TEMP __rgb32 rgb(register uint8_t r, register uint8_t g, register uint8_t b) {
    rgb32_t ret = (rgb32_t) {3, 10, 10};
    return ret.u;
}

/* =============== FUNCTION DECLARATION ================ */

TEMP int printCol(int fgcolour, int bgcolour, const char* __format, ...);
TEMP int printCol_rgb(rgb32_t fgColour, rgb32_t bgColour, const char* __format, ...);

const char* getTermColour(int fgcolour, int bgcolour);
    TEMP const char* _getTermColour1(int fgcolour, int bgcolour);
    TEMP const char* _getTermColour2(int fgcolour, int bgcolour);
void  setTermColour(int fgcolour, int bgcolour);
    int _termColour(char* buf, int bufsize, int fgColour, int bgColour);

const char* getTermColour_rgb(rgb32_t fgColour, rgb32_t bgColour);
void  setTermColour_rgb(rgb32_t fgColour, rgb32_t bgColour);
    int getTermColour_rgb_s(char* buf, int bufsize, __rgb32 fgColour, __rgb32 bgColour);
    int _termColour_rgb(register char* _buf, rgb32_t _colour);

/* ======================= END ======================== */

TEMP int printCol(int fgcolour, int bgcolour, const char* __format, ...) {
    va_list __args; va_start(__args, __format);
    setTermColour(fgcolour, bgcolour);

    int _retval = vfprintf(stdout, __format, __args);

    setTermColour(TERMCOLOUR_DEFAULT, TERMCOLOUR_DEFAULT);
    va_end(__args);
    return _retval;
}

TEMP int printCol_rgb(rgb32_t fgColour, rgb32_t bgColour, const char* __format, ...) {
    va_list __args; va_start(__args, __format);
    setTermColour_rgb(fgColour, bgColour);

    int _retval = vfprintf(stdout, __format, __args);

    setTermColour_rgb(RGBT_DEFAULT, RGBT_DEFAULT);
    va_end(__args);
    return _retval;
}


void setTermColour(int fgcolour, int bgcolour) {
    const char* _col = getTermColour(fgcolour, bgcolour);
    fprintf(stdout, "%s", _col);
}

const char* getTermColour(int fgColour, int bgColour) {
    return _getTermColour2(fgColour, bgColour);
}

const char* _getTermColour1(int fgColour, int bgColour) {
    char* curptr;
    fgColour += 30;
    bgColour += 40;

    for (unsigned char attempt = 0 ; 1 ; attempt++) {

        __cur_termbufPos = sizeof(__termbuf) - __remtermbuf;
        curptr = &__termbuf[__cur_termbufPos];
        __remtermbuf -= snprintf(curptr, __remtermbuf, "\x1B[%d;%dm", fgColour, bgColour) + 1;  

        if (__remtermbuf >= 0) 
            break;
        else 
            __remtermbuf = sizeof(__termbuf);

        if (attempt != 0) 
            return NULL;
    }

    return curptr;
}

const char* _getTermColour2(int fgColour, int bgColour) {
    char* __inittermBuf;
    fgColour += 30;
    bgColour += 40;

    for (unsigned char attempt = 0 ; 1 ; attempt++) {
        __inittermBuf = __curtermbuf;
        __curtermbuf += sizeof((char)'\0') + snprintf(__curtermbuf, __endtermbuf - __curtermbuf, "\x1B[%d;%dm", fgColour, bgColour);
        if(__curtermbuf > __endtermbuf) 
            __curtermbuf = __termbuf2;
        else 
            break;

        if (attempt != 0) 
            return NULL;
    }
    return __inittermBuf;
}

int _termColour(char* buf, int bufsize, int fgColour, int bgColour) {
    int len = snprintf(buf, bufsize, "\x1B[%d;%dm", fgColour, bgColour);
    return (bufsize <= len) ? 0 : len;
}

void  setTermColour_rgb(rgb32_t fgColour, rgb32_t bgColour) {
    const char* _col = getTermColour_rgb(fgColour, bgColour);
    fprintf(stdout, "%s", _col);
}

char __fgColourBuf[20];
char __bgColourBuf[20];
const char* getTermColour_rgb(rgb32_t fgColour, rgb32_t bgColour) {
    char* curptr;

    if (fgColour.u != RGB_DEFAULT) sprintf(__fgColourBuf, "38;2;%d;%d;%d", fgColour.r, fgColour.g, fgColour.b);
    else __fgColourBuf[0] = '\0';

    if (bgColour.u != RGB_DEFAULT) sprintf(__bgColourBuf, "48;2;%d;%d;%d", bgColour.r, bgColour.g, bgColour.b);
    else __bgColourBuf[0] = '\0';
    

    for (unsigned char attempt = 0 ; 1 ; attempt++) {

        __cur_termbufPos = sizeof(__termbuf) - __remtermbuf;
        curptr = &__termbuf[__cur_termbufPos];
        __remtermbuf -= snprintf(curptr, __remtermbuf, "\x1B[%s%s%sm", 
                                __fgColourBuf,
                                (__fgColourBuf[0] && __bgColourBuf[0]) ? ";" : "",
                                __bgColourBuf
        ) + 1;  

        if (__remtermbuf >= 0) 
            break;
        else 
            __remtermbuf = sizeof(__termbuf);

        if (attempt != 0) 
            return __defaultTermColour__;
    }

    return curptr;
}

// int _termColour_rgb(register char* _buf, rgb32_t _colour) {
//     if (_colour.u == RGB_DEFAULT) return __nullstr__;

//     sprintf(__fgColourBuf, "38;2;%d;%d;%d", fgColour.r, fgColour.g, fgColour.b);    
// }

#endif