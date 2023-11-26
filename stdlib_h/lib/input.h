#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <conio.h>
#include <stdint.h>
#include "Bit_manipulation.h"
#include "std_constants.h"
#include "mem_man.h"
#include "src_info.h"
#include "_string.h"

#include "decl/input.h"

#define STD_BUFSIZE 0xfff   /* Standard Buffer Size */

#ifndef STANDARD_CONSTANTS_H
#define IN 1
#define OUT 0
#endif

#define EXTENDED_INPUT TRUE
unsigned char extInput_table(unsigned char *c);

#define STD_STRING(variable, string) (variable) ? 0 : (variable = string)

typedef union INPUT_STATUS {
    stat8_t UNION;
    struct {
        stat8_t active   : 1; /* ACTIVE INPUT flag (0 if idle) */
        stat8_t extended : 1; /* Extended character flag (0 if within 0 ~ 127) */
        stat8_t blank    : 1; /* Blank characters flag (' ', '\t', '\n') */
        stat8_t newline  : 1; /* Newline flag ('\n') or (13) "carriage return ENTER key" */
        stat8_t backspace: 1; /* Backspace flag ('\b') */
        stat8_t c        : 1;
        stat8_t ctrl     : 1; /* Control Characters flag (0 ~ 26) */
        stat8_t exit     : 1; /* Force Exit Flag */
    } section; 
} INPUT_STATUS;


// INPUT STATUS (8-bit)
// | a | b | c | d | e | f | g | h |
/* 
 *
 * a - Force Exit Flag
 * b - Control Characters flag (0 ~ 26)
 * c -
 * d - Bacspace flag ('\b')
 * e - Newline flag ('\n') or (13) "carriage return ENTER key"
 * f - Blank characters flag (' ', '\t', '\n')
 * g - Extended character flag (0 if within 0 ~ 127)
 * h - ACTIVE INPUT flag (0 if idle)
*/


#define INPUT_STATUS_IDLE       0x00    /* 0000 0000 */

#define INPUT_STATUS_ACTIVE     0x01    /* 0000 0001 (active input flag)*/
#define INPUT_STATUS_EXTENDED   0x02    /* 0000 0010 (extended char flag) */
#define INPUT_STATUS_BLANK      0x04    /* 0000 0100 (blank input flag (' ', '\t', '\n')) */
#define INPUT_STATUS_NEWLINE    0x08    /* 0000 1000 (Newline flag) */
#define INPUT_STATUS_BACKSPACE  0x10    /* 0001 0000 (backspace flag) */

#define INPUT_STATUS_CONTROL    0x40    /* 0100 0000 (control characters flag) */
#define INPUT_STATUS_EXIT       0x80    /* 1000 0000 (force exit flag) */


// return INPUT_STATUS_OVERFLOW if cur_position more than or equal to array_size
#define CHECK_ARRAY_OVERFLOW(array_size, cur_pos) (cur_pos < array_size) ? FALSE : TRUE

#define WIN_KB_EXTENDFLAG1  0x00 /* Windows extended keyboard input flag */
#define WIN_KB_EXTENDFLAG2  0xe0 /* Windows extended keyboard input flag */

#define EOF_HEX 0xff    /* hexadecimal of EOF (-1) */
#define STRING_TERMINATOR '\0'  /* string (null) terminator '\0' */
#define KB_RETURN   '\r' /* 13 is carriage return "ENTER" key */
#define KB_EOF      26   /* 26 is unbuffered EOF (ctrl - Z) key */

#define INVALID_INPUT -1 /* invalid input, can be interchangeable with EOF */

#define KB_ESC      27  /* 27 is Windows unbuffered escape key (ESC) */

/* =================== EXTENDED INPUT TABLE ====================== */
#if EXTENDED_INPUT
// Arrow Key
#define INPUT_ARROW_UP      0x81    /* 1000 0001 (-126) */ 
#define INPUT_ARROW_DOWN    0x82    /*         *        */
#define INPUT_ARROW_LEFT    0x83    /*         *        */
#define INPUT_ARROW_RIGHT   0x84    /* 1000 0100 (-123) */

