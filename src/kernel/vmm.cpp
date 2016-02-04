#include "vmm.hpp"
#include "locks.hpp"

#define PAGING_ENABLED_FLAG 0x80000000

multiboot_info_t *multiboot_info;

namespace PageFlags{
	enum{
		Present 		= 1 << 0,
		Writable 		= 1 << 1,
		Usermode 		= 1 << 2,
		WriteThrough 	= 1 << 3,
		NoCache			= 1 << 4,
		Accessed		= 1 << 5,
		Dirty			= 1 << 6,
		Global			= 1 << 7,
	};
}

namespace TableFlags{
	enum{
		Present 		= 1 << 0,
		Writable 		= 1 << 1,
		Usermode 		= 1 << 2,
		WriteThrough 	= 1 << 3,
		NoCache			= 1 << 4,
		Accessed		= 1 << 5,
		LargePages		= 1 << 6,
    };
}

extern char _start, _end;
lock vmm_lock;

void vmm_refresh_addr(uint32_t pageaddr);
bool is_paging_enabled();

uint32_t vmm_tableframe[VMM_ENTRIES_PER_TABLE] __attribute__((aligned(0x1000)));
lock vmm_framelock;
static size_t kmem=0;

vmm_region vmm_regions[VMM_MAX_REGIONS]={0, 0};
uint32_t vmm_kpagedir[VMM_ENTRIES_PER_TABLE] __attribute__((aligned(0x1000)));
uint32_t vmm_kinitable[VMM_ENTRIES_PER_TABLE] __attribute__((aligned(0x1000)));
size_t vmm_totalmem=0;

void *vmm_ministack_alloc(size_t pages=1);
void vmm_ministack_free(void *ptr, size_t pages=1);
void vmm_page_fault_handler(int,isr_regs*);
void vmm_checkstack();

#include "vmm_pagedir.hpp"

void vmm_pagedir::init(uint32_t *dir){
	pagedir=dir;
	phys_addr=(uint32_t)dir;
	curtable=(uint32_t*)&vmm_tableframe;
    amm_mark_free((uint32_t)curtable);
}

void vmm_pagedir::init(){
	curtable=(uint32_t*)&vmm_tableframe;
	if((uint32_t)curtable != ((uint32_t)curtable & VMM_ADDRESS_MASK)){
		dbgpf("VMM: Table frame at: %p\n", curtable);
		panic("VMM: Misaligned table frame!");
	}
	uint32_t *pdir = (uint32_t*)vmm_alloc(1, vmm_allocmode::Kernel);
	//pagedir=(uint32_t*)vmm_alloc(1, vmm_allocmode::Kernel);
	dbgpf("VMM: Pagedir at %p\n", pdir);
	if(!pdir) panic("(VMM) Failed to allocate page directory!");
	{
		interrupt_lock il;
		memset(pdir, 0, VMM_ENTRIES_PER_TABLE * sizeof(uint32_t));
	}
	dbgpf("VMM: Pagedir at %p\n", pdir);
	phys_addr = vmm_cur_pagedir->virt2phys(pdir);
	pagedir = pdir;
	dbgpf("VMM: pdir: %p pagdir: %p\n", pdir, pagedir);
}

void vmm_pagedir::maptable(uint32_t phys_addr){
	if((uint32_t)curtable != ((uint32_t)curtable & VMM_ADDRESS_MASK)){
		dbgpf("VMM: Table frame at: %p\n", curtable);
		panic("(VMM) Misaligned table frame!");
	}
	if(phys_addr != (phys_addr & VMM_ADDRESS_MASK)){
		panic("(VMM) Request to map misaligned table address!");
	}
    uint32_t virtpage=(uint32_t)curtable/VMM_PAGE_SIZE;
    uint32_t physpage=phys_addr/VMM_PAGE_SIZE;
    size_t tableindex=virtpage/VMM_ENTRIES_PER_TABLE;
    size_t tableoffset=virtpage-(tableindex * VMM_ENTRIES_PER_TABLE);
    uint32_t table=pagedir[tableindex] & VMM_ADDRESS_MASK;
	if(table != (uint32_t)&vmm_kinitable){
		dbgpf("VMM: %x != %p\n", table, &vmm_kinitable);
		panic("(VMM) Cannot map using non-identity-mapped page table.");
	}
	if((((uint32_t*)table)[tableoffset] & VMM_ADDRESS_MASK) != (physpage * VMM_PAGE_SIZE)){
		//dbgpf("VMM: Mapping table at physical %x to virtual %p using table %x.\n", phys_addr, curtable, table);
		((uint32_t*)table)[tableoffset]=(physpage*VMM_PAGE_SIZE) | (PageFlags::Present | PageFlags::Writable);
		vmm_refresh_addr(virtpage * VMM_PAGE_SIZE);
	}
}

