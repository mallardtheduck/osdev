#include "kernel.hpp"
#include "locks.hpp"
#include "vmm_pagedir.hpp"

lock amm_a_lock;

struct amm_page_info{
    bool valid;
    uint32_t physaddr;
    amm_page_type::Enum type;
    void *info;
};

static amm_page_info* accounting;
static size_t totalpages=0;

uint32_t init_amm_page_accounting(vmm_region regions[], void *kend){
	dbgpf("AMM_A: Init at %p.\n", kend);
    for(size_t i=0; i<VMM_MAX_REGIONS; ++i){
        if(!regions[i].base) break;
        totalpages+=regions[i].pages;
    }
    size_t required_space=sizeof(amm_page_info) * totalpages;
    size_t required_pages=(required_space/VMM_PAGE_SIZE)+1;
    uint32_t kend_page=((uint32_t)kend & VMM_ADDRESS_MASK)+VMM_PAGE_SIZE;
    uint32_t accounting_start=kend_page;
    uint32_t accounting_end=kend_page+(required_pages*VMM_PAGE_SIZE);
    accounting=(amm_page_info*)accounting_start;
    for(size_t i=0; i<totalpages; ++i){
        accounting[i].valid=false;
    }
    for(size_t i=0; i<VMM_MAX_REGIONS; ++i){
        if(!regions[i].base) break;
        for(size_t j=0; j<regions[i].pages; ++j){
            uint32_t page_addr=(uint32_t)regions[i].base+(j*VMM_PAGE_SIZE);
            amm_accounting_add_free_page(page_addr);
            if(page_addr <= accounting_end){
                amm_accounting_mark_page(page_addr, amm_page_type::Kernel, NULL);
            }
        }
    }
    init_lock(amm_a_lock);
    return accounting_end/VMM_PAGE_SIZE;
}

void amm_accounting_add_free_page(uint32_t pageaddr){
    hold_lock hl(amm_a_lock);
	static size_t i = 0;
	bool fullsearch = false;
	while(!fullsearch){
		for(; i<totalpages; ++i){
			if(!accounting[i].valid){
				accounting[i].physaddr=pageaddr;
				accounting[i].type=amm_page_type::Free;
				accounting[i].valid=true;
				return;
			}
		}
		i = 0;
		fullsearch = true;
	}
    panic("(AMM_A) Ran out of page entries!");
}

void amm_accounting_mark_page(uint32_t pageaddr, amm_page_type::Enum type, void *info){
    hold_lock hl(amm_a_lock);
    for(size_t i=0; i<totalpages; ++i){
        if(accounting[i].valid && accounting[i].physaddr==pageaddr){
            accounting[i].type=type;
            accounting[i].info=info;
            return;
        }
    }
    dbgpf("AMM_A: Attempt to mark un-accounted page %x!\n", pageaddr);
}

uint32_t amm_accounting_get_free_page(uint32_t max){
    hold_lock hl(amm_a_lock);
    for(size_t i=totalpages; i>0; --i) {
		if(vmm_cur_pagedir->is_mapped(&accounting[i])){
			if(accounting[i].valid && accounting[i].type==amm_page_type::Free && accounting[i].physaddr < max) {
				if(!accounting[i].physaddr) panic("(AMM_A) Page accounting data corrupt!");
				return accounting[i].physaddr;
			}
		}
    }
    panic("(AMM_A) Out of memory!");
    return 0;
}

size_t amm_accounting_count_free_pages(){
    hold_lock hl(amm_a_lock);
    size_t ret=0;
    for(size_t i=0; i<totalpages; ++i){
        if(accounting[i].valid && accounting[i].type==amm_page_type::Free) ++ret;
    }
    return ret;
}