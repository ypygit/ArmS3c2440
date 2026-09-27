#include "hwuart.h"

// .data
char        g_c1 = 'A';
static int  g_i1 = 1;

// .rodata
const char  g_cc1 = 'B';

// .bss
int         g_bsszeroi1 = 0;
int         g_bssnvi1;

static delay(int v)
{
    int i = 0;
    for (; i <= v; ++i) {;}
}

int main(void)
{
    init_uart0();

    put_string("srdram init & relocation run in memory!\r\n");

    while (1) {
        print_hex(g_i1++);
        delay(1000000);
    }

    return 0;
}
