#include <btos_module.h>
#include <dev/video_dev.h>
#include <util/holdlock.hpp>
#include "vga.hpp"
#include "modes.hpp"
#include "device.hpp"
#include "ops.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"

extern vga_palette_entry vga_palette[256];
lock vga_device_lock;

bt_video_palette_entry get_palette_entry(uint8_t entry){
    bt_video_palette_entry ret;
    ret.index = entry;
    ret.r = vga_palette[entry].r << 2;
    ret.g = vga_palette[entry].g << 2;
    ret.b = vga_palette[entry].b << 2;
    ret.a=0xFF;
    return ret;
}

void *vga_open(void *id){
    vga_instance *inst=new vga_instance();
    inst->pos=0;
    inst->mode=bt_vid_text_access_mode::Simple;
    return (void*)inst;
}

bool vga_close(void *instance){
    if(instance) {
        delete (vga_instance *) instance;
        return true;
    }
    return false;
}

size_t vga_read(void *instance, size_t bytes, char *buf){
	hold_lock hl(&vga_device_lock, false);
    vga_instance *inst=(vga_instance*)instance;
    if(current_mode->vidmode.textmode){
        return text_read(inst, bytes, buf);
    }else{
        return graphics_read(inst, bytes, buf);
    }
}

size_t vga_write(void *instance, size_t bytes, char *buf){
	hold_lock hl(&vga_device_lock, false);
    vga_instance *inst=(vga_instance*)instance;
    if(current_mode->vidmode.textmode){
        return text_write(inst, bytes, buf);
    }else {
        return graphics_write(inst, bytes, buf);
    }
}

bt_filesize_t vga_seek(void *instance, bt_filesize_t pos, uint32_t flags){
	hold_lock hl(&vga_device_lock, false);
    vga_instance *inst=(vga_instance*)instance;
    if(current_mode->vidmode.textmode){
        return text_seek(inst, pos, flags);
    }else {
        return graphics_seek(inst, pos, flags);
    }
}

int vga_ioctl(void *instance, int fn, size_t bytes, char *buf){
	hold_lock hl(&vga_device_lock, false);
    vga_instance *inst=(vga_instance*)instance;
    if(fn == bt_vid_ioctl::GetModeCount) {
        return vga_mode_count;
    }
    else if(fn==bt_vid_ioctl::QueryMode) {
        if(bytes == sizeof(bt_vidmode)) {
            bt_vidmode &mode = current_mode->vidmode;
            memcpy(buf, &mode, max(bytes, sizeof(mode)));
            return bytes;
        }else return 0;
    }
    else if(fn==bt_vid_ioctl::GetMode) {
        if(bytes == sizeof(bt_vidmode)) {
            size_t index = *(size_t *) buf;
            if(index > vga_mode_count) return 0;
            bt_vidmode &mode = vga_modes[index]->vidmode;
            memcpy(buf, &mode, sizeof(mode));
            return bytes;
        }else return 0;
    }else if(fn==bt_vid_ioctl::SetMode) {
        if(bytes == sizeof(bt_vidmode)) {
			graphics_end();
            bt_vidmode vidmode = *(bt_vidmode *) buf;
            vga_mode *mode=NULL;
            for(size_t i=0; i<vga_mode_count; ++i){
                if(vga_modes[i]->vidmode.id == vidmode.id){
                    mode=vga_modes[i];
                    break;
                }
            }
            if(mode==NULL) return 0;
            current_mode = mode;
            mode->set_mode();
        }
        return 0;
    }else if(fn==bt_vid_ioctl::GetPaletteEntry) {
        if(bytes == sizeof(bt_video_palette_entry)){
            bt_video_palette_entry &entry=*(bt_video_palette_entry*)buf;
            entry= get_palette_entry((uint8_t)entry.index);
            return (int)entry.index;
        }
        return 0;
    }else{
        if(current_mode->vidmode.textmode){
            return text_ioctl(inst, fn, bytes, buf);
        }else{
            // return graphics_ioctl(inst, fn, bytes, buf);
            return 0;
        }
    }
}

int vga_type(){
    return driver_types::VIDEO;
}

char *vga_desc(){
    return "VGA video device";
}

drv_driver vga_device={&vga_open, &vga_close, &vga_read, &vga_write, &vga_seek, &vga_ioctl, &vga_type, &vga_desc};

void init_device(){
	init_lock(&vga_device_lock);
    add_device("VGA", &vga_device, NULL);
}
