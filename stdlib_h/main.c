/* #include "lib/datatype.h" */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __GNUC__
#endif

#define rgb32u(r, g, b) ((((((uint8_t)b << 8) | (uint8_t)g) << 8) | (uint8_t)r) | 0xff000000U)
#define rgb32s(r, g, b) (rgb) {r, g, b, 0xffu}

#define CLR_INBUF while(getchar() != '\n');
#define ISBLANK_CMD(c) ((c == ' ') || (c == '\t'))

char __sysbuf[512];

int _getline(register char* buf, int maxlen) {
    register char c;
    register char* endbuf = buf + maxlen;
    char* initbuf = buf;

    for ( ; buf < endbuf ; buf++) {
        c = getchar();
        if (c == '\n') { *buf = '\0'; return buf - initbuf; }
        *buf = c;
    }
    CLR_INBUF;
    return 0;
}
char* base = NULL;
int getargs(const char* argv[], int _maxargs) {
    int len = _getline(__sysbuf, sizeof(__sysbuf)) + 1;
    
    char* baseargs = (char*) malloc(len);
    if(baseargs == NULL) return -1;
    
    char* mainargv = baseargs;
    int argc = 0;
    register char c;
    register int charcnt = 0;
    for (int i = 0; 1 ; i++) {
        c = __sysbuf[i];

        (ISBLANK_CMD(c)) ? (charcnt = 0) : charcnt++;

        if (c == '\0') { *mainargv = '\0'; break;} /* null terminator */
        if (argc > _maxargs) {argc = -1; break;}
        
        /* first character in an argument */
        if (charcnt == 1) {
            if (argc != 0) mainargv++;
            argv[argc++] = mainargv; /* register */
        } 

        if (charcnt != 0) { *mainargv++ = c; }
        else              { *mainargv = '\0'; }
    }
    
    if ((argc == 0) || (argc == -1)) free(baseargs);
    return argc;
}

int main() {

    const char* argv[20];
    int argc = getargs(argv, 3);
    ptrdiff_t diff;
        printf("pass");

    for (int i = 0; i < argc; i++) {
        printf("%2d| [%4u/%4u] : %s|\n", i, argv[i] - argv[0], argv[i] - base,argv[i]);
    }
    
}