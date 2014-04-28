#ifndef _MM_HPP
#define _MM_HPP

#include "kernel.hpp"

void mm_init(multiboot_info_t *mbd);
void *mm_alloc(size_t bytes);
void mm_free(void *ptr);
size_t mm_getfreemem();

#endif
