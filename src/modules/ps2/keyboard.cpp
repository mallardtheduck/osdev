#include "ps2.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"

static const size_t buffer_size=128;
static uint32_t buffer[buffer_size];
static volatile size_t buffer_count=0;
static size_t buffer_top=0;
static lock buf_lock;
static bool input_available;
static uint16_t currentflags=0;
static uint8_t irq;
static uint8_t ps2_byte;

static uint8_t channel;

static key_info *layout;
static uint8_t *capskeys;
static uint8_t *numkeys;

extern key_info us_keyboard_layout[128];
extern uint8_t us_keyboard_capskeys[];
extern uint8_t us_keyboard_numkeys[];

static void updateflags(uint16_t keycode);
static uint16_t scancode2keycode(uint8_t c);
static uint32_t scancode2buffervalue(uint8_t c);

static void (*write_device)(uint8_t);

static void add_to_buffer(uint32_t c){
	if(buffer_count < buffer_size){
		buffer_count++;
		buffer[buffer_top] = c;
		buffer_top++;
        if(buffer_top == buffer_size) buffer_top=0;
        //dbgpf("KEYBOARD: %i in buffer, top at %i.\n", buffer_count, buffer_top);
	}
}

static uint32_t read_from_buffer(){
	if(buffer_count){
		int start=buffer_top-buffer_count;
		if(start < 0) {
			start+=buffer_size;
		}
		buffer_count--;
		//dbgpf("KEYBOARD: %i in buffer, top at %i.\n", buffer_count, buffer_top);
		return buffer[start];
	}else return 0;
}

static void keyboard_handler(int irq, isr_regs *regs){
	if(ps2_read_status() & 1) {
		input_available = true;
		ps2_byte=ps2_read_data();
		mask_irq(irq);
	}
	irq_ack(irq);
	enable_interrupts();
	yield();
}

static bool input_blockcheck(void*){
	return input_available;
}

static void keyboard_thread(void*){
	thread_priority(1);
	while(true){
		thread_setblock(input_blockcheck, NULL);
		take_lock(&buf_lock);
		disable_interrupts();
		uint8_t key=ps2_byte;
		unmask_irq(irq);
		if(buffer_count<buffer_size){
			uint16_t keycode=scancode2keycode(key);
			if(keycode){
				add_to_buffer(scancode2buffervalue(key));
				updateflags(keycode);
			}else{
				dbgpf("KEYBOARD: Ignored unmapped scancode %x (%x).\n", (int)key, (int)keycode);
			}
		}
		input_available=false;
		enable_interrupts();
		release_lock(&buf_lock);
	}
}

static bool is_capskey(uint8_t c){
	uint8_t *ptr=capskeys;
	while(true){
		if(!ptr || !*ptr) return false;
		if(*ptr==c) return true;
		ptr++;
	}
}

static bool is_numkey(uint8_t c){
	uint8_t *ptr=numkeys;
	while(true){
		if(!ptr || !*ptr) return false;
		if(*ptr==c) return true;
		ptr++;
	}
}

static uint16_t scancode2keycode(uint8_t c){
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

static uint32_t scancode2buffervalue(uint8_t c){
	uint8_t flag=Keyboard_Flag;
	uint8_t scancode=c;
	uint16_t keycode=scancode2keycode(c);
	return (flag << 24) | (scancode << 16) | keycode;
}

static void updateflags(uint16_t keycode){
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
	uint8_t leds=0;
	if(currentflags & KeyFlags::ScrollLock){
		leds |= 1 << 0;
	}
	if(currentflags & KeyFlags::NumLock){
		leds |= 1 << 1;
	}
	if(currentflags & KeyFlags::CapsLock){
		leds |= 1 << 2;
	}
	write_device(Device_Command::SetLEDs);
	ps2_write_data(leds);
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
	return (char*)"PS/2 keyboard.";
}

drv_driver keyboard_driver={&keyboard_open, &keyboard_close, &keyboard_read, &keyboard_write, &keyboard_seek,
&keyboard_ioctl, &keyboard_type, &keyboard_desc};

void init_keyboard(uint8_t kchannel){
	channel=kchannel;
	init_lock(&buf_lock);
	layout=us_keyboard_layout;
	capskeys=us_keyboard_capskeys;
	numkeys=us_keyboard_numkeys;
	input_available=false;
	if(channel==1){
		irq=Port1IRQ;
		ps2_write_command(PS2_Command::EnablePort1);
		write_device=&ps2_write_port1;

	}else{
		irq=Port2IRQ;
		ps2_write_command(PS2_Command::EnablePort2);
		write_device=&ps2_write_port2;
	}
	write_device(Device_Command::GetSetScanCode);
	ps2_write_data(0x01);
	write_device(Device_Command::EnableScanning);
	handle_irq(irq, &keyboard_handler);
	new_thread(&keyboard_thread, NULL);
	add_device("KEYBD", &keyboard_driver, NULL);
	unmask_irq(irq);
}