#ifndef _TTY_H
#define _TTY_H 1

#include "stdint.h"
#include "stddef.h"
#include "stdarg.h"

enum vga_color
{
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static enum vga_color default_font_color = COLOR_LIGHT_GREY;

void terminal_initialize(enum vga_color font_color, enum vga_color background_color);
void terminal_set_colors(enum vga_color font_color, enum vga_color background_color);
int printf(const char *format, ...);
int get_terminal_row(void);
int get_terminal_col(void);
void term_putc(char c, enum vga_color char_color);
enum vga_color change_font_color();
void change_background_color();

#endif