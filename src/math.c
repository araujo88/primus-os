#include "../include/math.h"
#include "../include/bool.h"

#define PI 3.14159265358979323846

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
    uint32_t n;
    double result = 0.;
    double coeffs[4] = {1., -0.16666, 0.0083143, -0.00018542};

    for (n = 0; n < 4; n++)
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