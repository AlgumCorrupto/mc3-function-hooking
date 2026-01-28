CC = mips64r5900el-ps2-elf-gcc
NM = mips64r5900el-ps2-elf-nm
CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding -Oz -fshort-wchar
LDFLAGS = -nodefaultlibs

all: modded.iso

modded.iso: data link
	ps2iso pack data/METADATA.json
	mv data/OUTPUT.iso modded.iso

link: data linker.asm mod.o
	chmod u+w ./data/FILES/slus_213.55
		armips linker.asm
	chmod u-w ./data/FILES/slus_213.55

.PHONY: data
data: default.iso
	rm -rf data
	ps2iso unpack default.iso
	mv UNPACK_default.iso data

mod.o: ./src/mod.c ./src/mc3.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c ./src/mod.c -o mod.o

default.iso:
	@echo "Error: default.iso not found!"
	@exit 1

clean:
	rm -rf data mod.o modded.iso
