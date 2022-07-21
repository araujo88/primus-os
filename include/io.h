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

/* keyboard interface IO port: data and control
   READ:   status port
   WRITE:  control register */
#define KBRD_INTRFC 0x64

/* keyboard interface bits */
#define KBRD_BIT_KDATA 0 /* keyboard data is in buffer (output buffer is empty) (bit 0) */
#define KBRD_BIT_UDATA 1 /* user data is in buffer (command buffer is empty) (bit 1) */

#define KBRD_IO 0x60    /* keyboard IO port */
#define KBRD_RESET 0xFE /* reset CPU command */

#define bit(n) (1 << (n)) /* Set bit n to 1 */

/* Check if bit n in flags is set */
#define check_flag(flags, n) ((flags)&bit(n))

void reboot();
void shutdown();
uint8_t input_bytes(uint16_t port);
void output_bytes(uint16_t port, uint8_t val);
uint8_t inw(uint16_t port);
void outw(uint16_t port, uint16_t data);
uint8_t scan(void);
void move_cursor(int row, int col);
void move_cursor2(char c, enum vga_color char_color);
void print_prompt(void);

#endif