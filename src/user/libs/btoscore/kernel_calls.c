#include <btos/btos_api.h>
#include <btos/bt_msg.h>
#include <btos/atoms.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t btos_call(uint32_t fn, uint32_t p1, uint32_t p2, uint32_t p3){
	volatile uint32_t ret=0;
	volatile uint32_t regs[4];
	regs[0] = fn; regs[1] = p1; regs[2] = p2; regs[3] = p3;
	asm volatile(
		"push %%ebx\n"
		"movl 4(%%eax), %%ebx\n"
		"movl 8(%%eax), %%ecx\n"
		"movl 12(%%eax), %%edx\n"
		"movl (%%eax), %%eax\n"
		"int $0x80\n"
		"pop %%ebx" 
		: "=a"(ret) : "a"(regs) : "ecx", "edx");
	return ret;
}

void bt_zero(const char *string){
	btos_call(0, (uint32_t)string, 0, 0);
}

void *bt_alloc_pages(size_t pages){
	return (void*)btos_call(BT_ALLOC_PAGES, pages, 0, 0);
}

void *bt_alloc_at(size_t pages, void *ptr){
	return (void*)btos_call(BT_ALLOC_AT, pages, (uint32_t)ptr, 0);
}

void bt_free_pages(void *address, size_t pages){
	btos_call(BT_FREE_PAGES, (uint32_t)address, pages, 0);
}

bt_handle_t bt_create_shm(uint32_t flags){
	return (bt_handle_t)btos_call(BT_CREATE_SHM, flags, 0, 0);
}

uint64_t bt_shm_id(bt_handle_t h){
	volatile uint64_t ret;
	btos_call(BT_SHM_ID, (uint32_t)h, (uint32_t)&ret, 0);
	return ret;
}

bt_handle_t bt_shm_map(uint64_t id, void *addr, uint32_t offset, size_t pages, uint32_t flags){
	volatile bt_shm_mapping mapping;
	mapping.id = id;
	mapping.addr = addr;
	mapping.offset = offset;
	mapping.pages = pages;
	mapping.flags = flags;
	return (bt_handle_t)btos_call(BT_SHM_MAP, (uint32_t)&mapping, 0, 0);
}

size_t bt_get_argc(){
	return btos_call(BT_GET_ARGC, 0, 0, 0);
}

size_t bt_get_arg(size_t index, char *buf, size_t size){
	return btos_call(BT_GET_ARG, index, (uint32_t)buf, size);
}

bt_lockhandle bt_create_lock(){
	return (bt_lockhandle)btos_call(BT_CREATE_LOCK, 0, 0, 0);
}

void bt_lock(bt_lockhandle lock){
	btos_call(BT_LOCK, lock, 0, 0);
}

bool bt_try_lock(bt_lockhandle lock){
	return (bool)btos_call(BT_TRY_LOCK, lock, 0, 0);
}

void bt_unlock(bt_lockhandle lock){
	btos_call(BT_UNLOCK, lock, 0, 0);
}

void bt_destroy_lock(bt_lockhandle lock){
	btos_call(BT_DESTROY_LOCK, lock, 0, 0);
}

bt_handle_t bt_create_atom(uint64_t ini_val){
	return (bt_handle_t) btos_call(BT_CREATE_ATOM, (uint32_t)&ini_val, 0, 0);
}

uint64_t bt_modify_atom(bt_handle_t a, ENUM_NAME(bt_atom_modify) mod, uint64_t val){
	btos_call(BT_MODIFY_ATOM, (uint32_t)a, (uint32_t)mod, (uint32_t)&val);
	return val;
}

bt_handle_t bt_make_wait_atom(bt_handle_t a, ENUM_NAME(bt_atom_compare) cmp, uint64_t val){
	return btos_call(BT_MAKE_WAIT_ATOM, (uint32_t)a, (uint32_t)cmp, (uint32_t)&val);
}

uint64_t bt_cmpxchg_atom(bt_handle_t a, uint64_t cmp, uint64_t xchg){
	volatile uint64_t ret = xchg;
	btos_call(BT_CMPXCHG_ATOM, (uint32_t)a, (uint32_t)&cmp, (uint32_t)&ret);
	return ret;
}

uint64_t bt_read_atom(bt_handle_t a){
	volatile uint64_t ret;
	btos_call(BT_READ_ATOM, (uint32_t)a, (uint32_t)&ret, 0);
	return ret;
}

bt_threadhandle bt_new_thread(void (*entry)(void*), void *param, void *stack){
    return btos_call(BT_NEW_THREAD, (uint32_t)entry, (uint32_t)param, (uint32_t)stack);
}

void bt_wait_thread(bt_threadhandle thread){
    btos_call(BT_WAIT_THREAD, thread, 0, 0);
}

void bt_block_thread(){
    btos_call(BT_BLOCK_THREAD, 0, 0, 0);
}

