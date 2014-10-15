#include "vterm.hpp"
#include "module_stubs.h"
#include "terminal.hpp"
#include "keyboard.h"
#include "device.hpp"

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

vterm::vterm(uint64_t nid, i_backend *back){
    backend=back;
    id=nid;
    buffer=NULL;
    bufsize=0;
    bufpos=0;
    scrolling=true;
    infoline=true;
    textcolour=0x07;
    echo=true;
    init_lock(&input_lock);
    input_top=0;
    input_count=0;
    sprintf(title, "BT/OS Terminal %i", (int)id);
}

vterm::~vterm(){
    if(buffer) free(buffer);
}

bool active_blockcheck(void */*p*/) {
    //FIXME: Return correct answer
    return true;
}

void vterm::wait_until_active() {
    if(!backend->is_active(id)) {
        thread_setblock(&active_blockcheck, (void*)&backend);
    }
}

void vterm::putchar(char c){
    if(!vidmode.textmode) return;
    if(c != '\n' && c != 0x08){
        buffer[bufpos++]=textcolour;
        buffer[bufpos++]=(uint8_t)c;
        if(backend->is_active(id)) backend->display_write(1, &c);
    }else if(c == '\n') {
        bufpos=(((bufpos/(vidmode.width*2))+1) * (vidmode.width*2));
        if(backend->is_active(id)) backend->display_write(1, &c);
    }else if(c == 0x08){
        if(bufpos >= 2) {
            bufpos -= 2;
            buffer[bufpos++]=textcolour;
            buffer[bufpos++] = ' ';
        }
        size_t cpos=backend->display_seek(0, true);
        cpos--;
        backend->display_seek(cpos, false);
        char s=' ';
        backend->display_write(1, &s);
        backend->display_seek(cpos, false);

    }
    if(bufpos>=bufsize){
        scroll();
    }
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
            buffer[source]=0;
        }
    }
    bufpos=((vidmode.height-1)*vidmode.width)*2;
}

void vterm::do_infoline(){
    vterm_options opts;
    if(backend->is_active(id) && infoline && vidmode.textmode){
        size_t pos=seek(opts, 0, true);
        seek(opts, 0, false);
        uint16_t linecol=0x1F;
        uint16_t colour=(uint16_t) backend->display_ioctl(bt_vid_ioctl::GetTextColours, 0, NULL);
        backend->display_ioctl(bt_vid_ioctl::SetTextColours, sizeof(linecol), (char*)&linecol);
        for(size_t i=0; i<vidmode.width; ++i){
            putchar(' ');
        }
        seek(opts, 0, false);
        char buf[8];
        sprintf(buf, "[%i:%i] ", terminals->get_count(), (int)id);
        putstring(buf);
        putstring(title);
        backend->display_ioctl(bt_vid_ioctl::SetTextColours, sizeof(colour), (char*)&colour);
        seek(opts, pos, false);
    }
}

uint64_t vterm::get_id() {
    return id;
}

const char *vterm::get_title(){
    return title;
}

void vterm::activate() {
    bool scroll=false;
    backend->set_active(id);
    backend->display_ioctl(bt_vid_ioctl::SetScrolling, sizeof(bool), (char*)&scroll);
    backend->display_seek(0, false);
    if(vidmode.textmode) {
        bt_vid_text_access_mode::Enum textmode=bt_vid_text_access_mode::Raw;
        backend->display_ioctl(bt_vid_ioctl::SetTextAccessMode, sizeof(textmode), (char*)&textmode);
        backend->display_ioctl(bt_vid_ioctl::SetTextColours, sizeof(textcolour), (char*)&textcolour);
    }
    backend->display_write(bufsize, (char*)buffer);
    if(vidmode.textmode) {
        bt_vid_text_access_mode::Enum textmode=bt_vid_text_access_mode::Simple;
        backend->display_ioctl(bt_vid_ioctl::SetTextAccessMode, sizeof(textmode), (char*)&textmode);
    }
    backend->display_seek(bufpos, false);
    backend->display_ioctl(bt_vid_ioctl::SetScrolling, sizeof(bool), (char*)&scrolling);
    do_infoline();
}

void vterm::deactivate() {
    //active=false;
}

size_t vterm::write(vterm_options &/*opts*/, size_t size, char *buf) {
    curpid=getpid();
    if(bufpos+size > bufsize) size=bufsize-bufpos;
    if(vidmode.textmode){
        for(size_t i=0; i<size; ++i) putchar(buf[i]);
    }else {
        memcpy(buffer + bufpos, buf, size);
        bufpos += size;
        if (backend->is_active(id)) {
            backend->display_write(size, buf);
        }
    }
    do_infoline();
    return size;
}

size_t vterm::read(vterm_options &opts, size_t size, char *buf) {
    curpid=getpid();
    if (opts.mode == bt_terminal_mode::Terminal || opts.mode == bt_terminal_mode::Keyboard) {
        int incr;
        for(size_t i=0; i<size; i+=incr) {
            incr=1;
            wait_until_active();
            uint32_t input = 0;
            char c = 0;
            while (!input || !c) {
                release_lock(&term_lock);
                input=get_input();
                take_lock(&term_lock);
                if ((input & KeyFlags::Control) && !(input & KeyFlags::KeyUp) && ((char) input == 'c' || (char) input == 'C')) {
                    release_lock(&term_lock);
                    kill(getpid());
                }
                c = KB_char(input);
            }
            buf[i] = c;
            if (opts.mode == bt_terminal_mode::Terminal) {
                bool put=true;
                if (c == 0x08){
                    if(i) {
                        --i;
                        buf[i] = '\0';
                    }else put=false;
                    incr=0;
                }
                if (c == '\n') {
                    if(echo) putchar(c);
                    return i + 1;
                }
                if (echo && put) putchar(c);
            }
        }
        return size;
    } else if (opts.mode == bt_terminal_mode::Video) {
        if (bufpos + size > bufsize) size = bufsize - bufpos;
        memcpy(buf, buffer + bufpos, size);
        bufpos += size;
        if (backend->is_active(id)) {
            backend->display_read(size, buf);
        }
        return size;
    }
    return 0;
}

