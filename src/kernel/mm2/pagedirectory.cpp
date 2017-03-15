#include "../kernel.hpp"
#include "../locks.hpp"
#include "mm2_internal.hpp"
#include "pagedirectory.hpp"

namespace MM2{
	
	static lock kdir_lock;
	static uint32_t table_frame[MM2_Table_Entries] __attribute__((aligned(0x1000)));
	size_t PageDirectory::kpages;

	bool PageDirectory::map_table(uint32_t tableaddr){
		if((tableaddr & MM2_Address_Mask) == 0) return false;
		tableaddr = tableaddr & MM2_Address_Mask;
		size_t framepageidx = (uint32_t)&table_frame / MM2_Page_Size;
		size_t frametableno = framepageidx / MM2_Table_Entries;
		size_t framepageno = framepageidx % MM2_Table_Entries;
		if(directory[frametableno] & MM2_TableFlags::Present){
			uint32_t *frametable = (uint32_t*)(directory[frametableno] & MM2_Address_Mask);
			frametable[framepageno] = tableaddr | MM2_PageFlags::Present | MM2_PageFlags::Writable;
			mm2_invlpg(&table_frame);
			current_table = tableaddr;
			return true;
		}else return false;
	}

	PageDirectory::PageDirectory(){
		directory_lock = new lock();
		init_lock(*directory_lock);
		directory = (uint32_t*)mm2_virtual_alloc(1);
		memset(directory, 0, MM2_Page_Size);
		directory_physical = MM2::current_pagedir->virt2phys(directory);
		dbgpf("MM2: Creating new page directory at %p.\n", (void*)directory);
		regions = new vector<region>();
		for(size_t i = 0; i < entrycache_size; ++i){
			entrycache[i].entry = 0;
		}
	}

	PageDirectory::~PageDirectory(){
		if(this == current_pagedir) panic("(MM2) Attempt to delete current page directory!");
		dbgpf("MM2: Deleing page directory %p (directory: %p).\n", (void*)this, (void*)directory);
		{
			hold_lock hl(*directory_lock);
			for(size_t i = MM2_Kernel_Tables; i < MM2_Table_Entries; ++i){
				hold_lock hl(table_frame_lock);
				if(map_table(directory[i])){
					for(size_t j = 0; j < MM2_Table_Entries; ++j){
						if(table_frame[j] & MM2_TableFlags::Present){
							physical_free(table_frame[j] & MM2_Address_Mask);
							table_frame[j] = 0;
						}
					}
					physical_free(directory[i] & MM2_Address_Mask);
					directory[i] = 0;
				}
			}
			mm2_virtual_free((void*)directory, 1);
		}
		delete directory_lock;
	}

	PageDirectory::PageDirectory(uint32_t *a){
		directory_lock = &kdir_lock;
		init_lock(*directory_lock);
		directory = a;
		directory_physical = (uint32_t)a;
		regions = NULL;
	}

	void *PageDirectory::alloc(size_t pages, uint32_t mode){
		hold_lock hl(*directory_lock);
		void *virtual_addr = NULL;
		if(mode & MM2_Alloc_Mode::Kernel || mode & MM2_Alloc_Mode::Userlow){
			uint32_t startpage = klowfree;
			if(mode & MM2_Alloc_Mode::Userlow) startpage = ulowfree;
			size_t found = 0;
			size_t firstpage = 0;
			for(uint32_t pageno = startpage; pageno < MM2_Total_Pages; ++pageno){
				if(is_available(pageno)){
					if(!firstpage) firstpage = pageno;
					++found;
				}else{
					if(pages == 1 && (mode & MM2_Alloc_Mode::Kernel)) klowfree = pageno; 
					if(pages == 1 && (mode & MM2_Alloc_Mode::Userlow)) ulowfree = pageno;
					firstpage = 0;
					found = 0;
				}
				if(found == pages){
					virtual_addr = (void*)(firstpage * MM2_Page_Size);
					break;
				}
			}
		}else{
			panic("(MM2) Allocation mode not implemented!");
		}
		
		if(virtual_addr){
			for(size_t page = 0; page < pages; ++page){
				void *page_addr = (void*)((uint32_t)virtual_addr + (page * MM2_Page_Size));
				map_page_at(page_addr, MM2_PageFlags::Present | MM2_PageFlags::Writable | MM2_PageFlags::Usermode);
			}
			//dbgpf("MM2: Allocated %i pages at %p.\n", (int)pages, virtual_addr);
		}else{
			dbgpf("MM2: Failed to allocate %i pages!\n", (int)pages);
		}
		return virtual_addr;
	}

