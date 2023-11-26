#include <stdio.h>
#include "terminal.h"
#include "test.h"
#include <string.h>

char buf1[0xffffff];
char buf2[0xffffff];
const char* initstr;

int temp_1();
int strcmp_h(register const unsigned char *str, register const unsigned char *str2);

#include <stdalign.h>
int funcs(rgb32_t arg) {
    rgb32 c = (rgb32) {10, 20, 30};
    // *(uint32_t*) &c = 0xff000000;

    uint32_t l = (*(uint32_t*) &(rgb32) {100, 150, 200}  | 0xff000000);
    // *(uint32_t*) &c = ((uint32_t) c  | 0xff000000);

    // c.u = (c.u | 0xff000000);





    return c.b;
}

typedef struct bit32 {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    // uint8_t d;
} bit32;

typedef struct bit32b {
    uint32_t a : 8;
    uint32_t b : 8;
    uint32_t c : 8;
    // uint32_t d : 8;
} bit32b;

int func() {
    char c = 0;

    int g = c;
    return g;
}

int funcb(bit32b a) {
    return a.b;
};

int funcc(register char a, register char b, register char c) {
    return a+b+c;
}

#define _MAXINC(n, max) (n < (max)) ? n++ : (n = 0)

#include <ncurses/curses.h>

int main() {
    int n = 0;
    int j;
    for (int i = 0; i < 10; i++) {
        // j = (n < 2) ? n++ : (n = 0);

        if (n < 2) { j = ++n; }
        else       { j = n = 0; }

        // j = _MAXINC(n, 1);


        printf("n:%d  j: %d\n", n, j);
    }

    // n | 0 1 
    // j | 0 1 
}

int temp_1() {

    __rgb32 fg = 0;
    __rgb32 bg = 0;

    int failcnt = 0;

    int len1, len2;
    int pos1, pos2;
    pos1 = pos2 = 0;

    rgb32_t fg32;
    rgb32_t bg32;

    for (int i = 0; i < 10000; i++, fg++, bg++)
    {
        fg32.u = fg;
        bg32.u = bg;

        len1 = snprintf(&buf1[pos1], 0xffffff, "%s  [%d] r: %3d  g: %3d  b: %3d\n", getTermColour_rgb((rgb32_t) fg32, (rgb32_t) bg32), i, fg32.r, fg32.g, fg32.b);
        len2 = snprintf(&buf2[pos2], 0xffffff, "%s  [%d] r: %3d  g: %3d  b: %3d\n", getTermColour_rgb((rgb32_t) fg32, (rgb32_t) bg32), i, fg32.r, fg32.g, fg32.b);

        if(len1 != len2) {
            testlogWrite(stderr, TEST_FAILED, "[%d] length not same: %d : %d", failcnt, len1, len2);
            failcnt++;
        }
        else
            // testlogWrite(stderr, TEST_SUCCESS, "[%d] length YES: %d : %d  POS: %d : %d", failcnt, len1, len2, __cur_termbufPos, (__curtermbuf - __termbuf2));


        pos1 += len1;
        pos2 += len2;

    }

    int cmpresult;
    if((cmpresult = strcmp_h(buf1, buf2)) != 1) {
        testlogWrite(stderr, TEST_FAILED, "Comparison Failed :%d  [%d]", cmpresult, initstr - buf1);
    }
    else
        testlogWrite(stderr, TEST_SUCCESS, "Comparison Success :%d  [%d]", cmpresult, initstr - buf1);

    printf("%s", buf1);
}


    
int strcmp_h(register const unsigned char *str, register const unsigned char *str2) {
    while (*str == *str2) {
        if (*str2 == '\0') {

            initstr = str;
            return 1;
        }

        // logwrite(stdout, "str1 : str2   |  '%c' : '%c'  |  %d : %d ", *str, *str2, *str, *str2);
        str++; str2++;
    }
    initstr = str;
    return 0;
}