// Function Key
#define INPUT_F1            0x85    /* 1000 0101 (-122) */
#define INPUT_F2            0x86    /*         *        */
#define INPUT_F3            0x87    /*         *        */
#define INPUT_F4            0x88    /*         *        */
#define INPUT_F5            0x89    /*         *        */
#define INPUT_F6            0x8a    /*         *        */
#define INPUT_F7            0x8b    /*         *        */
#define INPUT_F8            0x8c    /*         *        */
#define INPUT_F9            0x8d    /*         *        */
#define INPUT_F10           0x8e    /*         *        */
#define INPUT_F11           0x8f    /*         *        */
#define INPUT_F12           0x90    /* 1001 0000 (-111) */

#define INPUT_ALT_F1        0x91    /* 1001 0001 (-110) */
#define INPUT_ALT_F2        0x92    /*         *        */
#define INPUT_ALT_F3        0x93    /*         *        */
#define INPUT_ALT_F4        0x94    /*         *        */
#define INPUT_ALT_F5        0x95    /*         *        */
#define INPUT_ALT_F6        0x96    /*         *        */
#define INPUT_ALT_F7        0x97    /*         *        */
#define INPUT_ALT_F8        0x98    /*         *        */
#define INPUT_ALT_F9        0x99    /*         *        */
#define INPUT_ALT_F10       0x9a    /*         *        */
#define INPUT_ALT_F11       0x9b    /*         *        */
#define INPUT_ALT_F12       0x9c    /* 1001 1100 ( -99) */

#define INPUT_CTRL_F1       0x9d    /* 1001 1101 ( -98) */
#define INPUT_CTRL_F2       0x9e    /*         *        */
#define INPUT_CTRL_F3       0x9f    /*         *        */
#define INPUT_CTRL_F4       0xa0    /*         *        */
#define INPUT_CTRL_F5       0xa1    /*         *        */
#define INPUT_CTRL_F6       0xa2    /*         *        */
#define INPUT_CTRL_F7       0xa3    /*         *        */
#define INPUT_CTRL_F8       0xa4    /*         *        */
#define INPUT_CTRL_F9       0xa5    /*         *        */
#define INPUT_CTRL_F10      0xa6    /*         *        */
#define INPUT_CTRL_F11      0xa7    /*         *        */
#define INPUT_CTRL_F12      0xa8    /* 1010 1000 ( -87) */

// Misc
#define INPUT_DELETE
#define INPUT_HOME
#define INPUT_END
#define INPUT_PAGE_UP
#define INPUT_PAGE_DOWN
#define INPUT_
#define INPUT_
#define INPUT_
#define INPUT_
#endif

/* ================== ASCII BOOLEANS MACRO ================= */

#define IS_WINEXTEND(c) ((c == WIN_KB_EXTENDFLAG1) || (c == WIN_KB_EXTENDFLAG2))

#define ISUCHAR(c) ((c >= 'A') && (c <= 'Z'))   /* Uppercase Character */
#define ISLCHAR(c) ((c >= 'a') && (c <= 'z'))   /* Lowercase Character */
#define ISNUM(c)   ((c >= '0') && (c <= '9'))   /* Number Character */

/* Unbuffered Control Key (Ctrl + [key])  
 * ASCII Control Character */
#define ISCTRL(c) ((c >= 1) && (c <= 32))



#ifndef ISBLANK
#define ISBLANK(c)     (c > ' ') ? FALSE : ((c == ' ') || (c == '\t') || (c == '\n'))
#define ISBLANK_EX(c) (c > ' ') ? FALSE : ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r') || (c == STRING_TERMINATOR))
#endif

/*  extended keyboard input returns INPUT_ACTIVE (and INPUT_EXTENDED if detects extended char by 0x00 signal)
(return INPUT_IDLE if there's no match in the input table) */
#define INPUT_EXT(c)        (c = _getch()) ? INPUT_STATUS_ACTIVE : extInput_table(&c);

#define UNBUFF_INPUT(c)             if (_kbhit()) c = _getch();
#define UNBUFF_INPUT_EXT(c, status) if (_kbhit()) status = INPUT_EXT(c)

#define HALT_PRESS_ANY_KEY(msg)  {fprintf(stdout, "%s", msg); _getch();}

// Clear the buffered input from getchar
#define CLR_INBUF DEFCON_3 while (getchar() != '\n')

