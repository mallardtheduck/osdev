#include "../kernel.hpp"
#include "../locks.hpp"
#include "mm2_internal.hpp"
#include "pagedirectory.hpp"

namespace MM2{
	
	static lock kdir_lock;
	static uint32_t table_frame[MM2_Table_Entries] __attribute__((aligned(0x1000)));

	bool PageDirectory::map_table(uint32_t tableaddr){
		tableaddr = tableaddr & MM2_Address_Mask;
		size_t framepageidx = (uint32_t)&table_frame / MM2_Page_Size;
		size_t frametableno = framepageidx / MM2_Table_Entries;
		size_t framepageno = framepageidx % MM2_Table_Entries;
		if(directory[frametableno] & MM2_TableFlags::Present){
			uint32_t *frametable = (uint32_t*)(directory[frametableno] & MM2_Address_Mask);
			frametable[framepageno] = tableaddr | MM2_PageFlags::Present | MM2_PageFlags::Writable;
			mm2_invlpg(&table_frame);
			return true;
		}else return false;
	}

	PageDirectory::PageDirectory(){
		directory_lock = new lock();
		init_lock(*directory_lock);
		directory = (uint32_t*)mm2_virtual_alloc(1);
	}

	PageDirectory::~PageDirectory(){
		delete directory_lock;
		//TODO: Deallocate memory!
	}

	PageDirectory::PageDirectory(uint32_t *a){
		directory_lock = &kdir_lock;
		init_lock(*directory_lock);
		directory = a;
	}

	void *PageDirectory::alloc(size_t pages, uint32_t mode){
		void *virtual_addr = NULL;
		if(mode & MM2_Alloc_Mode::Kernel || mode & MM2_Alloc_Mode::Userlow){
			uint32_t startpage = 0;
			if(mode & MM2_Alloc_Mode::Userlow) startpage = MM2_Boundary_Page;
			size_t found = 0;
			for(uint32_t pageno = startpage; pageno < 0xFFFFFFFF; ++pageno){
				if(is_available(pageno)) ++found;
				else found = 0;
				if(found == pages){
					virtual_addr = (void*)(pageno * MM2_Page_Size);
					break;
				}
			}
		}else{
			panic("(MM2) Allocation mode not implemented!");
		}
		
		if(virtual_addr){
			for(size_t page = 0; page < pages; ++page){
				void *page_addr = (void*)((uint32_t)virtual_addr + (page * MM2_Page_Size));
				map_page_at(page_addr);
			}
		}
		return virtual_addr;
	}

	void PageDirectory::alloc_pages_at(size_t pages, void *baseaddr){
		for(size_t page = 0; page < pages; ++page){
			void *page_addr = (void*)((uint32_t)baseaddr + (page * MM2_Page_Size));
			map_page_at(page_addr);
		}
	}

	uint32_t PageDirectory::get_table_entry(size_t pageindex){
		uint32_t ret = 0;
		size_t tableno = pageindex / MM2_Table_Entries;
		size_t pageno = pageindex % MM2_Table_Entries;
		
		{
			hold_lock hl(table_frame_lock);
			if(map_table(directory[tableno]) && (table_frame[pageno] & MM2_PageFlags::Present)){
				ret = table_frame[pageno];
			}
		}
		return ret;
	}
	
	void  PageDirectory::set_table_entry(size_t pageindex, uint32_t entry){
		size_t tableno = pageindex / MM2_Table_Entries;
		size_t pageno = pageindex % MM2_Table_Entries;
		
		{
			hold_lock hl(table_frame_lock);
			if(!map_table(directory[tableno])){
				create_table(tableno);
				map_table(directory[tableno]);
			}
			table_frame[pageno] = entry;
		}
	}

	uint32_t PageDirectory::virt2phys(void *addr){
		uint32_t entry = get_table_entry((uint32_t)addr / MM2_Page_Size);
		entry &= MM2_Address_Mask;
		entry += (uint32_t)addr & ~MM2_Address_Mask;
		return entry;
	}
	
	bool PageDirectory::is_available(uint32_t pageno){
		uint32_t entry = get_table_entry(pageno);
		return !(entry & MM2_PageFlags::Present) && !(entry & MM2_PageFlags::Do_Not_Use);
	}
	
	size_t PageDirectory::resolve_addr(void *addr){
		uint32_t physaddr = virt2phys(addr);
		return physaddr % MM2_Page_Size;
	}


	void PageDirectory::map_page_at(void *addr, physical_page *page, uint32_t flags){
		uint32_t entry = page->address | flags;
		set_table_entry((uint32_t)addr / MM2_Page_Size, entry);
		mm2_invlpg(addr);
	}
	
	void PageDirectory::map_page_at(void *addr, uint32_t flags){
		physical_page *page = physical_alloc();
		map_page_at(addr, page, flags);
	}
	
	void PageDirectory::create_table(size_t tableno){
		physical_page *page = physical_alloc();
		directory[tableno] = page->address | MM2_TableFlags::Present | MM2_TableFlags::Writable;
	}
	
	void PageDirectory::copy_kernelspace(const PageDirectory &pdir){
		if(!directory) panic("(MM2) Copy to NULL page directory.");
		if(!&pdir) panic("(MM2) Copy from NULL object.");
		if(!pdir.directory) panic("(MM2) Copy from NULL page directory.");
    	memcpy(directory, pdir.directory, MM2_Kernel_Tables * sizeof(uint32_t));
	}
	
	size_t PageDirectory::get_kernel_used(){
		size_t ret = 0;
		for(size_t i = 0; i < MM2_Kernel_Tables; ++i){
			hold_lock hl(table_frame_lock);
			if(map_table(directory[i])){
				for(size_t j = 0; j < MM2_Table_Entries; ++j){
					if(table_frame[j] & MM2_TableFlags::Present) ret += MM2_Page_Size;
				}
			}
		}
		return ret;
	}
	
	size_t PageDirectory::get_user_used(){
		size_t ret = 0;
		for(size_t i = MM2_Kernel_Tables; i < MM2_Table_Entries; ++i){
			hold_lock hl(table_frame_lock);
			if(map_table(directory[i])){
				for(size_t j = 0; j < MM2_Table_Entries; ++j){
					if(table_frame[j] & MM2_TableFlags::Present) ret += MM2_Page_Size;
				}
			}
		}
		return ret;
	}
	
	void PageDirectory::guard_page_at(void *ptr){
		size_t pageno = (uint32_t)ptr / MM2_Page_Size;
		size_t entry = get_table_entry(pageno);
		if(entry & MM2_PageFlags::Present){
			free_pages(ptr, 1);
			entry = get_table_entry(pageno);
		}
		entry |= MM2_PageFlags::Guard_Page;
	}
	
	void PageDirectory::free_pages(void *addr, size_t pages){
		for(size_t i = 0; i < pages; ++i){
			uint32_t pageaddr = (uint32_t)addr + (i * MM2_Page_Size);
			uint32_t pageno = pageaddr / MM2_Page_Size;
			uint32_t entry = get_table_entry(pageno);
			if(entry & MM2_PageFlags::Present){
				physical_free(entry & MM2_Address_Mask);
			}
			set_table_entry(pageno, 0);
			mm2_invlpg((void*)pageaddr);
		}
	}
	
	void PageDirectory::activate(){
		asm volatile("mov %0, %%cr3":: "b"(directory));
	}
}