void vmm_pagedir::add_table(size_t tableno, uint32_t *table){
	uint32_t tableflags=(TableFlags::Present | TableFlags::Writable);
	if(tableno >= VMM_KERNEL_TABLES) tableflags |= TableFlags::Usermode;
	pagedir[tableno]=(uint32_t)table | tableflags;
}

uint32_t vmm_pagedir::virt2phys(void *ptr, bool present){
	uint32_t ret;
	{
		hold_lock hl1(vmm_lock, false);
		{
			hold_lock hl2(vmm_framelock);
			interrupt_lock il;
			uint32_t pageno=(size_t)ptr/VMM_PAGE_SIZE;
			size_t tableindex=pageno/VMM_ENTRIES_PER_TABLE;
			size_t tableoffset=pageno-(tableindex * VMM_ENTRIES_PER_TABLE);
			uint32_t table=pagedir[tableindex];
			if(!(table & TableFlags::Present)) return 0;
			table &= VMM_ADDRESS_MASK;
			if(is_paging_enabled()){
				interrupt_lock il;
				maptable(table);
				ret=curtable[tableoffset];
			}else{
				ret=((uint32_t*)table)[tableoffset];
			}
			if(!(ret & PageFlags::Present) && present) return 0;
			ret &= VMM_ADDRESS_MASK;
		}
	}
	return ret;
}

size_t vmm_pagedir::find_free_virtpages(size_t pages, vmm_allocmode::Enum mode){
	size_t freecount=0;
	size_t startpage=0;
	size_t loopstart=1;
	size_t loopend=VMM_KERNEL_PAGES;

	if(mode & vmm_allocmode::Userlow){
		loopstart=VMM_KERNEL_PAGES;
		loopend=VMM_MAX_PAGES;
	}else if(mode & vmm_allocmode::Userhigh){
		loopstart=VMM_MAX_PAGES;
		loopend=VMM_KERNEL_PAGES;
	}
	if(loopstart < loopend){
		for(size_t i=loopstart; i<loopend; ++i){
			void *pageptr=(void*)(i*VMM_PAGE_SIZE);
			bool im = is_mapped(pageptr, false) ;
			bool gf = (get_flags((uint32_t)pageptr) & amm_flags::Do_Not_Use);
			if(!im && !gf){
				if(!startpage) startpage=i;
				freecount++;
			}else {
                startpage = 0;
                freecount = 0;
            }
			if(freecount==pages) return startpage;
		}
	}else{
		for(size_t i=loopstart; i>=loopend; --i){
			void *pageptr=(void*)(i*VMM_PAGE_SIZE);
			if(!is_mapped(pageptr, false) && !(get_flags((uint32_t)pageptr) & amm_flags::Do_Not_Use)){
				startpage = i;
				freecount++;
			}else{
				startpage=0;
                freecount=0;
			}
			if(freecount==pages) return startpage;
		}
	}
	return 0;
}

