#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include <stdint.h>
#include "Tools/Debug.h"

#include "std_constants.h"
#include "src_info.h"

#include "data.h"

typedef FILE* FPTR, FILEPTR;

// File _Mode
#define FMD_READ         "r"    /* Read-only */
#define FMD_READBIN      "rb"   /* Read-only Binary */
#define FMD_WRITE        "w"    /* Write-only (overwrite) */
#define FMD_WRITEBIN     "wb"   /* Write-only binary (overwrite) */
#define FMD_MODIFY       "r+"   /* Modify (Read and Write) */
#define FMD_MODIFYBIN    "rb+"  /* Modify binary (read and write) */
#define FMD_OVERWRITE    "w+"   /* Modify b */
#define FMD_OVERWRITEBIN "wb+"
#define FMD_APPEND       "a"
#define FMD_APPENDBIN    "ab"
#define FMD_RAPPEND      "a+"
#define FMD_RAPPENDBIN   "ab+"

// windows C GNU mingw-w64 FILE handle

/*
 * == controlling IO buffering ==
 * functions: setbuf(), setvbuf()
 * from stdin and stdout buffer (4096 bytes)
 * 
 * mode
 *  _IONBF: No buffer
 *  _IOLBF: Line (feed) buffer
 *  _IOFBF: Full buffer
*/

/* == Controlling internal File pointer position ==
 * functions: fseek(), ftell(), fgetpos(), ftellpos()
 * success: 0   error: -1
 * moves the file pointer (if any) associated with stream 
 * to a new location that is offset bytes from origin.
 * 
 * origin
 *  SEEK_SET: Beginning of file
 *  SEEK_CUR: Current position of file pointer
 *  SEEK_END: End of file
 * 
 *
*/

#define FPOS(filename, FILE) printf("Fpos {%s}: %d\n", filename, ftell(FILE))
#define FOPEN(FPTR, dir) if((FPTR = fopen(dir, mode)) == NULL) fprintf(stderr_h, "%s error opening file \"%s\" (mode: %s)\n", DEBUG_WARNING, dir, mode);

FILE* fopen_h(const char* restrict dir, const char* restrict mode) {
    FILE* file;
    if((file = fopen(dir, mode)) == NULL) 
        fprintf(stderr_h, "%s error opening file \"%s\" (mode: %s)\n", DEBUG_WARNING, dir, mode);
    return file;
    
}

typedef struct dataChunk {
    unsigned short n;
    unsigned int chunkLen;
    unsigned char *data;
    unsigned long checksum;
} dataChunk;

typedef struct file_properties {
    char* filename;
    unsigned int totalSize;
    unsigned short totalChunk;
    dataChunk* data;
} FILE_h;

TEMP typedef struct staticChunk_s {
    struct {
        unsigned int count : 31;
        unsigned int datatype : 1;
    } n;
    unsigned char buffer[64];
    uint32_t checksum;

} ssChunk, staticChunk_s;

TEMP typedef struct staticChunk {
    unsigned int n;
    unsigned char* data;
    uint32_t checksum;
} sChunk, staticChunk;

TEMP typedef struct dynamicChunk {
    int chunkType;
    unsigned int chunkLen;
    uint8_t* data;
    unsigned long checksum;

} dChunk, dynamicChunk;

#define FILEDATA_POS (sizeof(FILE_h) - sizeof(dataChunk*))


/* print the contents of FILE struct */
/* the struct below is from GCC Mingw-w64 (_iobuf) struct */
#define FILE_PROPERTIES(fptr, span_char) NON_STD OPAQUE_TYPE\
        printf("fptr: %llx%cbase: %llx%cbufsiz: %d%ccharbuf: %d%ccnt: %d%cfile: %d%cflag: %d%cptr: %llx%ctmpfname: %llx\n\n",\
        fptr,           span_char,\
        fptr->_base,    span_char,\
        fptr->_bufsiz,  span_char,\
        fptr->_charbuf, span_char,\
        fptr->_cnt,     span_char,\
        fptr->_file,    span_char,\
        fptr->_flag,    span_char,\
        fptr->_ptr,     span_char,\
        fptr->_tmpfname);

