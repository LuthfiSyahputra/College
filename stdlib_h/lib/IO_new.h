#ifndef NEW_INPUTOUTPUT_H
#define NEW_INPUTOUTPUT_H

/* As InputOutput.h is no longer maintained all the new methods stored in here */


#include "std_constants.h"
#include "input.h"
#include "mem_man.h"
#include "src_info.h"
#include "Tools/Debug.h"

#define STREAM_EXITNORMAL  1
#define STREAM_EXITNEWLINE 2
#define STREAM_EXITFORCE   3

#define COL_LENGTH  32

#define ENDINPUT    EOF
#define BUFFER_SIZE 0x1000
const char* std_endSequence = "THE END";

// Clear current line in terminal, Based on ANSI screen drivers standard
#define CLRLINE fputs(__clrline__, stdout)
#define CLEARLINE printf("%s", __clrline__)

#ifndef putstr
#define putstr(str) fputs(str, stdout) /* unformatted put string to stdout */
#endif

// seek and modify the ptr value to nearest STRING TERMINATOR
#define STRNULL_SEEK(ptr) while(*ptr != STRING_TERMINATOR) ptr++;

// status to be passed down between IO Functions
typedef struct STREAM_STATUS {
    union {
        uint8_t UNION;
        struct {
            uint8_t exit      : 2;
            uint8_t undefined : 6;
        };
    } status;

    int cur_position;
    int size;
} STREAM_STATUS;


// partial string compare (if str2 - STRING_TERMINATOR meets str - blank)
int strcmp_part(register const unsigned char *str, register const unsigned char* str2, register int str2_len) {

    // check for end sequence length
    if(!str2_len) str2_len = strlen_h(str2);

    // deduct the possible outcome
    if (!blankCheck(str[str2_len])) return FALSE; 

    // compare (loop until str2 meets string terminator)
    while (*str2 != STRING_TERMINATOR) { 
        if (*str != *str2) return FALSE;
        str++; str2++;
    } 
    return TRUE;
}

/* 
 * string cat parameter:
 * 0 - return the position of null terminator '\0' of main string array 
 * 1 - return the total increment Value excluding null terminator '\0'
 */
STD_AVAILABLE DEFCON_BETA int strArrayCat(register char main[], register char sec[], register int mainPos, uint8_t parameter)
{
    register int i;
    for (i = 0; main[mainPos] = sec[i]; i++, mainPos++) ;
    if      (parameter == 0) return mainPos;
    else if (parameter == 1) return i - 1;
}

/* string cat
 * mainOffset (-1) to automatically check the nearest NULL_TERMINATOR
 * parameter:
 * default - returns the length
 * 1       - returns the offset (null terminator from main base ptr)
 * 2 (EXP) - returns the pointer to null terminator of mainstr
 */
DEFCON_ALPHA STD_AVAILABLE size_t strcat_h(register char *mainStr, register char *secStr, register int mainOffset, uint8_t parameter) {
    
    // check the length
    if (mainOffset == -1) mainOffset = strlen_h(mainStr);
    mainStr += mainOffset;

    // string cat
    register char c;
    const char *mainBase = mainStr;
    for (; TRUE ; mainStr++, secStr++) {
        *mainStr = c = *secStr;
        if (c == STRING_TERMINATOR) break;
    }

    // return
    if (parameter == 1) return (mainOffset + (mainStr - mainBase));
    EXPERIMENTAL DEFCON_4 if (parameter == 2) return (size_t) mainStr;
    return (mainStr - mainBase);
}


// span character -1 to ignore
TEMP int strcat2_h(register char* mainStr, char* secStr, char span) {
    register char c;
    
    // search for the NULL_TERMINATOR
    mainStr += strlen_h(mainStr);

    // insert span
    if ((span != -1) && (*secStr != STRING_TERMINATOR)) {*mainStr = span; mainStr++;}

    for (int i = 0; (c = *secStr) != STRING_TERMINATOR; ) {
        // c = *secStr;

        // if (c == STRING_TERMINATOR) {
        //     break;
        // }

        *mainStr = c;
    }
    
}

// getline with safety check
STREAM_STATUS getline_str(register unsigned char str[], const unsigned char* endSequence, STREAM_STATUS STREAM) {

    unsigned char buffer[BUFFER_SIZE];
    register INPUT_STATUS status;
    register unsigned char c;
    int nchar = 0;

    if (endSequence == NULL) endSequence = std_endSequence;

    int len = getline(buffer);
    int endlen = strlen_h(endSequence);


    // main check loop
    for (int i = 0; TRUE ; i++, STREAM.cur_position++)
    {
        // temporary variable for faster checking
        c = buffer[i];

        // check the input status
        status.UNION = check_input_status(c, 0x00);

        // nchar
        (status.UNION & INPUT_STATUS_BLANK) ? (nchar = 0) : nchar++;
        
        // Early Exit
        if      (c == STRING_TERMINATOR) STREAM.status.UNION = STREAM_EXITNEWLINE;
        else if (c == ENDINPUT)  STREAM.status.UNION = STREAM_EXITNORMAL;

        // overflow
        if (STREAM.cur_position >= STREAM.size) {
            STREAM.status.exit = STREAM_EXITFORCE;
            fprintf(stderr, "%s memory overflow [size: %d]\n", DEBUG_WARNING, STREAM.size);
        }

        // endsequence exit
        DEFCON_ALPHA /* additional blank problem */
        if ((nchar == 1) && (c == *endSequence)) {
            if (strcmp_part(&buffer[i], endSequence, endlen)) STREAM.status.exit = STREAM_EXITNORMAL;
            i--; /* additional blank problem */
        }


        // exit yeah
        if (STREAM.status.UNION) {
            str[STREAM.cur_position] = STRING_TERMINATOR; break;
        }
        
        // assign
        str[STREAM.cur_position] = c;
    }

    return STREAM;
}

// parameter 0 - print the value 1 - print the characters (ASCII)
DEFCON_ALPHA DEFCON_3 int strOutput_forced(const char* str, register unsigned int len, int parameter) {

    register char c;
    register int i = 0;
    for ( ; i < len ; i++, str++) {
        
        if ((i % COL_LENGTH) == 0) putchar('\n');
        c = *str;

        if (parameter == 0) printf("%3d ", c);
        else {
            printf("%s", "\'\\");
            if      (c == '\n') c = 'n';
            else if (c == '\0') c = '0';
            else if (c == '\b') c = 'b';
            else if (c == '\t') c = 't';
            else if (c == '\r') c = 'r';
            else if (c == EOF ) c = '-';
            else putchar('\b');

            printf("%c%s", c, "\' ");
        }
    }
    return i;
}

// parameter 0 - print the value 1 - print the characters (ASCII)
EXPERIMENTAL DEFCON_ALPHA DEFCON_3 int strOutput_forced_s(const char* str, char* buffer, unsigned int buf_len, register unsigned int len, int parameter) {

    register char c = 0;
    register int i = 0;
    char temp[8];
    for ( ; i < len ; i++, str++) {
        
        if ((i % COL_LENGTH) == 0) putchar('\n');
        c = *str;

        if (parameter == 0) snprintf(temp, 8, "%3d ", c);
        else {
            printf("%s", "\'\\");
            if      (c == '\n') c = 'n';
            else if (c == '\0') c = '0';
            else if (c == '\b') c = 'b';
            else if (c == '\t') c = 't';
            else if (c == '\r') c = 'r';
            else if (c == EOF ) c = '-';
            else putchar('\b');

            printf("%c%s", c, "\' ");
        }
    }
    return i;
}


#endif