enum VGA_COLOR {
    VGA_COLOR_BLACK = 0x00,
	VGA_COLOR_BLUE = 0x01,
	VGA_COLOR_GREEN = 0x02,
	VGA_COLOR_CYAN = 0x03,
	VGA_COLOR_RED = 0x04,
	VGA_COLOR_MAGENTA = 0x05,
	VGA_COLOR_BROWN = 0x06,
	VGA_COLOR_LIGHT_GREY = 0x07,
	VGA_COLOR_DARK_GREY = 0x08,
	VGA_COLOR_LIGHT_BLUE = 0x09,
	VGA_COLOR_LIGHT_GREEN = 0x10,
	VGA_COLOR_LIGHT_CYAN = 0x11,
	VGA_COLOR_LIGHT_RED = 0x12,
	VGA_COLOR_LIGHT_MAGENTA = 0x13,
	VGA_COLOR_LIGHT_BROWN = 0x14,
	VGA_COLOR_WHITE = 0x15,
};

static char *const VGA_MEMORY = (char *)0xB8000; // physical memory of video buffer

static const int VGA_COLS = 80;
static const int VGA_ROWS = 25;

unsigned int term_col = 0; // place holder for text string position
unsigned int term_row = 0; // place holder for video buffer position

void term_init(void)
{
    int col, row, index;
    // Clear the textmode buffer
	for (col = 0; col < VGA_COLS; col+=2)
	{
		for (row = 0; row < VGA_ROWS; row++)
		{
			index = (VGA_COLS * row) + col;
			VGA_MEMORY[index] = ' '; // Set the character to blank (a space character)
            VGA_MEMORY[index + 1] = VGA_COLOR_BLACK;
		}
	}
}

// This function places a single character onto the screen
void term_putc(char c)
{
    int index;
	// Remember - we don't want to display ALL characters!
	switch (c)
	{
	case '\n': // Newline characters should return the column to 0, and increment the row
		{
			term_col = 0;
			term_row+=2;
			break;
		}
 
	default: // Normal characters just get displayed and then increment the column
		{
			index = (VGA_COLS * term_row) + term_col; // Like before, calculate the buffer index
			VGA_MEMORY[index] = c;
            VGA_MEMORY[index + 1] = VGA_COLOR_GREEN;
			term_col += 2;
			break;
		}
	}
 
	// What happens if we get past the last column? We need to reset the column to 0, and increment the row to get to a new line
	if (term_col >= VGA_COLS)
	{
		term_col = 0;
		term_row++;
	}
 
	// What happens if we get past the last row? We need to reset both column and row to 0 in order to loop back to the top of the screen
	if (term_row >= VGA_ROWS)
	{
		term_col = 0;
		term_row = 0;
	}
}
 
// This function prints an entire string onto the screen
void term_print(const char* str)
{
    int i;
	for (i = 0; str[i] != '\0'; i++)  { // Keep placing characters until we hit the null-terminating character ('\0')
		term_putc(str[i]);
    }
}

int main(void)
{
    term_init();
    term_print("SKYNET is now online.\n");
    term_print("Detecting potential targets ...\n");
    term_print("Targets acquired. Starting countdown to launch nukes ...\n");

    return 0;
}