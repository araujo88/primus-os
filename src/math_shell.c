#include "../include/math_shell.h"
#include "../include/string.h"

#include "stdint.h"

uint32_t parse_int(char *string, char c)
{
    uint32_t i = 0;
    char parser[1024] = "";

    while (string[i] != c)
    {
        parser[i] = string[i];
        i++;
    }
    return atoi(parser);
}