#define FILE_PROPERTIES2(fptr) NON_STD OPAQUE_TYPE\
        printf("fptr:\t%llx  {%s}\nbase:\t%llx\nbufsiz:\t%d\ncharbuf:\t%d\ncnt:\t%d\nfile:\t%d\nflag:\t%d\nptr:\t%llx\ntmpfname:\t%llx\n\n",\
        fptr, "~/" #fptr,          \
        fptr->_base,    \
        fptr->_bufsiz,  \
        fptr->_charbuf, \
        fptr->_cnt,     \
        fptr->_file,    \
        fptr->_flag,    \
        fptr->_ptr,     \
        fptr->_tmpfname);


int fgetstr(FPTR file, int position, char* buffer, int buflen) {
    if(position != 0) fseek(file, position, SEEK_SET);

    int i;
    register char c;

    for (i = 0; TRUE ; i++) {
        c = getc(file);

        if (c == '\0') break;
        if (i >= buflen) break;

        buffer[i] = c;
    }
    buffer[i] = '\0';
    return i;
    
}

TEMP int verify_h(FILE* file, FILE_h file_properties) {

}


TEMP int chunkread_s(FILE* file, dataChunk chunk) {
    fseek(file, 0, SEEK_SET);

    FILE_h fbuf = {0};

    if (fread(&fbuf, sizeof(FILE_h) - sizeof(dataChunk*), 1, file) == 0) {
        fprintf(stderr_h, "%s cannot read and verify file\n", DEBUG_WARNING);
        return -1;
    } 

    // data verification
    if (chunk.n >= fbuf.totalChunk) {
        fprintf(stderr_h, "%s {~\\%s} nchunk more than total chunk: %2u/%2u\n", DEBUG_INFO, fbuf.filename, chunk.n, fbuf.totalChunk);
        return -1;
    }

    // // datawrite
    // fseek(file, chunk.n * (chunk.chunkLen + sizeof(chunk.checksum)), SEEK_CUR);
    // if (fwrite(chunk.data, 1, chunk.chunkLen, file) != chunk.chunkLen) 
    //     fprintf(stdout, "%s [0x%x] problem in writing data\n", DEBUG_WARNING, file->_ptr);

    // fwrite(checksum_dword(chunk.data, chunk.chunkLen), sizeof(chunk.checksum), 1, file);


    
}

TEMP int chunkwrite_s(FILE* file, dataChunk chunk) {

    fseek(file, 0, SEEK_SET);

    FILE_h fbuf = {0};


    // read file properties
    if (fread(&fbuf, sizeof(FILE_h) - sizeof(dataChunk*), 1, file) == 0) {
        fprintf(stderr_h, "%s unable to read and verify file\n", DEBUG_INFO);
        fseek(file, FILEDATA_POS, SEEK_SET);
    } 

    // data verification
    else {
        if (chunk.n >= fbuf.totalChunk) 
            fprintf(stderr_h, "%s {~\\%s} nchunk more than total chunk: %2u/%2u\n", DEBUG_INFO, fbuf.filename, chunk.n, fbuf.totalChunk);
    }

    // datawrite
    fseek(file, chunk.n * (chunk.chunkLen + sizeof(chunk.checksum)), SEEK_SET);
    if (fwrite(chunk.data, 1, chunk.chunkLen, file) != chunk.chunkLen) 
        fprintf(stderr_h, "%s [0x%x] problem in writing data\n", DEBUG_WARNING, file->_ptr);

    chunk.checksum = checksum_dword(chunk.data, chunk.chunkLen);
    fwrite(&chunk.checksum, sizeof(chunk.checksum), 1, file);

    printf("%llu\n", chunk.checksum);
    



    return 1;

}

int chunkread(dataChunk chunk);



TEMP char* getFileDir(char* fullDir) {
    unsigned char pos = 0;
    
    while ( TRUE )
    {
        
    }
    
}

TEMP char* getFileDir_f(FPTR file) {
    long cur_FilePtr = ftell(file);

    fseek(file, 0, SEEK_SET);
}

#endif