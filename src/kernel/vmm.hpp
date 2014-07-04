#ifndef _VMM_HPP
#define _VMM_HPP

#include "kernel.hpp"

void vmm_init(multiboot_info_t *mbt);
void *vmm_alloc(size_t pages, bool kernelspace=true);
void vmm_free(void *ptr, size_t pages);

#endif