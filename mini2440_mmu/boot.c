#include "nand.h"

int is_nand_boot(void)
{
    int isNandBoot = 0;
    volatile unsigned int *begPtr = (volatile unsigned int *)0;
    unsigned int backup = *begPtr, testV = 0x12345678;

    *begPtr = testV;

    if (*begPtr == testV) {
        isNandBoot = 1;
        *begPtr = backup;
    }

    return isNandBoot;
}

void copy_code_to_sdram(void)
{
    extern char __text_beg, __bss_beg;

    volatile unsigned int *src = (volatile unsigned int*)0;
    volatile unsigned int *dest = (volatile unsigned int*)&__text_beg;
    volatile unsigned int *end = (volatile unsigned int*)&__bss_beg;

    unsigned int len = (unsigned int)((unsigned long)&__bss_beg
                            - (unsigned long)&__text_beg);

    if (is_nand_boot()) {
        s3c2440_nand_controller_init();
        nand_read(0u, (unsigned char*)dest, len);
    } else {
        // nor
        while (dest < end) {
            *dest++ = *src++;
        }
    }
}

void clear_bss(void)
{
    extern char __bss_beg, __end;

    volatile unsigned int *beg = (volatile unsigned int*)&__bss_beg;
    volatile unsigned int *end = (volatile unsigned int*)&__end;

    while (beg < end) {
        *beg++ = 0;
    } 
}
