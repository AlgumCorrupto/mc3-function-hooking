#include "mc3.h"

// the function getting hooked
void hello_world() {
    // there's different animations and styles for the splash text, 
    // i'm calling them channels
    
    // feel free to experiment changing CH to a different number
    #define CH 28
    splash_manager* mgr = get_splash_manager();
    flush_splash_channel(mgr, CH);

    // utf-16 string
    const short text[] = {
        'y', 'o', 'y', ' ', 'c', 'r', 'a', 's', 'h', 0
    };

    set_splash_channel_text(mgr, CH, text);
    play_splash_animation(mgr, CH, 0, 0);
}

