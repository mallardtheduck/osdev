#include "syscalls.hpp"
#include "locks.hpp"

int module_syscall(int fn, void *p){
	switch(fn){
	case module_api::SYS_PANIC:{
		panic((char*)p);
		}break;
	case module_api::SYS_MALLOC:{
		return (int)malloc((size_t)p);
		}break;
	case module_api::SYS_FREE:{
		free(p);
		}break;
	case module_api::SYS_MEMSET:{
		struct ms_p{void *ptr; char value; size_t num;};
		ms_p &ms_pa=*(ms_p*)p;
		memset(ms_pa.ptr, ms_pa.value, ms_pa.num);
		}break;
	case module_api::SYS_MEMCPY:{
		struct mc_p{void *dst; void *src; size_t size;};
		mc_p &mc_pa=*(mc_p*)p;
		memcpy(mc_pa.dst, mc_pa.src, mc_pa.size);
		}break;
	case module_api::SYS_MEMMOVE:{
		struct mm_p{void *dst; void *src; size_t size;};
		mm_p &mm_pa=*(mm_p*)p;
		memmove(mm_pa.dst, mm_pa.src, mm_pa.size);
		}break;
	case module_api::SYS_STRCMP:{
		struct sc_p{char *s1; char *s2;};
		sc_p &sc_pa=*(sc_p*)p;
		return strcmp(sc_pa.s1, sc_pa.s2);
		}break;
	case module_api::SYS_STRNCPY:{
		struct snc_p{char *dst; char *src; size_t num;};
		snc_p &snc_pa=*(snc_p*)p;
		strncpy(snc_pa.dst, snc_pa.src, snc_pa.num);
		}break;
	case module_api::SYS_INITLOCK:{
		init_lock(*(lock*)p);
		}break;
	case module_api::SYS_TAKELOCK:{
		take_lock(*(lock*)p);
		}break;
	case module_api::SYS_TRYLOCK:{
		return try_take_lock(*(lock*)p);
		}break;
	case module_api::SYS_UNLOCK:{
		release_lock(*(lock*)p);
		}break;
	case module_api::SYS_DBGOUT:{
		dbgout((char*)p);
		}break;
	case module_api::SYS_NEWTHREAD:{
		struct nt_p{void(*entry)(void*); void *param;};
		nt_p &nt_pa=*(nt_p*)p;
		sch_new_thread(nt_pa.entry, nt_pa.param);
		}break;
	case module_api::SYS_BLOCK:{
		sch_block();
		}break;
	case module_api::SYS_YIELD:{
		sch_yield();
		}break;
	case module_api::SYS_THREADID:{
		return (uint32_t)&sch_get_id();
		}break;
	case module_api::SYS_PRIORITY:{
		sch_set_priority((uint32_t)p);
		}break;
	case module_api::SYS_ENDTHREAD:{
		sch_end_thread();
		}break;
	case module_api::SYS_UNBLOCK:{
		//TODO:Implement
		}break;
	}
	return 0;
}

int user_syscall(int, void*){return 0;}
