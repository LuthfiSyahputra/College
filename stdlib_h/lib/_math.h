#ifndef _MATHEMATICS_H
#define _MATHEMATICS_H

#include "src_info.h"
#include "std_constants.h"
#include <stdint.h>


#define ABSOLUTE(value) ((value < 0) ? -value : value)
#define NORMALIZE(value, max)       (value / max)
#define NORMALIZE_K(value, max, k) ((value / max) * k)


float normalize(register float input, register float max);
double normalize_lf(register double input, register double max);

float normalize(register float input, register float max) {
    return input / max;
}
double normalize_lf(register double input, register double max) {
    return input / max;
}




#endif