#include "vterm.hpp"
#include "module_stubs.h"
#include "drivers.h"
#include "holdlock.hpp"

lock term_lock;

const char *terminal_var="TERMID";

struct term_instance{
    vterm *terminal;
    vterm_options opts;
};

uint64_t atoi64(char *str) {
    uint64_t res = 0;
    for (int i = 0; str[i] != '\0'; ++i) res = res*10 + str[i] - '0';

    return res;
}

void reverse(char str[], int length) {
    int start = 0;
    int end = length -1;
    while (start < end) {
        char tmp=*(str+start);
        *(str+start)=*(str+end);
        *(str+end)=tmp;
        start++;
        end--;
    }
}

char* i64toa(uint64_t num, char* str, int base){
    int i = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    while (num != 0) {
        uint64_t rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    str[i] = '\0';
    reverse(str, i);
    return str;
}

void *term_open(void */*id*/){
    hold_lock hl(&term_lock);
    term_instance *ret=new term_instance();
    uint64_t termid=0;
    if(getenv(terminal_var, getpid())){
        termid=atoi64(getenv(terminal_var, getpid()));
    }
    ret->terminal=terminals->get(termid);
    ret->terminal->open();
    char termidvalue[128]={0};
    i64toa(ret->terminal->get_id(), termidvalue, 10);
    setenv(terminal_var, termidvalue, 0, 0);
    return ret;
}

bool term_close(void *instance){
    if(instance){
        term_instance *inst=(term_instance*)instance;
        inst->terminal->close();
        delete inst;
        return true;
    }
    return false;
}

size_t term_read(void *instance, size_t bytes, char *buf){
    if(instance) {
        term_instance *inst=(term_instance*)instance;
        return inst->terminal->read(inst->opts, bytes, buf);
    }
    return 0;
}

size_t term_write(void *instance, size_t bytes, char *buf){
    if(instance) {
        term_instance *inst=(term_instance*)instance;
        return inst->terminal->write(inst->opts, bytes, buf);
    }
    return 0;
}

size_t term_seek(void *instance, size_t pos, bool relative){
    if(instance) {
        hold_lock hl(&term_lock);
        term_instance *inst=(term_instance*)instance;
        return inst->terminal->seek(inst->opts, pos, relative);
    }
    return 0;
}

int term_ioctl(void *instance, int fn, size_t bytes, char *buf){
    if(instance) {
        term_instance *inst=(term_instance*)instance;
        return inst->terminal->ioctl(inst->opts, fn, bytes, buf);
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
    init_lock(&term_lock);
    char devname[BT_MAX_PATH]="DEV:/TERM";
    add_device(&devname[5], &term_driver, NULL);
    setenv("STDOUT", devname, 0, 0);
    setenv("STDIN", devname, 0, 0);
    setenv("STDERR", devname, 0, 0);
    setenv(terminal_var, "0", 0 ,0);
}
