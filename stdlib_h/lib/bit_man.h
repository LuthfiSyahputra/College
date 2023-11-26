#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

// standard fixed data types based on GCC
#ifndef _STDINT_H
typedef signed char int8_t;
typedef signed short int16_t;
// typedef signed int int32_t;
typedef signed long int32_t;   /* (long) has the same size as (int) in windows MinGW GCC Compiler */
typedef signed long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
// typedef unsigned int uint32_t;
typedef unsigned long uint32_t; /* (ulong) has the same size as (uint) in windows MinGW GCC Compiler */
typedef unsigned long long uint64_t;

#endif

// Bit level manipulation (with bitwise operators)
// NOTE: input and operand data type "size" must be the same to avoid overflow errors

// Bitwise Operators
#define BIT_OR(a, b)    (a | b) /* Bitwise or */
#define BIT_AND(a, b)   (a & b) /* Bitwise and */
#define BIT_XOR(a, b)   (a ^ b) /* Bitwise xor */
#define BIT_INV(a)       (~a)   /* Bitwise ternary (inverse) */


// Bit Switch
#define BIT_S0(data, operand)  (data ^ (data & operand)) /* Switch bits to 0 */
#define BIT_S0T(data, operand) (data & (~operand))       /* Switch bits to 0 but with different method */
#define BIT_S1(data, operand)  (data | operand)          /* Switch bits to 1 */

#define BIT_S(data, operand)   (data ^ operand)          /* Switch bits */

// Bit shift
#define BIT_SR(data, offset) (data >> offset)
#define BIT_SL(data, offset) (data << offset)


// check a bit status stored in "special" status byte (same as AND '&' bitwise operator) returns either true or false
#define BIT_CHECK(input, check) (input & check)

// check a specific bit position (bitpos starts from 0 at leftmost bit, returns either 1[TRUE] or 0[FALSE])
#define BITCHK(data, bitpos) ((data >> bitpos) & 1U)

/* check a specific bit position (returns either 0[FALSE] or 2^bitpos)
 * bitpos starts from 0 at leftmost bit
 *
 * for compilers that "not clever enough" to optimize
 * if still slow, just use bitwise and (&) with constant instead (BIT_CHECK)
*/
#define BITCHK_S(data, bitpos) (data & (1ULL << bitpos))

#ifndef BIT_DATATYPE
#define BIT_DATATYPE 4
struct _bit8{
    uint8_t _0  : 1, _1  : 1, _2  : 1, _3  : 1, _4  : 1, _5  : 1, _6  : 1, _7  : 1;
};

struct _bit16 {
    uint16_t _0  : 1, _1  : 1, _2  : 1, _3  : 1, _4  : 1, _5  : 1, _6  : 1, _7  : 1,
             _8  : 1, _9  : 1, _10 : 1, _11 : 1, _12 : 1, _13 : 1, _14 : 1, _15 : 1;
};

struct _bit32 {
    uint32_t _0  : 1, _1  : 1, _2  : 1, _3  : 1, _4  : 1, _5  : 1, _6  : 1, _7  : 1,
             _8  : 1, _9  : 1, _10 : 1, _11 : 1, _12 : 1, _13 : 1, _14 : 1, _15 : 1,
             _16 : 1, _17 : 1, _18 : 1, _19 : 1, _20 : 1, _21 : 1, _22 : 1, _23 : 1,
             _24 : 1, _25 : 1, _26 : 1, _27 : 1, _28 : 1, _29 : 1, _30 : 1, _31 : 1;
};

struct _bit64 {
    uint64_t _0  : 1, _1  : 1, _2  : 1, _3  : 1, _4  : 1, _5  : 1, _6  : 1, _7  : 1,
             _8  : 1, _9  : 1, _10 : 1, _11 : 1, _12 : 1, _13 : 1, _14 : 1, _15 : 1,
             _16 : 1, _17 : 1, _18 : 1, _19 : 1, _20 : 1, _21 : 1, _22 : 1, _23 : 1,
             _24 : 1, _25 : 1, _26 : 1, _27 : 1, _28 : 1, _29 : 1, _30 : 1, _31 : 1,
             _32 : 1, _33 : 1, _34 : 1, _35 : 1, _36 : 1, _37 : 1, _38 : 1, _39 : 1,
             _40 : 1, _41 : 1, _42 : 1, _43 : 1, _44 : 1, _45 : 1, _46 : 1, _47 : 1,
             _48 : 1, _49 : 1, _50 : 1, _51 : 1, _52 : 1, _53 : 1, _54 : 1, _55 : 1,
             _56 : 1, _57 : 1, _58 : 1, _59 : 1, _60 : 1, _61 : 1, _62 : 1, _63 : 1;
};

typedef union bitf8 {
    uint8_t u;
    struct _bit8 b;
} bit8_t;

typedef union bitf16 {
    uint16_t u;
    struct _bit16 b;
} bit16_t;

typedef union bitf32 {
    uint32_t u;
    struct _bit32 b;
} bit32_t;

typedef union bitf64 {
    uint64_t u;
    struct _bit64 b;
} bit64_t;

#endif  /* BIT DATATYPE */



#endif