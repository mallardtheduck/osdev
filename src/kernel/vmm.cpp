#include "vmm.hpp"
#include "locks.hpp"

const size_t VMM_PAGE_SIZE=4096;
const size_t VMM_ENTRIES_PER_TABLE=1024;
const size_t VMM_KERNELSPACE_END=1024*1024*1024;
const size_t VMM_USERSPACE_START=VMM_KERNELSPACE_END;

extern char _start, _end;
lock vmm_lock;

struct vmm_region{
	void *base;
	size_t pages;
};

void vmm_refresh_addr(uint32_t pageaddr);

class vmm_pagestack{
private:
    uint32_t *bottom;
    uint32_t *top;
    uint32_t *limit;

public:
    void init(uint32_t *ptr, size_t size){
        bottom=top=ptr;
        limit=(uint32_t*)((size_t)ptr+size);
    }

    void push(uint32_t page){
        if(top+1<limit){
            *(++top)=page;
        }
    }

    uint32_t pop(){
        if(top-1>=bottom){
            return *(top--);
        } else return 0;
    }
};

class vmm_pagedir{
private:
    uint32_t* pagedir;
public:
    void init(uint32_t *dir){
        pagedir=dir;
    }
    uint32_t *get(){
        return pagedir;
    }

    void add_table(size_t tableno, uint32_t *table){
        pagedir[tableno]=(uint32_t)table | 3;
    }

    size_t find_free_virtpages(size_t pages, bool kernelspace=true){
    	size_t freecount=0;
    	size_t startpage=0;
    	size_t starttable=0;
    	if(!kernelspace){
    		starttable=(VMM_KERNELSPACE_END/VMM_PAGE_SIZE)/VMM_ENTRIES_PER_TABLE;
    	}
    	for(size_t i=starttable; i<VMM_ENTRIES_PER_TABLE; ++i){
    		uint32_t *table=(uint32_t*)(pagedir[i] & 0xFFFFF000);
    		for(size_t j=0; j<VMM_ENTRIES_PER_TABLE; ++j){
    			if(!i && !j) continue; //never allocate page 0
    			if(!table){
    				if(pages<VMM_ENTRIES_PER_TABLE + freecount){
    					return startpage;
    				}else{
    					freecount+=VMM_ENTRIES_PER_TABLE;
    					break;
    				}
    			}
    			if(!table[j]){
    				if(!startpage) startpage=(i*VMM_ENTRIES_PER_TABLE)+j;
    				++freecount;
    			}else{
    				startpage=0;
    				freecount=0;
    			}
    			if(freecount==pages){
    				return startpage;
    			}
    		}
    	}
    	return 0;
    }

    void map_page(size_t virtpage, size_t physpage, bool alloc=true){
    	dbgpf("VMM: Mapping %x (v) to %x (p).\n", virtpage*VMM_PAGE_SIZE, physpage*VMM_PAGE_SIZE);
    	if(!virtpage || !physpage) panic("(VMM) Attempt to map page/address 0!");
    	if(!pagedir) panic("(VMM) Invalid page directory!");
    	size_t tableindex=virtpage/VMM_ENTRIES_PER_TABLE;
    	size_t tableoffset=virtpage-(tableindex * VMM_ENTRIES_PER_TABLE);
    	uint32_t *table=(uint32_t*)(pagedir[tableindex] & 0xFFFFF000);
    	if(!table){
    		if(alloc){
    			/*uint32_t *i;
    			for(i=vmm_fullstack_top; i<vmm_fullstack_bottom && vmm_vpage_inuse(pagedir, *i/VMM_PAGE_SIZE); --i);
    			if(i==vmm_fullstack_bottom) panic("(VMM) No identity mappable pages!");
    			size_t movedata=(size_t)(vmm_fullstack_top-(i));
    			dbgpf("VMM: Moving %i bytes from %x to %x\n", movedata, i+1, i);
    			memmove(i, i+1, movedata);
    			vmm_fullstack_top--;
    			vmm_identity_map(vmm_cur_pagedir, *i);
    			uint32_t phys_addr=(*i)*VMM_PAGE_SIZE;
    			pagedir[tableindex]=phys_addr | 3;
    			table=(uint32_t*)(pagedir[tableindex] & 0xFFFFF000);*/
    			panic("(VMM) Creating page tables not yet implemented!");
    		}else{
    			panic("(VMM) Cannot allocate page table for mapping!");
    		}
    	}
    	table[tableoffset]=(physpage*VMM_PAGE_SIZE) | 3;
    	vmm_refresh_addr(virtpage * VMM_PAGE_SIZE);
    }