size_t vmm_pagedir::unmap_page(size_t virtpage){
    hold_lock hlv(vmm_lock, false);
	hold_lock hl(vmm_framelock);
	if(!pagedir) panic("(VMM) Invalid page directory!");
	//dbgpf("VMM: Unammping %x.\n", virtpage*VMM_PAGE_SIZE);
	size_t tableindex=virtpage/VMM_ENTRIES_PER_TABLE;
	size_t tableoffset=virtpage-(tableindex * VMM_ENTRIES_PER_TABLE);
	uint32_t table=pagedir[tableindex] & VMM_ADDRESS_MASK;
	if(!table){
		panic("(VMM) No table for allocation!");
	}
	maptable(table);
	uint32_t entry=curtable[tableoffset];
    uint32_t ret=entry & VMM_ADDRESS_MASK;
	curtable[tableoffset] = 0;//&=VMM_FLAGS_MASK;
	bool freetable=true;
	for(size_t i=0; i<VMM_ENTRIES_PER_TABLE; ++i){
		if(curtable[i]){
			freetable=false;
			break;
		}
	}
	if(freetable){
		dbgpf("VMM: Page table %i no longer needed.\n", (int)tableindex);
		pagedir[tableindex] = 0 ;//| TableFlags::Writable;
        amm_mark_free(table);
	}
	vmm_refresh_addr(virtpage * VMM_PAGE_SIZE);
	if(virtpage >= VMM_KERNEL_PAGES && (entry & PageFlags::Present)) userpagecount--;
	return ret/VMM_PAGE_SIZE;
}

void vmm_pagedir::destroy(){
    hold_lock hlv(vmm_lock, false);
	if(this==vmm_cur_pagedir){
		panic("VMM: Attempt to delete current page directory!");
	}
	for(size_t i=VMM_KERNEL_TABLES; i<VMM_ENTRIES_PER_TABLE; ++i){
		if(pagedir[i] & TableFlags::Present){
			hold_lock hl(vmm_framelock);
			uint32_t table=pagedir[i] & VMM_ADDRESS_MASK;
			maptable(table);
			for(size_t j=0; j<VMM_ENTRIES_PER_TABLE; ++j){
                if(curtable[j] & PageFlags::Present) amm_mark_free(curtable[j] & VMM_ADDRESS_MASK);
            }
			amm_mark_free(table);
		}
	}
	vmm_free((void*)pagedir, 1);
}

void vmm_pagedir::map_page(size_t virtpage, size_t physpage, bool alloc, vmm_allocmode::Enum mode){
    hold_lock hlv(vmm_lock, false);
	//dbgpf("VMM: Mapping %x (v) to %x (p).\n", virtpage*VMM_PAGE_SIZE, physpage*VMM_PAGE_SIZE);
    if(is_mapped((void*)(virtpage*VMM_PAGE_SIZE))) panic("(VMM) Remapping already mapped page!");
    uint32_t pageflags;
    if(mode & vmm_allocmode::NotPresent){
        pageflags = 0;
    }else {
        pageflags = (PageFlags::Present | PageFlags::Writable);
    }
	if(!(mode & vmm_allocmode::Kernel)) pageflags |= PageFlags::Usermode;
	if(!virtpage || !physpage) panic("(VMM) Attempt to map page/address 0!");
	if(!pagedir) panic("(VMM) Invalid page directory!");
	size_t tableindex=virtpage/VMM_ENTRIES_PER_TABLE;
	size_t tableoffset=virtpage-(tableindex * VMM_ENTRIES_PER_TABLE);
	uint32_t table=pagedir[tableindex] & VMM_ADDRESS_MASK;
	if(!table){
		if(alloc){
			table=amm_accounting_get_free_page();
            amm_accounting_mark_page(table, amm_page_type::PageTable, (void*)this);
			dbgpf("VMM: Creating new page table %i at %x (p)\n", (int)tableindex, (int)table);
			add_table(tableindex, (uint32_t*)table);
			if(is_paging_enabled()){
				maptable(table);
				memset(curtable, 0, VMM_PAGE_SIZE);
			}else{
				memset((void*)table, 0, VMM_PAGE_SIZE);
			}
		}else{
			panic("(VMM) Cannot allocate page table for mapping!");
		}
	}
	if(is_paging_enabled()){
		hold_lock hl(vmm_framelock);
		maptable(table);
		curtable[tableoffset]=(physpage*VMM_PAGE_SIZE) | pageflags;
	}else{
		((uint32_t*)table)[tableoffset]=(physpage*VMM_PAGE_SIZE) | pageflags;
	}
	vmm_refresh_addr(virtpage * VMM_PAGE_SIZE);
	if(mode != vmm_allocmode::Kernel && !(mode & vmm_allocmode::NotPresent)) userpagecount++;
}

