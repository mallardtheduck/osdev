#ifndef _PROCESS_HPP
#define _PROCESS_HPP

#include "kernel.hpp"
#include "string.hpp"
#include "../include/locktype.h"

typedef uint64_t pid_t;
typedef uint32_t handle_t;

namespace proc_env_flags{
	enum {
		Global		= (1<<0), //Use PID 0 (kernel) value instead
		ReadOnly	= (1<<1), //Not changeable by user-mode code
		Private		= (1<<2), //Not visible to user-mode code
		NoInherit	= (1<<3), //Do not copy from parent to child
	};
}

namespace proc_status{
    enum Enum{
        Running,
        Ending,
    };
};

struct proc_process;
class string;

extern proc_process *proc_current_process;
extern pid_t proc_current_pid;

#include "load_elf.hpp"

void proc_init();
bool proc_switch(pid_t pid, bool setthread=true);
void proc_switch_sch(pid_t pid, bool setthread=true);
pid_t proc_new(const string &name, size_t argc, char **argv, pid_t parent=proc_current_pid);
void proc_end(pid_t pid=proc_current_pid);

void proc_setenv(const pid_t pid, const string &name, const string &value, const uint8_t flags=0, bool userspace=false);
void proc_setenv(const string &name, const string &value, const uint8_t flags=0, bool userspace=true);
const string &proc_getenv(const pid_t pid, const string &name, bool userspace=false);
const string &proc_getenv(const string &name, bool userspace=true);
pid_t proc_spawn(const string &path, size_t argc, char **argv, pid_t parent=proc_current_pid);
uint64_t proc_new_user_thread(proc_entry entry, void *param, void *stack, pid_t pid=proc_current_pid);

handle_t proc_add_lock(lock *l, pid_t pid=proc_current_pid);
lock *proc_get_lock(handle_t h, pid_t pid=proc_current_pid);
void proc_remove_lock(handle_t h, pid_t pid=proc_current_pid);

handle_t proc_add_handle(bt_handle_info handle, pid_t pid=proc_current_pid);
bt_handle_info proc_get_handle(handle_t h, pid_t pid=proc_current_pid);
void proc_remove_handle(handle_t h, pid_t pid=proc_current_pid);

handle_t proc_add_file(file_handle *file, pid_t pid=proc_current_pid);
file_handle *proc_get_file(handle_t h, pid_t pid=proc_current_pid);
void proc_remove_file(handle_t h, pid_t pid=proc_current_pid);

handle_t proc_add_dir(dir_handle *dir, pid_t pid=proc_current_pid);
dir_handle *proc_get_dir(handle_t h, pid_t pid=proc_current_pid);
void proc_remove_dir(handle_t h, pid_t pid=proc_current_pid);

void proc_setreturn(int ret, pid_t pid=proc_current_pid);
int proc_wait(pid_t pid);

size_t proc_get_argc(pid_t pid=proc_current_pid);
size_t proc_get_arg(size_t i, char *buf, size_t size, pid_t pid=proc_current_pid);

void proc_remove_thread(uint64_t thread_id, pid_t pid=proc_current_pid);
handle_t proc_add_thread(uint64_t thread_id, pid_t pid=proc_current_pid);
uint64_t proc_get_thread(handle_t h, pid_t pid=proc_current_pid);
handle_t proc_get_thread_handle(uint64_t id, pid_t pid=proc_current_pid);

void proc_terminate(pid_t pid=proc_current_pid);

void proc_set_status(proc_status::Enum status, pid_t pid=proc_current_pid);
proc_status::Enum proc_get_status(pid_t pid=proc_current_pid);

void proc_free_message_buffer(pid_t pid=proc_current_pid);
uint64_t proc_send_message(btos_api::bt_msg_header &header, pid_t pid=proc_current_pid);

#endif