#include "../kernel.hpp"
#include "../locks.hpp"
#include "mm2_internal.hpp"

extern "C" char _start, _end;

namespace MM2{
	vector<physical_page*> *io_pages = NULL;

	static char *end_of_kernel;
	static size_t total_pages;
	static physical_page *physical_pages;
	static size_t total_memory;
	static size_t free_pages;
	
	static lock mm2_pmm_lock;
	
	static char *totalmem_infofs(){
		char *ret = (char*)malloc(128);
		sprintf(ret, "%u", (unsigned)total_memory);
		return ret;
	}
	
	static char *freemem_infofs(){
		char *ret = (char*)malloc(128);
		sprintf(ret, "%u", (unsigned)(free_pages * MM2_Page_Size));
		return ret;
	}

	static void init_account(){
		for(size_t i = 0; i < total_pages; ++i){
			if(physical_pages[i].address() < (size_t)end_of_kernel) physical_pages[i].status(PageStatus::InUse);
		}
	}

	void *mm2_init_alloc(size_t size){
		void *ret = (void*)end_of_kernel;
		end_of_kernel += size;
		memset(ret, 0, size);
		if(physical_pages) init_account();
		return ret;
	}

	void *mm2_init_page_alloc(){
		if((uint32_t)end_of_kernel % MM2_Page_Size) end_of_kernel += MM2_Page_Size - ((uint32_t)end_of_kernel % MM2_Page_Size);
		return mm2_init_alloc(MM2_Page_Size);
	}

	void mm2_physical_init(multiboot_info_t *mbt){
		dbgout("MM2: Physical memory manager init.\n");
		physical_pages = NULL;
		end_of_kernel = &_end;
		total_pages = 0;
		
		for(size_t i = 0; i<mbt->mods_count; ++i){
			module_t *mod = (module_t*)(mbt->mods_addr + (sizeof(module_t) * i));
			dbgpf("VMM: Module at %x - %x\n", (int)mod->mod_start, (int)mod->mod_end);
			if(mod->mod_end > (uint32_t)end_of_kernel) end_of_kernel = (char*)mod->mod_end;
		}
		
		memory_map_t *mmap = (memory_map_t*)mbt->mmap_addr;
		while(mmap < (memory_map_t*)mbt->mmap_addr + mbt->mmap_length){
			if(mmap->type == 1 && mmap->length_low > 0){
				dbgpf("MM2: Usable region base: 0x%x pages: %u\n", (int)mmap->base_addr_low, (unsigned)(mmap->length_low/MM2_Page_Size));
				if(mmap->base_addr_low < 1024*1024 && mmap->length_low < 1024*1024){
					dbgpf("MM2: Ignoring low 1MB RAM\n");
				}else{
					total_pages+=mmap->length_low / MM2_Page_Size;
				}
			}
			mmap = (memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
		}
		
		total_memory = total_pages * MM2_Page_Size;
		free_pages = total_pages;
		dbgpf("MM2: PMM: %i pages (%i bytes RAM).\n", (int)total_pages, (int)total_memory);
		physical_pages = (physical_page*)mm2_init_alloc(sizeof(physical_page) * total_pages);
		
		dbgpf("MM2: PMM: physical_pages array at %x.\n", (uint32_t)physical_pages);
		size_t current_page = 0;
		
		mmap = (memory_map_t*)mbt->mmap_addr;
		while(mmap < (memory_map_t*)mbt->mmap_addr + mbt->mmap_length){
			if(mmap->type == 1 && mmap->length_low > 0){
				if(mmap->base_addr_low < 1024*1024 && mmap->length_low < 1024*1024){
					dbgpf("MM2: Ignoring low 1MB RAM\n");
				}else{
					for(size_t page_addr = mmap->base_addr_low; page_addr + MM2_Page_Size < mmap->length_low; page_addr+=MM2_Page_Size){
						physical_pages[current_page].address(page_addr);
						physical_pages[current_page].status(PageStatus::Free);
						++current_page;
					}
					dbgpf("MM2: Accounted region base: 0x%x pages: %u\n", (int)mmap->base_addr_low, (unsigned)(mmap->length_low/MM2_Page_Size));
				}
			}
			mmap = (memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
		}
		init_account();
		init_lock(mm2_pmm_lock);
	}

	physical_page *physical_alloc(size_t max_addr){
		hold_lock hl(mm2_pmm_lock);
		static size_t lastidx = 0;
		size_t idx = lastidx - 1;
		while(idx != lastidx){
			if(idx > total_pages) idx = total_pages - 1;
			if(physical_pages[idx].status() == PageStatus::Free && physical_pages[idx].address() < max_addr){
				physical_pages[idx].status(PageStatus::InUse);
				--free_pages;
				//dbgpf("MM2: Allocated physical page %p.\n", (void*)physical_pages[idx].address);
				lastidx = idx;
				return &physical_pages[idx];
			}
			--idx;
		}
		panic("(MM2) PYSICAL PAGE ALLOCATION FAILED!\n");
		return NULL; //OOM!
	}

	void physical_free(physical_page *page){
		hold_lock hl(mm2_pmm_lock, false);
		if(page->status() == PageStatus::InUse) page->status(PageStatus::Free);
		++free_pages;
	}
	
	static physical_page *find_page(uint32_t addr){
		if(io_pages){
			for(auto page : *io_pages){
				if(page->address() == addr) return page;
			}
		}
		int min = 0;
		int max = total_pages - 1;
		size_t guess = (min + max) / 2;
		while(physical_pages[guess].address() != addr){
			if(physical_pages[guess].address() < addr){
				min = guess + 1;
			}else{
				max = guess - 1;
			}
			guess = (min + max) / 2;
			if(max < min) return NULL;
		}
		return &physical_pages[guess];
	}

	void physical_free(uint32_t addr){
		hold_lock hl(mm2_pmm_lock);
		addr = addr & MM2_Address_Mask;
		physical_page *page = find_page(addr);
		if(page) physical_free(page);
	}

	void *get_kernel_end(){
		return (void*)end_of_kernel;
	}
	
	void physical_mark_used(uint32_t addr){
		addr = addr & MM2_Address_Mask;
		physical_page *page = find_page(addr);
		if(page){
			page->status(PageStatus::InUse);
		}
	}

	void physical_infofs_register(){
		infofs_register("TOTALMEM", &totalmem_infofs);
		infofs_register("FREEMEM", &freemem_infofs);
	}
	
	physical_page *physical_get_io_page(intptr_t addr){
		addr = addr & MM2_Address_Mask;
		physical_page *page = find_page(addr);
		if(!page){
			if(!io_pages) io_pages = new vector<physical_page*>();
			page = new physical_page(addr, PageStatus::MMIO);
			io_pages->push_back(page);
		}
		return page;
	}
}
