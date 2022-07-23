#include "../include/math.h"
#include "../include/bool.h"
#include "../include/limits.h"
#include "../include/memory.h"

// reference: https://developer.download.nvidia.com/cg/index_stdlib.html

double max(double a, double b)
{
    return a > b ? a : b;
}

double min(double a, double b)
{
    return a < b ? a : b;
}

const int tab32[32] = {
    0, 9, 1, 10, 13, 21, 2, 29,
    11, 14, 16, 18, 22, 25, 3, 30,
    8, 12, 20, 28, 15, 17, 24, 7,
    19, 27, 23, 6, 26, 5, 4, 31};

// https://stackoverflow.com/questions/11376288/fast-computing-of-log2-for-64-bit-integers
uint32_t log2(uint32_t x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return tab32[(uint32_t)(x * 0x07C4ACDD) >> 27];
}

typedef union
{
    long long i64;
    double d64;
} dbl_64;

double machine_eps(double x)
{
    dbl_64 s;
    s.d64 = x;
    s.i64++;
    return s.d64 - x;
}

uint32_t fact(uint32_t n)
{
    uint32_t i, fact = 1;

    for (i = 1; i <= n; i++)
    {
        fact = fact * i;
    }

    return fact;
}

double abs(double x)
{
    if (x < 0)
    {
        return -x;
    }
    else
    {
        return x;
    }
}

// https://stackoverflow.com/questions/47025373/fastest-implementation-of-the-natural-exponential-function-using-sse
double exp(double x) // quartic spline approximation
{
    static uint32_t it = 0;
    union
    {
        float f;
        int32_t i;
    } r;

    r.i = (int32_t)(12102203.0f * x) + 127 * (1 << 23);
    int32_t m = (r.i >> 7) & 0xFFFF; // copy mantissa
    // empirical values for small maximum relative error (1.21e-5):
    r.i += (((((((((((3537 * m) >> 16) + 13668) * m) >> 18) + 15817) * m) >> 14) - 80470) * m) >> 11);

    return r.f;
}

// double exp(double x)
// {
//     uint32_t it = 14;
//     uint32_t i;
//     double result = 0;
//     double coeffs[14] = {1.0,
//                          1.0,
//                          0.5,
//                          0.16666666666666666,
//                          0.041666666666666664,
//                          0.008333333333333333,
//                          0.001388888888888889,
//                          0.0001984126984126984,
//                          2.48015873015873e-05,
//                          2.7557319223985893e-06,
//                          2.755731922398589e-07,
//                          2.505210838544172e-08,
//                          2.08767569878681e-09,
//                          1.6059043836821613e-10};

//     for (i = 0; i < 14; i++)
//     {
//         result += ipow(x, i) * coeffs[i];
//     }
//     return result;
// }

double inv_sqrt(double x)
{
    uint32_t j;
    uint32_t it = 3; // num of iterations Newton-Raphson
    union
    {
        float f;
        uint32_t i;
    } r = {.f = x};
    r.i = 0x5f3759df - (r.i >> 1);
    for (j = 0; j < it; j++)
    {
        r.f *= 1.5F - (x * 0.5F * r.f * r.f);
    }
    return r.f;
}

double sqrt(double x)
{
    return 1. / inv_sqrt(x);
}

uint32_t msb(uint32_t v)
{
    static const uint32_t pos[32] = {0, 1, 28, 2, 29, 14, 24, 3,
                                     30, 22, 20, 15, 25, 17, 4, 8, 31, 27, 13, 23, 21, 19,
                                     16, 7, 26, 12, 18, 6, 11, 5, 10, 9};
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v = (v >> 1) + 1;
    return pos[(v * 0x077CB531UL) >> 27];
}

// https://stackoverflow.com/questions/9799041/efficient-implementation-of-natural-logarithm-ln-and-exponentiation
double ln(double y)
{
    uint32_t log2;
    double divisor, x, result;

    log2 = msb((uint32_t)y); // See: https://stackoverflow.com/a/4970859/6630230
    divisor = (double)(1 << log2);
    x = y / divisor; // normalized value between [1.0, 2.0]

    result = -1.7417939 + (2.8212026 + (-1.4699568 + (0.44717955 - 0.056570851 * x) * x) * x) * x;
    result += ((double)log2) * 0.69314718; // ln(2) = 0.69314718

    return result;
}

// double pow(double x, double y)
// {
//     return exp(y * ln(x));
// }

// double pow(double x, double y)
// {
//     uint32_t j;
//     uint32_t it2 = 3; // num of iterations Newton-Raphson
//     uint32_t it = 14;
//     uint32_t i;
//     double result = 0;

//     double coeffs[14] = {1.0,
//                          1.0,
//                          0.5,
//                          0.16666666666666666,
//                          0.041666666666666664,
//                          0.008333333333333333,
//                          0.001388888888888889,
//                          0.0001984126984126984,
//                          2.48015873015873e-05,
//                          2.7557319223985893e-06,
//                          2.755731922398589e-07,
//                          2.505210838544172e-08,
//                          2.08767569878681e-09,
//                          1.6059043836821613e-10};

//     for (i = 0; i < 14; i++)
//     {
//         result += ipow(y, i) * ipow(ln(x), i) * coeffs[i];
//     }

