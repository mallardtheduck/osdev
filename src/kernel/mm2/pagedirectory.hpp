#ifndef PAGEDIRECTORY_HPP
#define PAGEDIRECTORY_HPP

struct lock;

namespace MM2{
	struct physical_page;

	class PageDirectory{
	private:
		uint32_t *directory;
		lock *directory_lock;
		
		bool map_table(uint32_t tableaddr);
		void create_table(size_t tableno);
		uint32_t get_table_entry(size_t pageno);
		void set_table_entry(size_t pageno, uint32_t entry);
	public:
		PageDirectory();
		PageDirectory(uint32_t *a);
		~PageDirectory();

		void *alloc(size_t pages, uint32_t mode);
		void alloc_pages_at(size_t pages, void *baseaddr);
		void map_page_at(void *addr, uint32_t flags = MM2_PageFlags::Present | MM2_PageFlags::Writable);
		void map_page_at(void *addr, physical_page *page, uint32_t flags = MM2_PageFlags::Present | MM2_PageFlags::Writable);
		void free_pages(void *addr, size_t pages);
		
		uint32_t virt2phys(void *addr);
		bool is_available(uint32_t pageno);
		bool is_mapped(void *addr){
			return !!virt2phys(addr);
		}
		size_t resolve_addr(void *addr);
		
		void copy_kernelspace(const PageDirectory &pdir);
		
		size_t get_kernel_used();
		size_t get_user_used();
		
		void guard_page_at(void *ptr);
		
		void activate();
	};
	
	extern PageDirectory *kernel_pagedir;
	extern PageDirectory *current_pagedir;
}
#endif // PAGEDIRECTORY_HPP
