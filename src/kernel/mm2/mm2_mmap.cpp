#include "../kernel.hpp"
#include "mm2_internal.hpp"
#include "../ministl.hpp"

namespace MM2{
	struct mmapping{
		char *addr;
		file_handle file;
		bt_filesize_t offset;
		size_t size;
		
		size_t pre;
		size_t post;
		bt_filesize_t page_offset;
		char *page_addr;
		size_t pages;
		pid_t pid;
	};
	
	static map<uint64_t, mmapping> *mmappings;
	static uint64_t counter = 0;
	
	static lock mmap_lock;
	
	static void do_mapping(mmapping &m){
		bt_filesize_t pos = fs_seek(m.file, 0, FS_Relative);
		
		if(m.size <= MM2_Page_Size){
			//dbgpf("MM2: Reading %i bytes from %i to %p.\n", (int)m.size, (int)m.offset, (void*)m.addr);
			fs_seek(m.file, m.offset, FS_Set);
			fs_read(m.file, m.size, m.addr);
			fs_seek(m.file, pos, FS_Set);
			return;
		}
		
		if(m.pre){
			fs_seek(m.file, m.offset, FS_Set);
			fs_read(m.file, m.pre, m.addr);
			//dbgpf("MM2: Loading pre (%i bytes) from offset %i at %p.\n", (int)m.pre, (int)m.offset, (void*)m.addr);
		}
		
		if(m.post){
			bt_filesize_t postoffset = m.page_offset + (m.pages * MM2_Page_Size);
			char *postaddr = (char*)((uint32_t)m.page_addr + (m.pages * MM2_Page_Size));
			fs_seek(m.file, postoffset, FS_Set);
			fs_read(m.file, m.post, postaddr);
			//dbgpf("MM2: Loading post (%i bytes) from offset %i at %p.\n", (int)m.post, (int)postoffset, (void*)postaddr);
		}
		
		current_pagedir->free_pages((void*)m.page_addr, m.pages);
		for(size_t i = 0; i < m.pages; ++i){
			current_pagedir->guard_page_at(m.page_addr + (i * MM2_Page_Size));
		}
		fs_seek(m.file, pos, FS_Set);
	}
	
	static void flush_mapping(mmapping &m){
		pid_t curpid = proc_current_pid;
		proc_switch(m.pid);
		bt_filesize_t pos = fs_seek(m.file, 0, FS_Relative);
		
		if(m.size <= MM2_Page_Size){
			fs_seek(m.file, m.offset, FS_Set);
			fs_write(m.file, m.size, m.addr);
			fs_seek(m.file, pos, FS_Set);
			proc_switch(curpid);
			return;
		}
		
		if(m.pre){
			fs_seek(m.file, m.offset, FS_Set);
			fs_write(m.file, m.pre, m.addr);
		}
		
		if(m.post){
			bt_filesize_t postoffset = m.page_offset + (m.pages * MM2_Page_Size);
			char *postaddr = (char*)((uint32_t)m.page_addr + (m.pages * MM2_Page_Size));
			fs_seek(m.file, postoffset, FS_Set);
			fs_write(m.file, m.post, postaddr);
		}
		
		for(size_t i = 0; i < m.pages; ++i){
			char *pageaddr = m.page_addr + (i * MM2_Page_Size);
			if(current_pagedir->is_mapped(pageaddr)){
				bt_filesize_t fileoffset = m.page_offset + (i * MM2_Page_Size);
				fs_seek(m.file, fileoffset, FS_Set);
				fs_write(m.file, MM2_Page_Size, pageaddr);
				current_pagedir->free_pages(pageaddr, 1);
			}
			current_pagedir->guard_page_at(pageaddr);
		}
		fs_seek(m.file, pos, FS_Set);
		proc_switch(curpid);
	}
	
	static void mmap_read(uint64_t id, void *addr){
		//dbgpf("MM2: MMAP read at %p.\n", addr);
		if(mmappings->has_key(id)){
			mmapping m = (*mmappings)[id];
			bt_filesize_t pos = fs_seek(m.file, 0, FS_Relative);
			if(addr < m.page_addr || addr > m.page_addr + (m.pages * MM2_Page_Size)) panic("(MM2) Out-of range memory-mapped read!");
			
			uint32_t flags = MM2_PageFlags::Present | MM2_PageFlags::Writable;
			if((uint32_t)m.addr >= MM2_Kernel_Boundary) flags |= MM2_PageFlags::Usermode;
			
			void *pageaddr = (void*)((uint32_t)addr & MM2_Address_Mask);
			bt_filesize_t readofs = ((uint32_t)pageaddr - (uint32_t)m.page_addr) + m.page_offset;
			//dbgpf("MM2: Reading page from %i at %p.\n", (int)readofs, pageaddr);
			current_pagedir->map_page_at(pageaddr, flags);
			bt_filesize_t npos = fs_seek(m.file, readofs, FS_Set);
			if(npos != readofs) panic("(MM2) MMAP Seek failed!");
			bt_filesize_t rd = fs_read(m.file, MM2_Page_Size, (char*)pageaddr);
			if(rd != MM2_Page_Size) panic("(MM2) MMAP Read failed!");
			fs_seek(m.file, pos, FS_Set);
		}else{
			panic("(MM2) Invalid MMAP read request!");
		}
	}
	
