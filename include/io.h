#ifndef _IO_H
#define _IO_H 1

#include "stdint.h"
#include "tty.h"

/* The I/O ports */
#define FB_COMMAND_PORT 0x3d4
#define FB_DATA_PORT 0x3d5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 0x0e
#define FB_LOW_BYTE_COMMAND 0x0f

uint8_t input_bytes(uint16_t port);
void output_bytes(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t data);
uint8_t scan(void);
void move_cursor(int row, int col);
void move_cursor2(char c, enum vga_color char_color);
void print_prompt(void);

#endif