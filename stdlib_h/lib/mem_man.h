#ifndef MEMORY_MANIPULATION_H
#define MEMORY_MANIPULATION_H

#include <stdint.h>
#include <string.h>
#include <mem.h>
#include <memory.h>
#include <stdlib.h>

#include "src_info.h"
#include "datatype.h"
#include "std_constants.h"



typedef byte* _ptr;
union ptr_t;
union ptr_ct;
union type_t;
union type_m;


// Pseudo Template (EXPERIMENTAL)
#ifndef PSEUDO_TEMPLATE
#define PSEUDO_TEMPLATE EXPERIMENTAL
// Universal Pointer
typedef union ptr_t {
    void* base;     /* base address */

    int8_t*  int8;
    int16_t* int16;
    int32_t* int32;
    int64_t* int64;

    uint8_t*  uint8;
    uint16_t* uint16;
    uint32_t* uint32;
    uint64_t* uint64;

    float*  f;
    double* lf;
    // long double* llf;

} ptr_t, uniptr;

typedef union ptr_ct {
    void* base;     /* base address */

    const int8_t*  int8;
    const int16_t* int16;
    const int32_t* int32;
    const int64_t* int64;

    const uint8_t*  uint8;
    const uint16_t* uint16;
    const uint32_t* uint32;
    const uint64_t* uint64;

    const float*  f;
    const double* lf;
    // const long double* llf;

} ptr_ct, const_uniptr;

/* Universal Type (the size is always (size_t))
 * Always be careful of whether your machine Little Endian (LE) or Big Endian (BE)*/
typedef union type_t {
    size_t  base;   /* container */
    void*   ptr;    /* pointer */

    int64_t int64;
    int32_t int32;
    int16_t int16;
    int8_t  int8;

    uint64_t uint64;
    uint32_t uint32;
    uint16_t uint16;
    uint8_t  uint8;

    // Always be careful when converting these 2 values
    float   f;
    double  lf;
    // long double llf;
} type_t, unitype, __template;

typedef union type_m {
    size_t base;
    uint64_t QWORD;
    uint32_t DWORD[2];
    uint16_t WORD[4];
    uint8_t  BYTE[8];
} union_t, type_m;

TEMP
#define TYPE_T   0
#define TYPE_PTR 0xff
#define TYPE_F   1
#define TYPE_LF  2
#define TYPE_8   3
#define TYPE_8U  4
#define TYPE_16  5
#define TYPE_16U 6
#define TYPE_32  7
#define TYPE_32U 8
#define TYPE_64  9
#define TYPE_64U 10

/* Template for Pseudo Polymorphism
 * dataType is implementation defined, standard DataType:
 *
 * 0 (default) - size_t
 * 0xff - pointer
 * 
 * 1 - float
 * 2 - double
 * 
 * 3, 4 - int8, uint8
 * 5, 6 - int16, uint16
 * 7, 8 - int32, uint32
 * 9, 10 - int64, uint64  (if available)
 */
TEMP typedef struct pseudoTemplate {
    uint8_t dataType;
    __template T;
} template_s;

#endif

#define CONSTINIT(type, ptr, value) (*(type*) ptr = value)
#if DEPRECATED(04/11/2023)
/* Assign value to const variables (WARNING: Overwriting const is Highly DISCOURAGED)
 * Avoid putting address in "read-only" memory section (.rdata) leading to SEGFAULT in most systems
 * typically in (Global const variables, string literals, ...)
 *
 * data_type:
 * 1 - (char / BYTE) 
 * 2 - (short / WORD)
 * 3 - (long / DWORD) 
 * 4 - (long long / QWORD) 
 * default - system default (int)
 */
DEFCON_2 void constInit(register const void* ptr, register unsigned long long init_value, register int data_type) {
    // switch (type_size)
    // {
    // case 0: *(unsigned int*)      ptr = init_value; break;
    // case 1: *(unsigned char*)      ptr = init_value; break;
    // case 2: *(unsigned short*)     ptr = init_value; break;
    // case 3: *(unsigned long*)      ptr = init_value; break;
    // case 4: *(unsigned long long*) ptr = init_value; break;

    // default:  *(unsigned int*)      ptr = init_value; break;
    // }

    // these if else produce better jump table than (switch case)
    if (data_type == 1) {*(unsigned char*)      ptr = init_value; return;}
    if (data_type == 2) {*(unsigned short*)     ptr = init_value; return;}
    if (data_type == 3) {*(unsigned long*)      ptr = init_value; return;}
    if (data_type == 4) {*(unsigned long long*) ptr = init_value; return;}
    *(unsigned int*)      ptr = init_value; return;
}

