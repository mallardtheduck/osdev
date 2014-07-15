#include "module_stubs.h"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

#pragma GCC diagnostic ignored "-Wunused-parameter"

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
    /* TODO: Should %1 be %w1? */
    /* TODO: Is there any reason to force the use of eax and edx? */
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    /* TODO: Is it wrong to use 'N' for the port? It's not a 8-bit constant. */
    /* TODO: Should %1 be %w1? */
    /* TODO: Is there any reason to force the use of eax and edx? */
    return ret;
}

uint8_t read_cmos(int reg){
	outb(0x70, reg);
	return inb(0x71);
}

bool cmos_update_in_progress(){
	return read_cmos(0x0A) & (1<<7);
}

int module_main(syscall_table *systbl){
	SYSCALL_TABLE=systbl;
	while(!cmos_update_in_progress());
	while(cmos_update_in_progress());
	int seconds, minutes, hours, day, month, year;
	seconds=read_cmos(0x00);
	minutes=read_cmos(0x02);
	hours=read_cmos(0x04);
	day=read_cmos(0x07);
	month=read_cmos(0x08);
	year=read_cmos(0x09);
	dbgpf("RTC: %i:%i:%i %i/%i/%i\n", hours, minutes, seconds, day, month, year);
	return 0;
}