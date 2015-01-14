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
    uint64_t id;
    file_handle file;
    size_t offset;
    size_t size;
    void *start;
    pid_t pid;
};

extern lock vmm_lock, sch_lock;
static uint64_t filemap_idcount=0;

void amm_resolve_mmap(void * addr);

vector<amm_filemap> *amm_filemappings;

static const uint32_t amm_mmap_marker=0xFF01000;

static bool amm_inited=false;
static lock &amm_lock=vmm_lock;
extern char _start, _end;

void amm_page_fault_handler(int, isr_regs *regs);

void amm_init(){
    int_handle(0x0e, &amm_page_fault_handler);
    amm_filemappings=new vector<amm_filemap>();
    //Hack: Find a better way of ensuring that amm_filemappings is always in a consistent state
    amm_filemappings->reserve(32);
	amm_inited=true;
	init_lock(amm_lock);
}

void amm_mark_alloc(uint32_t pageaddr, amm_page_type::Enum type, void *info){
	if(!amm_inited) return;
    hold_lock hl(amm_lock, false);
    amm_accounting_mark_page(pageaddr, type, info);
}

void amm_mark_free(uint32_t pageaddr){
	if(!amm_inited) return;
	hold_lock hl(amm_lock, false);
    amm_accounting_mark_page(pageaddr, amm_page_type::Free, NULL);
}


