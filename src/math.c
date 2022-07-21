#include "../include/math.h"

uint32_t factorial(uint32_t n)
{
    uint32_t i, fact = 1;

    for (i = 1; i <= n; i++)
    {
        fact = fact * i;
    }

    return fact;
}

uint32_t pow(uint32_t x, uint32_t n)
{
    uint32_t i;
    uint32_t result = 1;
    for (i = 0; i < n; i++)
    {
        result *= x;
    }
    return result;
}

double sin(double x)
{
    uint32_t i;
    double result = 0;
    for (i = 0; i < 6; i++)
    {
        result += pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
    }
    return result;
}
