typedef struct {
   int unk04;
   int unk08;
   char* text;
} translation_t;

typedef struct {
    void *widget;   // vtable-based UI animation object
    int   param;    // style / duration / flags
} splash_entry;

typedef struct {
    /* 0x00 */ splash_entry entries[10]; // 80 bytes

    /* 0x50 */ char unk50[32];       // animation state / timing

    /* 0x70 */ int write_index;         // v13[40]
    /* 0x74 */ int read_index;          // v13[41]
    /* 0x78 */ int count;               // v13[42]

    /* total: 172 bytes */
} splash_channel_ring;

typedef struct {
    /* 0x00 */ void *vtable;
    /* 0x04 */ char unk[0x90 - 4];;

    /* 0x90 */ short *text_buffer;   // UTF-16, wcscpy target
} splash_channel;

typedef struct {
    /* 0x00 */ signed int unk00;
    /* 0x04 */ signed int unk04;
    /* 0x08 */ signed int unk08;
    /* 0x0C */ signed int unk0C;
    /* 0x10 */ signed int ring_index; // used to select SplashChannelRing
} splash_channel_ref;

typedef struct {
    /* 0x00 */ void *vtable;
    /* 0x04 */ unsigned int unk04;
    /* 0x08 */ unsigned int unk08;

    /* 0x0C */ splash_channel *channels_by_id[32];
    /* 0x8C */ splash_channel_ring rings[];  // indexed indirectly
} splash_manager;


typedef int ui_context;
typedef int hud_context;

extern void flush_splash_channel(splash_manager* splash_mgr, int channel_id);
extern translation_t get_translated_text(int* translation_mgr, char* key);
extern void set_splash_channel_text(splash_manager* splash_mgr, int channel_id, const short* wtext);
extern void play_splash_animation(splash_manager* splash_mgr, int channel_id, int unk_0, int unk_1);
extern int translation_manager_ptr;
extern int dword_61B1E0;

splash_manager* get_splash_manager(void) {
    ui_context  *ui = *(ui_context **)(dword_61B1E0 + 8);
    hud_context *hud = *(hud_context **)((unsigned char *)ui + 112);

    return *(splash_manager **)((unsigned char *)hud + 80);
}
