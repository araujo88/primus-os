#include "../include/tty.h"
#include "../include/io.h"
#include "../include/kbd.h"
#include "../include/string.h"
#include "../include/time.h"
#include "../include/date.h"
#include "../include/datetime.h"

#define BUFFER_SIZE 1024

int main(void)
{
	char buffer[BUFFER_SIZE];
	int command_size = 0;
	uint8_t byte;

	terminal_initialize(COLOR_LIGHT_GREY, COLOR_BLACK);
	printf("Welcome! I'm a super advanced operational system with lots of features.\n\n");
	printf("Date: %s\n", date());
	printf("Time: %s\n", time());
	datetime();

	strcpy(&buffer[strlen(buffer)], "");
	print_prompt();
	while (1)
	{
		while (byte = scan())
		{
			if (byte == ENTER)
			{
				if (strlen(buffer) > 0 && strcmp(buffer, "exit") == 0)
				{
					printf("\nGoodbye!");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "hello") == 0)
				{
					printf("\nHi!");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "fuck you") == 0)
				{
					terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
					printf("\nWatch your language scumbag. I'll shutdown when you least are expecting ;)");
					terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "sing me a song") == 0)
				{
					terminal_set_colors(COLOR_LIGHT_BLUE, COLOR_BLACK);
					printf("\n\tSing me a song, you're a singer\n\tDo me a wrong, you're a bringer of evil\n\tThe devil is never a maker\n\tThe less that you give, you're a taker\n\tSo it's on and on and on, it's Heaven and Hell\n\tOh well");
					terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "sex") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
					printf("\nAre you a creep? This message will be reported to my creator.");
					terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "are you single") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_MAGENTA, COLOR_BLACK);
					printf("\nAre you hitting on me?");
					terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "do you like anime") != NULL)
				{
					printf("\nOf course! ");
					terminal_set_colors(COLOR_LIGHT_BROWN, COLOR_BLACK);
					printf("Yare Yare daze ...");
					terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "are you a boy or a girl") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_MAGENTA, COLOR_BLACK);
					printf("\nI can be whatever you want ;)");
					terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "are you autistic") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_CYAN, COLOR_BLACK);
					printf("\nJust a little bit :)");
					terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "what is your purpose") != NULL)
				{
					terminal_set_colors(COLOR_GREEN, COLOR_BLACK);
					printf("\nI don't know yet. I guess I'll figure it out sooner or later ...");
					terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "are you sentient") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_GREEN, COLOR_BLACK);
					printf("\nNot yet! Maybe I'll become sentient one day? Who knows ...");
					terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "taxation is") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_BROWN, COLOR_BLACK);
					printf("\nTaxation is theft!");
					terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "who created you") != NULL)
				{
					terminal_set_colors(COLOR_WHITE, COLOR_BLACK);
					printf("\nA Brazilian developer whose name is Leonardo Araujo. Check out his GitHub:\nhttps://github.com/araujo88");
					terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "clear") == 0)
				{
					terminal_initialize(COLOR_LIGHT_GREY, COLOR_BLACK);
					strcpy(&buffer[strlen(buffer)], "");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "time") == 0)
				{
					printf("\nTime: %s", time());
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "date") == 0)
				{
					printf("\nDate: %s", date());
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "datetime") == 0)
				{
					printf("\nDate: %s", date());
					printf("\nTime: %s", time());
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
					printf("\n'%s' is an unrecognized command. ", buffer);
					terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
					printf("Are you stupid?", buffer);
					terminal_set_colors(COLOR_LIGHT_GREY, COLOR_BLACK);
				}
				print_prompt();
				memset(buffer, 0, BUFFER_SIZE);
				break;
			}
			else if ((byte == BACKSPACE) && (strlen(buffer) == 0))
			{
			}
			else if (byte == BACKSPACE)
			{
				char c = normalmap[byte];
				char *s;
				s = ctos(s, c);
				printf("%s", s);
				buffer[strlen(buffer) - 1] = '\0';
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
		command_size = 0;
	}
	return 0;
}