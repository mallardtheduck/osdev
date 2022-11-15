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
	auto &currentThread = CurrentThread();
	auto &currentProcess = CurrentProcess();
	if(currentProcess.ID() == 0) panic("(UAPI) Userspace PID 0!");
	if(currentProcess.GetStatus() == btos_api::bt_proc_status::Ending) currentThread.Abort();
	uint16_t *id=(uint16_t*)(&state.Get32BitRegister(Generic_Register::GP_Register_A));
	uint16_t ext=id[1], fn=id[0];
	//dbgpf("UAPI: Extension: %x, Function: %x\n", (int)ext, (int)fn);
	if(ext==0){
		userapi_syscall(fn, state);
	}else{
		GetKernelExtensionManager().ExtensionUserCall(ext, fn, state);
	}
	if(currentThread.GetLockCount() != 1){
		dbgpf("UAPI: Lock count: %i, ext: %i fn: %x\n", currentThread.GetLockCount(), (int)ext, (int)fn);
		panic("(UAPI) Non-zero lock count on return to userspace!\n");
	}
	if(currentProcess.GetStatus() == btos_api::bt_proc_status::Ending) currentThread.Abort();
}

bool is_safe_ptr(uint32_t ptr, size_t size, bt_pid_t pid){
	if(ptr >= MM2::MM2_Kernel_Boundary){
		bt_pid_t cur_pid = CurrentProcess().ID();
		GetProcessManager().SwitchProcess(pid);
		size_t i = 0;
		while(i<size){
			size_t res = MM2::current_pagedir->resolve_addr((char*)ptr + i);
			i += res;
			if(!res){ 
				GetProcessManager().SwitchProcess(cur_pid);
				dbgpf("UAPI: Verification of pointer %lx (%i) for %i failed.\n", ptr, (int)size, (int)pid);
				return false;
			}
		}
		GetProcessManager().SwitchProcess(cur_pid);
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
	debug_event_notify(CurrentProcess().ID(), CurrentThread().ID(), bt_debug_event::Exception, bt_exception::InvalidArg);
	CurrentProcess().Terminate();
}

[[maybe_unused]]
static void uapi_raise_security_error(const char *fn){
	dbgpf("UAPI: PID %llu error in call: %s\n", CurrentProcess().ID(), fn);
	debug_event_notify(CurrentProcess().ID(), CurrentThread().ID(), bt_debug_event::Exception, bt_exception::SecurityException);
	CurrentProcess().Terminate();
}

USERAPI_HANDLER(zero){
	static bool nl = true;
	if(nl) dbgpf("USER (%llu|%llu): ", CurrentProcess().ID(), CurrentThread().ID());
	string outputstr = (char*)state.Get32BitRegister(Generic_Register::GP_Register_B);
	dbgout(outputstr.c_str());
	nl = outputstr[outputstr.length() - 1] == '\n';
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

static void close_shm_space_handle(uint64_t id){
	GetMemoryManager().DestroySharedMemorySpace(id);
}

USERAPI_HANDLER(BT_CREATE_SHM){
	uint64_t id = GetMemoryManager().CreateSharedMemorySpace(state.Get32BitRegister(Generic_Register::GP_Register_B));
	auto handle = MakeKernelGenericHandle<KernelHandles::SHMSpace>(id, &close_shm_space_handle);
	state.Get32BitRegister(Generic_Register::GP_Register_A) = CurrentProcess().AddHandle(handle);
}

USERAPI_HANDLER(BT_SHM_ID){
	auto h = CurrentProcess().GetHandle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(uint64_t*))){
		if(auto handle = KernelHandleCast<KernelHandles::SHMSpace>(h)){
			*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_C) = handle->GetData();
		}
	}else RAISE_US_ERROR();
}

static void close_shm_map_handle(uint64_t id){
	GetMemoryManager().UnMapSharedMemory(id);
}

USERAPI_HANDLER(BT_SHM_MAP){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_shm_mapping*))){
		btos_api::bt_shm_mapping *mapping = (btos_api::bt_shm_mapping*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		if(is_safe_ptr((uint32_t)mapping->addr, mapping->pages * MM2::MM2_Page_Size)){
			uint64_t id = GetMemoryManager().MapSharedMemory(mapping->id, mapping->addr, mapping->offset, mapping->pages, mapping->flags);
			auto handle = MakeKernelGenericHandle<KernelHandles::SHMMapping>(id, &close_shm_map_handle);
			state.Get32BitRegister(Generic_Register::GP_Register_A) = CurrentProcess().AddHandle(handle);
		}else RAISE_US_ERROR();
	}else RAISE_US_ERROR();	
}

