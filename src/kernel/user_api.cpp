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
	dbgpf("UAPI: Init\n");
	int_handle(0x80, &userapi_handler);
}

void userapi_handler(int, isr_regs *regs){
	enable_interrupts();
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
	dbgout((char*)regs->ebx);
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
	take_lock(*proc_get_lock(regs->ebx));
}

USERAPI_HANDLER(BT_TRY_LOCK){
	regs->eax=try_take_lock(*proc_get_lock(regs->ebx));
}

USERAPI_HANDLER(BT_UNLOCK){
	release_lock(*proc_get_lock(regs->ebx));
}

USERAPI_HANDLER(BT_DESTROY_LOCK){
	lock *l=proc_get_lock(regs->ebx);
	proc_remove_lock(regs->ebx);
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

USERAPI_HANDLER(BT_FOPEN){
    //TODO: Flags...
    if(is_safe_ptr(regs->ebx)){
        file_handle *file=new file_handle(fs_open((char*)regs->ebx));
        if(file->valid) regs->eax=proc_add_file(file);
        else regs->eax=0;
    }
}

USERAPI_HANDLER(BT_FCLOSE){
    file_handle *file=proc_get_file(regs->ebx);
    if(file){
        regs->eax=fs_close(*file);
        proc_remove_file(regs->ebx);
        delete file;
    }
}

USERAPI_HANDLER(BT_FWRITE){
    file_handle *file=proc_get_file(regs->ebx);
    if(file && is_safe_ptr(regs->edx)){
        regs->eax=fs_write(*file, regs->ecx, (char*)regs->edx);
    }
}

USERAPI_HANDLER(BT_FREAD){
    file_handle *file=proc_get_file(regs->ebx);
    if(file && is_safe_ptr(regs->edx)){
        regs->eax=fs_read(*file, regs->ecx, (char*)regs->edx);
    }
}

USERAPI_HANDLER(BT_FIOCTL){
	file_handle *file=proc_get_file(regs->ebx);
    if(file && is_safe_ptr(regs->edx)){
    	btos_api::bt_fioctl_buffer *buf=(btos_api::bt_fioctl_buffer*)regs->edx;
    	if(is_safe_ptr((uint32_t)buf->buffer)){
    		regs->eax=fs_ioctl(*file, regs->ecx, buf->size, buf->buffer);
    	}
    }
}

USERAPI_HANDLER(BT_FSEEK){
    file_handle *file=proc_get_file(regs->ebx);
    if(file){
        regs->eax=fs_seek(*file, regs->ecx, regs->edx);
    }
}

USERAPI_HANDLER(BT_DOPEN){
   //TODO: Flags...
    if(is_safe_ptr(regs->ebx)){
        dir_handle *dir=new dir_handle(fs_open_dir((char*)regs->ebx));
        if(dir->valid) regs->eax=proc_add_dir(dir);
        else regs->eax=0;
    }
}

USERAPI_HANDLER(BT_DCLOSE){
	dir_handle *dir=proc_get_dir(regs->ebx);
	if(dir){
		regs->eax=fs_close_dir(*dir);
		proc_remove_dir(regs->ebx);
		delete dir;
	}
}

USERAPI_HANDLER(BT_DWRITE){
	dir_handle *dir=proc_get_dir(regs->ebx);
	if(dir && is_safe_ptr(regs->ecx)){
		directory_entry *entry=(directory_entry*)regs->ecx;
		fs_write_dir(*dir, *entry);
	}
}

USERAPI_HANDLER(BT_DREAD){
	dir_handle *dir=proc_get_dir(regs->ebx);
	if(dir && is_safe_ptr(regs->ecx)){
		directory_entry *entry=(directory_entry*)regs->ecx;
		*entry=fs_read_dir(*dir);
	}
}

USERAPI_HANDLER(BT_DSEEK){
	dir_handle *dir=proc_get_dir(regs->ebx);
	if(dir){
		regs->eax=fs_seek_dir(*dir, regs->ecx, regs->edx);
	}
}

USERAPI_HANDLER(BT_STAT){
	if(is_safe_ptr(regs->ebx) && is_safe_ptr(regs->ecx)){
		directory_entry *entry=(directory_entry*)regs->ecx;
		*entry=fs_stat((char*)regs->ebx);
	}
}

USERAPI_HANDLER(BT_LOAD_MODULE){
	if(is_safe_ptr(regs->ebx)){
		load_module((char*)regs->ebx);
	}
}

USERAPI_HANDLER(BT_GETENV){
	if(is_safe_ptr(regs->ebx) && is_safe_ptr(regs->ecx)){
		string value=proc_getenv((char*)regs->ebx, true);
		if(value.length() < regs->edx){
			strncpy((char*)regs->ecx, value.c_str(), regs->edx);
			regs->eax=true;
		}else regs->eax=false;
	}
}

USERAPI_HANDLER(BT_SETENV){
	if(is_safe_ptr(regs->ebx) && is_safe_ptr(regs->ecx)){
		proc_setenv((char*)regs->ebx, (char*)regs->ecx, regs->edx, true);
		regs->eax=true;
	}
}

USERAPI_HANDLER(BT_SPAWN){
	if(is_safe_ptr(regs->ebx) && is_safe_ptr(regs->edx)){
		//TODO: Parameters...
		regs->eax=proc_spawn((char*)regs->ebx, "");
	}
}

USERAPI_HANDLER(BT_WAIT){
	//TODO: Implement...
}

USERAPI_HANDLER(BT_KILL){
	proc_end(regs->ebx);
}

USERAPI_HANDLER(BT_PRIORITIZE){
	//TODO: Implement...
}

USERAPI_HANDLER(BT_EXIT){
	pid_t pid=proc_current_pid;;
	proc_switch(0);
	proc_end(pid);
	sch_end_thread();
}

USERAPI_HANDLER(BT_GETPID){
	regs->eax=(uint32_t)proc_current_pid;
}

void userapi_syscall(uint16_t fn, isr_regs *regs){
	switch(fn){
		case 0:
         	zero_call(regs);
         	break;

        //Memory managment
		USERAPI_HANDLE_CALL(BT_ALLOC_PAGES);
		USERAPI_HANDLE_CALL(BT_FREE_PAGES);

        //Locking
		USERAPI_HANDLE_CALL(BT_CREATE_LOCK);
		USERAPI_HANDLE_CALL(BT_LOCK);
		USERAPI_HANDLE_CALL(BT_TRY_LOCK);
		USERAPI_HANDLE_CALL(BT_UNLOCK);
		USERAPI_HANDLE_CALL(BT_DESTROY_LOCK);

        //VFS
		USERAPI_HANDLE_CALL(BT_MOUNT);
		USERAPI_HANDLE_CALL(BT_UNMOUNT);

        //Filesystem
		USERAPI_HANDLE_CALL(BT_FOPEN);
		USERAPI_HANDLE_CALL(BT_FCLOSE);
		USERAPI_HANDLE_CALL(BT_FWRITE);
		USERAPI_HANDLE_CALL(BT_FREAD);
		USERAPI_HANDLE_CALL(BT_FIOCTL);
		USERAPI_HANDLE_CALL(BT_FSEEK);
		USERAPI_HANDLE_CALL(BT_DOPEN);
		USERAPI_HANDLE_CALL(BT_DCLOSE);
		USERAPI_HANDLE_CALL(BT_DWRITE);
		USERAPI_HANDLE_CALL(BT_DREAD);
		USERAPI_HANDLE_CALL(BT_DSEEK);
		USERAPI_HANDLE_CALL(BT_STAT);

		//Modules
		USERAPI_HANDLE_CALL(BT_LOAD_MODULE);

		//Environment
		USERAPI_HANDLE_CALL(BT_GETENV);
		USERAPI_HANDLE_CALL(BT_SETENV);

		//Process
		USERAPI_HANDLE_CALL(BT_SPAWN);
		USERAPI_HANDLE_CALL(BT_WAIT);
		USERAPI_HANDLE_CALL(BT_KILL);
		USERAPI_HANDLE_CALL(BT_PRIORITIZE);
		USERAPI_HANDLE_CALL(BT_EXIT);
		USERAPI_HANDLE_CALL(BT_GETPID);

		default:
			regs->eax=-1;
			break;
	}
}

