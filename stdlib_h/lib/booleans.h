#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <stdio.h>

// BOOLEAN CONSTANTS
#define TRUE  1
#define FALSE 0

#define BOOL_P  1   /* Boolean Positive (+) */
#define BOOL_0  0   /* Boolean Neutral  (0) */
#define BOOL_N  -1  /* Boolean Negative (-) */

// Compare boolean Macro
#define MORE   (a, b)  (a >  b)
#define MORE_EQ(a, b)  (a >= b)
#define LESS   (a, b)  (a <  b)
#define LESS_EQ(a, b)  (a <= b)
#define EQUAL  (a, b)  (a == b)
#define NOEQUAL(a, b)  (a != b)

#define BETWEEN_EQ(val, min, max) ((val >= min) && (val <= max))
#define BETWEEN(val, min, max)    ((val >  min) && (val <  max))

#define CLAMP(val, min, max) ((val < min) ? min : ((val > max) ? max : val))
#define CLAMP_MIN(val, min) (val < min) ? min : val
#define CLAMP_MAX(val, max) (val > max) ? max : val


typedef unsigned char BOOL_H;
const char* __boolstr__[] = {"FALSE", "TRUE"};

#define boolstr(bool) (bool == FALSE) ? __boolstr__[FALSE] : __boolstr__[TRUE]

// LOGICAL OPERATORS
// #define BUF(a)      (a)
#define INV(a)      (!a)

#define OR(a, b)    (  a || b )
#define NOR(a, b)   (!(a || b))

#define AND(a, b)   (  a && b )
#define NAND(a, b)  (!(a && b))

#define XOR(a, b)   ((!a && b) || ( a && !b))
#define XNOR(a, b)  (( a && b) || (!a && !b))

BOOL_H _buf(register int a) { return  a; }
BOOL_H _inv(register int a) { return INV(a); }

BOOL_H _or(register int a, register int b)   { return OR (a, b); }
BOOL_H _nor(register int a, register int b)  { return NOR(a, b); }

BOOL_H _and(register int a, register int b)  { return AND (a, b); }
BOOL_H _nand(register int a, register int b) { return NAND(a, b); }

BOOL_H _xor(register int a, register int b)  { return XOR (a, b); }
BOOL_H _xnor(register int a, register int b) { return XNOR(a, b); }


#ifdef MOVETO_memex_h
// default integer type binary print
void binary_print(long long value, int sizeof_Type, int bitSection_Length) {

    for (int i = (sizeof_Type * 8) - 1; i >= 0 ; i--){
        putchar((value & (1ULL << i)) ? '1' : '0');     /* check and print the result */
        if (bitSection_Length)                          /* bit section length for easy readability */
            (!(i % bitSection_Length)) ? putchar(' ') : 0;
    }
}

// print a signed integer type value with its binary (value_name is optional (0 // NULL if undefined))
void value_print(long long value, int sizeof_Type, int bitSection_Length, char* value_name) {
    STD_STRING(value_name, "value\0");
    printf("%s: %12lld\t| ",value_name, value);
    binary_print(value, sizeof_Type, bitSection_Length);
    putchar('\n');
}

// print an unsigned integer type value with its binary (value_name is optional (0 // NULL if undefined))
void value_print_u(unsigned long long value, int sizeof_Type, int bitSection_Length, char* value_name) {
    STD_STRING(value_name, "value\0");
    printf("%s: %12llu\t| ", value_name, value);
    binary_print(value, sizeof_Type, bitSection_Length);
    putchar('\n');
}
    
// integer type binary print (with reversed bitshift hoping will be faster)
void binaryPrint(long long value, int sizeof_Type) {
    unsigned long long temp_value = (1ULL << ((sizeof_Type * 8) - 1));   /* base temporary test value */
    while (temp_value){
        putchar((value & temp_value) ? '1' : '0');  /* check the bit and print the result */
        temp_value = temp_value >> 1;   /* bit-shift temp_value to the right by 1 */
    }
}

char binaryStr[65];
// integer type binary print (returns the string to be printed)
char* binaryPrint_str(long long value, int sizeof_Type) {
    int n = sizeof_Type * 8;
    unsigned long long temp_value = 0x1ULL;                 /* base temporary test value */

    binaryStr[n] = '\0';  /* null string terminator */
    while (n){
        binaryStr[--n] = (value & temp_value) ? '1' : '0';  /* check the bit and assign the result to binaryStr */
        temp_value = temp_value << 1;                       /* bit-shift temp_value to the left by 1 */
    }
    return binaryStr;
}
#endif

