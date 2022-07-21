#include "../include/math.h"
#include "../include/bool.h"

#define PI 3.14159265358979323846

uint32_t factorial(uint32_t n)
{
    uint32_t i, fact = 1;

    for (i = 1; i <= n; i++)
    {
        fact = fact * i;
    }

    return fact;
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
        for (n = 0; n < 7; n++)
        {
            result += (pow(-1., n) * pow(x, 2 * n + 1)) / factorial(2 * n + 1.);
        }
    }
    else if ((x > PI / 2) && (x <= PI))
    {
        x = PI - x;
        for (n = 0; n < 7; n++)
        {
            result += (pow(-1., n) * pow(x, 2 * n + 1)) / factorial(2 * n + 1.);
        }
    }
    else if ((x > PI) && (x <= 3 * PI / 2))
    {
        x = x - PI;
        for (n = 0; n < 7; n++)
        {
            result += (pow(-1., n) * pow(x, 2 * n + 1)) / factorial(2 * n + 1.);
        }
        result = -result;
    }
    else if ((x >= 3 * PI / 2) && (x <= 2 * PI))
    {
        x = PI - x;
        for (n = 0; n < 7; n++)
        {
            result += (pow(-1., n) * pow(x, 2 * n + 1)) / factorial(2 * n + 1.);
        }
    }
    if (isNegative)
    {
        result = -result;
    }
    return result;
}