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

float combination(uint32_t n, uint32_t r)
{
    return (float)fact(n) / ((float)fact(r) * (float)fact(n - r));
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

float pow(float x, uint32_t n)
{
    uint32_t i;
    double result = 1;
    for (i = 0; i < n; i++)
    {
        result *= x;
    }
    return result;
}

float sin(float x)
{
    uint32_t n;
    float result = 0;
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
        for (n = 0; n < 7; n++)
        {
            result += (pow(-1., n) * pow(x, 2 * n + 1)) / fact(2 * n + 1.);
        }
    }
    else if ((x > PI / 2) && (x <= PI))
    {
        x = PI - x;
        for (n = 0; n < 7; n++)
        {
            result += (pow(-1., n) * pow(x, 2 * n + 1)) / fact(2 * n + 1.);
        }
    }
    else if ((x > PI) && (x <= 3 * PI / 2))
    {
        x = x - PI;
        for (n = 0; n < 7; n++)
        {
            result += (pow(-1., n) * pow(x, 2 * n + 1)) / fact(2 * n + 1.);
        }
        result = -result;
    }
    else if ((x >= 3 * PI / 2) && (x <= 2 * PI))
    {
        x = PI - x;
        for (n = 0; n < 7; n++)
        {
            result += (pow(-1., n) * pow(x, 2 * n + 1)) / fact(2 * n + 1.);
        }
    }
    if (isNegative)
    {
        result = -result;
    }
    return result;
}

float cos(float x)
{
    return sin(PI * 0.5 - x);
}

float tan(float x)
{
    return sin(x) / cos(x);
}