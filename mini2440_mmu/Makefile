MMU_ELF = mmu_elf
MMU_BIN = mmu.bin

CROSS_COMPILE ?= arm-linux-
CC 			  := $(CROSS_COMPILE)gcc
LD 			  := $(CROSS_COMPILE)ld
OBJCOPY 	  := $(CROSS_COMPILE)objcopy
OBJDUMP 	  := $(CROSS_COMPILE)objdump

CSRCS 		  := $(wildcard *.c)
ASMS 		  := $(wildcard *.S)
OBJS 		  := $(ASMS:.S=.o) $(CSRCS:.c=.o) 

all: $(MMU_ELF)
	$(OBJCOPY) -O binary -S $< $(MMU_BIN)
	$(OBJDUMP) -D $< > $(<:_elf=.dis)

$(MMU_ELF): $(OBJS)
	$(LD) -Tmmu.lds $^ -o $@ 

%.o: %.c
	$(CC) -c $< -o $@

%.o: %.S
	$(CC) -c $< -o $@

clean:
	rm -f *.o *.dis *.bin $(MMU_ELF) 

.PHONY: all clean