USERAPI_HANDLER(BT_GET_ARGC){
	state.Get32BitRegister(Generic_Register::GP_Register_A)=CurrentProcess().GetArgumentCount();
}

USERAPI_HANDLER(BT_GET_ARG){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D))){
		state.Get32BitRegister(Generic_Register::GP_Register_A)=CurrentProcess().GetArgument(
			state.Get32BitRegister(Generic_Register::GP_Register_B), 
			(char*)state.Get32BitRegister(Generic_Register::GP_Register_C), 
			state.Get32BitRegister(Generic_Register::GP_Register_D));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_CREATE_LOCK){
	auto lock = NewLock();
	auto handle = MakeKernelGenericHandle<KernelHandles::Lock>(lock, 
		[](ILock *l){
			delete l;
		},
		[](ILock *l){
			l->TakeExclusive(true);
			return true;
		}
	);
	state.Get32BitRegister(Generic_Register::GP_Register_A)=CurrentProcess().AddHandle(handle);
}

USERAPI_HANDLER(BT_LOCK){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::Lock>(h)) {
		auto lock = handle->GetData();
		lock->TakeExclusive(true);
		CurrentThread().DecrementLockCount();
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_TRY_LOCK){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::Lock>(h)){
		auto lock = handle->GetData();
		if(lock->TryTakeExclusive()){
			state.Get32BitRegister(Generic_Register::GP_Register_A) = 1;
			CurrentThread().DecrementLockCount();
			return;
		}
	}
	state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
}

USERAPI_HANDLER(BT_UNLOCK){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::Lock>(h)){
		auto lock = handle->GetData();
		CurrentThread().IncrementLockCount();
		lock->Release(true);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_DESTROY_LOCK){
	CurrentProcess().CloseAndRemoveHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
}