/* Assign value to const float (WARNING: Overwriting const is Highly DISCOURAGED)
 * the function overwrite Read-only section of memory (please ensure the data_type right) 
 */
DEFCON_2 void constinit_f(register const void* ptr, register float init_value) {
    *(float*) ptr = init_value;
}

/* Assign value to const double (WARNING: Overwriting const is Highly DISCOURAGED)
 * the function overwrite Read-only section of memory (please ensure the data_type right) 
 */
DEFCON_2 void constinit_lf(register const void* ptr, register double init_value) {
    *(double*) ptr = init_value;
}
#endif

#define RESET_ARR(array, n) while(n != 0) array[n--] = NUL;

int aa() {
    
}

STD_AVAILABLE DEFCON_BETA int memreset(void* baseptr, int size);
STD_AVAILABLE DEFCON_BETA int memreset_t(void* baseptr, int size);
    TEMPSOL DEFCON_BETA int   memreset_t2(void* baseptr, int size);
    TEMPSOL DEFCON_BETA int   memreset_t3(void* baseptr, int size);

STD_AVAILABLE DEFCON_BETA void memcpy_h( void* from,  void* to, unsigned int len);

STD_AVAILABLE DEFCON_BETA int memcmp_h(void* addr1, void* addr2, unsigned int len);
STD_AVAILABLE DEFCON_BETA int memcmp_h(void* addr1, void* addr2, unsigned int len);
STD_AVAILABLE DEFCON_BETA int memncmp_h(void* addr1, void* addr2, unsigned int len);

DEFCON_BETA void memmov(void* from, void* to, unsigned int len);


// reset chunk of contiguous memory to 0 (please ensure the size is right)
STD_AVAILABLE DEFCON_BETA int memreset(register void* baseptr, register int size) {
    register byte* address = baseptr;
    baseptr = (address + size);
    for (; baseptr != address ; address++) {
        *address = NUL; 
    }
    return size;
}

// reset chunk of contiguous memory to 0 (for large memory)
STD_AVAILABLE DEFCON_BETA int memreset_t(void* baseptr, register int size) {
    
    register byte *end_ptr = ((byte*) baseptr + (size & (sizeof(size_t) - 1)));

    // if (size & 0x1) {*(unsigned char *) address = 0; address += sizeof(unsigned char);}
    // if (size & 0x2) {*(unsigned short *) address = 0; address += sizeof(unsigned short);}
    // if (size & 0x4) {*(unsigned long *) address = 0; address += sizeof(unsigned long);}

    for (register byte* address = baseptr; address != end_ptr ; address++) { *(unsigned char *) address = 0; }

    end_ptr += (size & ( ~(sizeof(size_t) - 1) ));
    for (register size_t* address = baseptr; (void*) end_ptr != (void*) address ; address++) {
        *(size_t *) address = 0;
    }
    
    return (end_ptr - (byte*) baseptr);
}

STD_AVAILABLE DEFCON_BETA int memreset_t2(void* baseptr, register int size) {
    
    register size_t* address = baseptr;
    for ( ; size >= sizeof(size_t) ; size -= sizeof(size_t)) {
        *address = NUL; address++;
    }
    
    address = address + memreset(address, size);

    return ( (byte*) address - (byte*) baseptr);
}
STD_AVAILABLE DEFCON_BETA int memreset_t3(void* baseptr, register int size) {
    
    register size_t* address = baseptr;
    register byte* endptr = (byte*) address + (size & ~(sizeof(size_t) - 1));
    for ( ; (byte*) address != endptr; address++) {
        *address = NUL;
    }
    
    address = (size_t*) ((byte*) address + memreset(address, size & (sizeof(size_t) - 1)));

    return ( (byte*) address - (byte*) baseptr);
}



// memory copy
STD_AVAILABLE DEFCON_BETA void memcpy_h(register void* from, register void* to, unsigned int len) {
    register void* end = (byte*) from + len;
    for (; end != from ; ) {
        *(byte*) to = *(byte*) from;
        from = (byte*) from + 1; 
        to   = (byte*) to + 1;
    }
}

