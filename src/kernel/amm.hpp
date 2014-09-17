#ifndef _AMM_HPP
#define _AMM_HPP

#include "amm_flags.hpp"

void amm_init();
void amm_mark_alloc(uint32_t pageaddr, amm_flags::Enum flags, pid_t owner = proc_current_pid, void *ptr = NULL);
void amm_mark_free(uint32_t pageaddr);
amm_flags::Enum amm_get_flags(uint32_t pageaddr);
void amm_set_guard(void *ptr);
void amm_set_info(uint32_t pageaddr, amm_flags::Enum flags, void *ptr);
void amm_mmap(char *ptr, file_handle &file, size_t offset, size_t size);

#endif