//     for (j = 0; j < it2; j++)
//     {
//         result = result * (2 - result * exp(-y * ln(x)));
//     }

//     return result;
// }

// https://stackoverflow.com/questions/29860973/grokkable-algorithm-to-understand-exponentiation-where-the-exponent-is-floatin
double pow(double x, double y)
{
    if (x < 0 && abs((float)y - y) < EPS)
    {
        return pow(-x, y) * ((uint32_t)(float)y % 2 == 1 ? -1 : 1);
    }
    else if (y < 0)
    {
        return 1 / pow(x, -y);
    }
    else if (y > 1)
    {
        return pow(x * x, y / 2);
    }
    else
    {
        double fraction = 1;
        double result = 1;

        while (y > EPS)
        {
            if (y >= fraction)
            {
                y -= fraction;
                result *= x;
            }

            fraction /= 2;
            x = sqrt(x);
        }
        return result;
    }
}

double log(double x, double y)
{
    return ln(x) / ln(y);
}

double log10(double x)
{
    return ln(x) / 2.3025850929940456840179914546843642076011014886287729760333279009;
}

double ipow(double x, uint32_t n)
{
    uint32_t i;
    double result = 1;
    for (i = 0; i < n; i++)
    {
        result *= x;
    }
    return result;
}

double sin_1st_quadrant(double x)
{
    // uses minimax inequality to improve the taylor series expansion of sine
    // coefficients table: https://gist.github.com/publik-void/067f7f2fef32dbe5c27d6e215f824c91
    uint32_t n;
    double result = 0.;
    double coeffs[14] = {
        1.,
        -0.166666666666666666666666666666666667,
        0.00833333333333333333333333333333333249,
        -0.000198412698412698412698412698412687163,
        2.7557319223985890652557319223196184e-6,
        -2.50521083854417187750521080496821656e-8,
        1.60590438368216145993922833395466244e-10,
        -7.64716373181981647588299477063124316e-13,
        2.81145725434552076069439171257001611e-15,
        -8.22063524662432719823376264616227798e-18,
        1.95729410633894002963134479643128595e-20,
        -3.86817017052978023755526534728704583e-23,
        6.44695024472163654203964763071146247e-26,
        -9.1836788691334994160391130763503121e-29,
    }; // degree 29

    for (n = 0; n < 14; n++)
    {
        result += coeffs[n] * ipow(x, 2 * n + 1);
    }
    return result;
}

double sin(double x)
{
    uint32_t n;
    double result = 0;
    boolean isNegative = false;
    if (x < 0)
    {
        x = -x;
        isNegative = true;
    }
    while (x > (2 * PI))
    {
        x = x - (2 * PI);
    }
    if (x <= PI / 2)
    {
        result = sin_1st_quadrant(x);
    }
    else if ((x > PI / 2) && (x <= PI))
    {
        x = PI - x;
        result = sin_1st_quadrant(x);
    }
    else if ((x > PI) && (x <= 3 * PI / 2))
    {
        x = x - PI;
        result = sin_1st_quadrant(x);
        result = -result;
    }
    else if ((x >= 3 * PI / 2) && (x <= 2 * PI))
    {
        x = PI - x;
        result = sin_1st_quadrant(x);
    }
    if (isNegative)
    {
        result = -result;
    }
    return result;
}

double cos(double x)
{
    return sin(PI * 0.5 - x);
}

double tan(double x)
{
    return sin(x) / cos(x);
}

double sinh(double x)
{
    return 0.5 * (exp(x) - exp(-x));
}

double cosh(double x)
{
    return 0.5 * (exp(x) + exp(-x));
}

double tanh(double x)
{
    double exp2x = exp(2 * x);
    return (exp2x - 1) / (exp2x + 1);
}

double asinh(double x)
{
    return ln(x + sqrt(x * x + 1));
}

double acosh(double x)
{
    return ln(x + sqrt(x * x - 1));
}

double atanh(double x)
{
    return 0.5 * ln((1 + x) / (1 - x));
}

double asin(double x)
{
    boolean negate = (x < 0);
    x = abs(x);
    double ret = -0.0187293;
    ret *= x;
    ret += 0.0742610;
    ret *= x;
    ret -= 0.2121144;
    ret *= x;
    ret += 1.5707288;
    ret = PI * 0.5 - sqrt(1.0 - x) * ret;
    return ret - 2 * (double)negate * ret;
}

double acos(double x)
{
    boolean negate = (x < 0);
    x = abs(x);
    double ret = -0.0187293;
    ret = ret * x;
    ret = ret + 0.0742610;
    ret = ret * x;
    ret = ret - 0.2121144;
    ret = ret * x;
    ret = ret + 1.5707288;
    ret = ret * sqrt(1.0 - x);
    ret = ret - 2 * (double)negate * ret;
    return (double)negate * PI + ret;
}

// https://stackoverflow.com/questions/42537957/fast-accurate-atan-arctan-approximation-algorithm
double atan(double x)
{
    double A = 0.0776509570923569;
    double B = -0.287434475393028;
    return ((A * x * x + B) * x * x + (0.25 * PI - A - B)) * x;
}