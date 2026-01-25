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

; writing the compiled C code inside unused area of the executable
.org 0x61C860
    .importobj "./hello.o"

; patching starting from 0x005A0F74 to call the hello_world function defined in ./src/mc3hello.c
.org 0x005A0F74
    addiu sp, sp, -4
    sw    ra, 0(sp)
    jal 0x61C8A8 ; where the .o file was imported + the offset of hello_world function (that you can get with
                 ; mips64r5900el-ps2-elf-nm -S hello.o
                 ; (0x61C860 + 0x48) 
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
