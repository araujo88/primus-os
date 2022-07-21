#include "../include/tty.h"
#include "../include/string.h"
#include "../include/io.h"
#include "../include/bool.h"
#include "../include/kbd.h"

size_t terminal_row;
size_t terminal_column;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xb8000;
uint8_t terminal_color;
uint16_t *terminal_buffer;

#define BUFFER_SIZE 1024

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
        else if (*format == 'd')
        {
            format++;
            const char *s;
            sprintf(s, "%d", va_arg(parameters, const char *));
            print(s, strlen(s));
        }
        else if (*format == 'f')
        {
            format++;
            const char *s;
            sprintf(s, "%f", va_arg(parameters, const char *));
            print(s, strlen(s));
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

enum vga_color change_font_color()
{
    enum vga_color font_color;
    char buffer[BUFFER_SIZE];
    uint8_t byte;
    uint32_t color;

    memset(buffer, 0, BUFFER_SIZE);
    strcpy(&buffer[strlen(buffer)], "");

    printf("\nPlease select a font color. Valid options are:\n");
    terminal_set_colors(COLOR_BLUE, COLOR_BLACK);
    printf("\nCOLOR_BLUE = 1");
    terminal_set_colors(COLOR_GREEN, COLOR_BLACK);
    printf("\nCOLOR_GREEN = 2");
    terminal_set_colors(COLOR_CYAN, COLOR_BLACK);
    printf("\nCOLOR_CYAN = 3");
    terminal_set_colors(COLOR_RED, COLOR_BLACK);
    printf("\nCOLOR_RED = 4");
    terminal_set_colors(COLOR_MAGENTA, COLOR_BLACK);
    printf("\nCOLOR_MAGENTA = 5");
    terminal_set_colors(COLOR_BROWN, COLOR_BLACK);
    printf("\nCOLOR_BROWN = 6");
    terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
    printf("\nCOLOR_LIGHT_GREY = 7");
    terminal_set_colors(COLOR_DARK_GREY, COLOR_BLACK);
    printf("\nCOLOR_DARK_GREY = 8");
    terminal_set_colors(COLOR_LIGHT_BLUE, COLOR_BLACK);
    printf("\nCOLOR_LIGHT_BLUE = 9");
    terminal_set_colors(COLOR_LIGHT_GREEN, COLOR_BLACK);
    printf("\nCOLOR_LIGHT_GREEN = 10");
    terminal_set_colors(COLOR_LIGHT_CYAN, COLOR_BLACK);
    printf("\nCOLOR_LIGHT_CYAN = 11");
    terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
    printf("\nCOLOR_LIGHT_RED = 12");
    terminal_set_colors(COLOR_LIGHT_MAGENTA, COLOR_BLACK);
    printf("\nCOLOR_LIGHT_MAGENTA = 13");
    terminal_set_colors(COLOR_LIGHT_BROWN, COLOR_BLACK);
    printf("\nCOLOR_LIGHT_BROWN = 14");
    terminal_set_colors(COLOR_WHITE, COLOR_BLACK);
    printf("\nCOLOR_WHITE = 15\n");
    terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
    print_prompt();

    while (true)
    {
        while (byte = scan())
        {
            if (byte == ENTER)
            {
                switch (color)
                {
                case 1:
                    terminal_set_colors(COLOR_BLUE, COLOR_BLACK);
                    font_color = COLOR_BLUE;
                    return font_color;
                    break;
                case 2:
                    terminal_set_colors(COLOR_GREEN, COLOR_BLACK);
                    font_color = COLOR_GREEN;
                    return font_color;
                    break;
                case 3:
                    terminal_set_colors(COLOR_CYAN, COLOR_BLACK);
                    font_color = COLOR_CYAN;
                    return font_color;
                    break;
                case 4:
                    terminal_set_colors(COLOR_RED, COLOR_BLACK);
                    font_color = COLOR_RED;
                    return font_color;
                    break;
                case 5:
                    terminal_set_colors(COLOR_MAGENTA, COLOR_BLACK);
                    font_color = COLOR_MAGENTA;
                    return font_color;
                    break;
                case 6:
                    terminal_set_colors(COLOR_BROWN, COLOR_BLACK);
                    font_color = COLOR_BROWN;
                    return font_color;
                    break;
                case 7:
                    terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
                    font_color = COLOR_LIGHT_GREY;
                    return font_color;
                    break;
                case 8:
                    terminal_set_colors(COLOR_DARK_GREY, COLOR_BLACK);
                    font_color = COLOR_DARK_GREY;
                    return font_color;
                    break;
                case 9:
                    terminal_set_colors(COLOR_LIGHT_BLUE, COLOR_BLACK);
                    font_color = COLOR_LIGHT_BLUE;
                    return font_color;
                    break;
                case 10:
                    terminal_set_colors(COLOR_LIGHT_GREEN, COLOR_BLACK);
                    font_color = COLOR_LIGHT_GREEN;
                    return font_color;
                    break;
                case 11:
                    terminal_set_colors(COLOR_LIGHT_CYAN, COLOR_BLACK);
                    font_color = COLOR_LIGHT_CYAN;
                    return font_color;
                    break;
                case 12:
                    terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
                    font_color = COLOR_LIGHT_RED;
                    return font_color;
                    break;
                case 13:
                    terminal_set_colors(COLOR_LIGHT_MAGENTA, COLOR_BLACK);
                    font_color = COLOR_LIGHT_MAGENTA;
                    return font_color;
                    break;
                case 14:
                    terminal_set_colors(COLOR_LIGHT_BROWN, COLOR_BLACK);
                    font_color = COLOR_LIGHT_BROWN;
                    return font_color;
                    break;
                case 15:
                    terminal_set_colors(COLOR_WHITE, COLOR_BLACK);
                    font_color = COLOR_WHITE;
                    return font_color;
                    break;
                default:
                    printf("\nPlease select a font color. Valid options are:\n");
                    terminal_set_colors(COLOR_BLUE, COLOR_BLACK);
                    printf("\nCOLOR_BLUE = 1");
                    terminal_set_colors(COLOR_GREEN, COLOR_BLACK);
                    printf("\nCOLOR_GREEN = 2");
                    terminal_set_colors(COLOR_CYAN, COLOR_BLACK);
                    printf("\nCOLOR_CYAN = 3");
                    terminal_set_colors(COLOR_RED, COLOR_BLACK);
                    printf("\nCOLOR_RED = 4");
                    terminal_set_colors(COLOR_MAGENTA, COLOR_BLACK);
                    printf("\nCOLOR_MAGENTA = 5");
                    terminal_set_colors(COLOR_BROWN, COLOR_BLACK);
                    printf("\nCOLOR_BROWN = 6");
                    terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
                    printf("\nCOLOR_LIGHT_GREY = 7");
                    terminal_set_colors(COLOR_DARK_GREY, COLOR_BLACK);
                    printf("\nCOLOR_DARK_GREY = 8");
                    terminal_set_colors(COLOR_LIGHT_BLUE, COLOR_BLACK);
                    printf("\nCOLOR_LIGHT_BLUE = 9");
                    terminal_set_colors(COLOR_LIGHT_GREEN, COLOR_BLACK);
                    printf("\nCOLOR_LIGHT_GREEN = 10");
                    terminal_set_colors(COLOR_LIGHT_CYAN, COLOR_BLACK);
                    printf("\nCOLOR_LIGHT_CYAN = 11");
                    terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
                    printf("\nCOLOR_LIGHT_RED = 12");
                    terminal_set_colors(COLOR_LIGHT_MAGENTA, COLOR_BLACK);
                    printf("\nCOLOR_LIGHT_MAGENTA = 13");
                    terminal_set_colors(COLOR_LIGHT_BROWN, COLOR_BLACK);
                    printf("\nCOLOR_LIGHT_BROWN = 14");
                    terminal_set_colors(COLOR_WHITE, COLOR_BLACK);
                    printf("\nCOLOR_WHITE = 15\n");
                    terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
                    memset(buffer, 0, BUFFER_SIZE);
                    print_prompt();
                }
            }
            else
            {
                char *s;
                char c = normalmap[byte];
                s = ctos(s, c);
                printf("%s", s);
                strcpy(&buffer[strlen(buffer)], s);
                color = atoi(buffer);
            }
            move_cursor(get_terminal_row(), get_terminal_col());
        }
    }
}