USERAPI_HANDLER(BT_CREATE_ATOM){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
		auto atom = NewAtom(*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B));
		auto handle = MakeKernelGenericHandle<KernelHandles::Atom>(atom,
			[](IAtom *a){
				delete a;
			}
		);
		state.Get32BitRegister(Generic_Register::GP_Register_A) = CurrentProcess().AddHandle(handle);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MODIFY_ATOM){
	auto h = CurrentProcess().GetHandle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), sizeof(uint64_t))){
		if(auto handle = KernelHandleCast<KernelHandles::Atom>(h)){
			*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_D) = handle->GetData()->Modify(
				(bt_atom_modify::Enum)state.Get32BitRegister(Generic_Register::GP_Register_C), 
				*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_D));
			state.Get32BitRegister(Generic_Register::GP_Register_A) = 1;
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MAKE_WAIT_ATOM){
	auto h = CurrentProcess().GetHandle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), sizeof(uint64_t))){
		if(auto handle = KernelHandleCast<KernelHandles::Atom>(h)){
			auto wait = handle->GetData()->MakeWaitHandle((bt_atom_compare::Enum)state.Get32BitRegister(Generic_Register::GP_Register_C), *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_D));
			state.Get32BitRegister(Generic_Register::GP_Register_A) = CurrentProcess().AddHandle(wait);
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_CMPXCHG_ATOM){
	auto h = CurrentProcess().GetHandle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(uint64_t)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), sizeof(uint64_t))){
		if(auto handle = KernelHandleCast<KernelHandles::Atom>(h)){
			*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_D) = handle->GetData()->CompareExchange(*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_C), *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_D));
			state.Get32BitRegister(Generic_Register::GP_Register_A) = 1;
		}else{
			state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_READ_ATOM){
	auto h = CurrentProcess().GetHandle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(uint64_t))){
		if(auto handle = KernelHandleCast<KernelHandles::Atom>(h)) *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_C) = handle->GetData()->Read();
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MOUNT){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B)) && is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_C)) && is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_D))){
		if(GetPermissionManager().HasPermission(0, kperm::MountFS)){
			auto fsName = (char*)state.Get32BitRegister(Generic_Register::GP_Register_D);
			auto devicePath = (char*)state.Get32BitRegister(Generic_Register::GP_Register_C);
			auto mountPoint = (char*)state.Get32BitRegister(Generic_Register::GP_Register_B);
			auto fs = GetFilesystemManager().GetByName(fsName);
			auto node = (devicePath && strlen(devicePath)) ? GetVirtualFilesystem().GetNode(devicePath) : nullptr;
			if(fs && strlen(mountPoint)){
				auto mountedFs = fs->Mount(node);
				if(mountedFs) state.Get32BitRegister(Generic_Register::GP_Register_A) = GetVirtualFilesystem().Attach(mountPoint, mountedFs);
				return;
			}
		}
		state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_UNMOUNT){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B))){
		if(GetPermissionManager().HasPermission(0, kperm::UnMountFS)){
			auto mountPoint = (char*)state.Get32BitRegister(Generic_Register::GP_Register_B);
			if(strlen(mountPoint)){
				auto mountedFs = GetVirtualFilesystem().Detach(mountPoint);
				if(mountedFs){
					state.Get32BitRegister(Generic_Register::GP_Register_A) = mountedFs->Unmount();
					return;
				}
			}
		}
		else state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_FOPEN){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B))){
		auto &fs = GetVirtualFilesystem();
		auto path = (char*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		auto flags = (fs_mode_flags)state.Get32BitRegister(Generic_Register::GP_Register_C);
		auto node = fs.GetNode(path);
		IFileHandle *handle = nullptr;
		if(node){
			handle = node->OpenFile(flags);
		}else if((flags & fs_mode_flags::FS_Create)){
			auto pathObject = to_unique(fs.MakePath(path));
			if(pathObject){
				auto parentPath = to_unique(pathObject->GetParentPath());
				auto fileName = pathObject->GetLeaf();
				if(parentPath){
					auto parentNode = parentPath->GetNode();
					if(parentNode){
						handle = parentNode->CreateFile(fileName, flags);
					}
				}
			}
		}
		if(handle){
			state.Get32BitRegister(Generic_Register::GP_Register_A) = CurrentProcess().AddHandle(handle);
			return;
		}
		state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_FCLOSE){
	CurrentProcess().CloseAndRemoveHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
}

USERAPI_HANDLER(BT_FWRITE){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::File>(h)){
		if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), state.Get32BitRegister(Generic_Register::GP_Register_C))){
			state.Get32BitRegister(Generic_Register::GP_Register_A) = handle->Write(state.Get32BitRegister(Generic_Register::GP_Register_C), (char*)state.Get32BitRegister(Generic_Register::GP_Register_D));
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_FREAD){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::File>(h)){
		if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), state.Get32BitRegister(Generic_Register::GP_Register_C))){
			state.Get32BitRegister(Generic_Register::GP_Register_A) = handle->Read(state.Get32BitRegister(Generic_Register::GP_Register_C), (char*)state.Get32BitRegister(Generic_Register::GP_Register_D));
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_FIOCTL){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::File>(h)){
		if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), sizeof(btos_api::bt_fioctl_buffer))){
			btos_api::bt_fioctl_buffer *buf=(btos_api::bt_fioctl_buffer*)state.Get32BitRegister(Generic_Register::GP_Register_D);
			if(buf->size==0 || is_safe_ptr((uint32_t)buf->buffer, buf->size)){
				state.Get32BitRegister(Generic_Register::GP_Register_A) = handle->IOCtl(state.Get32BitRegister(Generic_Register::GP_Register_C), buf->size, buf->buffer);
			}else RAISE_US_ERROR();
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_FSEEK){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::File>(h)){
		if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(bt_filesize_t))){
			bt_filesize_t *pos = (bt_filesize_t*)state.Get32BitRegister(Generic_Register::GP_Register_C);
			*pos = handle->Seek(*pos, state.Get32BitRegister(Generic_Register::GP_Register_D));
			state.Get32BitRegister(Generic_Register::GP_Register_A) = 0; 
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_FSETSIZE){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::File>(h)){
		if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(bt_filesize_t))){
			bt_filesize_t *size = (bt_filesize_t*)state.Get32BitRegister(Generic_Register::GP_Register_C);
			state.Get32BitRegister(Generic_Register::GP_Register_A) = handle->Resize(*size);
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_FFLUSH){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::File>(h)) handle->Flush();
}

static void close_filemap_handle(uint64_t f){
	GetMemoryManager().UnMapFile(f);
}

