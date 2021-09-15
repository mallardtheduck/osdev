#include "mm2_internal.hpp"
#include "mm2_public.hpp"

class MemoryManager : public IMemoryManager{
public:
	void SwitchPageDirectory(MM2::PageDirectory *newDirectory) override{
		MM2::mm2_switch(newDirectory);
	}

	uint64_t MemoryMapFile(char *ptr, IFileHandle *file, bt_filesize_t offset, size_t size) override{
		return MM2::mm2_mmap(ptr, file, offset, size);
	}

	void UnMapFile(uint64_t id) override{
		MM2::mm2_closemap(id);
	}

	void FlushMemoryMappings(IFileHandle *file) override{
		MM2::mm2_flush(file);
	}

	void CloseMemoryMappings(IFileHandle *file) override{
		MM2::mm2_close(file);
	}

	uint64_t CreateSharedMemorySpace(uint32_t flags = btos_api::bt_shm_flags::Normal) override{
		return MM2::shm_create(flags);
	}

	void DestroySharedMemorySpace(uint64_t id) override{
		MM2::shm_close(id);
	}

	uint64_t MapSharedMemory(uint64_t id, void *addr, intptr_t offset, size_t pages, uint32_t flags = btos_api::bt_shm_flags::Normal) override{
		return MM2::shm_map(id, addr, offset, pages, flags);
	}

	void UnMapSharedMemory(uint64_t id) override{
		MM2::shm_close_map(id);
	}

	void *MapPhysicalMemory(intptr_t address, size_t pages) override{
		return MM2::mm2_map_physical(address, pages);
	}

	ILock *GetLowMemoryLock() override{
		return MM2::get_low_memory_lock();
	}
};

ManualStaticAlloc<MemoryManager> theMemoryManager;

namespace MM2{
	void init_class(){
		theMemoryManager.Init();
	}
}

IMemoryManager &GetMemoryManager(){
	return *theMemoryManager;
}