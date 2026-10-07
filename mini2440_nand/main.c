#include "hwuart.h"

#include "nand.h"

int main(void)
{
    unsigned char cmd = '\0';

    init_uart0();
    s3c2440_nand_controller_init();

    put_string("using nand flash(K9F2G08U0C).\r\n");

    while (1) {
        cmd = get_c();
        if (cmd != 'N') {
            continue;
        }

        nand_flash_read_id();
    }

    return 0;
}
