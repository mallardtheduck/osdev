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

int is_transmit_empty() {
	take_lock(ser_lock);
	int ret=inb(PORT + 5) & 0x20;
	release_lock(ser_lock);
	return ret;
}

void write_serial(char a) {
	while (is_transmit_empty() == 0);
	take_lock(ser_lock);
	outb(PORT, a);
	release_lock(ser_lock);
	while (is_transmit_empty() == 0);
}

void serial_writestring(char *str){
	for(int i=0; str[i]!='\0'; ++i) write_serial(str[i]);
}

int serial_received() {
	take_lock(ser_lock);
	int ret=inb(PORT + 5) & 1;
	release_lock(ser_lock);
	return ret;
}
 
char read_serial() {
	while (serial_received() == 0);
	take_lock(ser_lock);
	char ret=inb(PORT);
	release_lock(ser_lock);
	return ret;
}