USERAPI_HANDLER(BT_MMAP){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::File>(h)){
		if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), sizeof(btos_api::bt_mmap_buffer))){
			btos_api::bt_mmap_buffer *buffer=(btos_api::bt_mmap_buffer*)state.Get32BitRegister(Generic_Register::GP_Register_D);
			if(!is_safe_ptr((uint32_t)buffer->buffer, buffer->size)) return;

			auto id = GetMemoryManager().MemoryMapFile(buffer->buffer, handle, state.Get32BitRegister(Generic_Register::GP_Register_C), buffer->size);
			auto newHandle = MakeKernelGenericHandle<KernelHandles::MemoryMapping>(id, &close_filemap_handle);
			state.Get32BitRegister(Generic_Register::GP_Register_A) = CurrentProcess().AddHandle(newHandle);
			return;
		}else RAISE_US_ERROR();
		state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
	}
}

USERAPI_HANDLER(BT_DOPEN){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B))){
		auto &fs = GetVirtualFilesystem();
		auto path = (char*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		auto flags = (fs_mode_flags)state.Get32BitRegister(Generic_Register::GP_Register_C);
		auto node = GetVirtualFilesystem().GetNode(path);
		IDirectoryHandle *handle = nullptr;
		if(node){
			handle = node->OpenDirectory(flags);
		}else if((flags & fs_mode_flags::FS_Create)){
			auto pathObject = to_unique(fs.MakePath(path));
			if(pathObject){
				auto parentPath = to_unique(pathObject->GetParentPath());
				auto dirName = pathObject->GetLeaf();
				if(parentPath){
					auto parentNode = parentPath->GetNode();
					if(parentNode){
						handle = parentNode->CreateDirectory(dirName, flags);
					}
				}
			}
		}
		if(handle){
			state.Get32BitRegister(Generic_Register::GP_Register_A) = CurrentProcess().AddHandle(handle);
		}else{
			state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_DCLOSE){
	CurrentProcess().CloseAndRemoveHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
}

USERAPI_HANDLER(BT_DWRITE){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::Directory>(h)){
		if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(directory_entry))){
			directory_entry *entry=(directory_entry*)state.Get32BitRegister(Generic_Register::GP_Register_C);
			//TODO: Currently, DWRITE can only be used to rename files. Is that enough?
			auto node = handle->Read();
			if(node) node->Rename(entry->filename);
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_DREAD){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::Directory>(h)){
		if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(directory_entry))){
			directory_entry *entry=(directory_entry*)state.Get32BitRegister(Generic_Register::GP_Register_C);
			auto node = handle->Read();
			if(node){
				strncpy(entry->filename, node->GetName(), BT_MAX_SEGLEN - 1);
				entry->id = (uint64_t)node.get();
				entry->size = node->GetSize();
				entry->type = node->GetType();
				entry->valid = true;
			}else{
				entry->valid = false;
			}
		}else RAISE_US_ERROR();
	}
}

USERAPI_HANDLER(BT_DSEEK){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::Directory>(h)){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = handle->Seek(state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D));
	}
}

