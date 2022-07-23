#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdint.h"

float inv_sqrt(float x)
{
    uint32_t j;
    uint32_t it = 3; // num of iterations Newton-Raphson
    union
    {
        float f;
        uint32_t i;
    } conv = {.f = x};
    conv.i = 0x5f3759df - (conv.i >> 1);
    for (j = 0; j < it; j++)
    {
        conv.f *= 1.5F - (x * 0.5F * conv.f * conv.f);
    }
    return conv.f;
}

float sqrt2(float x)
{
    return 1. / inv_sqrt(x);
}

int main(int arc, char *argv[])
{
    uint32_t iterations = atoi(argv[1]);
    uint32_t i;
    float result;

    for (i = 0; i < iterations; i++)
    {
        result = sqrt2(2);
    }
    printf("result: %.20f\n", result);

    return 0;
}