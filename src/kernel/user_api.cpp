#include "user_api.hpp"
#include <btos/btos_api.h>
#include "locks.hpp"
#pragma GCC diagnostic ignored "-Wunused-parameter"

void userapi_handler(int, isr_regs*);
void userapi_syscall(uint16_t fn, isr_regs *regs);

#define USERAPI_HANDLE_CALL(name) \
 	case btos_api::name:\
 		name ## _call(regs);\
 		break

#define USERAPI_HANDLER(name) static void name ## _call(isr_regs *regs)

#define RAISE_US_ERROR() uapi_raise_us_error(__FUNCTION__) 

void userapi_init(){
	dbgpf("UAPI: Init\n");
	int_handle(0x80, &userapi_handler);
}

void userapi_handler(int, isr_regs *regs){
	enable_interrupts();
	if(proc_get_status() == proc_status::Ending) sch_end_thread();
	uint16_t *id=(uint16_t*)(&regs->eax);
	uint16_t ext=id[1], fn=id[0];
	//dbgpf("UAPI: Extension: %x, Function: %x\n", (int)ext, (int)fn);
	if(ext==0){
		userapi_syscall(fn, regs);
	}else{
		user_call_extension(ext, fn, regs);
	}
	if(sch_get_abortlevel() != 1){
		dbgpf("UAPI: Abortlevel: %i, ext: %i fn: %x\n", sch_get_abortlevel(), (int)ext, (int)fn);
		panic("(UAPI) Non-zero abortlevel on return to userspace!\n");
	}
    if(sch_user_abort() || proc_get_status() == proc_status::Ending) sch_end_thread();
}

bool is_safe_ptr(uint32_t ptr, size_t size, pid_t pid){
	if(ptr >= MM2::MM2_Kernel_Boundary){
		pid_t cur_pid = proc_current_pid;
		proc_switch(pid);
		size_t i = 0;
		while(i<size){
			size_t res = MM2::current_pagedir->resolve_addr((char*)ptr + i);
			i += res;
			if(!res){ 
				proc_switch(cur_pid);
				dbgpf("UAPI: Verification of pointer %x (%i) for %i failed.\n", ptr, (int)size, (int)pid);
				return false;
			}
		}
		proc_switch(cur_pid);
		return true;
	}else return false;
}

bool is_safe_string(uint32_t ptr, pid_t pid){
	char c = 0xFF;
	for(size_t i = 0; c != '\0'; ++i){
		if(!is_safe_ptr(ptr + i, 1, pid)){
			dbgpf("UAPI: Verification of string pointer %x failed after %lu chars.\n", ptr, i);
			return false;
		}
		c = ((char*)ptr)[i];
	}
	return true;
}

static void uapi_raise_us_error(const char *fn){
	dbgpf("UAPI: PID %llu error in call: %s\n", proc_current_pid, fn);
    debug_event_notify(proc_current_pid, sch_get_id(), bt_debug_event::Exception, bt_exception::InvalidArg);
    proc_terminate();
}

USERAPI_HANDLER(zero){
	dbgout((char*)regs->ebx);
}

USERAPI_HANDLER(BT_ALLOC_PAGES){
	regs->eax = (uint32_t)MM2::current_pagedir->alloc(regs->ebx, MM2::MM2_Alloc_Mode::Userlow);
}

USERAPI_HANDLER(BT_ALLOC_AT){
	size_t pages = regs->ebx;
	size_t addr = regs->ecx;
	if(addr != addr % MM2::MM2_Address_Mask) return;
	if(addr < MM2::MM2_Kernel_Boundary) return;
	for(size_t i = 0; i < pages; ++i){
		size_t pageaddr = addr + (i * MM2::MM2_Page_Size);
		if(pageaddr < MM2::MM2_Kernel_Boundary) return;
		MM2::current_pagedir->alloc_pages_at(1, (void*)pageaddr);
	}
}

USERAPI_HANDLER(BT_FREE_PAGES){
	if(is_safe_ptr(regs->ebx, 0)){
		MM2::current_pagedir->free_pages((void*)regs->ebx, regs->ecx);
	}else RAISE_US_ERROR();
}

