#ifndef MODULE_MM2_HPP
#define MODULE_MM2_HPP

#include <cstdint>
#include <cstddef>

#include <btos/btos_api.h>
#include <util/noncopyable.hpp>

class IFileHandle;
class ILock;

namespace MM2{
	class PageDirectory;

	const size_t MM2_Page_Size = 4096;
	const size_t MM2_Kernel_Boundary=1024*1024*1024;
	const uint32_t MM2_Boundary_Page = MM2_Kernel_Boundary / MM2_Page_Size;
	const uint32_t MM2_Address_Mask = 0xFFFFF000;

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
}

class IMemoryManager : private nonmovable{
public:
	virtual void SwitchPageDirectory(MM2::PageDirectory *newDirectory) = 0;
	virtual uint64_t MemoryMapFile(char *ptr, IFileHandle *file, bt_filesize_t offset, size_t size) = 0;
	virtual void UnMapFile(uint64_t id) = 0;
	virtual void FlushMemoryMappings(IFileHandle *file) = 0;
	virtual void CloseMemoryMappings(IFileHandle *file) = 0;

	virtual uint64_t CreateSharedMemorySpace(uint32_t flags = btos_api::bt_shm_flags::Normal) = 0;
	virtual void DestroySharedMemorySpace(uint64_t id) = 0;
	virtual uint64_t MapSharedMemory(uint64_t id, void *addr, uintptr_t offset, size_t pages, uint32_t flags = btos_api::bt_shm_flags::Normal) = 0;
	virtual void UnMapSharedMemory(uint64_t id) = 0;

	virtual void *MapPhysicalMemory(uintptr_t address, size_t pages) = 0;
	virtual ILock *GetLowMemoryLock() = 0;

	virtual ~IMemoryManager() {}
};

IMemoryManager &GetMemoryManager();

#endif