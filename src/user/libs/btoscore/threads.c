#include <btos.h>
#include <stdlib.h>
#include <stdio.h>

static const size_t reaper_stack_size = 4096;
static bt_threadhandle reaper_thread = 0;
static bt_handle_t reaper_atom;

#define dbgpf(...) do{ char *dbgpf_output; asprintf(&dbgpf_output, __VA_ARGS__); bt_zero(dbgpf_output); free(dbgpf_output); }while(0)

typedef struct{
	void (*entry)(void*);
	void *param;
	char *stack;
	bt_handle_t handle;
	bt_handle_t ready_atom;
} thread_details;

static void reaper(void *param){
	(void)param;
	//dbgpf("CORE: Reaper running!\n");
	while(true){
		bt_wait_atom(reaper_atom, bt_atom_compare_NotEqual, 0);
		thread_details *details = (thread_details*)(uint32_t)bt_read_atom(reaper_atom);
		//dbgpf("CORE: Reaping thread (details: %p)\n", details);
		bt_wait_thread(details->handle);
		free(details->stack);
		bt_closehandle(details->ready_atom);
		free(details);
		bt_modify_atom(reaper_atom, bt_atom_modify_Set, 0);
	}
}

static void init_reaper(){
	if(reaper_thread) return;
	reaper_atom = bt_create_atom(0);
	char *stack = (char*)malloc(reaper_stack_size);
	reaper_thread = bt_new_thread(&reaper, NULL, stack + reaper_stack_size);
}

static void thread_start(void *d){
	//dbgpf("CORE: Starting thread (details: %p @%p)\n", d, &d);
	thread_details *details = (thread_details*)d;
	bt_wait_atom(details->ready_atom, bt_atom_compare_Equal, 1);
	details->entry(details->param);
	uint64_t details64 = (uint64_t)(uint32_t)details;
	while(bt_cmpxchg_atom(reaper_atom, 0, details64) != details64) bt_wait_atom(reaper_atom, bt_atom_compare_Equal, 0);
	bt_end_thread();
}

bt_threadhandle btos_create_thread(void (*entry)(void*), void *param, size_t stack_size){
	init_reaper();
	char *stack = (char*)malloc(stack_size);
	thread_details *details = calloc(1, sizeof(thread_details));
	details->entry = entry;
	details->param = param;
	details->stack = stack;
	details->ready_atom = bt_create_atom(0);
	void **stack_top = (void**)(stack + stack_size - sizeof(void*));
	*stack_top = details;
	//dbgpf("CORE: Creating thread: entry: %p, param: %p, stack: %p, ready_atom: %i. stack_size: %i stack_top: %p details: %p\n", 
	//	details->entry, details->param, details->stack, details->ready_atom, (int)stack_size, stack_top, details);
	bt_handle_t ret = details->handle = bt_new_thread(&thread_start, NULL, stack_top - 1);
	bt_modify_atom(details->ready_atom, bt_atom_modify_Set, 1);
	return ret;
}