	void PageDirectory::alloc_pages_at(size_t pages, void *baseaddr){
		hold_lock hl(*directory_lock, false);
		uint32_t flags = MM2_PageFlags::Present | MM2_PageFlags::Writable;
		if((uint32_t)baseaddr >= MM2_Kernel_Boundary) flags |= MM2_PageFlags::Usermode;
		for(size_t page = 0; page < pages; ++page){
			void *page_addr = (void*)((uint32_t)baseaddr + (page * MM2_Page_Size));
			map_page_at(page_addr, flags);
		}
	}

	uint32_t PageDirectory::get_table_entry(size_t pageindex){
		hold_lock hl(*directory_lock, false);
		uint32_t ret = entrycache_get(pageindex);
		if(ret == 0){
			size_t tableno = pageindex / MM2_Table_Entries;
			size_t pageno = pageindex % MM2_Table_Entries;
			
			{
				hold_lock hl(table_frame_lock);
				if((directory[tableno] & MM2_Address_Mask) && map_table(directory[tableno])){
					ret = table_frame[pageno];
				}
			}
			entrycache_set(pageindex, ret);
		}
		//dbgpf("MM2: Getting page table entry %i (%x) value: %x.\n", (int)pageindex, (unsigned)(pageindex * MM2_Page_Size), ret);
		return ret;
	}
	
	void PageDirectory::set_table_entry(size_t pageindex, uint32_t entry){
		//dbgpf("MM2: Setting page table entry %i (%x) to %x.\n", (int)pageindex, (unsigned)(pageindex * MM2_Page_Size), entry);
		hold_lock hl(*directory_lock, false);
		size_t tableno = pageindex / MM2_Table_Entries;
		size_t pageno = pageindex % MM2_Table_Entries;
		
		{
			hold_lock hl(table_frame_lock);
			if(!(directory[tableno] && MM2_PageFlags::Present) || !map_table(directory[tableno])){
				dbgpf("MM2: Creating page table %i.\n", (int)tableno);
				create_table(tableno);
				map_table(directory[tableno]);
				memset(table_frame, 0, MM2_Page_Size);
			}
			table_frame[pageno] = entry;
		}
		entrycache_clear(pageindex);
	}
	
	uint32_t PageDirectory::entrycache_get(size_t pageindex){
		for(size_t i = 0; i < entrycache_size; ++i){
			if(entrycache[i].index == pageindex){
				if(entrycache[i].hits < entrycache_maxhits) entrycache[i].hits++;
				return entrycache[i].entry;
			}
		}
		return 0;
	}
	
	void PageDirectory::entrycache_set(size_t pageindex, uint32_t entry){
		if(entry == 0) return;
		size_t pos = 0;
		for(size_t i = 0; i < entrycache_size; ++i){
			if(entrycache[i].hits < entrycache[pos].hits) pos = i;
		}
		entrycache[pos].index = pageindex;
		entrycache[pos].entry = entry;
		entrycache[pos].hits = 0;
	}
	
	void PageDirectory::entrycache_clear(size_t pageindex){
		for(size_t i = 0; i < entrycache_size; ++i){
			if(entrycache[i].index == pageindex){
				entrycache[i].index = 0;
				entrycache[i].entry = 0;
				entrycache[i].hits = 0;
			}
		}
	}

	uint32_t PageDirectory::virt2phys(void *addr){
		hold_lock hl(*directory_lock, false);
		uint32_t entry = get_table_entry((uint32_t)addr / MM2_Page_Size);
		entry &= MM2_Address_Mask;
		if(entry) entry += (uint32_t)addr & ~MM2_Address_Mask;
		return entry;
	}
	
	bool PageDirectory::is_available(uint32_t pageno){
		hold_lock hl(*directory_lock, false);
		uint32_t entry = get_table_entry(pageno);
		bool ret = !(entry & MM2_PageFlags::Present) && !(entry & MM2_PageFlags::Do_Not_Use);
		return ret;
	}
	
	size_t PageDirectory::resolve_addr(void *addr){
		handle_pf(addr);
		hold_lock hl(*directory_lock);
		uint32_t physaddr = virt2phys(addr);
		size_t ret = 0;
		if(physaddr) {
			ret = physaddr % MM2_Page_Size;
			if(ret == 0) ret = MM2_Page_Size;
		}
		return ret;
	}


	void PageDirectory::map_page_at(void *addr, physical_page *page, uint32_t flags){
		hold_lock hl(*directory_lock, false);
		uint32_t entry = page->address() | flags;
		set_table_entry((uint32_t)addr / MM2_Page_Size, entry);
		mm2_invlpg(addr);
		if((uint32_t)addr > MM2_Kernel_Boundary){
			++upages;
		}else{
			++kpages;
		}
	}
	
	void PageDirectory::map_page_at(void *addr, uint32_t flags){
		addr = (void*)((uint32_t)addr & MM2_Address_Mask);
		hold_lock hl(*directory_lock, false);
		physical_page *page = physical_alloc();
		map_page_at(addr, page, flags);
		//dbgpf("MM2: Zeroing page at %p.\n", addr);
		memset(addr, 0, MM2_Page_Size);
	}
	
