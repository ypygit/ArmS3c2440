#include "am29lv160db.h"
#include "hwuart.h"

#define BANK0_BASE_ADDR 0x0

static void nor_write_addr(volatile unsigned int base, unsigned int offset, unsigned int val)
{
    volatile unsigned short *addr = (volatile unsigned short*)((unsigned long)(base + (offset << 1)));

    *addr = val;
}

static void nor_cmd(unsigned int offset, unsigned int val)
{
    nor_write_addr(BANK0_BASE_ADDR, offset, val);
}

unsigned short nor_read_addr(unsigned int base, unsigned int offset)
{
    volatile unsigned short *addr = (volatile unsigned short*)((unsigned long)(base + (offset << 1)));

    return *addr;
}

unsigned int nor_data(unsigned int offset)
{
	return nor_read_addr(BANK0_BASE_ADDR, offset);
}

void qry_am29lv160db_info(void)
{
    int vender_id = 0, device_id = 0;
    char qry_str[4];
    unsigned int device_bytes;
    int region_count = 0;
    unsigned int blk_addr, blk_size;
    int loc = 0;
    
    // [0] auto select mode
    nor_cmd(0x555, 0xAA);
    nor_cmd(0x2AA, 0x55);
    nor_cmd(0x555, 0x90);

    vender_id = nor_data(0x0);
    device_id = nor_data(0x1);

    nor_cmd(0x0, 0xF0);

    // [1] enter CFI Query mode
    nor_cmd(0x55, 0x98);

    //[1.0] read query string
    qry_str[0] = nor_data(0x10);
    qry_str[1] = nor_data(0x11);
    qry_str[2] = nor_data(0x12);
    qry_str[3] = '\0';
    put_string(qry_str);
    put_string("\r\n");

    // [1.1] Device Size
    device_bytes = 1 << nor_data(0x27);

    put_string("friendlyArm mini2440 nor flash{device id: ");
    print_hex(device_id);
    put_string(" vender id: ");
    print_hex(vender_id);
    put_string(" device size: ");
    print_hex(device_bytes >> 20);
    put_string("MB}\r\n");

    // [1.2] region count
    region_count = nor_data(0x2c);
    put_string("nor flash region number = ");
    print_hex(region_count);
    put_string("\r\n");

    // [1.3] show Sector Start Address
    blk_addr = 0;
    int region_addr = 0x2D;
    unsigned int blk_number = 0;
    int i, j;

    // [1.3.1] logic block
    for (i = 0; i < region_count; ++i) {
        blk_number = nor_data(region_addr) + (nor_data(region_addr + 1) << 8) + 1;
        blk_size   = (nor_data(region_addr + 2) + (nor_data(region_addr + 3) << 8)) * 256;

        region_addr += 4;

        // [1.3.2] Erase Block(S) of the Region 
        for (j = 0; j < blk_number; ++j) {
            print_hex(blk_addr); 
            put_c(' ');
            blk_addr += blk_size;
            loc++;
            if (loc % 5 == 0) {
                put_string("\r\n");
            }
        }
    }

    nor_cmd(0x0, 0xF0);

    put_string("\r\n");
}
