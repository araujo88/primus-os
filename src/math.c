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

uint32_t pow(uint32_t num, uint32_t n)
{
    uint32_t i;
    uint32_t result = 1;
    for (i = 0; i < n; i++)
    {
        result *= num;
    }
    return result;
}
