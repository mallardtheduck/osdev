#include "user_api.hpp"
#include <btos/btos_api.h>
#include "locks.hpp"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Waddress-of-packed-member"

void userapi_handler(ICPUState &state);
void userapi_syscall(uint16_t fn, ICPUState &state);

#define USERAPI_HANDLE_CALL(name) \
 	case btos_api::name:\
 		name ## _call(state);\
 		break

#define USERAPI_HANDLER(name) static void name ## _call(ICPUState &state)

#define RAISE_US_ERROR() uapi_raise_us_error(__FUNCTION__) 
#define RAISE_SECURITY_ERROR() uapi_raise_security_error(__FUNCTION__) 

void userapi_init(){
	dbgpf("UAPI: Init\n");
	GetHAL().HandleUserSyscall(&userapi_handler);
}

void userapi_handler(ICPUState &state){
	GetHAL().EnableInterrupts();
	if(proc_get_status() == btos_api::bt_proc_status::Ending) sch_end_thread();
	uint16_t *id=(uint16_t*)(&state.Get32BitRegister(Generic_Register::GP_Register_A));
	uint16_t ext=id[1], fn=id[0];
	//dbgpf("UAPI: Extension: %x, Function: %x\n", (int)ext, (int)fn);
	if(ext==0){
		userapi_syscall(fn, state);
	}else{
		user_call_extension(ext, fn, state);
	}
	if(sch_get_abortlevel() != 1){
		dbgpf("UAPI: Abortlevel: %i, ext: %i fn: %x\n", sch_get_abortlevel(), (int)ext, (int)fn);
		panic("(UAPI) Non-zero abortlevel on return to userspace!\n");
	}
    if(sch_user_abort() || proc_get_status() == btos_api::bt_proc_status::Ending) sch_end_thread();
}

bool is_safe_ptr(uint32_t ptr, size_t size, bt_pid_t pid){
	if(ptr >= MM2::MM2_Kernel_Boundary){
		pid_t cur_pid = CurrentProcess().ID();
		proc_switch(pid);
		size_t i = 0;
		while(i<size){
			size_t res = MM2::current_pagedir->resolve_addr((char*)ptr + i);
			i += res;
			if(!res){ 
				proc_switch(cur_pid);
				dbgpf("UAPI: Verification of pointer %lx (%i) for %i failed.\n", ptr, (int)size, (int)pid);
				return false;
			}
		}
		proc_switch(cur_pid);
		return true;
	}else return false;
}

bool is_safe_string(uint32_t ptr, bt_pid_t pid){
	char c = 0xFF;
	for(size_t i = 0; c != '\0'; ++i){
		if(!is_safe_ptr(ptr + i, 1, pid)){
			dbgpf("UAPI: Verification of string pointer %lx failed after %lu chars.\n", ptr, i);
			return false;
		}
		c = ((char*)ptr)[i];
	}
	return true;
}

static void uapi_raise_us_error(const char *fn){
	dbgpf("UAPI: PID %llu error in call: %s\n", CurrentProcess().ID(), fn);
	debug_event_notify(CurrentProcess().ID(), sch_get_id(), bt_debug_event::Exception, bt_exception::InvalidArg);
	proc_terminate();
}

[[maybe_unused]]
static void uapi_raise_security_error(const char *fn){
	dbgpf("UAPI: PID %llu error in call: %s\n", CurrentProcess().ID(), fn);
	debug_event_notify(CurrentProcess().ID(), sch_get_id(), bt_debug_event::Exception, bt_exception::SecurityException);
	proc_terminate();
}

USERAPI_HANDLER(zero){
	dbgout((char*)state.Get32BitRegister(Generic_Register::GP_Register_B));
}

USERAPI_HANDLER(BT_ALLOC_PAGES){
	state.Get32BitRegister(Generic_Register::GP_Register_A) = (uint32_t)MM2::current_pagedir->alloc(state.Get32BitRegister(Generic_Register::GP_Register_B), MM2::MM2_Alloc_Mode::Userlow);
}

