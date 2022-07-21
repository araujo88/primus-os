#include "../include/crypto.h"

uint32_t _rotl(const uint32_t value, int shift)
{
    if ((shift &= sizeof(value) * 32 - 1) == 0)
        return value;
    return (value << shift) | (value >> (sizeof(value) * 32 - shift));
}

uint32_t _rotr(const uint32_t value, int shift)
{
    if ((shift &= sizeof(value) * 32 - 1) == 0)
        return value;
    return (value >> shift) | (value << (sizeof(value) * 32 - shift));
}

uint32_t concatenate_bits(uint32_t b1, uint32_t b2, uint32_t b3, uint32_t b4)
{

    return (b4) | (b3 << 8) | (b2 << 16) | (b1 << 24);
}