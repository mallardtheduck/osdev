#include "kernel.hpp"
#include "ministl.hpp"
#include "locks.hpp"
#include "vmm_pagedir.hpp"

static const uint32_t ec_user = (1 << 2);

struct amm_pagedetails{
	amm_flags::Enum flags;
	pid_t owner;
	void *ptr;
};

struct amm_filemap{
    file_handle file;
    size_t offset;
    size_t size;
    void *start;
    pid_t pid;
};

extern lock vmm_lock, sch_lock;
static bool in_reserve=false;

void amm_resolve_mmap(void * addr);

template<typename T> class amm_allocator {
public:
typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef T value_type;

	pointer allocate (size_t n, void* hint=0){
		size_t pages=((n*sizeof(value_type))/VMM_PAGE_SIZE)+1;
        take_lock_exclusive(sch_lock);
        take_lock_recursive(vmm_lock);
		in_reserve=true;
		pointer ret=(pointer)vmm_alloc(pages);
		in_reserve=false;
		release_lock(vmm_lock);
		release_lock(sch_lock);
		return ret;
	}
	void deallocate (pointer p, size_type n){
		size_t pages=((n*sizeof(value_type))/VMM_PAGE_SIZE)+1;
        take_lock_exclusive(sch_lock);
        take_lock_recursive(vmm_lock);
		vmm_free(p, pages);
        release_lock(vmm_lock);
        release_lock(sch_lock);
	}

	size_t max_size() const throw(){
		return (size_t)0xFFFFFFFF;
	}
	void construct ( pointer p, const_reference val ){
		new ((void*)p) value_type (val);
	}
	void destroy (pointer p){
		p->~T();
	}
	pointer address ( reference x ) const{
		return &x;
	}
	const_pointer address ( const_reference x ) const{
		return &x;
	}
};

typedef map<uint32_t, amm_pagedetails, less<amm_pagedetails>, amm_allocator<pair<const uint32_t, amm_pagedetails> > > amm_alloc_map;
amm_alloc_map *amm_allocated_pages;
vector<amm_filemap> *amm_filemappings;

static const uint32_t amm_mmap_marker=0xFF01000;

static bool amm_inited=false;
static lock amm_lock;
extern char _start, _end;

void amm_page_fault_handler(int, isr_regs *regs);

void amm_init(){
	amm_allocated_pages=new amm_alloc_map();
    amm_filemappings=new vector<amm_filemap>();
	//size_t reservation=(&_end-&_start)/VMM_PAGE_SIZE + 4096;
    size_t reservation= (vmm_gettotalmem()/4096)+1;
	amm_allocated_pages->reserve(reservation);
	if(!amm_allocated_pages) panic("(AMM) Init failed!");
	dbgpf("AMM: Map allocated at %x\n", amm_allocated_pages);
	amm_inited=true;
	int_handle(0x0e, &amm_page_fault_handler);
	init_lock(amm_lock);
}

void amm_mark_alloc(uint32_t pageaddr, amm_flags::Enum flags, pid_t owner, void *ptr){
	if(!amm_inited) return;
	amm_pagedetails p={flags, owner, ptr};
    hold_lock hl(amm_lock, false);
	/*if(!in_reserve && amm_allocated_pages->capacity() < amm_allocated_pages->size() * 2){
        dbgout("AMM: Growing accounting structure...\n");
		amm_allocated_pages->reserve(amm_allocated_pages->capacity() + 1024);
	}*/
    if(amm_allocated_pages->size() == amm_allocated_pages->capacity()) panic("(AMM) Too many pages allocated!");
	if(!amm_allocated_pages->has_key(pageaddr)) {
        amm_allocated_pages->insert(amm_alloc_map::value_type(pageaddr, p));
    }
}

void amm_mark_free(uint32_t pageaddr){
	if(!amm_inited) return;
	hold_lock hl(amm_lock, false);
    if(amm_allocated_pages->has_key(pageaddr)) {
        amm_allocated_pages->erase(pageaddr);
    }
}

amm_flags::Enum amm_get_flags(uint32_t pageaddr){
	if(!amm_inited) return amm_flags::Normal;
	hold_lock hl(amm_lock);
	if(amm_allocated_pages->has_key(pageaddr)){
		return (*amm_allocated_pages)[pageaddr].flags;
	}else return amm_flags::Normal;
}