USERAPI_HANDLER(BT_ALLOC_AT){
	size_t pages = state.Get32BitRegister(Generic_Register::GP_Register_B);
	size_t addr = state.Get32BitRegister(Generic_Register::GP_Register_C);
	if(addr != addr % MM2::MM2_Address_Mask) return;
	if(addr < MM2::MM2_Kernel_Boundary) return;
	for(size_t i = 0; i < pages; ++i){
		size_t pageaddr = addr + (i * MM2::MM2_Page_Size);
		if(pageaddr < MM2::MM2_Kernel_Boundary) return;
		MM2::current_pagedir->alloc_pages_at(1, (void*)pageaddr);
	}
}

USERAPI_HANDLER(BT_FREE_PAGES){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), 0)){
		MM2::current_pagedir->free_pages((void*)state.Get32BitRegister(Generic_Register::GP_Register_B), state.Get32BitRegister(Generic_Register::GP_Register_C));
	}else RAISE_US_ERROR();
}

static void close_shm_space_handle(void *f){
    MM2::shm_close(*(uint64_t*)f);
    delete (uint64_t*)f;
}

USERAPI_HANDLER(BT_CREATE_SHM){
	uint64_t *id = new uint64_t(MM2::shm_create(state.Get32BitRegister(Generic_Register::GP_Register_B)));
	bt_handle_info handle=create_handle(kernel_handle_types::shm_space, id, &close_shm_space_handle);
	state.Get32BitRegister(Generic_Register::GP_Register_A) = proc_add_handle(handle);
}

USERAPI_HANDLER(BT_SHM_ID){
	bt_handle_info h=proc_get_handle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(uint64_t*))){
		if(h.open && h.type == kernel_handle_types::shm_space){
			*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_C) = *(uint64_t*)h.value;
		}
	}else RAISE_US_ERROR();
}

static void close_shm_map_handle(void *f){
    MM2::shm_close_map(*(uint64_t*)f);
    delete (uint64_t*)f;
}

USERAPI_HANDLER(BT_SHM_MAP){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_shm_mapping*))){
		btos_api::bt_shm_mapping *mapping = (btos_api::bt_shm_mapping*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		if(is_safe_ptr((uint32_t)mapping->addr, mapping->pages * MM2::MM2_Page_Size)){
			uint64_t *id = new uint64_t(MM2::shm_map(mapping->id, mapping->addr, mapping->offset, mapping->pages, mapping->flags));
			bt_handle_info handle=create_handle(kernel_handle_types::shm_mapping, id, &close_shm_map_handle);
			state.Get32BitRegister(Generic_Register::GP_Register_A) = proc_add_handle(handle);
		}else RAISE_US_ERROR();
	}else RAISE_US_ERROR();	
}

USERAPI_HANDLER(BT_GET_ARGC){
	state.Get32BitRegister(Generic_Register::GP_Register_A)=proc_get_argc();
}

USERAPI_HANDLER(BT_GET_ARG){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D))){
		state.Get32BitRegister(Generic_Register::GP_Register_A)=proc_get_arg(
			state.Get32BitRegister(Generic_Register::GP_Register_B), 
			(char*)state.Get32BitRegister(Generic_Register::GP_Register_C), 
			state.Get32BitRegister(Generic_Register::GP_Register_D));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_CREATE_LOCK){
	lock *l=new lock();
	state.Get32BitRegister(Generic_Register::GP_Register_A)=proc_add_lock(l);
}

USERAPI_HANDLER(BT_LOCK){
    lock *l=proc_get_lock(state.Get32BitRegister(Generic_Register::GP_Register_B));
    if(l) {
		take_lock_exclusive(*l, sch_get_id(), true);
		sch_abortable(true);
	}
}

USERAPI_HANDLER(BT_TRY_LOCK){
    lock *l=proc_get_lock(state.Get32BitRegister(Generic_Register::GP_Register_B));
    if(l && try_take_lock_exclusive(*l)){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = 1;
		sch_abortable(true);
	}else state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
}

