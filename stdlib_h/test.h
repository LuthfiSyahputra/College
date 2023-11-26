#ifndef TEST_HEADER
#define TEST_HEADER

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

typedef unsigned char testbool;
typedef unsigned long long testbool_p;

#define WIN_DEFINED (_WIN32 || _WIN64 || __WIN32 || __WIN64 || __WIN32__ || __WIN64__ || __WINNT || __WINNT__)
#define RETURN_TIME 1

#define TEST_STATE   5

#define TEST_FAILED  0
#define TEST_SUCCESS 1
#define TEST_NORMAL  2
#define TEST_UNKNOWN 3
#define TEST_INVALID 4

#define PARENT  0
#define CHILD   (!PARENT)

#define PRINT_MODE  1
#if WIN_DEFINED
#define DIRECTORY_SIGN  '\\'
#define DEFAULT_LOGDIR  "test\\log"
#else
#define DIRECTORY_SIGN  '/'
#define DEFAULT_LOGDIR  "test/log"
#endif

#define STDIN_BUFCLEAR while(getchar() != '\n');

#define TEST_HALT   {printf("===== press any key ====="); while(1) if(_kbhit()) {printf("%s", __clrline__); break;} }
const char* __clrline__ = "\r\33[K";
const char* __clrscr__  = "\33[2J\33[H";

const char* __testerrSign__ = "\033[1;38;2;255;0;0mTEST_ERROR\033[0;39m";


int testSummary(int nTest, ...);
int testArrSummary(testbool result[], int n);
int printResult(testbool result, const char* testname, char* _format, ...);

int _testprompt(const char* _msg, ...);

// TIME
clock_t __globalLastClock = 0;
clock_t _startclock = 0;
time_t __globalTestTime = 0;
time_t* __globalTestTimeptr = &__globalTestTime;

#define SET_TESTCLK (_startclock = clock())
#define END_TESTCLK (clock() - _startclock)

#define ELAPSED_CLK(lastclock) (clock() - lastclock)

clock_t _clockElapsed(void);
clock_t clockUpdateElapsed(clock_t* _lastclock);
time_t* timeptr(void) { time(__globalTestTimeptr); return __globalTestTimeptr;}
#define CUR_TIME localtime(timeptr())


#if PRINT_MODE

#define TEST_STDBUFLEN    0xff
char _testlogbuf[TEST_STDBUFLEN]      = { 0 };
char _testlocationbuf[TEST_STDBUFLEN] = { 0 };
char _testtimebuf[0x20]               = { 0 };
char _testerrbuf[0x200]               = { 0 };
char _testdirbuf[TEST_STDBUFLEN]      = { 0 };

unsigned long lastLogLen = 0;

// PRINT MODE REQUIRED (logfile)
int __checkdir(register char* _dir);
char* __checkdir_s(const char* dir);

FILE* _openFile(const char* restrict dir, const char* restrict mode, const char* _errormsg, ...);
int _closeFile(FILE** file, const char* _errormsg, ...);
int _deleteFile(const char* restrict dir, const char* _errormsg, ...);

FILE* openTempFile(const char* restrict dir);
FILE* createTempFile(const char* restrict dir);
void deleteTempFile(FILE** file, const char* restrict dir);

FILE* testlogCreate(const char* dir);
void testlogClose(FILE** file);

int testlogWrite(FILE* file, testbool test, const char* str, ...);
int testlogWritef(const char* restrict dir, testbool test, const char* str, ...);
    int _vtestlogWrite(FILE* file, testbool test, const char* str, va_list __args);

int logwrite(FILE* file, const char* str, ...);
int logwritef(const char* restrict dir, const char* str, ...);
    int _vlogWrite(FILE* file, const char* str, va_list __args);


// misc
char* _tabCreate(int n, unsigned char tablen);
char* _testlocate(const char *filename, const char *funcname, int linenum);
#define TEST_LOCATION   _testlocate(__FILE__, __func__, __LINE__)
#define TEST_TAB(level, space) _tabCreate((level > 10) ? 10 : level, space)


FILE* _testlogFile = NULL;
unsigned int logCount = 0;
const char* testStateStr[TEST_STATE] = {"FAILED", "SUCCESS", "  ...  ", "UNKNOWN", "INVALID"};
const char* testStateCol[TEST_STATE] = {"\033[1;38;2;200;0;0m", "\033[1;38;2;0;200;0m", "", "", ""};

const char* testHierarchy[] = {"PARENT", "CHILD"};

