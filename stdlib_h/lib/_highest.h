#ifndef __HIGHEST_H
#define __HIGHEST_H


#include <stdint.h>
#include <stdlib.h>
#include "std_constants.h"

uint8_t  _highest_b (uint8_t* data, int n);
uint16_t _highest_w (register uint16_t* data, int n);
uint32_t _highest_dw(register uint32_t* data, int n);
uint64_t _highest_qw(register uint64_t* data, int n);
float    _highest_f (register float* data, int n);
double   _highest_lf(register double* data, int n);

void* highest_ft(void* data, int n, int sizeof_data, int (*_cmpFunc)(void*, void*));

// return the address of the highest value data
void* highest_ft(register void* data, int n, int sizeof_data, register int (*_cmpFunc)(void* data, void* max)) {
    register void* max = data;
    for ( ; n != 0; n--) {
        if( TRUE == (*_cmpFunc)(data, max) )
            max = data;
        
        data = (char*) data + sizeof_data;
    }
    return max;
}

uint8_t  _highest_b(register uint8_t* data, register int n) {
    register uint8_t highest = 0;
    register uint8_t tempval;
    for ( ; n > 0 ; n--, data++) {
        tempval = *data;
        if(tempval > highest) highest = tempval;

    }
    return highest;
    

    
}





#endif