    void identity_map(size_t page, bool alloc){
    	map_page(page, page, alloc);
    }

    size_t unmap_page(size_t virtpage){
    	if(!pagedir) panic("(VMM) Invalid page directory!");
    	size_t tableindex=virtpage/VMM_ENTRIES_PER_TABLE;
        size_t tableoffset=virtpage-(tableindex * VMM_ENTRIES_PER_TABLE);
        uint32_t *table=(uint32_t*)(pagedir[tableindex] & 0xFFFFF000);
        if(!table){
        	panic("(VMM) No table for allocation!");
        }
        uint32_t ret=table[tableoffset] & 0xFFFFF000;
        table[tableoffset]=0;
        vmm_refresh_addr(virtpage * VMM_PAGE_SIZE);
        return ret/VMM_PAGE_SIZE;
    }
};

const size_t VMM_MAX_REGIONS=32;
vmm_region vmm_regions[VMM_MAX_REGIONS]={0, 0};
uint32_t vmm_kpagedir[VMM_ENTRIES_PER_TABLE] __attribute__((aligned(0x1000)));
uint32_t vmm_kinitable[VMM_ENTRIES_PER_TABLE] __attribute__((aligned(0x1000)));
vmm_pagedir *vmm_cur_pagedir, vmm_kernel_pagedir;
vmm_pagestack vmm_pages;

void *vmm_ministack_alloc(size_t pages=1);
void vmm_ministack_free(void *ptr, size_t pages=1);
void vmm_identity_map(uint32_t *pagedir, size_t page, bool alloc=true);
void vmm_page_fault_handler(int,isr_regs*);

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
				if(cregion>=VMM_MAX_REGIONS) break;
			}
		}
		mmap = (memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
    }
    size_t totalpages=0;
    for(size_t i=0; i<VMM_MAX_REGIONS; ++i){
    	if(vmm_regions[i].base){
    		for(size_t j=0; j<vmm_regions[i].pages; ++j){
    			size_t phys_page_num=((size_t)vmm_regions[i].base/VMM_PAGE_SIZE)+j;
    			void* phys_page_addr=(void*)(phys_page_num*VMM_PAGE_SIZE);
    			if(phys_page_num < 256) panic("(VMM) Page number too low!");
    			if(phys_page_num>=k_first_page && phys_page_num<=k_last_page){
    				dbgpf("VMM: Region %i, page %i (%x) - KERNEL\n", i, j, phys_page_num);
    			}else{
    				memset(phys_page_addr, 0, VMM_PAGE_SIZE);
    				++totalpages;
    			}
    		}
    	}else break;
    }
    dbgpf("VMM: Total pages: %i\n", totalpages);
    printf("VMM: Available RAM: %iKB\n", totalpages*4);
   	dbgpf("VMM: Initializing kernel page directory at %x.\n", vmm_kpagedir);
	for(size_t i=0; i<VMM_ENTRIES_PER_TABLE; ++i){
		vmm_kpagedir[i]=0|2;
	}
	dbgpf("VMM: Initializing initial page table at %x.\n", vmm_kinitable);
	memset((void*)vmm_kinitable, 0, VMM_PAGE_SIZE);
	vmm_kernel_pagedir.init(vmm_kpagedir);
	vmm_kernel_pagedir.add_table(0, vmm_kinitable);
    size_t stacksize=totalpages * sizeof(uint32_t);
    size_t stackpages=(stacksize/VMM_PAGE_SIZE)+1;
    dbgpf("VMM: Pages needed for page stack: %i\n", stackpages);
    size_t firstfreepage=k_last_page+stackpages+1;
    dbgpf("VMM: First free page: %x", firstfreepage);
    dbgpf("VMM: Setting up identity mappings.\n");
    for(size_t i=1; i<firstfreepage; ++i){
    	vmm_kernel_pagedir.identity_map(i, false);
    }
    int_handle(0x0e, &vmm_page_fault_handler);
    dbgout("VMM: Enabing paging...");
    asm volatile("mov %0, %%cr3":: "b"(vmm_kernel_pagedir.get()));
    unsigned int cr0;
    asm volatile("mov %%cr0, %0": "=b"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0":: "b"(cr0));
    dbgout("Done.\n");
    vmm_cur_pagedir=&vmm_kernel_pagedir;
    vmm_pages.init((uint32_t*)((k_last_page+1)*VMM_PAGE_SIZE), stacksize*VMM_PAGE_SIZE);
    for(size_t i=0; i<VMM_MAX_REGIONS; ++i){
    	if(vmm_regions[i].base){
    		size_t base=(size_t)vmm_regions[i].base;
    		for(size_t j=0; j<vmm_regions[i].pages; ++j){
    			size_t pageaddr=base+(VMM_PAGE_SIZE*j);
    			if(pageaddr >= (firstfreepage*VMM_PAGE_SIZE)){
    				vmm_pages.push(pageaddr);
    			}
    		}
    	}else{
    		break;
    	}
    }
    dbgout("VMM: Page stack initialized.\n");
    /*void *q=malloc(10*1024*1024);
    memset(q, 0xcc, 10*1024*1024);
    free(q);*/
}

