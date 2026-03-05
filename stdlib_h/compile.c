#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#define TRUE  1
#define FALSE 0

#define RET_TRUE  TRUE
#define RET_FALSE FALSE
#define RET_ERR   -1

#define DISABLED FALSE
#define TEMP(msg)

#define sizeof_arr(arr) (sizeof(arr) / sizeof(*arr))
#define STD_STRING(str, std_str) (str == 0) ? std_str : str 
#define ISBLANK_CMD(c)  ((c == ' ') || (c == '\t'))
#define ISNUM(c)        ((c >= '0') && (c <= '9'))
#define ASCII_ISLOW(c)  ((c >= 'a') && (c <= 'z'))
#define ASCII_ISHIGH(c) ((c >= 'A') && (c <= 'Z'))

// Reset a 1-dimensional array with inlining
#define RESET_ARR(arr, n) for(int i = 0; i < n; i++) {arr[i] = 0;}

#define LOGICAL_XOR(A, B, TRUE, FALSE)  (((A == TRUE) && (B == FALSE)) || ((A == FALSE) && (B == TRUE)))
#define LOGICAL_XOR0(A, B, TRUE)        (((A == TRUE) && !B) || (!A && (B == TRUE)))

// Convert and map any ASCII alphabet character into [a .. z] = [A .. Z] = [1 .. 27] 
#define ASCII_CASECONVERT(c) ASCII_ISHIGH(c) ? (c - 64) : ASCII_ISLOW(c) ? (c - 96) : c
#define ASCII_ISALPHABET(c) (ASCII_ISLOW(c) || ASCII_ISHIGH(c))


// STANDARD PARAMETER
#define STD_STRLEN   512
#define MAX_ARGS     64
#define STD_DIR      "Debug"
#define DEBUG_DIR    "Debug"
#define STD_FILENAME "Filename"

#ifdef _WIN32
#define PATH_SEP '\\'
#define PATH_SEP_STR "\\"
#else
#define PATH_SEP '/'
#define PATH_SEP_STR "/"
#endif

#define DIR_TOKENIZE    0x1
#define DIR_REALNAMEPTR 0x2
#define DIR_MODIFY      0x4
#define DIR_LOCAL       0x8

// #define DIR_STRCMP      0x1


typedef struct filef {
    char buf[0x100];
    char* filename;
    char* fileext;
} filef;


#define HALT_PRESS_ANY_KEY(_msg_) {printf("\n%s\n", _msg_); getch();}
const char* compileCmd_str[] = {
    "Executable File",
    "Assembly",
    "Debug",
    "Optimize",
    "Safe Mode",
    "Specify the Source file",
    "Change Input Directory",
    "Change Output Directory",
    "exit",
    "[EXPERIMENTAL] DIR"
};

char* _filetype[] = {
    "c",
    "h",
    "s",
    "exe",
    ""
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
    IN_DIR,
    OUT_DIR,
    CMD_EXIT,
    DIR
};

#define ERR_FILENAME -1

#define BUFFER_OVERFLOW -101
#define MALLOC_FAILED   -102

#define ERR_DIR_INVALIDPARAM    -101
#define ERR_DIR_INVALIDLOCAL    -102
#define ERR_DIR_NOTFOUND        -103

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

int dirParse(register char* file, filef* fd, int exParam);
int filetype(char* str, char* filetype_collection[]);
char* lastchar(char* str, register char c);
int _word_check(char* collection[], char* str, int n);
int _nstring_check(char* str[]);
int isfullpath_h(char* dir, int n);

int get_localdir(char* buf, char* dir, int bufsize);
int _ndircmp(register char* dir1, register char* dir2, int n, int exParam);

int getargs(char* argv[], int _maxargs);
int _getargs(char* arginput, char* argv[], int _maxargs);
int _setargs(char* arginput, char* _argsbuffer, char* argv[], int _maxargs);
void freeargs(register char* argv[], register int argc);
int _getline(char* buf, int maxlen);
int _strcmp(char* str1, char* str2);
int _printArgs(int argc, char* argv[]);
int strcpyd(char* src, char* dst, int n, char delim);
char* charFind(char* str, char* c, int n);
char* _cfind(char* str, char c, int n);

void printMenu(const char* menu[], int n, int nStart);
int print_cls(char* str, ...);

int compile(int argc, char* argv[], filef* fd, char* filename, char* input_dir, char* output_dir);
int customcmd(int argc, char* argv[]);

