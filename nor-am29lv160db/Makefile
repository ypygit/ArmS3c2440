NOR_ELF = nor_elf
NOR_BIN = nor.bin

CROSS_COMPILE ?= arm-linux-
CC 			  := $(CROSS_COMPILE)gcc
LD 			  := $(CROSS_COMPILE)ld
OBJCOPY 	  := $(CROSS_COMPILE)objcopy
OBJDUMP 	  := $(CROSS_COMPILE)objdump

CSRCS 		  := $(wildcard *.c)
ASMS 		  := $(wildcard *.S)
OBJS 		  := $(CSRCS:.c=.o) $(ASMS:.S=.o)

all: $(NOR_ELF)
	$(OBJCOPY) -O binary -S $< $(NOR_BIN)
	$(OBJDUMP) -D $< > $(<:_elf=.dis)

#$(LD) -Tnand_boot.lds $^ $(LIBGCC) -o $@ 
$(NOR_ELF): $(OBJS)
	$(LD) -Tnor.lds $^ -o $@ 

%.o: %.c
	$(CC) -march=armv4 -c $< -o $@

%.o: %.S
	$(CC) -march=armv4 -c $< -o $@

clean:
	rm -f *.o *.dis *.bin $(NOR_ELF) 

.PHONY: all clean
