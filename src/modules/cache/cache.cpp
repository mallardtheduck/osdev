#include <module/module.inc>
#include <module/cache.hpp>
#include <util/ministl.hpp>
#include <util/asprintf.h>

static const size_t MaxCacheSize = 4 * 1024 * 1024; //Max cache: 4MB

class Cache : public btos_api::ICache{
private:
	struct CacheEntry{
		uint64_t id;
		char *buf;
		uint32_t usage;
	};
	
	vector<CacheEntry> entries;
	void Prune();
public:
	Cache(size_t blockSize, size_t maxBlocks);
	~Cache();

	void Store(uint64_t id, const char *buf);
	bool Retrieve(uint64_t id, char *buf);
	void Drop(uint64_t id);
	
	size_t blockSize;
	size_t maxBlocks;
	
	uint64_t hits = 0;
	uint64_t misses = 0;
};

vector<Cache*> *caches;

static char *caches_infofs(){
	char *buffer = nullptr;
	asprintf(&buffer, "# id, blockSize, maxBlocks, hits, misses\n");
	for(auto c : *caches){
		reasprintf_append(&buffer, "%p, %zu, %zu, %llu, %llu\n", 
			c, c->blockSize, c->maxBlocks, c->hits, c->misses
		);
	}
	return buffer;
}

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
	uint32_t min = maxBlocks;
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
			if(e.usage < maxBlocks) ++e.usage;
			else{
				for(auto &f : entries){
					if(&e != &f && f.usage > 0) --f.usage;
				}
			}
			return;
		}
	}
	while(entries.size() >= maxBlocks) Prune();
	CacheEntry e;
	e.id = id;
	e.buf = (char*)malloc(blockSize);
	memcpy(e.buf, buf, blockSize);
	e.usage = 1;
	entries.push_back(e);
	//dbgpf("CACHE: Stored entry %i for ID: %i\n", (int)entries.size() - 1, (int)id);
}

bool Cache::Retrieve(uint64_t id, char *buf){
	CacheEntry *found = nullptr;
	for(auto &e : entries){
		if(e.id == id){
			found = &e;
			memcpy(buf, e.buf, blockSize);
			if(e.usage < maxBlocks) ++e.usage;
			else{
				for(auto &f : entries){
					if(&e != &f && f.usage > 0) --f.usage;
				}
			}
			//dbgpf("CACHE: Retrieved entry for ID: %i\n", (int)id);
			++hits;
			break;
		}
	}
	if(found) ++hits;
	else ++misses;
	return (bool)found;
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

class CacheExtension : public btos_api::ICacheExtension{
public:
	btos_api::ICache *CreateCache(size_t blockSize, size_t maxBlocks) override{
		auto ret = new Cache(blockSize, maxBlocks);
		caches->push_back(ret);
		return ret;
	}
	
	void DestroyCache(btos_api::ICache *cache) override{
		delete (Cache*)cache;
		auto i = caches->find((Cache*)cache);
		if(i != caches->npos) caches->erase(i);
	}

	const char *GetName() override{
		return "CACHE";
	}

	void UserAPIHandler(uint16_t, ICPUState &) override{}
};

int module_main(char *){
	caches = new vector<Cache*>();
	API->GetKernelExtensionManager().AddExtension(new CacheExtension());
	API->InfoRegister("CACHESTATS", &caches_infofs);
	return 0;
}