USERAPI_HANDLER(BT_UNLOCK){
    lock *l=proc_get_lock(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(l){
		release_lock(*l, sch_get_id(), true);
		sch_abortable(false);
	}
}

USERAPI_HANDLER(BT_DESTROY_LOCK){
	lock *l=proc_get_lock(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(l) {
        proc_remove_lock(state.Get32BitRegister(Generic_Register::GP_Register_B));
        delete l;
    }
}

USERAPI_HANDLER(BT_CREATE_ATOM){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
		bt_atom *a = atom_create(*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B));
		bt_handle_info handle = create_handle(kernel_handle_types::atom, (void*)a, (handle_close_fn)&atom_destroy);
		state.Get32BitRegister(Generic_Register::GP_Register_A) = proc_add_handle(handle);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MODIFY_ATOM){
	bt_handle_info h=proc_get_handle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(h.open && h.type == kernel_handle_types::atom && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), sizeof(uint64_t))){
		*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_D) = atom_modify(
			(bt_atom*)h.value, 
			(bt_atom_modify::Enum)state.Get32BitRegister(Generic_Register::GP_Register_C), 
			*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_D));
		state.Get32BitRegister(Generic_Register::GP_Register_A) = 1;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MAKE_WAIT_ATOM){
	bt_handle_info h=proc_get_handle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(h.open && h.type == kernel_handle_types::atom && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), sizeof(uint64_t))){
		auto hdl = atom_make_wait((bt_atom*)h.value, (bt_atom_compare::Enum)state.Get32BitRegister(Generic_Register::GP_Register_C), *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_D));
		state.Get32BitRegister(Generic_Register::GP_Register_A) = proc_add_handle(hdl);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_CMPXCHG_ATOM){
	bt_handle_info h=proc_get_handle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(h.open && h.type == kernel_handle_types::atom && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(uint64_t)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), sizeof(uint64_t))){
		*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_D) = atom_cmpxchg((bt_atom*)h.value, *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_C), *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_D));
		state.Get32BitRegister(Generic_Register::GP_Register_A) = 1;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_READ_ATOM){
	bt_handle_info h=proc_get_handle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(h.open && h.type == kernel_handle_types::atom && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(uint64_t))){
		*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_C) = atom_read((bt_atom*)h.value);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MOUNT){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B)) && is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_C)) && is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_D))){
		if(has_perm(0, kperm::MountFS)) state.Get32BitRegister(Generic_Register::GP_Register_A)=fs_mount((char*)state.Get32BitRegister(Generic_Register::GP_Register_B), (char*)state.Get32BitRegister(Generic_Register::GP_Register_C), (char*)state.Get32BitRegister(Generic_Register::GP_Register_D));
		else state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_UNMOUNT){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B))){
		if(has_perm(0, kperm::UnMountFS)) state.Get32BitRegister(Generic_Register::GP_Register_A)=fs_unmount((char*)state.Get32BitRegister(Generic_Register::GP_Register_B));
		else state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_FOPEN){
    if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B))){
        file_handle *file=new file_handle(fs_open((char*)state.Get32BitRegister(Generic_Register::GP_Register_B), (fs_mode_flags)state.Get32BitRegister(Generic_Register::GP_Register_C)));
        if(file->valid){
        	state.Get32BitRegister(Generic_Register::GP_Register_A)=proc_add_file(file);
        } else {
        	state.Get32BitRegister(Generic_Register::GP_Register_A)=0;
        	delete file;
        }
    }else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_FCLOSE){
    file_handle *file=proc_get_file(state.Get32BitRegister(Generic_Register::GP_Register_B));
    if(file){
        state.Get32BitRegister(Generic_Register::GP_Register_A)=fs_close(*file);
        proc_remove_file(state.Get32BitRegister(Generic_Register::GP_Register_B));
        delete file;
    }
}

USERAPI_HANDLER(BT_FWRITE){
    file_handle *file=proc_get_file(state.Get32BitRegister(Generic_Register::GP_Register_B));
    if(file){
		if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), state.Get32BitRegister(Generic_Register::GP_Register_C))){
	        state.Get32BitRegister(Generic_Register::GP_Register_A)=fs_write(*file, state.Get32BitRegister(Generic_Register::GP_Register_C), (char*)state.Get32BitRegister(Generic_Register::GP_Register_D));
	    }else RAISE_US_ERROR();
    }
}

