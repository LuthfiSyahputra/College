#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

#define TRUE  1
#define FALSE 0

#define DISABLED FALSE

#define sizeof_arr(arr) (sizeof(arr) / sizeof(*arr))
#define STD_STRING(str, std_str) (str == 0) ? std_str : str 
#define ISBLANK_CMD(c)  ((c == ' ') || (c == '\t'))
#define ISNUM(c)        ((c >= '0') && (c <= '9'))

#define STD_STRLEN  512
#define MAX_ARGS    64
#define STD_DIR     "Debug"

// Reset a 1-dimensional array with inlining
#define RESET_ARR(arr, n) for(int i = 0; i < n; i++) {arr[i] = 0;}

#define HALT_PRESS_ANY_KEY(_msg_) {printf("\n%s\n", _msg_); getch();}
const char* compileCmd_str[] = {
    "Executable File",
    "Assembly",
    "Debug",
    "Optimize",
    "Safe Mode",
    "Change File Name",
    "Change Output Directory",
    "exit",
    "[EXPERIMENTAL] DIR"
};

#define TOTAL_CMD_MODE (sizeof(compileCmd_str) / sizeof(char*))

char cmdbool[TOTAL_CMD_MODE + 1] = {0};

enum {
    EXE_FILE = 1,
    ASM_FILE,
    DEBUG,
    OPTIMIZE,
    SAFE_MODE,
    FILENAME,
    OUT_DIR,
    CMD_EXIT,
    DIR
};

#define ERR_FILENAME 1

#define BUFFER_OVERFLOW -1
#define MALLOC_FAILED   -2


typedef char* string;

#define CLR_INBUF while(getchar() != '\n');
int clr_inbuf(void) { CLR_INBUF }

unsigned int sys_count = 0;
clock_t _globalClock = 0;

char __sysbuf[STD_STRLEN] = { 0 };
char* argv[64] = { NULL };

int system_h(const char* __command);
int _systemf(const char* __cmdformat, va_list __local_args);
int systemf(const char* __cmdformat, ...);
int systemf_s(const char* __cmdformat, ...);

clock_t clockElapsed(register clock_t* _lastClock);
clock_t _clockElapsed();

int getargs(char* argv[], int _maxargs);
int _getargs(char* arginput, char* argv[], int _maxargs);
int _setargs(char* arginput, char* _argsbuffer, char* argv[], int _maxargs);
void freeargs(register char* argv[], register int argc);
int _getline(char* buf, int maxlen);
int _strcmp(char* str1, char* str2);
int _printArgs(int argc, char* argv[]);

void printMenu(const char* menu[], int n, int nStart);
int print_cls(char* str, ...);

int compile(int argc, char* argv[], char* filename, char* output_dir);
int customcmd(int argc, char* argv[]);

const char* __border__ = "===========================================================================================";

int tempcompile(int argc, char* argv[]) {

    char str[STD_STRLEN];
    char dir[STD_STRLEN];


    if(argc < 1) {
        fprintf(stderr, "%s", "Please specify the filename (excluding the extension)\n");
        return 0;
    }
    
    // make directory
    snprintf(dir, STD_STRLEN, "%s", (argc >= 2) ? argv[1] : STD_DIR);


    systemf("mkdir %s", dir);
    system("cls");

    // compile border
    printf("%s\n\n\n%s\n", __border__, __border__);

    // main executable
    systemf_s("gcc %s.c -o %s/%s", argv[0], dir, argv[0]);

    // // main optimized
    // systemf_s("gcc -O4 %s.c -o %s/%s_optimized", argv[0], dir, argv[0]);

    // // main asm
    // systemf_s("gcc -S -masm=intel %s.c -o %s/%s.s", argv[0], dir, argv[0]);

    // // unoptimized asm
    // systemf_s("gcc -O1 -S -masm=intel %s.c -o %s/%s_unoptimized.s", argv[0], dir, argv[0]);

    // // optimized asm
    // systemf_s("gcc -O4 -S -masm=intel %s.c -o %s/%s_optimized.s", argv[0], dir, argv[0]);

    // // dirctory check
    // systemf_s("dir %s", dir);

    // open the file
    printf("%s", "\n================= DEBUG MODE ==================\n\n");
    systemf_s("%s\\%s", dir, argv[0]);

    // test file (if exist)
    if(argc >= 4) {
        snprintf(str, STD_STRLEN, "gcc %s.c -o %s/%s", argv[3], dir, argv[3]);
        system_h(str);

        snprintf(str, STD_STRLEN, "%s\\%s", dir, argv[3]);
        system_h(str);
    }


}

