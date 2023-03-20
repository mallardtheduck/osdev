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
	
	class ICacheExtension : public IKernelExtension{
	public:
		virtual ICache *CreateCache(size_t blockSize, size_t maxBlocks) = 0;
		virtual void DestroyCache(ICache *cache) = 0;
	};
	
	inline static bool IsCacheLoaded(){
		uint16_t extid = API->GetKernelExtensionManager().GetExtensionID("CACHE");
		if(extid) return true;
		else return false;
	}
	
	inline static ICache *CreateCache(size_t blockSize, size_t maxBlocks){
		uint16_t extid = API->GetKernelExtensionManager().GetExtensionID("CACHE");
		if(!extid) return nullptr;
		ICacheExtension *calltable = static_cast<ICacheExtension*>(API->GetKernelExtensionManager().GetExtension(extid));
		if(!calltable) return nullptr;
		return calltable->CreateCache(blockSize, maxBlocks);
	}
	
	inline static void DestroyCache(ICache *cache){
		uint16_t extid = API->GetKernelExtensionManager().GetExtensionID("CACHE");
		if(!extid) return;
		ICacheExtension *calltable = static_cast<ICacheExtension*>(API->GetKernelExtensionManager().GetExtension(extid));
		if(!calltable) return;
		calltable->DestroyCache(cache);
	}
}

#endif