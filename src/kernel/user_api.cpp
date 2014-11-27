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
	//dbgpf("UAPI: Extension: %x, Function: %x\n", (int)ext, (int)fn);
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
	regs->eax = (uint32_t)vmm_alloc(regs->ebx, vmm_allocmode::Userlow);
}

USERAPI_HANDLER(BT_FREE_PAGES){
	if(is_safe_ptr(regs->ebx)){
		vmm_free((void*)regs->ebx, regs->ecx);
	}
}

USERAPI_HANDLER(BT_CLOSEHANDLE){
    bt_handle_info h=proc_get_handle((handle_t)regs->eax);
    if(h.open && h.type!=kernel_handle_types::invalid){
        close_handle(h);
        proc_remove_handle((handle_t)regs->eax);
    }
}

USERAPI_HANDLER(BT_GET_ARGC){
	regs->eax=proc_get_argc();
}

USERAPI_HANDLER(BT_GET_ARG){
	if(is_safe_ptr(regs->ecx)){
		regs->eax=proc_get_arg(regs->ebx, (char*)regs->ecx, regs->edx);
	}
}

USERAPI_HANDLER(BT_CREATE_LOCK){
	lock *l=new lock();
	regs->eax=proc_add_lock(l);
}

USERAPI_HANDLER(BT_LOCK){
    lock *l=proc_get_lock(regs->ebx);
    if(l) take_lock_exclusive(*l);
}

USERAPI_HANDLER(BT_TRY_LOCK){
    lock *l=proc_get_lock(regs->ebx);
    if(l) regs->eax=try_take_lock_exclusive(*l);
}

USERAPI_HANDLER(BT_UNLOCK){
    lock *l=proc_get_lock(regs->ebx);
	if(l) release_lock(*l);
}

