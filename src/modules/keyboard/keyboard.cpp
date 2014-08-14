#include "module_stubs.h"
#include "io.h"
#include "module_cpp.hpp"
#include "keyboard.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

const size_t buffer_size=128;
uint32_t buffer[buffer_size];
volatile size_t buffer_count=0;
size_t buffer_top=0;
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
uint32_t scancode2buffervalue(uint8_t c);

void add_to_buffer(uint32_t c){
	if(buffer_count < buffer_size){
		buffer_count++;
		buffer[buffer_top] = c;
		buffer_top++;
        if(buffer_top == buffer_size) buffer_top=0;
        dbgpf("KEYBOARD: %i in buffer, top at %i.\n", buffer_count, buffer_top);
	}
}

uint32_t read_from_buffer(){
	if(buffer_count){
		int start=buffer_top-buffer_count;
		if(start < 0) {
			start+=buffer_size;
		}
		buffer_count--;
		dbgpf("KEYBOARD: %i in buffer, top at %i.\n", buffer_count, buffer_top);
		return buffer[start];
	}else return 0;
}

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
			if(buffer_count<buffer_size){
				uint16_t keycode=scancode2keycode(key);
				if(keycode){
					add_to_buffer(scancode2buffervalue(key));
					updateflags(keycode);
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
	if(code==0) code=layout[(size_t)c][KI_Normal];
	if(code==0) return 0;
	ret |= code | currentflags;
	return ret;
}

uint32_t scancode2buffervalue(uint8_t c){
	uint8_t flag=Keyboard_Flag;
	uint8_t scancode=c;
	uint16_t keycode=scancode2keycode(c);
	return (flag << 24) | (scancode << 16) | keycode;
}

void updateflags(uint16_t keycode){
	if(!(keycode & KeyFlags::NonASCII)) return;
	if(keycode & KeyFlags::KeyUp){
		if((keycode & KC_Mask) == KeyCodes::Shift) currentflags &= ~KeyFlags::Shift;
		if((keycode & KC_Mask) == KeyCodes::Alt) currentflags &= ~KeyFlags::Alt;
		if((keycode & KC_Mask) == KeyCodes::Control) currentflags &= ~KeyFlags::Control;
		if((keycode & KC_Mask) == KeyCodes::Meta) currentflags &= ~KeyFlags::Meta;
	} else {
		if((keycode & KC_Mask) == KeyCodes::Shift) currentflags |= KeyFlags::Shift;
		if((keycode & KC_Mask) == KeyCodes::Alt) currentflags |= KeyFlags::Alt;
		if((keycode & KC_Mask) == KeyCodes::Control) currentflags |= KeyFlags::Control;
		if((keycode & KC_Mask) == KeyCodes::Meta) currentflags |= KeyFlags::Meta;
		if((keycode & KC_Mask) == KeyCodes::CapsLock) currentflags ^= KeyFlags::CapsLock;
		if((keycode & KC_Mask) == KeyCodes::NumLock) currentflags ^= KeyFlags::NumLock;
	}
	//Update LEDs...
	return;
}

struct keyboard_instance{
	bool rawmode;
};

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
	return buffer_count >= *(size_t*)p;
}

size_t keyboard_read(void *instance, size_t bytes, char *cbuf){
	if((bytes % sizeof(uint32_t))) return 0;
	size_t values = bytes / sizeof(uint32_t);
	uint32_t *buf=(uint32_t*)cbuf;
	if(values > buffer_size) values=buffer_size;
	while(true){
		if(buffer_count < values){
			thread_setblock(&keyread_lockcheck, (void*)&values);
		}
		take_lock(&buf_lock);
		if(buffer_count >= values) break;
		release_lock(&buf_lock);
	}
	for(size_t i=0; i<values; ++i){
		uint32_t buffervalue=read_from_buffer();
		buf[i]=buffervalue;
	}
	release_lock(&buf_lock);
	return bytes;
}

size_t keyboard_write(void *instance, size_t bytes, char *buf){
	return 0;
}

size_t keyboard_seek(void *instance, size_t pos, bool relative){
	return 0;
}

int keyboard_ioctl(void *instance, int fn, size_t bytes, char *buf){
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

extern "C" int module_main(syscall_table *systbl, char *params){
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