
enum {
    ADDR_MEM = 0,
    ADDR_IO = 1
};

/*
     Section Descptor:
    
     31                          20 19      12  11   10  9 8        5  4  3  2  1  0
    +------------------------------+-----------+-------+--+----------+--+--+--+-----+
    |     Section base address     |           |  AP   |  |  Domain  | 1| C| B| 1  0|
    +------------------------------+-----------+-------+--+----------+--+--+--+-----+
*/

// AP = 0b11, don`t care S & R, usr & svc mode can read & write memory
#define MMU_SECDESC_AP      (0x3 << 10)  

// Domain[0]
#define MMU_SECDESC_DOMAIN  (0 << 5)    

// no cache & no write buffer
#define MMU_SECDESC_NCNB    (0 << 2)   

// cache & write buffer
#define MMU_SECDESC_WB      (3 << 2)     

#define MMU_SECDESC_TYPE    ((1 << 4) | (1 << 1))

#define MMU_SECDESC_FOR_IO   (MMU_SECDESC_AP | MMU_SECDESC_DOMAIN | MMU_SECDESC_NCNB | MMU_SECDESC_TYPE)
#define MMU_SECDESC_FOR_MEM  (MMU_SECDESC_AP | MMU_SECDESC_DOMAIN | MMU_SECDESC_WB   | MMU_SECDESC_TYPE)

static inline void make_mmu_descptor(volatile unsigned int *ttb, 
                    unsigned int vir_addr, unsigned int phy_addr, int bc)
{
    int idx = 0;

    idx = vir_addr / 0x100000;

    ttb[idx] = (phy_addr & 0xfff00000) | 
                (bc == ADDR_IO ? MMU_SECDESC_FOR_IO : MMU_SECDESC_FOR_MEM);
}

void make_mmu_descriptors_table(void)
{
    unsigned int va, pa = va = 0;
    volatile unsigned int *ttb = (volatile unsigned int*)0x32000000;
   
    // [0]
    make_mmu_descptor(ttb, 0x0, 0x0, ADDR_MEM);

    // [1] nor boot, inter sram map to 0x40000000
    make_mmu_descptor(ttb, 0x40000000, 0x40000000, ADDR_MEM);

    // [2] 64M sdram
	va = 0x30000000;
	pa = 0x30000000;
	for (; va < 0x34000000;) {
		make_mmu_descptor(ttb, va, pa, ADDR_MEM);
		va += 0x100000;
		pa += 0x100000;
    }

    // [3] register
    va = 0x48000000;
    pa = 0x48000000;
    for (; va < 0x5B100000; ) {
       make_mmu_descptor(ttb, va, pa, ADDR_IO);
        va += 0x100000;
        pa += 0x100000;
    }

    // [4]
    make_mmu_descptor(ttb, 0xB0000000, 0x30000000, ADDR_MEM);
}
