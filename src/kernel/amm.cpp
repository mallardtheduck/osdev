#include "kernel.hpp"
#include "ministl.hpp"
#include "locks.hpp"

struct amm_pagedetails{
	amm_flags::Enum flags;
	pid_t owner;
	void *ptr;
};

typedef map<uint32_t, amm_pagedetails> amm_alloc_map;
amm_alloc_map *amm_allocated_pages;

static bool amm_inited=false;
static lock amm_lock;

void amm_init(){
	amm_allocated_pages=new amm_alloc_map();
	amm_allocated_pages->reserve(4096);
	if(!amm_allocated_pages) panic("(AMM) Init failed!");
	dbgpf("AMM: Map allocated at %x\n", amm_allocated_pages);
	amm_inited=true;
	init_lock(amm_lock);
}

void amm_mark_alloc(uint32_t pageaddr, amm_flags::Enum flags, pid_t owner, void *ptr){
	if(!amm_inited) return;
	hold_lock hl(amm_lock);
	amm_pagedetails p={flags, owner, ptr};
	amm_allocated_pages->insert(amm_alloc_map::value_type(pageaddr, p));
	amm_allocated_pages->reserve(amm_allocated_pages->size() + 1);
}

void amm_mark_free(uint32_t pageaddr){
	if(!amm_inited) return;
	hold_lock hl(amm_lock);
	amm_allocated_pages->erase(pageaddr);
}

amm_flags::Enum amm_get_flags(uint32_t pageaddr){
	if(!amm_inited) return amm_flags::Normal;
	hold_lock hl(amm_lock);
	if(amm_allocated_pages->has_key(pageaddr)){
		return (*amm_allocated_pages)[pageaddr].flags;
	}else return amm_flags::Normal;
}