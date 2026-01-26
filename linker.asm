/*
    This is the armips code that I use to link my code written in C into the game’s .elf.
    See https://github.com/Kingcom/armips
*/

.ps2
.Open "./data/FILES/slus_213.55", 0x19FF80

; exporting symbols to be used by the C code
.definelabel flush_splash_channel, 0x002969B8
.definelabel get_translated_text, 0x002BE510
.definelabel set_splash_channel_text, 0x00296BF8
.definelabel play_splash_animation, 0x002967A8
.definelabel translation_manager_ptr, 0x6BE860
.definelabel dword_61B1E0, 0x61B1E0

c_code_addr equ 0x61C860 ; where the C code will be stored in the executable
hello_world_offs equ 0x00000018 ; the offset of the hello_world function relative to the start of the c_code_addr
                                ; you can get it by running mips64r5900el-ps2-elf-nm -n hello.c
hello_world_addr equ c_code_addr + hello_world_offs ; absolute hello world function address

; writing the compiled C code inside unused area of the executable
.org c_code_addr
    .importobj "./hello.o"

; patching starting from 0x005A0F74 to call the hello_world function defined in ./src/hello.c
.org 0x005A0F74
    addiu sp, sp, -4
    sw    ra, 0(sp)
    jal hello_world_addr
    nop
    lw ra, 0(sp)
    addiu sp, sp, 0x4
.org 0x5a0fe4
    nop
    nop
    nop
.org 0x005A0FF4
    nop

.Close
