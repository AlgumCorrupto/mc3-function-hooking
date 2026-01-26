CC = mips64r5900el-ps2-elf-gcc
NM = mips64r5900el-ps2-elf-nm
CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding -Oz
LDFLAGS = -nodefaultlibs

all: modded.iso

modded.iso: data link
	ps2iso pack data/METADATA.json
	mv data/OUTPUT.iso modded.iso

link: data linker.asm hello.o
	chmod u+w ./data/FILES/slus_213.55
	armips linker.asm
	chmod u-w ./data/FILES/slus_213.55

.PHONY: data
data: default.iso
	rm -rf data
	ps2iso unpack default.iso
	mv UNPACK_default.iso data

hello.o: ./src/hello.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c ./src/hello.c -o hello.o

default.iso:
	@echo "Error: default.iso not found!"
	@exit 1

clean:
	rm -rf data hello.o modded.iso
