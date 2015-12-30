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

context get_context(uint64_t thread);
void out_context(const context ctx);
void debug_peek(void *dst, pid_t pid, uint32_t src, size_t size);
void debug_poke(pid_t pid, uint32_t dst, void *src, size_t size);
void do_stacktrace(bt_pid_t pid, context ctx);

void out_event(const bt_debug_event_msg &event);

void test_symbols(std::string filename);

#endif