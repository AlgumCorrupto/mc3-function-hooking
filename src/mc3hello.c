#include "mc3.h"


void hello_world() {
    #define CH 28
    splash_manager* mgr = get_splash_manager();
    flush_splash_channel(mgr, CH);

    // utf-8 string
    const short text[] = {
        'y', 'o', 'y', ' ', 'c', 'r', 'a', 's', 'h'
    };

    set_splash_channel_text(mgr, CH, text);
    play_splash_animation(mgr, CH, 0, 0);
}

