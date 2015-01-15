#include <module_stubs.h>
#include <terminal.h>
#include <video_dev.h>
#include "terminal.hpp"

void draw_cursor_8bpp(file_handle *file, uint32_t x, uint32_t y, bt_terminal_pointer_bitmap *bitmap, uint8_t *data, bt_vidmode &mode);
uint8_t *get_background_8bpp(file_handle *file, uint32_t left, uint32_t top, bt_terminal_pointer_bitmap *bitmap, bt_vidmode &mode);

static bool bmemcmp(const void *p1, const void *p2, size_t n) {
    unsigned char *s1=(unsigned char*)p1, *s2=(unsigned char*)p2;
    unsigned char u1, u2;

    for (; n--; s1++, s2++) {
        u1 = *(unsigned char *) s1;
        u2 = *(unsigned char *) s2;
        if (u1 != u2) {
            return false;
        }
    }
    return true;
}

void draw_graphics_pointer(file_handle *file, uint32_t x, uint32_t y, bt_terminal_pointer_bitmap *bitmap, uint8_t *data){
    if(!bitmap) return;
    if(!data) data=bitmap->data;
    bt_vidmode mode;
    fioctl(file, bt_vid_ioctl::QueryMode, sizeof(mode), (char*)&mode);
    if(!mode.bpp == bitmap->bpp) return;
    if(mode.bpp >= 8){
        draw_cursor_8bpp(file, x, y, bitmap, data, mode);
    }
}

void draw_cursor_8bpp(file_handle *file, uint32_t left, uint32_t top, bt_terminal_pointer_bitmap *bitmap, uint8_t *data, bt_vidmode &mode) {
    int x=left - bitmap->spot_x;
    int y=top - bitmap->spot_y;
    size_t pos=fseek(file, 0, true);
    size_t depth=mode.bpp/8;
    for(int ypos=y; ypos < (int)(y+bitmap->h); ++ypos){
            if(ypos < 0 || ypos >= (int)(mode.height)) continue;
            for(int xpos=x; xpos < (int)(x+bitmap->w); ++xpos) {
                if(xpos < 0 || xpos >= (int)(mode.width)) continue;
                uint32_t by = (uint32_t)(ypos - y);
                uint32_t bx = (uint32_t)(xpos - x);
                size_t datapos = (by * bitmap->w * depth) + (bx * depth);
                size_t outpos = (ypos * mode.width * depth) + (xpos * depth);
                if (data!=bitmap->data || !bmemcmp((void *) &data[datapos], (void *) &bitmap->transparent, depth)) {
                    fseek(file, outpos, false);
                    fwrite(file, depth, (char *) &data[datapos]);
                }
            }
        }
    fseek(file, pos, false);
}

uint8_t *get_graphics_pointer_background(file_handle *file, uint32_t x, uint32_t y, bt_terminal_pointer_bitmap *bitmap) {
    if(!bitmap) return NULL;
    bt_vidmode mode;
    fioctl(file, bt_vid_ioctl::QueryMode, sizeof(mode), (char*)&mode);
    if(!mode.bpp == bitmap->bpp) return NULL;
    if(mode.bpp >= 8){
        return get_background_8bpp(file, x, y, bitmap, mode);
    }
    return NULL;
}

uint8_t *get_background_8bpp(file_handle *file, uint32_t left, uint32_t top, bt_terminal_pointer_bitmap *bitmap, bt_vidmode &mode) {
    int x=left - bitmap->spot_x;
    int y=top - bitmap->spot_y;
    size_t pos=fseek(file, 0, true);
    size_t depth=mode.bpp/8;
    uint8_t *ret=(uint8_t*)malloc(bitmap->datasize);
    memset(ret, 0, bitmap->datasize);
    for(int ypos=y; ypos < (int)(y+bitmap->h); ++ypos){
        if(ypos < 0 || ypos >= (int)(mode.height)) continue;
        for(int xpos=x; xpos < (int)(x+bitmap->w); ++xpos) {
            if(xpos < 0 || xpos >= (int)(mode.width)) continue;
            uint32_t by = (uint32_t)(ypos - y);
            uint32_t bx = (uint32_t)(xpos - x);
            size_t datapos = (by * bitmap->w * depth) + (bx * depth);
            size_t outpos = (ypos * mode.width * depth) + (xpos * depth);
            fseek(file, outpos, false);
            fread(file, depth, (char*)&ret[datapos]);
        }
    }
    fseek(file, pos, false);
    return ret;
}
