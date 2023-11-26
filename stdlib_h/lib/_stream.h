#ifndef __STREAM_H
#define __STREAM_H

#include <stdio.h>
#include "mem_ex.h"

#define PAGESIZE 0x1000
#define MAX_ACTIVE_STREAM 32 /* specify the maximum output stream buffer */
#if MAX_ACTIVE_STREAM == 0
    #error MAX_ACTIVE_STREAM cannot be 0: No active stream
#endif

// THE STATIC STREAM STRUCTURE
/* MAIN STREAM
 * Similar to stdout and stdin buffer, this is the core stream
 * to store temporary buffer when executing system methods
 * 
 * The stream datatype structure is opaque and shall be maintained by the system
 *  
 *  Size : PAGESIZE (4096 bytes)
 *  Var  : __mainOBuf, __mainIBuf
 */

/* SECONDARY STREAM
 * Any system execution will always use main stream, exept for following conditions:
 * - The required buffer size to execute a method is larger than PAGESIZE (4096 bytes)
 * - User defined methods or functions
 * - Multiple statically temporary buffer
 * 
 * size : Variable
 * Variable : __OStream (list of all the stream address) (will be recycled after met its maximum)
 *            __curOStream (current pointer to the __OStream)
 */

CORE_H PRIVATE GLOBAL char __mainOBuf[PAGESIZE];
CORE_H PRIVATE GLOBAL char __mainIBuf[PAGESIZE];

// Main Output Stream container (One time use)
CORE_H PRIVATE GLOBAL void* __OStream[MAX_ACTIVE_STREAM] = { 0 };
CORE_H PRIVATE GLOBAL void* __IStream[MAX_ACTIVE_STREAM] = { 0 };
CORE_H PRIVATE GLOBAL unsigned int __curOStream = 0;
CORE_H PRIVATE GLOBAL unsigned int __curIStream = 0;

// return n then increments it, if n above max reset to 0
#define _MAXINC(n, max) (n < (max)) ? n++ : (n = 0)

CORE_H void* _getOStream(unsigned int size);
CORE_H void* _getIStream(unsigned int size);

// request for output stream memory allocation
CORE_H void* _getOStream(register unsigned int size) {
    register void** ptr = &__OStream[__curOStream];
    
    memswap_s(ptr, size);       /* solution 1 */
    *ptr = memswap(*ptr, size); /* solution 2 */

    if (__curOStream < MAX_ACTIVE_STREAM) { __curOStream++; }
    else                                  { __curOStream = 0; }

    return *ptr;
}

CORE_H void* _getIStream(register unsigned int size) {
    register void** ptr = &__IStream[__curIStream];
    
    memswap_s(ptr, size);       /* solution 1 */
    *ptr = memswap(*ptr, size); /* solution 2 */

    if (__curIStream < MAX_ACTIVE_STREAM) { __curIStream++; }
    else                                  { __curIStream = 0; }

    return *ptr;
}

#endif