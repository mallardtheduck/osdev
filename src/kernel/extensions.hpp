#ifndef _EXTENSIONS_HPP
#define _EXTENSIONS_HPP

#include "kernel.hpp"
namespace module_api {
#include <module/extension.h>
}

void init_extensions();
uint16_t add_extension(module_api::kernel_extension *ext);
module_api::kernel_extension *get_extension(uint16_t ext);
uint16_t get_extension_id(const char *name);
void user_call_extension(uint16_t ext_id, uint16_t fn, isr_regs *regs);

#endif