void amm_set_info(uint32_t pageaddr, amm_flags::Enum flags, void *ptr){
    if(!amm_inited) return;
    hold_lock hl(amm_lock);
    if(amm_allocated_pages->has_key(pageaddr)) {
        dbgpf("AMM: Setting info on %x: flags: %x ptr: %x\n", pageaddr, flags, ptr);
        (*amm_allocated_pages)[pageaddr].flags=flags;
        (*amm_allocated_pages)[pageaddr].ptr=ptr;
    }else panic("TEST!");
}

void amm_page_fault_handler(int, isr_regs *regs){
	uint32_t addr;
	asm volatile("mov %%cr2, %%eax\r\n mov %%eax,%0": "=m"(addr): : "eax");
    uint32_t physaddr=vmm_cur_pagedir->virt2phys((void*)addr, false);
    if(physaddr == amm_mmap_marker){
        amm_resolve_mmap((void*)addr);
    } else if(regs->error_code & ec_user){
        proc_terminate();
    }else{
        dbgpf("AMM: Page fault on %x at %x!\n", addr, regs->eip);
        dbgpf("AMM: Physical address: %x\n", physaddr);
        if (addr < VMM_PAGE_SIZE) {
            panic("(AMM) Probable NULL pointer dereference!");
        } else if(vmm_get_flags(addr & VMM_ADDRESS_MASK) == amm_flags::Guard_Page){
            panic("(AMM) Use of guard page!");
        } else panic("(AMM) Page fault!");
    }
}

void amm_set_guard(void *ptr){
    void *page=(void*)((uint32_t)ptr & VMM_ADDRESS_MASK);
    vmm_set_flags((uint32_t)page, amm_flags::Guard_Page);
    vmm_free(page, 1);
}

amm_filemap *amm_getfilemap(uint32_t addr, pid_t pid=proc_current_pid){
    hold_lock hl(amm_lock, false);
    for(size_t i=0; i<amm_filemappings->size(); ++i){
        amm_filemap *map=&(*amm_filemappings)[i];
        if(map->pid==pid && (uint32_t)map->start < addr && (uint32_t)map->start + map->size > addr){
            return map;
        }
    }
    return NULL;
}

void amm_resolve_mmap(void *addr){
    dbgpf("AMM: Resolving memory-mapped file load at %x.\n", addr);
    void *page=(void*)((uint32_t)addr & VMM_ADDRESS_MASK);
    amm_filemap *map=amm_getfilemap((uint32_t)addr);
    size_t offset=((uint32_t)page - (uint32_t)map->start)+map->offset;
    vmm_cur_pagedir->unmap_page((size_t)page/VMM_PAGE_SIZE);
    amm_flags::Enum flags=((uint32_t)addr < VMM_KERNELSPACE_END)?amm_flags::Kernel : amm_flags::User;
    vmm_cur_pagedir->set_flags((uint32_t)page, flags);
    vmm_alloc_at(1, (uint32_t)page);
    size_t pos= fs_seek(map->file, 0, true);
    fs_seek(map->file, offset, false);
    size_t bytes=fs_read(map->file, VMM_PAGE_SIZE, (char*)page);
    fs_seek(map->file, pos, false);
    if(bytes != VMM_PAGE_SIZE) panic("(AMM) Memory-mapped read failed.");
}

