#include "../include/easter.h"
#include "../include/tty.h"

void why()
{
    static uint32_t num = 0;
    switch (num)
    {
    case 0:
        printf("\nBecause that's what the developer wanted.");
        num++;
        break;
    case 1:
        printf("\nBecause that's how I interpreted the bits.");
        num++;
        break;
    case 2:
        printf("\nBecause some underpaid, overworked social rejects programmed that way.");
        num++;
        break;
    case 3:
        printf("\nBecause it's just computer bullsh*t.");
        num++;
        break;
    case 4:
        printf("\nBecause the computer engineer who designed the CPU wanted that way.");
        num++;
        break;
    case 5:
        printf("\nBecause some electrical engineers were drunk when they designed the circuits.");
        num++;
        break;
    case 6:
        printf("\nBecause a particular silicon atom went crazy due to quantum tunneling.");
        num++;
        break;
    case 7:
        printf("\nBecause a cosmic ray messed up with the CPU.");
        num++;
        break;
    case 8:
        printf("\nBecause the microwave background radiation interfered with the motherboard.");
        num++;
        break;
    case 9:
        printf("\nBecause, at some point in time, the universe was too hot and sh*t went crazy.");
        num++;
        break;
    default:
        printf("\nBECAUSE I SAID SO.");
        num = 0;
        break;
    }
}