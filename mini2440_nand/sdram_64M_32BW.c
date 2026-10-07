#include "s3c2440friend.h"
#include "sdram_64M_32BW.h"

void mini2440_sdram_init(void)
{
    BWSCON = 0x22000000;

    BANKCON6 = 0x18001;
    BANKCON7 = 0x18001;
    
    SDRAMREFR = 0x8404f5;

    BANKSIZE = 0xb1;

    BKMODSET_6 = 0x20;
    BKMODSET_7 = 0x20;
}
