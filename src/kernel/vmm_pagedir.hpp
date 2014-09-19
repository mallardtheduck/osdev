#ifndef _VMM_PAGEDIR_HPP
#define _VMM_PAGEDIR_HPP

class vmm_pagedir{
private:
    uint32_t* pagedir;
    uint32_t* curtable;
    uint32_t phys_addr;
    size_t userpagecount;

    void maptable(uint32_t phys_addr);
public:
    void init(uint32_t *dir);
    void init();

    uint32_t *getvirt(){
        return pagedir;
    }
    uint32_t getphys(){
    	return phys_addr;
    }

    uint32_t virt2phys(void *ptr, bool present=true);
    void add_table(size_t tableno, uint32_t *table);

    bool is_mapped(void *ptr, bool present=true){
        return !!virt2phys(ptr, present);
    }

    size_t find_free_virtpages(size_t pages, vmm_allocmode::Enum mode);
    void map_page(size_t virtpage, size_t physpage, bool alloc=true, vmm_allocmode::Enum mode=vmm_allocmode::Kernel);

    void identity_map(size_t page, bool alloc=true){
    	map_page(page, page, alloc);
    }

    size_t unmap_page(size_t virtpage);

    void copy_kernelspace(vmm_pagedir *other){
    	memcpy(pagedir, other->pagedir, VMM_KERNEL_TABLES * sizeof(uint32_t));
    }

    size_t getuserpagecount(){
    	return userpagecount;
    }

    void destroy();

    void set_flags(uint32_t pageaddr, amm_flags::Enum flags);
    amm_flags::Enum get_flags(uint32_t pageaddr);
    bool is_dirty(uint32_t pageaddr);
};

#endif