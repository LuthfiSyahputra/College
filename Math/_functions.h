

float slope2(float dx, float dy);

// smallest 32-bit floating-point mantissa unit (2^-23) [x -> 0]
#define _MANTISSA_MINF_ (1.0/(1024.0 * 1024.0 * 8.0))
#define MANTISSA_MINF(x) (x * (_MANTISSA_MINF_))

typedef float(*func)(float x);
typedef float(*func2)(float x, float y);
typedef float(*func3)(float x, float y, float z);
typedef float(*funcn)(int nVar, float a, ...);

float integral_ub(float (*f)(float x), unsigned int sections, float x1, float x2);
double integral_ubl(double (*f)(double x), unsigned int sections, double x1, double x2);

float integral_tz(float (*f)(float x), unsigned int sections, float x1, float x2);
double integral_tzl(double (*f)(double x), unsigned int sections, double x1, double x2);


// this is just an approximation [1 < precision < FLOAT_MAX] (1 for most precise)
float _derivative(float (*f)(float x), float x1, float precision);

// using 32 possible iterations, might be slow if the actual result is 0 { f'(x) = 0 }
float derivative(float (*f)(float x), float x1);

float derivative(float (*f)(float x), float x1) {

    float result = 0;
    float precision = 1.0;

    for (int i = 0; i <= 32 ; i++) {
        result = _derivative(f, x1, precision);
        if(result == 0) precision *= 2.0;
        else            break;
    }
    return result;
}


float _derivative(float (*f)(float x), float x1, float precision) {

    float dx_p = 1.0;
    float dx_n = 0.000000000001f;

    float y1 = (*f)(x1);
    float y2_p = (*f)(x1 + dx_p);
    float y2_n = (*f)(x1 + dx_n);

    float dx = dx_p;
    float dy = y2_p - y1;

    printf("dy: %f  y2: %f  y1: %f dx: %f\n", dy, y2_p, y1, dx);

    // dy / dx
    float result = dy / dx;
    return result;

}

float integral_ub(float (*f)(float x), unsigned int sections, float x1, float x2) {
    float dx = (x2 - x1) / sections;

    float y1, y2;
    float sum = 0;
    float tempval = 0;

    for (int i = 0; i < sections; i++) {
        y1 = (*f)(x1);
        y2 = (*f)(x1 + dx);

        // calculate the (upper) block area
        // tempval = y2;
        tempval = y2 * dx;

        sum += tempval;

        // printf("%3d| {dx: %f} x1: %.4f, y2: %.4f  sum: %f (+ %f)\n", i, dx, x1, y2, sum, tempval);
        x1 += dx;
    }
    // sum *= dx;


    return sum;
}

double integral_ubl(double (*f)(double x), unsigned int sections, double x1, double x2) {
    double dx = (x2 - x1) / sections;

    double y1, y2;
    double sum = 0;
    double tempval = 0;

    for (int i = 0; i < sections; i++) {
        y1 = (*f)(x1);
        y2 = (*f)(x1 + dx);

        // calculate the (upper) block area
        tempval = y2 * dx;
        sum += tempval;

        // printf("%3d| {dx: %lf} x1: %.4lf, y2: %.4lf  sum: %lf (+ %lf)\n", i, dx, x1, y2, sum, tempval);
        x1 += dx;
    }


    return sum;
}


float integral_tz(float (*f)(float x), unsigned int sections, float x1, float x2) {
    float sum = 0;
    float dx = ((x2 - x1) / sections);
    float y1, y2, tempval;

    for (int i = 0; i < sections; i++) {
        y1 = (*f)(x1);
        y2 = (*f)(x1 + dx);

        // trapezodial equation
        tempval = ((y1 + y2) * dx) / 2.0;
        sum += tempval;

        // printf("%3d| {dx: %f} x1: %.4f, y2: %.4f  sum: %f (+ %f)\n", i, dx, x1, y2, sum, tempval);

        x1 += dx;
    }
    
    return sum;
}

double integral_tzl(double (*f)(double x), unsigned int sections, double x1, double x2) {
    double sum = 0;
    double dx = ((x2 - x1) / sections);
    double y1, y2, tempval;

    for (int i = 0; i < sections; i++) {
        y1 = (*f)(x1);
        y2 = (*f)(x1 + dx);

        // trapezodial equation
        tempval = ((y1 + y2) * dx) / 2.0;
        sum += tempval;

        // printf("%3d| {dx: %f} x1: %.4f, y2: %.4f  sum: %f (+ %f)\n", i, dx, x1, y2, sum, tempval);

        x1 += dx;
    }
    
    return sum;
}