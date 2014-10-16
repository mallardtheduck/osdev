#ifndef _VTERM_HPP
#define _VTERM_CPP

#include <stdint.h>
#include "module_api.h"
#include "video_dev.h"
#include "terminal.h"
#include "backend.hpp"

struct vterm_options{
    bt_terminal_mode::Enum mode;

    vterm_options() : mode(bt_terminal_mode::Terminal) {}
};

class vterm{
private:
    i_backend *backend;

    uint64_t id;
    uint8_t *buffer;
    size_t bufsize;
    size_t bufpos;
    bool scrolling;
    bool infoline;
    bt_vidmode vidmode;
    uint8_t textcolour;
    bool echo;

    static const size_t input_size=128;
    uint32_t input_buffer[input_size];
    size_t input_count, input_top;
    lock input_lock;

    pid_t curpid;

    void putchar(char c);
    void putstring(char *s);
    void scroll();
    void do_infoline();
    char get_char();
    uint32_t get_input();

    friend bool input_blockcheck(void *p);

    static const size_t titlemax=256;
    char title[titlemax];

public:
    vterm(uint64_t id, i_backend *back);
    ~vterm();

    uint64_t get_id();
    const char *get_title();

    void activate();
    void deactivate();

    size_t write(vterm_options &opts, size_t size, char *buf);
    size_t read(vterm_options &opts, size_t size, char *buf);
    size_t seek(vterm_options &opts, size_t pos, bool relative);
    int ioctl(vterm_options &opts, int fn, size_t size, char *buf);

    void queue_input(uint32_t code);

    void sync(bool content=true);
};

extern vterm *current_vterm;

class vterm_list{
private:
    vterm **terminals;
    size_t count;
    uint64_t id;

public:
    vterm_list();

    uint64_t create_terminal(i_backend *back);
    void delete_terminal(uint64_t id = current_vterm->get_id());
    void switch_terminal(uint64_t id);
    vterm *get(uint64_t id);
    size_t get_count();

    friend char *terms_infofs();
};

char *terms_infofs();
extern vterm_list *terminals;

#endif