#include "vga.hpp"
#include "modes.hpp"
#include "drivers.h"
#include "device.hpp"
#include "ops.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"

void *vga_open(void *id){
    return new vga_instance;
}

bool vga_close(void *instance){
    if(instance) {
        delete (vga_instance *) instance;
        return true;
    }
    return false;
}

size_t vga_read(void *instance, size_t bytes, char *buf){
    vga_instance *inst=(vga_instance*)instance;
    if(current_mode.vidmode.textmode){
        return text_read(inst, bytes, buf);
    }else{
        //return graphics_read(inst, bytes, buf);
        return 0;
    }
}

size_t vga_write(void *instance, size_t bytes, char *buf){
    vga_instance *inst=(vga_instance*)instance;
    if(current_mode.vidmode.textmode){
        return text_write(inst, bytes, buf);
    }else {
        //return graphics_write(inst, bytes, buf);
        return 0;
    }
}

size_t vga_seek(void *instance, size_t pos, bool relative){
    vga_instance *inst=(vga_instance*)instance;
    if(current_mode.vidmode.textmode){
        return text_seek(inst, pos, relative);
    }else {
        //return graphics_seek(inst, pos, relative);
        return 0;
    }
}

int vga_ioctl(void *instance, int fn, size_t bytes, char *buf){
    vga_instance *inst=(vga_instance*)instance;
    if(fn == bt_vid_ioctl::GetModeCount) {
        return vga_mode_count;
    }
    else if(fn==bt_vid_ioctl::QueryMode) {
        bt_vidmode &mode = current_mode.vidmode;
        memcpy(buf, &mode, max(bytes, sizeof(mode)));
        return max(bytes, sizeof(mode));
    }
    else if(fn==bt_vid_ioctl::GetMode) {
        if(bytes >= sizeof(size_t)) {
            size_t index = *(size_t *) buf;
            bt_vidmode &mode = vga_modes[index].vidmode;
            memcpy(buf, &mode, max(bytes, sizeof(mode)));
            return max(bytes, sizeof(mode));
        }else return 0;
    }else if(fn==bt_vid_ioctl::SetMode) {
        return 0;
    }else{
        if(current_mode.vidmode.textmode){
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
    return "VGA video device.";
}

drv_driver vga_device={&vga_open, &vga_close, &vga_read, &vga_write, &vga_seek, &vga_ioctl, &vga_type, &vga_desc};

void init_device(){
    add_device("VGA", &vga_device, NULL);
}
