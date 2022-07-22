#ifndef _PARSING_H
#define _PARSING_H 1

#include "stdint.h"

uint32_t parse_int(char *string, char c);
double parse_float(char *string, char c);
void parse_string(char *parser, char *string, char c);

#endif