void amm_mmap(char *ptr, file_handle &file, size_t offset, size_t size){
    if(size<VMM_PAGE_SIZE){
        size_t pos=fs_seek(file, 0, true);
        fs_seek(file, offset, false);
        fs_read(file, size, ptr);
        fs_seek(file, pos, false);
        amm_filemap map;
        map.file=file;
        map.offset=offset;
        map.size=size;
        map.start=ptr;
        map.pid=proc_current_pid;
        dbgpf("AMM: Mapped %x\n", map.file.filedata);
        (*amm_filemappings).push_back(map);
        return;
    }
    dbgpf("AMM: Memory-mapping %i bytes (offset %i) at %x.\n", size, offset, ptr);
    size_t pages=size/VMM_PAGE_SIZE;
    bool exact=false;
    if(pages*VMM_PAGE_SIZE==size && (uint32_t)ptr==((uint32_t)ptr & VMM_ADDRESS_MASK)) exact=true;
    else pages++;
    dbgpf("AMM: Pages to map: %i\n", pages);
    amm_filemap *map=new amm_filemap();
    map->pid=proc_current_pid;
    map->file=file;
    map->offset=offset;
    map->size=size;
    map->start=ptr;
    size_t start=0;
    size_t end=pages;
    if(!exact){
        dbgout("AMM: Not exactly page-aligned.\n");
        if((uint32_t)ptr != ((uint32_t)ptr & VMM_ADDRESS_MASK)){
            dbgout("AMM: Loading first page.\n");
            start=1;
            size_t rdsize=(((uint32_t)ptr & VMM_ADDRESS_MASK) + VMM_PAGE_SIZE)-(uint32_t)ptr;
            dbgpf("AMM: Reading %i bytes from offset %i to %x.\n", rdsize, offset, ptr);
            size_t pos=fs_seek(file, 0, true);
            fs_seek(file, offset, false);
            fs_read(file, rdsize, ptr);
            fs_seek(file, pos, false);
        }
        if((uint32_t)ptr+size % VMM_PAGE_SIZE){
            dbgout("AMM: Loading last page.\n");
            end=pages-1;
            char *lastpageaddr=(char*)((uint32_t)ptr+((pages-1)*VMM_PAGE_SIZE));
            size_t rdsize=((uint32_t)ptr+size)-(uint32_t)lastpageaddr;
            size_t rdoffset=((uint32_t)lastpageaddr-(uint32_t)ptr)+offset;
            dbgpf("AMM: Reading %i bytes from offset %i to %x.\n", rdsize, offset, lastpageaddr);
            size_t pos=fs_seek(file, 0, true);
            fs_seek(file, rdoffset, false);
            fs_read(file, rdsize, lastpageaddr);
            fs_seek(file, pos, false);
        }
    }
    vmm_allocmode::Enum mode=((uint32_t)ptr<VMM_KERNELSPACE_END)?vmm_allocmode::Kernel:vmm_allocmode::Userlow;
    for(size_t i=start; i<end; ++i){
        dbgpf("AMM: Mapping page %i.\n", i);
        uint32_t virtaddr=(uint32_t)ptr+(i*VMM_PAGE_SIZE);
        vmm_free((void*)virtaddr, 1);
        vmm_cur_pagedir->map_page(virtaddr/VMM_PAGE_SIZE, amm_mmap_marker/VMM_PAGE_SIZE, true, (vmm_allocmode::Enum)(mode | vmm_allocmode::NotPresent));
    }
    dbgout("AMM: Mapping completed.\n");
    (*amm_filemappings).push_back(*map);
}

