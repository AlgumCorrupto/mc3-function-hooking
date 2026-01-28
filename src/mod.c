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
void custom_handler(u64 unknown) {
    benchmark_flag = 1 ? benchmark_flag == 0 : 1;
    resume(unknown);
}

void custom_button() {
    menu_item custom_item;
    menu_item_widget* custom_widget;
    u32* pause_menu_ctx = get_pause_menu_ctx();

    menu_item_params params = {0xFFFF0000, custom_handler};

    // create the menu item with warning type
    create_menu_item(&custom_item, params, pause_menu_ctx[3]);

    // add the item to the menu (pause_menu_ctx[60] is the menu id)
    custom_widget = add_menu_item(pause_menu_ctx[60], 0, 0, &custom_item);

    static const wchar button_label[] = L"Show Debug View";

    // set the button text
    widget_string(pause_menu_ctx[60], custom_widget, 2, button_label);
}
