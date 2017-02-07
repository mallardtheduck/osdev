#include "kernel.hpp"
#include "locks.hpp"

#define PORT 0x3f8   /* COM1 */

char dbgbuf[256];
lock ser_lock;

void init_serial() {
	init_lock(ser_lock);
	outb(PORT + 1, 0x00);    // Disable all interrupts
	outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outb(PORT + 1, 0x00);    //                  (hi byte)
	outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	serial_writestring("Serial debugging enabled.\n");
}

void reinit_serial() {
	outb(PORT + 1, 0x00);    // Disable all interrupts
	outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outb(PORT + 1, 0x00);    //                  (hi byte)
	outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	serial_writestring("Serial debugging enabled.\n");
}

int is_transmit_empty() {
	//if(!try_take_lock_exclusive(ser_lock))return -1;
	int ret=inb(PORT + 5) & 0x20;
	//release_lock(ser_lock);
	return ret;
}

void write_serial(const char a) {
	if(a == '\n') write_serial('\r');
	//if(!try_take_lock_exclusive(ser_lock)) return;
    bool interrupts= are_interrupts_enabled();
    disable_interrupts();
    while (is_transmit_empty() == 0);
	outb(PORT, a);
    if(interrupts)enable_interrupts();
	//release_lock(ser_lock);
	while (is_transmit_empty() == 0);
}

extern "C" void serial_writestring(const char *str){
	if(!str) return;
    bool interrupts= are_interrupts_enabled();
    disable_interrupts();
	for(int i=0; str[i]!='\0'; ++i) write_serial(str[i]);
    if(interrupts)enable_interrupts();
}

int serial_received() {
	if(!try_take_lock_exclusive(ser_lock))return -1;
	int ret=inb(PORT + 5) & 1;
	release_lock(ser_lock);
	return ret;
}
 
char read_serial() {
	while (serial_received() == 0);
	if(!try_take_lock_exclusive(ser_lock))return '\0';
	char ret=inb(PORT);
	release_lock(ser_lock);
	return ret;
}