int main() {

    FILE* source_file = NULL;
    string argv[MAX_ARGS] = { NULL };
    int errcode = 0;
    int argc = 0;
    int arg = -1;
    char filename_buf[0x400] = { 0 };
    char output_dir[0x400] = STD_DIR;
    char halt = FALSE;

    for (int i = 0; TRUE ; i++) {
        RESET_ARR(cmdbool, TOTAL_CMD_MODE + 1);
        halt = FALSE;

        print_cls("filename: \"%s\"  => \"%s/%s\"\n", filename_buf, output_dir, filename_buf);
        printMenu(compileCmd_str, TOTAL_CMD_MODE, EXE_FILE);
        printf("\t[...] custom command\n");

        printf("\nmode: ");
        argc = getargs(argv, MAX_ARGS);
        
        arg = atoi(argv[0]);
        switch (arg)
        {
        case FILENAME:
            print_cls("Specify the local path filename: \"$/.../filename\" (no extension)\n=> ");
            _getline(filename_buf, sizeof(filename_buf));
            break;
        
        case OUT_DIR:
            print_cls("Specify the output directory: \"$/{dir}\"\n=> ");
            _getline(output_dir, sizeof(output_dir));
            break;
        
        case CMD_EXIT:
            exit(0);
            break;

        case DIR:
            systemf("dir");
            halt = TRUE;
            break;
        
        case EXE_FILE: case ASM_FILE: case DEBUG: case OPTIMIZE: case SAFE_MODE:
            compile(argc, argv, filename_buf, output_dir);
            halt = TRUE;
            break;

        default :
            customcmd(argc, argv);
            halt = TRUE;
        }

        if (halt == TRUE) HALT_PRESS_ANY_KEY("Press any key to continue...");
        freeargs(argv, argc);
    }
}


int compile(int argc, char* argv[], char* filename, char* output_dir){
    int cmd = 0;
    unsigned int optimize = 0;
    char tempbuf[0xff];
    char exParams[0xfff] = "";
    char outputfile[0xfff];

    // set all compile flags from the args input
    for (int i = 0; i < argc; i++) {
        cmd = atoi(argv[i]);
        cmdbool[((cmd >= 0) && (cmd < TOTAL_CMD_MODE)) ? cmd : TOTAL_CMD_MODE] = TRUE;
    }

    // OPTIMIZE
    if(cmdbool[OPTIMIZE] == TRUE) {
        printf("Optimize level (0 ~ 4): ");
        _getline(tempbuf, sizeof(tempbuf));
        optimize = atoi(tempbuf);
        optimize = (optimize > 4) ? 0 : optimize;
    }

    // SAFETY CHECK
    if(cmdbool[SAFE_MODE] == TRUE) {
        snprintf(tempbuf, sizeof(tempbuf), "-pedantic -Werror");
        strcat(exParams, tempbuf);
    }
    
    // output directory
    if (*output_dir != '\0') { systemf("mkdir %s", output_dir); }
    snprintf(outputfile, sizeof(outputfile), "%s%s%s", output_dir, (*output_dir == '\0') ? "" : "\\", filename);

    // main compile
    if(cmdbool[ASM_FILE] == TRUE) systemf("gcc %s -O%d -S -masm=intel %s.c -o %s_O%d.s", exParams, optimize, filename, outputfile, optimize);
    if(cmdbool[EXE_FILE] == TRUE) systemf("gcc %s -O%d %s.c -o %s_O%d", exParams, optimize, filename, outputfile, optimize);
    if(cmdbool[DEBUG] == TRUE) {
        printf("%s\n\n%47s\n\n%s\n", __border__, "DEBUGGING", __border__);
        systemf("gcc %s -O%d %s.c -o %s_O%d", exParams, optimize, filename, outputfile, optimize);
        systemf("%s_O%d.exe", outputfile, optimize);

    }
}

int customcmd(int argc, char* argv[]) {
    if (argc == 0) return 0;

    register char* buffer = argv[0];
    for (int n = 0; n < argc - 1 ; buffer++){
        if(*buffer == '\0') { *buffer = ' '; n++; }
    }

    return systemf("%s", argv[0]);
}

/* =============================================================================== */


/* =============================================================================== */