	uint64_t mm2_mmap(char *ptr, file_handle &file, bt_filesize_t offset, size_t size){
		dbgpf("MM2: Mapping %i bytes from file offset %i at %p.\n", (int)size, (int)offset, (void*)ptr);
		mmapping m;
		m.addr = ptr;
		m.file = file;
		m.offset = offset;
		m.size = size;
		m.pid = proc_current_pid;
		
		size_t asize = 0;
		if((uint32_t)ptr % MM2_Page_Size){
			m.page_addr = (char*)(((uint32_t)ptr + MM2_Page_Size) & MM2_Address_Mask);
			m.pre = ((uint32_t)m.page_addr - (uint32_t)ptr);
			asize = size - m.pre;
		}else{
			m.pre = 0;
			m.page_addr = ptr;
			asize = size;
		}
		m.page_offset = offset + m.pre;
		
		m.pages = asize / MM2_Page_Size;
		m.post = asize - (m.pages * MM2_Page_Size);
		
		//dbgpf("MM2: Mapping: pre: %i post: %i page_offset: %i page_addr: %p pages: %i. asize: %i\n", (int)m.pre, (int)m.post, (int)m.page_offset, (void*)m.page_addr, (int)m.pages, (int)asize);
		
		do_mapping(m);
		uint64_t id = ++counter;
		{
			hold_lock hl(mmap_lock);
			(*mmappings)[id] = m;
		}
		
		if(size > MM2_Page_Size){
			if((uint32_t)ptr < MM2_Kernel_Boundary){
				kernel_pagedir->add_region(m.page_addr, m.pages * MM2_Page_Size, &mmap_read, id);
			}else{
				current_pagedir->add_region(m.page_addr, m.pages * MM2_Page_Size, &mmap_read, id);
			}
		}
		
		return id;
	}
	
	void mm2_flush(file_handle &file){
		hold_lock hl(mmap_lock);
		for(auto i = mmappings->begin(); i != mmappings->end(); ++i){
			if(i->second.file.filedata == file.filedata){
				flush_mapping(i->second);
			}
		}
	}
	
	void mm2_close(file_handle &file){
		hold_lock hl(mmap_lock);
		bool changed = false;
		do{
			changed = false;
			for(auto i = mmappings->begin(); i != mmappings->end(); ++i){
				if(i->second.file.filedata == file.filedata){
					mm2_closemap(i->first);
					changed = true;
					break;
				}
			}
		}while(changed);
	}
	
	void mm2_closemap(uint64_t id){
		hold_lock hl(mmap_lock, false);
		if(mmappings->has_key(id)){
			mmapping m = (*mmappings)[id];
			pid_t curpid = proc_current_pid;
			proc_switch(m.pid);
			flush_mapping(m);
			if(m.size > MM2_Page_Size){
				for(size_t i = 0; i < m.pages; ++i){
					char *pageaddr = m.page_addr + (i * MM2_Page_Size);
					if(!current_pagedir->is_mapped(pageaddr)){
						uint32_t flags = MM2_PageFlags::Present | MM2_PageFlags::Writable;
						if((uint32_t)m.addr >= MM2_Kernel_Boundary) flags = MM2_PageFlags::Present | MM2_PageFlags::Writable | MM2_PageFlags::Usermode;
						current_pagedir->map_page_at(pageaddr, flags);
					}
				}
			}
			if(m.size > MM2_Page_Size){
				if((uint32_t)m.addr < MM2_Kernel_Boundary){
					kernel_pagedir->remove_region(m.page_addr);
				}else{
					current_pagedir->remove_region(m.page_addr);
				}
			}
			mmappings->erase(id);
			proc_switch(curpid);
		}
	}
	
	void init_mmap(){
		init_lock(mmap_lock);
		mmappings = new map<uint64_t, mmapping>();
	}
}