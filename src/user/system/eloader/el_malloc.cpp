#include "el_malloc.hpp"
#include "util.hpp"

const size_t Heap_Base = 0xE0000000;
const size_t Heap_Size = 16 * 1024 * 1024;
const size_t Heap_Pages = Heap_Size / Page_Size;
uint32_t heap_bitmap[Heap_Pages / 32] = {0};

extern "C" int liballoc_lock() {
	return 0;
}
extern "C" int liballoc_unlock() {
	return 0;
}

static bool getbit(size_t index){
	size_t idx = index / 32;
	size_t bit = index % 32;
	return !!(heap_bitmap[idx] & (1 << bit));
}

static void setbit(size_t index, bool value){
	size_t idx = index / 32;
	size_t bit = index % 32;
	
	if(value) heap_bitmap[idx] |= (1 << bit);
	else heap_bitmap[idx] &= ~(1 << bit);
}

extern "C" void* liballoc_alloc(size_t pages){
	size_t base = 0;
	size_t found = 0;
	for(size_t i = 0; i < Heap_Pages; ++i){
		if(!getbit(i)){
			if(found == 0) base = i;
			++found;
		}else{
			found = 0;
		}
		if(found == pages){
			for(size_t j = base; j < base + pages; ++j){
				bt_alloc_at(1, (void*)(Heap_Base + (j * Page_Size)));
				setbit(j, true);
			}
			return (void*)(Heap_Base + (Page_Size * base));
		}
	}
	return NULL;
}

extern "C" int liballoc_free(void *addr, size_t pages){
	size_t offset = (size_t)addr - Heap_Base;
	size_t index = offset / Page_Size;
	for(size_t i = index; i < index + pages; ++i){
		bt_free_pages((void*)(Heap_Base + (i * Page_Size)), 1);
		setbit(i, false);
	}
	return 0;
}