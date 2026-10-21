#include "nand.h"
#include "hwuart.h"
#include "s3c2440friend.h"

const unsigned int page_size = 2 * 1024U;

static inline void nand_chip_enable(void)
{
    NFCONT &= ~(1 << 1);
}

static inline void nand_chip_disable(void)
{
    NFCONT |= (1 << 1);
}

static void nand_cmd(unsigned char cmd)
{
    volatile int i = 0;

    NFCMMD = cmd;

    for (; i < 10; i++);
}

static void nand_addr(unsigned char addr)
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

void friendlyArm_mini2440_nand_read_data(unsigned int addr, const unsigned int len, unsigned char *buff)
{
	int i = 0;
	int row = addr / page_size;
	int column = addr & (page_size - 1);

	nand_chip_enable();

	while (i < len) {
        // send cmd
        nand_cmd(0x00);

		// send column 0 1
        nand_addr(column & 0xff);
        nand_addr((column >> 8) & 0xff);
        // send row 0 1 2
        nand_addr(row & 0xff);
        nand_addr((row >> 8) & 0xff);
        nand_addr((column >> 16) & 0xff);

        nand_cmd(0x30);
		
		// wait ready
        wait_ready();
		
		// read
		for (; (column < page_size) && (i < len); ++column) {
			buff[i++] = nand_data();
		}

		if (i == len) {
			break;
		}

		row++;
		column = 0;
	}

	nand_chip_disable();
}