// memory compare
STD_AVAILABLE DEFCON_BETA int memcmp_h(register void* addr1, register void* addr2, register unsigned int len) {
    for ( ; len != 0 ; len--) {
        if (*(byte*) addr1 != *(byte*) addr2) return FALSE;
        addr1 = (byte*) addr1 + 1; 
        addr2 = (byte*) addr2 + 1;
    }
    return TRUE;
}

// memory compare with extended boolean
STD_AVAILABLE DEFCON_BETA int memcmp_hc(register void* addr1, register void* addr2, register unsigned int len) {
    for ( ; len != 0 ; len--) {
        if (*(byte*) addr1 != *(byte*) addr2)
            return (*(byte*) addr1 > *(byte*) addr2) ? BOOL_P : BOOL_N;
        addr1 = (byte*) addr1 + 1; 
        addr2 = (byte*) addr2 + 1;
    }
    return BOOL_E;
}

// compare and find the max length of similiarty
STD_AVAILABLE DEFCON_BETA int memcmp_hl(register void* addr1, register void* addr2, register unsigned int len) {
    unsigned int maxlen = len;
    for ( ; len != 0 ; len--) {
        if (*(byte*) addr1 != *(byte*) addr2) break;
        addr1 = (byte*) addr1 + 1; 
        addr2 = (byte*) addr2 + 1;
    }
    return (maxlen - len);
}


// memory move
DEFCON_BETA void memmov(register void* from, register void* to, register unsigned int len) {

    for (; len != 0 ; len--) {
        *(byte*) to = *(byte*) from;
        *(byte*) from = NUL;
        from = (byte*) from + 1;
        to   = (byte*) to   + 1;   /* assume it's incremented on BYTE level */
    }
}

#if DISABLED(4/11/2023, 0)
/* memory print mode:
 * 0 - bin
 * 1 - value
 * default - hex
 */
EXPERIMENTAL void memprint(register void* address, unsigned int len, uint8_t mode) {
    register uint8_t value = 0;

    // print the address
    printf("0x%x ~ 0x%x|", address, (address + len - 1));

    for (int i = 0; len != 0 ; i++, len--)
    {
        putchar(' ');

        // fetch the memory
        value = *(uint8_t*) address;
        address++;
    
        // print
        if (mode == 0) for (register int i = (sizeof(uint8_t) * 8) - 1; i >= 0 ; i--){

            putchar((value & (1ULL << i)) ? '1' : '0');     /* check and print the result */
            // ((i % 8) == 0) ? putchar(' ') : 0;  /* bit section length for easy readability */
        }
        else printf((mode == 1) ? "%u" : "%2x", value);
    }
}

EXPERIMENTAL void memprint_h(register void* address, uint8_t sizeof_type, unsigned int len, uint8_t mode) {

    if (mode > 2) {printf("[WARNING] memprint_h | Invalid mode: %u \n", mode); return;}

    register void* end_ptr = address + (len * sizeof_type);

    for ( ; address < end_ptr ; len--, address++)
    {
        // print the address
        printf("0x%llx | ", address);

        // print the value
        if (mode == 0) for (register int i = 7; i >= 0 ; i--) {
            putchar(( *(uint8_t*) address & (1ULL << i)) ? '1' : '0');     /* check and print the result */
        }
        else printf((mode == 1) ? "%u" : "%2x", *(uint8_t*) address);

        putchar('\n');
    }
   
}

// Memory print
TEMP void memprint_t(void* address, unsigned int len, int mode) {
    size_t value;
    int n;

    // print the address
    printf("0x%llx ~ 0x%llx|", address, address + len);

    for (int i = 0 ; len != 0 ; i++)
    {
        // fetch the memory
        if (len & (~0x7))   {value = *(uint64_t*) address; len -= sizeof(uint64_t); address += sizeof(uint64_t);}
        else if (len & 0x4) {value = *(uint32_t*) address; len -= sizeof(uint32_t); address += sizeof(uint32_t);}
        else if (len & 0x2) {value = *(uint16_t*) address; len -= sizeof(uint16_t); address += sizeof(uint16_t);}
        else if (len & 0x1) {value = *(uint8_t*) address; len -= sizeof(uint8_t); address += sizeof(uint8_t);}
    
        // print the value
        for (int i = (len * 8) - 1; i >= 0 ; i--){

            putchar((value & (1ULL << i)) ? '1' : '0');     /* check and print the result */
            ((i % 8) == 0) ? putchar(' ') : 0;  /* bit section length for easy readability */
        }
    }
}
#endif


#endif