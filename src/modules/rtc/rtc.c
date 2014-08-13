#include "module_stubs.h"

#define FORMAT "%02i:%02i:%02i %02i/%02i/%02i"
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

struct datetime{
	int day, month, year;
	int hour, minute, second;
};
typedef struct datetime datetime;

inline static int bcdtobin(int bcd){
	return ( (bcd & 0xF0) >> 1) + ( (bcd & 0xF0) >> 3) + (bcd & 0xf);
}

datetime read_rtc(){
	int status=read_cmos(0x0B);
	bool rtc_bin=(status & 4);
	bool rtc_24h=(status & 2);
	bool rtc_pm=false;
	dbgpf("RTC: 24-Hour:%i Binary:%i\n", (int)rtc_24h, (int)rtc_bin);
	datetime ret;
	while(!cmos_update_in_progress());
	while(cmos_update_in_progress());
	ret.day=read_cmos(0x07);
	ret.month=read_cmos(0x08);
	ret.year=read_cmos(0x09);
	ret.hour=read_cmos(0x04);
	ret.minute=read_cmos(0x02);
	ret.second=read_cmos(0x00);
	if(!rtc_24h){
		rtc_pm=(ret.hour & 0x80);
		ret.hour-=(ret.hour & 0x80);
	}
	if(!rtc_bin){
		ret.day=bcdtobin(ret.day);
		ret.month=bcdtobin(ret.month);
		ret.year=bcdtobin(ret.year);
		ret.hour=bcdtobin(ret.hour);
		ret.minute=bcdtobin(ret.minute);
		ret.second=bcdtobin(ret.second);
	}
	if(rtc_pm){
		ret.hour+=12;
		if(ret.hour==24) ret.hour=12;
	}
	if(!rtc_24h && !rtc_pm && ret.hour==12) ret.hour=0;
	return ret;
}

char *rtc_infofs(){
	char *buf=(char*)malloc(128);
	datetime dt=read_rtc();
	sprintf(buf, FORMAT "\n", dt.hour, dt.minute, dt.second, dt.day, dt.month, dt.year);
	return buf;
}

int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
	datetime dt=read_rtc();
	dbgpf("RTC: " FORMAT "\n", dt.hour, dt.minute, dt.second, dt.day, dt.month, dt.year);
	char buf[128];
	sprintf(buf, FORMAT "\n", dt.hour, dt.minute, dt.second, dt.day, dt.month, dt.year);
	setenv("BOOT_TIME", buf, ENV_Global, 0);

	infofs_register("RTC", &rtc_infofs);
	return 0;
}