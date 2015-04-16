#include "ps2.hpp"
#include <circular_buffer.hpp>

#pragma GCC diagnostic ignored "-Wunused-parameter"

static uint8_t channel;
static bool input_available=false;
static constexpr bt_mouse_packet zero_packet={0, 0, 0};

static circular_buffer<bt_mouse_packet, 512> mouse_buffer{zero_packet};
static circular_buffer<uint8_t, 48> pre_buffer{0};

static uint8_t irq;
static thread_id_t mouse_thread_id;
static lock buf_lock;

static void (*write_device)(uint8_t);


static void mouse_handler(int irq, isr_regs *regs){
	uint8_t ps2_byte= ps2_read_data_nocheck();
	pre_buffer.add_item(ps2_byte);
	input_available = true;
	if(thread_id()!=mouse_thread_id) {
		enable_interrupts();
		yield();
		disable_interrupts();
	}
}

bool input_blockcheck(void*){
	return !!pre_buffer.count();
}

void mouse_thread(void*){
	thread_priority(1);
	while(true){
		uint8_t byte1=0, byte2=0, byte3=0;
		while(!(byte1 & (1 << 3))) {
			thread_setblock(&input_blockcheck, NULL);
			disable_interrupts();
			byte1 = pre_buffer.read_item();
			input_available = false;
			enable_interrupts();
		}
		thread_setblock(&input_blockcheck, NULL);
		disable_interrupts();
		byte2=pre_buffer.read_item();
		input_available=false;
		enable_interrupts();
		thread_setblock(&input_blockcheck, NULL);
		disable_interrupts();
		byte3=pre_buffer.read_item();
		input_available=false;
		enable_interrupts();

		uint8_t state=byte1;
		int16_t mouse_x=byte2 - ((state << 4) & 0x100);
		int16_t mouse_y=byte3 - ((state << 3) & 0x100);

		if(!(state & (1 << 3))){
			dbgpf("PS2: Invalid first mouse byte: %x!\n", state);
			disable_interrupts();
			pre_buffer.clear();
			input_available=false;
			enable_interrupts();
			mask_irq(irq);
			write_device(Device_Command::Reset);
			write_device(Device_Command::EnableReporting);
			unmask_irq(irq);
			continue;
		}

		bool button1=state & (1 << 0);
		bool button2=state & (1 << 1);
		bool button3=state & (1 << 2);
		bt_mouse_packet packet;
		packet.flags = MouseFlags::Valid | (button1?MouseFlags::Button1:0) | (button2?MouseFlags::Button2:0) | (button3?MouseFlags::Button3:0);
		packet.x_motion=mouse_x;
		packet.y_motion=mouse_y;
		take_lock(&buf_lock);
		mouse_buffer.add_item(packet);
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
	return mouse_buffer.count() >= *(size_t*)p;
}

size_t mouse_read(void *instance, size_t bytes, char *cbuf){
	if((bytes % sizeof(bt_mouse_packet))) return 0;
	size_t values = bytes / sizeof(bt_mouse_packet);
	bt_mouse_packet *buf=(bt_mouse_packet*)cbuf;
	if(values > mouse_buffer.max_size()) values=mouse_buffer.max_size();
	while(true){
		if(mouse_buffer.count() < values){
			thread_setblock(&mouseread_lockcheck, (void*)&values);
		}
		take_lock(&buf_lock);
		if(mouse_buffer.count() >= values) break;
		release_lock(&buf_lock);
	}
	for(size_t i=0; i<values; ++i){
		bt_mouse_packet buffervalue=mouse_buffer.read_item();
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
	if(fn==bt_mouse_ioctl::ClearBuffer) {
		take_lock(&buf_lock);
		mouse_buffer.clear();
		release_lock(&buf_lock);
	}
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

	pre_buffer.clear();
	handle_irq(irq, &mouse_handler);
	mouse_thread_id=new_thread(&mouse_thread, NULL);
	write_device(Device_Command::EnableReporting);
	unmask_irq(irq);

	add_device("MOUSE", &mouse_driver, NULL);
}