#include "ps2.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"

static uint8_t channel;
static bool input_available=false;

static void (*write_device)(uint8_t);

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

		//dbgpf("PS2: Mouse data: %x %x %x\n", (int)byte1, (int)byte2, (int)byte3);
		uint8_t state=byte1;
		int16_t mouse_x=byte2 - ((state << 4) & 0x100);
		int16_t mouse_y=byte3 - ((state << 3) & 0x100);

		bool button1=state & (1 << 0);
		bool button2=state & (1 << 1);
		bool button3=state & (1 << 2);
		dbgpf("PS2: b1: %i b2: %i b3: %i x: %i y: %i\n", (int)button1, (int)button2, (int)(button3), (int)mouse_x, (int)mouse_y);
	}
}

void init_mouse(uint8_t mchannel){
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
	write_device(Device_Command::EnableReporting);

	handle_irq(irq, &mouse_handler);
	new_thread(&mouse_thread, NULL);
	unmask_irq(irq);
}