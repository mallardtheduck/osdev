#include "ops.hpp"
#include "modes.hpp"
#include "device.hpp"

size_t graphics_read(vga_instance *inst, size_t bytes, char *buf){
    size_t maxpix=current_mode->vidmode.width * current_mode->vidmode.height;
    size_t maxbytes=maxpix - inst->pos;
    if(bytes > maxpix) bytes=0;
    if(bytes > maxbytes) bytes=maxbytes;
    size_t pixpos=inst->pos;
    size_t pixcount=bytes;
    if(current_mode->vidmode.bpp == 4) {
        pixpos = inst->pos * 2;
        pixcount=bytes * 2;
    }
    current_mode->read_pixels(pixpos, pixcount, (uint8_t*)buf);
    inst->pos+=bytes;
    return bytes;
}

size_t graphics_write(vga_instance *inst, size_t bytes, char *buf){
    size_t maxpix=current_mode->vidmode.width * current_mode->vidmode.height;
    size_t maxbytes=maxpix - inst->pos;
    if(bytes > maxpix) bytes=0;
    if(bytes > maxbytes) bytes=maxbytes;
    size_t pixpos=inst->pos;
    size_t pixcount=bytes;
    if(current_mode->vidmode.bpp == 4) {
        pixpos = inst->pos * 2;
        pixcount=bytes * 2;
    }
    current_mode->write_pixels(pixpos, pixcount, (uint8_t*)buf);
    inst->pos+=bytes;
    return bytes;
}

size_t graphics_seek(vga_instance *inst, size_t pos, uint32_t flags){
	size_t maxpix=current_mode->vidmode.width * current_mode->vidmode.height;
    if(flags & FS_Relative){
        inst->pos+=pos;
	}else if(flags & FS_Backwards){
		inst->pos=maxpix - pos;
	}else if(flags == (FS_Relative | FS_Backwards)){
		inst->pos-=pos;
    }else{
        inst->pos=pos;
    }
    if(inst->pos > maxpix) inst->pos=maxpix;
    if(current_mode->vidmode.bpp == 4 && inst->pos > maxpix/2) inst->pos=maxpix/2;
    return inst->pos;
}
