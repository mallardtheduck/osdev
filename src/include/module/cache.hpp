#ifndef _CACHE_HPP
#define _CACHE_HPP

#include <stdint.h>
#include <btos_module.h>

namespace btos_api{
	class ICache{
	public:
		virtual void Store(uint64_t id, const char *buf) = 0;
		virtual bool Retrieve(uint64_t id, char *buf) = 0;
		virtual void Drop(uint64_t id) = 0;
	
		virtual ~ICache() {}
	};
	
	struct CacheCallTable{
		ICache *(*CreateCache)(size_t blockSize, size_t maxBlocks);
		void (*DestroyCache)(ICache *cache);
	};
	
	inline static bool IsCacheLoaded(){
		uint16_t extid = get_extension_id("CACHE");
		if(extid) return true;
		else return false;
	}
	
	inline static ICache *CreateCache(size_t blockSize, size_t maxBlocks){
		uint16_t extid = get_extension_id("CACHE");
		if(!extid) return nullptr;
		CacheCallTable *calltable = (CacheCallTable*)get_extension(extid)->calltable;
		if(!calltable) return nullptr;
		return calltable->CreateCache(blockSize, maxBlocks);
	}
	
	inline static void DestroyCache(ICache *cache){
		uint16_t extid = get_extension_id("CACHE");
		if(!extid) return;
		CacheCallTable *calltable = (CacheCallTable*)get_extension(extid)->calltable;
		if(!calltable) return;
		calltable->DestroyCache(cache);
	}
}

#endif