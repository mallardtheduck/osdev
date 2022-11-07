#include "../kernel.hpp"
#include "mm2_internal.hpp"
#include "../utils/ministl.hpp"

namespace MM2{
	static StaticAllocLock shm_lock;
	
	struct shm_space{
		map<uint32_t, physical_page*> pages;
		uint32_t flags;
		bt_pid_t owner;
	};
	
	struct shm_mapping{
		shm_space *space;
		void *addr;
		uint32_t offset;
		size_t pages;
		uint32_t flags;
		bt_pid_t pid;
	};
	
	static ManualStaticAlloc<map<uint64_t, shm_space*>> spaces;
	static ManualStaticAlloc<map<uint64_t, shm_mapping*>> mappings;
	static uint64_t space_id_counter = 0;
	static uint64_t mapping_id_counter = 0;
	
	uint64_t shm_create(uint32_t flags){
		auto hl = shm_lock->LockExclusive();
		uint64_t id = ++space_id_counter;
		shm_space *space = new shm_space();
		space->flags = flags;
		space->owner = CurrentProcess().ID();
		(*spaces)[id] = space;
		dbgpf("MM2: Created SHM space %i\n", (int)id);
		return id;
	}
	
	void shm_close(uint64_t id){
		auto hl = shm_lock->LockExclusive();
		shm_space *space = (*spaces)[id];
		bool cont = true;
		while(cont){
			for(auto i = mappings->begin(); i != mappings->end(); ++i){
				if(i->second && i->second->space == space) {
					shm_close_map(i->first);
					break;
				}
			}
			cont = false;
		}
		for(auto i = space->pages.begin(); i != space->pages.end(); ++i){
			physical_free(i->second);
		}
		delete (*spaces)[id];
		spaces->erase(id);
	}
	
	static void shm_pf_handler(uint64_t id, void *addr){
		//dbgpf("MM2: SHM mapping %i PF at %p.\n", (int)id, addr);
		auto hl = shm_lock->LockExclusive();
		
		if(!mappings->has_key(id)) panic("(MM2) Invalid mapping!");
		shm_mapping *mapping = (*mappings)[id];
		uint32_t space_addr = ((uint32_t)addr - (uint32_t)mapping->addr) + mapping->offset;
		uint32_t page_addr = space_addr & MM2_Address_Mask;
		shm_space *space = mapping->space;
		physical_page *page = (physical_page*)0xBADF00D;
		if(space->pages.has_key(page_addr)){
			page = space->pages[page_addr];
		}else{
			page = physical_alloc();
			space->pages[page_addr] = page;
		}
		void *addr_page = (void*)((uint32_t)addr & MM2_Address_Mask);
		//dbgpf("MM2: Mapping shared page %p from SHM mapping %i at address %p.\n", (void*)page->address(), (int)id, addr_page);
		uint32_t pageflags = MM2_PageFlags::Present | MM2_PageFlags::Usermode;
		if((space->owner == CurrentProcess().ID() || !(space->flags & btos_api::bt_shm_flags::ReadOnly)) && !(mapping->flags & btos_api::bt_shm_flags::ReadOnly)){
			pageflags |= MM2_PageFlags::Writable;
		}
		current_pagedir->map_page_at(addr_page, page, MM2_PageFlags::Present | MM2_PageFlags::Writable | MM2_PageFlags::Usermode);
	}
	
	uint64_t shm_map(uint64_t id, void *addr, uint32_t offset, size_t pages, uint32_t flags){
		auto hl = shm_lock->LockExclusive();
		dbgout("MM2: Creating SHM mapping.\n");
		if(!spaces->has_key(id)) {
			dbgpf("MM2: No such SHM space %i\n", (int)id);
			return 0;
		}
		if((uint32_t)addr % MM2_Page_Size != 0){
			dbgpf("MM2: Mapping address (%p) is not page-aligned!\n", addr);
			return 0;
		}
		if(offset % MM2_Page_Size != 0){
			dbgpf("MM2: Offset (%i) is not a multiple of page size.\n", (int)offset);
			return 0;
		}
		if(!GetPermissionManager().HasPermission(0, kperm::SHMAnyUser) && GetProcess((*spaces)[id]->owner)->GetUID() != CurrentProcess().GetUID()){
			dbgpf("MM2: Permission to map SHM denied.\n");
			return 0;
		}
		
		uint64_t ret = ++mapping_id_counter;
		
		current_pagedir->free_pages(addr, pages);
		for(uint32_t i = (uint32_t)addr; i < (uint32_t)addr + (pages * MM2_Page_Size); i += MM2_Page_Size){
			current_pagedir->guard_page_at((void*)i);
		}
		current_pagedir->add_region(addr, pages * MM2_Page_Size, &shm_pf_handler, ret);
		shm_mapping *mapping = new shm_mapping();
		mapping->space = (*spaces)[id];
		mapping->addr = addr;
		mapping->offset = offset;
		mapping->pages = pages;
		mapping->pid = CurrentProcess().ID();
		(*mappings)[ret] = mapping;
		dbgpf("MM2: Mapped %i pages from SHM space %i offset %x to address %p as mapping ID: %i\n", (int)pages, (int)id, (unsigned)offset, addr, (int)ret);
		return ret;
	}
	
	void shm_close_map(uint64_t id){
		auto hl = shm_lock->LockRecursive();
		
		if(mappings->has_key(id)){
			shm_mapping *mapping = (*mappings)[id];
			bt_pid_t pid = CurrentProcess().ID();
			if(!GetProcessManager().SwitchProcess(mapping->pid)) panic("(MM2) Cannot switch to process!");
			current_pagedir->remove_region(mapping->addr);
			void *addr = mapping->addr;
			for(uint32_t i = (uint32_t)addr; i < (uint32_t)addr + (mapping->pages * MM2_Page_Size); i += MM2_Page_Size){
				current_pagedir->map_page_at((void*)i, MM2_PageFlags::Present | MM2_PageFlags::Writable | MM2_PageFlags::Usermode);
			}
			delete mapping;
			mappings->erase(id);
			if(!GetProcessManager().SwitchProcess(pid)) panic("(MM2) Cannot switch to process!");
		}
	}
	
	void init_shm(){
		shm_lock.Init();
		spaces.Init();
		mappings.Init();
	}
}
