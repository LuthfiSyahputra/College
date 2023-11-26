
#ifndef PASSCODE_H
#define PASSCODE_H

#include <stdio.h>
#include <conio.h>
#include "input.h"
#include "mem_man.h"
#include "_string.h"
#include "Tools/Debug.h"
#include "src_info.h"

#include <windows.h>


#define MAX_PASSWORD_LENGTH 16U
#define MIN_PASSWORD_LENGTH 4
#define MAX_ATTEMPT 3

#ifndef NEW_INPUTOUTPUT_H
// Clear current line in terminal, Based on ANSI screen drivers standard
#define CLEARLINE printf("%s", __clrline__)
#define CLRLINE fputs(__clrline__, stdout)

#endif



// len must be factor of 4
DEFCON_ALPHA int pass_obfuscator(register void* ptr, register unsigned int salt, register int len) {
    len >>= 2;
    while (len){
        *(unsigned int*) ptr += salt; 
        ptr += sizeof(unsigned int);
        len--; salt +=salt;
    }
}
// len must be factor of 4
DEFCON_ALPHA int pass_deobfuscator(register void* ptr, register unsigned int salt, register int len) {
    len >>= 2;
    while (len){
        *(unsigned int*) ptr -= salt; 
        ptr += sizeof(unsigned int);
        len--; salt += salt;
    }
}

// get password input (max_len should no more than allowed MAX_PASSWORD_LENGTH)
int password_input(unsigned char* password, unsigned int max_len)
{
    register unsigned char c;
    unsigned char buffer[MAX_PASSWORD_LENGTH];
    
    if (max_len > MAX_PASSWORD_LENGTH) {
        printf("%s max_len: %d should be less than buffer: %d (MAX_PASSWORD_LENGTH)\n"\
                , DEBUG_WARNING, max_len, MAX_PASSWORD_LENGTH);
        return 0;
    }

    memreset(buffer, max_len);
    register unsigned int len = 0;
    for (int i = 0; TRUE ; i++) {
        
        c = getch();
        if ((c == WIN_KB_EXTENDFLAG1) || (c == WIN_KB_EXTENDFLAG2)) {getch(); c = OUT;}

        // check the status to avoid extended input
        // status = check_input_status(c, 0x00);
        if (c != OUT) {

            // return key 
            if((c == KB_RETURN) || (c == '\n')) {
                memcpy_h(buffer, password, max_len);
                return len;
            }

            // backspace key (pre-decrement len because array always started from 0 not 1)
            if (c == '\b' && (len > 0)) {
                len--; buffer[len] = 0;
                printf("\b \b");
            }

            // force exit
            if (c == 27)  return -1;

            // allowed password input
            if ((c >= 30) && (len < max_len)) {
                buffer[len] = c; len++;
                putch('*');
            }
        }
    }
}


EXPERIMENTAL int password_new(unsigned char *password, unsigned int pass_maxlen) {
    int len;
    unsigned char buffer[MAX_PASSWORD_LENGTH];
    unsigned char temp_pass[MAX_PASSWORD_LENGTH];
    if(pass_maxlen < MIN_PASSWORD_LENGTH) {
        printf("%s maxLen must not less than MIN_PASSWORD_LENGTH: %d  maxlen: %d\n", DEBUG_WARNING, MIN_PASSWORD_LENGTH, pass_maxlen);
        return -1;
    }

    while (TRUE) {
        putstr("enter new password: ");
        len = password_input(temp_pass, pass_maxlen);

        if (len < MIN_PASSWORD_LENGTH) {
            printf("\tpassword must be %d ~ %d characters", MIN_PASSWORD_LENGTH, pass_maxlen);
            Sleep(1000);
            CLRLINE;
        }
        else break;

        if (len == -1) return -1;
    }

    putchar('\n');
    for (int i = 0; TRUE ; i++) {
        if (i >= MAX_ATTEMPT) return FALSE;

        putstr("confirm new password: ");
        if     (len != password_input(buffer, pass_maxlen)) ;            /* first check (length)*/
        else if(memcmp_h(buffer, temp_pass, pass_maxlen) == TRUE) break; /* second check (contents)*/

        // if checking false
        putstr("\t Password not match!!");
        Sleep(500);
        CLRLINE;
    }

    // post processing
    memcpy_h(temp_pass, password, pass_maxlen);
    return TRUE;
    
    // pass_obfuscator(pass, 0xafed7b95U, 16);
    // printf("%s\n", pass);
    // pass_deobfuscator(pass, 0xafed7b95U, 16);
    // printf("%s\n", pass);
}


#endif