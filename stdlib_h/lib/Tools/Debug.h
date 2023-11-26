#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <stdio.h>



#define FILENAME __FILE__
#define FUNC     __func__
#define LINE     __LINE__

#define TRUE    1
#define FALSE   0

#define SHOW_DEBUG          TRUE
#define SHOW_DEBUG_INFO     TRUE
#define SHOW_DEBUG_WARNING  TRUE

char* info(const char *filename, const char *funcname, int linenum);
char* debug(const char *filename, const char *funcname, int linenum);
char* warning(const char *filename, const char *funcname, int linenum);

char* _debugstr(const char* status, char* _format, va_list _local_arg);
int debugprint(FILE* stream, const char* status, char* _format, ...);

#define DEBUG_INFO      info(__FILE__, __func__, __LINE__)
#define DEBUG_DEBUG     debug(__FILE__, __func__, __LINE__)
#define DEBUG_WARNING   warning(__FILE__, __func__, __LINE__)


#define SHOW_DEBUG_LOCATION TRUE

// Global character array
char debugInfo[50];
char debugbuf[0xfff];

// char* info(const char *FILE, const char *func /* , char *text */)
// {
//     char *str = "o";
//     // snprintf("{%s/%s} %s", FILE, func, text);
//     sprintf(str, "{%s/%s} ", &FILE, &func);
//     return FILE;
// }




char* info(const char *filename, const char *funcname, int linenum)
{
    if (SHOW_DEBUG_LOCATION) {
        if (linenum != 0)
            snprintf(debugInfo, sizeof(debugInfo), "[INFO] {%s/%s :%d} ", filename, funcname, linenum);
        else
            snprintf(debugInfo, sizeof(debugInfo), "[INFO] {%s/%s} ", filename, funcname);
        return debugInfo;
        
    }
}

char* debug(const char *filename, const char *funcname, int linenum)
{
    if (SHOW_DEBUG_LOCATION) {
        if (linenum != 0)
            snprintf(debugInfo, sizeof(debugInfo), "[DEBUG] {%s/%s :%d} ", filename, funcname, linenum);
        else
            snprintf(debugInfo, sizeof(debugInfo), "[DEBUG] {%s/%s} ", filename, funcname);
        return debugInfo;
    }
}

char* warning(const char *filename, const char *funcname, int linenum)
{
    if (SHOW_DEBUG_LOCATION) {
        if (linenum != 0)
            snprintf(debugInfo, sizeof(debugInfo), "[WARNING] {%s/%s :%d} ", filename, funcname, linenum);
        else
            snprintf(debugInfo, sizeof(debugInfo), "[WARNING] {%s/%s} ", filename, funcname);
        return debugInfo;
    }
}

// global log file pointer
static FILE* flog = NULL;

#define stderr_h stderr

FILE* flog_init(char* dir) {
    if ((flog = fopen(dir, "ab")) == 0) {
        fprintf(stderr, "%s error opening/creating log file \"~\\%s\"\n", DEBUG_WARNING, dir);
        return NULL;
    }
    return flog;
}


#define DEBUG_PASS(_stream, str) fprintf(stream, "[%s] %s\n", "PASS", str);


int debug_log(char *str, char* savedir) {

    FILE *logFile;
    if ((logFile = fopen(savedir, "ab")) == 0) {
        fprintf(stderr, "%s Error opening / creating log file \"~/%s\"\n", DEBUG_WARNING, savedir);
        return 0;
    }

    char buffer[0xfff];
    int len = snprintf(buffer, sizeof(buffer), "%s\n", str);

    fwrite(buffer, sizeof(char), len, logFile);
    fclose(logFile);
    return TRUE;
}


#endif