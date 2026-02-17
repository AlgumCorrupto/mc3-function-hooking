CC = mips64r5900el-ps2-elf-gcc
NM = mips64r5900el-ps2-elf-nm
CFLAGS = -Wall -nostdlib -nostartfiles -ffreestanding -fshort-wchar -mabi=eabi -mno-abicalls -mlong32 -fno-builtin-printf -I./include/ -mhard-float -O2 -G0
AR = mips64r5900el-ps2-elf-ar

SRCS:=$(wildcard ./src/*.c)
OBJS:= $(patsubst ./src/%.c,./obj/%.o,$(SRCS))

all: pnach

pnach: pnach.asm mod.asm mod.a UNPACK_default.iso
	armips pnach.asm
	python3 ./armips2pnach.py

iso: data link
	ps2iso pack data/METADATA.json
	mv data/OUTPUT.iso modded.iso

link: data UNPACK_default.iso iso.asm mod.a mod.asm
	chmod u+w ./data/FILES/slus_213.55
	armips iso.asm
	chmod u-w ./data/FILES/slus_213.55

UNPACK_default.iso: default.iso
	ps2iso unpack default.iso

data: UNPACK_default.iso
	rm -rf data
	cp -r UNPACK_default.iso data

./obj/%.o: ./src/%.c | ./obj
	$(CC) $(CFLAGS) -c $< -o $@

./obj:
	mkdir -p ./obj

mod.a: $(OBJS)
	cd ./obj && ar x /usr/local/ps2dev/ee/lib/gcc/mips64r5900el-ps2-elf/15.2.0/libgcc.a
	cd ..
	$(AR) rcs $@ $^ ./obj/_unpack_sf.o ./obj/_make_df.o  ./obj/_sf_to_df.o  ./obj/_pack_df.o

default.iso:
	@echo "Error: default.iso not found!"
	@exit 1

.PHONY: clean
clean:
	rm -rf $(OBJDIR) mod.a
