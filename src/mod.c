#include <types.h>
#include <mc3.h>
#include <sdk.h>

static u32 announce_code = 28;
// Making a splash message that say hello!
void say_hello(u32 channel) {
    // i'm calling them channels
    char char_buffer[32];
    sprintf(char_buffer, "Testing channel %d", channel);
    // hacking get_translated_text to convert ascii text to utf-16 text
    translation_t* channel_text = get_translated_text(&translation_manager_ptr, char_buffer);
    // feel free to experiment changing CH to a different number
    splash_manager* mgr = get_splash_manager();
    flush_splash_channel(mgr, channel);
    // utf-16 string
    set_splash_channel_text(mgr, channel, channel_text->text);
    play_splash_animation(mgr, channel, 0, 0);
}

// just toggles the debug displays
void debug_widget_handler(void* self, i32 direction) {
    benchmark_flag += direction;
    benchmark_flag %= 3;
    update_widget(self);
}

void announce_cyclic_handler(void* self, i32 direction) {
    announce_code += direction;
    announce_code %= 30;
    update_widget(self);
}

void announce_handler(void* self, i32 unused) {
    resume();
    say_hello(announce_code);
}

void custom_button(int menu_ctx) {
    u32* pause_menu_ctx = get_pause_menu_ctx();

    // debug cyclic
    menu_item debug_item;
    menu_item_widget* debug_widget;

    menu_item_params params;
    params.unknown = 0xFFFF0000;
    params.handler = debug_widget_handler;

    create_menu_item_action(&debug_item, params, menu_ctx, 1, 0);
    debug_widget = add_menu_item(pause_menu_ctx[60], 4, CYCLE, &debug_item);

    char char_buffer[32];
    char debug_fmt[32] = "Debug: %d";
    sprintf(char_buffer, debug_fmt, benchmark_flag);
    // hacking get_translated_text to convert ascii text to utf-16 text
    translation_t* debug_text = get_translated_text(&translation_manager_ptr, char_buffer);

    widget_string(pause_menu_ctx[60], debug_widget, 2, debug_text->text);

    // announce cyclic
    menu_item announce_cyclic;
    menu_item_widget* announce_cyclic_widget;

    params.unknown = 0xFFFF0000;
    params.handler = announce_cyclic_handler;

    create_menu_item_action(&announce_cyclic, params, menu_ctx, 1, 0);
    announce_cyclic_widget = add_menu_item(pause_menu_ctx[60], 5, CYCLE, &announce_cyclic);

    sprintf(char_buffer, "Announce code: %d", announce_code);

    // hacking get_translated_text to convert ascii text to utf-16 text
    translation_t* announce_cyclic_text = get_translated_text(&translation_manager_ptr, char_buffer);

    widget_string(pause_menu_ctx[60], announce_cyclic_widget, 2, announce_cyclic_text->text);

    // do announce button
    menu_item do_announce;
    menu_item_widget* do_announce_widget;

    params.unknown = 0xFFFF0000;
    params.handler = announce_handler;

    create_menu_item(&do_announce, params, menu_ctx);
    do_announce_widget = add_menu_item(pause_menu_ctx[60], 6, CLICK, &do_announce);

    wchar announce_text[] = L"Announce!";
    widget_string(pause_menu_ctx[60], do_announce_widget, 2, announce_text);
}

static char triangle_status = 0;

void check_input()
{
    struct padButtonStatus status;
    char last = triangle_status;

    if (padRead(0, 0, &status))
    {
        u16 raw = status.btns;
        u16 pressed = ~status.btns;
        
        if (pressed & PAD_TRIANGLE)
            say_hello(1);
        
        //if (status.triangle_p > 0)
        //    say_hello(2);

    }
}
