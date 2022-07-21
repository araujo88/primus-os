#include "../include/math_shell.h"
#include "../include/string.h"

#include "stdint.h"

uint32_t parse_int(char *string)
{
    uint32_t i;
    char *parser = 0;
    while (string[i] != ')')
    {
        strcat(parser, string[i]);
    }
    strcat(parser, '\0');
    return atoi(parser);
}