void amm_flush(file_handle &file){
    hold_lock hl(amm_lock);
    if(!(file.mode & FS_Write)) return;
    vector<amm_filemap> &mappings=*amm_filemappings;
    for(size_t i=0; i<mappings.size(); ++i){
        if(mappings[i].file.filedata != file.filedata) continue;
        dbgpf("AMM: Flusing mapping %i\n", i);
        pid_t curpid=proc_current_pid;
        proc_switch(mappings[i].pid);
        if(mappings[i].size < VMM_PAGE_SIZE){
            dbgout("AMM: Mapping is less than one page, performing fs_write.\n");
            size_t pos=fs_seek(file, 0, true);
            fs_seek(file, mappings[i].offset, false);
            fs_write(file, mappings[i].size, (char*)mappings[i].start);
            fs_seek(file, pos, false);
            continue;
        }
        size_t pages=mappings[i].size/VMM_PAGE_SIZE;
        size_t start=0;
        bool exact=false;
        if(pages*VMM_PAGE_SIZE==mappings[i].size &&
                (uint32_t)mappings[i].start==((uint32_t)mappings[i].start & VMM_ADDRESS_MASK)) exact=true;
        else pages++;
        size_t end=pages;
        if(!exact){
            dbgout("AMM: Not exactly page-aligned.\n");
            if((uint32_t)mappings[i].start != ((uint32_t)mappings[i].start & VMM_ADDRESS_MASK)){
                dbgout("AMM: Writing first page.\n");
                start=1;
                size_t wrsize=(((uint32_t)mappings[i].start & VMM_ADDRESS_MASK) + VMM_PAGE_SIZE)-(uint32_t)mappings[i].start;
                dbgpf("AMM: Writing %i bytes from offset %i to %x.\n", wrsize, mappings[i].offset, mappings[i].start);
                size_t pos=fs_seek(file, 0, true);
                fs_seek(file, mappings[i].offset, false);
                fs_write(file, wrsize, (char*)mappings[i].start);
                fs_seek(file, pos, false);
            }
            if((uint32_t)mappings[i].start+mappings[i].size % VMM_PAGE_SIZE){
                dbgout("AMM: Writing last page.\n");
                end=pages-1;
                char *lastpageaddr=(char*)((uint32_t)mappings[i].start+((pages-1)*VMM_PAGE_SIZE));
                size_t wrsize=((uint32_t)mappings[i].start+mappings[i].size)-(uint32_t)lastpageaddr;
                size_t wroffset=((uint32_t)lastpageaddr-(uint32_t)mappings[i].start)+mappings[i].offset;
                dbgpf("AMM: Writing %i bytes from offset %i to %x.\n", wrsize, mappings[i].offset, lastpageaddr);
                size_t pos=fs_seek(file, 0, true);
                fs_seek(file, wroffset, false);
                fs_write(file, wrsize, lastpageaddr);
                fs_seek(file, pos, false);
            }
        }
        for(size_t j=start; j<end; ++j) {
            uint32_t virtaddr=((uint32_t)mappings[i].start+(j*VMM_PAGE_SIZE)) & VMM_ADDRESS_MASK;
            if(vmm_cur_pagedir->is_mapped((void*)virtaddr)) {
                vmm_allocmode::Enum mode=((uint32_t)mappings[i].start<VMM_KERNELSPACE_END)?vmm_allocmode::Kernel:vmm_allocmode::Userlow;
                if (vmm_cur_pagedir->is_dirty(virtaddr)) {
                    size_t offset = ((uint32_t) virtaddr - (uint32_t) mappings[i].start) + mappings[i].offset;
                    size_t pos=fs_seek(file, 0, true);
                    fs_seek(file, offset, false);
                    fs_write(file, VMM_PAGE_SIZE, (char *) virtaddr);
                    fs_seek(file, pos, false);
                }
                vmm_free((void*)virtaddr, 1);
                vmm_cur_pagedir->map_page(virtaddr/VMM_PAGE_SIZE, amm_mmap_marker/VMM_PAGE_SIZE, true, (vmm_allocmode::Enum)(mode | vmm_allocmode::NotPresent));
            }
        }
        proc_switch(curpid);
    }
}

void amm_close(file_handle &file) {
    amm_flush(file);
    hold_lock hl(amm_lock);
    vector<amm_filemap> &mappings=*amm_filemappings;
    for(size_t i=0; i<mappings.size(); ++i){
        if(mappings[i].file.filedata != file.filedata) continue;
        pid_t curpid=proc_current_pid;
        proc_switch(mappings[i].pid);
        dbgpf("AMM: Closing memory mapping %i\n", i);
        if(mappings[i].size < VMM_PAGE_SIZE) continue;
        size_t pages=mappings[i].size/VMM_PAGE_SIZE;
        size_t start=0;
        size_t end=pages;
        bool exact=false;
        if(pages*VMM_PAGE_SIZE==mappings[i].size &&
                (uint32_t)mappings[i].start==((uint32_t)mappings[i].start & VMM_ADDRESS_MASK)) exact=true;
        else pages++;
        if(!exact){
            if((uint32_t)mappings[i].start != ((uint32_t)mappings[i].start & VMM_ADDRESS_MASK)){
                start=1;
            }
            if((uint32_t)mappings[i].start+mappings[i].size % VMM_PAGE_SIZE){
                end=pages-1;
            }
        }
        for(size_t j=start; j<end; ++j) {
            uint32_t virtaddr = ((uint32_t) mappings[i].start + (j * VMM_PAGE_SIZE)) & VMM_ADDRESS_MASK;
            if (!vmm_cur_pagedir->is_mapped((void *) virtaddr)){
                dbgpf("AMM: Re-mapping page at %x\n", virtaddr);
                vmm_cur_pagedir->unmap_page(virtaddr/VMM_PAGE_SIZE);
                vmm_alloc_at(1, virtaddr);
            }
        }
        proc_switch(curpid);
    }
    bool changed=true;
    while(changed){
        changed=false;
        for(size_t i=0; i<mappings.size(); ++i){
            if(mappings[i].file.filedata == file.filedata){
                mappings.erase(i);
                changed=true;
                break;
            }
        }
    }
}
