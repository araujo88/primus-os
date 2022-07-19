#include "../include/string.h"

char *ctos(char s[2], const char c)
{
    s[0] = c;
    s[1] = '\0';
    return s;
}

int memcmp(const void *aptr, const void *bptr, size_t size)
{
    const unsigned char *a = (const unsigned char *)aptr;
    const unsigned char *b = (const unsigned char *)bptr;
    size_t i;
    for (i = 0; i < size; i++)
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    return 0;
}

void *memset(void *bufptr, int value, size_t size)
{
    unsigned char *buf = (unsigned char *)bufptr;
    size_t i;
    for (i = 0; i < size; i++)
        buf[i] = (unsigned char)value;
    return bufptr;
}

size_t strlen(const char *str)
{
    size_t ret = 0;
    while (str[ret] != 0)
        ret++;
    return ret;
}

char *strcpy(char *dest, const char *src)
{
    char *tmp = dest;
    while ((*dest++ = *src++) != 0)
        ;
    return tmp;
}

int strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
        s1++, s2++;
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
    while (n--)
        if (*s1++ != *s2++)
            return *(unsigned char *)(s1 - 1) - *(unsigned char *)(s2 - 1);
    return 0;
}

char *strchr(const char *s, int c)
{
    while (*s != (char)c)
        if (!*s++)
            return 0;
    return (char *)s;
}

char *strstr(char *s1, const char *s2)
{
    size_t n = strlen(s2);
    while (*s1)
        if (!memcmp(s1++, s2, n))
            return s1 - 1;
    return 0;
}

char *strcat(char *dest, const char *src)
{
    char *tmp = dest;
    while (*dest)
        dest++;
    while ((*dest++ = *src++) != 0)
        ;
    return tmp;
}

int isupper(char c)
{
    return (c >= 'A' && c <= 'Z');
}

int islower(char c)
{
    return (c >= 'a' && c <= 'z');
}

int isalpha(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\12');
}

int isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

char *ltrim(char *s)
{
    while (isspace(*s))
        s++;
    return s;
}

char *rtrim(char *s)
{
    char *back = s + strlen(s);
    while (isspace(*--back))
        ;
    *(back + 1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}