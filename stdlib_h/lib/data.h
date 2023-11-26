#ifndef DATA_PROCESSOR
#define DATA_PROCESSOR


#include <stdio.h>
#include "src_info.h"
#include "Tools\Debug.h"

/* == CHECKSUM == */
TEMP int checksum(register void* ptr, unsigned int len, int datatype);
unsigned char checksum_byte(register void* ptr, register unsigned int len);
unsigned short checksum_word(register void* ptr, register unsigned int len);
unsigned long checksum_dword(register void* ptr, register unsigned int len);
unsigned long long checksum_qword(register void* ptr, register unsigned int len);


/* == DATA OBFUSCATION == */
DEFCON_BETA int data_obfuscator(register void *ptr, register unsigned int len, register size_t salt);
DEFCON_BETA int data_deobfuscator(register void *ptr, register unsigned int len, register size_t salt);

// Do not pass "read-only" data (such as string literals) leading to undefined behavior
DEFCON_BETA int data_obfuscator(register void *ptr, register unsigned int len, register size_t salt) {
    salt = (~salt * MAGIC_NUMBER 0xea291f384c);
    for (int i = 0; len >= 0x8; i++) {

        *(unsigned long long*) ptr += salt;
        len -= 0x8; ptr += sizeof(unsigned long long);
        salt -= MAGIC_NUMBER 0xe5c9a76fb38e43d7ULL;
    }
    if (len & 0x4) { *(unsigned long*) ptr += salt; ptr += sizeof(unsigned long);}
    if (len & 0x2) { *(unsigned short*) ptr += salt; ptr += sizeof(unsigned short);}
    if (len & 0x1) { *(unsigned char*) ptr += salt;}
    
    return 1;
}

// Do not pass "read-only" data (such as string literals) leading to undefined behavior
DEFCON_BETA int data_deobfuscator(register void *ptr, register unsigned int len, register size_t salt) {
    salt = (~salt * MAGIC_NUMBER 0xea291f384c);
    for (int i = 0; len >= 0x8; i++) {
        *(unsigned long long*) ptr -= salt;
        len -= 0x8; ptr += sizeof(unsigned long long);
        salt -= MAGIC_NUMBER 0xe5c9a76fb38e43d7ULL;
    }
    if (len & 0x4) { *(unsigned long*) ptr -= salt; ptr += sizeof(unsigned long);}
    if (len & 0x2) { *(unsigned short*) ptr -= salt; ptr += sizeof(unsigned short);}
    if (len & 0x1) { *(unsigned char*) ptr -= salt;}
    
    return 1;
}

TEMP int checksum(register void* ptr, unsigned int len, int datatype) {
    
    size_t sum = 0;
    while (len--) { sum += *(unsigned char*) ptr; ptr += datatype;}
    while (len--) { sum += *(unsigned short*) ptr; }
    while (len--) { sum += *(unsigned long*) ptr; }
    while (len--) { sum += *(unsigned long long*) ptr; }
}

unsigned char checksum_byte(register void* ptr, register unsigned int len) {
    register unsigned char sum = 0;
    while (len) { sum += *(unsigned char*) ptr; ptr += sizeof(char); len--;}
    return sum;
}

unsigned short checksum_word(register void* ptr, register unsigned int len) {
    register unsigned short sum = 0;
    if (len & 0x1) {fprintf(stderr, "%s len is not factor of 2 (WORD) | len: %u\n", DEBUG_WARNING, len); return 0;}
    len >>= 1;
    while (len) { sum += *(unsigned short*) ptr; ptr += sizeof(short); len--;}
    return sum;
}

unsigned long checksum_dword(register void* ptr, register unsigned int len) {
    register unsigned long sum = 0;
    if (len & (0x1 | 0x2)) {fprintf(stderr, "%s len is not factor of 4 (DWORD) | len: %u\n", DEBUG_WARNING, len); return 0;}
    len >>= 2;
    while (len) { sum += *(unsigned long*) ptr; ptr += sizeof(long); len--;}
    return sum;
}

unsigned long long checksum_qword(register void* ptr, register unsigned int len) {
    register unsigned long long sum = 0;
    if (len & (0x1 | 0x2 | 0x4)) {fprintf(stderr, "%s len is not factor of 8 (QWORD) | len: %u\n", DEBUG_WARNING, len); return 0;}

    len >>= 3;
    while (len) { sum += *(unsigned long long*) ptr; ptr += sizeof(long long); len--;}
    return sum;
}



#endif