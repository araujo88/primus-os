#include "../include/tty.h"

int main(void)
{
	terminal_initialize(COLOR_GREEN, COLOR_BLACK);
	printf("Hello world\n");
	return 0;
}
