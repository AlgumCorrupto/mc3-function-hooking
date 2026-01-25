CC = mips64r5900el-ps2-elf-gcc
CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding
LDFLAGS = -nodefaultlibs

.PHONY: all
all: modded.iso

modded.iso: data link
	ps2iso pack data/METADATA.json
	mv data/OUTPUT.iso modded.iso

link: data linker.asm hello.o
	chmod u+w ./data/FILES/slus_213.55
	armips linker.asm
	chmod u-w ./data/FILES/slus_213.55

data: default.iso
	ps2iso unpack default.iso
	mv UNPACK_default.iso data

hello.o: ./src/hello.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c ./src/hello.c
