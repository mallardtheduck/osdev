#ifndef _HANDLES_HPP
#define _HANDLES_HPP

#include <handle.h>

namespace kernel_handle_types{
    static const uint32_t invalid=0;
    static const uint32_t lock=1;
    static const uint32_t file=2;
    static const uint32_t directory=3;
    static const uint32_t thread=4;
    static const uint32_t memory_mapping=5;
};

bt_handle create_handle(uint32_t type, void *value, handle_close_fn close);
void close_handle(bt_handle &handle);

extern bt_handle invalid_handle;

#endif