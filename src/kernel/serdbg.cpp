#include "kernel.hpp"
#include "locks.hpp"

#define PORT 0x3f8   /* COM1 */

char dbgbuf[256];
StaticAllocLock ser_lock;

void init_serial_debug() {
	ser_lock.Init();
	GetHAL().IOOutByte(PORT + 1, 0x00);    // Disable all interrupts
	GetHAL().IOOutByte(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	GetHAL().IOOutByte(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	GetHAL().IOOutByte(PORT + 1, 0x00);    //                  (hi byte)
	GetHAL().IOOutByte(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	GetHAL().IOOutByte(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	GetHAL().IOOutByte(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	serial_writestring("Serial debugging enabled.\n");
}

void reinit_serial() {
	GetHAL().IOOutByte(PORT + 1, 0x00);    // Disable all interrupts
	GetHAL().IOOutByte(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	GetHAL().IOOutByte(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	GetHAL().IOOutByte(PORT + 1, 0x00);    //                  (hi byte)
	GetHAL().IOOutByte(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	GetHAL().IOOutByte(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	GetHAL().IOOutByte(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	serial_writestring("Serial debugging enabled.\n");
}

int is_transmit_empty() {
	//if(!try_take_lock_exclusive(ser_lock))return -1;
	int ret=GetHAL().IOInByte(PORT + 5) & 0x20;
	//release_lock(ser_lock);
	return ret;
}

void write_serial(const char a) {
	if(a == '\n') write_serial('\r');
	//if(!try_take_lock_exclusive(ser_lock)) return;
	bool interrupts = GetHAL().AreInterruptsEnabled();
	GetHAL().DisableInterrupts();
	while (is_transmit_empty() == 0) {};
	GetHAL().IOOutByte(PORT, a);
	if(interrupts) GetHAL().EnableInterrupts();
	//release_lock(ser_lock);
	while (is_transmit_empty() == 0);
}

extern "C" void serial_writestring(const char *str){
	if(!str) return;
	bool interrupts = GetHAL().AreInterruptsEnabled();
	GetHAL().DisableInterrupts();
	for(int i=0; str[i]!='\0'; ++i) write_serial(str[i]);
	if(interrupts) GetHAL().EnableInterrupts();
}

int serial_received() {
	if((ser_lock)->TryTakeExclusive()) return -1;
	int ret = GetHAL().IOInByte(PORT + 5) & 1;
	ser_lock->Release();
	return ret;
}
 
char read_serial() {
	while (serial_received() == 0);
	if(!ser_lock->TryTakeExclusive()) return '\0';
	char ret = GetHAL().IOInByte(PORT);
	ser_lock->Release();
	return ret;
}
