UNDIRQ_ELF = undirq_elf
UNDIRQ_BIN = undirq.bin

CROSS_COMPILE ?= arm-linux-
CC 			  := $(CROSS_COMPILE)gcc
LD 			  := $(CROSS_COMPILE)ld
OBJCOPY 	  := $(CROSS_COMPILE)objcopy
OBJDUMP 	  := $(CROSS_COMPILE)objdump

CSRCS 		  := $(wildcard *.c)
ASMS 		  := $(wildcard *.S)
OBJS 		  := $(CSRCS:.c=.o) $(ASMS:.S=.o)


all: $(UNDIRQ_ELF)
	$(OBJCOPY) -O binary -S $< $(UNDIRQ_BIN)
	$(OBJDUMP) -D $< > $(<:_elf=.dis)

$(UNDIRQ_ELF): $(OBJS)
	$(LD) -Tundirq.lds $^  -o $@ 

%.o: %.c
	$(CC) -c $< -o $@

%.o: %.S
	$(CC) -c $< -o $@

clean:
	rm -f *.o *.dis *.bin $(UNDIRQ_ELF) 

.PHONY: all clean
