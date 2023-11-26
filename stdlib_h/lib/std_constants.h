#ifndef STANDARD_CONSTANTS_H
#define STANDARD_CONSTANTS_H

// STANDARD BOOLEAN CONSTANTS
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define WIN_DEFINED (_WIN32 || _WIN64 || __WIN32 || __WIN64 || __WIN32__ || __WIN64__ || __WINNT || __WINNT__)


#ifndef NULL
#define NULL ((void*) 0)
#endif

#define ERR_INVALID -1 /* Invalid Input Error */
#define ERR_UNKNOWN -2 /* Unknown Error */
#define ERR_FORCE   -3 /* Force Exit Error (due to undefined behavior) */

// STANDARD COMPARE BOOLEAN CONSTANTS
#define BOOL_P  1   /* positive (+) | [n > p]  (n more than p) */
#define BOOL_E  0   /* equal    (0) | [n == p] (n equal to p) (can be treated as true in multiple booleans)*/
#define BOOL_0  0   /* equal    (0) | [n == p] (n equal to p) */
#define BOOL_N  -1  /* negative (-) | [n < p]  (n less than p) */
// #define BOOL_CMP(a, b) ((a > b) ? BOOL_P : BOOL_N)

// Standard Input Constants
#ifndef IN
#define IN  1   /* readable input characters */
#endif

#ifndef OUT
#define OUT 0   /* un-readable input (blanks & ASCII Control value) */
#endif

#define END_OF_INDEX -5

#define STRING_TERMINATOR '\0'

// Clear a line sequence on stdout, Based on ANSI screen drivers standard
const char* __clrline__ = "\r\33[K";

// data types
#define reg register    /* just for simplicity */

// standard error
#define stderr_h stderr

/* ==== MACROS ==== */
#define ISBLANK(c)     (c > ' ') ? FALSE : ((c == ' ') || (c == '\t') || (c == '\n'))
#define ISBLANK_EX(c) (c > ' ') ? FALSE : ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r') || (c == STRING_TERMINATOR))

#define NUL          0          /* Literal NULL ( 0 ) */
#define NULL        ((void *)0) /* NULL Pointer (in case it's not yet defined) */

/* Null initialization for arrays, structures, or even arrays of arrays of structures
 * (let the compiler do the hard works "compliers know it the best") */
#define NULL_INIT   { NUL }

#define bitsize(type) (sizeof(type) * 8)
#define ABS(value) ((value < 0) ? -value : value)

// Standard Integer Bit Assignments
#ifndef BIT_CONST_VALUE
#define BIT_CONST_VALUE

#define BIT_NULL    0
#define BIT_8_FULL  0xffU
#define BIT_16_FULL 0xffffU
#define BIT_32_FULL 0xffffffffUL
#define BIT_64_FULL 0xffffffffffffffffULL

/* Use these when needed */
// #define BIT_VALUE_8
// #define BIT_VALUE_16
// #define BIT_VALUE_32
// #define BIT_VALUE_64

#ifdef BIT_VALUE_8
#define BIT_0   0x1U
#define BIT_1   0x2U
#define BIT_2   0x4U
#define BIT_3   0x8U
#define BIT_4   0x10U
#define BIT_5   0x20U
#define BIT_6   0x40U
#define BIT_7   0x80U

#ifdef BIT_VALUE_16
#define BIT_8   0x100U
#define BIT_9   0x200U
#define BIT_10  0x400U
#define BIT_11  0x800U
#define BIT_12  0x1000U
#define BIT_13  0x2000U
#define BIT_14  0x4000U
#define BIT_15  0x8000U

#ifdef BIT_VALUE_32
#define BIT_16  0x10000UL
#define BIT_17  0x20000UL
#define BIT_18  0x40000UL
#define BIT_19  0x80000UL
#define BIT_20  0x100000UL
#define BIT_21  0x200000UL
#define BIT_22  0x400000UL
#define BIT_23  0x800000UL
#define BIT_24  0x1000000UL
#define BIT_25  0x2000000UL
#define BIT_26  0x4000000UL
#define BIT_27  0x8000000UL
#define BIT_28  0x10000000UL
#define BIT_29  0x20000000UL
#define BIT_30  0x40000000UL
#define BIT_31  0x80000000UL

#ifdef BIT_VALUE_64
#define BIT_32  0x100000000ULL
#define BIT_33  0x200000000ULL
#define BIT_34  0x400000000ULL
#define BIT_35  0x800000000ULL
#define BIT_36  0x1000000000ULL
#define BIT_37  0x2000000000ULL
#define BIT_38  0x4000000000ULL
#define BIT_39  0x8000000000ULL
#define BIT_40  0x10000000000ULL
#define BIT_41  0x20000000000ULL
#define BIT_42  0x40000000000ULL
#define BIT_43  0x80000000000ULL
#define BIT_44  0x100000000000ULL
#define BIT_45  0x200000000000ULL
#define BIT_46  0x400000000000ULL
#define BIT_47  0x800000000000ULL
#define BIT_48  0x1000000000000ULL
#define BIT_49  0x2000000000000ULL
#define BIT_50  0x4000000000000ULL
#define BIT_51  0x8000000000000ULL
#define BIT_52  0x10000000000000ULL
#define BIT_53  0x20000000000000ULL
#define BIT_54  0x40000000000000ULL
#define BIT_55  0x80000000000000ULL
#define BIT_56  0x100000000000000ULL
#define BIT_57  0x200000000000000ULL
#define BIT_58  0x400000000000000ULL
#define BIT_59  0x800000000000000ULL
#define BIT_60  0x1000000000000000ULL
#define BIT_61  0x2000000000000000ULL
#define BIT_62  0x4000000000000000ULL
#define BIT_63  0x8000000000000000ULL

#endif  /* 64 - BIT */
#endif  /* 32 - BIT */
#endif  /* 16 - BIT */
#endif  /*  8 - BIT */
#endif  /* BIT_CONST_VALUE */

#endif