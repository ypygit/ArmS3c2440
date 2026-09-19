#include "hwuart.h"
#include "s3c2440friend.h"

void init_uart(void)
{
    // [0] GPH2/3 -> TX/RX
    GPHCON &= ~((3 << 4) | (3 << 6));
    GPHCON |= ((2 << 4) | (2 << 6));

    // [1] TX/RX pull up
   	GPHUP &= ~((1<<2) | (1<<3));  
 
    // [2] work mode & clock source
    UCON_0 = 0x5;

    // [3] buad rate = 115200  
    UBRDIV0 = 26;

    // [4] data framat(8n1)
    ULCON0 = 0x03;

}

void put_c(int c)
{
    // have data, wait
    while(!(UTRSTAT0 & (1 << 2)));

    UTXH0 = (unsigned char)c;
}

int get_c(void)
{  
    // no data, wait
    while (!(UTRSTAT0 & (1 << 0)));

    return URXH0;
}

void put_string(const char *str)
{
    while (*str) {
        put_c(*str);
        str++;
    }
}
