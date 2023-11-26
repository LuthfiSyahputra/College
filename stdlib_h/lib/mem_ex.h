#ifndef MEMORY_EXTENDED_H
#define MEMORY_EXTENDED_H

#include "mem_man.h"
#include "src_info.h"

#include <stdlib.h>
#include "Tools/Debug.h"

// typedef void* memptr;

// standard memory allocation
#define MALLOC(ptr, size) if ((ptr = malloc(size)) == NULL)\
    fprintf(stderr, "%s Error Allocating memory [%llu byte%c]\n", DEBUG_WARNING, size, (size > 1) ? 's' : 0 );

#if DISABLED(6/11/2023, 0)
size_t clampMaxInc(register size_t n, register size_t max);
size_t clampMinInc(register size_t n, register size_t min);
size_t clampMaxDec(register size_t n, register size_t max);
size_t clampMinDec(register size_t n, register size_t min);
size_t clampInc(register size_t n, register size_t max, register size_t min);
size_t clampDec(register size_t n, register size_t max, register size_t min);

size_t clampMaxInc(register size_t n, register size_t max) {
    return (n >= max) ? 0 : n++;
}

size_t clampMinInc(register size_t n, register size_t min) {
    return (++n <= 0) ? min : n;
}

#define _clampMaxInc(n, max) ((n >= max) ? 0 : n++)
#define _clampMinInc(n, min) ((++n <= min) ? min : n)
#define _clampMaxDec(n, max) ((--n > max) ? max : n)
#define _clampMinDec(n, min) ((n <= min) ? 0 : n--)
#define _clampInc(n, min, max)
#define _clampDec(n, min, max)

#endif

#define MEMFREE(memory) {free(memory); memory = NULL;}

void memfree(void** _memory) {
    if(*_memory == NULL) return;
    free(*_memory);
    *_memory = NULL;
}

// free old memory and replace with newly allocated address ptr
void memswap_s(void** _oldMemoryptr, int _newSize) {
    if (*_oldMemoryptr != NULL) MEMFREE(*_oldMemoryptr)
    MALLOC(*_oldMemoryptr, _newSize);
}

void* memswap(void* _oldMemory, int _newSize) {
    if (_oldMemory != NULL) free(_oldMemory);
    return malloc(_newSize);
}



#endif