USERAPI_HANDLER(BT_FREAD){
    file_handle *file=proc_get_file(state.Get32BitRegister(Generic_Register::GP_Register_B));
    if(file){
	    if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), state.Get32BitRegister(Generic_Register::GP_Register_C))){
	        state.Get32BitRegister(Generic_Register::GP_Register_A)=fs_read(*file, state.Get32BitRegister(Generic_Register::GP_Register_C), (char*)state.Get32BitRegister(Generic_Register::GP_Register_D));
	    }else RAISE_US_ERROR();
    }
}

USERAPI_HANDLER(BT_FIOCTL){
	file_handle *file=proc_get_file(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(file){
	    if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), sizeof(btos_api::bt_fioctl_buffer))){
	    	btos_api::bt_fioctl_buffer *buf=(btos_api::bt_fioctl_buffer*)state.Get32BitRegister(Generic_Register::GP_Register_D);
	    	if(buf->size==0 || is_safe_ptr((uint32_t)buf->buffer, buf->size)){
	    		state.Get32BitRegister(Generic_Register::GP_Register_A)=fs_ioctl(*file, state.Get32BitRegister(Generic_Register::GP_Register_C), buf->size, buf->buffer);
	    	}else RAISE_US_ERROR();
	    }else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_FSEEK){
    file_handle *file=proc_get_file(state.Get32BitRegister(Generic_Register::GP_Register_B));
    if(file){
	    if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(bt_filesize_t))){
			bt_filesize_t *pos = (bt_filesize_t*)state.Get32BitRegister(Generic_Register::GP_Register_C);
	        *pos=fs_seek(*file, *pos, state.Get32BitRegister(Generic_Register::GP_Register_D));
			state.Get32BitRegister(Generic_Register::GP_Register_A) = 0; 
	    }else RAISE_US_ERROR();
    }
}

USERAPI_HANDLER(BT_FSETSIZE){
	file_handle *file=proc_get_file(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(file){
	    if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(bt_filesize_t))){
			bt_filesize_t *size = (bt_filesize_t*)state.Get32BitRegister(Generic_Register::GP_Register_C);
			state.Get32BitRegister(Generic_Register::GP_Register_A) = fs_setsize(*file, *size);
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_FFLUSH){
    file_handle *file=proc_get_file(state.Get32BitRegister(Generic_Register::GP_Register_B));
    if(file){
        fs_flush(*file);
    }
}

static void close_filemap_handle(void *f){
    MM2::mm2_closemap(*(uint64_t*)f);
    delete (uint64_t*)f;
}

USERAPI_HANDLER(BT_MMAP){
    file_handle *file=proc_get_file(state.Get32BitRegister(Generic_Register::GP_Register_B));
    if(file){
		if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), sizeof(btos_api::bt_mmap_buffer))){
		    btos_api::bt_mmap_buffer *buffer=(btos_api::bt_mmap_buffer*)state.Get32BitRegister(Generic_Register::GP_Register_D);
		    if(!is_safe_ptr((uint32_t)buffer->buffer, buffer->size)) return;
		    uint64_t *id=new uint64_t(MM2::mm2_mmap(buffer->buffer, *file, state.Get32BitRegister(Generic_Register::GP_Register_C), buffer->size));
		    bt_handle_info handle=create_handle(kernel_handle_types::memory_mapping, id, &close_filemap_handle);
		    state.Get32BitRegister(Generic_Register::GP_Register_A)= proc_add_handle(handle);
			return;
		}else RAISE_US_ERROR();
		state.Get32BitRegister(Generic_Register::GP_Register_A)=0;
    }
}

