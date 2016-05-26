#ifndef PAGEDIRECTORY_HPP
#define PAGEDIRECTORY_HPP

#include "mm2_internal.hpp"

namespace MM2{

	class PageDirectory{
	private:
		uint32_t *directory;
		lock directory_lock;
		
		bool map_table(uint32_t tableaddr);
		void create_table(size_t tableno);
	public:
		PageDirectory();
		PageDirectory(uint32_t *a);
		~PageDirectory();

		void *alloc(size_t pages, uint32_t mode);
		void map_page_at(void *addr, uint32_t flags = MM2_PageFlags::Present | MM2_PageFlags::Writable);
		void map_page_at(void *addr, physical_page *page, uint32_t flags = MM2_PageFlags::Present | MM2_PageFlags::Writable);
		void free(void *addr, size_t pages);
		
		uint32_t virt2phys(void *addr);
		bool is_available(uint32_t pageno);
		bool is_mapped(void *addr){
			return !!virt2phys(addr);
		}
	};

}
#endif // PAGEDIRECTORY_HPP
