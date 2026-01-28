typedef unsigned long long  u64;
typedef unsigned int        u32;
typedef unsigned short      u16;
typedef unsigned char       u8;
typedef signed long long    i64;
typedef signed int          i32;
typedef signed short        i16;
typedef signed char         i8;
typedef unsigned short      wchar;

typedef struct {
   u32 unk04;
   u32 unk08;
   char* text;
} translation_t;

typedef struct {
    void *widget;   // vtable-based UI animation object
    u32   param;    // style / duration / flags
} splash_entry;

typedef struct {
    /* 0x00 */ splash_entry entries[10]; // 80 bytes

    /* 0x50 */ u8 unk50[32];       // animation state / timing

    /* 0x70 */ u32 write_index;         // v13[40]
    /* 0x74 */ u32 read_index;          // v13[41]
    /* 0x78 */ u32 count;               // v13[42]

    /* total: 172 bytes */
} splash_channel_ring;

typedef struct {
    /* 0x00 */ void *vtable;
    /* 0x04 */ u8 unk[0x90 - 4];;
    /* 0x90 */ wchar *text_buffer;   // UTF-16, wcscpy target
} splash_channel;

typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u32 unk0C;
    /* 0x10 */ u32 ring_index; // used to select SplashChannelRing
} splash_channel_ref;

typedef struct {
    /* 0x00 */ void *vtable;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u32 unk08;

    /* 0x0C */ splash_channel *channels_by_id[32];
    /* 0x8C */ splash_channel_ring rings[];  // indexed indirectly
} splash_manager;

typedef struct {
    u32 unknown0;
    u64 unknown1;
    u32 unknown2;
    u32 unknown3;
} menu_item_widget;


typedef void (*handler_t)(u64, i32);
//typedef void (*click_handler_t)(u64);
typedef struct {
    u32 unknown;
    handler_t handler;
} menu_item_params;

typedef struct {
    u32 owner;
    menu_item_params params;
    u32 action;
    u32 unknown;
} menu_item;

typedef int ui_context;
typedef int hud_context;
typedef enum {
    CLICK = 0,
    IDK0  = 1,
    CYCLE = 2,
} menu_item_type;

extern void flush_splash_channel(splash_manager* splash_mgr, u32 channel_id);
extern translation_t get_translated_text(int* translation_mgr, char* key);
extern void set_splash_channel_text(splash_manager* splash_mgr, u32 channel_id, const wchar* text);
extern void play_splash_animation(splash_manager* splash_mgr, u32 channel_id, u32 unk_0, u32 unk_1);
extern void create_menu_item(menu_item* item, menu_item_params params, u32 owner);
extern void create_menu_item_action(menu_item* item, menu_item_params params, u32 owner, u32 action, u32 flag);
// i put 0 into unknown when calling this function
extern menu_item_widget* add_menu_item(u32 menu_id, u32 position, menu_item_type type, menu_item* item);
extern void resume(u64 unknown);
// text is a utf-16 string
extern void widget_string(u32 menu_id, menu_item_widget* item, u32 unknown, const wchar* text);
extern u64 update_pause_menu(u64 unknown);
extern u32 translation_manager_ptr;
extern u32 dword_61B1E0; // used for the splash text
extern u32 dword_617ADC; // used to get the pause menu context
extern u64 unk_656664;
extern u8  benchmark_flag;
extern u32 unpause_function_base;

splash_manager* get_splash_manager() {
    ui_context  *ui = *(ui_context **)(dword_61B1E0 + 8);
    hud_context *hud = *(hud_context **)((u8 *)ui + 112);

    return *(splash_manager **)((u8 *)hud + 80);
}

u32* get_pause_menu_ctx() {
    return *(u32**)(dword_617ADC + 12);
}

// Or one-liner:

typedef void (*widget_update_fn_t)(u32 self);
void update_widget(u32 self) {
    u32 vtable = *(u32 *)self;
    widget_update_fn_t fn =
        *(widget_update_fn_t *)(vtable + 228);

    fn(self);

}
//typedef void (*unpause_fn_t)(u64 self, u64 arg);
//void unpause(u64 code) {
//    u32 obj_addr = unpause_function_base;
//
//    // read vtable pointer (32-bit)
//    u32 vtable_addr = *(u32 *)obj_addr;
//
//    // get function pointer at offset +12
//    unpause_fn_t fn = *(unpause_fn_t *)((char *)vtable_addr + 12);
//
//    // call it
//    fn(obj_addr, 2);
//}
