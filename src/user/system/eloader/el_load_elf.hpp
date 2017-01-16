#ifndef _EL_LOAD_ELF_HPP
#define _EL_LOAD_ELF_HPP

#include "elf.hpp"

typedef void (*entrypoint)();

entrypoint load_elf_proc(bt_handle_t file);

#endif