USERAPI_HANDLER(BT_DOPEN){
   //TODO: Flags...
    if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B))){
        dir_handle *dir=new dir_handle(fs_open_dir((char*)state.Get32BitRegister(Generic_Register::GP_Register_B), (fs_mode_flags)state.Get32BitRegister(Generic_Register::GP_Register_C)));
        if(dir->valid) {
        	state.Get32BitRegister(Generic_Register::GP_Register_A)=proc_add_dir(dir);
        }else{
        	state.Get32BitRegister(Generic_Register::GP_Register_A)=0;
        	delete dir;
        }
    }else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_DCLOSE){
	dir_handle *dir=proc_get_dir(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(dir){
		state.Get32BitRegister(Generic_Register::GP_Register_A)=fs_close_dir(*dir);
		proc_remove_dir(state.Get32BitRegister(Generic_Register::GP_Register_B));
		delete dir;
	}
}

USERAPI_HANDLER(BT_DWRITE){
	dir_handle *dir=proc_get_dir(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(dir){
		if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(directory_entry))){
			directory_entry *entry=(directory_entry*)state.Get32BitRegister(Generic_Register::GP_Register_C);
			fs_write_dir(*dir, *entry);
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_DREAD){
	dir_handle *dir=proc_get_dir(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(dir){
		if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(directory_entry))){
			directory_entry *entry=(directory_entry*)state.Get32BitRegister(Generic_Register::GP_Register_C);
			*entry=fs_read_dir(*dir);
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_DSEEK){
	dir_handle *dir=proc_get_dir(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(dir){
		state.Get32BitRegister(Generic_Register::GP_Register_A)=fs_seek_dir(*dir, state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D));
	}
}

USERAPI_HANDLER(BT_STAT){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(directory_entry))){
		directory_entry *entry=(directory_entry*)state.Get32BitRegister(Generic_Register::GP_Register_C);
		*entry=fs_stat((char*)state.Get32BitRegister(Generic_Register::GP_Register_B));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_FORMAT){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B)) && is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_C)) && (!state.Get32BitRegister(Generic_Register::GP_Register_D) || is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), 1))){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = fs_format((const char*)state.Get32BitRegister(Generic_Register::GP_Register_B), (const char*)state.Get32BitRegister(Generic_Register::GP_Register_C), (void*)state.Get32BitRegister(Generic_Register::GP_Register_D));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_LOAD_MODULE){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B))){
		if(has_perm(0, kperm::LoadModule)){
			char *params=is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_C))?(char*)state.Get32BitRegister(Generic_Register::GP_Register_C):NULL;
			load_module((char*)state.Get32BitRegister(Generic_Register::GP_Register_B), params);
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_GETENV){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B)) && (state.Get32BitRegister(Generic_Register::GP_Register_D) == 0 || is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D)))){
		string value=proc_getenv((char*)state.Get32BitRegister(Generic_Register::GP_Register_B), true);
		if(value != ""){
			if(state.Get32BitRegister(Generic_Register::GP_Register_D)) strncpy((char*)state.Get32BitRegister(Generic_Register::GP_Register_C), value.c_str(), state.Get32BitRegister(Generic_Register::GP_Register_D));
			state.Get32BitRegister(Generic_Register::GP_Register_A)=value.length() + 1;
		}else state.Get32BitRegister(Generic_Register::GP_Register_A)=0;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_SETENV){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B)) && is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_C))){
		proc_setenv((char*)state.Get32BitRegister(Generic_Register::GP_Register_B), (char*)state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D), true);
		state.Get32BitRegister(Generic_Register::GP_Register_A)=true;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_SPAWN){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B)) &&  (!state.Get32BitRegister(Generic_Register::GP_Register_C) || is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), sizeof(char*) * state.Get32BitRegister(Generic_Register::GP_Register_C)))){
		if(state.Get32BitRegister(Generic_Register::GP_Register_C)){
			size_t argc=state.Get32BitRegister(Generic_Register::GP_Register_C);
			char **argv=(char**)state.Get32BitRegister(Generic_Register::GP_Register_D);
			for(size_t i=0; i<argc; ++i){
				if(!is_safe_string((uint32_t)argv[i])){
					RAISE_US_ERROR();
					return;
				}
			}
		}
		dbgpf("UAPI:Spawning %s\n", (char*)state.Get32BitRegister(Generic_Register::GP_Register_B));
		state.Get32BitRegister(Generic_Register::GP_Register_A)=proc_spawn((char*)state.Get32BitRegister(Generic_Register::GP_Register_B), state.Get32BitRegister(Generic_Register::GP_Register_C), (char**)state.Get32BitRegister(Generic_Register::GP_Register_D));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_WAIT){
	state.Get32BitRegister(Generic_Register::GP_Register_A)=proc_wait(state.Get32BitRegister(Generic_Register::GP_Register_B));
}