USERAPI_HANDLER(BT_STAT){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(directory_entry))){
		directory_entry *entry=(directory_entry*)state.Get32BitRegister(Generic_Register::GP_Register_C);
		auto node = GetVirtualFilesystem().GetNode((char*)state.Get32BitRegister(Generic_Register::GP_Register_B));
		if(node){
			strncpy(entry->filename, node->GetName(), BT_MAX_SEGLEN - 1);
			entry->id = (uint64_t)node.get();
			entry->size = node->GetSize();
			entry->type = node->GetType();
			entry->valid = true;
		}else{
			entry->valid = false;
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_FORMAT){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B)) && is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_C)) && (!state.Get32BitRegister(Generic_Register::GP_Register_D) || is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), 1))){
		auto fsName = (const char*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		auto devicePath = (const char*)state.Get32BitRegister(Generic_Register::GP_Register_C);
		auto options = (void*)state.Get32BitRegister(Generic_Register::GP_Register_D);
		auto fs = GetFilesystemManager().GetByName(fsName);
		auto node = GetVirtualFilesystem().GetNode(devicePath);
		if(fs && node){
			state.Get32BitRegister(Generic_Register::GP_Register_A) = fs->Format(*node, options);
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_LOAD_MODULE){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B))){
		if(GetPermissionManager().HasPermission(0, kperm::LoadModule)){
			char *params=is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_C))?(char*)state.Get32BitRegister(Generic_Register::GP_Register_C):NULL;
			GetModuleManager().LoadModule((char*)state.Get32BitRegister(Generic_Register::GP_Register_B), params);
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_GETENV){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B)) && (state.Get32BitRegister(Generic_Register::GP_Register_D) == 0 || is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D)))){
		string value = CurrentProcess().GetEnvironmentVariable((char*)state.Get32BitRegister(Generic_Register::GP_Register_B), true);
		if(value != ""){
			if(state.Get32BitRegister(Generic_Register::GP_Register_D)) strncpy((char*)state.Get32BitRegister(Generic_Register::GP_Register_C), value.c_str(), state.Get32BitRegister(Generic_Register::GP_Register_D));
			state.Get32BitRegister(Generic_Register::GP_Register_A)=value.length() + 1;
		}else state.Get32BitRegister(Generic_Register::GP_Register_A)=0;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_SETENV){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B)) && is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_C))){
		CurrentProcess().SetEnvironmentVariable((char*)state.Get32BitRegister(Generic_Register::GP_Register_B), (char*)state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D), true);
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
		dbgpf("UAPI: Spawning %s\n", (char*)state.Get32BitRegister(Generic_Register::GP_Register_B));
		auto argc = state.Get32BitRegister(Generic_Register::GP_Register_C);
		auto argv = (char**)state.Get32BitRegister(Generic_Register::GP_Register_D);
		vector<const char*> args;
		for(size_t i = 0; i < argc; ++i) args.push_back(argv[i]);
		auto proc = GetProcessManager().Spawn((char*)state.Get32BitRegister(Generic_Register::GP_Register_B), args);
		state.Get32BitRegister(Generic_Register::GP_Register_A) = proc ? proc->ID() : 0;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_WAIT){
	GetProcessManager().WaitProcess(state.Get32BitRegister(Generic_Register::GP_Register_B));
	state.Get32BitRegister(Generic_Register::GP_Register_A) = 1;
}

USERAPI_HANDLER(BT_KILL){
	auto process = GetProcessManager().GetByID(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(!GetPermissionManager().HasPermission(0, kperm::KillAll) && process && process->GetUID() != CurrentProcess().GetUID()) return;
	if(process) process->End();
}

USERAPI_HANDLER(BT_PRIORITIZE){
	//TODO: Implement...
}

USERAPI_HANDLER(BT_EXIT){
	auto &process = CurrentProcess();
	process.SetReturnValue(state.Get32BitRegister(Generic_Register::GP_Register_B));
	debug_event_notify(process.ID(), CurrentThread().ID(), bt_debug_event::ThreadEnd);
	//proc_switch(0);
	process.End();
	CurrentThread().Abort();
}

USERAPI_HANDLER(BT_GETPID){
	state.Get32BitRegister(Generic_Register::GP_Register_A)=(uint32_t)CurrentProcess().ID();
}

USERAPI_HANDLER(BT_PROCSTATUS){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(bt_pid_t))){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = GetProcessManager().GetProcessStatusByID(*(bt_pid_t*)state.Get32BitRegister(Generic_Register::GP_Register_B));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_NEW_THREAD){
	if(CurrentProcess().GetStatus() == btos_api::bt_proc_status::Ending){
		state.Get32BitRegister(Generic_Register::GP_Register_A)=0;
		return;
	}
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(ProcessEntryPoint)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_D), 0) && (!state.Get32BitRegister(Generic_Register::GP_Register_C) || is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), 0))){
		auto id = CurrentProcess().NewUserThread((ProcessEntryPoint)state.Get32BitRegister(Generic_Register::GP_Register_B), (void*)state.Get32BitRegister(Generic_Register::GP_Register_C), (void*)state.Get32BitRegister(Generic_Register::GP_Register_D));
		auto handle = MakeKernelGenericHandle<KernelHandles::Thread>(id->GetWeakReference(), [](WeakThreadRef &t){
			auto thread = t.Lock();
			if(thread) thread->Abort();
		});
		state.Get32BitRegister(Generic_Register::GP_Register_A) = CurrentProcess().AddHandle(handle);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_BLOCK_THREAD){
	CurrentThread().AbortableBlock();
}

USERAPI_HANDLER(BT_UNBLOCK_THREAD){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::Thread>(h)){
		auto thread = handle->GetData().Lock();
		if(thread) thread->Unblock();
	}
}

