CC = mips64r5900el-ps2-elf-gcc
NM = mips64r5900el-ps2-elf-nm
CFLAGS = -Wall  -nostdlib -nostartfiles -ffreestanding -fshort-wchar -mabi=eabi -mno-abicalls -mlong32 -fno-builtin-printf -I./include/
AR = mips64r5900el-ps2-elf-ar

SRCS:=$(wildcard ./src/*.c)
OBJS:=$(patsubst ./src/%.c,./obj/%.o,$(SRCS))

all: pnach

pnach: pnach.asm mod.asm mod.a original.elf
	armips pnach.asm
	python3 ./armips2pnach.py

./obj/%.o: ./src/%.c | ./obj
	$(CC) $(CFLAGS) -c $< -o $@

./obj:
	mkdir -p ./obj

mod.a: $(OBJS)
	$(AR) rcs $@ $^

original.elf:
	@echo "Error: original.elf not found!"
	@exit 1

.PHONY: clean
clean:
	rm -rf $(OBJDIR) mod.a
