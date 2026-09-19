#include "hwuart.h"

int main(void)
{
    unsigned char c = '\0';

    init_uart();

    put_string("hello word from uart0!!!\r\n");

    while (1) {
        c = get_c();

        if (c == '\r') {
            put_c('\n');
        }

        if (c == '\n') {
            put_c('\r');
        }

        put_c(c);
    }

    return 0;
}
