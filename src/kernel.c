#include "../include/tty.h"
#include "../include/io.h"
#include "../include/kbd.h"
#include "../include/string.h"

int main(void)
{
	char buffer[1024];
	uint8_t byte;

	terminal_initialize(COLOR_LIGHT_GREY, COLOR_BLACK);
	printf("Welcome! I'm a super advanced operational system with lots of features.\n\n");

	strcpy(&buffer[strlen(buffer)], "");
	print_prompt();
	while (1)
	{
		while (byte = scan())
		{
			if (byte == 0x1c)
			{
				if (strlen(buffer) > 0 && strcmp(buffer, "exit") == 0)
				{
					printf("\nGoodbye!");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "hello") == 0)
				{
					printf("\nHi!");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "reboot") == 0)
				{
					reboot();
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "restart") == 0)
				{
					reboot();
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "shutdown") == 0)
				{
					outw(0xB004, 0x2000);
					outw(0x604, 0x2000);
					outw(0x4004, 0x3400);
				}
				else if (strlen(buffer) == 0)
				{
				}
				else
				{
					printf("\nUnrecognized command. Are you stupid?");
					printf("%s", buffer);
				}
				print_prompt();
				memset(&buffer[0], 0, sizeof(buffer));
				break;
			}
			else
			{
				char c = normalmap[byte];
				char *s;
				s = ctos(s, c);
				printf("%s", s);
				strcpy(&buffer[strlen(buffer)], s);
			}
			move_cursor(get_terminal_row(), get_terminal_col());
		}
	}
	return 0;
}