	void PageDirectory::create_table(size_t tableno){
		physical_page *page = physical_alloc();
		dbgpf("MM2: Creating table %i at %x.\n", (int)tableno, (uint32_t)page->address());
		uint32_t flags = MM2_TableFlags::Present | MM2_TableFlags::Writable;
		if(tableno >= MM2_Kernel_Tables) flags |= MM2_TableFlags::Usermode;
		directory[tableno] = page->address() | flags;
		{
			hold_lock hl(table_frame_lock, false);
			uint32_t last_table = current_table;
			map_table(page->address());
			memset(table_frame, 0, MM2_Page_Size);
			if(last_table) map_table(last_table);
		}
	}
	
	void PageDirectory::copy_kernelspace(const PageDirectory &pdir){
		if(!directory) panic("(MM2) Copy to NULL page directory.");
		if(!&pdir) panic("(MM2) Copy from NULL object.");
		if(!pdir.directory) panic("(MM2) Copy from NULL page directory.");
    	memcpy(directory, pdir.directory, MM2_Kernel_Tables * sizeof(uint32_t));
		klowfree = pdir.klowfree;
	}
	
	size_t PageDirectory::get_kernel_used(){
		return kpages * MM2_Page_Size;
	}
	
	size_t PageDirectory::get_user_used(){
		return upages * MM2_Page_Size;
	}
	
	void PageDirectory::guard_page_at(void *ptr){
		hold_lock hl(*directory_lock);
		//dbgpf("MM2: Setting guard page at %p.\n", ptr);
		size_t pageno = (uint32_t)ptr / MM2_Page_Size;
		size_t entry = get_table_entry(pageno);
		if(entry & MM2_PageFlags::Present){
			free_pages(ptr, 1);
			entry = get_table_entry(pageno);
		}
		entry |= MM2_PageFlags::Guard_Page;
		set_table_entry(pageno, entry);
		mm2_invlpg(ptr);
	}
	
	void PageDirectory::free_pages(void *addr, size_t pages){
		//dbgpf("MM2: Freeing %i pages at %p.\n", (int)pages, addr);
		hold_lock hl(*directory_lock);
		for(size_t i = 0; i < pages; ++i){
			uint32_t pageaddr = (uint32_t)addr + (i * MM2_Page_Size);
			uint32_t pageno = pageaddr / MM2_Page_Size;
			if(pageno < MM2_Kernel_Pages && pageno < klowfree) klowfree = pageno;
			else if(pageno >= MM2_Kernel_Pages && pageno < ulowfree) ulowfree = pageno;
			uint32_t entry = get_table_entry(pageno);
			if(entry & MM2_PageFlags::Present){
				physical_free(entry & MM2_Address_Mask);
			}
			set_table_entry(pageno, 0);
			if(pageaddr > MM2_Kernel_Boundary){
				--upages;
			}else{
				--kpages;
			}
			mm2_invlpg((void*)pageaddr);
		}
	}
	
	void PageDirectory::activate(){
		asm volatile("mov %0, %%cr3":: "b"(directory_physical));
	}
	
	void PageDirectory::add_region(void *addr, size_t size, void (*pf_handle)(uint64_t id, void *addr), uint64_t id){
		region r;
		r.addr = addr;
		r.size = size;
		r.pf_handle = pf_handle;
		r.id = id;
		regions->push_back(r);
	}
	
	void PageDirectory::remove_region(void *addr){
		for(size_t i = 0; i < regions->size(); ++i){
			region &r = (*regions)[i];
			if(r.addr == addr){
				regions->erase(i);
				return;
			}
		}
	}
	
	bool PageDirectory::handle_pf(void *addr){
		if(is_mapped(addr)) return false;
		if(!regions) return false;
		for(size_t i = 0; i < regions->size(); ++i){
			region &r = (*regions)[i];
			if(r.addr <= addr && (char*)r.addr + r.size > addr){
				//dbgpf("MM2: PF at %p is in region %p; handling with %p (id %i).\n", addr, r.addr, (void*)r.pf_handle, (int)r.id);
				r.pf_handle(r.id, addr);
				return true;
			}
		}
		return false;
	}
	
	void PageDirectory::kernel_pagedir_late_init(){
		if(!regions){
			regions = new vector<region>();
			for(size_t i = 0; i < MM2_Kernel_Tables; ++i){
				hold_lock hl(table_frame_lock);
				if(map_table(directory[i])){
					for(size_t j = 0; j < MM2_Table_Entries; ++j){
						if(table_frame[j] & MM2_TableFlags::Present) ++kpages;
					}
				}
			}
		}
	}
}
