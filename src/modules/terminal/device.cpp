#include "vterm.hpp"
#include "module_stubs.h"
#include "drivers.h"

struct term_instance{
    vterm *terminal;
};

void *term_open(void */*id*/){
    term_instance *ret=new term_instance();
    ret->terminal=current_vterm;
    return ret;
}

bool term_close(void *instance){
    if(instance){
        delete (term_instance*)instance;
        return true;
    }
    return false;
}

size_t term_read(void *instance, size_t bytes, char *buf){
    if(instance) {
        term_instance *inst=(term_instance*)instance;
        return inst->terminal->read(bytes, buf);
    }
    return 0;
}

size_t term_write(void *instance, size_t bytes, char *buf){
    if(instance) {
        term_instance *inst=(term_instance*)instance;
        return inst->terminal->write(bytes, buf);
    }
    return 0;
}

size_t term_seek(void *instance, size_t pos, bool relative){
    if(instance) {
        term_instance *inst=(term_instance*)instance;
        return inst->terminal->seek(pos, relative);
    }
    return 0;
}

int term_ioctl(void *instance, int fn, size_t bytes, char *buf){
    if(instance) {
        term_instance *inst=(term_instance*)instance;
        return inst->terminal->ioctl(fn, bytes, buf);
    }
    return 0;
}

int term_type(){
    return driver_types::TERMINAL;
}

char *term_desc(){
    return (char*)"Terminal device.";
}

drv_driver term_driver={&term_open, &term_close, &term_read, &term_write, &term_seek, &term_ioctl, &term_type, &term_desc};

void init_device(){
    char devname[BT_MAX_PATH]="DEV:/TERMINAL";
    add_device(&devname[5], &term_driver, NULL);
    setenv("STDOUT", devname, 0, 0);
}
