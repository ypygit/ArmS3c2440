NAND_ELF = nand_elf
NAND_BIN = nand.bin

CROSS_COMPILE ?= arm-linux-
CC 			  := $(CROSS_COMPILE)gcc
LD 			  := $(CROSS_COMPILE)ld
OBJCOPY 	  := $(CROSS_COMPILE)objcopy
OBJDUMP 	  := $(CROSS_COMPILE)objdump

CSRCS 		  := $(wildcard *.c)
ASMS 		  := $(wildcard *.S)
OBJS 		  := $(CSRCS:.c=.o) $(ASMS:.S=.o)


all: $(NAND_ELF)
	$(OBJCOPY) -O binary -S $< $(NAND_BIN)
	$(OBJDUMP) -D $< > $(<:_elf=.dis)

$(NAND_ELF): $(OBJS)
	$(LD) -Tnand.lds $^ -o $@ 

%.o: %.c
	$(CC) -c $< -o $@

%.o: %.S
	$(CC) -c $< -o $@

clean:
	rm -f *.o *.dis *.bin $(NAND_ELF) 

.PHONY: all clean
