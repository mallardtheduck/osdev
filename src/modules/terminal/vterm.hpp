#ifndef _VTERM_HPP
#define _VTERM_HPP

#include <stdint.h>
#include <btos_module.h>
#include <dev/video_dev.h>
#include <dev/terminal.h>
#include <util/circular_buffer.hpp>
#include <util/ministl.hpp>
#include "backend.hpp"

struct vterm_options{
    bt_terminal_mode::Enum mode;
	bool event_mode_owner;

    vterm_options() : mode(bt_terminal_mode::Terminal), event_mode_owner(false) {}
};

static constexpr bt_terminal_pointer_event zero_event={bt_terminal_pointer_event_type::None, 0, 0, 0};

class i_backend;

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
    uint32_t refcount;
    lock term_lock;
    uint64_t scrollcount;
    bool pointer_enabled;
	bool pointer_autohide;
    bt_terminal_pointer_bitmap *pointer_bitmap;
	uint64_t last_move_message;

    circular_buffer<uint32_t, 128> keyboard_buffer;
    circular_buffer<bt_terminal_pointer_event, 512> pointer_buffer{zero_event};
    lock input_lock;

    pid_t curpid;
	pid_t events_pid;
	bt_terminal_event_mode::Enum event_mode;
	bool event_mode_enabled;

    void putchar(char c);
    void putstring(char *s);
    void setcolours(uint8_t c);
    uint8_t getcolours();
    void scroll();
    void do_infoline();
    char get_char();
    uint32_t get_input();
    bt_terminal_pointer_event get_pointer();
    void create_terminal(char *command);
	uint64_t send_event(const bt_terminal_event &e);

    friend bool input_blockcheck(void *p);
    friend bool pointer_blockcheck(void *p);
    friend bool event_blockcheck(void *p);

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
    size_t seek(vterm_options &opts, size_t pos, uint32_t flags);
    int ioctl(vterm_options &opts, int fn, size_t size, char *buf);
    void open();
    void close(vterm_options &opts);

    void queue_input(uint32_t code);
    void queue_pointer(bt_terminal_pointer_event event);
    void sync(bool content=true);

    void allocate_buffer();
    void clear_buffer();
	
	void update_current_pid();
	i_backend *get_backend();
	
	void read_buffer(size_t size, uint8_t *buf);
	void set_backend(i_backend *back);
	size_t getpos();
};

//extern vterm *current_vterm;

class vterm_list{
private:
	vector<vterm*> terminals;
    uint64_t id;
    lock vtl_lock;

public:
    vterm_list();

    uint64_t create_terminal(i_backend *back);
    void delete_terminal(uint64_t id);
	void delete_backend(i_backend *back);
    vterm *get(uint64_t id);
    size_t get_count();

    friend char *terms_infofs();
};

char *terms_infofs();
extern vterm_list *terminals;
size_t strlen(const char *str);

#endif