#include "../include/tty.h"
#include "../include/string.h"

size_t terminal_row;
size_t terminal_column;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xb8000;
uint8_t terminal_color;
uint16_t *terminal_buffer;

static inline uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t make_vgaentry(char c, uint8_t color)
{
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}

void terminal_initialize(enum vga_color font_color, enum vga_color background_color)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = make_color(font_color, background_color);
    terminal_buffer = VGA_MEMORY;
    size_t y;
    for (y = 0; y < VGA_HEIGHT; y++)
    {
        size_t x;
        for (x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = make_vgaentry(' ', terminal_color);
        }
    }
}

void terminal_scroll()
{
    int i;
    for (i = 0; i < VGA_HEIGHT; i++)
    {
        int m;
        for (m = 0; m < VGA_WIDTH; m++)
        {
            terminal_buffer[i * VGA_WIDTH + m] = terminal_buffer[(i + 1) * VGA_WIDTH + m];
        }
        terminal_row--;
    }
    terminal_row = VGA_HEIGHT - 1;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c)
{
    if (c == '\n' || c == '\r')
    {
        terminal_column = 0;
        terminal_row++;
        if (terminal_row == VGA_HEIGHT)
            terminal_scroll();
        return;
    }
    else if (c == '\t')
    {
        terminal_column += 4;
        return;
    }
    else if (c == '\b')
    {
        terminal_putentryat(' ', terminal_color, terminal_column--, terminal_row);
        terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
        return;
    }
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
        {
            terminal_row = 0;
        }
    }
}

void terminal_write(const char *data, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

int putchar(int ic)
{
    char c = (char)ic;
    terminal_write(&c, sizeof(c));
    return ic;
}

void term_putc(char c, enum vga_color char_color)
{
    unsigned int i = 0; // place holder for text string position
    unsigned int j = 0; // place holder for video buffer position

    int index;
    // Remember - we don't want to display ALL characters!
    switch (c)
    {
    case '\n': // Newline characters should return the column to 0, and increment the row
    {
        terminal_column = 0;
        terminal_row += 2;
        break;
    }

    default: // Normal characters just get displayed and then increment the column
    {
        index = (VGA_WIDTH * terminal_row) + terminal_column; // Like before, calculate the buffer index
        VGA_MEMORY[index] = c;
        VGA_MEMORY[index + 1] = char_color;
        // terminal_column += 2;
        break;
    }
    }

    // What happens if we get past the last column? We need to reset the column to 0, and increment the row to get to a new line
    if (terminal_column >= VGA_WIDTH)
    {
        terminal_column = 0;
        terminal_row++;
    }

    // What happens if we get past the last row? We need to reset both column and row to 0 in order to loop back to the top of the screen
    if (terminal_row >= VGA_WIDTH)
    {
        terminal_column = 0;
        terminal_row = 0;
    }
}

// This function prints an entire string onto the screen
// void term_print(const char *str)
// {
//     int i;
//     for (i = 0; str[i] != '\0'; i++)
//     { // Keep placing characters until we hit the null-terminating character ('\0')
//         term_putc(str[i]);
//     }
// }

static void print(const char *data, size_t data_length)
{
    size_t i;
    for (i = 0; i < data_length; i++)
        putchar((int)((const unsigned char *)data)[i]);
}

int printf(const char *format, ...)
{
    va_list parameters;
    va_start(parameters, format);
    int written = 0;
    size_t amount;
    int rejected_bad_specifier = 0;
    while (*format != '\0')
    {
        if (*format != '%')
        {
        print_c:
            amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
            print(format, amount);
            format += amount;
            written += amount;
            continue;
        }
        const char *format_begun_at = format;
        if (*(++format) == '%')
            goto print_c;
        if (rejected_bad_specifier)
        {
        incomprehensible_conversion:
            rejected_bad_specifier = 1;
            format = format_begun_at;
            goto print_c;
        }
        if (*format == 'c')
        {
            format++;
            char c = (char)va_arg(parameters, int /* char promotes to int */);
            print(&c, sizeof(c));
        }
        else if (*format == 's')
        {
            format++;
            const char *s = va_arg(parameters, const char *);
            print(s, strlen(s));
        }
        else
        {
            goto incomprehensible_conversion;
        }
    }
    va_end(parameters);
    return written;
}

int get_terminal_row(void)
{
    return terminal_row;
}

int get_terminal_col(void)
{
    return terminal_column;
}

void terminal_set_colors(enum vga_color font_color, enum vga_color background_color)
{
    terminal_color = make_color(font_color, background_color);
    // terminal_buffer = VGA_MEMORY;
    // size_t y;
    // for (y = 0; y < VGA_HEIGHT; y++)
    // {
    //     size_t x;
    //     for (x = 0; x < VGA_WIDTH; x++)
    //     {
    //         const size_t index = y * VGA_WIDTH + x;
    //         terminal_buffer[index] = make_vgaentry('\0', terminal_color);
    //     }
    // }
}