USERAPI_HANDLER(BT_KILL){
	if(!has_perm(0, kperm::KillAll) && proc_get_uid(state.Get32BitRegister(Generic_Register::GP_Register_B)) != proc_get_uid()) return;
	proc_end(state.Get32BitRegister(Generic_Register::GP_Register_B));
}

USERAPI_HANDLER(BT_PRIORITIZE){
	//TODO: Implement...
}

USERAPI_HANDLER(BT_EXIT){
	pid_t pid=CurrentProcess().ID();
	proc_setreturn(state.Get32BitRegister(Generic_Register::GP_Register_B));
	debug_event_notify(CurrentProcess().ID(), sch_get_id(), bt_debug_event::ThreadEnd);
	//proc_switch(0);
	proc_end(pid);
	sch_end_thread();
}

USERAPI_HANDLER(BT_GETPID){
	state.Get32BitRegister(Generic_Register::GP_Register_A)=(uint32_t)CurrentProcess().ID();
}

USERAPI_HANDLER(BT_PROCSTATUS){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(bt_pid_t))){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = proc_get_status(*(bt_pid_t*)state.Get32BitRegister(Generic_Register::GP_Register_B));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_NEW_THREAD){
    if(proc_get_status()==btos_api::bt_proc_status::Ending){
        state.Get32BitRegister(Generic_Register::GP_Register_A)=0;
        return;
    }
    if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(proc_entry)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), 0) && (!state.Get32BitRegister(Generic_Register::GP_Register_C) || is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), 0))){
        uint64_t id=proc_new_user_thread((proc_entry)state.Get32BitRegister(Generic_Register::GP_Register_B), (void*)state.Get32BitRegister(Generic_Register::GP_Register_C), (void*)state.Get32BitRegister(Generic_Register::GP_Register_D));
        state.Get32BitRegister(Generic_Register::GP_Register_A)=proc_get_thread_handle(id);
    }else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_BLOCK_THREAD){
    sch_abortable(true);
    sch_block();
    sch_abortable(false);
}

USERAPI_HANDLER(BT_UNBLOCK_THREAD){
    uint64_t id=proc_get_thread(state.Get32BitRegister(Generic_Register::GP_Register_B));
    sch_unblock(id);
}

USERAPI_HANDLER(BT_GET_THREAD){
    state.Get32BitRegister(Generic_Register::GP_Register_A)=proc_get_thread_handle(sch_get_id());
}

USERAPI_HANDLER(BT_WAIT_THREAD){
    uint64_t id=proc_get_thread(state.Get32BitRegister(Generic_Register::GP_Register_B));
    if(id){
        sch_wait(id);
    }
}

USERAPI_HANDLER(BT_END_THREAD){
	debug_event_notify(CurrentProcess().ID(), sch_get_id(), bt_debug_event::ThreadEnd);
    sch_end_thread();
}

USERAPI_HANDLER(BT_YIELD){
    sch_yield();
}

USERAPI_HANDLER(BT_THREAD_ABORT){
    uint64_t id=proc_get_thread(state.Get32BitRegister(Generic_Register::GP_Register_B));
    if(id){
        proc_remove_thread(id);
        sch_abort(id);
    }
}

