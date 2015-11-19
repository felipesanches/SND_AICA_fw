# $Id: Makefile,v 1.3 2002/10/29 15:43:18 mrbrown Exp $
#define cross compiler location etc

CROSS_COMPILE=arm-elf-

#change the next variable to fit your set up!
PATH_TO_X=/home/Adrian/ARM/build/H-i686-pc-linux-gnu/bin/

DC_ARM7AS		= $(PATH_TO_X)$(CROSS_COMPILE)as
DC_ARM7LD		= $(PATH_TO_X)$(CROSS_COMPILE)ld
DC_ARM7CC		= $(PATH_TO_X)$(CROSS_COMPILE)gcc
DC_ARM7CPP		= $(PATH_TO_X)$(CC) -E
DC_ARM7AR		= $(PATH_TO_X)$(CROSS_COMPILE)ar
DC_ARM7NM		= $(PATH_TO_X)$(CROSS_COMPILE)nm
DC_ARM7STRIP		= $(PATH_TO_X)$(CROSS_COMPILE)strip
DC_ARM7OBJCOPY		= $(PATH_TO_X)$(CROSS_COMPILE)objcopy
DC_ARM7OBJDUMP		= $(PATH_TO_X)$(CROSS_COMPILE)objdump

all: stream.drv

#aica_fw.h: stream.drv
#	../../../utils/bin2c/bin2c stream.drv aica_fw.h.tmp
#	echo 'unsigned char aica_fw[] = {' > aica_fw.h
#	cat aica_fw.h.tmp >> aica_fw.h
#	echo '};' >> aica_fw.h
#	-rm aica_fw.h.tmp

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


