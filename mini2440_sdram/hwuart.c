#include "hwuart.h"
#include "s3c2440friend.h"

void init_uart0(void)
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

void print_hex(const unsigned int value)
{
    int i = 0;
    unsigned int v = value;
    unsigned char arr[8];

    for (i = 0; i < 8; ++i) {
        arr[i] = v & 0x0000000f;
        v >>= 4; 
    }

    put_string("0x");

    for (i = 7; i >= 0; --i) {
        if (arr[i] >= 0 && arr[i] <= 9) {
            put_c(arr[i] + '0');
        } else if (arr[i] >= 0xA && arr[i] <= 0xF) {
            put_c(arr[i] - 0xA + 'A');
        }
    }
}
