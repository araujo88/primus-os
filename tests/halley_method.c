#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdint.h"
#include <limits.h>

float sqrt_halley(float x)
{
    uint32_t iterations = 5;
    uint32_t i;
    float r = x;

    for (i = 0; i < iterations; i++)
    {
        r = r - (2. * r * r * r - 2. * x * r) / (3. * r * r + x);
    }
    return r;
}

int main(int arc, char *argv[])
{
    uint32_t iterations = atoi(argv[1]);
    uint32_t i;
    float result;

    for (i = 0; i < iterations; i++)
    {
        result = sqrt_halley(2);
    }
    printf("result: %.20f\n", result);

    return 0;
}