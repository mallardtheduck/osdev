#include <btos_module.h>
#include <dev/terminal.h>
#include <dev/video_dev.h>
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
	const size_t staticbuffersize = 32;
	static uint8_t static_linebuffer[staticbuffersize];
	static uint8_t static_gbuffer[staticbuffersize];
	bool freebuffers = false;
    int x=left - bitmap->spot_x;
    int y=top - bitmap->spot_y;
    bool enable_transp = (bitmap->data == data);
    size_t pos=fseek(file, 0, true);
	uint8_t transp = (bitmap->transparent & 0x0F) | ((bitmap->transparent << 4) & 0xF0);
	size_t buffersize = (bitmap->w / 2) + 1;
	uint8_t *linebuffer = static_linebuffer;
	uint8_t *gbuffer = static_gbuffer;;
	if(buffersize > staticbuffersize){
		linebuffer = (uint8_t*)malloc(buffersize);
		gbuffer = (uint8_t*)malloc(buffersize);
		freebuffers = true;
	}
    for(int ypos=y; ypos < (int)(y+bitmap->h); ++ypos){
        if(ypos < 0 || ypos >= (int)(mode.height)) continue;
		uint8_t *linedata;
		size_t dsize = 0;
		if(left % 2){
			dsize = bitmap->w / 2;
			linedata = (data + (((ypos - y) * bitmap->w) / 2));
		}else{
			dsize = (bitmap->w / 2) + 1;
			linedata = linebuffer;
			memset(linedata, transp, dsize);
			for(size_t i=0; i<dsize - 1; ++i){
				uint8_t *source = (data + (((ypos - y) * bitmap->w) / 2));
				linedata[i] = (linedata[i] & 0xF0) | ((source[i] >> 4) & 0x0F);
				linedata[i + 1] = (linedata[i + 1] & 0x0F) | ((source[i] << 4) & 0xF0);
			}
		}
		uint8_t *gdata = gbuffer;
		size_t offset = 0;
		if(y <= 0 && ypos == 0 && x < 0) offset = ((-x) / 2) + ((-x) % 2);
		size_t outpos = (ypos * mode.width) + (x) + (offset * 2);
		size_t oindex = outpos / 2;
		if(enable_transp){
			fseek(file, oindex, false);
			fread(file, dsize - offset, (char*)gdata+offset);
			for(size_t i=0; i<dsize; ++i){
				int fxpos;
				int sxpos;
				if(left % 2){
					fxpos = x + (i * 2);
					sxpos = fxpos + 1;
				}else{
					fxpos = x + (i * 2) - 1;
					sxpos = fxpos + 1;
				}
				if(linedata[i] == transp) continue;
				if(fxpos >= (int)mode.width) continue;
				if(fxpos + (int)bitmap->w < 0) continue;
				if((linedata[i] & 0x0F) != (transp & 0x0F) && sxpos >= 0 && sxpos < (int)mode.width) gdata[i] = (gdata[i] & 0xF0) | (linedata[i] & 0x0F);
				if((linedata[i] & 0xF0) != (transp & 0xF0) && fxpos >= 0 && fxpos < (int)mode.width) gdata[i] = (gdata[i] & 0x0F) | (linedata[i] & 0xF0);
			}
		}else{
			if(left % 2) memcpy(gdata, linedata, dsize);
			else{
				fseek(file, oindex, false);
				fread(file, dsize - offset, (char*)gdata+offset);
				for(size_t i=0; i<dsize; ++i){
					if(i == 0) gdata[i] = (gdata[i] & 0xF0) | (linedata[i] & 0x0F);
					else if(i == dsize - 1) gdata[i] = (gdata[i] & 0x0F) | (linedata[i] & 0xF0);
					else gdata[i] = linedata[i];
				}
			}
		}
		fseek(file, oindex, false);
		fwrite(file, dsize - offset, (char*)gdata+offset);
    }
    fseek(file, pos, false);
	if(freebuffers){
		free(gbuffer);
		free(linebuffer);
	}
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
	const size_t staticbuffersize = 32;
	static uint8_t static_linebuffer[staticbuffersize];
	bool freebuffer = false;
    int x=left - bitmap->spot_x;
    int y=top - bitmap->spot_y;
    size_t pos=fseek(file, 0, true);
    uint8_t *ret=(uint8_t*)malloc(bitmap->datasize);
    memset(ret, 0, bitmap->datasize);
	size_t buffersize = (bitmap->w / 2) + 1;
	uint8_t *linebuffer = static_linebuffer;
	if(buffersize > staticbuffersize){
		linebuffer = (uint8_t*)malloc(buffersize);
		freebuffer = true;
	}
    for(int ypos=y; ypos < (int)(y+bitmap->h); ++ypos){
        if(ypos < 0 || ypos >= (int)(mode.height)) continue;
		size_t offset = 0;
		if(y <= 0 && ypos == 0 && x < 0) offset = ((-x) / 2) + ((-x) % 2);
		size_t outpos = (ypos * mode.width) + (x) + (offset * 2);
		size_t oindex = outpos / 2;
        size_t dsize = 0;
		uint8_t *linedata;
		if(left % 2){
			dsize = bitmap->w / 2;
			linedata = (ret + (((ypos - y) * bitmap->w) / 2));
		}else{
			dsize = (bitmap->w / 2) + 1;
			linedata = linebuffer;
		}
		fseek(file, oindex, false);
		fread(file, dsize - offset, (char*)linedata+offset);
		if(!(left % 2)){
			uint8_t *dest = (ret + (((ypos - y) * bitmap->w) / 2));
			for(size_t i=0; i<dsize - 1; ++i){
				dest[i] = ((linedata[i + 1] >> 4) & 0x0F) | ((linedata[i] << 4) & 0xF0);
			}
		}
    }
    fseek(file, pos, false);
	if(freebuffer) free(linebuffer);
    return ret;
}
