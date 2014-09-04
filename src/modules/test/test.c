#include "module_stubs.h"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];
lock lck;
uint64_t test_thread_id=0;

volatile bool unblock_end=false;

#pragma GCC diagnostic ignored "-Wunused-parameter"

bool test(char *item, bool value){
	dbgout("TEST: ");
	dbgout(item);
	if(value){
		dbgout(" - PASS\n");
	}else{
		dbgout(" - FAIL\n");
		char buf[128];
		sprintf(buf, "(TEST) Failure! (%s)\n", item);
		panic(buf);
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

void abortable_thread(void*q){
	thread_abortable(true);
	while(true)asm("hlt");
}

void *test_driver_open(){
	dbgout("TEST: Driver open.\n");
	return (void*)0x42;
}

bool test_driver_close(void *instance){
	dbgout("TEST: Driver close.\n");
	if(instance==(void*)0x42) return true;
	else return false;
}

size_t test_driver_read(void *instance, size_t bytes, char *buf){
	if(instance==(void*)0x42){
		memset(buf, 0xee, bytes);
		return bytes;
	}
	return 0;
}

size_t test_driver_write(void *instance, size_t bytes, char *buf){
	if(instance==(void*)0x42){
		return bytes;
	}
	return 0;
}

size_t test_driver_seek(void *instance, size_t pos, bool relative){
	return 0;
}

int test_driver_ioctl(void *instance, int fn, size_t bytes, char *buf){
	return 0;
}

int test_driver_type(){
	return USER;
}

char *test_driver_desc(){
	return (char*)"Test device.";
}

drv_driver test_driver={
	&test_driver_open,	//void *(*open)();
	&test_driver_close,	//bool (*close)(void *instance);
	&test_driver_read,	//int (*read)(void *instance, size_t bytes, char *buf);
    &test_driver_write,	//bool (*write)(void *instance, size_t bytes, char *buf);
    &test_driver_seek,	//void (*seek)(void *instance, size_t pos, bool relative);
    &test_driver_ioctl,	//int (*ioctl)(void *instance, int fn, size_t bytes, char *buf);
    &test_driver_type,	//int (*type)();
    &test_driver_desc,	//char *(*desc)();
};

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
	end_thread();
	test("end_thread()", false);
}

int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
	if(params) dbgpf("TEST: Parameters: %s\n", params);
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
	strncpy(str1, str2, 5);
	a=(strcmp(str1, str2)==0);
	test("strncpy()", a);
	lck=-1;
	init_lock(&lck);
	test("init_lock()", !lck);
	take_lock(&lck);
	test("take_lock()", !!lck);
	release_lock(&lck);
	test("release_lock()", !lck);
	try_take_lock(&lck);
    test("try_take_lock()", !!lck);
    release_lock(&lck);
    test("dbgout()", true);
    uint64_t id=new_thread(&test_thread, NULL);
    thread_wait(id);
    test("end_thread(), thread_wait()", true);
    char devname[]={'T','E','S','T','\0','\0','\0','\0','\0'};
	add_device(devname, &test_driver, NULL);
	void *d=devopen(devname);
	test("add_device(), devopen()", (d!=NULL));
	uint64_t abort_id=new_thread(&abortable_thread, NULL);
	thread_abort(abort_id);
	test("thread_abortable(), thread_abort()", true);
	unsigned char r=0x00;
	devread(d, 1, (char*)&r);
	test("devread()", r==0xee);
	test("devwrite()", devwrite(d, 1, (char*)&d));
	//test("devseek()", devseek(d, 1, true));
	test("devioctl()", devioctl(d, 0, 0, NULL)==0);
	test("devtype()", devtype(devname)==USER);
	test("devdesc()", devdesc(devname)==test_driver_desc());
	test("devclose()", devclose(d));
	return 0;
}