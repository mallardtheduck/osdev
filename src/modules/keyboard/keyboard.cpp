#include "module_stubs.h"
#include "io.h"
#include "module_cpp.hpp"
#include "keycodes.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

const size_t buffer_size=128;
char buffer[buffer_size];
volatile size_t bufferptr=0;
lock buf_lock;
bool input_available;
uint16_t currentflags=0;

key_info *layout;
uint8_t *capskeys;
uint8_t *numkeys;

extern key_info us_keyboard_layout[128];
extern uint8_t us_keyboard_capskeys[];
extern uint8_t us_keyboard_numkeys[];

void updateflags(uint16_t keycode);
uint16_t scancode2keycode(uint8_t c);

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
		take_lock(&buf_lock);
		disable_interrupts();
		while(inb(0x64) & 1){
			uint8_t key=inb(0x60);
			if(bufferptr<buffer_size){
				uint16_t keycode=scancode2keycode(key);
				if(keycode){
					buffer[bufferptr++]=key;
					updateflags(keycode);
					dbgpf("KEYBOARD: Keycode %x proccessed.\n", (int)keycode);
					if(!(keycode & KeyFlags::NonASCII) && !(keycode & KeyFlags::KeyUp)) dbgpf("KEYBOARD: Decoded character: %c\n", (char)keycode);
				}else{
					dbgpf("KEYBOARD: Ignored unmapped scancode %x (%x).\n", (int)key, (int)keycode);
				}
			}
		}
		input_available=false;
		enable_interrupts();
		release_lock(&buf_lock);
	}
}

bool is_capskey(uint8_t c){
	uint8_t *ptr=capskeys;
	while(true){
		if(!ptr || !*ptr) return false;
		if(*ptr==c) return true;
		ptr++;
	}
}

bool is_numkey(uint8_t c){
	uint8_t *ptr=numkeys;
	while(true){
		if(!ptr || !*ptr) return false;
		if(*ptr==c) return true;
		ptr++;
	}
}

uint16_t scancode2keycode(uint8_t c){
	uint16_t ret=0;
	if(c & 0x80){
		ret |= KeyFlags::KeyUp;
		c &= ~0x80;
	}
	size_t index=KI_Normal;
	if(currentflags & KeyFlags::Shift) index=KI_Shift;
	if(currentflags & KeyFlags::Alt) index=KI_AltGr;
	if(currentflags & KeyFlags::CapsLock && is_capskey(c)){
		if(currentflags & KeyFlags::Shift) index=KI_Normal;
		else index=KI_Shift;
	}
	if(currentflags & KeyFlags::NumLock && is_numkey(c)){
		if(currentflags & KeyFlags::Shift) index=KI_Normal;
		else index=KI_Shift;
    }
	uint16_t code=layout[(size_t)c][index];
	dbgpf("KEYBOARD: %x, %i, %x\n", (int)c, index, (int)code);
	if(code==0) code=layout[(size_t)c][KI_Normal];
	if(code==0) return 0;
	ret |= code | currentflags;
	return ret;
}

void updateflags(uint16_t keycode){
	if(!(keycode & KeyFlags::NonASCII)) return;
	if(keycode & KeyFlags::KeyUp){
		if(keycode & KeyCodes::Shift) currentflags &= ~KeyFlags::Shift;
		if(keycode & KeyCodes::Alt) currentflags &= ~KeyFlags::Alt;
		if(keycode & KeyCodes::Control) currentflags &= ~KeyFlags::Control;
		if(keycode & KeyCodes::Meta) currentflags &= ~KeyFlags::Meta;
	} else {
		if(keycode & KeyCodes::Shift) currentflags |= KeyFlags::Shift;
		if(keycode & KeyCodes::Alt) currentflags |= KeyFlags::Alt;
		if(keycode & KeyCodes::Control) currentflags |= KeyFlags::Control;
		if(keycode & KeyCodes::Meta) currentflags |= KeyFlags::Meta;
		if(keycode & KeyCodes::CapsLock) currentflags ^= KeyFlags::CapsLock;
		if(keycode & KeyCodes::NumLock) currentflags ^= KeyFlags::NumLock;
	}
	dbgpf("KEYBOARD: Flags: %x\n", (int)currentflags);
	//Update LEDs...
	return;
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
	if(fn==1 && bytes>=1){
		return scancode2keycode(*buf);
	}
	return 0;
}

int keyboard_type(){
	return driver_types::IN_KEYBOARD;
}

char *keyboard_desc(){
	return (char*)"Hacky PS/2 keyboard driver.";
}

drv_driver keyboard_driver={&keyboard_open, &keyboard_close, &keyboard_read, &keyboard_write, &keyboard_seek,
&keyboard_ioctl, &keyboard_type, &keyboard_desc};

extern "C" int module_main(syscall_table *systbl){
		SYSCALL_TABLE=systbl;
		init_lock(&buf_lock);
		layout=us_keyboard_layout;
		capskeys=us_keyboard_capskeys;
		numkeys=us_keyboard_numkeys;
		input_available=false;
		handle_irq(1, &keyboard_handler);
		new_thread(&keyboard_thread, NULL);
		add_device("KEYBOARD", &keyboard_driver, NULL);
		unmask_irq(1);
    	return 0;
}