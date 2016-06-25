#include "../kernel.hpp"
#include "mm2_internal.hpp"
#include "../ministl.hpp"

namespace MM2{
	struct shm_space{
		map<uint32_t, physical_page> pages;
	};
	
	struct shm_mapping{
		uint64_t space;
		void *addr;
		uint32_t offset;
		size_t pages;
	};
	
	static map<uint64_t, shm_space> *spaces;
	static map<uint64_t, shm_mapping> *mappings;
	
	uint64_t shm_create();
	void shm_close(uint64_t id);
	uint64_t shm_map(uint64_t id, void *addr, uint32_t offset, size_t pages);
	void shm_close_map(uint64_t id);
	
	void init_shm(){
		spaces = new map<uint64_t, shm_space>();
		mappings = new map<uint64_t, shm_mapping>();
	}
}