FILE* _openFile(const char* restrict dir, const char* restrict mode, const char* _errormsg, ...) {
    va_list __errArgs; va_start(__errArgs, _errormsg);

    FILE* file = fopen(__checkdir_s(dir), mode);
    if(file == NULL) {
        vsnprintf(_testerrbuf, sizeof(_testerrbuf), _errormsg, __errArgs);
        perror(_testerrbuf);
    }

    va_end(__errArgs);
    return file;
}

int _closeFile(FILE** file, const char* _errormsg, ...) {
    va_list __errArgs; va_start(__errArgs, _errormsg);

    int _retval = fclose(*file);
    if (_retval != 0) {
        vsnprintf(_testerrbuf, sizeof(_testerrbuf), _errormsg, __errArgs);
        perror(_testerrbuf);
    }
    else { *file = NULL; }

    va_end(__errArgs);
    return _retval;
}

int _deleteFile(const char* restrict dir, const char* _errormsg, ...){
    char _sysbuf[TEST_STDBUFLEN];
    va_list _errArgs; va_start(_errArgs, _errormsg);

    snprintf(_sysbuf, sizeof(_sysbuf), "DEL %s", __checkdir_s(dir));
    int _retval = system(_sysbuf);
    if (_retval != 0) {
        vsnprintf(_testerrbuf, sizeof(_testerrbuf), _errormsg, _errArgs);
        perror(_testerrbuf);
    }

    va_end(_errArgs);
    return _retval;
}

FILE* createTempFile(const char* restrict dir) {
    FILE* file = _openFile(
        dir,
        "wb+",
        "[%s] {%s} cannot create temporary file \"%s\"", __testerrSign__, TEST_LOCATION, dir
    );
    return file;
}

void deleteTempFile(FILE** file, const char* restrict dir) {
    _closeFile(file, "[%s] {%s} cannot close temp file", __testerrSign__, TEST_LOCATION);
    _deleteFile(dir, "[%s] {%s} unable to delete temp file \"%s\"", __testerrSign__, TEST_LOCATION, dir);
}


FILE* testlogCreate(const char* dir) {
    if (dir == NULL) {
        fprintf(stderr, "[%s] {%s} Invalid dir (dir* = 0x%llx); assign dir to default \"%s\"\n", __testerrSign__, TEST_LOCATION, dir, DEFAULT_LOGDIR);
        dir = DEFAULT_LOGDIR;
    }

    return _testlogFile = _openFile(dir, "ab+",
        "[%s] {%s} cannot create logfile \"%s\"", __testerrSign__, TEST_LOCATION, dir
    );
} 

// call by reference (&file)
void testlogClose(register FILE** file) { 
    if (*file != _testlogFile) 
        fprintf(stderr, "[%s] {%s} file is not _testlogFile: %llx, use _closeFile() instead\n", "TEST_INFO", TEST_LOCATION);

    else if (0 == _closeFile(file, "[%s] {%s} uninitialized _testlogFile or is in used, initialize with %s", __testerrSign__, TEST_LOCATION, "testlogCreate()"))
        _testlogFile = NULL;
}


int testlogWrite(FILE* file, testbool test, const char* str, ...) {
    if(file == NULL) file = stdout;
    va_list arg; va_start(arg, str);

    int cnt = _vtestlogWrite(file, test, str, arg);
    
    va_end(arg);
    return cnt;
}

int testlogWritef(const char* restrict dir, testbool test, const char* str, ...) {
    FILE* tempfile = _openFile(
        dir, "ab+", 
        "[%s] {%s} cannot create logfile \"%s\"", __testerrSign__, TEST_LOCATION, dir
    );
    if(tempfile == NULL) return TEST_FAILED;


    va_list arg; va_start(arg, str);
    int cnt = _vtestlogWrite(tempfile, test, str, arg);
    
    fclose(tempfile);
    va_end(arg);
    return cnt;
}

int _vtestlogWrite(FILE* file, testbool test, const char* str, va_list __args) {
    int cnt;
    const char* __bufptr = testStateStr[test];

    if ((file == stdout) || (file == stderr)) {
        snprintf(_testlogbuf, TEST_STDBUFLEN, "%s%s%s", testStateCol[test], testStateStr[test], "\033[0;39m");
        __bufptr = _testlogbuf;
    }

    cnt  = fprintf(file, "%3u| (%4u ms) [%s] ", logCount++, _clockElapsed(), __bufptr);
    cnt += vfprintf(file, str, __args); putc('\n', file); 
    return cnt;
}

int logwrite(FILE* file, const char* str, ...) {
    if(file == NULL) file = stdout;
    va_list arg; va_start(arg, str);

    int cnt = _vlogWrite(file, str, arg);
    
    va_end(arg);
    return cnt;
}

