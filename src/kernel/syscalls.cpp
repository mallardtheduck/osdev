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
		sch_unblock(*(uint64_t*)p);
		}break;
	case module_api::SYS_ADDDEVICE:{
		struct ad_p{char *name; drv_driver *driver;};
		ad_p &ad_pa=*(ad_p*)p;
		drv_add_device(ad_pa.name, ad_pa.driver);
		}break;
	case module_api::SYS_GETDEVICE:{
		return (int)drv_get((char*)p);
		}break;
	case module_api::SYS_FIRSTDEVICE:{
		return (int)drv_firstdevice((char**)p);
		}break;
	case module_api::SYS_NEXTDEVICE:{
		struct nd_p{void *itr; char **name;};
		nd_p &nd_pa=*(nd_p*)p;
    	return (int)drv_nextdevice(nd_pa.itr, nd_pa.name);
    	}break;
    case module_api::SYS_DEVOPEN:{
    	return (int)drv_open((char*)p);
    	}break;
    case module_api::SYS_DEVCLOSE:{
    	return (int)drv_close(p);
    	}break;
    case module_api::SYS_DEVREAD:{
    	struct dr_p{void* handle; size_t bytes; char *buffer;};
    	dr_p &dr_pa=*(dr_p*)p;
    	return (int)drv_read(dr_pa.handle, dr_pa.bytes, dr_pa.buffer);
    	}break;
    case module_api::SYS_DEVWRITE:{
		struct dw_p{void* handle; size_t bytes; char *buffer;};
		dw_p &dw_pa=*(dw_p*)p;
		return (int)drv_write(dw_pa.handle, dw_pa.bytes, dw_pa.buffer);
		}break;
	case module_api::SYS_DEVSEEK:{
		struct ds_p{void *handle; size_t pos; bool relative;};
		ds_p &ds_pa=*(ds_p*)p;
		drv_seek(ds_pa.handle, ds_pa.pos, ds_pa.relative);
		}break;
	case module_api::SYS_DEVIOCTL:{
		struct di_p{void *handle; int fn; size_t bytes; char *buf;};
        di_p &di_pa=*(di_p*)p;
        return drv_ioctl(di_pa.handle, di_pa.fn, di_pa.bytes, di_pa.buf);
        }break;
    case module_api::SYS_DEVTYPE:{
    	return drv_get_type((char*)p);
    	}break;
    case module_api::SYS_DEVDESC:{
    	return (int)drv_get_desc((char*)p);
    	}break;
    case module_api::SYS_HANDLEINT:{
    	struct ha_p{int intno; int_handler handler;};
    	ha_p &ha_pa=*(ha_p*)p;
    	int_handle(ha_pa.intno, ha_pa.handler);
    	}break;
	case module_api::SYS_HANDLEIRQ:{
		struct ha_p{int irqno; int_handler handler;};
		ha_p &ha_pa=*(ha_p*)p;
		irq_handle(ha_pa.irqno, ha_pa.handler);
		}break;
	}
	return 0;
}

int user_syscall(int, void*){return 0;}
