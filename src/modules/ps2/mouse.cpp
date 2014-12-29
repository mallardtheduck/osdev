#include "ps2.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"

static uint8_t channel;
static bool input_available=false;

static const size_t buffer_size=512;
static bt_mouse_packet buffer[buffer_size];
static size_t buffer_count=0;
static size_t buffer_top=0;
static const bt_mouse_packet zero_packet={0, 0, 0};

static lock buf_lock;

static void (*write_device)(uint8_t);

static void add_to_buffer(bt_mouse_packet c){
	if(buffer_count < buffer_size){
		buffer_count++;
		buffer[buffer_top] = c;
		buffer_top++;
		if(buffer_top == buffer_size) buffer_top=0;
	}
}

static bt_mouse_packet read_from_buffer(){
	if(buffer_count){
		int start=buffer_top-buffer_count;
		if(start < 0) {
			start+=buffer_size;
		}
		buffer_count--;
		return buffer[start];
	}else return zero_packet;
}


void mouse_handler(int irq, isr_regs *regs){
	input_available=true;
	irq_ack(irq);
	enable_interrupts();
	yield();
}

bool input_blockcheck(void*){
	return input_available;
}

void mouse_thread(void*){
	thread_priority(1);
	while(true){
		thread_setblock(&input_blockcheck, NULL);
		disable_interrupts();
		uint8_t byte1= ps2_read_data();
		input_available=false;
		enable_interrupts();
		thread_setblock(&input_blockcheck, NULL);
		disable_interrupts();
		uint8_t byte2= ps2_read_data();
		input_available=false;
		enable_interrupts();
		thread_setblock(&input_blockcheck, NULL);
		disable_interrupts();
		uint8_t byte3= ps2_read_data();
		input_available=false;
		enable_interrupts();

		uint8_t state=byte1;
		int16_t mouse_x=byte2 - ((state << 4) & 0x100);
		int16_t mouse_y=byte3 - ((state << 3) & 0x100);

		bool button1=state & (1 << 0);
		bool button2=state & (1 << 1);
		bool button3=state & (1 << 2);
		dbgpf("PS2: b1: %i b2: %i b3: %i x: %i y: %i\n", (int)button1, (int)button2, (int)(button3), (int)mouse_x, (int)mouse_y);
		bt_mouse_packet packet;
		packet.flags = MouseFlags::Valid | (button1?MouseFlags::Button1:0) | (button2?MouseFlags::Button2:0) | (button3?MouseFlags::Button3:0);
		packet.x_motion=mouse_x;
		packet.y_motion=mouse_y;
		take_lock(&buf_lock);
		add_to_buffer(packet);
		release_lock(&buf_lock);
	}
}

struct mouse_instance{
};

void *mouse_open(void *id){
	return new mouse_instance();
}

bool mouse_close(void *instance){
	delete (mouse_instance*)instance;
	return true;
}

bool mouseread_lockcheck(void *p){
	return buffer_count >= *(size_t*)p;
}

size_t mouse_read(void *instance, size_t bytes, char *cbuf){
	if((bytes % sizeof(bt_mouse_packet))) return 0;
	size_t values = bytes / sizeof(bt_mouse_packet);
	bt_mouse_packet *buf=(bt_mouse_packet*)cbuf;
	if(values > buffer_size) values=buffer_size;
	while(true){
		if(buffer_count < values){
			thread_setblock(&mouseread_lockcheck, (void*)&values);
		}
		take_lock(&buf_lock);
		if(buffer_count >= values) break;
		release_lock(&buf_lock);
	}
	for(size_t i=0; i<values; ++i){
		bt_mouse_packet buffervalue=read_from_buffer();
		buf[i]=buffervalue;
	}
	release_lock(&buf_lock);
	return bytes;
}

size_t mouse_write(void *instance, size_t bytes, char *cbuf){
	return 0;
}

size_t mouse_seek(void *instance, size_t pos, bool relative){
	return 0;
}

int mouse_ioctl(void *instance, int fn, size_t bytes, char *buf){
	return 0;
}

int mouse_type(){
	return driver_types::IN_MOUSE;
}

char *mouse_description(){
	return (char*)"PS/2 mouse/pointing device.";
}

drv_driver mouse_driver={&mouse_open, &mouse_close, &mouse_read, &mouse_write, &mouse_seek, &mouse_ioctl, &mouse_type, &mouse_description};

void init_mouse(uint8_t mchannel){
	init_lock(&buf_lock);
	channel=mchannel;
	uint8_t irq;
	if(channel==1){
		write_device=&ps2_write_port1;
		irq=Port1IRQ;
		ps2_write_command(PS2_Command::EnablePort1);
	}else{
		write_device=&ps2_write_port2;
		irq=Port2IRQ;
		ps2_write_command(PS2_Command::EnablePort2);
	}
	write_device(Device_Command::Identify);
	uint8_t id=ps2_read_data();
	dbgpf("PS: Mouse type: %x\n", (int)id);
	write_device(Device_Command::Reset);
	write_device(Device_Command::DisableReporting);

	handle_irq(irq, &mouse_handler);
	new_thread(&mouse_thread, NULL);
	unmask_irq(irq);
	write_device(Device_Command::EnableReporting);

	add_device("MOUSE", &mouse_driver, NULL);
}