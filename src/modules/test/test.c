#include "module_stubs.h"

typedef int (*syscall_vector)(int, void*);
syscall_vector syscall;
uint64_t lock;

int getthenumber(){
	return 42;
}

void thread_a(void*q){
	while(true){
		take_lock(&lock);
		dbgout("TEST: Thread A\n");
		release_lock(&lock);
		yield();
	}
}

void thread_b(void*q){
	while(true){
		take_lock(&lock);
		dbgout("TEST: Thread B\n");
		release_lock(&lock);
		yield();
	}
}

int module_main(syscall_vector sys){
	syscall=sys;
	int thenumber=getthenumber();
	dbgout("TEST: Hello world!\n");
	init_lock(&lock);
	new_thread(&thread_a, NULL);
	new_thread(&thread_b, NULL);
	block();
	return thenumber*2;
}