// char  rel_path[3] = {'~', PATH_SEP, '\0'}; TEMP(Need more dynamic string)
const char* __border__ = "===========================================================================================";

int main() {

    FILE* source_file = NULL;
    filef fd = { 0 };
    string argv[MAX_ARGS] = { NULL };
    int errcode = 0;
    int argc = 0;
    int arg = -1;
    char filename[STD_STRLEN] = { 0 };

    // char cur_dir[STD_STRLEN] = { 0 };
    char compile_dir[0x400] = { 0 };
    char input_dir[0x400] = { 0 };
    char output_dir[0x400] = STD_DIR;
    char halt = FALSE;

    for (int i = 0; TRUE ; i++) {
        RESET_ARR(cmdbool, TOTAL_CMD_MODE + 1);
        halt = FALSE;

        
        TEMP(Need a better way to parse path directory)
        print_cls("filename: \"%s%s%s%s%s%s\"  => \"%s%s%s\"\n",
            (isfullpath_h(fd.buf, sizeof(fd.buf)) == TRUE) ? "# " : "~ ", // Path type
            (fd.filename == fd.buf) ? "" : fd.buf,          // Directory
            // (fd.filename == fd.buf) ? "" : PATH_SEP_STR,    // Path Separator
            PATH_SEP_STR,                                   // Path Separator
            (fd.filename == fd.fileext) ? "" : fd.filename, // Filename
            (fd.fileext == NULL) ? "" : ".",                // Extension Separator
            (fd.fileext == NULL) ? "" : fd.fileext,         // File Extension

            _fullpath(compile_dir, output_dir, sizeof(compile_dir)), // Output directory
            PATH_SEP_STR,
            fd.filename
        );
        
        printMenu(compileCmd_str, TOTAL_CMD_MODE, EXE_FILE);
        printf("\t[...] custom command\n");
        
        printf("\nmode: ");
        argc = getargs(argv, MAX_ARGS);
        
        TEMP(need an actual error handling possibly by passing argc ptr as parameter)
        if(argc < 0) argc = 0;
        
        arg = atoi(argv[0]);
        switch (arg)
        {
            case FILENAME:
            print_cls("Specify the local path filename: \"$%c...%cfilename\"\n=> ", PATH_SEP, PATH_SEP);
            _getline(filename, sizeof(filename));
            errcode = dirParse(filename, &fd, DIR_REALNAMEPTR | DIR_TOKENIZE | DIR_LOCAL);
            break;
        
        case OUT_DIR:
            print_cls("Specify the output directory: \"$%c{dir}\"\n=> ", PATH_SEP);
            _getline(output_dir, sizeof(output_dir));
            break;
        
        case IN_DIR:
            print_cls("Specify the input directory: \"$%c{dir}\"\n=> ", PATH_SEP);
            _getline(input_dir, sizeof(input_dir));
            break;
        
        case CMD_EXIT:
            exit(0);
            break;

        case DIR:
            systemf("dir");
            halt = TRUE;
            break;
        
        case EXE_FILE: case ASM_FILE: case DEBUG: case OPTIMIZE: case SAFE_MODE:
            // snprintf(filename_buf, sizeof(filename_buf), "%s%s%s", filename_dir, (*filename_dir == '\0') ? "" : "\\", filename);
            compile(argc, argv, &fd, filename, input_dir, output_dir);
            // compile(argc, argv, filename, input_dir, output_dir);
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


int compile(int argc, char* argv[], filef* fd, char* filename, char* input_dir, char* output_dir) {
    int cmd = 0;
    unsigned int optimize = 0;
    char tempbuf[0xff];
    char exParams[0xfff] = "";
    char inputFile[0xfff];
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

    snprintf(inputFile, sizeof(inputFile), "\"%s%s%s%s%s\"",
        (fd->buf == fd->filename) ? "" : fd->buf,           // Directory
        (fd->buf == fd->filename) ? "" : PATH_SEP_STR,      // Directory path separator
        (fd->filename == fd->fileext) ? "" : fd->filename,  // Filename (although with tokenized str the check isn't needed)
        (fd->fileext == NULL) ? "" : ".",                   // Extension dot identifier
        (fd->fileext == NULL) ? ".c" : fd->fileext            // File extension
    );

    // output directory
    TEMP(output file should be updated to be more dynamic especially handling space with double quote)
    if (*output_dir != '\0') { systemf("mkdir %s", output_dir); }
    snprintf(outputfile, sizeof(outputfile), "%s%s%s", output_dir, (*output_dir == '\0') ? "" : "\\", (*fd->filename == '\0') ? STD_FILENAME : fd->filename);

    // main compile
    if(cmdbool[ASM_FILE] == TRUE) systemf("gcc %s -O%d -S -masm=intel %s.c -o \"%s_O%d.s\"", exParams, optimize, inputFile, outputfile, optimize);
    if(cmdbool[EXE_FILE] == TRUE) systemf("gcc %s -O%d %s -o \"%s_O%d\"", exParams, optimize, inputFile, outputfile, optimize);
    if(cmdbool[DEBUG] == TRUE) {
        printf("%s\n\n%47s\n\n%s\n", __border__, "DEBUGGING", __border__);
        systemf("gcc %s -O%d %s -o \"%s_O%d\"", exParams, optimize, inputFile, outputfile, optimize);
        systemf("\"%s_O%d.exe\"", outputfile, optimize);

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
    
    if ((argc == 0) || (argc == BUFFER_OVERFLOW)) free(mainargs_buf);
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

// ================================================================


// ================================================================

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

int strcpyd(char* src, char* dst, int n, char delim) {
    if((src == NULL) || (dst == NULL)) return RET_ERR;
    if(n == 0) n = strlen(src);

    int i = 0;
    for (; i < n; i++) {
        if(src[i] == delim) { break; }
        dst[i] = src[i];
    }
    dst[i] = '\0';
    return i;
}

char* charFind(char* str, char* c, int n) {
    if ((str == NULL) || (c == NULL)) { return NULL; }
    if (n == 0)                       { n = strlen(str); }

    register char ch, *strend, *cend, *tempc;
    cend   = c + strlen(c);
    strend = str + n;

    for ( ; str < strend ; str++) {
        ch = *str;
        for (tempc = c ; tempc < cend ; tempc++){
            if(ch == *tempc) return str;
        }
    }
    return NULL;
}

char* _cfind(char* str, char c, register int n) {
    if(str == NULL) return NULL;
    if(n == 0)      n = strlen(str);

    for ( ; n > 0; n--, str++) {
        if(*str == c) return str;
    }
    return NULL;
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

// ===========================================================================


// ===========================================================================


// Return the modified buffer along with pointer to its associated filename and fileext
// NULL ptr if not found
int dirParse(register char* file, filef* fd, int exParam){
    if((file == NULL) || (strlen(file) == 0) || (fd == NULL)) {
        fd->buf[0] = '\0';
        fd->fileext = fd->filename = NULL;
        return ERR_DIR_INVALIDPARAM;
    }
    
    int errcode;
    char tempbuf[STD_STRLEN];
    char* cch = _cfind(file, '\"', strlen(file));
    if(cch != NULL) strcpyd(++cch, tempbuf, 0, '\"');
    else            strcpy_s(tempbuf, sizeof(tempbuf), file);

    // because the position of local directory is always bigger than its starting point 
    // it is safe to pass tempbuf simultaneously
    if(exParam & DIR_LOCAL)  errcode = get_localdir(tempbuf, tempbuf, sizeof(tempbuf));
    if(exParam & DIR_MODIFY) errcode = strcpy_s(file, sizeof(tempbuf), tempbuf);

    strcpy_s(fd->buf, sizeof(fd->buf), tempbuf);   
    register char *filename_ptr, *fileext_ptr;
    filename_ptr = lastchar(fd->buf, PATH_SEP);
    fileext_ptr  = lastchar(fd->buf, '.');

    /* there are 8 cases
        A. NO DIR                           fname [0, inf]
            - ext < fname   UNDEFINED       []
            - ext NULL      No extension    []
            - ext = fname   Special Files   [0]
            - ext > fname   Normal          [1, inf]

        B. DIR                              fname [1, inf]
            - ext < fname   No extension    []
            - ext NULL      No extension    []
            - ext = fname   Special Files   [1, inf]
            - ext > fname   Normal          [1, inf]
    */

    // directory
    if(filename_ptr == NULL) { filename_ptr = fd->buf; }
    else {
        if (exParam & DIR_TOKENIZE)    { *filename_ptr = '\0'; }
        if (exParam & DIR_REALNAMEPTR) { filename_ptr += 1;    }
    }

    // File extension
    if((fileext_ptr < filename_ptr) || (fileext_ptr == NULL)) { }
    else { 
        if (exParam & DIR_TOKENIZE)    { *fileext_ptr = '\0'; }
        if (exParam & DIR_REALNAMEPTR) { fileext_ptr += 1;    }
    }

    // Hidden, Special file, or no filename 
    // (because buf is guaranteed to have contents it is impossible for both pointers to be NULL)
    // if(/* fileext_ptr == filename_ptr  || */ *filename_ptr == '.') { }

    fd->filename =  filename_ptr;
    fd->fileext  =  fileext_ptr;
    return errcode;
}

// filetype_collection end with "\0", or NULL to default
int filetype(char* str, char* filetype_collection[]) {
    char* dot_pos;
    if((dot_pos = lastchar(str, '.')) != NULL) dot_pos++;
    else return -1; 

    int n;
    if (filetype_collection == NULL) {
        filetype_collection = _filetype;
        n = sizeof(_filetype) / sizeof(char*);
    }
    else n = _nstring_check(filetype_collection);
    return _word_check(filetype_collection, dot_pos, n);
    
}

// get local directory relative from current working directory (buf won't be modified if its invalid)
int get_localdir(char* buf, char* target_dir, int bufsize) {
    if((buf == NULL) || (target_dir == NULL) || (bufsize == 0)) {
        return ERR_DIR_INVALIDPARAM;
    }

    char _curdir[0x200];
    int dirlen = strlen(getcwd(_curdir, sizeof(_curdir)));
    int n      = _ndircmp(_curdir, target_dir, bufsize, 0) + 1;
    
    // Check if it's valid for current local dir
    if(n >= dirlen) { strcpy_s(buf, bufsize, &target_dir[n]); }
    else { return ERR_DIR_INVALIDLOCAL; }
    return n;
}

int _ndircmp(char* dir1, char* dir2, int n, int exParam) {

    int i = 0;
    int lastSeparator = 0;
    register char c1, c2;
    for (; i < n; i++) {
        c1 = dir1[i];
        c2 = dir2[i];
        
    // Handle Case Insensitive path for some systems
    #if _WIN32 || __APPLE__
        c1 = ASCII_CASECONVERT(c1);
        c2 = ASCII_CASECONVERT(c2);
    #endif

        // There are 3 possible value we should check (NULL_TERMINATOR, PATH_SEP, and c1 != c2)
        if((c1 == '\0') && (c2 == '\0')) { 
            lastSeparator = i;
            break;
        }
        if(c1 != c2) {
            if (LOGICAL_XOR(c1, c2, PATH_SEP, '\0')) { lastSeparator = i; }
            break;
        }
        if(c1 == PATH_SEP) lastSeparator = i;
    }   
    return lastSeparator;
}


int isfullpath_h(char* dir, int n) {
    if((dir == NULL) || (n == 0)) 
    return RET_ERR;
    
    int retval = RET_TRUE;
    // based on Windows shell naming conventions (This is only an approximation, works for most but not all)
    // https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file?redirectedfrom=MSDN#fully_qualified_vs._relative_paths
#if _WIN32

    if     (dir[0] == '\\') { }
    else if((dir[0] == '\\') && (dir[1] == '\\')) {}
    else if(ASCII_ISALPHABET(dir[0]) && (dir[1] == ':') && (dir[2] == '\\')) { }

    else {retval = RET_FALSE;}

#elif __linux__
    if(dir[0] == '\\'){}
    else retval = RET_FALSE;
#elif __APPLE__


#endif
    return retval;
}


int _word_check(char* collection[], char* str, int n) {
    for (int k = 0; k < n; k++) {
        char* temp_n = collection[k];
        for (int i = 0; str[i] == temp_n[i] ; i++) {
            if (str[i] == '\0') return (i == 0) ? -1 : k;
        }        
    }
    return -1;
}

char* lastchar(char* str, register char c){
    for (register int i = strlen(str); i >= 0 ; i--) {
        if(str[i] == c) return &str[i];
    }
    return NULL;
}

// {WARNING / UNSAFE} BRUTE FORCE for calculating n of a string collection
int _nstring_check(char* str[]) {
    for (int retval = 0; 1 ; retval++) {
        if(*str[retval] == '\0') return retval;
    }
}
