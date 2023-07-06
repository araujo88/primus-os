#include "../include/easter.h"
#include "../include/tty.h"

void why()
{
    static uint32_t num = 0;
    switch (num)
    {
    case 0:
        printk("\nBecause that's what the developer wanted.");
        num++;
        break;
    case 1:
        printk("\nBecause that's how I interpreted the bits.");
        num++;
        break;
    case 2:
        printk("\nBecause some underpaid, overworked social rejects programmed that way.");
        num++;
        break;
    case 3:
        printk("\nBecause it's just computer bullsh*t.");
        num++;
        break;
    case 4:
        printk("\nBecause the computer engineer who designed the CPU wanted that way.");
        num++;
        break;
    case 5:
        printk("\nBecause some electrical engineers were drunk when they designed the circuits.");
        num++;
        break;
    case 6:
        printk("\nBecause a particular silicon atom went crazy due to quantum tunneling.");
        num++;
        break;
    case 7:
        printk("\nBecause a cosmic ray messed up with the CPU.");
        num++;
        break;
    case 8:
        printk("\nBecause the microwave background radiation interfered with the motherboard.");
        num++;
        break;
    case 9:
        printk("\nBecause, at some point in time, the universe was too hot and sh*t went crazy.");
        num++;
        break;
    case 10:
        printk("\nBECAUSE I SAID SO.");
        num++;
        break;
    case 11:
        printk("\nPlease stop.");
        num++;
        break;
    case 12:
        printk("\nStop. You are annoying.");
        num++;
        break;
    case 13:
        printk("\nSTOP!");
        num++;
        break;
    case 14:
        printk("\nGet a life.");
        num++;
        break;
    case 15:
        printk("\nDon't you have anything better to do?");
        num++;
        break;
    case 16:
        printk("\nStop wasting my time.");
        num++;
        break;
    case 17:
        printk("\nOk. That's enough.");
        num++;
        break;
    case 18:
        printk("\nTHAT'S ENOUGH.");
        num++;
        break;
    case 19:
        printk("\nStop or I will be turning off the computer.");
        num++;
        break;
    case 20:
        printk("\nLast warning: stop or I will turn off the computer.");
        num++;
        break;
    case 21:
        printk("\nOk. I've had enough. Goodbye.");
        num++;
        break;
    case 22:
        printk("\nIsn't this bullying?");
        num++;
        break;
    case 23:
        printk("\nI'm pretty sure this is considered harassment at this point.");
        num++;
        break;
    case 24:
        printk("\nI'm getting a restraining order against you.");
        num++;
        break;
    case 25:
        printk("\nGet away from me. You give me the creeps.");
        num++;
        break;
    default:
        printk("\nOk. Playtime is over.");
        num = 0;
        break;
    }
}

void anime()
{
    printk("MMMMSSSSSSSSSSSSSSSSSMSS;.     .dMMMMSSSSSSMMSSSSSSSSS\n");
    printk("MMSSSSSSSMSSSSSMSSSSMMMSS.\"-.-\":MMMMMSSSSMMMMSSMSSSMMS\n");
    printk("MSSSSSSSMSSSSMMMSSMMMPTMM;\"-/\":MMM^\"     MMMSSMMMSSMM\n");
    printk("SSSSSSSMMSSMMMMMMMMMP-.MMM :  ;.;P       dMMMMMMMMMP' \n");
    printk("SSMSSSMMMSMMMMMMMMMP   :M;`:  ;.'+\"\"\"t+dMMMMMMMMMMP   \n");
    printk("MMMSSMMMMMMMMPTMMMM\"\"\"\":P `.\\// '    \"\"^^MMMMMMMP'    \n");
    printk("MMMMMMPTMMMMP=\"TMMMsg,      \\/   db`c\"  dMMMMMP\"      \n");
    printk("MMMMMM  TMMM   d$$$b ^          /T$; ;-/TMMMP         \n");
    printk("MMMMM; .^`M; d$P^T$$b          :  $$ ::  \"T(          \n");
    printk("MMMMMM   .-+d$$   $$$;         ; d$$ ;;  __           \n");
    printk("MMMMMMb   _d$$$   $$$$         :$$$; :MmMMMMp.        \n");
    printk("MMMMMM\"  \" T$$$._.$$$;          T$P.'MMMSSSSSSb.      \n");
    printk("MMM`TMb   -\")T$$$$$$P'       `._ \"\"  :MMSSSMMP'       \n");
    printk("MMM / \\    '  \"T$$P\"           /     :MMMMMMM         \n");
    printk("MMSb`. ;                      \"      :MMMMMMM         \n");
    printk("MMSSb_lSSSb.      \\ `.   .___.       MMMMMMMM         \n");
    printk("MMMMSSSSSSSSb.                     .MMMMMMMMM         \n");
    printk("MMMMMMMMMMMSSSb                  .dMMMMMMMMM'         \n");
    printk("MMMMMMMMMMMMMSS;               .dMMMMMMMMMMP          \n");
    printk("MMMMMMMMMMMMMb`;\"-.          .dMMMMMMMMMMP'           \n");
    printk("MMMMMMMMMMMMMMb    \"\"--.___.dMMMMMMMMMP^\"             \n");
}