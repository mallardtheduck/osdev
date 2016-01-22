#ifndef _VMM_HPP
#define _VMM_HPP

#include "amm_flags.hpp"
#include "kernel.hpp"


const size_t VMM_MAX_REGIONS=32;
struct vmm_region{
    void *base;
    size_t pages;
};

const size_t VMM_PAGE_SIZE=4096;
const size_t VMM_KERNELSPACE_END=1024*1024*1024;
const size_t VMM_USERSPACE_START=VMM_KERNELSPACE_END;
const uint32_t VMM_ADDRESS_MASK=0xFFFFF000;
const size_t VMM_ENTRIES_PER_TABLE=1024;
const size_t VMM_KERNEL_PAGES=VMM_KERNELSPACE_END/VMM_PAGE_SIZE;
const size_t VMM_KERNEL_TABLES=VMM_KERNEL_PAGES/VMM_ENTRIES_PER_TABLE;
const size_t VMM_MAX_PAGES=VMM_ENTRIES_PER_TABLE * VMM_ENTRIES_PER_TABLE;
const size_t VMM_MAX_RAM=VMM_MAX_PAGES*VMM_PAGE_SIZE;
const uint32_t VMM_FLAGS_MASK=0x00000E00;

namespace vmm_allocmode{
	enum Enum{
		Kernel      = (1<<0),
		Userlow     = (1<<1),
		Userhigh    = (1<<2),
        NotPresent  = (1<<3),
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
uint32_t vmm_physaddr(void *ptr);
multiboot_info_t *vmm_get_multiboot();

#endif