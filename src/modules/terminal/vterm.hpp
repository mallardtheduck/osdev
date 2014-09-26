#ifndef _VTERM_HPP
#define _VTERM_CPP

#include "module_api.h"
#include "video_dev.h"
#include "terminal.h"
#include "backend.hpp"

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

    pid_t curpid;
    bt_terminal_mode::Enum mode;

    void wait_until_active();
    void putchar(char c);
    void putstring(char *s);
    void scroll();
    void do_infoline();

    char title[256];

public:
    vterm(uint64_t id, i_backend *back);
    ~vterm();

    uint64_t get_id();

    void activate();
    void deactivate();

    size_t write(size_t size, char *buf);
    size_t read(size_t size, char *buf);
    size_t seek(size_t pos, bool relative);
    int ioctl(int fn, size_t size, char *buf);

    void sync();
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
};

extern vterm_list *terminals;

#endif