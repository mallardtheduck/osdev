#include "module_stubs.h"
#include "io.h"
#include "module_cpp.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

const size_t buffer_size=128;
char buffer[buffer_size];
volatile size_t bufferptr=0;
lock buf_lock;
bool input_available;

extern unsigned char kbdus[128];

void keyboard_handler(int irq, isr_regs *regs){
	input_available=true;
	irq_ack(irq);
	enable_interrupts();
	yield();
}

bool input_blockcheck(void*){
	return input_available;
}

void keyboard_thread(void*){
	thread_priority(1);
	while(true){
		thread_setblock(input_blockcheck, NULL);
		char key;
		while(inb(0x64) & 1){
			key=inb(0x60);
			take_lock(&buf_lock);
			if(bufferptr<buffer_size){
				if(key > 0) {
					key=kbdus[(size_t)key];
					buffer[bufferptr++]=key;
				}
			}
			release_lock(&buf_lock);
		}
		input_available=false;
	}
}

struct keyboard_instance{
	bool rawmode;
};

/*struct drv_driver{
	void *(*open)(void *id);
	bool (*close)(void *instance);
	int (*read)(void *instance, size_t bytes, char *buf);
	bool (*write)(void *instance, size_t bytes, char *buf);
	void (*seek)(void *instance, size_t pos, bool relative);
	int (*ioctl)(void *instance, int fn, size_t bytes, char *buf);
	int (*type)();
	char *(*desc)();
};*/

void *keyboard_open(void *id){
	keyboard_instance *ret=new keyboard_instance();
	ret->rawmode=false;
	return (void*)ret;
}

bool keyboard_close(void *instance){
	delete (keyboard_instance*)instance;
	return true;
}

bool keyread_lockcheck(void *p){
	return bufferptr >= *(size_t*)p;
}

int keyboard_read(void *instance, size_t bytes, char *buf){
	dbgpf("KEYBOARD: Reading %i bytes.\n", bytes);
	if(bytes > buffer_size) bytes=buffer_size;
	while(true){
		if(bufferptr < bytes){
			thread_setblock(&keyread_lockcheck, (void*)&bytes);
		}
		take_lock(&buf_lock);
		if(bufferptr>=bytes) break;
		release_lock(&buf_lock);
	}
	size_t start=bufferptr-bytes;
	for(size_t i=start; i<bytes; ++i){
		buf[i-start]=buffer[i];
	}
	bufferptr-=bytes;
	dbgpf("KEYBOARD: Bytes left: %i\n", bufferptr);
	release_lock(&buf_lock);
	return bytes;
}

bool keyboard_write(void *instance, size_t bytes, char *buf){
	return false;
}

void keyboard_seek(void *instance, size_t pos, bool relative){
}

int keyboard_ioctl(void *instance, int fn, size_t bytes, char *buf){
	return 0;
}

int keyboard_type(){
	return driver_types::IN_KEYBOARD;
}

char *keyboard_desc(){
	return (char*)"Hacky keyboard driver.";
}

drv_driver keyboard_driver={&keyboard_open, &keyboard_close, &keyboard_read, &keyboard_write, &keyboard_seek,
&keyboard_ioctl, &keyboard_type, &keyboard_desc};

extern "C" int module_main(syscall_table *systbl){
		SYSCALL_TABLE=systbl;
		init_lock(&buf_lock);
		input_available=false;
		handle_irq(1, &keyboard_handler);
		new_thread(&keyboard_thread, NULL);
		add_device("KEYBOARD", &keyboard_driver, NULL);
		unmask_irq(1);
    	return 0;
}