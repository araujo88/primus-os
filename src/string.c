#include "../include/string.h"
#include "../include/limits.h"

#include "stdarg.h"
#include "stdint.h"

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
    return NULL;
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

char *toupper(char *string)
{
    for (char *p = string; *p != '\0'; p++)
    {
        if (*p >= 'a' && *p <= 'z') // Only if it's a lower letter
            *p -= 32;
    }
    return string;
}

char *tolower(char *string)
{
    for (char *p = string; *p != '\0'; p++)
    {
        if (*p >= 'A' && *p <= 'Z') // Only if it's a lower letter
            *p += 32;
    }
    return string;
}

static char *sitoa(char *buf, unsigned int num, int width, enum flag_itoa flags)
{
    unsigned int base;
    if (flags & BASE_2)
        base = 2;
    else if (flags & BASE_10)
        base = 10;
    else
        base = 16;

    char tmp[32];
    char *p = tmp;
    do
    {
        int rem = num % base;
        *p++ = (rem <= 9) ? (rem + '0') : (rem + 'a' - 0xA);
    } while ((num /= base));
    width -= p - tmp;
    char fill = (flags & FILL_ZERO) ? '0' : ' ';
    while (0 <= --width)
    {
        *(buf++) = fill;
    }
    if (flags & PUT_MINUS)
        *(buf++) = '-';
    else if (flags & PUT_PLUS)
        *(buf++) = '+';
    do
        *(buf++) = *(--p);
    while (tmp < p);
    return buf;
}

int vsprintf(char *buf, const char *fmt, va_list va)
{
    char c;
    const char *save = buf;

    while ((c = *fmt++))
    {
        int width = 0;
        enum flag_itoa flags = 0;
        if (c != '%')
        {
            *(buf++) = c;
            continue;
        }
    redo_spec:
        c = *fmt++;
        switch (c)
        {
        case '%':
            *(buf++) = c;
            break;
        case 'c':;
            *(buf++) = va_arg(va, int);
            break;
        case 'd':;
            int num = va_arg(va, int);
            if (num < 0)
            {
                num = -num;
                flags |= PUT_MINUS;
            }
            buf = sitoa(buf, num, width, flags | BASE_10);
            break;
        case 'u':
            buf = sitoa(buf, va_arg(va, unsigned int), width, flags | BASE_10);
            break;
        case 'x':
            buf = sitoa(buf, va_arg(va, unsigned int), width, flags);
            break;
        case 'b':
            buf = sitoa(buf, va_arg(va, unsigned int), width, flags | BASE_2);
            break;
        case 's':;
            const char *p = va_arg(va, const char *);
            if (p)
            {
                while (*p)
                    *(buf++) = *(p++);
            }
            break;
        case 'm':;
            const uint8_t *m = va_arg(va, const uint8_t *);
            width = min(width, 64); // buffer limited to 256!
            if (m)
                for (;;)
                {
                    buf = sitoa(buf, *(m++), 2, FILL_ZERO);
                    if (--width <= 0)
                        break;
                    *(buf++) = ':';
                }
            break;
        case '0':
            if (!width)
                flags |= FILL_ZERO;
            // fall through
        case '1' ... '9':
            width = width * 10 + c - '0';
            goto redo_spec;
        case '*':
            width = va_arg(va, unsigned int);
            goto redo_spec;
        case '+':
            flags |= PUT_PLUS;
            goto redo_spec;
        case '\0':
        default:
            *(buf++) = '?';
        }
        width = 0;
    }
    *buf = '\0';
    return buf - save;
}

int sprintf(char *buf, const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    int ret = vsprintf(buf, fmt, va);
    va_end(va);
    return ret;
}

uint32_t atoi(const char *str)
{
    uint32_t sign = 1, base = 0, i = 0;

    // if whitespaces then ignore.
    while (str[i] == ' ')
    {
        i++;
    }

    // sign of number
    if (str[i] == '-' || str[i] == '+')
    {
        sign = 1 - 2 * (str[i++] == '-');
    }

    // checking for valid input
    while (str[i] >= '0' && str[i] <= '9')
    {
        // handling overflow test case
        if (base > INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > 7))
        {
            if (sign == 1)
                return INT_MAX;
            else
                return INT_MIN;
        }
        base = 10 * base + (str[i++] - '0');
    }
    return base * sign;
}