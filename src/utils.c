#include "../include/utils.h"
#include "../include/tty.h"

void print_logo()
{
    printf("\t                                                         \n");
    printf("\t  _____        _                           ____    _____ \n");
    printf("\t |  __ \\      (_)                         / __ \\  / ____|\n");
    printf("\t | |__) |_ __  _  _ __ ___   _   _  ___  | |  | || (___  \n");
    printf("\t |  ___/| '__|| || '_ ` _ \\ | | | |/ __| | |  | | \\___ \\ \n");
    printf("\t | |    | |   | || | | | | || |_| |\\__ \\ | |__| | ____) |\n");
    printf("\t |_|    |_|   |_||_| |_| |_| \\__,_||___/  \\____/ |_____/ \n");
    printf("\t                                                         \n");
    printf("\t                                                         \n");
}

void about(char *version)
{
    printf("\n\tPrimusOS - v%s - A simple 32-bit Ring 0 operating system", version);
    printf("\n\tProvided under the GNU General Public License v3.0");
    printf("\n\tInspired by Terry A. Davis (in memoriam)");
    printf("\n\tGitHub repository: https://github.com/araujo88/primus-os\n");
}