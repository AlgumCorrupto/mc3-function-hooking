/*
    This is the armips code that I use to link my code written in C into the game’s .elf.
    See https://github.com/Kingcom/armips
*/

.ps2
.Open "./data/FILES/slus_213.55", 0x19FF80

; exporting symbols to be used by the C code
; some function pointers
.definelabel flush_splash_channel, 0x002969B8
.definelabel get_translated_text, 0x002BE510 
.definelabel set_splash_channel_text, 0x00296BF8
.definelabel play_splash_animation, 0x002967A8
.definelabel create_menu_item, 0x42a630
.definelabel create_menu_item_action, 0x42a668
.definelabel add_menu_item, 0x5882c8
.definelabel widget_string, 0x588540
.definelabel do_resume, 0x33b2f8
.definelabel update_pause_menu, 0x3578a8
.definelabel close_menu, 0x33b3e0

; some libc functions
.definelabel sprintf, 0x42f9f0
.definelabel memset, 0x4329b0
.definelabel memcpy, 0x432b20
.definelabel memcmp, 0x432d38
.definelabel strol, 0x4317d8
.definelabel strlen, 0x432808
.definelabel strncmp, 0x432968
.definelabel strcat, 0x432d78
.definelabel strncat, 0x432dd0
.definelabel strcpy, 0x432e58
.definelabel strncpy, 0x432e98
.definelabel strcmp, 0x432f18
.definelabel strcspn, 0x433160

; some magic variables
.definelabel dword_61B1E0, 0x61B1E0
.definelabel dword_617ADC, 0x617ADC
.definelabel translation_manager_ptr, 0x6BE860
.definelabel unk_656664,      0x656664
.definelabel benchmark_flag,  0x6F60B0
.definelabel unpause_function_base, 0x619958
.definelabel cyclic_direction, 0x6E0398
c_code_addr equ 0x61C860 ; where the C code will be stored in the executable

; writing the compiled C code inside unused area of the executable
.org c_code_addr
    .importlib "./mod.a"

; hijacking the control flow of the pause ui building
;.org 0x358D18
;    li  s4, 2 ; setting the acumulator to 1
;.org 0x358cac
;.definelabel normal_flow, 0x358CD4
;.definelabel dword_619D5C, 0x619D5C
;    jal custom_button_addr
;    nop
;    j normal_flow

; hijacking the translate text function to never make the text !!look like this!!
.org 0x002BE5D0
    j 0x002BE684

; hijacking the audio menu for testing
.org 0x3847d0
    lw a0,0xa0(sp)
    jal custom_button
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

.Close
