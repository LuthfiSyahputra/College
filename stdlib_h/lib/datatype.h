#ifndef STDH_DATATYPE_H
#define STDH_DATATYPE_H

#include <stdint.h>
// primitive data type promotion auto-conversion
/*      DATATYPE HIERARCHY 
 *
 *   8   long double
 *   7   double
 *   6   float
 *   5   unsigned long long (uint64_t)
 *   4   (signed) long long (int64_t)
 *   3   unsigned long (uint32_t)
 *   2   (signed) long (int32_t)
 *   1   unsigned int
 *   0   (signed) int
 * 
 *          ^
 *          |
 *  -1   unsigned short (uint16_t) - short (int16_t) - unsigned char (uint8_t) - char (int8_t)
*/

/* 
 * 1. Every arithmetic operation (unary or binary) are in [int] type by default
 *
 * 1b. size and type of [int] is system dependent (typically long on 64-bit system, short on 32-bit system)
 * 1c. pointer type [*] is unsigned (probably) because it has to point addresses from 0x0 to 0xffffffffffffffff
 * 1d. even pointer arithmetics have to be able to return signed in subtraction
 *
 * 2. Whenever there are two operands of different data types in an expression, 
 *   the operand with a lower rank will be converted (promoted) to the datatype of higher rank operand.
 * 
 * 3. As point no.1 stands, special case occur in type lower than [int] such as
 *   [unsigned short], [short], [unsigned char], and [char] will be automatically
 *   promoted to [int] whenever they used in arithmetic operations
 * 
 * n - all arithmetic operations including
 *  fundamental op - [+][-][*][/], modulus op [%]
 *  relational op  - [>][<][>=][<=]
 *  logical op     - [&&][||][!]
 *  bitwise op     - [&][|][^][~][>>][<<]
 *  inc & dec op   - [++][--]
 * 
 *  assignment op  - [=][+=][-=][*=][/=][%=][>>=][<<=][&=][|=][^=][~=]
 * 
 *  
*/

typedef uint8_t  byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;


typedef void* ptr;

#endif