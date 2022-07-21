#include "../include/math.h"

uint32_t factorial(uint32_t n)
{
    if (n == 0)
    {
        return 1;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
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
