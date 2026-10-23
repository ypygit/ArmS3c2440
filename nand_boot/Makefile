NAND-BOOT_ELF = nand-boot_elf
NAND-BOOT_BIN = nand-boot.bin

CROSS_COMPILE ?= arm-linux-
CC 			  := $(CROSS_COMPILE)gcc
LD 			  := $(CROSS_COMPILE)ld
OBJCOPY 	  := $(CROSS_COMPILE)objcopy
OBJDUMP 	  := $(CROSS_COMPILE)objdump

CSRCS 		  := $(wildcard *.c)
ASMS 		  := $(wildcard *.S)
OBJS 		  := $(CSRCS:.c=.o) $(ASMS:.S=.o)

# LIBGCC := $(shell $(CC) -print-libgcc-file-name)

all: $(NAND-BOOT_ELF)
	$(OBJCOPY) -O binary -S $< $(NAND-BOOT_BIN)
	$(OBJDUMP) -D $< > $(<:_elf=.dis)

#$(LD) -Tnand_boot.lds $^ $(LIBGCC) -o $@ 
$(NAND-BOOT_ELF): $(OBJS)
	$(LD) -Tnand_boot.lds $^ -o $@ 

%.o: %.c
	$(CC) -c $< -o $@

%.o: %.S
	$(CC) -c $< -o $@

clean:
	rm -f *.o *.dis *.bin $(NAND-BOOT_ELF) 

.PHONY: all clean