void vmm_pagedir::set_flags(uint32_t pageaddr, amm_flags::Enum flags){
    hold_lock hlv(vmm_lock, false);
	uint32_t flagval = (uint32_t)flags & VMM_FLAGS_MASK;
	size_t virtpage=pageaddr/VMM_PAGE_SIZE;
	size_t tableindex=virtpage/VMM_ENTRIES_PER_TABLE;
    size_t tableoffset=virtpage-(tableindex * VMM_ENTRIES_PER_TABLE);
    uint32_t table=pagedir[tableindex] & VMM_ADDRESS_MASK;
    if(!table) return;
    {   hold_lock hl(vmm_framelock);
        maptable(table);
        curtable[tableoffset] |= flagval;
    }
}

amm_flags::Enum vmm_pagedir::get_flags(uint32_t pageaddr){
	size_t virtpage=pageaddr/VMM_PAGE_SIZE;
	size_t tableindex=virtpage/VMM_ENTRIES_PER_TABLE;
    size_t tableoffset=virtpage-(tableindex * VMM_ENTRIES_PER_TABLE);
    uint32_t table=pagedir[tableindex] & VMM_ADDRESS_MASK;
    if(!table) return amm_flags::Normal;
    {   hold_lock hl(vmm_framelock);
        maptable(table);
        return (amm_flags::Enum)(curtable[tableoffset] & VMM_FLAGS_MASK);
    }
}

bool vmm_pagedir::is_dirty(uint32_t pageaddr){
    hold_lock hl(vmm_framelock);
    uint32_t pageno=pageaddr/VMM_PAGE_SIZE;
    size_t tableindex=pageno/VMM_ENTRIES_PER_TABLE;
    size_t tableoffset=pageno-(tableindex * VMM_ENTRIES_PER_TABLE);
    uint32_t table=pagedir[tableindex];
    if(!(table & TableFlags::Present)) return false;
    table &= VMM_ADDRESS_MASK;
    maptable(table);
    uint32_t ret=curtable[tableoffset];
    if(!(ret & PageFlags::Present)) return false;
    return ret & PageFlags::Dirty;
}

vmm_pagedir *vmm_cur_pagedir, vmm_kernel_pagedir;

char *freemem_infofs(){
	char *buffer=(char*)malloc(512);
    memset(buffer, 0, 512);
    size_t freemem= amm_accounting_count_free_pages() * VMM_PAGE_SIZE;
    sprintf(buffer, "%i\n", (int)freemem);
    return buffer;
}

char *totalmem_infofs(){
	char *buffer=(char*)malloc(512);
    memset(buffer, 0, 512);
    sprintf(buffer, "%i\n", (int)vmm_totalmem);
    return buffer;
}

char *totalused_infofs(){
	char *buffer=(char*)malloc(512);
    memset(buffer, 0, 512);
    size_t used=0;
    for(size_t i=0; i<VMM_MAX_PAGES; ++i){
       	if(vmm_cur_pagedir->is_mapped((void*)(i*VMM_PAGE_SIZE))) used+=VMM_PAGE_SIZE;
    }
    sprintf(buffer, "%i\n", (int)used);
    return buffer;
}

