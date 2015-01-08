#include "ops.hpp"
#include "modes.hpp"
#include "device.hpp"

size_t graphics_read(vga_instance *inst, size_t bytes, char *buf){
    size_t pixpos=inst->pos;
    size_t pixcount=bytes;
    if(current_mode->vidmode.bpp == 4) {
        pixpos = inst->pos / 2;
        pixcount=bytes * 2;
    }
    size_t maxpix=current_mode->vidmode.width * current_mode->vidmode.height;
    size_t maxbytes=maxpix - inst->pos;
    if(bytes > maxpix) bytes=0;
    if(bytes > maxbytes) bytes=maxbytes;
    for(size_t i=pixpos; i<pixpos+pixcount; ++i){
        uint32_t y=(uint32_t)(pixpos / current_mode->vidmode.width);
        uint32_t x=(uint32_t)(pixpos - (current_mode->vidmode.width * y));
        uint8_t pix=current_mode->get_pixel(x, y);
        if(current_mode->vidmode.bpp == 4){
            bool high=!!(i % 2);
            size_t bufpos=(i-pixpos)/2;
            if(!high){
                buf[bufpos] = (char)((buf[bufpos] & 0xF0) | (pix & 0x0F));
            }else{
                buf[bufpos] = (char)((buf[bufpos] & 0x0F) | ((pix << 4) & 0xF0));
            }
        }else{
            buf[i-pixpos]=(char)pix;
        }
    }
    inst->pos+=bytes;
    return bytes;
}

size_t graphics_write(vga_instance *inst, size_t bytes, char *buf){
    size_t pixpos=inst->pos;
    size_t pixcount=bytes;
    size_t maxpix=current_mode->vidmode.width * current_mode->vidmode.height;
    size_t maxbytes=maxpix - inst->pos;
    if(bytes > maxpix) bytes=0;
    if(bytes > maxbytes) bytes=maxbytes;
    if(current_mode->vidmode.bpp == 4) {
        pixpos = inst->pos / 2;
        pixcount=bytes * 2;
    }
    for(size_t i=pixpos; i<pixpos+pixcount; ++i){
        uint32_t y=(uint32_t)(pixpos / current_mode->vidmode.width);
        uint32_t x=(uint32_t)(pixpos - (current_mode->vidmode.width * y));
        uint8_t pix;
        if(current_mode->vidmode.bpp == 4){
            bool high=!!(i % 2);
            size_t bufpos=(i-pixpos)/2;
            if(!high){
                pix=(uint8_t)(buf[bufpos] & 0x0F);
            }else{
                pix=(uint8_t)((buf[bufpos] >> 4) & 0x0F);
            }
        }else{
            pix=buf[i-pixpos];
        }
        current_mode->put_pixel(x, y, pix);
    }
    inst->pos+=bytes;
    return bytes;
}

size_t graphics_seek(vga_instance *inst, size_t pos, bool relative){
    if(relative){
        inst->pos+=pos;
    }else{
        inst->pos=pos;
    }
    size_t maxpix=current_mode->vidmode.width * current_mode->vidmode.height;
    if(inst->pos > maxpix) inst->pos=maxpix;
    if(current_mode->vidmode.bpp == 4 && inst->pos > maxpix/2) inst->pos=maxpix/2;
    return inst->pos;
}
