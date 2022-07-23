#include "../include/sha256.h"
#include "../include/crypto.h"
#include "../include/string.h"
#include "../include/memory.h"
#include "../include/tty.h"

void sha256(char *message)
{
    /* Note 1: All variables are 32 bit uint32_tegers and addition is calculated modulo 2^32
    Note 2: For each round, there is one round constant k[i] and one entry in the message schedule array w[i], 0 ≤ i ≤ 63
    Note 3: The compression function uses 8 working variables, a through h
    Note 4: Big-endian convention is used when expressing the constants in this pseudocode,
    and when parsing message block data from bytes to words, for example,
    the first word of the input message "abc" after padding is 0x61626380 */

    // Initialize hash values:
    // (first 32 bits of the fractional parts of the square roots of the first 8 primes 2..19):
    uint32_t h0 = 0x6a09e667;
    uint32_t h1 = 0xbb67ae85;
    uint32_t h2 = 0x3c6ef372;
    uint32_t h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f;
    uint32_t h5 = 0x9b05688c;
    uint32_t h6 = 0x1f83d9ab;
    uint32_t h7 = 0x5be0cd19;

    // Initialize array of round constants:
    // (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311):
    uint32_t k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

    int i, j = 0;
    unsigned char aux[SIZE][4];
    uint32_t WORD[SIZE];
    uint32_t w[SIZE];

    for (i = 0; i < SIZE; i++)
    {
        WORD[i] = 0;
    }

    // Step 1 - Convert message to binary
    while (message[j] != '\0')
    {
        WORD[j] = (uint32_t)message[j];
        j++;
    }

    // Step 2 - pad data with zeros

    // Step 3 - append a single bit
    WORD[j] = 0b10000000;

    // Step 4 - append length of message at the end
    WORD[SIZE - 1] = strlen(message) * sizeof(char) * 8;

    // Step 5 - Copy data from step 1 into new array with 32-bits words
    for (i = 0; i < SIZE; i++)
    {
        w[i] = concatenate_bits(WORD[4 * i], WORD[4 * i + 1], WORD[4 * i + 2], WORD[4 * i + 3]);
    }

    for (i = 16; i < SIZE; i++)
    {
        w[i] = 0;
    }

    // Step 6 - Modify the zero-ed indexes at the end of the array
    for (i = SIZE / 4; i < SIZE; i++)
    {
        uint32_t s0, s1;
        s0 = _rotr(w[i - 15], 7) ^ _rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
        s1 = _rotr(w[i - 2], 17) ^ _rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    // Step 7 - Compression
    uint32_t a = h0;
    uint32_t b = h1;
    uint32_t c = h2;
    uint32_t d = h3;
    uint32_t e = h4;
    uint32_t f = h5;
    uint32_t g = h6;
    uint32_t h = h7;

    for (i = 0; i < SIZE; i++)
    {
        uint32_t S0, S1, temp1, temp2, ch, maj;

        S1 = _rotr(e, 6) ^ _rotr(e, 11) ^ _rotr(e, 25);
        ch = (e & f) ^ ((~e) & g);
        temp1 = (h + S1 + ch + k[i] + w[i]) % _2E32;
        S0 = _rotr(a, 2) ^ _rotr(a, 13) ^ _rotr(a, 22);
        maj = (a & b) ^ (a & c) ^ (b & c);
        temp2 = (S0 + maj) % _2E32;
        h = g;
        g = f;
        f = e;
        e = (d + temp1) % _2E32;
        d = c;
        c = b;
        b = a;
        a = (temp1 + temp2) % _2E32;
    }

    // Step 8 - modify final values
    h0 = (h0 + a) % _2E32;
    h1 = (h1 + b) % _2E32;
    h2 = (h2 + c) % _2E32;
    h3 = (h3 + d) % _2E32;
    h4 = (h4 + e) % _2E32;
    h5 = (h5 + f) % _2E32;
    h6 = (h6 + g) % _2E32;
    h7 = (h7 + h) % _2E32;

    // Final step - concatenate
    unsigned char digest[256];
    sprintf(digest, "%x%x%x%x%x%x%x%x", h0, h1, h2, h3, h4, h5, h6, h7);
    printf("\n%s", digest);
}