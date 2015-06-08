#ifndef _AMM_HPP
#define _AMM_HPP

#include "kernel.hpp"
#include "amm_page_accounting.hpp"

void amm_init();
void amm_mark_alloc(uint32_t pageaddr, amm_page_type::Enum type, void *info = NULL);
void amm_mark_free(uint32_t pageaddr);
void amm_set_guard(void *ptr);
uint64_t amm_mmap(char *ptr, file_handle &file, size_t offset, size_t size);
void amm_flush(file_handle &file);
void amm_close(file_handle &file);
void amm_closemap(uint64_t id);
bool amm_resolve_addr(void *addr);

#endif