// unformatted put string to stdout
#define putstr(str) fputs(str, stdout)
// #define putstr(str) printf("%s", str)


TEMP typedef union KB_STATUS {
    stat8_t UNION;
    struct {
        stat8_t lcase   : 1; /* Keyboard Lowercase */
        stat8_t ucase   : 1; /* Keyboard Uppercase */
        stat8_t num     : 1; /* Keyboard Number */
        stat8_t blank   : 1; /* Keyboard Blank */
        stat8_t ctrl    : 1; /* Keyboard Control */
        stat8_t c       : 1;
        stat8_t extended : 1; /* Keyboard Extended */
        stat8_t custom  : 1; /* Custom Input */
    }; 
} KB_STATUS, kbstat;

// Keyboard Input Flag
TEMP
#define KB_DEFAULT  0x0fff    /* Allow Any Input */
#define KB_LOWCASE  0x0001    /* Lowercase Character */
#define KB_UPCASE   0x0002    /* Uppercase Character */
#define KB_NUM      0x0004    /* Number Character */

#define KB_CHAR     (KB_UPCASE | KB_LOWCASE)    /* Alphabet Character */
#define KB_CHARNUM  (KB_UPCASE | KB_LOWCASE | KB_NUM)  /* Basic Character */

#define KB_BLANK    0x0008    /* Blank Character (use either ISBLANK or ISBLANK_EX) */
#define KB_CTRL TEMP 0x0010   /* Control Character (use either ISCTRL or ISCTRL_EX) */
#define KB_WINEX TEMP  0x0020    /* Win Extended Keyboard Input */
#define KB_EXTRA TEMP  0x0040    /* Extra or user defined Input */

#define KB_CUSTOM   0x0080  /* Custom Keyboard Input */

#define CH_NOPRINT      0X00  /* NO PRINT */
#define CH_PRINTDEFAULT 0x1b  /* print default characters */
#define CH_PRINTCUSTOM  0xff  /* custom print */

#define CH_WITHNULLSTR TEMPSOL  0x8000  /* with STRING TERMINATOR (make sure to reserve 1 more byte for string terminator) */

// getline but with getch
TEMP int getch_line(register char* str, register uint16_t mode, const char extraInput[], const char output) {
    register char c;
    char* restrict baseStr = str;
    unsigned int i, TEMP len;
    len = 0;
    
    // main loop
    for (i = 0; TRUE ; i++) {
        c = _getch();
        if (IS_WINEXTEND(c)) {_getch(); c = INVALID_INPUT;}

        // exit
        if (c == KB_ESC) return -1;
        else if ((c == '\n') || (c == KB_RETURN)) break;

        // backspace
        if (c == '\b') {
            c = INVALID_INPUT;
            if (str != baseStr) {
                *str = 0; str--; len--;

                // backspace print
                if      (output == CH_PRINTCUSTOM) ;
                else if (output != CH_NOPRINT) TEMP putstr("\b \b");
            }
        }

        // main check
        {
        if (c == INVALID_INPUT) ; /* Skip the entire checking */
        else if (mode == KB_DEFAULT) ;  
        else if (BITCHK(mode, KB_LOWCASE) && ISLCHAR(c)) ;
        else if (BITCHK(mode, KB_UPCASE)  && ISUCHAR(c)) ;
        else if (BITCHK(mode, KB_NUM)     && ISNUM(c)) ;
        else if (BITCHK(mode, KB_BLANK)   && ISBLANK_EX(c)) ;
        else if (BITCHK(mode, KB_EXTRA)   && (cfind(extraInput, c) != -1) ) ;
        else c = INVALID_INPUT;
        }

        // assign and print
        if (c != INVALID_INPUT) {
            *str = c; str++; len++;
            if (output != CH_PRINTCUSTOM) putchar((output == CH_PRINTDEFAULT) ? c : output);
            else ;
        }
    }
    
    *str = STRING_TERMINATOR;
    return (str - baseStr);
}

