# ======================================================================
#  This Makefile builds a test2 application *.ebf file for Aquila.
#
#  Chun-Jen Tsai, Dec/09/2019
# ======================================================================

CROSS = riscv32-unknown-elf
CCPATH = $(RISCV)/bin

CC = $(CCPATH)/$(CROSS)-gcc
AS = $(CCPATH)/$(CROSS)-as
LD = $(CCPATH)/$(CROSS)-ld
OC = $(CCPATH)/$(CROSS)-objcopy
OD = $(CCPATH)/$(CROSS)-objdump

LIBC = ../elibc

CCFLAGS = -Wall -I$(LIBC) -fomit-frame-pointer -fno-builtin -march=rv32im -mstrict-align -mabi=ilp32
ASFLAGS = -march=rv32im
LDFLAGS = -T$(PROJ).ld -Map=$(PROJ).map # -Ttext=0
LD_SOFT_FP = -L$(RISCV)/lib/gcc/riscv32-unknown-elf/8.2.0 -lgcc

OCFLAGS = -O binary
ODFLAGS = -d

PROJ = test2
OBJS = boot.o test2.o $(LIBC)/stdio.o $(LIBC)/stdlib.o $(LIBC)/heap_4.o $(LIBC)/string.o $(LIBC)/time.o $(LIBC)/uart.o

all:
	make $(PROJ).ebf

clean:
	rm -rf *.s $(LIBC)/*.o *.o *.bin *.objdump *.map *.ebf *.content

%.o: %.c $(PROJ).ld
	$(CC) $(CCFLAGS) -c $< -o $@

_$(PROJ).o: $(ASMS) $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(LD_SOFT_FP) -o $@

$(PROJ).bin: _$(PROJ).o
	$(OC) $(OCFLAGS) $< $@
	$(OD) $(ODFLAGS) $< > $(PROJ).objdump
	$(OD) -s $< > $(PROJ).content
	rm $<

$(PROJ).ebf: $(PROJ).bin
	./create_ebf.sh $<
