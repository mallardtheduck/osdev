#include "vmm.hpp"
#include "locks.hpp"

const size_t VMM_PAGE_SIZE=4096;
const size_t VMM_ENTRIES_PER_TABLE=1024;
const size_t VMM_MINISTACK_PAGES=VMM_PAGE_SIZE/sizeof(uint16_t);
extern char _start, _end;
lock vmm_lock;

struct vmm_region{
	void *base;
	size_t pages;
};

const size_t MAX_REGIONS=32;
vmm_region vmm_regions[MAX_REGIONS]={0, 0};
uint32_t *vmm_kpagedir;
uint16_t *vmm_free_pages;
uint16_t *vmm_ministack;

void *vmm_ministack_alloc(size_t pages=1);
void vmm_ministack_free(void *ptr, size_t pages=1);
void vmm_identity_map(uint32_t *pagedir, size_t page);

void vmm_init(multiboot_info_t *mbt){
	init_lock(vmm_lock);
	dbgout("VMM: Init\n");
	memory_map_t *mmap = (memory_map_t*)mbt->mmap_addr;
	size_t k_first_page=((size_t)&_start/VMM_PAGE_SIZE);
	size_t k_last_page=((size_t)&_end/VMM_PAGE_SIZE);
	dbgpf("VMM: Kernel start: %x (page %x) end: %x (page %x).\n", &_start,
		k_first_page, &_end, k_last_page);
	size_t cregion=0;
    while(mmap < (memory_map_t*)mbt->mmap_addr + mbt->mmap_length) {
		if(mmap->type == 1 && mmap->length_low > 0){
			dbgpf("VMM: Usable region base: 0x%x pages: %u\n", mmap->base_addr_low, mmap->length_low/VMM_PAGE_SIZE);
			if(mmap->base_addr_low < 1024*1024 && mmap->length_low < 1024*1024){
				dbgpf("VMM: Ignoring low 1MB RAM\n");
			}else{
				vmm_regions[cregion].base=(void*)mmap->base_addr_low;
				vmm_regions[cregion].pages=mmap->length_low/VMM_PAGE_SIZE;
				++cregion;
				if(cregion>=MAX_REGIONS) break;
			}
		}
		mmap = (memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
    }
    size_t totalpages=0;
    size_t minipage=0;
    for(size_t i=0; i<MAX_REGIONS; ++i){
    	if(vmm_regions[i].base){
    		for(size_t j=0; j<vmm_regions[i].pages; ++j){
    			size_t phys_page_num=((size_t)vmm_regions[i].base/VMM_PAGE_SIZE)+j;
    			void* phys_page_addr=(void*)(phys_page_num*VMM_PAGE_SIZE);
    			if(phys_page_num < 256) panic("(VMM) Page number too low!");
    			if(phys_page_num>=k_first_page && phys_page_num<=k_last_page){
    				dbgpf("VMM: Region %i, page %i (%x) - KERNEL\n", i, j, phys_page_num);
    			}else{
    				if(!vmm_ministack) vmm_ministack=(uint16_t*)phys_page_addr;
    				else if(minipage < VMM_MINISTACK_PAGES){
    					vmm_ministack[minipage++]=phys_page_num;
    				}
    				memset(phys_page_addr, 0, VMM_PAGE_SIZE);
    				++totalpages;
    			}
    		}
    	}
    }
    dbgpf("VMM: Total pages: %i\n", totalpages);
    printf("VMM: Available RAM: %iKB\n", totalpages*4);
   	uint32_t *temp_pagedir=(uint32_t*)vmm_ministack_alloc();
	for(size_t i=0; i<VMM_ENTRIES_PER_TABLE; ++i){
		temp_pagedir[i]=0|2;
	}
	for(int i=0; i<5; ++i){
		uint32_t temp_table=(uint32_t)vmm_ministack_alloc();
		temp_pagedir[i]=temp_table;
		temp_pagedir[i] |= 3;
	}
	vmm_kpagedir=temp_pagedir;
   	if(!vmm_kpagedir){
   		panic("(VMM) Could not allocate kernel page directory!");
   	}
   	dbgpf("VMM: Kernel page directory: %x\n", vmm_kpagedir);
   	vmm_identity_map(vmm_kpagedir, (size_t)vmm_ministack/VMM_PAGE_SIZE);
    vmm_identity_map(vmm_kpagedir, (size_t)vmm_kpagedir/VMM_PAGE_SIZE);
    for(int i=0; i<5; ++i){
    	uint32_t temp_table=vmm_kpagedir[i] & 0xFFFFF000;
    	vmm_identity_map(vmm_kpagedir, temp_table/VMM_PAGE_SIZE);
    }
    for(size_t i=0; i<=k_last_page; ++i){
    	vmm_identity_map(vmm_kpagedir, i);
    }
    //for(size_t i=0; i<VMM_MINISTACK_PAGES; ++i){
    //	if(vmm_ministack[i]) vmm_identity_map(vmm_kpagedir, vmm_ministack[i]);
    //}
    asm volatile("mov %0, %%cr3":: "b"(vmm_kpagedir));
    unsigned int cr0;
    asm volatile("mov %%cr0, %0": "=b"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0":: "b"(cr0));
}

void vmm_identity_map(uint32_t *pagedir, size_t page){
	dbgpf("VMM: Idenitiy mapping page %x\n", page);
	uint32_t pageaddr=page*VMM_PAGE_SIZE;
	size_t table=page/VMM_ENTRIES_PER_TABLE;
	size_t offset=page-(table*VMM_ENTRIES_PER_TABLE);
	uint32_t *tableaddr=(uint32_t*)(pagedir[table] & 0xFFFFF000);
	if(!tableaddr){
		panic("(VMM) No table for allocation!\n");
		tableaddr=(uint32_t*)vmm_ministack_alloc();
		pagedir[table] = (uint32_t)tableaddr;
		pagedir[table] |= 3;
	}
	tableaddr[offset]=pageaddr | 3;
	asm volatile("invlpg (%0)" ::"r" (pageaddr) : "memory");
}

void vmm_unmap(uint32_t *pagedir, size_t page){
	dbgpf("VMM: Unmapping page %x.\n", page);
	if(page <= ((size_t)&_end/VMM_PAGE_SIZE)){
		panic("Attempt to unmap low page!");
	}
	uint32_t pageaddr=page*VMM_PAGE_SIZE;
    size_t table=page/VMM_ENTRIES_PER_TABLE;
    size_t offset=page-(table*VMM_ENTRIES_PER_TABLE);
    uint32_t *tableaddr=(uint32_t*)(pagedir[table] & 0xFFFFF000);
    tableaddr[offset] = 0;
    asm volatile("invlpg (%0)" ::"r" (pageaddr) : "memory");
}

bool vmm_ministack_find(size_t page){
	for(size_t i=0; i<VMM_MINISTACK_PAGES; ++i){
			if(vmm_ministack[i]==page) return true;
	}
	return false;
}

void vmm_ministack_take(size_t page){
	for(size_t i=0; i<VMM_MINISTACK_PAGES; ++i){
			if(vmm_ministack[i]==page) vmm_ministack[i]=0;
	}
}

void *vmm_ministack_alloc(size_t pages){
	hold_lock hl(vmm_lock);
	void *ret;
	for(size_t i=0; i<VMM_MINISTACK_PAGES; ++i){
		size_t base=vmm_ministack[i];
		if(!base) continue;
		bool ok=false;
		for(size_t j=base; j<base+pages; ++j){
			ok=vmm_ministack_find(j);
			if(!ok) break;
		}
		if(ok){
           	for(size_t j=base; j<base+pages; ++j){
				vmm_ministack_take(j);
        		if(vmm_kpagedir)vmm_identity_map(vmm_kpagedir, j);
        	}
			memset((void*)base, 0xaa, pages*VMM_PAGE_SIZE);
			ret=(void*)(base*VMM_PAGE_SIZE);
			return ret;
		}
	}
	dbgout("VMM: Out of kernel heap space!");
	return NULL;
}

void vmm_ministack_free(void *ptr, size_t pages){
	hold_lock hl(vmm_lock);
	memset(ptr, 0xfe, pages * VMM_PAGE_SIZE);
	for(size_t j=0; j<pages; ++j){
		uint16_t page_num=j+(size_t)ptr/VMM_PAGE_SIZE;
		for(size_t i=0; i<VMM_MINISTACK_PAGES; ++i){
			if(!vmm_ministack[i]){
				vmm_ministack[i]=page_num;
				vmm_unmap(vmm_kpagedir, page_num);
				break;
			}
		}
	}
}
