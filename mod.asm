.ps2
.Open "./data/FILES/slus_213.55", 0x19FF80

.definelabel flush_splash_channel, 0x002969B8
.definelabel get_translated_text, 0x002BE510
.definelabel set_splash_channel_text, 0x00296BF8
.definelabel play_splash_animation, 0x002967A8
.definelabel translation_manager_ptr, 0x6BE860
.definelabel dword_61B1E0, 0x61B1E0

.org 0x61C860
    .importobj "./mc3hello.o"

.org 0x005A0F78
    jal 0x61C878
    nop
    nop
    nop
    nop
    nop

.org 0x5a10d4
    nop
    nop
    nop
    nop

.org 0x002BE5D0
    j 0x002BE684
    nop

.org 0x0064C38A
    .asciiz "Fucking around"

.Close
