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
void custom_click_handler(u64 self, i32 unknown2) {
    benchmark_flag ^= 1;
    //update_widget((u32)self);
}

//void custom_cycle_handler(u64 unknown1, i32 unknown2) {
//    benchmark_flag = 1 ? benchmark_flag == 0 : 1;
//}

void custom_button() {
    menu_item custom_item;
    menu_item_widget* custom_widget;
    u32* pause_menu_ctx = get_pause_menu_ctx();

    menu_item_params params = {0xFFFF0000, custom_click_handler};

    // create the menu item with warning type
    create_menu_item_action(&custom_item, params, pause_menu_ctx[3], 1, 1);

    // add the item to the menu (pause_menu_ctx[60] is the menu id)
    custom_widget = add_menu_item(pause_menu_ctx[60], 0, CYCLE, &custom_item);

    static const wchar debug_on[]  = L"Debug: on";
    static const wchar debug_off[] = L"Debug: off";

    // set the button text
    if (benchmark_flag)
        widget_string(pause_menu_ctx[60], custom_widget, 2, debug_on);
    else
        widget_string(pause_menu_ctx[60], custom_widget, 2, debug_off);
}
