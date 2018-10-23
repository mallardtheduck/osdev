#include <btos_module.h>
#include <module/cache.hpp>
#include <util/ministl.hpp>

USE_SYSCALL_TABLE;
USE_DEBUG_PRINTF;
USE_PURE_VIRTUAL;

static const size_t MaxCacheSize = 4 * 1024 * 1024; //Max cache: 4MB
static const size_t MaxUsage = 1024;

class Cache : public btos_api::ICache{
private:
	struct CacheEntry{
		uint64_t id;
		char *buf;
		uint32_t usage;
	};
	size_t blockSize;
	size_t maxBlocks;
	
	vector<CacheEntry> entries;
	void Prune();
public:
	Cache(size_t blockSize, size_t maxBlocks);
	~Cache();

	void Store(uint64_t id, const char *buf);
	bool Retrieve(uint64_t id, char *buf);
	void Drop(uint64_t id);
};

Cache::Cache(size_t bS, size_t mB) : blockSize(bS), maxBlocks(mB){
	if(blockSize * maxBlocks > MaxCacheSize) maxBlocks = MaxCacheSize / blockSize;
	//dbgpf("CACHE: Created new cache. Block size: %i, max blocks: %i\n", (int)blockSize, (int)maxBlocks);
}

Cache::~Cache(){
	for(auto &e : entries){
		free(e.buf);
	}
}

void Cache::Prune(){
	uint32_t min = MaxUsage;
	size_t idx = maxBlocks;
	char *buf = nullptr;
	for(size_t i = 0; i < entries.size(); ++i){
		auto &e = entries[i];
		if(e.usage <= min){
			min = e.usage;
			idx = i;
			buf = e.buf;
		}
	}
	if(idx != maxBlocks) entries.erase(idx);
	if(buf) free(buf);
	//dbgpf("CACHE: Pruned entry %i\n", (int)idx);
}

void Cache::Store(uint64_t id, const char *buf){
	for(auto &e : entries){
		if(e.id == id){
			memcpy(e.buf, buf, blockSize);
			e.usage = 0;
			return;
		}
	}
	while(entries.size() >= maxBlocks) Prune();
	CacheEntry e;
	e.id = id;
	e.buf = (char*)malloc(blockSize);
	memcpy(e.buf, buf, blockSize);
	e.usage = 0;
	entries.push_back(e);
	//dbgpf("CACHE: Stored entry %i for ID: %i\n", (int)entries.size() - 1, (int)id);
}

bool Cache::Retrieve(uint64_t id, char *buf){
	bool ret = false;
	for(auto &e : entries){
		if(!ret && e.id == id){
			memcpy(buf, e.buf, blockSize);
			if(e.usage < MaxUsage) e.usage += 5;
			//dbgpf("CACHE: Retrieved entry for ID: %i\n", (int)id);
			ret = true;
		}else{
			if(e.usage > 0) --e.usage;
		}
	}
	return ret;
}

void Cache::Drop(uint64_t id){
	for(size_t i = 0; i < entries.size(); ++i){
		auto &e = entries[i];
		if(e.id == id){
			free(e.buf);
			entries.erase(i);
			//dbgpf("CACHE: Dropped entry %i for ID: %i\n", (int)i, (int)id);
		}
	}
}

btos_api::ICache *CreateCache(size_t blockSize, size_t maxBlocks){
	return new Cache(blockSize, maxBlocks);
}

void DestroyCache(btos_api::ICache *cache){
	delete (Cache*)cache;
}

btos_api::CacheCallTable calltable = {&CreateCache, &DestroyCache};

kernel_extension cache_extension{"CACHE", (void*)&calltable, nullptr};

extern "C" int module_main(syscall_table *systbl, char */*params*/){
	SYSCALL_TABLE=systbl;
	add_extension(&cache_extension);
	return 0;
}