static void close_shm_space_handle(void *f){
    MM2::shm_close(*(uint64_t*)f);
    delete (uint64_t*)f;
}

USERAPI_HANDLER(BT_CREATE_SHM){
	uint64_t *id = new uint64_t(MM2::shm_create(regs->ebx));
	bt_handle_info handle=create_handle(kernel_handle_types::shm_space, id, &close_shm_space_handle);
	regs->eax = proc_add_handle(handle);
}

USERAPI_HANDLER(BT_SHM_ID){
	bt_handle_info h=proc_get_handle((handle_t)regs->ebx);
	if(is_safe_ptr(regs->ecx, sizeof(uint64_t*))){
		if(h.open && h.type == kernel_handle_types::shm_space){
			*(uint64_t*)regs->ecx = *(uint64_t*)h.value;
		}
	}else RAISE_US_ERROR();
}

static void close_shm_map_handle(void *f){
    MM2::shm_close_map(*(uint64_t*)f);
    delete (uint64_t*)f;
}

USERAPI_HANDLER(BT_SHM_MAP){
	if(is_safe_ptr(regs->ebx, sizeof(btos_api::bt_shm_mapping*))){
		btos_api::bt_shm_mapping *mapping = (btos_api::bt_shm_mapping*)regs->ebx;
		if(is_safe_ptr((uint32_t)mapping->addr, mapping->pages * MM2::MM2_Page_Size)){
			uint64_t *id = new uint64_t(MM2::shm_map(mapping->id, mapping->addr, mapping->offset, mapping->pages, mapping->flags));
			bt_handle_info handle=create_handle(kernel_handle_types::shm_mapping, id, &close_shm_map_handle);
			regs->eax = proc_add_handle(handle);
		}else RAISE_US_ERROR();
	}else RAISE_US_ERROR();	
}

USERAPI_HANDLER(BT_GET_ARGC){
	regs->eax=proc_get_argc();
}