USERAPI_HANDLER(BT_SEND){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_header)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(uint64_t))){
		btos_api::bt_msg_header header=*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		if(header.length && !is_safe_ptr((uint32_t)header.content, header.length)) return;
		uint64_t &ret=*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_C);
		header.flags=header.flags | btos_api::bt_msg_flags::UserSpace;
		header.from=CurrentProcess().ID();
		header.critical=false;
		if(header.length > btos_api::BT_MSG_MAX) return;
		ret=proc_send_message(header);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_RECV){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_header))){
		btos_api::bt_msg_header &header=*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		if(state.Get32BitRegister(Generic_Register::GP_Register_C)){
			header=msg_recv_block();
			header.content=NULL;
		}else{
			state.Get32BitRegister(Generic_Register::GP_Register_A)=(uint32_t)msg_recv(header);
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_NEXTMSG){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_header))){
		btos_api::bt_msg_header &header=*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		msg_nextmessage(header);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_CONTENT){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_header)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D))){
		state.Get32BitRegister(Generic_Register::GP_Register_A)=msg_getcontent(*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_B), (void*)state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_ACK){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_header))){
		msg_acknowledge(*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_B));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MSGWAIT){
	proc_message_wait();
}

USERAPI_HANDLER(BT_SUBSCRIBE){
	msg_subscribe((btos_api::bt_kernel_messages::Enum)state.Get32BitRegister(Generic_Register::GP_Register_B));
}

USERAPI_HANDLER(BT_UNSUBSCRIBE){
	msg_unsubscribe((btos_api::bt_kernel_messages::Enum)state.Get32BitRegister(Generic_Register::GP_Register_B));
}

USERAPI_HANDLER(BT_RECVFILTERED){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_filter)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(btos_api::bt_msg_header))){
		(*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_C)) = msg_recv_filtered(*(btos_api::bt_msg_filter*)state.Get32BitRegister(Generic_Register::GP_Register_B), CurrentProcess().ID(), (bool)state.Get32BitRegister(Generic_Register::GP_Register_D));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_NEXTMSGFILTERED){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_filter)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(btos_api::bt_msg_header))){
		btos_api::bt_msg_header &header=*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_C);
		msg_nextmessage_filtered(*(btos_api::bt_msg_filter*)state.Get32BitRegister(Generic_Register::GP_Register_B), header);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MSGQUERY){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = msg_query_recieved(*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MAKE_MSG_WAIT){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_filter))){
		bt_handle_info h = msg_create_recv_handle(*(btos_api::bt_msg_filter*)state.Get32BitRegister(Generic_Register::GP_Register_B));
		state.Get32BitRegister(Generic_Register::GP_Register_A) = proc_add_handle(h);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_READ_MSG_WAIT){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(btos_api::bt_msg_header))){
		bt_handle_info h = proc_get_handle(state.Get32BitRegister(Generic_Register::GP_Register_B));
		*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_C) = msg_read_recv_handle(h);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_QUERY_EXT){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B))){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = get_extension_id((char*)state.Get32BitRegister(Generic_Register::GP_Register_B));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MULTI_CALL){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), state.Get32BitRegister(Generic_Register::GP_Register_C) * sizeof(btos_api::bt_syscall_item))){
		//dbgpf("UAPI: BT_MULTI_CALL: %i calls.\n", (int)state.Get32BitRegister(Generic_Register::GP_Register_C));
		btos_api::bt_syscall_item *items = (btos_api::bt_syscall_item*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		ICPUState *fake_state = GetHAL().GetDefaultCPUState().Clone();
		for(size_t i = 0; i < state.Get32BitRegister(Generic_Register::GP_Register_C); ++i){
			//dbgpf("UAPI: BT_MULTI_CALL %i - %x\n", (int)i, items[i].call_id);
			fake_state->Get32BitRegister(Generic_Register::GP_Register_A) = items[i].call_id;
			fake_state->Get32BitRegister(Generic_Register::GP_Register_B) = items[i].p1;
			fake_state->Get32BitRegister(Generic_Register::GP_Register_C) = items[i].p2;
			fake_state->Get32BitRegister(Generic_Register::GP_Register_D) = items[i].p3;
			userapi_handler(*fake_state);
			items[i].call_id = fake_state->Get32BitRegister(Generic_Register::GP_Register_A);
		}
		delete fake_state;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_CLOSEHANDLE){
    bt_handle_info h=proc_get_handle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
    if(h.open && h.type!=kernel_handle_types::invalid){
        close_handle(h);
        proc_remove_handle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
    }
}

USERAPI_HANDLER(BT_QUERYHANDLE){
	bt_handle_info h=proc_get_handle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(h.open && h.type!=kernel_handle_types::invalid){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = 1;
	}else{
		state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
	}
}

USERAPI_HANDLER(BT_WAITHANDLE){
	bt_handle_info h = proc_get_handle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(h.open && h.type != kernel_handle_types::invalid){
		wait_handle(h);
	}
}

USERAPI_HANDLER(BT_MAKE_WAITALL){
	size_t size = state.Get32BitRegister(Generic_Register::GP_Register_C);
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), size * sizeof(bt_handle_t))){
		bt_handle_t *sarr = (bt_handle_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		auto harr = new bt_handle_info[size];
		for(size_t i = 0; i < size; ++i){
			harr[i] = proc_get_handle(sarr[i]);
			if(!harr[i].open || harr[i].type == kernel_handle_types::invalid){
				delete[] harr;
				return;
			}
		}
		auto hdl = create_wait_all_handle(harr, size);
		state.Get32BitRegister(Generic_Register::GP_Register_A) = proc_add_handle(hdl);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MAKE_WAITANY){
	size_t size = state.Get32BitRegister(Generic_Register::GP_Register_C);
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), size * sizeof(bt_handle_t))){
		bt_handle_t *sarr = (bt_handle_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		auto harr = new bt_handle_info[size];
		for(size_t i = 0; i < size; ++i){
			harr[i] = proc_get_handle(sarr[i]);
			if(!harr[i].open || harr[i].type == kernel_handle_types::invalid){
				delete[] harr;
				return;
			}
		}
		auto hdl = create_wait_any_handle(harr, size);
		state.Get32BitRegister(Generic_Register::GP_Register_A) = proc_add_handle(hdl);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_WAIT_INDEX){
	bt_handle_info h = proc_get_handle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(h.open && h.type == kernel_handle_types::wait){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = get_wait_index(h);
	}
}

USERAPI_HANDLER(BT_SET_UID){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
		uint64_t nuid = *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		state.Get32BitRegister(Generic_Register::GP_Register_A) = switch_uid(nuid);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_GET_UID){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
		uint64_t *uid = (uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		*uid = proc_get_uid();
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_GETSET_PERMS){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(uint64_t))){
		uint16_t ext = (uint16_t)state.Get32BitRegister(Generic_Register::GP_Register_B);
		uint64_t *perms = (uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_C);
		dbgpf("UAPI: BT_GETSET_PERMS %u, %llu\n", ext, *perms);
		*perms = set_perms(ext, *perms);
	}else RAISE_US_ERROR();
}

