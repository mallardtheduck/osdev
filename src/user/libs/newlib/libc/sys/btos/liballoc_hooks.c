#include "liballoc.ih"
#include <btos.h>
#include <stdio.h>

static bt_handle_t la_lock;
static bt_handle_t pm_lock;

typedef struct{
	bool inuse;
	void *from;
	void *to;
} ptr_mapping;

static ptr_mapping *mappings = NULL;
static size_t mappings_sz = 0;

static void init(){
	static bool done = false;
	if(!done){
		la_lock = bt_create_lock();
		done = true;
	}
}

int liballoc_lock(){
	init();
	bt_lock(la_lock);
	return 0;
}

int liballoc_unlock(){
	bt_unlock(la_lock);
	return 0;
}

void *liballoc_alloc(size_t n){
	return bt_alloc_pages(n);
}

int liballoc_free(void *p, size_t n){
	bt_free_pages(p, n);
	return 0;
}

void *malloc(size_t sz){
	return la_malloc(sz);
}

void *realloc(void *p, size_t sz){
	return la_realloc(p, sz);
}

void *calloc(size_t c, size_t sz){
	return la_calloc(c, sz);
}

void *_calloc_r(struct _reent *r, size_t num, size_t size){
	(void)r;
	return calloc(num, size);
}

void *_malloc_r(struct _reent *r, size_t sz){
	(void)r;
	return malloc(sz);
}

void *_realloc_r(struct _reent *r, void *p, size_t sz){
	(void)r;
	return realloc(p, sz);
}

static void init_mapping(){
	static bool done = false;
	if(!done){
		pm_lock = bt_create_lock();
	}
}

static void add_mapping(void *from, void *to){
	init_mapping();
	bt_lock(pm_lock);
	if(!mappings){
		mappings = calloc(1, sizeof(ptr_mapping));
		mappings_sz = 1;
	}
	for(size_t i = 0; i < mappings_sz; ++i){
		if(!mappings[i].inuse){
			mappings[i].inuse = true;
			mappings[i].from = from;
			mappings[i].to = to;
			bt_unlock(pm_lock);
			return;
		}
	}
	++mappings_sz;
	mappings = realloc(mappings, sizeof(ptr_mapping) * mappings_sz);
	mappings[mappings_sz - 1] .inuse = true;
	mappings[mappings_sz - 1].from = from;
	mappings[mappings_sz - 1].to = to;
	bt_unlock(pm_lock);
}

static void *get_mapping(void *to){
	init_mapping();
	bt_lock(pm_lock);
	for(size_t i = 0; i < mappings_sz; ++i){
		if(!mappings[i].inuse && mappings[i].to == to){
			bt_unlock(pm_lock);
			return mappings[i].from;
		}
	}
	return NULL;
	bt_unlock(pm_lock);
}

static void clear_mapping(void *from){
	init_mapping();
	bt_lock(pm_lock);
	for(size_t i = 0; i < mappings_sz; ++i){
		if(!mappings[i].inuse && mappings[i].from == from){
			mappings[i].inuse = false;
			bt_unlock(pm_lock);
			return;
		}
	}
	bt_unlock(pm_lock);
}

void free(void *p){
	void *mp = get_mapping(p);
	if(mp){
		clear_mapping(mp);
		la_free(mp);
	}else{
		la_free(p);
	}
}

void _free_r(struct _reent *r, void *p){
	(void)r;
	free(p);
}

void cfree(void *p){
	free(p);
}

void *memalign(size_t a, size_t sz){
	void *from = malloc(sz + a);
	void *to = NULL;
	if(a != 0){
		uint32_t pre = ((uint32_t)from / a) * a;
		to = (void*)(pre + a);
		add_mapping(from, to);
	}else{
		to = from;
	}
	return to;
}

void *valloc(size_t sz){
	return memalign(4096, sz);
}