int getargs(register char* argv[], int _maxargs) {
    if ( 0 == _getline(__sysbuf, sizeof(__sysbuf)))
        return 0;

    return _getargs(__sysbuf, argv, _maxargs);
}

// 
int _getargs(register char* arginput, register char* argv[], int _maxargs) {
    register char* mainargs_buf = NULL;
    int len = strlen(arginput);

    if((mainargs_buf = (char*) malloc(len)) == NULL)
        return MALLOC_FAILED;

    int argc = _setargs(arginput, mainargs_buf, argv, _maxargs);
    
    if ((argc == 0) || (argc == -1)) free(mainargs_buf);
    return argc;
}

// set every arginput to argsbuffer where argv is the index position of every arguments in argsbuffer
// arginput:    lorem    ipsum  color   12   345 67
// argsbuf :    lorem ipsum color 12 345 67     (every blank is a '\0')
// argv    :    ^     ^     ^     ^  ^   ^      (argc: 6)
int _setargs(char* arginput, register char* _argsbuffer, char* argv[], int _maxargs) {

    int argc = 0;
    register char c;
    register int charcnt = 0;
    for (int i = 0; 1 ; i++) {
        c = arginput[i];

        (ISBLANK_CMD(c)) ? (charcnt = 0) : charcnt++;

        if (c == '\0')       { *_argsbuffer = '\0'; break; } /* null terminator */
        if (argc > _maxargs) { argc = BUFFER_OVERFLOW; break ; }
        
        /* first character in an argument */
        if (charcnt == 1) {
            if (argc != 0) _argsbuffer++;
            argv[argc++] = _argsbuffer; /* register */
        }

        if (charcnt != 0) { *_argsbuffer++ = c; }
        else              { *_argsbuffer = '\0'; }
    }
    return argc;
}


void freeargs(register char* argv[], register int argc) {
    free(argv[0]);
    while (argc) { argv[--argc] = NULL; }   
}

int system_h(const char* __command) {
    int retval = system(__command);
    printf("[%u] (%4dms) system: %5d  { %s }\n", sys_count++, _clockElapsed(), retval, __command);

    return retval;
}


int systemf(const char* __cmdformat, ...) {
    va_list _args; va_start(_args, __cmdformat);
    int retval = _systemf(__cmdformat, _args);
    va_end(_args);
    return retval;
}

// systemf() but will immediately abort programs if not return 0
int systemf_s(const char* __cmdformat, ...) {
    va_list _args; va_start(_args, __cmdformat);
    int retval = _systemf(__cmdformat, _args);
    va_end(_args);
    if (retval != 0) exit(retval);
    return retval;
}


int _systemf(const char* __cmdformat, va_list __local_args) {
    int len, retval;
    
    len = vsnprintf(__sysbuf, 512, __cmdformat, __local_args);
    retval = system_h(__sysbuf);

    return retval;
}

int _getline(register char* buf, int maxlen) {
    register char c;
    register char* endbuf = buf + maxlen;
    char* initbuf = buf;

    for ( ; (c = getchar()) ; buf++) {
        if (buf >= endbuf) { 
            (c == '\n') ? 0 : clr_inbuf(); 
            return 0;
        }

        if (c == '\n') break;
        *buf = c;
    }

    *buf = '\0';
    return buf - initbuf;
}

clock_t clockElapsed(register clock_t* _lastClock) {
    register clock_t tempClock = *_lastClock;
    return ((*_lastClock = clock()) - tempClock);
}

clock_t _clockElapsed() {
    register clock_t lastclock = _globalClock;
    return ((_globalClock = clock()) - lastclock); 
}

int _strcmp(char* str1, char* str2) {
    while (*str1 == *str2) {
        if(*str1 == '\0') return 1;
        str1++; str2++;
    }
    return 0;
}

int _printArgs(int argc, char* argv[]) {
    printf("arguments: \n");
    for (int i = 0; i < argc; i++) {
        printf("[%2d] %s\n", i, argv[i]);
    }
    return argc;
}

void printMenu(const char* menu[], int n, int nStart) {
    for (int i = 0; i < n; i++) {
        printf("\t[%d] %s\n", i + nStart, menu[i]);    
    }
}

int print_cls(char* str, ...) {
    va_list local_argv; va_start(local_argv, str);
    system("cls");
    int retval = vprintf(str, local_argv);
    va_end(local_argv);
    return retval;
}