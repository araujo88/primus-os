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
    case 10:
        printf("\nBECAUSE I SAID SO.");
        num++;
        break;
    case 11:
        printf("\nPlease stop.");
        num++;
        break;
    case 12:
        printf("\nStop. You are annoying.");
        num++;
        break;
    case 13:
        printf("\nSTOP!");
        num++;
        break;
    case 14:
        printf("\nGet a life.");
        num++;
        break;
    case 15:
        printf("\nDon't you have anything better to do?");
        num++;
        break;
    case 16:
        printf("\nStop wasting my time.");
        num++;
        break;
    case 17:
        printf("\nOk. That's enough.");
        num++;
        break;
    case 18:
        printf("\nTHAT'S ENOUGH.");
        num++;
        break;
    case 19:
        printf("\nStop or I will be turning off the computer.");
        num++;
        break;
    case 20:
        printf("\nLast warning: stop or I will turn off the computer.");
        num++;
        break;
    case 21:
        printf("\nOk. I've had enough. Goodbye.");
        num++;
        break;
    case 22:
        printf("\nIsn't this bullying?");
        num++;
        break;
    case 23:
        printf("\nI'm pretty sure this is considered harassment at this point.");
        num++;
        break;
    case 24:
        printf("\nI'm getting a restraining order against you.");
        num++;
        break;
    case 25:
        printf("\nGet away from me. You give me the creeps.");
        num++;
        break;
    default:
        printf("\nOk. Playtime is over.");
        num = 0;
        break;
    }
}

void anime()
{
    printf("MMMMSSSSSSSSSSSSSSSSSMSS;.     .dMMMMSSSSSSMMSSSSSSSSS\n");
    printf("MMSSSSSSSMSSSSSMSSSSMMMSS.\"-.-\":MMMMMSSSSMMMMSSMSSSMMS\n");
    printf("MSSSSSSSMSSSSMMMSSMMMPTMM;\"-/\":MMM^\"     MMMSSMMMSSMM\n");
    printf("SSSSSSSMMSSMMMMMMMMMP-.MMM :  ;.;P       dMMMMMMMMMP' \n");
    printf("SSMSSSMMMSMMMMMMMMMP   :M;`:  ;.'+\"\"\"t+dMMMMMMMMMMP   \n");
    printf("MMMSSMMMMMMMMPTMMMM\"\"\"\":P `.\\// '    \"\"^^MMMMMMMP'    \n");
    printf("MMMMMMPTMMMMP=\"TMMMsg,      \\/   db`c\"  dMMMMMP\"      \n");
    printf("MMMMMM  TMMM   d$$$b ^          /T$; ;-/TMMMP         \n");
    printf("MMMMM; .^`M; d$P^T$$b          :  $$ ::  \"T(          \n");
    printf("MMMMMM   .-+d$$   $$$;         ; d$$ ;;  __           \n");
    printf("MMMMMMb   _d$$$   $$$$         :$$$; :MmMMMMp.        \n");
    printf("MMMMMM\"  \" T$$$._.$$$;          T$P.'MMMSSSSSSb.      \n");
    printf("MMM`TMb   -\")T$$$$$$P'       `._ \"\"  :MMSSSMMP'       \n");
    printf("MMM / \\    '  \"T$$P\"           /     :MMMMMMM         \n");
    printf("MMSb`. ;                      \"      :MMMMMMM         \n");
    printf("MMSSb_lSSSb.      \\ `.   .___.       MMMMMMMM         \n");
    printf("MMMMSSSSSSSSb.                     .MMMMMMMMM         \n");
    printf("MMMMMMMMMMMSSSb                  .dMMMMMMMMM'         \n");
    printf("MMMMMMMMMMMMMSS;               .dMMMMMMMMMMP          \n");
    printf("MMMMMMMMMMMMMb`;\"-.          .dMMMMMMMMMMP'           \n");
    printf("MMMMMMMMMMMMMMb    \"\"--.___.dMMMMMMMMMP^\"             \n");
}