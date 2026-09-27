SDRAM_ELF = sdram_elf
SDRAM_BIN = sdram.bin

CROSS_COMPILE ?= arm-linux-
CC 			  := $(CROSS_COMPILE)gcc
LD 			  := $(CROSS_COMPILE)ld
OBJCOPY 	  := $(CROSS_COMPILE)objcopy
OBJDUMP 	  := $(CROSS_COMPILE)objdump

CSRCS 		  := $(wildcard *.c)
ASMS 		  := $(wildcard *.S)
OBJS 		  := $(CSRCS:.c=.o) $(ASMS:.S=.o)


all: $(SDRAM_ELF)
	$(OBJCOPY) -O binary -S $< $(SDRAM_BIN)
	$(OBJDUMP) -D $< > $(<:_elf=.dis)

$(SDRAM_ELF): $(OBJS)
	$(LD) -Tsdram.lds $^  -o $@ 

%.o: %.c
	$(CC) -c $< -o $@

%.o: %.S
	$(CC) -c $< -o $@

clean:
	rm -f *.o *.dis *.bin $(SDRAM_ELF) 

.PHONY: all clean
