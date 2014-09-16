#ifndef _VMM_HPP
#define _VMM_HPP

#include "amm_flags.hpp"
#include "kernel.hpp"

const size_t VMM_PAGE_SIZE=4096;
const size_t VMM_KERNELSPACE_END=1024*1024*1024;
const size_t VMM_USERSPACE_START=VMM_KERNELSPACE_END;
const uint32_t VMM_ADDRESS_MASK=0xFFFFF000;

namespace vmm_allocmode{
	enum Enum{
		Kernel,
		Userlow,
		Userhigh,
	};
}

class vmm_pagedir;

extern vmm_pagedir *vmm_cur_pagedir;

void vmm_init(multiboot_info_t *mbt);
void *vmm_alloc(size_t pages, vmm_allocmode::Enum mode=vmm_allocmode::Kernel);
void *vmm_alloc_at(size_t pages, size_t baseaddr);
void vmm_free(void *ptr, size_t pages);
void vmm_switch(vmm_pagedir *dir);
vmm_pagedir *vmm_newpagedir();
void vmm_deletepagedir(vmm_pagedir *dir);
size_t vmm_getusermemory(vmm_pagedir *dir);
size_t vmm_getkernelmemory();
size_t vmm_gettotalmem();
void vmm_set_flags(uint32_t pageaddr, amm_flags::Enum flags);
amm_flags::Enum vmm_get_flags(uint32_t pageaddr);

#endif