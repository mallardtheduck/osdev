#include "vterm.hpp"
#include "module_stubs.h"
#include "terminal.hpp"

vterm *current_vterm=NULL;
vterm_list *terminals=NULL;

vterm::vterm(uint64_t nid){
    id=nid;
    buffer=NULL;
    bufpos=0;
    scrolling=true;
}

vterm::~vterm(){
    if(buffer) free(buffer);
}

uint64_t vterm::get_id() {
    return id;
}

bool active_blockcheck(void *p) {
    return *(bool*)p;
}

void vterm::wait_until_active() {
    if(!active) {
        thread_setblock(&active_blockcheck, (void*)&active);
    }
}

void vterm::activate() {
    bool scroll=false;
    fioctl(video_device_handle, bt_vid_ioctl::SetScrolling, sizeof(bool), (char*)&scroll);
    fseek(video_device_handle, 0, false);
    fwrite(video_device_handle, bufsize, (char*)buffer);
    fseek(video_device_handle, bufpos, false);
    fioctl(video_device_handle, bt_vid_ioctl::SetScrolling, sizeof(bool), (char*)&scrolling);
    active=true;
}

void vterm::deactivate() {
    active=false;
}

size_t vterm::write(size_t size, char *buf) {
    if(bufpos+size > bufsize) size=bufsize-bufpos;
    memcpy(buffer+bufpos, buf, size);
    bufpos+=size;
    if(active){
        fwrite(video_device_handle, size, buf);
    }
    return size;
}

size_t vterm::read(size_t size, char *buf) {
    if (mode == bt_terminal_mode::Terminal || mode == bt_terminal_mode::Keyboard) {
        if(!active) {
            wait_until_active();
            return fread(input_device_handle, size, buf);
        }
    } else if (mode == bt_terminal_mode::Video) {
        if (bufpos + size > bufsize) size = bufsize - bufpos;
        memcpy(buf, buffer + bufpos, size);
        bufpos += size;
        if (active) {
            fread(video_device_handle, size, buf);
        }
        return size;
    }
    return 0;
}

size_t vterm::seek(size_t pos, bool relative) {
    if(relative) bufpos+=pos;
    else bufpos=pos;
    if(bufpos>bufsize) bufpos=bufsize;
    if(active){
        fseek(video_device_handle, pos, relative);
    }
    return bufpos;
}

int vterm::ioctl(int /*fn*/, size_t /*size*/, char */*buf*/) {
    //TODO: implement
    return 0;
}

void vterm::sync() {
    bt_vidmode mode;
    fioctl(video_device_handle, bt_vid_ioctl::GetMode, sizeof(mode), (char*)&mode);
    if(mode.textmode){
        bufsize=(mode.width * mode.height) * ((mode.bpp * 2) / 8);
    }else{
        bufsize=(mode.width * mode.height) * (mode.bpp / 8);
    }
    if(buffer) {
        free(buffer);
        buffer=NULL;
    }
    buffer=(uint8_t*)malloc(bufsize);
    size_t vpos=fseek(video_device_handle, 0, true);
    fseek(video_device_handle, 0, false);
    fread(video_device_handle, bufsize, (char*)buffer);
    fseek(video_device_handle, vpos, false);
    bufpos=fseek(video_device_handle, 0, true);
    scrolling=(bool)fioctl(video_device_handle, bt_vid_ioctl::GetScrolling, 0, NULL);
}

vterm_list::vterm_list() {
    terminals=(vterm**)malloc(0);
    count=0;
}

uint64_t vterm_list::create_terminal() {
    vterm *newterm=new vterm(++id);
    vterm **terms=new vterm*[count+1];
    memcpy(terms, terminals, count*sizeof(vterm*));
    free(terminals);
    terminals=terms;
    terminals[count]=newterm;
    count++;
    return id;
}

void vterm_list::delete_terminal(uint64_t id) {
    for(size_t i=0; i<count; ++i){
        if(terminals[i]->get_id() == id){
            delete terminals[i];
            vterm **terms=new vterm*[count-1];
            memcpy(terms, terminals, i*sizeof(vterm*));
            memcpy(terms[i], terminals[i+1], count-(i+1));
            free(terminals);
            terminals=terms;
            count--;
            return;
        }
    }
}

void vterm_list::switch_terminal(uint64_t id) {
    for(size_t i=0; i<count; ++i){
        if(terminals[i]->get_id() == id){
            if(current_vterm) current_vterm->deactivate();
            current_vterm=terminals[i];
            current_vterm->activate();
            return;
        }
    }
}

vterm *vterm_list::get(uint64_t id) {
    for(size_t i=0; i<count; ++i) {
        if (terminals[i]->get_id() == id) {
            return terminals[i];
        }
    }
    return NULL;
}
