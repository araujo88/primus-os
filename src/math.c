#include "../include/math.h"
#include "../include/bool.h"

uint32_t fact(uint32_t n)
{
    uint32_t i, fact = 1;

    for (i = 1; i <= n; i++)
    {
        fact = fact * i;
    }

    return fact;
}

float inv_sqrt(float x)
{
    union
    {
        float f;
        uint32_t i;
    } conv = {.f = x};
    conv.i = 0x5f3759df - (conv.i >> 1);
    conv.f *= 1.5F - (x * 0.5F * conv.f * conv.f);
    return conv.f;
}

float sqrt(float x)
{
    return 1. / inv_sqrt(x);
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