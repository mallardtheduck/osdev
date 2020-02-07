#ifndef _DEBUG_HPP
#define _DEBUG_HPP

#include <btos.h>
#include <iostream>
#include <ext/debug.h>
#include <cstdio>
#include <string>

struct context {
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t interrupt_number, error_code;
	uint32_t eip, cs, eflags;
	uint32_t useresp, userss;
} __attribute__((packed));

struct el_loaded_module{
	uint32_t id;
	intptr_t name;
	intptr_t full_path;
	intptr_t dynamic;
	intptr_t base;
	size_t limit;
	bool is_dynamic;
};

context get_context(uint64_t thread);
void out_context(const context ctx);
void debug_peek(void *dst, pid_t pid, uint32_t src, size_t size);
void debug_peek_string(char *dst, pid_t pid, uint32_t src, size_t max_size);
void debug_poke(pid_t pid, uint32_t dst, void *src, size_t size);
void debug_stop(pid_t pid);
void debug_continue(pid_t pid);
bool debug_setbreakpoint(uint64_t thread, intptr_t addr, uint8_t type);
bool debug_clearbreakpoint(uint64_t thread, intptr_t addr);
uint32_t debug_getbpinfo(uint64_t thread);

void do_stacktrace(btos_api::bt_pid_t pid, context ctx);
void out_event(const bt_debug_event_msg &event);
void test_symbols(std::string filename);

extern uint16_t debug_ext_id;

#endif