void bt_unblock_thread(bt_threadhandle thread){
    btos_call(BT_UNBLOCK_THREAD, thread, 0, 0);
}

bt_threadhandle bt_get_thread(){
    return btos_call(BT_GET_THREAD, 0, 0, 0);
}

void bt_end_thread(){
    btos_call(BT_END_THREAD, 0, 0, 0);
}

void bt_yield(){
    btos_call(BT_YIELD, 0, 0, 0);
}

void bt_thread_abort(bt_threadhandle thread){
    btos_call(BT_THREAD_ABORT, thread, 0, 0);
}

bool bt_mount(const char *name, const char *device, const char *filesystem){
	return btos_call(BT_MOUNT, (uint32_t)name, (uint32_t)device, (uint32_t)filesystem);
}

bool bt_unmount(const char *name){
	return btos_call(BT_UNMOUNT, (uint32_t)name, 0, 0);
}

bt_filehandle bt_fopen(const char *path, uint32_t flags){
	return btos_call(BT_FOPEN, (uint32_t)path, flags, 0);
}

bool bt_fclose(bt_filehandle file){
	return btos_call(BT_FCLOSE, file, 0, 0);
}

size_t bt_fwrite(bt_filehandle file, size_t bytes, const char *buffer){
	return btos_call(BT_FWRITE, file, bytes, (uint32_t)buffer);
}

size_t bt_fread(bt_filehandle file, size_t bytes, char *buffer){
	return btos_call(BT_FREAD, file, bytes, (uint32_t)buffer);
}

size_t bt_fioctl(bt_filehandle file, int function, size_t bytes, char *buffer){
	volatile bt_fioctl_buffer buf = {bytes, buffer};
	return btos_call(BT_FIOCTL, file, function, (uint32_t)&buf);
}

bt_filesize_t bt_fseek(bt_filehandle file, bt_filesize_t bytes, uint32_t flags){
	volatile bt_filesize_t ret = bytes;
	btos_call(BT_FSEEK, file, (uint32_t)&ret, flags);
	return ret;
}

bool bt_fsetsize(bt_filehandle file, bt_filesize_t size){
	return !!btos_call(BT_FSETSIZE, file, (uint32_t)&size, 0);
}

bool bt_format(const char *fs, const char *device, void *options){
	return !!btos_call(BT_FORMAT, (uint32_t)fs, (uint32_t)device, (uint32_t)options);
}

void bt_fflush(bt_filehandle file){
    btos_call(BT_FFLUSH, file, 0, 0);
}

bt_handle bt_mmap(bt_filehandle file, size_t offset, char *ptr, size_t size){
    volatile bt_mmap_buffer buffer={size, ptr};
    return btos_call(BT_MMAP, file, offset, (uint32_t)&buffer);
}

bt_dirhandle bt_dopen(const char *path, uint32_t flags){
	return btos_call(BT_DOPEN, (uint32_t)path, flags, 0);
}

bool bt_dclose(bt_dirhandle dir){
	return btos_call(BT_DCLOSE, dir, 0, 0);
}

bool bt_dwrite(bt_dirhandle dir, bt_directory_entry entry){
	return btos_call(BT_DWRITE, dir, (uint32_t)&entry, 0);
}

bt_directory_entry bt_dread(bt_dirhandle dir){
	volatile bt_directory_entry ret;
	btos_call(BT_DREAD, dir, (uint32_t)&ret, 0);
	return *(bt_directory_entry*)&ret;
}

size_t bt_dseek(bt_dirhandle dir, size_t bytes, uint32_t flags){
	return btos_call(BT_DSEEK, dir, bytes, flags);
}

bt_directory_entry bt_stat(const char *path){
	volatile bt_directory_entry ret;
	btos_call(BT_STAT, (uint32_t)path, (uint32_t)&ret, 0);
	return *(bt_directory_entry*)&ret;
}

bool bt_load_module(const char *path, const char *params){
	return btos_call(BT_LOAD_MODULE, (uint32_t)path, (uint32_t)params, 0);
}

size_t bt_getenv(const char *name, char *buffer, size_t size){
	return btos_call(BT_GETENV, (uint32_t)name, (uint32_t)buffer, size);
}

bool bt_setenv(const char *name, const char *value, uint32_t flags){
	return btos_call(BT_SETENV, (uint32_t)name, (uint32_t)value, flags);
}

bt_pid_t bt_spawn(const char *path, size_t argc, char **argv){
	return btos_call(BT_SPAWN, (uint32_t)path, argc, (uint32_t)argv);
}

int bt_wait(bt_pid_t pid){
	return btos_call(BT_WAIT, pid, 0, 0);
}

bool bt_kill(bt_pid_t pid){
	return btos_call(BT_KILL, pid, 0, 0);
}

bt_priority bt_prioritize(bt_pid_t pid, bt_priority priority){
	return btos_call(BT_PRIORITIZE, pid, priority, 0);
}

