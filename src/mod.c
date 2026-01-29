#include "mc3.h"

// can't declare const wchars as local variables for some reason
// without clashing

// Making a splash message that say hello!
void say_hello() {
    // there's different animations and styles for the splash text, 
    // i'm calling them channels
    
    // feel free to experiment changing CH to a different number
    #define CH 28
    splash_manager* mgr = get_splash_manager();
    flush_splash_channel(mgr, CH);
    static const wchar splash_text[] = L"Sup my brochacho";

    // utf-16 string
    set_splash_channel_text(mgr, CH, splash_text);
    play_splash_animation(mgr, CH, 0, 0);
}

// just toggles the debug displays
void debug_widget_handler(void* self, i32 unknown2) {
    benchmark_flag = benchmark_flag == 1 ? 0 : 1;
    update_widget(self);
}

static u8 announce_code = 22;
void announce_cyclic_handler(void* self, i32 direction) {
    announce_code += direction;
    update_widget(self);
}

void custom_button(int menu_ctx) {
    //// debug cyclic
    menu_item debug_item;
    menu_item_widget* debug_widget;
    u32* pause_menu_ctx = get_pause_menu_ctx();

    menu_item_params params = {0xFFFF0000, debug_widget_handler};

    create_menu_item_action(&debug_item, params, menu_ctx, 1, 1);
    debug_widget = add_menu_item(pause_menu_ctx[60], 4, CYCLE, &debug_item);

    // Use writable static memory
    wchar debug_on[32]  = { 'D','e','b','u','g',':',' ','o','n',0 };
    wchar debug_off[32] = { 'D','e','b','u','g',':',' ','o','f','f',0 };

    if (benchmark_flag == 1)
        widget_string(pause_menu_ctx[60], debug_widget, 2, debug_on);
    else
        widget_string(pause_menu_ctx[60], debug_widget, 2, debug_off);

    // announce
    //menu_item announce_cyclic;
    //menu_item_widget* announce_cyclic_widget;
    //menu_item_params announce_cyclic_params = {0xFFFF0000, announce_cyclic_handler};

    //create_menu_item_action(&announce_cyclic, announce_cyclic_params, menu_ctx, 1, 1);
    //announce_cyclic_widget = add_menu_item(pause_menu_ctx[60], 4, CYCLE, &announce_cyclic);

    //char code[32];
    //sprintf(code, "Code: %d", announce_code);
    //translation_t code_text = get_translated_text(&translation_manager_ptr, code);
    //widget_string(pause_menu_ctx[60], announce_cyclic_widget, 2, code_text.text);
}
