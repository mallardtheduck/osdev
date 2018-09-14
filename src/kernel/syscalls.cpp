#include "syscalls.hpp"
#include "locks.hpp"

module_api::thread_id_t thread_id(){
	return sch_get_id();
}

void mod_memcpy(void *dst, const void *src, size_t size){
	memcpy(dst, src, size);
}

void mod_memmove(void *dst, void *src, size_t size){
	memmove(dst, src, size);
}

int mod_strcmp(char *s1, char *s2){
	return strcmp(s1, s2);
}

void mod_strncpy(char *dst, char *src, size_t size){
	strncpy(dst, src, size);
}

void mod_init_lock(lock *l){
	init_lock(*l);
}

void mod_take_lock(lock *l){
    take_lock_exclusive(*l);
}

void mod_take_lock_recursive(lock *l){
    take_lock_recursive(*l);
}

bool mod_try_take_lock(lock *l){
	return try_take_lock_exclusive(*l);
}

void mod_release_lock(lock *l){
	return release_lock(*l);
}

uint64_t new_thread(module_api::thread_func e, void *p){
	return sch_new_thread(e, p);
}

void add_filesystem(fs_driver *fs){
	fs_registerfs(*fs);
}

file_handle *fopen(const char *path, fs_mode_flags mode){
	return new file_handle(fs_open((char*)path, mode));
}

bool fclose(file_handle *h){
	if(fs_close(*h)){
		delete h;
		return true;
	}else return false;
}

size_t fread(file_handle *h, size_t bytes, char *buf){
	return fs_read(*h, bytes, buf);
}

size_t fwrite(file_handle *h, size_t bytes, char *buf){
	return fs_write(*h, bytes, buf);
}

bt_filesize_t fseek(file_handle *handle, bt_filesize_t pos, uint32_t flags){
	return fs_seek(*handle, pos, flags);
}

bool fsetsize(file_handle *handle, bt_filesize_t size){
	return fs_setsize(*handle, size);
}

int fioctl(file_handle *handle, int fn, size_t bytes, char *buf){
	return fs_ioctl(*handle, fn, bytes, buf);
}

void fflush(file_handle *handle){
    fs_flush(*handle);
}

dir_handle *diropen(const char *path, fs_mode_flags mode){
	return new dir_handle(fs_open_dir((char*)path, mode));
}

bool dirclose(dir_handle *handle){
	if(fs_close_dir(*handle)){
		delete handle;
		return true;
	}else return false;
}

directory_entry dirread(dir_handle *handle){
	return fs_read_dir(*handle);
}

bool dirwrite(dir_handle *handle, directory_entry entry){
	return fs_write_dir(*handle, entry);
}

bool dirseek(dir_handle *handle, size_t pos, uint32_t flags){
	return fs_seek_dir(*handle, pos, flags);
}

void setenv(const char *name, char *value, uint8_t flags, pid_t pid){
	proc_setenv(name, value, flags, pid);
}

char *getenv(const char *name, pid_t pid){
	const string &ret=proc_getenv(name, pid);
	if(ret=="") return NULL;
	else return (char*)ret.c_str();
}

pid_t getpid(){
	return proc_current_pid;
}

pid_t mod_spawn(const char *exec, size_t argc, char **argv){
	return proc_spawn(exec, argc, argv);
}

void mod_wait(pid_t pid){
	proc_wait(pid);
}

void mod_kill(pid_t pid){
    proc_terminate(pid);
}

void mask_irq(size_t irqno){
	IRQ_set_mask(irqno);
}

void unmask_irq(size_t irqno){
	IRQ_clear_mask(irqno);
}

bool setpid(pid_t pid){
	if(proc_get_status(pid) != proc_status::DoesNotExist){
		proc_switch(pid);
		if(proc_current_pid != pid) return false;
		return true;
	}else{
		return false;
	}
}

uint64_t mod_msg_send(btos_api::bt_msg_header *msg){
	return msg_send(*msg);
}

size_t mod_msg_getcontent(btos_api::bt_msg_header *msg, void *buffer, size_t buffersize){
	return msg_getcontent(*msg, buffer, buffersize);
}

void mod_msg_acknowledge(btos_api::bt_msg_header *msg, bool set_status){
	msg_acknowledge(*msg, set_status);
}

bool mod_msg_recv_reply(btos_api::bt_msg_header *msg, uint64_t msg_id){
	return msg_recv_reply(*msg, msg_id);
}

void mod_abortable(bool abortable){
	sch_abortable(abortable);
}

uint32_t physical_addr(void *addr){
	return MM2::current_pagedir->virt2phys(addr);
}

void mod_set_kvar(const char *name, const char *value){
	set_kvar(name, value);
}

size_t mod_get_kvar(const char *name, char *buffer, size_t size){
	string value = get_kvar(name);
	strncpy(buffer, value.c_str(), size);
	return value.length();
}

void *mod_map_physical(uint32_t addr, size_t pages){
	return MM2::mm2_map_physical(addr, pages);
}

void mod_free_pages(void *addr, size_t pages){
	mm2_virtual_free(addr, pages);
}

void mod_lock_low_memory(){
	MM2::lock_low_memory();
}

void mod_unlock_low_memory(){
	MM2::unlock_low_memory();	
}

module_api::syscall_table MODULE_SYSCALL_TABLE={
	&panic,
	&malloc,
	&free,
	&memset,
	&mod_memcpy,
	&mod_memmove,
	&mod_strcmp,
	&mod_strncpy,
    &physical_addr,
    &mod_map_physical,
    &mod_free_pages,
    &mod_lock_low_memory,
    &mod_unlock_low_memory,

	&mod_init_lock,
	&mod_take_lock,
    &mod_take_lock_recursive,
	&mod_try_take_lock,
	&mod_release_lock,

	&dbgout,
	&sprintf,

	&new_thread,
	&sch_block,
	&sch_yield,
	&sch_yield_to,
	&thread_id,
	&sch_set_priority,
	&sch_end_thread,
	&sch_unblock,
	&sch_wait,
	&sch_setblock,
	&mod_abortable,
	&sch_abort,

	&drv_add_device,
	&drv_get,
	&drv_firstdevice,
	&drv_nextdevice,
	&drv_open,
	&drv_close,
	&drv_read,
	&drv_write,
	&drv_seek,
	&drv_ioctl,
	&drv_get_type,
	&drv_get_desc,
	&int_handle,
	&irq_handle,
	&mask_irq,
	&unmask_irq,
	&irq_ack,
	&int_handle_raw,
	&irq_handle_raw,

	&add_filesystem,
	&fs_mount,
	&fs_unmount,

	&fopen,
	&fclose,
	&fread,
	&fwrite,
	&fseek,
	&fsetsize,
	&fioctl,
    &fflush,

	diropen,
	dirclose,
	dirread,
	dirwrite,
	dirseek,
	&fs_stat,

	&load_module,

	&setenv,
	&getenv,

	&getpid,
    &setpid,
	&mod_spawn,
	&mod_wait,
    &mod_kill,

	&infofs_register,
    &add_extension,
    &get_extension,
    &get_extension_id,
	
	&mod_msg_send,
	&mod_msg_getcontent,
	&mod_msg_acknowledge,
	&mod_msg_recv_reply,
	&msg_recv_reply_block,
	&msg_query_recieved,
	
	&proc_add_handle,
	&proc_get_handle,
	
	&mod_set_kvar,
	&mod_get_kvar,
};