void bt_exit(int retval){
	btos_call(BT_EXIT, (uint32_t)retval, 0, 0);
}

bt_pid_t bt_getpid(){
	return btos_call(BT_GETPID, 0, 0, 0);
}

bt_proc_status bt_get_proc_status(bt_pid_t pid){
	return (bt_proc_status)btos_call(BT_PROCSTATUS, (uint32_t)&pid, 0, 0);
}

uint64_t bt_send(bt_msg_header msg){
	volatile uint64_t ret;
	btos_call(BT_SEND, (uint32_t)&msg, (uint32_t)&ret, 0);
	return ret;
}

bt_msg_header bt_recv(bool block){
	volatile bt_msg_header ret;
	ret.valid=false;
	btos_call(BT_RECV, (uint32_t)&ret, (uint32_t)block, 0);
	return *(bt_msg_header*)&ret;
}

void bt_next_msg(bt_msg_header *msg){
	btos_call(BT_NEXTMSG, (uint32_t)msg, 0, 0);
}

size_t bt_msg_content(bt_msg_header *header, void *buf, size_t size){
	return btos_call(BT_CONTENT, (uint32_t)header, (uint32_t)buf, size);
}

void bt_msg_ack(bt_msg_header *header){
	btos_call(BT_ACK, (uint32_t)header, 0, 0);
}

void bt_subscribe(ENUM_NAME(bt_kernel_messages) msg){
	btos_call(BT_SUBSCRIBE, (uint32_t)msg, 0, 0);
}

void bt_unsubscribe(ENUM_NAME(bt_kernel_messages) msg){
	btos_call(BT_UNSUBSCRIBE, (uint32_t)msg, 0, 0);
}

void bt_msgwait(){
	btos_call(BT_MSGWAIT, 0, 0, 0);
}

bt_msg_header bt_recv_filtered(bt_msg_filter filter, bool block){
	volatile bt_msg_header ret;
	ret.valid=false;
	btos_call(BT_RECVFILTERED, (uint32_t)&filter, (uint32_t)&ret, (uint32_t)block);
	return *(bt_msg_header*)&ret;
}

void bt_next_msg_filtered(bt_msg_header *msg, bt_msg_filter filter){
	btos_call(BT_NEXTMSGFILTERED, (uint32_t)&filter, (uint32_t)msg, 0);
}

bool bt_query_msg(uint64_t id){
	return (bool)btos_call(BT_MSGQUERY, (uint32_t)&id, 0, 0);
}

bt_handle_t bt_make_msg_wait(bt_msg_filter filter){
	return (bt_handle_t)btos_call(BT_MAKE_MSG_WAIT, (uint32_t)&filter, 0, 0);
}

bt_msg_header bt_read_msg_wait(bt_handle_t h){
	volatile bt_msg_header ret;
	ret.valid=false;
	btos_call(BT_READ_MSG_WAIT, (uint32_t)h, (uint32_t)&ret, 0);
	return *(bt_msg_header*)&ret;
}

void bt_closehandle(bt_handle h){
    btos_call(BT_CLOSEHANDLE, (uint32_t)h, 0, 0);
}

bool bt_queryhandle(bt_handle h){
	return !!btos_call(BT_QUERYHANDLE, (uint32_t)h, 0, 0);
}

void bt_waithandle(bt_handle_t h){
	btos_call(BT_WAITHANDLE, (uint32_t)h, 0, 0);
}

bt_handle_t bt_make_wait_any(bt_handle_t *h, size_t count){
	return btos_call(BT_MAKE_WAITANY, (uint32_t)h, (uint32_t)count, 0);
}

bt_handle_t bt_make_wait_all(bt_handle_t *h, size_t count){
	return btos_call(BT_MAKE_WAITALL, (uint32_t)h, (uint32_t)count, 0);
}

size_t bt_wait_index(bt_handle_t h){
	return btos_call(BT_WAIT_INDEX, (uint32_t)h, 0, 0);
}

bool bt_set_uid(uint64_t uid){
	return !!btos_call(BT_SET_UID, (uint32_t)&uid, 0, 0);
}

uint64_t bt_get_uid(){
	uint64_t ret;
	btos_call(BT_GET_UID, (uint32_t)&ret, 0, 0);
	return ret;
}

uint64_t bt_getset_perms(uint16_t ext, uint64_t pmask){
	uint64_t ret = pmask;
	btos_call(BT_GETSET_PERMS, ext, (uint32_t)&ret, 0);
	return ret;
}

uint16_t bt_query_extension(const char *name){
	return btos_call(BT_QUERY_EXT, (uint32_t)name, 0, 0);
}

void bt_multi_call(bt_syscall_item *items, size_t count){
	btos_call(BT_MULTI_CALL, (uint32_t)items, (uint32_t)count, 0);
}
