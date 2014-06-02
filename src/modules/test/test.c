#include "module_stubs.h"

typedef int (*syscall_vector)(int, void*);
syscall_vector syscall;
uint64_t lock;
uint64_t test_thread_id=0;

volatile bool thread_done=false;
volatile bool unblock_end=false;

bool test(char *item, bool value){
	dbgout("TEST: ");
	dbgout(item);
	if(value){
		dbgout(" - PASS\n");
	}else{
		dbgout(" - FAIL\n");
	}
	return value;
}

void unblocker_thread(void*q){
	while(!unblock_end){
		unblock(test_thread_id);
		yield();
	}
}

void hacky_timeout(void*q){
	int i=0;
	while(!unblock_end && i<1000){
		++i;
		asm("hlt");
	}
	if(!unblock_end){
		test("block(), unblock(), yield()", false);
	}
}

void test_thread(void*q){
	test("new_thread()", true);
	test_thread_id=thread_id();
	test("thread_id()", test_thread_id);
	new_thread(&unblocker_thread, NULL);
	new_thread(&hacky_timeout, NULL);
	block();
	test("block(), unblock(), yield()", true);
	unblock_end=true;
	thread_priority(100);
	test("thread_priority()", true);
	thread_done=true;
	end_thread();
	test("end_thread()", false);
}

int module_main(syscall_vector sys){
	syscall=sys;
	dbgout("TEST: Not testing \"panic()\"...\n");
	void *malloctest=malloc(1024);
	test("malloc()", !!malloctest);
	free(malloctest);
	test("free()", !!malloctest);
	char memtest[32];
	memset(&memtest, 'A', 32);
	test("memset()", (memtest[31]=='A'));
	char copytest[32];
	memcpy(&copytest, &memtest, 32);
	test("memcpy()", (copytest[31]=='A'));
	memset(&copytest, 'B', 32);
	memmove(&memtest, &copytest, 32);
	test("memmove()", (memtest[31]=='B'));
	char *str1="STR1", *str2="STR2";
	bool a=strcmp(str1, str2) && !strcmp(str1, str1);
	test("strcmp()", a);
	strncpy(str1, str2, 4);
	a=!strcmp(str1, str2);
	test("strncpy()", a);
	lock=-1;
	init_lock(&lock);
	test("init_lock()", !lock);
	take_lock(&lock);
	test("take_lock()", !!lock);
	release_lock(&lock);
	test("release_lock()", !lock);
	try_take_lock(&lock);
    test("try_take_lock()", !!lock);
    release_lock(&lock);
    dbgout("No point testing \"dbgout()\"...\n");
    new_thread(&test_thread, NULL);
    while(!thread_done) yield();
    test("end_thread()", true);
	return 0;
}