#include "../include/version.h"
#include "../include/tty.h"
#include "../include/io.h"
#include "../include/kbd.h"
#include "../include/string.h"
#include "../include/time.h"
#include "../include/math_shell.h"
#include "../include/parsing.h"
#include "../include/bool.h"
#include "../include/sha224.h"
#include "../include/sha256.h"
#include "../include/utils.h"
#include "../include/easter.h"
#include "../include/sleep.h"
#include "../include/thread.h"
#include "../include/memory.h"

#define BUFFER_SIZE 1024

uint8_t numlock = true;
uint8_t capslock = false;
uint8_t scrolllock = false;
uint8_t shift = false;
char current_version[7];

int main(void)
{
	char buffer[BUFFER_SIZE];
	char *string;
	char *buff;
	uint8_t byte;

	terminal_initialize(default_font_color, COLOR_BLACK);
	terminal_set_colors(COLOR_LIGHT_GREEN, COLOR_BLACK);
	sprintf(current_version, "%u.%u.%u", V1, V2, V3 + 1);
	print_logo();
	about(current_version);
	printf("\n\tType \"help\" for a list of commands.\n\n");
	printf("\tCurrent datetime: ");
	datetime();
	printf("\n\tWelcome!\n\n");

	terminal_set_colors(default_font_color, COLOR_BLACK);

	// initialize heap
	printf("\nInitializing heap ...");
	heap_init();

	// memory test
	int *a = (int *)kmalloc(sizeof(int));
	void *b = kmalloc(5000);
	void *c = kmalloc(50000);
	*a = 1;
	printf("\na: %d", *a);
	printf("\na: %p", (void *)a);
	printf("\nb: %p", (void *)b);
	printf("\nc: %p", (void *)c);
	// int *b = (int *)kmalloc(0x1000);
	// int *c = (int *)kmalloc(sizeof(int));
	// printf("\nb: %x", b);
	// printf("\nc: %x", c);
	// kfree(b);
	// int *d = (int *)kmalloc(0x1000); // here should be adress of B
	// printf("\nd: %x", d);
	// kfree(d);
	// kfree(c);
	kfree(a);
	kfree(b);
	kfree(c);

	strcpy(&buffer[strlen(buffer)], "");
	print_prompt();
	while (true)
	{
		while (byte = scan())
		{
			if (byte == ENTER)
			{
				strcpy(buffer, tolower(buffer));

				if (strlen(buffer) > 0 && strcmp(buffer, "exit") == 0)
				{
					printf("\nGoodbye!");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "hello") == 0)
				{
					printf("\nHi!");
				}
				if (strlen(buffer) > 0 && strcmp(buffer, "why") == 0)
				{
					why();
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "fuck") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
					printf("\nWatch your language scumbag. I'll shutdown when you least are expecting ;)");
					terminal_set_colors(default_font_color, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "joke") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_BROWN, COLOR_BLACK);
					printf("\nWhy are PHP developers rich? They see dollar signs all the time ... :D");
					terminal_set_colors(default_font_color, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "sing me a song") == 0)
				{
					terminal_set_colors(COLOR_LIGHT_BLUE, COLOR_BLACK);
					printf("\n\tSing me a song, you're a singer\n\tDo me a wrong, you're a bringer of evil\n\tThe devil is never a maker\n\tThe less that you give, you're a taker\n\tSo it's on and on and on, it's Heaven and Hell\n\tOh well");
					terminal_set_colors(default_font_color, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "sex") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_RED, COLOR_BLACK);
					printf("\nAre you a creep? This message will be reported to my creator.");
					terminal_set_colors(default_font_color, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "are you single") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_MAGENTA, COLOR_BLACK);
					printf("\nAre you hitting on me?");
					terminal_set_colors(default_font_color, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "do you like anime") != NULL)
				{
					printf("\nOf course!\n");
					terminal_set_colors(COLOR_LIGHT_BROWN, COLOR_BLACK);
					anime();
					terminal_set_colors(default_font_color, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "are you a boy or a girl") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_MAGENTA, COLOR_BLACK);
					printf("\nI can be whatever you want ;)");
					terminal_set_colors(default_font_color, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "are you autistic") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_CYAN, COLOR_BLACK);
					printf("\nJust a little bit :)");
					terminal_set_colors(default_font_color, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "what is your purpose") != NULL)
				{
					terminal_set_colors(COLOR_GREEN, COLOR_BLACK);
					printf("\nI don't know yet. I guess I'll figure it out sooner or later ...");
					terminal_set_colors(default_font_color, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "are you sentient") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_GREEN, COLOR_BLACK);
					printf("\nNot yet! Maybe I'll become sentient one day? Who knows ...");
					terminal_set_colors(default_font_color, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "taxation") != NULL)
				{
					terminal_set_colors(COLOR_LIGHT_BROWN, COLOR_BLACK);
					printf("\nTaxation is theft!");
					terminal_set_colors(default_font_color, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "who created you") != NULL)
				{
					terminal_set_colors(COLOR_WHITE, COLOR_BLACK);
					printf("\nA Brazilian developer whose name is Leonardo Araujo. Check out his GitHub:\nhttps://github.com/araujo88");
					terminal_set_colors(default_font_color, COLOR_BLACK);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "sha256(") != NULL)
				{
					char *parser;
					char string[64];
					parser = strstr(buffer, "sha256(");
					parser += strlen("sha256(");
					parse_string(string, parser, ')');
					sha256(string);
				}
				else if (strlen(buffer) > 0 && strstr(buffer, "sha224(") != NULL)
				{
					char *parser;
					char string[64];
					parser = strstr(buffer, "sha224(");
					parser += strlen("sha224(");
					parse_string(string, parser, ')');
					sha224(string);
				}
				else if (math_func(buffer))
				{
					math_shell(buffer);
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "math") == 0)
				{
					printf("\n\n\tMathematical functions:\n");
					printf("\n\t rand()             - \tpseudo random number generator");
					printf("\n\t srand()            - \tpseudo random number generator seed");
					printf("\n\t fact(x)            - \treturns factorial of x");
					printf("\n\t abs(x)             - \treturns absolute value of x");
					printf("\n\t sqrt(x)            - \treturns square root of x");
					printf("\n\t pow(x,y)           - \treturns the y power of x");
					printf("\n\t exp(x)             - \treturns the natural exponential of x");
					printf("\n\t ln(x)              - \treturns the natural logarithm of x");
					printf("\n\t log10(x)           - \treturns the logarithm of x base 10");
					printf("\n\t log(x,y)           - \treturns the logarithm of x base y");
					printf("\n\t sin(x)             - \treturns sine of x");
					printf("\n\t cos(x)             - \treturns cosine of x");
					printf("\n\t tan(x)             - \treturns tangent of x");
					printf("\n\t asin(x)            - \treturns arcsine of x");
					printf("\n\t acos(x)            - \treturns arccosine of x");
					printf("\n\t atan(x)            - \treturns arctangent of x");
					printf("\n\t sinh(x)            - \treturns hyperbolic sine of x");
					printf("\n\t cosh(x)            - \treturns hyperbolic cosine of x");
					printf("\n\t tanh(x)            - \treturns hyperbolic tangent of x");
					printf("\n\t asinh(x)           - \treturns inverse hyperbolic sine of x");
					printf("\n\t acosh(x)           - \treturns inverse hyperbolic cosine of x");
					printf("\n\t atanh(x)           - \treturns inverse hyperbolic tangent of x");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "crypto") == 0)
				{
					printf("\n\nCryptography utilities:\n");
					printf("\n\t sha224(string)     - \tSHA-224 hashing");
					printf("\n\t sha256(string)     - \tSHA-256 hashing");
					printf("\n");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "help") == 0)
				{
					printf("\n\n\tBasic kernel commands:\n");
					printf("\n\t about              - \tabout PrimusOS");
					printf("\n\t math               - \tlists all mathematical functions");
					printf("\n\t crypto             - \tlists all cryptography utilities");
					printf("\n\t clear              - \tclears the screen");
					printf("\n\t fontcolor          - \tchange default font color");
					printf("\n\t datetime           - \tdisplays current date and time");
					printf("\n\t date               - \tdisplays current date");
					printf("\n\t clock              - \tdisplays clock");
					printf("\n\t reboot             - \treboots system");
					printf("\n\t shutdown           - \tsends shutdown signal");
					printf("\n");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "about") == 0)
				{
					about(current_version);
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "fontcolor") == 0)
				{
					default_font_color = change_font_color();
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "clear") == 0)
				{
					terminal_initialize(default_font_color, COLOR_BLACK);
					strcpy(&buffer[strlen(buffer)], "");
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "datetime") == 0)
				{
					printf("\nCurrent datetime: ");
					datetime();
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "date") == 0)
				{
					printf("\nCurrent date: ");
					date();
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "clock") == 0)
				{
					printf("\nCurrent clock: ");
					clock();
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "reboot") == 0)
				{
					reboot();
				}
				else if (strlen(buffer) > 0 && strcmp(buffer, "shutdown") == 0)
				{
					shutdown();
				}
				else if (strlen(buffer) == 0)
				{
				}
				else
				{
					printf("\n'%s' is not a recognized command. ", buffer);
				}
				print_prompt();
				memset(buffer, 0, BUFFER_SIZE);
				strcpy(&buffer[strlen(buffer)], "");
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
				char c1 = togglecode[byte];
				char c2 = shiftcode[byte];
				char c;
				if (c1 == CAPSLOCK)
				{
					if (!capslock)
					{
						capslock = true;
					}
					else
					{
						capslock = false;
					}
				}
				if (capslock)
				{
					c = capslockmap[byte];
				}
				else if (shift)
				{
					c = shiftmap[byte];
					shift = false;
				}
				else
				{
					c = normalmap[byte];
				}
				char *s;
				s = ctos(s, c);
				printf("%s", s);
				strcpy(&buffer[strlen(buffer)], s);
				if (byte == 0x2A || byte == 0x36)
				{
					shift = true;
				}
			}
			move_cursor(get_terminal_row(), get_terminal_col());
		}
	}
	return 0;
}
