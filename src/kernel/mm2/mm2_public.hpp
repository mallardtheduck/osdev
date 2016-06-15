#ifndef _MM2_PUBLIC_HPP
#define _MM2_PUBLIC_HPP

#include "../kernel.hpp"

namespace MM2{
	class PageDirectory;

	const size_t MM2_Page_Size = 4096;
	const size_t MM2_Kernel_Boundary=1024*1024*1024;
	const uint32_t MM2_Boundary_Page = MM2_Kernel_Boundary / MM2_Page_Size;

	namespace MM2_Alloc_Mode{
		const uint32_t
		Kernel      = (1<<0),
		Userlow     = (1<<1),
		Userhigh    = (1<<2),
		NoBacking   = (1<<3),
		Immediate	= (1<<4);
	}

	namespace MM2_PageFlags{
		const uint32_t
		Present 		= 1 << 0,
		Writable 		= 1 << 1,
		Usermode 		= 1 << 2,
		WriteThrough 	= 1 << 3,
		NoCache			= 1 << 4,
		Accessed		= 1 << 5,
		Dirty			= 1 << 6,
		Global			= 1 << 7,

		Do_Not_Use      = 1 << 9,
		Do_Not_Move     = 1 << 10,
		Do_Not_Swap     = 1 << 11,

		Kernel          = Do_Not_Move | Do_Not_Swap,
		User            = Usermode,
		Guard_Page      = Do_Not_Use | Do_Not_Swap,
		PageTable       = Do_Not_Move | Do_Not_Swap;
	};
	
	void mm2_switch(PageDirectory *newdir);
	
	uint64_t mm2_mmap(char *ptr, file_handle &file, bt_filesize_t offset, size_t size);
	void mm2_flush(file_handle &file);
	void mm2_close(file_handle &file);
	void mm2_closemap(uint64_t id);
	
	void mm2_liballoc_lock();
	void mm2_liballoc_unlock();
}

#endif