// getline but with getch
TEMP int getch_line_s(char* str, uint16_t size, register uint16_t mode, const char extraInput[], const char output) {
    register char c;
    unsigned int i;

    char baseBuf[STD_BUFSIZE];
    register char* buffer = baseBuf;

    // Pre-Check
    if ((size > STD_BUFSIZE) || (size == 0)) {
        fprintf(stderr_h, "size may not more than [sizeof(buffer)] 0xfff or 0 | [size: %u]\n", (size & 0xafff));
        return -1;
    }

    // reserve 1 byte for STRING TERMINATOR
    if (BITCHK(mode, CH_WITHNULLSTR)) size--;
    
    // main loop
    for (i = 0; TRUE ; i++) {
        c = _getch();
        if (IS_WINEXTEND(c)) {_getch(); c = INVALID_INPUT;}

        // backspace and safety check
        if (c == '\b') {
            c = INVALID_INPUT;
            if (buffer != baseBuf) {
                *buffer = 0; buffer--; size++;

                // backspace print
                if      (output == CH_PRINTCUSTOM) ;
                else if (output != CH_NOPRINT) TEMPSOL putstr("\b \b");
            }
        }

        // exit
        if (c == KB_ESC) return -1;
        else if ((c == '\n') || (c == KB_RETURN)) break;

        // safety size check
        TEMPSOL if (size == 0) c = INVALID_INPUT;

        /* main check */ {
        if (c == INVALID_INPUT) ; /* Skip the entire checking */
        else if (mode == KB_DEFAULT) ;  
        else if (BITCHK(mode, KB_LOWCASE) && ISLCHAR(c)) ;
        else if (BITCHK(mode, KB_UPCASE)  && ISUCHAR(c)) ;
        else if (BITCHK(mode, KB_NUM)     && ISNUM(c)) ;
        else if (BITCHK(mode, KB_BLANK)   && ISBLANK_EX(c)) ;
        else if (BITCHK(mode, KB_EXTRA)   && (cfind(extraInput, c) != -1) ) ;
        else c = INVALID_INPUT;
        }

        // assign and print
        if (c != INVALID_INPUT) {
            *buffer = c; buffer++; size--;
            if (output != CH_PRINTCUSTOM) putchar((output == CH_PRINTDEFAULT) ? c : output);
            else ;
        }
    }
    
    // post-processing
    if(BITCHK(mode, CH_WITHNULLSTR)) {*buffer = STRING_TERMINATOR; buffer++;}
    return strmov_s(baseBuf, str, buffer - baseBuf);
}

// no fuss no wuss no safety-checking, just plain getline start from 0 position
// make sure to allocate enough memory
int getline(register unsigned char* str) {
    register unsigned char *initStr = str;
    register unsigned char eax;  /* eax register */

    // Heavily use register "eax" to avoid reading/writing to memory twice (which is slower than register)
    while ((eax = getchar()) != '\n') {*str = eax; str++;}
    // while ((*str = getchar()) != '\n') str++;

    *str = STRING_TERMINATOR;
    return (str - initStr);
}

// getline with safety check (return the length if success and -1 if detects overflow)
DEFCON_ALPHA int getline_s(register unsigned char* str, unsigned int size) {
    unsigned char *initStr = str;
    register unsigned char *endStr = str + size; 
    register unsigned char c;  /* register */

    // Heavily use register "eax" to avoid reading/writing to memory twice (which is slower than register)
    while ((c = getchar()) != '\n') {
        *str = c; str++;
        if (str == endStr) {CLR_INBUF; return -1;} /* safety check */
    }
    // while ((*str = getchar()) != '\n') str++;

    *str = STRING_TERMINATOR;
    return (str - initStr);
}


// check input status (return the input status as designed as above)
uint8_t check_input_status(register unsigned char c, uint8_t default_status) {
    register uint8_t status = default_status;

    // control characters
    if (c < 27) BIT_SWITCH_1(status, INPUT_STATUS_CONTROL);

    // Special Characters
    switch (c)
    {
    case '\n': case  KB_RETURN:    /* Newline characters, 13 is carriage return "ENTER" key */
        BIT_SWITCH_1(status, INPUT_STATUS_NEWLINE);
    case '\t': case ' ':   /* Blank characters (including newline characters) */
        BIT_SWITCH_1(status, INPUT_STATUS_BLANK); break;

    case '\b': /* backspace character */
        BIT_SWITCH_1(status, INPUT_STATUS_BACKSPACE); break;

    case EOF_HEX: case KB_EOF:    /* FORCE EXIT, 26 is unbuffered version of EOF (ctrl - Z) */
        BIT_SWITCH_1(status, INPUT_STATUS_EXIT); break;

    case WIN_KB_EXTENDFLAG1: case WIN_KB_EXTENDFLAG2:    /* EXTENDED CHARACTERS 0x00 and -32 is windows flag for extended keyboard input */
        BIT_SWITCH_1(status, INPUT_STATUS_EXTENDED); break;

    default: break;
    }
    return status;
}

