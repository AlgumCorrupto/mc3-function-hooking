CC = mips64r5900el-ps2-elf-gcc
NM = mips64r5900el-ps2-elf-nm
CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding -fshort-wchar
LDFLAGS = -nodefaultlibs
AR = mips64r5900el-ps2-elf-ar


all: modded.iso

modded.iso: data link
	ps2iso pack data/METADATA.json
	mv data/OUTPUT.iso modded.iso

link: data linker.asm mod.a
	chmod u+w ./data/FILES/slus_213.55
	armips linker.asm
	chmod u-w ./data/FILES/slus_213.55

UNPACK_default.iso: default.iso
	ps2iso unpack default.iso

.PHONY: data
data: UNPACK_default.iso
	rm -rf data
	cp -r UNPACK_default.iso data

mod.o: ./src/mod.c ./src/mc3.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c ./src/mod.c -o mod.o

mod.a: mod.o
	ar rcs mod.a mod.o

default.iso:
	@echo "Error: default.iso not found!"
	@exit 1

.PHONY: clean
clean:
	rm -rf mod.o mod.a
