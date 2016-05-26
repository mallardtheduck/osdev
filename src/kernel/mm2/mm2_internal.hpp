#ifndef _MM2_INTERNAL_HPP
#define _MM2_INTERNAL_HPP

namespace MM2{
	void mm2_physical_init(multiboot_info_t *mbt);
	void mm2_virtual_init();

	const size_t MM2_Table_Entries = 1024;

	enum class PageStatus{
		Free,
		InUse,
		MMIO
	};

	struct physical_page{
		uint32_t address;
		PageStatus status;
		bool zeroed;
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

	namespace MM2_PageFlags{
		const uint32_t
		Present 		= 1 << 0,
		Writable 		= 1 << 1,
		Usermode 		= 1 << 2,
		WriteThrough 	= 1 << 3,
		NoCache			= 1 << 4,
		Accessed		= 1 << 5,
		Dirty			= 1 << 6,
		Global			= 1 << 7;
	};

	static const uint32_t MM2_Address_Mask = 0xFFFFF000;
	extern lock table_frame_lock;

	void *mm2_init_alloc(size_t size);
	void *mm2_init_page_alloc();

	physical_page *physical_alloc(size_t max_addr = 0xFFFFFFFF);
	void physical_free(physical_page *page);
	void mm2_invlpg(void *pageaddr);

	void *get_kernel_end();
}

#endif