USERAPI_HANDLER(BT_GET_THREAD){
	auto &currentProcess = CurrentProcess();
	auto &currentThread = CurrentThread();
	auto threadHandles = currentProcess.GetHandlesByType(KernelHandles::Thread::id);
	for(auto &hId : threadHandles){
		auto h = currentProcess.GetHandle(hId);
		if(auto handle = KernelHandleCast<KernelHandles::Thread>(h)){
			if(handle->GetData() == currentThread){
				state.Get32BitRegister(Generic_Register::GP_Register_A) = hId;
				return;
			}
		}
	}
	state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
}

USERAPI_HANDLER(BT_WAIT_THREAD){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	bool found = false;
	uint64_t id = 0;
	if(auto handle = KernelHandleCast<KernelHandles::Thread>(h)){
		if(auto thread = handle->GetData().Lock()){
			found = true;
			id = handle->GetData()->ID();
		}
	}
	if(found) GetScheduler().JoinThread(id);
}

USERAPI_HANDLER(BT_END_THREAD){
	debug_event_notify(CurrentProcess().ID(), CurrentThread().ID(), bt_debug_event::ThreadEnd);
	CurrentThread().Abort();
}

USERAPI_HANDLER(BT_YIELD){
	CurrentThread().Yield();
}

USERAPI_HANDLER(BT_THREAD_ABORT){
	CurrentProcess().CloseAndRemoveHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
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
		ret = GetMessageManager().SendMessage(header);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_RECV){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_header))){
		btos_api::bt_msg_header &header=*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		if(state.Get32BitRegister(Generic_Register::GP_Register_C)){
			header = GetMessageManager().AwaitMessage();
			header.content = nullptr;
		}else{
			state.Get32BitRegister(Generic_Register::GP_Register_A) = (uint32_t)GetMessageManager().RecieveMessage(header);
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_NEXTMSG){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_header))){
		auto &header=*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		GetMessageManager().AwaitNextMessage(header);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_CONTENT){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_header)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), state.Get32BitRegister(Generic_Register::GP_Register_D))){
		auto &header = *(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		auto buffer = (void*)state.Get32BitRegister(Generic_Register::GP_Register_C);
		size_t size = state.Get32BitRegister(Generic_Register::GP_Register_D);
		auto content = GetMessageManager().MessageContent(header);
		if(!content.empty()) memcpy(buffer, &content[0], min(size, content.size()));
		state.Get32BitRegister(Generic_Register::GP_Register_A) = content.size();
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_ACK){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_header))){
		GetMessageManager().AcknowledgeMessage(*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_B));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MSGWAIT){
	auto &msg = GetMessageManager();
	msg.AwaitMessage();
}

USERAPI_HANDLER(BT_SUBSCRIBE){
	GetMessageManager().Subscribe((btos_api::bt_kernel_messages::Enum)state.Get32BitRegister(Generic_Register::GP_Register_B));
}

USERAPI_HANDLER(BT_UNSUBSCRIBE){
	GetMessageManager().UnSubscribe((btos_api::bt_kernel_messages::Enum)state.Get32BitRegister(Generic_Register::GP_Register_B));
}

