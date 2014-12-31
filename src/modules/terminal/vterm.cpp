#include "vterm.hpp"
#include "module_stubs.h"
#include "terminal.hpp"
#include "keyboard.h"
#include "device.hpp"
#include "holdlock.hpp"

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
    init_lock(&term_lock);
    init_lock(&input_lock);
    input_top=0;
    input_count=0;
    refcount=0;
    scrollcount=0;
    sprintf(title, "BT/OS Terminal %i", (int)id);
    pointer_enabled=false;
}

vterm::~vterm(){
    backend->close(id);
    if(buffer) free(buffer);
}

void vterm::putchar(char c){
    if(!vidmode.textmode) return;
    if(c == '\n') {
        bufpos=(((bufpos/(vidmode.width*2))+1) * (vidmode.width*2));
        if(backend->is_active(id)) backend->display_write(1, &c);
    }else if(c == 0x08){
        if(bufpos >= 2) {
            bufpos -= 2;
            buffer[bufpos++] = ' ';
            buffer[bufpos++] = textcolour;
            bufpos -= 2;
        }
        if(backend->is_active(id)) {
            size_t cpos = backend->display_seek(0, true);
            cpos--;
            backend->display_seek(cpos, false);
            char s = ' ';
            backend->display_write(1, &s);
            backend->display_seek(cpos, false);
        }
    } else {
        buffer[bufpos++]=(uint8_t)c;
        buffer[bufpos++]=textcolour;
        if(backend->is_active(id)) backend->display_write(1, &c);
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

void vterm::setcolours(uint8_t c) {
    textcolour=c;
    backend->display_ioctl(bt_vid_ioctl::SetTextColours, sizeof(c), (char*)&c);
}

uint8_t vterm::getcolours() {
    return textcolour;
}

void vterm::scroll(){
    int factor=1;
    if(vidmode.textmode) factor=2;
    for(size_t y=0; y<vidmode.height; ++y){
        for(size_t x=0; x<(vidmode.width*factor); ++x){
            const size_t source = y * (vidmode.width*factor) + x;
            if(y){
                const size_t dest = (y-1) * (vidmode.width*factor) + x;
                buffer[dest]=buffer[source];
            }
            buffer[source]=0;
            if(vidmode.textmode && source % 2) buffer[source]=textcolour;
        }
    }
    bufpos=((vidmode.height-1)*vidmode.width)*factor;
    scrollcount++;
}

void vterm::do_infoline(){
    vterm_options opts;
    if(backend->is_active(id) && infoline && vidmode.textmode){
        size_t pos=seek(opts, 0, true);
        seek(opts, 0, false);
        uint16_t linecol=0x1F;
        uint16_t colour=(uint16_t) backend->display_ioctl(bt_vid_ioctl::GetTextColours, 0, NULL);
        setcolours(linecol);
        for(size_t i=0; i<vidmode.width; ++i){
            putchar(' ');
        }
        seek(opts, 0, false);
        char buf[8];
        sprintf(buf, "[%i:%i] ", (int)terminals->get_count(), (int)id);
        putstring(buf);
        putstring(title);
        setcolours(colour);
        seek(opts, pos, false);
    }
}

uint64_t vterm::get_id() {
    hold_lock hl(&term_lock, false);
    return id;
}

const char *vterm::get_title(){
    hold_lock hl(&term_lock);
    return title;
}

void vterm::activate() {
    hold_lock hl(&term_lock, false);
    bool scroll=false;
    backend->display_ioctl(bt_vid_ioctl::SetMode, sizeof(vidmode), (char*)&vidmode);
    backend->set_active(id);
    backend->display_ioctl(bt_vid_ioctl::SetScrolling, sizeof(bool), (char*)&scroll);
    if(vidmode.textmode) {
        bt_vid_text_access_mode::Enum textmode=bt_vid_text_access_mode::Raw;
        backend->display_ioctl(bt_vid_ioctl::SetTextAccessMode, sizeof(textmode), (char*)&textmode);
        setcolours(getcolours());
    }
    backend->display_seek(0, false);
    backend->display_write(bufsize, (char*)buffer);
    if(vidmode.textmode) {
        bt_vid_text_access_mode::Enum textmode=bt_vid_text_access_mode::Simple;
        backend->display_ioctl(bt_vid_ioctl::SetTextAccessMode, sizeof(textmode), (char*)&textmode);
    }
    backend->display_seek(bufpos/2, false);
    backend->display_ioctl(bt_vid_ioctl::SetScrolling, sizeof(bool), (char*)&scrolling);
    do_infoline();
    if(infoline && bufpos==0) putchar('\n');
    if(pointer_enabled){
        backend->show_pointer();
    }else{
        backend->hide_pointer();
    }
}

void vterm::deactivate() {
}

size_t vterm::write(vterm_options &/*opts*/, size_t size, char *buf) {
    hold_lock hl(&term_lock);
    curpid=getpid();
    bool iline_valid=infoline && vidmode.textmode;
    if(bufpos <= vidmode.width) iline_valid=false;
    if(bufpos+size > bufsize) size = bufsize - bufpos;
    if(vidmode.textmode){
        uint64_t scount=scrollcount;
        for(size_t i=0; i<size; ++i) putchar(buf[i]);
        if(scount != scrollcount) iline_valid=false;
    }else {
        memcpy(buffer + bufpos, buf, size);
        bufpos += size;
        if (backend->is_active(id)) {
            backend->display_write(size, buf);
        }
    }
    if(!iline_valid) do_infoline();
    return size;
}

size_t vterm::read(vterm_options &opts, size_t size, char *buf) {
    hold_lock hl(&term_lock);
    curpid=getpid();
    if (opts.mode == bt_terminal_mode::Terminal || opts.mode == bt_terminal_mode::Keyboard) {
        int incr;
        for(size_t i=0; i<size; i+=incr) {
            incr=1;
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
    hold_lock hl(&term_lock, false);
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
    hold_lock hl(&term_lock);
    curpid=getpid();
    if(fn==bt_terminal_ioctl::SetTitle){
        memset(title, 0, titlemax);
        memcpy(title, buf, size);
        do_infoline();
    }else if(fn==bt_vid_ioctl::ClearScreen){
        clear_buffer();
        seek(opts, 0, false);
        if(backend->is_active(id)){
            backend->display_ioctl(fn, size, buf);
        }
        if(infoline) {
            putchar('\n');
            do_infoline();
        }
    }else if(fn == bt_terminal_ioctl::SetEcho){
        if(size) echo=*(bool*)buf;
    }else if(fn == bt_terminal_ioctl::SetMode){
        opts.mode=*(bt_terminal_mode::Enum*)buf;
    }else if(fn == bt_terminal_ioctl::NewTerminal){
        create_terminal(buf);
    }else if(fn == bt_terminal_ioctl::SwtichTerminal){
        uint64_t sw_id=*(uint64_t*)buf;
        terminals->switch_terminal(sw_id);
    }else if(fn == bt_vid_ioctl::GetModeCount){
        return backend->display_ioctl(fn, size, buf);
    }else if(fn == bt_vid_ioctl::GetMode) {
        return backend->display_ioctl(fn, size, buf);
    }else if(fn == bt_vid_ioctl::SetMode){
        if(size==sizeof(bt_vidmode)){
            if(backend->is_active(id)){
                backend->display_ioctl(fn, size, buf);
            }
            vidmode=*(bt_vidmode*)buf;
            allocate_buffer();
            clear_buffer();
        }
    }else if(fn == bt_vid_ioctl::QueryMode){
        if(size==sizeof(bt_vidmode)){
            bt_vidmode *mode=(bt_vidmode*)buf;
            *mode=vidmode;
            return size;
        }
    }else if(fn == bt_vid_ioctl::SetTextColours){
        if(size==sizeof(uint8_t)){
            setcolours(*(uint8_t*)buf);
            dbgpf("VTERM: colours: %x\n", *(uint8_t*)buf);
        }
    }else if(fn == bt_vid_ioctl::GetTextColours){
        return getcolours();
    }else if(fn == bt_vid_ioctl::GetScrolling){
        return scrolling;
    }else if(fn == bt_vid_ioctl::SetScrolling){
        if(size==sizeof(bool)){
            scrolling=*(bool*)buf;
            if(backend->is_active(id)){
                backend->display_ioctl(fn, size, buf);
            }
        }
    }else if(fn == bt_terminal_ioctl::ShowPointer){
        backend->show_pointer();
        pointer_enabled=true;
    }else if(fn == bt_terminal_ioctl::HidePointer){
        backend->hide_pointer();
        pointer_enabled=false;
    }else if(fn == bt_terminal_ioctl::GetPointerInfo){
        if(size==sizeof(bt_terminal_pointer_info)){
            *(bt_terminal_pointer_info*)buf=backend->get_pointer_info();
        }
    }
    //TODO: implement more
    return 0;
}

void vterm::create_terminal(char *command) {
    uint64_t new_id=terminals->create_terminal(backend);
    dbgpf("TERM: Created new terminal %i.\n", (int) new_id);
    terminals->get(new_id)->sync(false);
    terminals->switch_terminal(new_id);
    if(command){
        char old_terminal_id[128]="0";
        strncpy(old_terminal_id, getenv(terminal_var, getpid()), 128);
        char new_terminal_id[128]={0};
        i64toa(new_id, new_terminal_id, 10);
        setenv(terminal_var, new_terminal_id, 0, getpid());
        pid_t pid=spawn(command, 0, NULL);
        setenv(terminal_var, old_terminal_id, 0, getpid());
        if(!pid) terminals->get(new_id)->close();
    }
}

void vterm::open(){
    hold_lock hl(&term_lock);
    refcount++;
}

void vterm::close(){
    take_lock(&term_lock);
    if(refcount) refcount--;
    if(!refcount){
        if(terminals->get_count() > 1){
            release_lock(&term_lock);
            terminals->delete_terminal(id);
            return;
        }
    }
    release_lock(&term_lock);
}

void vterm::sync(bool content) {
    hold_lock hl(&term_lock);
    backend->display_ioctl(bt_vid_ioctl::GetMode, sizeof(vidmode), (char*)&vidmode);
    allocate_buffer();
    if(content) {
        size_t vpos = this->backend->display_seek(0, true);
        this->backend->display_seek(0, false);
        if (this->vidmode.textmode) {
            bt_vid_text_access_mode::Enum textmode = bt_vid_text_access_mode::Raw;
            this->backend->display_ioctl(bt_vid_ioctl::SetTextAccessMode, sizeof(textmode), (char *) &textmode);
            this->backend->display_ioctl(bt_vid_ioctl::GetTextColours, sizeof(this->textcolour), (char *) &this->textcolour);
        }
        this->backend->display_read(this->bufsize, (char *) this->buffer);
        if (this->vidmode.textmode) {
            bt_vid_text_access_mode::Enum textmode = bt_vid_text_access_mode::Simple;
            this->backend->display_ioctl(bt_vid_ioctl::SetTextAccessMode, sizeof(textmode), (char *) &textmode);
        }
        this->backend->display_seek(vpos, false);
        this->bufpos = this->backend->display_seek(0, true);
        if (this->vidmode.textmode) {
            this->bufpos *= 2;
        }
    }else{
        clear_buffer();
    }
    this->scrolling =(bool) this->backend->display_ioctl(bt_vid_ioctl::GetScrolling, 0, NULL);
}

void vterm::clear_buffer() {
    memset(buffer, 0, bufsize);
    if(vidmode.textmode) {
            for (size_t i = 1; i < bufsize; i += 2) {
                buffer[i] = textcolour;
            }
        }
    bufpos = 0;
}

void vterm::allocate_buffer() {
    if(vidmode.textmode){
        bufsize =(vidmode.width * vidmode.height) * (((vidmode.bpp * 2) / 8) + 1);
    }else{
        bufsize =(vidmode.width * vidmode.height) * (vidmode.bpp / 8);
    }
    if(buffer) {
        free(buffer);
        buffer =NULL;
    }
    buffer=(uint8_t*)malloc(bufsize);
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
		int start=input_top-input_count;
		if(start<0) start+=input_size;
        ret=input_buffer[start];
        input_count--;
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
    init_lock(&vtl_lock);
}

uint64_t vterm_list::create_terminal(i_backend *back) {
    hold_lock hl(&vtl_lock);
    uint64_t new_id=++id;
    vterm *newterm=new vterm(new_id, back);
    vterm **terms=new vterm*[count+1];
    memcpy(terms, terminals, count*sizeof(vterm*));
    free(terminals);
    terminals=terms;
    terminals[count]=newterm;
    count++;
    return new_id;
}

void vterm_list::delete_terminal(uint64_t id) {
    hold_lock hl(&vtl_lock);
    if(id==default_terminal) default_terminal=0;
    bool switchterm=false;
    if(current_vterm->get_id() == id){
        switchterm=true;
        current_vterm->deactivate();
    }
    vterm *term=NULL;
    for(size_t i=0; i<count; ++i){
        if(terminals[i]->get_id() == id){
            term=terminals[i];
            vterm **terms=new vterm*[count-1];
            for(size_t j=0; j<i; ++j){
                terms[j]=terminals[j];
            }
            for(size_t j=i+1; j<count; ++j){
                terms[j-1]=terminals[j];
            }
            free(terminals);
            terminals=terms;
            count--;
        }else if(switchterm){
            current_vterm=terminals[i];
            current_vterm->activate();
            switchterm=false;
        }
        if(term) delete term;
    }
}

void vterm_list::switch_terminal(uint64_t id) {
    hold_lock hl(&vtl_lock);
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
    hold_lock hl(&vtl_lock);
    if(!id) id=default_terminal;
    for(size_t i=0; i<count; ++i) {
        if (!id || terminals[i]->get_id() == id) {
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
