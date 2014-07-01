#include "kernel.hpp"
#include "locks.hpp"

#define MAX_REGIONS 64


extern char _start, _end;

struct mm_region;
struct mm_allocation{
	mm_allocation *next, *prev;
	mm_region *reg;
	size_t size;
	char bytes[];
} __attribute__((packed));

struct mm_region{
	char *base;
	size_t size;
	bool valid;
	mm_allocation *head;
};

lock mm_lock;

mm_region mm_regions[MAX_REGIONS]={};

void mm_alloctest();

void mm_init(multiboot_info_t *mbt){
	init_lock(mm_lock);
	dbgout("MM: Init\n");
	dbgpf("MM: Kernel start: 0x%x end: 0x%x\n", &_start, &_end);

	size_t total=0;
	int cregion=0;
	memory_map_t *mmap = (memory_map_t*)mbt->mmap_addr;
	while(mmap < (memory_map_t*)mbt->mmap_addr + mbt->mmap_length) {
		if(mmap->type == 1 && mmap->length_low > 0){
			dbgpf("MM: Usable region base: 0x%x size: %uKB\n", mmap->base_addr_low, mmap->length_low/1024);
			if(mmap->base_addr_low < 1024*1024 && mmap->length_low < 1024*1024){
				dbgpf("MM: Ignoring low 1MB RAM\n");
			}else{
				mm_region r;
				r.base=(char*)mmap->base_addr_low;
				r.size=mmap->length_low;
				r.head=NULL;
				r.valid=true;
				if(r.base <= &_end && r.base + r.size >= &_end){
					dbgpf("MM: Kernel is in this region.\n");
					size_t overlap = &_end - (char*)r.base;
					r.size-=overlap;
					r.base=&_end;
				}
				dbgout("MM: clearmem\n");
				memset(r.base, 0xFE, r.size);
				mm_regions[cregion]=r;
				++cregion;
			}
			total += mmap->length_low;
		}
		mmap = (memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
	}
	printf("MM: %iKB RAM\n", total/1024);
	for(int i=0; mm_regions[i].valid; ++i){
		dbgpf("MM: Using %iKB at 0x%x\n", mm_regions[i].size/1024, mm_regions[i].base);
	}
	mm_alloctest();
	dbgout("MM: Allocation test completed.\n");
	size_t freemem=mm_getfreemem();
	printf("MM: %iKB FREE\n", freemem/1024);
}

void *mm_alloc(size_t bytes){
	panic("(MM) mm_alloc called!\n");
	hold_lock lck(mm_lock);
	bytes += sizeof(mm_allocation);
	for(int i=0; i< MAX_REGIONS; ++i){
		if(!mm_regions[i].valid) break;
		size_t sizeleft=mm_regions[i].size;
		mm_allocation *node=mm_regions[i].head;
		if((!node && sizeleft > bytes) //Cases where allocation is at beginning of region.
			|| (node && (size_t)((char*)node - (char*)mm_regions[i].base) >= bytes)){
			mm_allocation *alloc=(mm_allocation*)mm_regions[i].base;
			memset(alloc, 0xAA, bytes);
			alloc->next=node;
			alloc->prev=NULL;
			alloc->reg=&mm_regions[i];
			alloc->size=bytes;
			if(!node) mm_regions[i].head=alloc;
			else node->prev=alloc;
			//dbgpf("Allocated %x at start of region. Allocation node at %x.\n", alloc->bytes, alloc);
			return alloc->bytes;
		}
		while(node){
			if((!node->next && sizeleft - node->size >= bytes)
				|| (node->next && (size_t)node->next - (size_t)((char*)node + node->size) >= bytes)){
				mm_allocation *alloc=(mm_allocation*)((char*)node + node->size);
				memset(alloc, 0xAA, bytes);
				alloc->next=node->next;
				alloc->prev=node;
				alloc->reg=&mm_regions[i];
				alloc->size=bytes;
				if(alloc->prev){
					alloc->prev->next=alloc;
				}
				if(alloc->next){
					alloc->next->prev=alloc;
				}
				//dbgpf("MM: Allocated %x within region. Allocation node at %x.\n", alloc->bytes, alloc);
				return alloc->bytes;
			}
			if(node->next) sizeleft-=node->size;
			node=node->next;
		}
		
	}
	return NULL;
}

void mm_free(void *ptr){
	panic("(MM) mm_free called!\n");
	if(!ptr) return;
	hold_lock hl(mm_lock);
	mm_allocation *alloc=(mm_allocation*)ptr-1;
	if(!(alloc->reg->base <= (char*)alloc && (char*)alloc->reg->base + alloc->reg->size >= (char*)alloc + alloc->size)){
		dbgpf("MM: Pointer %x, Region: base: %x size: %i, Allocation: base: %x size: %i\n",
			ptr, alloc->reg->base, alloc->reg->size, alloc, alloc->size);
		panic("(MM) Pointer passed to mm_free fails sanity check!\n");
	}
	if(alloc->prev){
		alloc->prev->next=alloc->next;
	}else{
		alloc->reg->head=alloc->next;
	}
	if(alloc->next){
		alloc->next->prev=alloc->prev;
	}
	memset(alloc, 0xFE, alloc->size);
	//dbgpf("MM: Successfully freed %x\n", ptr);
}

void mm_alloctest(){
	size_t freemem=mm_getfreemem();
	#define MM_TESTBLOCKSIZE (100*1024)
	int ntests=(freemem/MM_TESTBLOCKSIZE)+1;
	void **tests=(void**)mm_alloc(sizeof(void*)*ntests);
	memset(tests, 0, sizeof(void*)*ntests);
	for(int i=0; i < ntests; ++i){
		tests[i]=(char*)mm_alloc(MM_TESTBLOCKSIZE);
		if(!tests[i]){
			dbgpf("MM: Alloctest: allocated %i blocks.\n", i-1);
			break;
		}
		memset(tests[i], 'Q', MM_TESTBLOCKSIZE);
	}
	mm_getfreemem();
	for(int i=0; i<ntests; ++i){
		if(tests[i]) mm_free(tests[i]);
	}
	mm_getfreemem();
}

size_t mm_getfreemem(){
	take_lock(mm_lock);
	size_t ret=0;
	for(int i=0; i< MAX_REGIONS; ++i){
		if(!mm_regions[i].valid) break;
		size_t sizeleft=mm_regions[i].size;
		//dbgpf("Region %i size: %iKB\n", i, sizeleft/1024);
		mm_allocation *node=mm_regions[i].head;
		while(node){
			//dbgpf("Allocation in region %i: size: %i bytes\n", i, node->size);
			if((char*)node < mm_regions[i].base ||
				(char*)node + node->size > mm_regions[i].base + mm_regions[i].size){
				dbgpf("MM: Allocation in region %i: base: %x size: %i bytes (end: %x)\n", i, node, node->size, (char*)node + node->size);
				dbgpf("MM: Region %i: base: %x size: %i bytes (end: %x)\n", i, mm_regions[i].base, mm_regions[i].size, mm_regions[i].base + mm_regions[i].size);
				if((char*)node + node->size > mm_regions[i].base + mm_regions[i].size){
					dbgout("MM: Allocation end > region end.\n");
				}else if((char*)node < mm_regions[i].base){
					dbgout("MM: Allocation base < region base.\n");
				}else{
					panic("(UNIVERSE) Boolean logic failure.\n");
				}
				panic("(MM)Invalid/corrupt memory allocation detected!\n");
			}
			sizeleft-=node->size;
			node=node->next;
		}
		dbgpf("MM: Region %i remaining: %iKB\n", i, sizeleft/1024);
		ret+=sizeleft;
	}
	release_lock(mm_lock);
	return ret;
}
