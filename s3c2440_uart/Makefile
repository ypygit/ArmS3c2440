###############################
# noOS makefile example
###############################

Target=uart_elf
BIN=uart_bin

CROSS_COMPILE ?= arm-linux-
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

SRCS := $(wildcard *.c) 
ASMS := $(wildcard *.S)

OBJS := $(SRCS:.c=.o) $(ASMS:.S=.o)

all: $(Target)
	$(OBJCOPY) -O binary -S $< $(BIN)
	$(OBJDUMP) -D $< > $(<:_elf=.dis)

$(Target): $(OBJS)
	$(LD) -Tlink.lds $^ -o $(Target)

%.o: %.S
	$(CC) -c $< -o $@

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(Target) $(BIN) *.o *.dis

.PHONY: clean all