USERAPI_HANDLER(BT_GET_ARG){
	if(is_safe_ptr(regs->ecx, regs->edx)){
		regs->eax=proc_get_arg(regs->ebx, (char*)regs->ecx, regs->edx);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_CREATE_LOCK){
	lock *l=new lock();
	regs->eax=proc_add_lock(l);
}

USERAPI_HANDLER(BT_LOCK){
    lock *l=proc_get_lock(regs->ebx);
    if(l) {
		take_lock_exclusive(*l, sch_get_id(), true);
		sch_abortable(true);
	}
}

USERAPI_HANDLER(BT_TRY_LOCK){
    lock *l=proc_get_lock(regs->ebx);
    if(l && try_take_lock_exclusive(*l)){
		regs->eax = 1;
		sch_abortable(true);
	}else regs->eax = 0;
}

USERAPI_HANDLER(BT_UNLOCK){
    lock *l=proc_get_lock(regs->ebx);
	if(l){
		release_lock(*l, sch_get_id(), true);
		sch_abortable(false);
	}
}

USERAPI_HANDLER(BT_DESTROY_LOCK){
	lock *l=proc_get_lock(regs->ebx);
	if(l) {
        proc_remove_lock(regs->ebx);
        delete l;
    }
}

USERAPI_HANDLER(BT_CREATE_ATOM){
	if(is_safe_ptr(regs->ebx, sizeof(uint64_t))){
		bt_atom *a = atom_create(*(uint64_t*)regs->ebx);
		bt_handle_info handle = create_handle(kernel_handle_types::atom, (void*)a, (handle_close_fn)&atom_destroy);
		regs->eax = proc_add_handle(handle);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MODIFY_ATOM){
	bt_handle_info h=proc_get_handle((handle_t)regs->ebx);
	if(h.open && h.type == kernel_handle_types::atom && is_safe_ptr(regs->edx, sizeof(uint64_t))){
		*(uint64_t*)regs->edx = atom_modify((bt_atom*)h.value, (bt_atom_modify::Enum)regs->ecx, *(uint64_t*)regs->edx);
		regs->eax = 1;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MAKE_WAIT_ATOM){
	bt_handle_info h=proc_get_handle((handle_t)regs->ebx);
	if(h.open && h.type == kernel_handle_types::atom && is_safe_ptr(regs->edx, sizeof(uint64_t))){
		auto hdl = atom_make_wait((bt_atom*)h.value, (bt_atom_compare::Enum)regs->ecx, *(uint64_t*)regs->edx);
		regs->eax = proc_add_handle(hdl);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_CMPXCHG_ATOM){
	bt_handle_info h=proc_get_handle((handle_t)regs->ebx);
	if(h.open && h.type == kernel_handle_types::atom && is_safe_ptr(regs->ecx, sizeof(uint64_t)) && is_safe_ptr(regs->edx, sizeof(uint64_t))){
		*(uint64_t*)regs->edx = atom_cmpxchg((bt_atom*)h.value, *(uint64_t*)regs->ecx, *(uint64_t*)regs->edx);
		regs->eax = 1;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_READ_ATOM){
	bt_handle_info h=proc_get_handle((handle_t)regs->ebx);
	if(h.open && h.type == kernel_handle_types::atom && is_safe_ptr(regs->ecx, sizeof(uint64_t))){
		*(uint64_t*)regs->ecx = atom_read((bt_atom*)h.value);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MOUNT){
	if(is_safe_string(regs->ebx) && is_safe_string(regs->ecx) && is_safe_string(regs->edx)){
		regs->eax=fs_mount((char*)regs->ebx, (char*)regs->ecx, (char*)regs->edx);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_UNMOUNT){
	if(is_safe_string(regs->ebx)){
		regs->eax=fs_unmount((char*)regs->ebx);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_FOPEN){
    if(is_safe_string(regs->ebx)){
        file_handle *file=new file_handle(fs_open((char*)regs->ebx, (fs_mode_flags)regs->ecx));
        if(file->valid){
        	regs->eax=proc_add_file(file);
        } else {
        	regs->eax=0;
        	delete file;
        }
    }else RAISE_US_ERROR();
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
    if(file){
		if(is_safe_ptr(regs->edx, regs->ecx)){
	        regs->eax=fs_write(*file, regs->ecx, (char*)regs->edx);
	    }else RAISE_US_ERROR();
    }
}

USERAPI_HANDLER(BT_FREAD){
    file_handle *file=proc_get_file(regs->ebx);
    if(file){
	    if(is_safe_ptr(regs->edx, regs->ecx)){
	        regs->eax=fs_read(*file, regs->ecx, (char*)regs->edx);
	    }else RAISE_US_ERROR();
    }
}

USERAPI_HANDLER(BT_FIOCTL){
	file_handle *file=proc_get_file(regs->ebx);
	if(file){
	    if(is_safe_ptr(regs->edx, sizeof(btos_api::bt_fioctl_buffer))){
	    	btos_api::bt_fioctl_buffer *buf=(btos_api::bt_fioctl_buffer*)regs->edx;
	    	if(buf->size==0 || is_safe_ptr((uint32_t)buf->buffer, buf->size)){
	    		regs->eax=fs_ioctl(*file, regs->ecx, buf->size, buf->buffer);
	    	}else RAISE_US_ERROR();
	    }else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_FSEEK){
    file_handle *file=proc_get_file(regs->ebx);
    if(file){
	    if(is_safe_ptr(regs->ecx, sizeof(bt_filesize_t))){
			bt_filesize_t *pos = (bt_filesize_t*)regs->ecx;
	        *pos=fs_seek(*file, *pos, regs->edx);
			regs->eax = 0; 
	    }else RAISE_US_ERROR();
    }
}

USERAPI_HANDLER(BT_FSETSIZE){
	file_handle *file=proc_get_file(regs->ebx);
	if(file){
	    if(is_safe_ptr(regs->ecx, sizeof(bt_filesize_t))){
			bt_filesize_t *size = (bt_filesize_t*)regs->ecx;
			regs->eax = fs_setsize(*file, *size);
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_FFLUSH){
    file_handle *file=proc_get_file(regs->ebx);
    if(file){
        fs_flush(*file);
    }
}

static void close_filemap_handle(void *f){
    MM2::mm2_closemap(*(uint64_t*)f);
    delete (uint64_t*)f;
}

USERAPI_HANDLER(BT_MMAP){
    file_handle *file=proc_get_file(regs->ebx);
    if(file){
		if(is_safe_ptr(regs->edx, sizeof(btos_api::bt_mmap_buffer))){
		    btos_api::bt_mmap_buffer *buffer=(btos_api::bt_mmap_buffer*)regs->edx;
		    if(!is_safe_ptr((uint32_t)buffer->buffer, buffer->size)) return;
		    uint64_t *id=new uint64_t(MM2::mm2_mmap(buffer->buffer, *file, regs->ecx, buffer->size));
		    bt_handle_info handle=create_handle(kernel_handle_types::memory_mapping, id, &close_filemap_handle);
		    regs->eax= proc_add_handle(handle);
			return;
		}else RAISE_US_ERROR();
		regs->eax=0;
    }
}

USERAPI_HANDLER(BT_DOPEN){
   //TODO: Flags...
    if(is_safe_string(regs->ebx)){
        dir_handle *dir=new dir_handle(fs_open_dir((char*)regs->ebx, (fs_mode_flags)regs->ecx));
        if(dir->valid) {
        	regs->eax=proc_add_dir(dir);
        }else{
        	regs->eax=0;
        	delete dir;
        }
    }else RAISE_US_ERROR();
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
	if(dir){
		if(is_safe_ptr(regs->ecx, sizeof(directory_entry))){
			directory_entry *entry=(directory_entry*)regs->ecx;
			fs_write_dir(*dir, *entry);
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_DREAD){
	dir_handle *dir=proc_get_dir(regs->ebx);
	if(dir){
		if(is_safe_ptr(regs->ecx, sizeof(directory_entry))){
			directory_entry *entry=(directory_entry*)regs->ecx;
			*entry=fs_read_dir(*dir);
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_DSEEK){
	dir_handle *dir=proc_get_dir(regs->ebx);
	if(dir){
		regs->eax=fs_seek_dir(*dir, regs->ecx, regs->edx);
	}
}

USERAPI_HANDLER(BT_STAT){
	if(is_safe_string(regs->ebx) && is_safe_ptr(regs->ecx, sizeof(directory_entry))){
		directory_entry *entry=(directory_entry*)regs->ecx;
		*entry=fs_stat((char*)regs->ebx);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_FORMAT){
	if(is_safe_string(regs->ebx) && is_safe_string(regs->ecx) && (!regs->edx || is_safe_ptr(regs->edx, 1))){
		regs->eax = fs_format((const char*)regs->ebx, (const char*)regs->ecx, (void*)regs->edx);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_LOAD_MODULE){
	if(is_safe_string(regs->ebx)){
        char *params=is_safe_string(regs->ecx)?(char*)regs->ecx:NULL;
		load_module((char*)regs->ebx, params);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_GETENV){
	if(is_safe_string(regs->ebx) && (regs->edx == 0 || is_safe_ptr(regs->ecx, regs->edx))){
		string value=proc_getenv((char*)regs->ebx, true);
		if(value != ""){
			if(regs->edx) strncpy((char*)regs->ecx, value.c_str(), regs->edx);
			regs->eax=value.length() + 1;
		}else regs->eax=0;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_SETENV){
	if(is_safe_string(regs->ebx) && is_safe_string(regs->ecx)){
		proc_setenv((char*)regs->ebx, (char*)regs->ecx, regs->edx, true);
		regs->eax=true;
	}
}

USERAPI_HANDLER(BT_SPAWN){
	if(is_safe_string(regs->ebx) &&  (!regs->ecx || is_safe_ptr(regs->edx, sizeof(char*) * regs->ecx))){
		if(regs->ecx){
			size_t argc=regs->ecx;
			char **argv=(char**)regs->edx;
			for(size_t i=0; i<argc; ++i){
				if(!is_safe_string((uint32_t)argv[i])){
					RAISE_US_ERROR();
					return;
				}
			}
		}
		dbgpf("UAPI:Spawning %s\n", (char*)regs->ebx);
		regs->eax=proc_spawn((char*)regs->ebx, regs->ecx, (char**)regs->edx);
	}else RAISE_US_ERROR();
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
	debug_event_notify(proc_current_pid, sch_get_id(), bt_debug_event::ThreadEnd);
	//proc_switch(0);
	proc_end(pid);
	sch_end_thread();
}

USERAPI_HANDLER(BT_GETPID){
	regs->eax=(uint32_t)proc_current_pid;
}

USERAPI_HANDLER(BT_PROCSTATUS){
	if(is_safe_ptr(regs->ebx, sizeof(pid_t))){
		regs->eax = proc_get_status(*(pid_t*)regs->ebx);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_NEW_THREAD){
    if(proc_get_status()==proc_status::Ending){
        regs->eax=0;
        return;
    }
    if(is_safe_ptr(regs->ebx, sizeof(proc_entry)) && is_safe_ptr(regs->edx, 0) && (!regs->ecx || is_safe_ptr(regs->ecx, 0))){
        uint64_t id=proc_new_user_thread((proc_entry)regs->ebx, (void*)regs->ecx, (void*)regs->edx);
        regs->eax=proc_get_thread_handle(id);
    }else RAISE_US_ERROR();
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
	debug_event_notify(proc_current_pid, sch_get_id(), bt_debug_event::ThreadEnd);
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
	if(is_safe_ptr(regs->ebx, sizeof(btos_api::bt_msg_header)) && is_safe_ptr(regs->ecx, sizeof(uint64_t))){
		btos_api::bt_msg_header header=*(btos_api::bt_msg_header*)regs->ebx;
		if(header.length && !is_safe_ptr((uint32_t)header.content, header.length)) return;
		uint64_t &ret=*(uint64_t*)regs->ecx;
		header.flags=header.flags | btos_api::bt_msg_flags::UserSpace;
		header.from=proc_current_pid;
		header.critical=false;
		if(header.length > btos_api::BT_MSG_MAX) return;
		ret=proc_send_message(header);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_RECV){
	if(is_safe_ptr(regs->ebx, sizeof(btos_api::bt_msg_header))){
		btos_api::bt_msg_header &header=*(btos_api::bt_msg_header*)regs->ebx;
		if(regs->ecx){
			header=msg_recv_block();
			header.content=NULL;
		}else{
			regs->eax=(uint32_t)msg_recv(header);
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_NEXTMSG){
	if(is_safe_ptr(regs->ebx, sizeof(btos_api::bt_msg_header))){
		btos_api::bt_msg_header &header=*(btos_api::bt_msg_header*)regs->ebx;
		msg_nextmessage(header);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_CONTENT){
	if(is_safe_ptr(regs->ebx, sizeof(btos_api::bt_msg_header)) && is_safe_ptr(regs->ecx, regs->edx)){
		regs->eax=msg_getcontent(*(btos_api::bt_msg_header*)regs->ebx, (void*)regs->ecx, regs->edx);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_ACK){
	if(is_safe_ptr(regs->ebx, sizeof(btos_api::bt_msg_header))){
		msg_acknowledge(*(btos_api::bt_msg_header*)regs->ebx);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MSGWAIT){
	proc_message_wait();
}

USERAPI_HANDLER(BT_SUBSCRIBE){
	msg_subscribe((btos_api::bt_kernel_messages::Enum)regs->ebx);
}

USERAPI_HANDLER(BT_UNSUBSCRIBE){
	msg_unsubscribe((btos_api::bt_kernel_messages::Enum)regs->ebx);
}

USERAPI_HANDLER(BT_RECVFILTERED){
	if(is_safe_ptr(regs->ebx, sizeof(btos_api::bt_msg_filter)) && is_safe_ptr(regs->ecx, sizeof(btos_api::bt_msg_header))){
		(*(btos_api::bt_msg_header*)regs->ecx) = msg_recv_filtered(*(btos_api::bt_msg_filter*)regs->ebx, proc_current_pid, (bool)regs->edx);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_NEXTMSGFILTERED){
	if(is_safe_ptr(regs->ebx, sizeof(btos_api::bt_msg_filter)) && is_safe_ptr(regs->ecx, sizeof(btos_api::bt_msg_header))){
		btos_api::bt_msg_header &header=*(btos_api::bt_msg_header*)regs->ecx;
		msg_nextmessage_filtered(*(btos_api::bt_msg_filter*)regs->ebx, header);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MSGQUERY){
	if(is_safe_ptr(regs->ebx, sizeof(uint64_t))){
		regs->eax = msg_query_recieved(*(uint64_t*)regs->ebx);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_QUERY_EXT){
	if(is_safe_string(regs->ebx)){
		regs->eax = get_extension_id((char*)regs->ebx);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MULTI_CALL){
	if(is_safe_ptr(regs->ebx, regs->ecx * sizeof(btos_api::bt_syscall_item))){
		//dbgpf("UAPI: BT_MULTI_CALL: %i calls.\n", (int)regs->ecx);
		btos_api::bt_syscall_item *items = (btos_api::bt_syscall_item*)regs->ebx;
		isr_regs fake_regs;
		for(size_t i = 0; i < regs->ecx; ++i){
			//dbgpf("UAPI: BT_MULTI_CALL %i - %x\n", (int)i, items[i].call_id);
			fake_regs.eax = items[i].call_id;
			fake_regs.ebx = items[i].p1;
			fake_regs.ecx = items[i].p2;
			fake_regs.edx = items[i].p3;
			userapi_handler(0x80, &fake_regs);
			items[i].call_id = fake_regs.eax;
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_CLOSEHANDLE){
    bt_handle_info h=proc_get_handle((handle_t)regs->ebx);
    if(h.open && h.type!=kernel_handle_types::invalid){
        close_handle(h);
        proc_remove_handle((handle_t)regs->ebx);
    }
}

USERAPI_HANDLER(BT_QUERYHANDLE){
	bt_handle_info h=proc_get_handle((handle_t)regs->ebx);
	if(h.open && h.type!=kernel_handle_types::invalid){
		regs->eax = 1;
	}else{
		regs->eax = 0;
	}
}

USERAPI_HANDLER(BT_WAITHANDLE){
	bt_handle_info h = proc_get_handle((handle_t)regs->ebx);
	if(h.open && h.type != kernel_handle_types::invalid){
		wait_handle(h);
	}
}

USERAPI_HANDLER(BT_MAKE_WAITALL){
	size_t size = regs->ecx;
	if(is_safe_ptr(regs->ebx, size * sizeof(bt_handle_t))){
		bt_handle_t *sarr = (bt_handle_t*)regs->ebx;
		auto harr = new bt_handle_info[size];
		for(size_t i = 0; i < size; ++i){
			harr[i] = proc_get_handle(sarr[i]);
			if(!harr[i].open || harr[i].type == kernel_handle_types::invalid){
				delete[] harr;
				return;
			}
		}
		auto hdl = create_wait_all_handle(harr, size);
		regs->eax = proc_add_handle(hdl);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MAKE_WAITANY){
	size_t size = regs->ecx;
	if(is_safe_ptr(regs->ebx, size * sizeof(bt_handle_t))){
		bt_handle_t *sarr = (bt_handle_t*)regs->ebx;
		auto harr = new bt_handle_info[size];
		for(size_t i = 0; i < size; ++i){
			harr[i] = proc_get_handle(sarr[i]);
			if(!harr[i].open || harr[i].type == kernel_handle_types::invalid){
				delete[] harr;
				return;
			}
		}
		auto hdl = create_wait_any_handle(harr, size);
		regs->eax = proc_add_handle(hdl);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_WAIT_INDEX){
	bt_handle_info h = proc_get_handle((handle_t)regs->ebx);
	if(h.open && h.type == kernel_handle_types::wait){
		regs->eax = get_wait_index(h);
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
        USERAPI_HANDLE_CALL(BT_ALLOC_AT);
        //USERAPI_HANDLE_CALL(BT_GUARD_PAGE);
        //USERAPI_HANDLE_CALL(BT_CREATE_REGION);
        
		USERAPI_HANDLE_CALL(BT_CREATE_SHM);
		USERAPI_HANDLE_CALL(BT_SHM_ID);
		USERAPI_HANDLE_CALL(BT_SHM_MAP);

		USERAPI_HANDLE_CALL(BT_GET_ARGC);
		USERAPI_HANDLE_CALL(BT_GET_ARG);

        //Locking
		USERAPI_HANDLE_CALL(BT_CREATE_LOCK);
		USERAPI_HANDLE_CALL(BT_LOCK);
		USERAPI_HANDLE_CALL(BT_TRY_LOCK);
		USERAPI_HANDLE_CALL(BT_UNLOCK);
		USERAPI_HANDLE_CALL(BT_DESTROY_LOCK);
		USERAPI_HANDLE_CALL(BT_CREATE_ATOM);
		USERAPI_HANDLE_CALL(BT_MODIFY_ATOM);
		USERAPI_HANDLE_CALL(BT_MAKE_WAIT_ATOM);
		USERAPI_HANDLE_CALL(BT_CMPXCHG_ATOM);
		USERAPI_HANDLE_CALL(BT_READ_ATOM);

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
		USERAPI_HANDLE_CALL(BT_FSETSIZE);
        USERAPI_HANDLE_CALL(BT_FFLUSH);
        USERAPI_HANDLE_CALL(BT_MMAP);
		USERAPI_HANDLE_CALL(BT_DOPEN);
		USERAPI_HANDLE_CALL(BT_DCLOSE);
		USERAPI_HANDLE_CALL(BT_DWRITE);
		USERAPI_HANDLE_CALL(BT_DREAD);
		USERAPI_HANDLE_CALL(BT_DSEEK);
		USERAPI_HANDLE_CALL(BT_STAT);
		USERAPI_HANDLE_CALL(BT_FORMAT);

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
		USERAPI_HANDLE_CALL(BT_PROCSTATUS);

		//Messaging
		USERAPI_HANDLE_CALL(BT_SEND);
		USERAPI_HANDLE_CALL(BT_RECV);
		USERAPI_HANDLE_CALL(BT_NEXTMSG);
		USERAPI_HANDLE_CALL(BT_CONTENT);
		USERAPI_HANDLE_CALL(BT_ACK);
		USERAPI_HANDLE_CALL(BT_MSGWAIT);
		USERAPI_HANDLE_CALL(BT_SUBSCRIBE);
		USERAPI_HANDLE_CALL(BT_UNSUBSCRIBE);
		USERAPI_HANDLE_CALL(BT_RECVFILTERED);
		USERAPI_HANDLE_CALL(BT_NEXTMSGFILTERED);
		USERAPI_HANDLE_CALL(BT_MSGQUERY);

		//Handles
        USERAPI_HANDLE_CALL(BT_CLOSEHANDLE);
		USERAPI_HANDLE_CALL(BT_QUERYHANDLE);
		USERAPI_HANDLE_CALL(BT_WAITHANDLE);
		USERAPI_HANDLE_CALL(BT_MAKE_WAITALL);
		USERAPI_HANDLE_CALL(BT_MAKE_WAITANY);
		USERAPI_HANDLE_CALL(BT_WAIT_INDEX);

		//Extensions
		USERAPI_HANDLE_CALL(BT_QUERY_EXT);
		
		//Magic
		USERAPI_HANDLE_CALL(BT_MULTI_CALL);

		default:
			regs->eax=-1;
			break;
	}
}

