#include "../kernel.hpp"
#include "mm2_internal.hpp"
#include "pagedirectory.hpp"

namespace MM2{

	static const uint32_t CR0_Paging_Enabled = 0x80000000;

	static uint32_t init_kernel_pagedir[MM2_Table_Entries] __attribute__((aligned(0x1000)));
	static char kpd_place[sizeof(PageDirectory)];
	static PageDirectory *kernel_pagedir;
	static PageDirectory *current_pagedir;
	
	lock table_frame_lock;

	static void idmap_page(size_t pageno){
		size_t tableno = pageno / MM2_Table_Entries;
		size_t entry = pageno % MM2_Table_Entries;
		
		uint32_t *table = (uint32_t*)(init_kernel_pagedir[tableno] & MM2_Address_Mask);
		table[entry] = (pageno * MM2_Page_Size) | MM2_PageFlags::Present | MM2_PageFlags::Writable;
	}

	static uint32_t div_ceil(uint32_t num, uint32_t den){
		size_t ret = num / den;
		if(num % den) ++ret;
		return ret;
	}

	void mm2_virtual_init(){
		dbgout("MM2: Virtual memory manager init.\n");
		memset(&init_kernel_pagedir, 0, sizeof(init_kernel_pagedir));
		size_t pages_to_idmap = div_ceil((uint32_t)get_kernel_end(), MM2_Page_Size);
		size_t tables_needed = div_ceil(pages_to_idmap, MM2_Table_Entries);
		dbgpf("MM2: VMM: Pages to identity map: %i, tables needed: %i\n", (int)pages_to_idmap, (int)tables_needed);
		
		size_t tables_allocated = 0;
		while(tables_allocated < tables_needed){
			size_t table_address = (size_t)mm2_init_page_alloc();
			init_kernel_pagedir[tables_allocated] = table_address | MM2_TableFlags::Present | MM2_TableFlags::Writable;
			++tables_allocated;
			
			pages_to_idmap = div_ceil((uint32_t)get_kernel_end(), MM2_Page_Size);
			tables_needed = div_ceil(pages_to_idmap, MM2_Table_Entries);
			dbgpf("MM2: VMM: Pages to identity map: %i, tables needed: %i\n", (int)pages_to_idmap, (int)tables_needed);
		}
		
		for(size_t page = 0; page < pages_to_idmap; ++page){
			idmap_page(page);
		}
		dbgpf("MM2: VMM: Identity mapped %i pages.\n", (int)pages_to_idmap);
		
		dbgout("MM2: VMM: Enabing paging...");
		asm volatile("mov %0, %%cr3":: "b"(init_kernel_pagedir));
		uint32_t cr0;
		asm volatile("mov %%cr0, %0": "=b"(cr0));
		cr0 |= CR0_Paging_Enabled;
		asm volatile("mov %0, %%cr0":: "b"(cr0));
		dbgout("Done.\n");
		
		current_pagedir = kernel_pagedir = new(&kpd_place) PageDirectory(init_kernel_pagedir);
		init_lock(table_frame_lock);
	}

	void *mm2_virtual_alloc(size_t pages, uint32_t mode){
		return current_pagedir->alloc(pages, mode);
	}

	void mm2_invlpg(void *pageaddr){
		asm volatile("invlpg (%0)" ::"r" (pageaddr) : "memory");
	}

}