int logwritef(const char* restrict dir, const char* str, ...) {
    FILE* tempfile = _openFile(dir, "ab+", "[%s] {%s} cannot create logfile \"%s\"\n", __testerrSign__, TEST_LOCATION, dir);
    if(tempfile == NULL) {
        return TEST_FAILED;
    }

    va_list arg; va_start(arg, str);
    int cnt = _vlogWrite(tempfile, str, arg);
    
    fclose(tempfile);
    va_end(arg);
    return cnt;
}

int _vlogWrite(FILE* file, const char* str, va_list __args) {
    int cnt;
    cnt  = fprintf(file, "%s", "\t=> ");
    cnt += vfprintf(file, str, __args); putc('\n', file); 
    return cnt;
}

// return yes[1] | no[0] | invalid[-1]
int _testprompt(const char* _msg, ...) {
    va_list _msgArgs; va_start(_msgArgs, _msg);

    vfprintf(stdout, _msg, _msgArgs);
    fprintf(stdout, "%s", " (y/n) ");
    char c = getchar();
    if (c != '\n') STDIN_BUFCLEAR;

    int _retval;
    if      ((c == 'y') || (c == 'Y')) _retval = 1;
    else if ((c == 'n') || (c == 'N')) _retval = 0;
    else _retval = -1;

    va_end(_msgArgs);
    return _retval;
};




#define TABLEN 2
char* _tabCreate(int n, unsigned char tablen) {
    int i = 0;
    for ( ; n != 0; n--) {
        if (tablen == 0) _testlogbuf[i++] = '\t';
        else for (int j = 0 ; j < tablen; i++, j++) { _testlogbuf[i] = ' '; }
    }
    _testlogbuf[i] = '\0';
    return _testlogbuf;
}

char* _testlocate(const char *filename, const char *funcname, int linenum) {
    char filebuf[0x20], funcbuf[0x20], linebuf[0x10];

    if (filename != NULL) snprintf(filebuf, 0x20, "%s", filename);
    else filebuf[0] = '\0';

    if (funcname != NULL) snprintf(funcbuf, 0x20, "%s%s()", (filename == NULL) ? "\0" : "/", funcname);
    else funcbuf[0] = '\0';

    if (linenum != 0) snprintf(linebuf, 0x10, "%s%d", (filename == funcname) ? "... :" : " :", linenum);
    else linebuf[0] = '\0';

    snprintf(_testlocationbuf, 256, "%s%s%s", filebuf, funcbuf, linebuf);
    return _testlocationbuf;
}

char* __checkdir_s(const char* _dir) {
    register char c = !'\0';
    for (int i = 0; c != '\0' ; i++, _dir++) {
        c = *_dir;
        if((c == '\\') || (c == '/')) { c = DIRECTORY_SIGN; }
        if (i >= sizeof(_testdirbuf)) {
            fprintf(stderr, "{%s} _dir too long, insufficient buffer size _testdirbuf: %u bytes", TEST_LOCATION, sizeof(_testdirbuf));
            return NULL;
        }
        _testdirbuf[i] = c;
    }

    return _testdirbuf;
}

int __checkdir(register char* _dir) {
    char* _initDir = _dir;
    register char c;
    for ( ; (c = *_dir) != '\0' ; _dir++) {
        if((c == '\\') || (c == '/')) { *_dir = DIRECTORY_SIGN; }
    }
    return _dir - _initDir;
}

#endif

// return clock since last call
clock_t _clockElapsed(void) {
    register clock_t lastclock = __globalLastClock;
    return ((__globalLastClock = clock()) - lastclock); 
}

clock_t clockUpdateElapsed(clock_t* _lastclock) {
    register clock_t tempClock = *_lastclock;
    return ((*_lastclock = clock()) - tempClock); 
}


int testArrSummary(testbool result[], int n) {
    for (int i = 0; i < n; i++) {
        if (result[i] != TEST_SUCCESS) return TEST_FAILED;
    }
    return TEST_SUCCESS;
}

// only accepts (testbool) as variadic argument
int testSummary(int nTest, ...) {
    if (nTest <= 0) return TEST_UNKNOWN;

    testbool result = 0;
    va_list args; va_start(args, nTest);

    for( ; 1 ; nTest--){
        if (nTest == 0) {
            result = TEST_SUCCESS;
            break;
        }
        else if (va_arg(args, int) != TEST_SUCCESS) {
            result = TEST_FAILED;
            break;
        }
    }

    va_end(args);
    return result;
}

#endif