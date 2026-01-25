CC = mips64r5900el-ps2-elf-gcc
CFLAGS = -Wall -Oz -nostdlib -nostartfiles -ffreestanding
LDFLAGS = -nodefaultlibs

all: modded.iso

modded.iso: data patch
	./ps2iso_linux pack data/METADATA.json
	mv data/OUTPUT.iso modded.iso

patch: data mod.asm mc3hello.o
	chmod u+w ./data/FILES/slus_213.55
	armips mod.asm
	chmod u-w ./data/FILES/slus_213.55

data: default.iso
	./ps2iso_linux unpack default.iso
	mv UNPACK_default.iso data

mc3hello.o: ./src/mc3hello.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c ./src/mc3hello.c
