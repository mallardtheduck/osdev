#include <dev/video_dev.h>
#include "ops.hpp"
#include "device.hpp"
#include "modes.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"

void text_poscursor(size_t row, size_t col);

size_t text_read(vga_instance *inst, size_t bytes, char *buf){
    size_t maxchar=current_mode->vidmode.width * current_mode->vidmode.height * 2;
    if(inst->pos > maxchar) return 0;
    if(inst->pos+bytes > maxchar) bytes=maxchar-inst->pos;
    memcpy(buf, (char*)text_memory+inst->pos, bytes);
    inst->pos+=bytes;
    return bytes;
}

size_t text_write(vga_instance *inst, size_t bytes, char *buf){
    size_t maxchar=current_mode->vidmode.width * current_mode->vidmode.height * 2;
    if(inst->pos > maxchar) return 0;
    if(inst->pos+bytes > maxchar) bytes=maxchar-inst->pos;
    memcpy((char*)text_memory+inst->pos, buf, bytes);
    inst->pos+=bytes;
    return bytes;
}

size_t text_seek(vga_instance *inst, size_t pos, uint32_t flags){
    size_t ret=0;
    if(flags & FS_Relative) inst->pos+=pos;
	else if(flags & FS_Backwards){
		inst->pos = (current_mode->vidmode.height * current_mode->vidmode.width * 2) - pos;
	}else if(flags == (FS_Relative | FS_Backwards)) inst->pos-=pos;
    else inst->pos=pos;
    ret=inst->pos;
    return ret;
}

void text_poscursor(size_t row, size_t col){
    uint16_t position=(row*80) + col;

    write_crtc(CRTC_Registers::CursorLocLow, (unsigned char)(position&0xFF));
    write_crtc(CRTC_Registers::CursorLocHigh, (unsigned char )((position>>8)&0xFF));
}

void init_text(){
    for ( size_t y = 0; y < current_mode->vidmode.height; y++ )
    {
        for ( size_t x = 0; x < current_mode->vidmode.width; x++ )
        {
            const size_t index = y * current_mode->vidmode.width + x;
            ((uint16_t*)text_memory)[index] = (' ' | 0x0700);
        }
    }
}