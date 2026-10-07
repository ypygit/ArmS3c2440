#include "nand.h"
#include "hwuart.h"
#include "s3c2440friend.h"

static inline void nand_chip_enable(void)
{
    NFCONT &= ~(1 << 1);
}

static inline void nand_chip_disable(void)
{
    NFCONT |= (1 << 1);
}

static inline void nand_cmd(unsigned char cmd)
{
    volatile int i = 0;

    NFCMMD = cmd;

    for (; i < 10; i++);
}

static inline void nand_addr(unsigned char addr)
{
    volatile int i = 0;

    NFADDR = addr;

    for (; i < 10; i++);
}

static inline unsigned char nand_data(void)
{
    return NFDATA;
}

void s3c2440_nand_controller_init(void)
{
    // [0] config nand flash timing
    NFCONF = (0 << 12) | (1 << 8) | (0 << 4);

    // [1] enable nand flash controller
    NFCONT = (1 << 4) |  (1 << 1) | (1 << 0);
}

void nand_flash_read_id(void)
{
    int i = 0;
    unsigned char bytes[5] = {};

    nand_chip_enable();

    nand_cmd(0x90);
    nand_addr(0x00);

    for (i = 0; i < 5; ++i) {
        bytes[i] = nand_data();
    }

    nand_chip_disable();

    for (i = 0; i < 5; ++i) {
        print_hex(bytes[i]);
        put_string("\r\n");
    }
}