size_t vterm::seek(vterm_options &/*opts*/, size_t pos, bool relative) {
    curpid=getpid();
    int factor=1;
    if(vidmode.textmode) factor=2;
    if(relative) bufpos+=pos*factor;
    else bufpos=pos*factor;
    if(bufpos>bufsize) bufpos=bufsize;
    if(backend->is_active(id)){
        backend->display_seek(pos, relative);
    }
    return bufpos/factor;
}

int vterm::ioctl(vterm_options &opts, int fn, size_t size, char *buf) {
    curpid=getpid();
    if(fn==bt_terminal_ioctl::SetTitle){
        memset(title, 0, titlemax);
        memcpy(title, buf, size);
        do_infoline();
    }else if(fn==bt_vid_ioctl::ClearScreen){
        memset(buffer, 0, bufsize);
        seek(opts, 0, false);
        if(backend->is_active(id)){
            backend->display_ioctl(fn, size, buf);
        }
        if(infoline) putchar('\n');
    }else if(fn == bt_terminal_ioctl::SetEcho){
        if(size) echo=*(bool*)buf;
    }else if(fn == bt_terminal_ioctl::SetMode){
        opts.mode=*(bt_terminal_mode::Enum*)buf;
    }
    //TODO: implement more
    return 0;
}

void vterm::sync() {
    backend->display_ioctl(bt_vid_ioctl::GetMode, sizeof(vidmode), (char*)&vidmode);
    if(vidmode.textmode){
        bufsize=(vidmode.width * vidmode.height) * (((vidmode.bpp * 2) / 8) + 1);
    }else{
        bufsize=(vidmode.width * vidmode.height) * (vidmode.bpp / 8);
    }
    if(buffer) {
        free(buffer);
        buffer=NULL;
    }
    buffer=(uint8_t*)malloc(bufsize);
    size_t vpos=backend->display_seek(0, true);
    backend->display_seek(0, false);
    if(vidmode.textmode) {
        bt_vid_text_access_mode::Enum textmode=bt_vid_text_access_mode::Raw;
        backend->display_ioctl(bt_vid_ioctl::SetTextAccessMode, sizeof(textmode), (char*)&textmode);
        backend->display_ioctl(bt_vid_ioctl::GetTextColours, sizeof(textcolour), (char*)&textcolour);
    }
    backend->display_read(bufsize, (char*)buffer);
    if(vidmode.textmode) {
        bt_vid_text_access_mode::Enum textmode=bt_vid_text_access_mode::Simple;
        backend->display_ioctl(bt_vid_ioctl::SetTextAccessMode, sizeof(textmode), (char*)&textmode);
    }
    backend->display_seek(vpos, false);
    bufpos=backend->display_seek(0, true);
    if(vidmode.textmode){
        bufpos*=2;
    }
    scrolling=(bool)backend->display_ioctl(bt_vid_ioctl::GetScrolling, 0, NULL);
}

void vterm::queue_input(uint32_t code) {
    take_lock(&input_lock);
    if ((code & KeyFlags::Control) && !(code & KeyFlags::KeyUp) && ((char) code == 'c' || (char) code == 'C')) {
        release_lock(&input_lock);
        kill(curpid);
        return;
    }
    if(input_count < input_size){
        input_count++;
        input_top++;
        if(input_top==input_size) input_top=0;
        input_buffer[input_top]=code;
    }
    release_lock(&input_lock);
}

bool input_blockcheck(void *p){
    vterm *v=(vterm*)p;
    return (bool)v->input_count;
}

uint32_t vterm::get_input() {
    bool lockok=false;
    while(!lockok) {
        while (!input_count) thread_setblock(&input_blockcheck, (void *) this);
        take_lock(&input_lock);
        if(!input_count) release_lock(&input_lock);
        else lockok=true;
    }
    uint32_t ret=0;
    if(input_count){
        ret=input_buffer[input_top];
        input_count--;
        if(input_top==0) input_top=input_count;
        input_top--;
    }
    release_lock(&input_lock);
    return ret;
}

char vterm::get_char(){
    return KB_char(get_input());
}

vterm_list::vterm_list() {
    terminals=(vterm**)malloc(0);
    count=0;
    id=0;
}

uint64_t vterm_list::create_terminal(i_backend *back) {
    vterm *newterm=new vterm(++id, back);
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

size_t vterm_list::get_count(){
    return count;
}

char *terms_infofs(){
    char *buffer=(char*)malloc(4096);
    vterm_list *t=terminals;
    memset(buffer, 0, 4096);
    sprintf(buffer, "# ID, title\n");
    for(size_t i=0; i<t->count; ++i){
        sprintf(&buffer[strlen(buffer)], "%i, \"%s\"\n", (int)t->terminals[i]->get_id(), t->terminals[i]->get_title());
    }
    return buffer;
}