#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#ifdef _WIN32
    #define PATH_SEP '\\'
#else 
    #define PATH_SEP '/'
#endif

typedef struct filedir {
    char buf[0x100];
    uint8_t filename;
    uint8_t ext;
} filedir;


int filetype(char* str, char* filetype_collection[]);
char* lastchar(char* str, register char c);
int _word_check(char* collection[], char* str, int n);
int _nstring_check(char* str[]);
int get_filedir(char* str, filedir* fd);

char* _filetype[] = {
    "c",
    "h",
    "exe",
    ""
};

char* _file = "mefwkp.h.fff.h.exe";

int main(){
    int filet = filetype(_file, _filetype);
    if (filet != -1) printf("type: %s\n", _filetype[filet]);
    return filet;
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