void vmm_init(multiboot_info_t *mbt){
	multiboot_info = mbt;
	init_lock(vmm_lock);
	init_lock(vmm_framelock);
	dbgout("VMM: Init\n");
	memory_map_t *mmap = (memory_map_t*)mbt->mmap_addr;
	size_t k_first_page=((size_t)&_start/VMM_PAGE_SIZE);
	size_t k_last_page=((size_t)&_end/VMM_PAGE_SIZE);
	dbgpf("VMM: Kernel start: %p (page %x) end: %p (page %x).\n", &_start,
		(int)k_first_page, &_end, (int)k_last_page);
	size_t cregion=0;
	vmm_totalmem=0;
    while(mmap < (memory_map_t*)mbt->mmap_addr + mbt->mmap_length) {
		if(mmap->type == 1 && mmap->length_low > 0){
			dbgpf("VMM: Usable region base: 0x%x pages: %u\n", (int)mmap->base_addr_low, (unsigned)(mmap->length_low/VMM_PAGE_SIZE));
			if(mmap->base_addr_low < 1024*1024 && mmap->length_low < 1024*1024){
				dbgpf("VMM: Ignoring low 1MB RAM\n");
			}else{
				vmm_totalmem+=mmap->length_low;
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
    			//void* phys_page_addr=(void*)(phys_page_num*VMM_PAGE_SIZE);
    			if(phys_page_num < 256) panic("(VMM) Page number too low!");
    			if(phys_page_num>=k_first_page && phys_page_num<=k_last_page){
    				dbgpf("VMM: Region %i, page %i (%x) - KERNEL\n", (int)i, (int)j, (int)phys_page_num);
    			}else{
    				//memset(phys_page_addr, 0, VMM_PAGE_SIZE);
    				++totalpages;
    			}
    		}
    	}else break;
    }
    dbgpf("VMM: Total pages: %i\n", (int)totalpages);
    printf("VMM: Total RAM: %iKB\n", (int)(vmm_totalmem/1024));
   	dbgpf("VMM: Initializing kernel page directory at %x.\n", (int)vmm_kpagedir);
	for(size_t i=0; i<VMM_ENTRIES_PER_TABLE; ++i){
		vmm_kpagedir[i]=0 | TableFlags::Writable;
	}
	dbgpf("VMM: Initializing initial page table at %x.\n", (int)vmm_kinitable);
	memset((void*)vmm_kinitable, 0, VMM_PAGE_SIZE);
	vmm_kernel_pagedir.init(vmm_kpagedir);
	vmm_kernel_pagedir.add_table(0, vmm_kinitable);
    dbgpf("VMM: Init accounting...\n");
    size_t firstfreepage=init_amm_page_accounting(vmm_regions, (void*)&_end);
	size_t kernel_ends_at_page = firstfreepage;
	dbgout("VMM: Finding end of modules...\n");
	for(size_t i = 0; i<mbt->mods_count; ++i){
		module_t *mod = (module_t*)(mbt->mods_addr + (sizeof(module_t) * i));
		size_t firstpage = mod->mod_start & VMM_ADDRESS_MASK;
		size_t lastpage = mod->mod_end & VMM_ADDRESS_MASK;
		dbgpf("VMM: Module at %x - %x\n", (int)firstpage, (int)lastpage);
		if(lastpage > firstfreepage) firstfreepage = lastpage;
	}
    dbgpf("VMM: First free page: %x\n", (int)firstfreepage);
    dbgpf("VMM: Setting up kernel identity mappings.\n");
    for(size_t i=1; i<kernel_ends_at_page; ++i){
    	vmm_kernel_pagedir.identity_map(i, false);
    }
    int_handle(0x0e, &vmm_page_fault_handler);
    dbgout("VMM: Enabing paging...");
    asm volatile("mov %0, %%cr3":: "b"(vmm_kpagedir));
    unsigned int cr0;
    asm volatile("mov %%cr0, %0": "=b"(cr0));
    cr0 |= PAGING_ENABLED_FLAG;
    asm volatile("mov %0, %%cr0":: "b"(cr0));
    dbgout("Done.\n");
	dbgout("VMM: Identity mapping modules...\n");
	for(size_t i = 0; i<mbt->mods_count; ++i){
		module_t *mod = (module_t*)(mbt->mods_addr + (sizeof(module_t) * i));
		size_t firstpage = mod->mod_start & VMM_ADDRESS_MASK;
		size_t lastpage = mod->mod_end & VMM_ADDRESS_MASK;
		dbgpf("VMM: Module at %x - %x\n", (int)firstpage, (int)lastpage);
		for(size_t page = firstpage; page <= lastpage; page+=VMM_PAGE_SIZE){
			vmm_kernel_pagedir.identity_map(page / VMM_PAGE_SIZE, false);
			vmm_kernel_pagedir.set_flags(page, amm_flags::Kernel);
		}
	}
	dbgout("VMM: Done\n");
    vmm_cur_pagedir=&vmm_kernel_pagedir;
    dbgout("VMM: Init complete.\n");
    dbgout("VMM: Init AMM...\n");
    amm_init();
    dbgout("VMM: Accouting for kernel pages...\n");
    vmm_cur_pagedir->set_flags(0, amm_flags::Guard_Page);
    for(size_t i=1; i<VMM_KERNEL_PAGES; ++i){
        void *pageptr=(void*)(i*VMM_PAGE_SIZE);
        if(vmm_cur_pagedir->is_mapped(pageptr)){
            dbgpf("VMM: Marking page %x\n", (int)pageptr);
            amm_mark_alloc(vmm_cur_pagedir->virt2phys(pageptr), amm_page_type::Kernel, NULL);
            vmm_cur_pagedir->set_flags((i*VMM_PAGE_SIZE), amm_flags::Kernel);
			kmem+=VMM_PAGE_SIZE;
        }
    }
    infofs_register("FREEMEM", &freemem_infofs);
    infofs_register("TOTALMEM", &totalmem_infofs);
    infofs_register("ACTIVEMEM", &totalused_infofs);
}

