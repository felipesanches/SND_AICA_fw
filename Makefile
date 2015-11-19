CROSS_COMPILE = arm-none-eabi-

DC_ARM7AS	= $(CROSS_COMPILE)as
DC_ARM7LD	= $(CROSS_COMPILE)ld
DC_ARM7CC	= $(CROSS_COMPILE)gcc
DC_ARM7CPP	= $(CC) -E
DC_ARM7AR	= $(CROSS_COMPILE)ar
DC_ARM7NM	= $(CROSS_COMPILE)nm
DC_ARM7STRIP	= $(CROSS_COMPILE)strip
DC_ARM7OBJCOPY	= $(CROSS_COMPILE)objcopy
DC_ARM7OBJDUMP	= $(CROSS_COMPILE)objdump

all: stream.drv

stream.drv: prog.elf
	$(DC_ARM7OBJCOPY) -O binary prog.elf stream.drv

prog.elf: crt0.o main.o aica.o
	$(DC_ARM7CC) -Wl,-Ttext,0x00000000 -nostartfiles -nostdlib -e reset -o prog.elf crt0.o main.o aica.o -lgcc

%.o: %.c
	$(DC_ARM7CC) -O2 $(DC_ARM7INCS) -c $< -o $@

%.o: %.s
	$(DC_ARM7AS) $< -o $@

clean:
	-rm -f *.o *.srec *.elf 1ST_READ.BIN prog.bin *.bck
