#include "user_api.hpp"
#include "../include/btos_api.h"
#include "locks.hpp"
#pragma GCC diagnostic ignored "-Wunused-parameter"

void userapi_handler(int, isr_regs*);
void userapi_syscall(uint16_t fn, isr_regs *regs);

#define USERAPI_HANDLE_CALL(name) \
 	case btos_api::name:\
 		name ## _call(regs);\
 		break

#define USERAPI_HANDLER(name) static void name ## _call(isr_regs *regs)

void userapi_init(){
	dbgpf("UAPI: Init");
	int_handle(0x80, &userapi_handler);
}

void userapi_handler(int, isr_regs *regs){
	uint16_t *id=(uint16_t*)(&regs->eax);
	uint16_t ext=id[1], fn=id[0];
	dbgpf("UAPI: Extension: %x, Function: %x\n", (int)ext, (int)fn);
	if(ext==0){
		userapi_syscall(fn, regs);
	}else{
		regs->eax=-1;
		return;
	}
}

static bool is_safe_ptr(uint32_t ptr){
	return ptr>=VMM_USERSPACE_START;
}

USERAPI_HANDLER(zero){
	printf("%s", regs->ebx);
}

USERAPI_HANDLER(BT_ALLOC_PAGES){
	regs->eax = (uint32_t)vmm_alloc(regs->ebx, false);
}

USERAPI_HANDLER(BT_FREE_PAGES){
	if(is_safe_ptr(regs->ebx)){
		vmm_free((void*)regs->ebx, regs->ecx);
	}
}

USERAPI_HANDLER(BT_CREATE_LOCK){
	lock *l=new lock();
	regs->eax=proc_add_lock(l);
}

USERAPI_HANDLER(BT_LOCK){
	take_lock(*proc_get_lock(regs->eax));
}

USERAPI_HANDLER(BT_TRY_LOCK){
	regs->eax=try_take_lock(*proc_get_lock(regs->eax));
}

USERAPI_HANDLER(BT_UNLOCK){
	release_lock(*proc_get_lock(regs->eax));
}

USERAPI_HANDLER(BT_DESTROY_LOCK){
	lock *l=proc_get_lock(regs->eax);
	delete l;
}

USERAPI_HANDLER(BT_MOUNT){
	if(is_safe_ptr(regs->ebx) && is_safe_ptr(regs->ecx) && is_safe_ptr(regs->edx)){
		regs->eax=fs_mount((char*)regs->ebx, (char*)regs->ecx, (char*)regs->edx);
	}
}

USERAPI_HANDLER(BT_UNMOUNT){
	if(is_safe_ptr(regs->ebx)){
		regs->eax=fs_unmount((char*)regs->ebx);
	}
}

USERAPI_HANDLER(BT_EXIT){
	pid_t pid=proc_current_pid;
	sch_setpid(0);
	proc_switch(0);
	proc_end(pid);
	sch_end_thread();
}


void userapi_syscall(uint16_t fn, isr_regs *regs){
	switch(fn){
		case 0:
         	zero_call(regs);
         	break;

		USERAPI_HANDLE_CALL(BT_ALLOC_PAGES);
		USERAPI_HANDLE_CALL(BT_FREE_PAGES);

		USERAPI_HANDLE_CALL(BT_CREATE_LOCK);
		USERAPI_HANDLE_CALL(BT_LOCK);
		USERAPI_HANDLE_CALL(BT_TRY_LOCK);
		USERAPI_HANDLE_CALL(BT_UNLOCK);
		USERAPI_HANDLE_CALL(BT_DESTROY_LOCK);

		USERAPI_HANDLE_CALL(BT_MOUNT);
		USERAPI_HANDLE_CALL(BT_UNMOUNT);

		USERAPI_HANDLE_CALL(BT_EXIT);
		default:
			regs->eax=-1;
			break;
	}
}

