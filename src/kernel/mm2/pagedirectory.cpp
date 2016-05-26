#include "../kernel.hpp"
#include "../locks.hpp"
#include "mm2_internal.hpp"
#include "pagedirectory.hpp"

namespace MM2{

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
		init_lock(directory_lock);
	}

	PageDirectory::~PageDirectory()
	{
	}

	PageDirectory::PageDirectory(uint32_t *a){
		init_lock(directory_lock);
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
		}
		
		if(virtual_addr){
			for(size_t page = 0; page < pages; ++page){
				void *page_addr = (void*)((uint32_t)virtual_addr + (page * MM2_Page_Size));
				map_page_at(page_addr);
			}
		}
		return virtual_addr;
	}

	uint32_t PageDirectory::virt2phys(void *addr){
		uint32_t ret = 0;
		size_t pageindex = (uint32_t)addr / MM2_Page_Size;
		size_t tableno = pageindex / MM2_Table_Entries;
		size_t pageno = pageindex % MM2_Table_Entries;
		
		{
			hold_lock hl(table_frame_lock);
			if(map_table(directory[tableno]) && (table_frame[pageno] & MM2_PageFlags::Present)){
				ret = table_frame[pageno] & MM2_Address_Mask;
				ret += (uint32_t)addr & ~MM2_Address_Mask;
			}
		}
		return ret;
	}
	
	bool PageDirectory::is_available(uint32_t pageno){
		void *addr = (void*)(pageno * MM2_Page_Size);
		return !!virt2phys(addr);
	}


	void PageDirectory::map_page_at(void *addr, physical_page *page, uint32_t flags){
		size_t pageidx = (uint32_t)addr / MM2_Page_Size;
		size_t tableno = pageidx / MM2_Table_Entries;
		size_t pageno = pageidx % MM2_Table_Entries;
		{
			hold_lock hl(table_frame_lock);
			if(!map_table(directory[tableno])){
				create_table(tableno);
				map_table(directory[tableno]);
			}
			if(table_frame[pageno] & MM2_PageFlags::Present) return;
			else table_frame[pageno] = page->address | flags;
		}
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
}