void boolPrint(register int value);
void boolfPrint(register FILE* _stream, register int value);
const char* boolStr(register int value);

void boolPrint(register int value) {
    fprintf(stdout, "%s", boolstr(value));
}

void boolfPrint(register FILE* _stream, register int value) {
    if (_stream == NULL) _stream = stdout;
    fprintf(_stream, "%s", boolstr(value));
};

const char* boolStr(register int value) {
    return boolstr(value);
}

#ifdef TEMP_DISABLE
// Boolean Value Print
void boolPrint_s(int value) {
    if      (value == TRUE)  printf("TRUE");
    else if (value == FALSE) printf("FALSE");
    else    printf("\n%s Incorrect Boolean Value ( value: %d )\n", DEBUG_WARNING, value);
}

// Boolean Value Print (return the string)
char* boolStr_s(int value) {
    if      (value == TRUE)  return "TRUE";
    else if (value == FALSE) return "FALSE";
    else    {printf("\n%s Incorrect Boolean Value ( value: %d )\n", DEBUG_WARNING, value); return 0;}
}

#endif

/* Assign bit in reg_varible (value should be either TRUE or FALSE)
   Position is based on 'n' in (2^n), ex: 2^0 = 1 (n = 0) */
#ifdef DISABLED  /* Type safe fixed bit assign */
#define ASSIGN_FIXED(max_Pos) {\
    if ((position >= 0) && (position <= (max_Pos - 1))) { \
        if ((value == TRUE) || (value == FALSE)) return reg_variable | (value << position); \
        else printf("\n%s value must either TRUE (1) or FALSE (0)\n", DEBUG_WARNING); \
    } \
    else printf("\n%s Invalid Position for %d-bit integer; pos: %d  (should be 0 ~ %d)\n", DEBUG_WARNING, max_Pos, position, max_Pos - 1); \
    return reg_variable; \
}

uint8_t  assignFixed_8bit (uint8_t  value, uint8_t  reg_variable, int position) ASSIGN_FIXED(8); 
uint16_t assignFixed_16bit(uint16_t value, uint16_t reg_variable, int position) ASSIGN_FIXED(16);
uint32_t assignFixed_32bit(uint32_t value, uint32_t reg_variable, int position) ASSIGN_FIXED(32);
uint64_t assignFixed_64bit(uint64_t value, uint64_t reg_variable, int position) ASSIGN_FIXED(64);

/* Assign bit from reg_variable and return the result (value should be either TRUE or FALSE)
 *
 * $ Position is based on 'n' in (2^n), ex: 2^0 = 1 (n = 0)
 * position should be in between the range of the max data type (long long) to avoid overflow resulting in repeating pattern
 * check the (ULL) bit-width in <stdint.h> library; current (unsigned long long) is 64-bit (valid Pos: 0 ~ 63)
 * [warning: this is highly machine dependent]
 * 
 * $ returning data type should be the same or bigger than the input to avoid overflow in type conversion 
*/
unsigned long long assignFixed_bit(unsigned long long value, unsigned long long reg_variable, int position) {
    if ((value == TRUE) || (value == FALSE)) return reg_variable | (value << position);
    else printf("\n%s value must either TRUE (1) or FALSE (0)\n", DEBUG_WARNING);
    return reg_variable;
}


uint8_t  assign_8bit (uint8_t  value, uint8_t  reg_variable) { return reg_variable | value; }
uint16_t assign_16bit(uint16_t value, uint16_t reg_variable) { return reg_variable | value; }
uint32_t assign_32bit(uint32_t value, uint32_t reg_variable) { return reg_variable | value; }
uint64_t assign_64bit(uint64_t value, uint64_t reg_variable) { return reg_variable | value; }

/* Assign bit from reg_variable and return the result (with bitwise OR | operator)
 returning data type should be the same or bigger than the input to avoid overflow in type conversion */
unsigned long long assign_bit(unsigned long long value, unsigned long long reg_variable) { return reg_variable | value; }

#endif

#endif