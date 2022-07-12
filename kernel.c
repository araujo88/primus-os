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

static char *const VGA_MEMORY = (char *)0xb8000; // physical memory of video buffer

static const int VGA_WIDTH = 80;  // num of chars
static const int VGA_HEIGHT = 25; // num of lines

void kernel_early(void)
{
    // do stuff
}

int main(void)
{
    const char *str = "Hello world!";
    unsigned int i = 0; // place holder for text string position
    unsigned int j = 0; // place holder for video buffer position

    while (str[i] != '\0')
    {
        VGA_MEMORY[j] = str[i];
        VGA_MEMORY[j + 1] = VGA_COLOR_LIGHT_GREY;
        i++;
        j += 2; // increment by two bytes
    }

    return 0;
}