USERAPI_HANDLER(BT_RECVFILTERED){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_filter)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(btos_api::bt_msg_header))){
		auto &header = (*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_C));
		auto filter = *(btos_api::bt_msg_filter*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		if(state.Get32BitRegister(Generic_Register::GP_Register_D)){
			header = GetMessageManager().AwaitMessage(filter, CurrentProcess());
		}else{
			header.valid = false;
			GetMessageManager().RecieveMessage(header, filter, CurrentProcess());
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_NEXTMSGFILTERED){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_filter)) && is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(btos_api::bt_msg_header))){
		btos_api::bt_msg_header &header=*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_C);
		GetMessageManager().AwaitNextMessage(*(btos_api::bt_msg_filter*)state.Get32BitRegister(Generic_Register::GP_Register_B), header);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MSGQUERY){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = GetMessageManager().HasMessageBeenProcessed(*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MAKE_MSG_WAIT){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(btos_api::bt_msg_filter))){
		auto h = GetMessageManager().CreateRecieveHandle(*(btos_api::bt_msg_filter*)state.Get32BitRegister(Generic_Register::GP_Register_B));
		if(h) state.Get32BitRegister(Generic_Register::GP_Register_A) = CurrentProcess().AddHandle(h);
		else state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_READ_MSG_WAIT){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(btos_api::bt_msg_header))){
		auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
		if(auto handle = KernelHandleCast<KernelHandles::MessageRecive>(h)){
			*(btos_api::bt_msg_header*)state.Get32BitRegister(Generic_Register::GP_Register_C) = handle->Read();
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_QUERY_EXT){
	if(is_safe_string(state.Get32BitRegister(Generic_Register::GP_Register_B))){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = GetKernelExtensionManager().GetExtensionID((char*)state.Get32BitRegister(Generic_Register::GP_Register_B));
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MULTI_CALL){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), state.Get32BitRegister(Generic_Register::GP_Register_C) * sizeof(btos_api::bt_syscall_item))){
		//dbgpf("UAPI: BT_MULTI_CALL: %i calls.\n", (int)state.Get32BitRegister(Generic_Register::GP_Register_C));
		btos_api::bt_syscall_item *items = (btos_api::bt_syscall_item*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		auto count = state.Get32BitRegister(Generic_Register::GP_Register_C);
		for(size_t i = 0; i < count; ++i){
			//dbgpf("UAPI: BT_MULTI_CALL %i - %lx\n", (int)i, items[i].call_id);
			state.Get32BitRegister(Generic_Register::GP_Register_A) = items[i].call_id;
			state.Get32BitRegister(Generic_Register::GP_Register_B) = items[i].p1;
			state.Get32BitRegister(Generic_Register::GP_Register_C) = items[i].p2;
			state.Get32BitRegister(Generic_Register::GP_Register_D) = items[i].p3;
			userapi_handler(state);
			items[i].call_id = state.Get32BitRegister(Generic_Register::GP_Register_A);
		}
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_CLOSEHANDLE){
	CurrentProcess().CloseAndRemoveHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
}

USERAPI_HANDLER(BT_QUERYHANDLE){
	auto h = CurrentProcess().GetHandle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(h && h->GetType() != KernelHandles::Invald::id){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = 1;
	}else{
		state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
	}
}

USERAPI_HANDLER(BT_WAITHANDLE){
	auto h = CurrentProcess().GetHandle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(h) WaitOnHandle(h);
}

USERAPI_HANDLER(BT_MAKE_WAITALL){
	size_t size = state.Get32BitRegister(Generic_Register::GP_Register_C);
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), size * sizeof(bt_handle_t))){
		bt_handle_t *sarr = (bt_handle_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		vector<IHandle*> harr;
		for(size_t i = 0; i < size; ++i){
			auto handle = CurrentProcess().GetHandle(sarr[i]);
			if(handle) harr.push_back(handle);
		}
		auto hdl = MakeWaitAllHandle(harr);
		state.Get32BitRegister(Generic_Register::GP_Register_A) = CurrentProcess().AddHandle(hdl);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_MAKE_WAITANY){
	size_t size = state.Get32BitRegister(Generic_Register::GP_Register_C);
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), size * sizeof(bt_handle_t))){
		bt_handle_t *sarr = (bt_handle_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		vector<IHandle*> harr;
		for(size_t i = 0; i < size; ++i){
			auto handle = CurrentProcess().GetHandle(sarr[i]);
			if(handle) harr.push_back(handle);
		}
		auto hdl = MakeWaitAnyHandle(harr);
		state.Get32BitRegister(Generic_Register::GP_Register_A) = CurrentProcess().AddHandle(hdl);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_WAIT_INDEX){
	auto h = CurrentProcess().GetHandle((handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = KernelHandleCast<KernelHandles::Wait>(h)){
		state.Get32BitRegister(Generic_Register::GP_Register_A) = GetWaitIndex(handle);
	}
}

USERAPI_HANDLER(BT_SET_UID){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
		uint64_t nuid = *(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		state.Get32BitRegister(Generic_Register::GP_Register_A) = GetPermissionManager().SwitchUID(nuid);
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_GET_UID){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(uint64_t))){
		uint64_t *uid = (uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B);
		*uid = CurrentProcess().GetUID();
	}else RAISE_US_ERROR();
}

USERAPI_HANDLER(BT_GETSET_PERMS){
	if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_C), sizeof(uint64_t))){
		uint16_t ext = (uint16_t)state.Get32BitRegister(Generic_Register::GP_Register_B);
		uint64_t *perms = (uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_C);
		dbgpf("UAPI: BT_GETSET_PERMS %u, %llu\n", ext, *perms);
		*perms = GetPermissionManager().SetPermissions(ext, *perms);
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

