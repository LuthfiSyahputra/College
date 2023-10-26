#include <stdio.h>
#include "math_ex.h"
#include "_functions.h"

double fl(double x) {


    return (x*x);
}
float f(float x) {
    return fl(x);
}

#define SECTIONS 200000
double x1 = 0;
double x2 = 83;

int main() {

    float pasterr = 0;
    

    float  result  = integral_ub(f, SECTIONS, x1, x2);
    double result2 = integral_ubl(fl, SECTIONS, x1, x2);
    double  result3 = integral_tzl(fl, SECTIONS, x1, x2);

    double expected = (1.0/3.0) * (pow(x2, 3) - pow(x1, 3));
    float  error    = expected - result;
    float  error2   = expected - result2;
    float  error3   = expected - result3;


    printf("sum: %f  expected: %f  (+- %f) [ %f ]\n", result, expected, error, pasterr - error);
    printf("sum: %lf  expected: %lf  (+- %lf)\n", result2, expected, error2);
    printf("sum: %lf  expected: %lf  (+- %lf)\n\n", result3, expected, error3);

    // printf("derivative: %f\n", derivative(f, x2));

    for (float i = 0; i < 1; i++)
    {
        float resultd = _derivative(f, x2, 1 * i);
        float expect = 2 * x2;
        float err   = resultd - expect;
        printf("%3.0f| derivative2: %f  expected: %f (+- %f)\n", i, resultd, expect, err);
        /* code */
    }
    

}