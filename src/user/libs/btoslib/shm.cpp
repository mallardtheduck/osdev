#include <btos/shm.hpp>

namespace btos_api{

	SHMSpace::SHMSpace(uint32_t flags) : Handle(bt_create_shm(flags)) {}

	uint64_t SHMSpace::ID(){
		return bt_shm_id(handle);
	}

	SHMMapping SHMSpace::Map(void *addr, uint32_t offset, size_t pages, uint32_t flags){
		bt_handle_t maphandle = bt_shm_map(ID(), addr, offset, pages, flags);
		return SHMMapping(maphandle, addr, offset, pages, flags);
	}


	SHMMapping::SHMMapping(bt_handle_t h, uint64_t i, void *a, uint32_t o, size_t p, uint32_t f) : 
		Handle(h), id(i), addr(a), offset(o), pages(p), flags(f) {}

	SHMMapping::SHMMapping(uint64_t i, void *a, uint32_t o, size_t p, uint32_t f) :
		Handle(bt_shm_map(i, a, o, p, f)), id(i), addr(a), offset(o), pages(p), flags(f)
	{}
	
	uint64_t SHMMapping::ID(){
		return id;
	}

	void *SHMMapping::Address(){
		return addr;
	}

	uint32_t SHMMapping::Offset(){
		return offset;
	}

	size_t SHMMapping::Pages(){
		return pages;
	}

	size_t SHMMapping::Size(){
		return pages * 4096;
	}

	uint32_t SHMMapping::Flags(){
		return flags;
	}
}
