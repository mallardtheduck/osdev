#include <module_stubs.h>
#include <terminal.h>
#include <video_dev.h>
#include "terminal.hpp"

void draw_cursor_8bpp(file_handle *file, uint32_t left, uint32_t top, bt_terminal_pointer_bitmap *bitmap, uint8_t *data, bt_vidmode &mode);
void draw_cursor_4bpp(file_handle *file, uint32_t left, uint32_t top, bt_terminal_pointer_bitmap *bitmap, uint8_t *data, bt_vidmode &mode);
uint8_t *get_background_8bpp(file_handle *file, uint32_t left, uint32_t top, bt_terminal_pointer_bitmap *bitmap, bt_vidmode &mode);
uint8_t *get_background_4bpp(file_handle *file, uint32_t left, uint32_t top, bt_terminal_pointer_bitmap *bitmap, bt_vidmode &mode);

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
    if(mode.bpp != bitmap->bpp) return;
    if(mode.bpp >= 8){
        draw_cursor_8bpp(file, x, y, bitmap, data, mode);
    }else if(mode.bpp == 4){
        draw_cursor_4bpp(file, x, y, bitmap, data, mode);
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
                if(datapos+depth > bitmap->datasize) return;
                size_t outpos = (ypos * mode.width * depth) + (xpos * depth);
                if (data!=bitmap->data || !bmemcmp((void *) &data[datapos], (void *) &bitmap->transparent, depth)) {
                    fseek(file, outpos, false);
                    fwrite(file, depth, (char *) &data[datapos]);
                }
            }
        }
    fseek(file, pos, false);
}

void draw_cursor_4bpp(file_handle *file, uint32_t left, uint32_t top, bt_terminal_pointer_bitmap *bitmap, uint8_t *data, bt_vidmode &mode) {
    int x=left - bitmap->spot_x;
    int y=top - bitmap->spot_y;
    uint8_t ovalue;
    size_t lastread=0;
    size_t pos=fseek(file, 0, true);
    for(int ypos=y; ypos < (int)(y+bitmap->h); ++ypos){
        if(ypos < 0 || ypos >= (int)(mode.height)) continue;
        for(int xpos=x; xpos < (int)(x+bitmap->w); ++xpos) {
            if(xpos < 0 || xpos >= (int)(mode.width)) continue;
            uint32_t by = (uint32_t)(ypos - y);
            uint32_t bx = (uint32_t)(xpos - x);
            size_t datapos = (by * bitmap->w)  + (bx);
            size_t dindex=datapos/2;
            if(dindex >= bitmap->datasize) return;
            uint8_t value=0;
            if(datapos % 2){
                value = (uint8_t)(data[dindex] & 0x0F);
            }else{
                value = (uint8_t)((data[dindex] >> 4) & 0x0F);
            }
            size_t outpos = (ypos * mode.width) + (xpos);
            size_t oindex = outpos/2;
            if (data != bitmap->data || value != bitmap->transparent) {
                if(!lastread || lastread != oindex) {
                    fseek(file, oindex, false);
                    fread(file, 1, (char *) &ovalue);
                    lastread=oindex;
                }
                if(outpos % 2){
                    ovalue = (uint8_t)((ovalue & 0xF0) | (value & 0x0F));
                }else{
                    ovalue = (uint8_t)((ovalue & 0x0F) | ((value << 4) & 0xF0));
                }
                fseek(file, oindex, false);
                fwrite(file, 1, (char *) &ovalue);
            }
        }
    }
    fseek(file, pos, false);
}

uint8_t *get_graphics_pointer_background(file_handle *file, uint32_t x, uint32_t y, bt_terminal_pointer_bitmap *bitmap) {
    if(!bitmap) return NULL;
    bt_vidmode mode;
    fioctl(file, bt_vid_ioctl::QueryMode, sizeof(mode), (char*)&mode);
    if(mode.bpp != bitmap->bpp) return NULL;
    if(mode.bpp >= 8){
        return get_background_8bpp(file, x, y, bitmap, mode);
    }else if(mode.bpp==4){
        return get_background_4bpp(file, x, y, bitmap, mode);
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

uint8_t *get_background_4bpp(file_handle *file, uint32_t left, uint32_t top, bt_terminal_pointer_bitmap *bitmap, bt_vidmode &mode) {
    int x=left - bitmap->spot_x;
    int y=top - bitmap->spot_y;
    size_t pos=fseek(file, 0, true);
    uint8_t *ret=(uint8_t*)malloc(bitmap->datasize);
    memset(ret, 0, bitmap->datasize);
    for(int ypos=y; ypos < (int)(y+bitmap->h); ++ypos){
        if(ypos < 0 || ypos >= (int)(mode.height)) continue;
        for(int xpos=x; xpos < (int)(x+bitmap->w); ++xpos) {
            if(xpos < 0 || xpos >= (int)(mode.width)) continue;
            uint32_t by = (uint32_t)(ypos - y);
            uint32_t bx = (uint32_t)(xpos - x);
            size_t datapos = (by * bitmap->w) + (bx);
            size_t dindex=datapos/2;
            uint8_t value=ret[dindex];
            size_t outpos = (ypos * mode.width) + (xpos);
            size_t oindex = outpos/2;
            uint8_t ovalue;
            fseek(file, oindex, false);
            fread(file, 1, (char*)&ovalue);
            if(outpos % 2){
                ovalue = (uint8_t)(ovalue & 0x0F);
            }else{
                ovalue = (uint8_t)((ovalue >> 4) & 0x0F);
            }
            if(datapos % 2){
                ret[dindex] = (uint8_t)((value & 0xF0) | (ovalue & 0x0F));
            }else{
                ret[dindex] = (uint8_t)((value & 0x0F) | ((ovalue << 4) & 0xF0));
            }
        }
    }
    fseek(file, pos, false);
    return ret;
}
