#include "../include/math.h"
#include "../include/bool.h"
#include "../include/memory.h"

const int tab32[32] = {
    0, 9, 1, 10, 13, 21, 2, 29,
    11, 14, 16, 18, 22, 25, 3, 30,
    8, 12, 20, 28, 15, 17, 24, 7,
    19, 27, 23, 6, 26, 5, 4, 31};

uint32_t log2(uint32_t value)
{
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return tab32[(uint32_t)(value * 0x07C4ACDD) >> 27];
}

typedef union
{
    long long i64;
    double d64;
} dbl_64;

double machine_eps(double value)
{
    dbl_64 s;
    s.d64 = value;
    s.i64++;
    return s.d64 - value;
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

double exp(double x) // quartic spline approximation
{

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

double inv_sqrt(double x)
{
    uint32_t j;
    uint32_t it = 3; // num of iterations Newton-Raphson
    union
    {
        double f;
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

double log(double y)
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

double pow(double x, uint32_t n)
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
        result += coeffs[n] * pow(x, 2 * n + 1);
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
    return sinh(x) / cosh(x);
}