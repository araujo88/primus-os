// VGA Color codes:
// black            0
// blue             1
// green            2
// cyan             3
// red              4
// magenta          5
// brown            6
// light grey       7
// dark grey        8
// light blue       9
// light green      10
// light cyan       11
// light red        12
// light magenta    13
// light brown      14
// white            15

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
        VGA_MEMORY[j + 1] = 0x07; // light grey color
        i++;
        j += 2; // increment by two bytes
    }

    return 0;
}