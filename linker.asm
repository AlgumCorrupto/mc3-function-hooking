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
.definelabel create_menu_item_warn, 0x42a668
.definelabel add_menu_item, 0x5882c8
.definelabel widget_string, 0x588540
; some magic variables
.definelabel dword_61B1E0, 0x61B1E0
.definelabel dword_617ADC, 0x617ADC
.definelabel translation_manager_ptr, 0x6BE860
.definelabel unk_656664,      0x656664
.definelabel benchmark_flag,  0x6F60B0
.definelabel unpause_function_base, 0x619958
.definelabel resume, 0x33b2f8

c_code_addr equ 0x61C860 ; where the C code will be stored in the executable
;custom_handler_offs equ 0x0000009c
;custon_handler_addr equ c_code_addr + custom_handler_offs
custom_button_offs  equ 0x00000090
custom_button_addr  equ c_code_addr + custom_button_offs

; writing the compiled C code inside unused area of the executable
.org c_code_addr
    .importobj "./mod.o"

; hijacking the control flow of the pause ui building
.org 0x358D18
    li  s4, 1 ; setting the acumulator to 1
.org 0x358cac
.definelabel normal_flow, 0x358CD4
.definelabel dword_619D5C, 0x619D5C
    jal custom_button_addr
    nop
    j normal_flow

; hooking the action code handler
;.org 0x33b980
;.definelabel retu, 0x0033BA50
;    jal custon_handler_addr     ;nop
;    nop
;    j retu

.Close
