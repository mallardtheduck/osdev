#include "kernel.hpp"
#include "ministl.hpp"

struct amm_pagedetails{
	uint32_t flags;
	pid_t owner;
	void *ptr;
};
typedef map<uint32_t, amm_pagedetails> amm_alloc_map;
amm_alloc_map *amm_allocated_pages;

void amm_init(){
	amm_allocated_pages=new amm_alloc_map();
}

void amm_mark_alloc(uint32_t pageaddr, uint32_t flags, pid_t owner, void *ptr){
	amm_pagedetails p={flags, owner, ptr};
	amm_allocated_pages->insert(amm_alloc_map::value_type(pageaddr, p));
}

void amm_mark_free(uint32_t pageaddr){
	amm_allocated_pages->erase(pageaddr);
}

uint32_t amm_get_flags(uint32_t pageaddr){
	if(amm_allocated_pages->has_key(pageaddr)){
		return (*amm_allocated_pages)[pageaddr].flags;
	}else return 0;
}