#ifndef _MM2_HPP
#define _MM2_HPP

#include "kernel.hpp"
#include "mm2/mm2_public.hpp"

void mm2_init(multiboot_info_t *mbt);
void *mm2_virtual_alloc(size_t pages, uint32_t mode = MM2::MM2_Alloc_Mode::Kernel);
void mm2_virtual_free(void *ptr, size_t pages);

#include "mm2/pagedirectory.hpp"

#endif