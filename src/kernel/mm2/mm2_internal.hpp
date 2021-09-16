#ifndef _MM2_INTERNAL_HPP
#define _MM2_INTERNAL_HPP

#include "../kernel.hpp"
#include "../locks.hpp"

namespace MM2{
	void mm2_physical_init(multiboot_info_t *mbt);
	void mm2_virtual_init();

	const size_t MM2_Table_Entries = 1024;
	const size_t MM2_Kernel_Pages = MM2_Kernel_Boundary / MM2_Page_Size;
	const size_t MM2_Kernel_Tables = MM2_Kernel_Pages / MM2_Table_Entries;
	const size_t MM2_Total_Pages = 0xFFFFFFFF / MM2_Page_Size;

	enum class PageStatus{
		Free,
		InUse,
		MMIO
	};

	class PageDirectory;
	
	class physical_page{
	private:
		uint32_t value;
	public:
		physical_page(uint32_t addr, PageStatus status){
			int s;
			memcpy(&s, &status, sizeof(s));
			value = addr | s;
		}
		
		uint32_t address(){
			return value & MM2_Address_Mask;
		}
		
		uint32_t address(uint32_t a){
			value = (value & ~MM2_Address_Mask) | a;
			return a;
		}
		
		PageStatus status(){
			int sv = (value & ~MM2_Address_Mask);
			PageStatus s;
			memcpy(&s, &sv, sizeof(s));
			return s;
		}
		
		PageStatus status(PageStatus s){
			int sv;
			memcpy(&sv, &s, sizeof(s));
			value = (value & MM2_Address_Mask) | sv;
			return s;
		}
	};

	namespace MM2_TableFlags{
		const uint32_t
		Present 		= 1 << 0,
		Writable 		= 1 << 1,
		Usermode 		= 1 << 2,
		WriteThrough 	= 1 << 3,
		NoCache			= 1 << 4,
		Accessed		= 1 << 5,
		LargePages		= 1 << 6;
	};

	extern StaticAllocLock table_frame_lock;

	void *mm2_init_alloc(size_t size);
	void *mm2_init_page_alloc();

	physical_page *physical_alloc(size_t max_addr = 0xFFFFFFFF);
	void physical_free(physical_page *page);
	void physical_free(uint32_t addr);
	void physical_mark_used(uint32_t addr);
	void physical_infofs_register();
	physical_page *physical_get_io_page(uintptr_t addr);
	
	void mm2_invlpg(void *pageaddr);
	
	void *mm2_virtual_alloc(size_t pages, uint32_t mode = MM2_Alloc_Mode::Kernel);
	void mm2_virtual_free(void *ptr, size_t pages);
	
	void *get_kernel_end();
	void page_fault_handler(ICPUState &state);
	
	void init_mmap();
	void init_shm();

	void init_class();

	//Formerly public
	void mm2_switch(PageDirectory *newdir);
	
	uint64_t mm2_mmap(char *ptr, IFileHandle *file, bt_filesize_t offset, size_t size);
	void mm2_flush(IFileHandle *file);
	void mm2_close(IFileHandle *file);
	void mm2_closemap(uint64_t id);

	uint64_t shm_create(uint32_t flags = btos_api::bt_shm_flags::Normal);
	void shm_close(uint64_t id);
	uint64_t shm_map(uint64_t id, void *addr, uint32_t offset, size_t pages, uint32_t flags = btos_api::bt_shm_flags::Normal);
	void shm_close_map(uint64_t id);
	
	void *mm2_map_physical(uint32_t addr, size_t pages);
	
	void lock_low_memory();
	void unlock_low_memory();

	ILock *get_low_memory_lock();
}

#include "pagedirectory.hpp"

#endif
