#include "vterm.hpp"
#include "module_stubs.h"
#include "terminal.hpp"
#include "keyboard.h"

vterm *current_vterm=NULL;
vterm_list *terminals=NULL;

extern lock term_lock;

size_t strlen(const char* str)
{
    size_t ret = 0;
    while ( str[ret] != 0 )
        ret++;
    return ret;
}

vterm::vterm(uint64_t nid){
    id=nid;
    buffer=NULL;
    bufsize=0;
    bufpos=0;
    scrolling=true;
    infoline=true;
    mode=bt_terminal_mode::Terminal;
    sprintf(title, "BT/OS Terminal %i", (int)id);
}

vterm::~vterm(){
    if(buffer) free(buffer);
}

bool active_blockcheck(void *p) {
    return *(bool*)p;
}

void vterm::wait_until_active() {
    if(!active) {
        thread_setblock(&active_blockcheck, (void*)&active);
    }
}

void vterm::putchar(char c){
    if(c != '\n'){
        buffer[bufpos++]=(uint8_t)c;
    }else{
        bufpos=((bufpos/vidmode.width)+1) * vidmode.width;
    }
    if(bufpos>=bufsize){
        scroll();
    }
    if(active) fwrite(video_device_handle, 1, &c);
}

void vterm::putstring(char *s){
    for(size_t i=0; i<strlen(s); ++i){
        putchar(s[i]);
    }
}

void vterm::scroll(){
    for(size_t y=0; y<vidmode.height; ++y){
        for(size_t x=0; x<vidmode.width; ++x){
            const size_t source = y * vidmode.width + x;
            if(y){
                const size_t dest = (y-1) * vidmode.width + x;
                buffer[dest]=buffer[source];
            }
            buffer[source]=' ';
        }
    }
    bufpos=(vidmode.height-1)*vidmode.width;
}

void vterm::do_infoline(){
    if(active && infoline && vidmode.textmode){
        size_t pos=seek(0, true);
        seek(0, false);
        uint16_t linecol=0x1F;
        uint16_t colour=(uint16_t)fioctl(video_device_handle, bt_vid_ioctl::GetTextColours, 0, NULL);
        fioctl(video_device_handle, bt_vid_ioctl::SetTextColours, sizeof(linecol), (char*)&linecol);
        for(size_t i=0; i<vidmode.width; ++i){
            putchar(' ');
        }
        seek(0, false);
        putstring(title);
        fioctl(video_device_handle, bt_vid_ioctl::SetTextColours, sizeof(colour), (char*)&colour);
        seek(pos, false);
    }
}

uint64_t vterm::get_id() {
    return id;
}

void vterm::activate() {
    bool scroll=false;
    fioctl(video_device_handle, bt_vid_ioctl::SetScrolling, sizeof(bool), (char*)&scroll);
    fseek(video_device_handle, 0, false);
    fwrite(video_device_handle, bufsize, (char*)buffer);
    fseek(video_device_handle, bufpos, false);
    fioctl(video_device_handle, bt_vid_ioctl::SetScrolling, sizeof(bool), (char*)&scrolling);
    active=true;
    do_infoline();
}

void vterm::deactivate() {
    active=false;
}

size_t vterm::write(size_t size, char *buf) {
    curpid=getpid();
    if(bufpos+size > bufsize) size=bufsize-bufpos;
    if(vidmode.textmode){
        for(size_t i=0; i<size; ++i) putchar(buf[i]);
    }else {
        memcpy(buffer + bufpos, buf, size);
        bufpos += size;
        if (active) {
            fwrite(video_device_handle, size, buf);
        }
    }
    do_infoline();
    return size;
}

size_t vterm::read(size_t size, char *buf) {
    curpid=getpid();
    if (mode == bt_terminal_mode::Terminal || mode == bt_terminal_mode::Keyboard) {
        for(size_t i=0; i<size; ++i) {
            wait_until_active();
            uint32_t input=0;
            char c=0;
            while(!input || !c) {
                fread(input_device_handle, sizeof(input), (char *) &input);
                if ((input & KeyFlags::Control) && !(input & KeyFlags::KeyUp) && ((char) input == 'c' || (char) input == 'C')) {
                    release_lock(&term_lock);
                    kill(getpid());
                }
                c = KB_char(input);
            }
            buf[i] = c;
        }
        return size;
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
    curpid=getpid();
    if(relative) bufpos+=pos;
    else bufpos=pos;
    if(bufpos>bufsize) bufpos=bufsize;
    if(active){
        fseek(video_device_handle, pos, relative);
    }
    return bufpos;
}

int vterm::ioctl(int /*fn*/, size_t /*size*/, char */*buf*/) {
    curpid=getpid();
    //TODO: implement
    return 0;
}

void vterm::sync() {
    fioctl(video_device_handle, bt_vid_ioctl::GetMode, sizeof(vidmode), (char*)&vidmode);
    if(vidmode.textmode){
        bufsize=(vidmode.width * vidmode.height) * (((vidmode.bpp /** 2*/) / 8) + 1);
    }else{
        bufsize=(vidmode.width * vidmode.height) * (vidmode.bpp / 8);
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
    id=0;
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
