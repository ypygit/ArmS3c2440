#include "hwuart.h"

static delay(int v)
{
    int i = 0;
    for (; i <= v; ++i) {;}
}

int main(void)
{
    put_string("srdram init & relocation run in memory!\r\n");

    while (1); 

    return 0;
}