USERAPI_HANDLER(BT_DESTROY_LOCK){
	lock *l=proc_get_lock(regs->ebx);
	if(l) {
        proc_remove_lock(regs->ebx);
        delete l;
    }
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
    if(is_safe_ptr(regs->ebx)){
        file_handle *file=new file_handle(fs_open((char*)regs->ebx, (fs_mode_flags)regs->ecx));
        if(file->valid){
        	regs->eax=proc_add_file(file);
        } else {
        	regs->eax=0;
        	delete file;
        }
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
    	if(buf->size==0 || is_safe_ptr((uint32_t)buf->buffer)){
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

USERAPI_HANDLER(BT_FFLUSH){
    file_handle *file=proc_get_file(regs->ebx);
    if(file){
        fs_flush(*file);
    }
}

static void close_filemap_handle(void *f){
    amm_closemap(*(uint64_t*)f);
    delete (uint64_t*)f;
}

USERAPI_HANDLER(BT_MMAP){
    file_handle *file=proc_get_file(regs->ebx);
    if(file && is_safe_ptr(regs->edx)){
        btos_api::bt_mmap_buffer *buffer=(btos_api::bt_mmap_buffer*)regs->edx;
        if(!is_safe_ptr((uint32_t)buffer->buffer)) return;
        uint64_t *id=new uint64_t(amm_mmap(buffer->buffer, *file, regs->ecx, buffer->size));
        bt_handle_info handle=create_handle(kernel_handle_types::memory_mapping, id, &close_filemap_handle);
        regs->eax= proc_add_handle(handle);
    }
    regs->eax=0;
}

USERAPI_HANDLER(BT_DOPEN){
   //TODO: Flags...
    if(is_safe_ptr(regs->ebx)){
        dir_handle *dir=new dir_handle(fs_open_dir((char*)regs->ebx, (fs_mode_flags)regs->ecx));
        if(dir->valid) {
        	regs->eax=proc_add_dir(dir);
        }else{
        	regs->eax=0;
        	delete dir;
        }
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
        char *params=is_safe_ptr(regs->ecx)?(char*)regs->ecx:NULL;
		load_module((char*)regs->ebx, params);
	}
}

USERAPI_HANDLER(BT_GETENV){
	if(is_safe_ptr(regs->ebx) && is_safe_ptr(regs->ecx)){
		string value=proc_getenv((char*)regs->ebx, true);
		if(value != "" && value.length() < regs->edx){
			strncpy((char*)regs->ecx, value.c_str(), regs->edx);
			regs->eax=value.length();
		}else regs->eax=0;
	}
}

USERAPI_HANDLER(BT_SETENV){
	if(is_safe_ptr(regs->ebx) && is_safe_ptr(regs->ecx)){
		proc_setenv((char*)regs->ebx, (char*)regs->ecx, regs->edx, true);
		regs->eax=true;
	}
}

USERAPI_HANDLER(BT_SPAWN){
	if(is_safe_ptr(regs->ebx) &&  (!regs->ecx || is_safe_ptr(regs->edx))){
		if(regs->ecx){
			size_t argc=regs->ecx;
			char **argv=(char**)regs->edx;
			for(size_t i=0; i<argc; ++i){
				if(!is_safe_ptr((uint32_t)argv[i])) return;
			}
		}
		dbgpf("UAPI:Spawning %s\n", (char*)regs->ebx);
		regs->eax=proc_spawn((char*)regs->ebx, regs->ecx, (char**)regs->edx);
	}
}

USERAPI_HANDLER(BT_WAIT){
	regs->eax=proc_wait(regs->ebx);
}

USERAPI_HANDLER(BT_KILL){
	proc_end(regs->ebx);
}

USERAPI_HANDLER(BT_PRIORITIZE){
	//TODO: Implement...
}

USERAPI_HANDLER(BT_EXIT){
	pid_t pid=proc_current_pid;
	proc_setreturn(regs->ebx);
	proc_switch(0);
	proc_end(pid);
	sch_end_thread();
}

USERAPI_HANDLER(BT_GETPID){
	regs->eax=(uint32_t)proc_current_pid;
}

USERAPI_HANDLER(BT_NEW_THREAD){
    if(proc_get_status()==proc_status::Ending){
        regs->eax=0;
        return;
    }
    if(is_safe_ptr(regs->ebx) && is_safe_ptr(regs->edx) && (!regs->ecx || is_safe_ptr(regs->ecx))){
        uint64_t id=proc_new_user_thread((proc_entry)regs->ebx, (void*)regs->ecx, (void*)regs->edx);
        regs->eax=proc_get_thread_handle(id);
    }
}

USERAPI_HANDLER(BT_BLOCK_THREAD){
    sch_abortable(true);
    sch_block();
    sch_abortable(false);
}

USERAPI_HANDLER(BT_UNBLOCK_THREAD){
    uint64_t id=proc_get_thread(regs->ebx);
    sch_unblock(id);
}

USERAPI_HANDLER(BT_GET_THREAD){
    regs->eax=proc_get_thread_handle(sch_get_id());
}

USERAPI_HANDLER(BT_WAIT_THREAD){
    uint64_t id=proc_get_thread(regs->ebx);
    if(id){
        sch_wait(id);
    }
}

USERAPI_HANDLER(BT_END_THREAD){
    sch_end_thread();
}

USERAPI_HANDLER(BT_YIELD){
    sch_yield();
}

USERAPI_HANDLER(BT_THREAD_ABORT){
    uint64_t id=proc_get_thread(regs->ebx);
    if(id){
        proc_remove_thread(id);
        sch_abort(id);
    }
}

USERAPI_HANDLER(BT_SEND){
	if(is_safe_ptr(regs->ebx) && is_safe_ptr(regs->ecx)){
		btos_api::bt_msg_header &header=*(btos_api::bt_msg_header*)regs->ebx;
		uint64_t &ret=*(uint64_t*)regs->ecx;
		header.flags=header.flags | btos_api::bt_msg_flags::UserSpace;
		header.from=proc_current_pid;
		if(header.length > btos_api::BT_MSG_MAX) return;
		ret=proc_send_message(header);
	}
}

void userapi_syscall(uint16_t fn, isr_regs *regs){
	switch(fn){
		case 0:
         	zero_call(regs);
         	break;

        //Memory managment
		USERAPI_HANDLE_CALL(BT_ALLOC_PAGES);
		USERAPI_HANDLE_CALL(BT_FREE_PAGES);
        //USERAPI_HANDLE_CALL(BT_ALLOC_AT);
        //USERAPI_HANDLE_CALL(BT_GUARD_PAGE);
        //USERAPI_HANDLE_CALL(BT_PF_HANDLE);
        USERAPI_HANDLE_CALL(BT_CLOSEHANDLE);

		USERAPI_HANDLE_CALL(BT_GET_ARGC);
		USERAPI_HANDLE_CALL(BT_GET_ARG);

        //Locking
		USERAPI_HANDLE_CALL(BT_CREATE_LOCK);
		USERAPI_HANDLE_CALL(BT_LOCK);
		USERAPI_HANDLE_CALL(BT_TRY_LOCK);
		USERAPI_HANDLE_CALL(BT_UNLOCK);
		USERAPI_HANDLE_CALL(BT_DESTROY_LOCK);

        //Threading
        USERAPI_HANDLE_CALL(BT_NEW_THREAD);
        USERAPI_HANDLE_CALL(BT_WAIT_THREAD);
        //USERAPI_HANDLE_CALL(BT_THREAD_STATUS);
        USERAPI_HANDLE_CALL(BT_BLOCK_THREAD);
        USERAPI_HANDLE_CALL(BT_UNBLOCK_THREAD);
        USERAPI_HANDLE_CALL(BT_GET_THREAD);
        USERAPI_HANDLE_CALL(BT_END_THREAD);
        USERAPI_HANDLE_CALL(BT_YIELD);
        //USERAPI_HANDLE_CALL(BT_THREAD_PRIORITIZE);
        USERAPI_HANDLE_CALL(BT_THREAD_ABORT);

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
        USERAPI_HANDLE_CALL(BT_FFLUSH);
        USERAPI_HANDLE_CALL(BT_MMAP);
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

		//Messaging
		USERAPI_HANDLE_CALL(BT_SEND);
		//USERAPI_HANDLE_CALL(BT_RECV);
		//USERAPI_HANDLE_CALL(BT_SUBSCRIBE);

		default:
			regs->eax=-1;
			break;
	}
    if(sch_user_abort()) sch_end_thread();
}