bool is_paging_enabled(){
    unsigned int cr0;
    asm volatile("mov %%cr0, %0": "=b"(cr0));
    return cr0 & PAGING_ENABLED_FLAG;
}

void vmm_page_fault_handler(int, isr_regs *regs){
	uint32_t addr;
	asm volatile("mov %%cr2, %%eax\r\n mov %%eax,%0": "=m"(addr): : "eax");
	dbgpf("VMM: Page fault on %x at %x!\n", addr, regs->eip);
	if(addr < VMM_PAGE_SIZE) panic("(VMM) Probable NULL pointer dereference!");
	else panic("(VMM) Page fault!");
}

void vmm_refresh_addr(uint32_t pageaddr){
	asm volatile("invlpg (%0)" ::"r" (pageaddr) : "memory");
}

void *vmm_alloc(size_t pages, vmm_allocmode::Enum mode){
	hold_lock hl(vmm_lock, false);
	size_t virtpage=vmm_cur_pagedir->find_free_virtpages(pages, mode);
	if(!virtpage) return NULL;
	for(size_t i=0; i<pages; ++i){
        amm_page_type::Enum page_type;
        if(mode == vmm_allocmode::Kernel){
            page_type=amm_page_type::Kernel;
        }else{
            page_type=amm_page_type::Userspace;
        }
		uint32_t phys_page= amm_accounting_get_free_page();
        amm_mark_alloc(phys_page, page_type, mode==vmm_allocmode::Kernel?NULL:proc_current_process);
        phys_page/=VMM_PAGE_SIZE;
		if(!phys_page){
		    dbgpf("VMM: Allocation of %i pages failed.\n", (int)pages);
            panic("(VMM) Out of memory!");
		    return NULL;
		}
		vmm_cur_pagedir->map_page(virtpage+i, phys_page, true, mode);
    }
	void *ret=(void*)(virtpage*VMM_PAGE_SIZE);
	memset(ret, 0xaa, pages*VMM_PAGE_SIZE);
	if(mode==vmm_allocmode::Kernel) kmem+=pages*VMM_PAGE_SIZE;
	return ret;
}

void *vmm_alloc_at(size_t pages, size_t baseaddr){
	//dbgpf("VMM: Allocating %i pages at %x\n", pages, baseaddr);
	hold_lock hl(vmm_lock, false);
	size_t virtpage=baseaddr/VMM_PAGE_SIZE;
	for(size_t i=0; i<pages; ++i){
		if(vmm_cur_pagedir->is_mapped((void*)((virtpage+i)*VMM_PAGE_SIZE))) continue;
        vmm_allocmode::Enum mode = ((virtpage+i)*VMM_PAGE_SIZE < VMM_KERNELSPACE_END)?
                vmm_allocmode::Kernel : vmm_allocmode::Userlow;
        amm_page_type::Enum page_type;
        if(mode == vmm_allocmode::Kernel){
            page_type=amm_page_type::Kernel;
        }else{
            page_type=amm_page_type::Userspace;
        }
        uint32_t phys_page= amm_accounting_get_free_page();
        amm_mark_alloc(phys_page, page_type, mode==vmm_allocmode::Kernel?NULL:proc_current_process);
        phys_page/=VMM_PAGE_SIZE;
		if(!phys_page){
			dbgpf("VMM: Allocation of %i pages failed.\n", (int)pages);
			return NULL;
		}
        vmm_cur_pagedir->map_page(virtpage+i, phys_page, true, mode);
		if(mode==vmm_allocmode::Kernel) kmem+=VMM_PAGE_SIZE;
		memset((void*)((virtpage+i)*VMM_PAGE_SIZE), 0xaa, VMM_PAGE_SIZE);
	}
	return (void*)baseaddr;
}

