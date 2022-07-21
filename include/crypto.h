#ifndef _CRYPTO_H
#define _CRYPTO_H 1

#include "stdint.h"

#define _2E32 4294967296
#define SIZE 64
#define ROTL(X, N) ((X << N) | (X >> (32 - N)))
#define ROTR(X, N) ((X >> N) | (X << (32 - N)))

uint32_t _rotl(const uint32_t value, int shift);
uint32_t _rotr(const uint32_t value, int shift);
uint32_t concatenate_bits(uint32_t b1, uint32_t b2, uint32_t b3, uint32_t b4);

#endif