// check for blank
int blankCheck(register unsigned char c) {

    // switch (c) {
    // case '\t': case '\n': case ' ': case 13: case STRING_TERMINATOR:   /* Blank characters, 13 is carriage return "ENTER" key */
    //     return TRUE;
    // default : 
    //     return FALSE;
    // }

    // early return (all blank characters are below 32 ' ')
    if (c > ' ') return FALSE;

    // I'm using (OR) (if) mainly because it generates actual simple lookup table in the assembly unlike (switch case)
    if ((c == ' ') || (c == '\n') || (c == '\t') || (c == 13) || (c == STRING_TERMINATOR)) return TRUE;
    return FALSE;
}


// check and assign the extended input table after the extended (0x00) signal
// return INPUT_EXTENDED signal if exists or INPUT_IDLE signal if not
unsigned char extInput_table(unsigned char *c) {
    switch (*c = _getch())
    {

#if EXTENDED_INPUT
    // Windows Function Key
    case  59: *c = INPUT_F1;   break;
    case  60: *c = INPUT_F2;   break;
    case  61: *c = INPUT_F3;   break;
    case  62: *c = INPUT_F4;   break;
    case  63: *c = INPUT_F5;   break;
    case  64: *c = INPUT_F6;   break;
    case  65: *c = INPUT_F7;   break;
    case  66: *c = INPUT_F8;   break;
    case  67: *c = INPUT_F9;   break;
    case  68: *c = INPUT_F10;  break;
    case 133: *c = INPUT_F11;  break;
    case 134: *c = INPUT_F12;  break; 

    // Windows Crtl-Function key
    case  94: *c = INPUT_CTRL_F1;    break;
    case  95: *c = INPUT_CTRL_F2;    break;
    case  96: *c = INPUT_CTRL_F3;    break;
    case  97: *c = INPUT_CTRL_F4;    break;
    case  98: *c = INPUT_CTRL_F5;    break;
    case  99: *c = INPUT_CTRL_F6;    break;
    case 100: *c = INPUT_CTRL_F7;    break;
    case 101: *c = INPUT_CTRL_F8;    break;
    case 102: *c = INPUT_CTRL_F9;    break;
    case 103: *c = INPUT_CTRL_F10;   break;
    case 137: *c = INPUT_CTRL_F11;   break;
    case 138: *c = INPUT_CTRL_F12;   break;

    // Windows Alt-Function Key
    case 104: *c = INPUT_ALT_F1;    break;
    case 105: *c = INPUT_ALT_F2;    break;
    case 106: *c = INPUT_ALT_F3;    break;
    case 107: *c = INPUT_ALT_F4;    break;
    case 108: *c = INPUT_ALT_F5;    break;
    case 109: *c = INPUT_ALT_F6;    break;
    case 110: *c = INPUT_ALT_F7;    break;
    case 111: *c = INPUT_ALT_F8;    break;
    case 112: *c = INPUT_ALT_F9;    break;
    case 113: *c = INPUT_ALT_F10;   break;
    case 139: *c = INPUT_ALT_F11;   break;
    case 140: *c = INPUT_ALT_F12;   break;
    
    // Windows Arrow Key Input
    case 72: *c = INPUT_ARROW_UP;    return (INPUT_STATUS_EXTENDED);
    case 75: *c = INPUT_ARROW_LEFT;  return (INPUT_STATUS_EXTENDED);
    case 77: *c = INPUT_ARROW_RIGHT; return (INPUT_STATUS_EXTENDED);
    case 80: *c = INPUT_ARROW_DOWN;  return (INPUT_STATUS_EXTENDED);
#endif
    
    default: return (INPUT_STATUS_EXTENDED | INPUT_STATUS_IDLE);
        break;
    }
    return (INPUT_STATUS_EXTENDED | INPUT_STATUS_ACTIVE);
}



#endif