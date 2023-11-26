// #include "lib/mem_man.h"
#include "lib/mem_ex.h"
#include <stdio.h>

// #include "lib/_string.h"
#include <conio.h>

#include <stdlib.h>
#include <windows.h>
int main()
{
    char mem[5] = {5, 0, 45, 23, 90};
    char mem2[5] = {0};

    // [1234567890]         src
    //        [1234567890]  dst
    int start = 3;
    int dst   = 4;
    int len   = 10;
    
    char str[100] =  "1234567890";
    char str2[100] = "1234567890";
    char str3[100] = "1234567890";

    memcpy (&str[dst], &str[start], len);
    memmove(&str2[dst], &str2[start], len);
    memcpy_h(&str3[start], &str3[dst], len);

    // for (int i = 0; i < 5; i++) {
    //     printf("%2d| %d  %d\n", i, mem[i], mem2[i]);
    // }
    printf("memcpy:  %s\n", &str[0]);
    printf("memmove: %s\n", &str2[0]);
    printf("memcpy_H:  %s\n", &str3[0]);
    return strlen(str);
}