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
uint32_t vmm_kpagedir[VMM_ENTRIES_PER_TABLE] __attribute__((aligned(0x1000)));
uint32_t vmm_kinitable[VMM_ENTRIES_PER_TABLE] __attribute__((aligned(0x1000)));
uint16_t *vmm_free_pages;
uint16_t *vmm_ministack;

void *vmm_ministack_alloc(size_t pages=1);
void vmm_ministack_free(void *ptr, size_t pages=1);
void vmm_identity_map(uint32_t *pagedir, size_t page);
void vmm_page_fault_handler(int);

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
   	dbgpf("VMM: Initializing kernel page directory at %x.\n", vmm_kpagedir);
	for(size_t i=0; i<VMM_ENTRIES_PER_TABLE; ++i){
		vmm_kpagedir[i]=0|2;
	}
	dbgpf("VMM: Initializing initial page table.\n");
	memset((void*)vmm_kinitable, 0, VMM_PAGE_SIZE);
	vmm_kpagedir[0]=(uint32_t)vmm_kinitable | 3;
   	dbgpf("VMM: Setting up identity mappings.\n");
   	vmm_identity_map(vmm_kpagedir, (size_t)vmm_ministack/VMM_PAGE_SIZE);
    vmm_identity_map(vmm_kpagedir, (size_t)vmm_kpagedir/VMM_PAGE_SIZE);
    for(size_t i=1; i<=k_last_page; ++i){
    	vmm_identity_map(vmm_kpagedir, i);
    }
    int_handle(0x0e, &vmm_page_fault_handler);
    dbgout("VMM: Enabing paging...");
    asm volatile("mov %0, %%cr3":: "b"(vmm_kpagedir));
    unsigned int cr0;
    asm volatile("mov %%cr0, %0": "=b"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0":: "b"(cr0));
    dbgout("Done.");
}

void vmm_page_fault_handler(int){
	uint32_t addr;
	asm("mov %%cr2, %%eax\r\n mov %%eax,%0": "=m"(addr): : "eax");
	dbgpf("VMM: Page fault at %x!\n", addr);
	if(addr < VMM_PAGE_SIZE) panic("(VMM) Probable NULL pointer deference!");
	else panic("(VMM) Page fault!");
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

size_t vmm_find_free_virtpages(uint32_t *pagedir, size_t pages){
	size_t freecount=0;
	size_t startpage=0;
	for(size_t i=0; i<VMM_ENTRIES_PER_TABLE; ++i){
		uint32_t *table=(uint32_t*)(pagedir[i] & 0xFFFFF000);
		for(size_t j=0; j<VMM_ENTRIES_PER_TABLE; ++j){
			if(!i && !j) continue; //never allocate page 0
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

void vmm_refresh_addr(uint32_t pageaddr){
	asm volatile("invlpg (%0)" ::"r" (pageaddr) : "memory");
}

void vmm_map_page(uint32_t *pagedir, size_t virtpage, size_t physpage){
	dbgpf("VMM: Mapping page %x at %x\n", physpage, virtpage);
	size_t tableindex=virtpage/VMM_ENTRIES_PER_TABLE;
	size_t tableoffset=virtpage-(tableindex * VMM_ENTRIES_PER_TABLE);
	uint32_t *table=(uint32_t*)(pagedir[tableindex] & 0xFFFFF000);
	if(!table){
		panic("(VMM) No table for allocation!");
	}
	table[tableoffset]=(physpage*VMM_PAGE_SIZE) | 3;
	vmm_refresh_addr(virtpage * VMM_PAGE_SIZE);
}

void vmm_identity_map(uint32_t *pagedir, size_t page){
	vmm_map_page(pagedir, page, page);
}

size_t vmm_unmap_page(uint32_t *pagedir, size_t virtpage){
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

void *vmm_ministack_alloc(size_t pages){
	hold_lock hl(vmm_lock);
	size_t virtpage=vmm_find_free_virtpages(vmm_kpagedir, pages);
	if(!virtpage) return NULL;
	for(size_t i=0; i<pages; ++i){
		for(size_t j=0; j<VMM_MINISTACK_PAGES; ++j){
			if(vmm_ministack[j]){
				vmm_map_page(vmm_kpagedir, virtpage+i, vmm_ministack[j]);
				vmm_ministack[j]=0;
				break;
			}
		}
	}
	void *ret=(void*)(virtpage*VMM_PAGE_SIZE);
	memset(ret, 0xaa, pages*VMM_PAGE_SIZE);
	return ret;
}

void vmm_ministack_free(void *ptr, size_t pages){
	hold_lock hl(vmm_lock);
	memset(ptr, 0xfe, pages * VMM_PAGE_SIZE);
	size_t virtpage=(uint32_t)ptr/VMM_PAGE_SIZE;
	for(size_t i=0; i<pages; ++i){
		size_t physpage=vmm_unmap_page(vmm_kpagedir, virtpage+i);
		for(size_t j=0; j<VMM_MINISTACK_PAGES; ++j){
			if(!vmm_ministack[j]){
				vmm_ministack[j]=physpage;
				break;
			}
        }
	}
}
