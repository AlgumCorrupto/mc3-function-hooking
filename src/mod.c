#include <mc3.h>

static u32 x = 515;
static u32 y = 245;

//static u32 announce_code = 28;
static enum {
    DISABLED = 0,
    MPH      = 1,
    KMH      = 2,
    MS       = 3,
    MPH_KMH  = 4,
} unit = 1;

// Making a splash message that say hello!
//void say_hello(u32 channel) {
//    // i'm calling them channels
//    char char_buffer[32];
//    sprintf(char_buffer, "Testing channel %d", channel);
//    // hacking get_translated_text to convert ascii text to utf-16 text
//    translation_t* channel_text = get_translated_text(&translation_manager_ptr, char_buffer);
//    // feel free to experiment changing CH to a different number
//    splash_manager* mgr = get_splash_manager();
//    flush_splash_channel(mgr, channel);
//    // utf-16 string
//    set_splash_channel_text(mgr, channel, channel_text->text);
//    play_splash_animation(mgr, channel, 0, 0);
//}

void change_unit_handler(void* self, i32 direction) {
    unit += 5;
    unit += direction;
    unit %= 5;
    update_widget(self);
}

void change_x_handler(void* self, i32 direction) {
    x += direction;
    update_widget(self);
}

void change_y_handler(void* self, i32 direction) {
    y += direction;
    update_widget(self);
}

void render_speedo(int this) {
    if(unit == DISABLED) {
        return;
    } else {
        float speed_ms = *(float *)(*(u32 *)((u8 *)this + 0x440) + 0xb0);
        char buffer[32];
        int oy = 0;
        switch(unit) {
            case MS:
                sprintf(buffer, "%3d ms", (int)(speed_ms + .5f));
                break;
            case MPH:
                sprintf(buffer, "%3d mph", (int)(speed_ms * 2.237f + .5f));
                break;
            case KMH:
                sprintf(buffer, "%3d kmh", (int)(speed_ms * 3.6f + .5f));
                break;
            case MPH_KMH:
                sprintf(buffer, "%3d kmh\n%3d mph", (int)(speed_ms * 3.6f + .5f), (int)(speed_ms * 2.237f + .5f));
                oy = -16;
                break;
            default:
                sprintf(buffer, "Not a valid unit!");
                break;
        }
        debug_draw(x, y+oy, buffer, (void *)0x80ffffff);
    }
}

void custom_button(int menu_ctx) {
    u32* pause_menu_ctx = get_pause_menu_ctx();
    int menu_offs = -1;
    if (((DAT_0061443c != 0) && (*(int *)(DAT_0061443c + 0xc) != 0)) &&
    (*(char *)(DAT_00619318 + 0x70) == '\0')) {
        menu_offs = 1;
    }

    // debug cyclic
    menu_item unit_item;
    menu_item_widget* unit_widget;

    menu_item_params params;
    params.unknown = 0xFFFF0000;
    params.handler = change_unit_handler;

    create_menu_item_action(&unit_item, params, menu_ctx, 1, 0);
    unit_widget = add_menu_item(pause_menu_ctx[60], 5, CYCLE, &unit_item);
    char* unit_fmt;

    switch(unit) {
        case DISABLED:
            unit_fmt = "Speedometer: Default";
            break;
        case MPH:
            unit_fmt = "Speedometer: MPH";
            break;
        case KMH:
            unit_fmt = "Speedometer: KMH";
            break;
        case MS:
            unit_fmt = "Speedometer: MS";
            break;
        case MPH_KMH:
            unit_fmt = "Speedometer: MPH and KMH";
            break;
        default:
            unit_fmt = "Speedometer: Unknown";
            break;
    }

    // hacking get_translated_text to convert ascii text to utf-16 text
    translation_t* unit_text = get_translated_text(&translation_manager_ptr, unit_fmt);

    widget_string(pause_menu_ctx[60], unit_widget, 2, unit_text->text);

    menu_item x_item;
    menu_item_widget* x_widget;

    params.unknown = 0xFFFF0000;
    params.handler = change_x_handler;
    char coord_fmt[32];
    sprintf(coord_fmt, "Speedo X: %d", x);
    create_menu_item_action(&x_item, params, menu_ctx, 1, 0);
    x_widget = add_menu_item(pause_menu_ctx[60], 5+menu_offs, CYCLE, &x_item);
    translation_t* x_text = get_translated_text(&translation_manager_ptr, coord_fmt);
    widget_string(pause_menu_ctx[60], x_widget, 2, x_text->text);

    menu_item y_item;
    menu_item_widget* y_widget;

    params.unknown = 0xFFFF0000;
    params.handler = change_y_handler;
    sprintf(coord_fmt, "Speedo Y: %d", y);
    create_menu_item_action(&y_item, params, menu_ctx, 1, 0);
    y_widget = add_menu_item(pause_menu_ctx[60], 6+menu_offs, CYCLE, &y_item);
    translation_t* y_text = get_translated_text(&translation_manager_ptr, coord_fmt);
    widget_string(pause_menu_ctx[60], y_widget, 2, y_text->text);
}