void userapi_syscall(uint16_t fn, ICPUState &state){
	switch(fn){
		case 0:
         	zero_call(state);
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
		USERAPI_HANDLE_CALL(BT_MAKE_MSG_WAIT);
		USERAPI_HANDLE_CALL(BT_READ_MSG_WAIT);

		//Handles
        USERAPI_HANDLE_CALL(BT_CLOSEHANDLE);
		USERAPI_HANDLE_CALL(BT_QUERYHANDLE);
		USERAPI_HANDLE_CALL(BT_WAITHANDLE);
		USERAPI_HANDLE_CALL(BT_MAKE_WAITALL);
		USERAPI_HANDLE_CALL(BT_MAKE_WAITANY);
		USERAPI_HANDLE_CALL(BT_WAIT_INDEX);

		//Security
		USERAPI_HANDLE_CALL(BT_SET_UID);
		USERAPI_HANDLE_CALL(BT_GET_UID);
		USERAPI_HANDLE_CALL(BT_GETSET_PERMS);

		//Extensions
		USERAPI_HANDLE_CALL(BT_QUERY_EXT);
		
		//Magic
		USERAPI_HANDLE_CALL(BT_MULTI_CALL);

		default:
			state.Get32BitRegister(Generic_Register::GP_Register_A)=-1;
			break;
	}
}

