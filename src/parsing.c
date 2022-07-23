#include "../include/parsing.h"
#include "../include/string.h"
#include "../include/limits.h"

#include "stdint.h"

uint32_t parse_int(char *string, char c)
{
    uint32_t i = 0;
    char parser[1024] = "";

    while (string[i] != c)
    {
        parser[i] = string[i];
        i++;
        if (string[i] == '\0')
        {
            return (uint32_t)NULL;
        }
    }
    return atoi(parser);
}

double parse_float(char *string, char c)
{
    uint32_t i = 0;
    char parser[1024] = "";

    while (string[i] != c)
    {
        parser[i] = string[i];
        i++;
        if (string[i] == '\0')
        {
            return EPS;
        }
    }
    return atof(parser);
}

void parse_string(char *parser, char *string, char c)
{
    uint32_t i = 0;

    while (string[i] != c)
    {
        parser[i] = string[i];
        i++;
    }
    parser[i] = '\0';
}