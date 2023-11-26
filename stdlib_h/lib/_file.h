#ifndef _CUSTOM_FILE_H
#define _CUSTOM_FILE_H

#include "std_constants.h"
#include <stdio.h>
#include <fcntl.h>

#if WIN_DEFINED
#include <windows.h>
#endif

/* GET FILE* from file HANDLE in windows */
/* 
 *      Open or Create File with Win32 API [HANDLE]
 *                          |
 *       _open_osfhandle() [int / File Descriptor]
 *                          |
 *                  _fdopen() [FILE*]
 */
/* 
 *  Open or create file from Win32 API and obtain the HANDLE
 *
 *  Get file Descriptor from HANDLE with _open_osfhandle()
 *  NOTE: _open_osfhandle() transfers the ownership of the file to file descriptor 
 *        hence, no need to close the handle, just close the descriptor would suffice
 * 
 *  Get FILE* from file descriptor with _fdopen()
 *  NOTE: _fdopen() transfers the ownership of the file to FILE*
 *        hence, calling fclose() with FILE* will automatically close the file handle as well as descriptor
 */

FILE* _createTempFile(const char* filename);

FILE* _createTempFile(const char* filename) {

    // Replace "C:\\Path\\To\\Your\\File.txt" with the actual path to your file

    HANDLE fileH = CreateFileA(
        (LPCSTR) filename,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_FLAG_DELETE_ON_CLOSE,
        NULL
    );

    // Handle error
    if (fileH == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error opening file\n");
        return NULL;
    }
    
    // Get the file descriptor
    int fileDescriptor = _open_osfhandle((intptr_t) fileH, _O_WRONLY | O_RDONLY);
    
    // File Descriptor error
    if (fileDescriptor == -1) {
        fprintf(stderr, "Error obtaining file descriptor\n");
        CloseHandle(fileH);
        return NULL;
    }

    // Convert the file descriptor to a FILE* pointer
    FILE* filePointer = _fdopen(fileDescriptor, "wb+");

    // File Pointer error
    if (filePointer == NULL) {
        fprintf(stderr, "Error obtaining FILE* pointer\n");
        _close(fileDescriptor);
        CloseHandle(fileH);
        return NULL;
    }

    // Now you can use filePointer as a regular FILE* in your code
    // ...

    // Close the file and cleanup
    // fclose(filePointer);
    // CloseHandle(fileH);

    setvbuf(filePointer, NULL, _IONBF, 0);
    return filePointer;


}



#endif