void vmm_free(void *ptr, size_t pages){
	hold_lock hl(vmm_lock, false);
	if((uint32_t)ptr != ((uint32_t)ptr & VMM_ADDRESS_MASK)) panic("(VMM) Attempt to free misaligned page!");
	memset(ptr, 0xfe, pages * VMM_PAGE_SIZE);
	size_t virtpage=(uint32_t)ptr/VMM_PAGE_SIZE;
	for(size_t i=0; i<pages; ++i){
		size_t physpage=vmm_cur_pagedir->unmap_page(virtpage+i);
		amm_mark_free((physpage)*VMM_PAGE_SIZE);
		if((virtpage)*VMM_PAGE_SIZE < VMM_KERNELSPACE_END) kmem-=VMM_PAGE_SIZE;
	}
}

void vmm_activate_pagedir(vmm_pagedir *pagedir){
	uint32_t dir=pagedir->getphys();
	if(!dir) panic("VMM: Invalid page directory!");
	disable_interrupts();
	asm volatile("mov %0, %%cr3":: "b"(dir));
    enable_interrupts();
}

void vmm_switch(vmm_pagedir *dir){
	if(dir!=vmm_cur_pagedir){
		vmm_kernel_pagedir.copy_kernelspace(vmm_cur_pagedir);
		dir->copy_kernelspace(vmm_cur_pagedir);
		vmm_cur_pagedir=dir;
		vmm_activate_pagedir(vmm_cur_pagedir);
	}
}

vmm_pagedir *vmm_newpagedir(){
	interrupt_lock il;
	vmm_pagedir *ret=new vmm_pagedir();
	ret->init();
	ret->copy_kernelspace(vmm_cur_pagedir);
	return ret;
}

void vmm_deletepagedir(vmm_pagedir *dir){
	dir->destroy();
	delete dir;
}

size_t vmm_getusermemory(vmm_pagedir *dir){
	if(dir)	return dir->getuserpagecount() * VMM_PAGE_SIZE;
	else return 0;
}

size_t vmm_getkernelmemory(){
	return kmem;
}

size_t vmm_gettotalmem(){
    return vmm_totalmem;
}

void vmm_set_flags(uint32_t pageaddr, amm_flags::Enum flags){
    vmm_cur_pagedir->set_flags(pageaddr, flags);
}

amm_flags::Enum vmm_get_flags(uint32_t pageaddr){
    return vmm_cur_pagedir->get_flags(pageaddr);
}

uint32_t vmm_physaddr(void *ptr){
    uint32_t offset=(uint32_t)ptr & ~VMM_ADDRESS_MASK;
    return vmm_cur_pagedir->virt2phys(ptr) | offset;
}

multiboot_info_t *vmm_get_multiboot(){
	return multiboot_info;
}

void vmm_debug_check(){
	//Don't run this on a running system...
	init_lock(vmm_lock);
	for(size_t i=0; i<VMM_MAX_PAGES; ++i){
		uint32_t physaddr = vmm_cur_pagedir->virt2phys((void*)(i * VMM_PAGE_SIZE));
		if(physaddr){
			for(size_t j=0; j<VMM_MAX_PAGES; ++j){
				if(i != j && vmm_cur_pagedir->virt2phys((void*)(j * VMM_PAGE_SIZE)) == physaddr){
					dbgpf("VMM: Pages %i and %i are both mapped to %x.\n", (int)i, (int)j, (int)physaddr);
				}
			}
		}
	}
	dbgout("VMM: Debug check complete.\n");
}