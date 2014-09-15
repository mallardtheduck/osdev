#include "kernel.hpp"
#include "ministl.hpp"
#include "locks.hpp"

static const uint32_t ec_user = (1 << 2);

struct amm_pagedetails{
	amm_flags::Enum flags;
	pid_t owner;
	void *ptr;
};

extern lock vmm_lock, sch_lock;
static bool in_reserve=false;

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
		bool lock_vmm=true;
		if(vmm_lock.lock==sch_get_id()){
			release_lock(vmm_lock);
		}else{
			lock_vmm=false;
			release_lock(sch_lock);
            take_lock_exclusive(vmm_lock);
            take_lock_exclusive(sch_lock);
			release_lock(vmm_lock);
		}
		in_reserve=true;
		pointer ret=(pointer)vmm_alloc(pages);
		in_reserve=false;
		if(lock_vmm) take_lock_exclusive(vmm_lock);
		release_lock(sch_lock);
		return ret;
	}
	void deallocate (pointer p, size_type n){
		size_t pages=((n*sizeof(value_type))/VMM_PAGE_SIZE)+1;
        take_lock_exclusive(sch_lock);
		bool lock_vmm=true;
		if(vmm_lock.lock==sch_get_id()){
			release_lock(vmm_lock);
		}else{
			lock_vmm=false;
			release_lock(sch_lock);
            take_lock_exclusive(vmm_lock);
            take_lock_exclusive(sch_lock);
			release_lock(vmm_lock);
		}
		vmm_free(p, pages);
		if(lock_vmm) take_lock_exclusive(vmm_lock);
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

static bool amm_inited=false;
static lock amm_lock;
extern char _start, _end;

void amm_page_fault_handler(int, isr_regs *regs);

void amm_init(){
	amm_allocated_pages=new amm_alloc_map();
	size_t reservation=(&_end-&_start)/VMM_PAGE_SIZE + 4096;
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
	if(!in_reserve && amm_allocated_pages->capacity() < amm_allocated_pages->size() + 128){
		amm_allocated_pages->reserve(amm_allocated_pages->capacity() + 1024);
	}
	{	hold_lock hl(amm_lock);
		amm_allocated_pages->insert(amm_alloc_map::value_type(pageaddr, p));
	}
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

void amm_page_fault_handler(int, isr_regs *regs){
	uint32_t addr;
	asm volatile("mov %%cr2, %%eax\r\n mov %%eax,%0": "=m"(addr): : "eax");
	dbgpf("AMM: Page fault on %x at %x!\n", addr, regs->eip);
    if(regs->error_code & ec_user){
        proc_terminate();
    }else {
        if (addr < VMM_PAGE_SIZE) panic("(AMM) Probable NULL pointer dereference!");
        else panic("(AMM) Page fault!");
    }
}