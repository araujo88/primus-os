#ifndef _MATH_H
#define _MATH_H 1

#include "stdint.h"

uint32_t fact(uint32_t n);
float combination(uint32_t n, uint32_t r);
float pow(float x, uint32_t n);
float sqrt(float x);
float inv_sqrt(float x);
float sin(float x);
float cos(float x);
float tan(float x);
float asin(float x);
float acos(float x);
float atan(float x);
float sinh(float x);
float cosh(float x);
float tanh(float x);
float asinh(float x);
float acosh(float x);
float atanh(float x);
float exp(float x);
float log(float x);
float log10(float x);

#endif