void amm_page_fault_handler(int, isr_regs *regs){
	uint32_t addr;
	asm volatile("mov %%cr2, %%eax\r\n mov %%eax,%0": "=m"(addr): : "eax");
    uint32_t physaddr=vmm_cur_pagedir->virt2phys((void*)addr, false);
    if(physaddr == amm_mmap_marker){
        amm_resolve_mmap((void*)addr);
    } else if(regs->error_code & ec_user){
        dbgpf("AMM: Page fault on %x at %x!\n", addr, regs->eip);
        out_int_info(*regs);
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
    //dbgpf("AMM: Resolving memory-mapped file load at %x.\n", addr);
    void *page=(void*)((uint32_t)addr & VMM_ADDRESS_MASK);
    amm_filemap *map=amm_getfilemap((uint32_t)addr);
    //If this is a write-only mapping, return.
    size_t offset=((uint32_t)page - (uint32_t)map->start)+map->offset;
    vmm_cur_pagedir->unmap_page((size_t)page/VMM_PAGE_SIZE);
    amm_flags::Enum flags=((uint32_t)addr < VMM_KERNELSPACE_END)?amm_flags::Kernel : amm_flags::User;
    vmm_cur_pagedir->set_flags((uint32_t)page, flags);
    vmm_alloc_at(1, (uint32_t)page);
    memset(page, 0, VMM_PAGE_SIZE);
    if(!(map->file.mode & FS_Read)) return;
    size_t pos= fs_seek(map->file, 0, true);
    fs_seek(map->file, offset, false);
    size_t bytes=fs_read(map->file, VMM_PAGE_SIZE, (char*)page);
    fs_seek(map->file, pos, false);
    if(bytes != VMM_PAGE_SIZE) dbgpf("AMM: Failed to read page for memory-mapped I/O. Got %i bytes.\n", bytes);
}

uint64_t amm_mmap(char *ptr, file_handle &file, size_t offset, size_t size){
    if(size<VMM_PAGE_SIZE){
        size_t pos=fs_seek(file, 0, true);
        fs_seek(file, offset, false);
        fs_read(file, size, ptr);
        fs_seek(file, pos, false);
        amm_filemap map;
        map.id=++filemap_idcount;
        map.file=file;
        map.offset=offset;
        map.size=size;
        map.start=ptr;
        map.pid=proc_current_pid;
        //dbgpf("AMM: Mapped %x\n", map.file.filedata);
        (*amm_filemappings).push_back(map);
        return map.id;
    }
    //dbgpf("AMM: Memory-mapping %i bytes (offset %i) at %x.\n", size, offset, ptr);
    size_t pages=size/VMM_PAGE_SIZE;
    bool exact=false;
    if(pages*VMM_PAGE_SIZE==size && (uint32_t)ptr==((uint32_t)ptr & VMM_ADDRESS_MASK)) exact=true;
    else pages++;
    //dbgpf("AMM: Pages to map: %i\n", pages);
    amm_filemap *map=new amm_filemap();
    map->id=++filemap_idcount;
    map->pid=proc_current_pid;
    map->file=file;
    map->offset=offset;
    map->size=size;
    map->start=ptr;
    size_t start=0;
    size_t end=pages;
    if(!exact){
        //dbgout("AMM: Not exactly page-aligned.\n");
        if((uint32_t)ptr != ((uint32_t)ptr & VMM_ADDRESS_MASK)){
            //dbgout("AMM: Loading first page.\n");
            start=1;
            size_t rdsize=(((uint32_t)ptr & VMM_ADDRESS_MASK) + VMM_PAGE_SIZE)-(uint32_t)ptr;
            //dbgpf("AMM: Reading %i bytes from offset %i to %x.\n", rdsize, offset, ptr);
            size_t pos=fs_seek(file, 0, true);
            if(file.mode & FS_Read) {
                fs_seek(file, offset, false);
                fs_read(file, rdsize, ptr);
            }else memset(ptr, 0, rdsize);
            fs_seek(file, pos, false);
        }
        if((uint32_t)ptr+size % VMM_PAGE_SIZE){
            //dbgout("AMM: Loading last page.\n");
            end=pages-1;
            char *lastpageaddr=(char*)(((uint32_t)ptr+((pages-1)*VMM_PAGE_SIZE)) % VMM_ADDRESS_MASK);
            size_t rdsize=((uint32_t)ptr+size)-(uint32_t)lastpageaddr;
            size_t rdoffset=((uint32_t)lastpageaddr-(uint32_t)ptr)+offset;
            //dbgpf("AMM: Reading %i bytes from offset %i to %x.\n", rdsize, offset, lastpageaddr);
            size_t pos=fs_seek(file, 0, true);
            if(file.mode & FS_Read) {
                fs_seek(file, rdoffset, false);
                fs_read(file, rdsize, lastpageaddr);
            }else memset(lastpageaddr, 0, rdsize);
            fs_seek(file, pos, false);
        }
    }
    vmm_allocmode::Enum mode=((uint32_t)ptr<VMM_KERNELSPACE_END)?vmm_allocmode::Kernel:vmm_allocmode::Userlow;
    for(size_t i=start; i<end; ++i){
        //dbgpf("AMM: Mapping page %i.\n", i);
        uint32_t virtaddr=(uint32_t)ptr+(i*VMM_PAGE_SIZE);
        vmm_free((void*)virtaddr, 1);
        vmm_cur_pagedir->map_page(virtaddr/VMM_PAGE_SIZE, amm_mmap_marker/VMM_PAGE_SIZE, true, (vmm_allocmode::Enum)(mode | vmm_allocmode::NotPresent));
    }
    //dbgout("AMM: Mapping completed.\n");
    {
        hold_lock hl(sch_lock);
        (*amm_filemappings).push_back(*map);
    }
    return map->id;
}

void amm_flush(file_handle &file){
    hold_lock hl(amm_lock, false);
    if(!(file.mode & FS_Write)) return;
    vector<amm_filemap> &mappings=*amm_filemappings;
    for(size_t i=0; i<mappings.size(); ++i){
        if(mappings[i].file.filedata != file.filedata) continue;
        //dbgpf("AMM: Flusing mapping %i\n", i);
        pid_t curpid=proc_current_pid;
        proc_switch(mappings[i].pid);
        if(mappings[i].size < VMM_PAGE_SIZE){
           //dbgout("AMM: Mapping is less than one page, performing fs_write.\n");
            size_t pos=fs_seek(file, 0, true);
            if (file.mode & FS_Write) {
                fs_seek(file, mappings[i].offset, false);
                fs_write(file, mappings[i].size, (char *) mappings[i].start);
            }
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
            //dbgout("AMM: Not exactly page-aligned.\n");
            if((uint32_t)mappings[i].start != ((uint32_t)mappings[i].start & VMM_ADDRESS_MASK)) {
                //dbgout("AMM: Writing first page.\n");
                start = 1;
                size_t wrsize = (((uint32_t) mappings[i].start & VMM_ADDRESS_MASK) + VMM_PAGE_SIZE) - (uint32_t) mappings[i].start;
                //dbgpf("AMM: Writing %i bytes from offset %i to %x.\n", wrsize, mappings[i].offset, mappings[i].start);
                size_t pos = fs_seek(file, 0, true);
                if (file.mode & FS_Write) {
                    fs_seek(file, mappings[i].offset, false);
                    fs_write(file, wrsize, (char *) mappings[i].start);
                }
                memset(mappings[i].start, 0, wrsize);
                if(file.mode & FS_Read) {
                    fs_seek(file, mappings[i].offset, false);
                    fs_read(file, wrsize, (char *) mappings[i].start);
                }
                fs_seek(file, pos, false);
            }
            if((uint32_t)mappings[i].start+mappings[i].size % VMM_PAGE_SIZE){
                //dbgout("AMM: Writing last page.\n");
                end=pages-1;
                char *lastpageaddr=(char*)(((uint32_t)mappings[i].start+((pages-1)*VMM_PAGE_SIZE)) & VMM_ADDRESS_MASK);
                size_t wrsize=((uint32_t)mappings[i].start+mappings[i].size)-(uint32_t)lastpageaddr;
                size_t wroffset=((uint32_t)lastpageaddr-(uint32_t)mappings[i].start)+mappings[i].offset;
                //dbgpf("AMM: Writing %i bytes from  %x to %i.\n", wrsize, lastpageaddr, wroffset);
                size_t pos=fs_seek(file, 0, true);
                if (file.mode & FS_Write) {
                    fs_seek(file, wroffset, false);
                    fs_write(file, wrsize, lastpageaddr);
                }
                memset(lastpageaddr, 0, wrsize);
                if(file.mode & FS_Read) {
                    fs_seek(file, wroffset, false);
                    fs_read(file, wrsize, lastpageaddr);
                }
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
                    if(file.mode & FS_Write) {
                        fs_seek(file, offset, false);
                        fs_write(file, VMM_PAGE_SIZE, (char *) virtaddr);
                    }
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
    hold_lock hl(amm_lock, false);
    vector<amm_filemap> &mappings=*amm_filemappings;
    for(size_t i=0; i<mappings.size(); ++i){
        if(mappings[i].file.filedata != file.filedata) continue;
        pid_t curpid=proc_current_pid;
        proc_switch(mappings[i].pid);
       ///dbgpf("AMM: Closing memory mapping %i\n", i);
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
                //dbgpf("AMM: Re-mapping page at %x\n", virtaddr);
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

void amm_closemap(uint64_t id) {
    hold_lock hl(amm_lock, false);
    vector<amm_filemap> &mappings=*amm_filemappings;
    for(size_t i=0; i<mappings.size(); ++i){
        if(mappings[i].id != id) continue;
        amm_flush(mappings[i].file);
        pid_t curpid=proc_current_pid;
        proc_switch(mappings[i].pid);
        //dbgpf("AMM: Closing memory mapping %i\n", i);
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
                //dbgpf("AMM: Re-mapping page at %x\n", virtaddr);
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
            if(mappings[i].id == id){
                mappings.erase(i);
                changed=true;
                break;
            }
        }
    }
}