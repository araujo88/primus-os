#ifndef _RANDOM_H
#define _RANDOM_H 1
#include "math.h"
#include "time.h"
#include "stdint.h"

static uint32_t seed = 0;

#define RAND_MAX 4294967295 // 2^32 - 1
#define NORM 2.328306549295728e-10

double rand();
void srand();

#endif