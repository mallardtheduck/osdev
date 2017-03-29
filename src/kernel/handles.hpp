#ifndef _HANDLES_HPP
#define _HANDLES_HPP

#include <module/handle.h>

namespace kernel_handle_types{
    static const uint32_t invalid=0;
    static const uint32_t lock=1;
    static const uint32_t file=2;
    static const uint32_t directory=3;
    static const uint32_t thread=4;
    static const uint32_t memory_mapping=5;
	static const uint32_t shm_space=6;
	static const uint32_t shm_mapping=7;
	static const uint32_t atom=8;
};

bt_handle_info create_handle(uint32_t type, void *value, handle_close_fn close);
void close_handle(bt_handle_info &handle);

extern bt_handle_info invalid_handle;

#endif