void vmm_page_fault_handler(int, isr_regs *regs){
	uint32_t addr;
	asm("mov %%cr2, %%eax\r\n mov %%eax,%0": "=m"(addr): : "eax");
	dbgpf("VMM: Page fault on %x at %x!\n", addr, regs->eip);
	if(addr < VMM_PAGE_SIZE) panic("(VMM) Probable NULL pointer deference!");
	else panic("(VMM) Page fault!");
}

void vmm_refresh_addr(uint32_t pageaddr){
	asm volatile("invlpg (%0)" ::"r" (pageaddr) : "memory");
}

bool vmm_vpage_inuse(uint32_t *pagedir, size_t virtpage){
	if(!pagedir) panic("(VMM) Invalid page directory!");
	size_t tableindex=virtpage/VMM_ENTRIES_PER_TABLE;
    size_t tableoffset=virtpage-(tableindex * VMM_ENTRIES_PER_TABLE);
    uint32_t *table=(uint32_t*)(pagedir[tableindex] & 0xFFFFF000);
    if(!table){
    	panic("(VMM) No table for allocation!");
    }
    uint32_t ret=table[tableoffset] & 0xFFFFF000;
    return ret!=0;
}

void *vmm_alloc(size_t pages, bool kernelspace){
	hold_lock hl(vmm_lock);
	size_t virtpage=vmm_cur_pagedir->find_free_virtpages(pages, kernelspace);
	if(!virtpage) return NULL;
	for(size_t i=0; i<pages; ++i){
		uint32_t phys_page=vmm_pages.pop();
		if(!phys_page) return NULL;
		vmm_cur_pagedir->map_page(virtpage+i, phys_page);
	}
	void *ret=(void*)(virtpage*VMM_PAGE_SIZE);
	memset(ret, 0xaa, pages*VMM_PAGE_SIZE);
	return ret;
}

void vmm_free(void *ptr, size_t pages){
	hold_lock hl(vmm_lock);
	memset(ptr, 0xfe, pages * VMM_PAGE_SIZE);
	size_t virtpage=(uint32_t)ptr/VMM_PAGE_SIZE;
	for(size_t i=0; i<pages; ++i){
		size_t physpage=vmm_cur_pagedir->unmap_page(virtpage+i);
		vmm_pages.push(physpage*VMM_PAGE_SIZE);
	}
}
