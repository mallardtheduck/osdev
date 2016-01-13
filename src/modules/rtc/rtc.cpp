#include "rtc.hpp"

USE_SYSCALL_TABLE;
USE_DEBUG_PRINTF;

#pragma GCC diagnostic ignored "-Wunused-parameter"

const uint16_t RTC_Index = 0x70;
const uint16_t RTC_Data = 0x71;
const uint8_t RTC_IRQ = 0x08;
const int RTC_Rate = 6;
volatile uint64_t msec_counter = 0;
volatile uint32_t int_counter42 = 0;
volatile uint32_t int_counter1000 = 0;

size_t strlen(const char* str){
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}


uint8_t read_cmos(int reg){
	outb(RTC_Index, reg);
	return inb(RTC_Data);
}

bool cmos_update_in_progress(){
	return read_cmos(0x0A) & (1<<7);
}

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
	ret.year += 2000;
	if(!rtc_24h && !rtc_pm && ret.hour==12) ret.hour=0;
	return ret;
}

char *rtc_infofs(){
	char *buf=(char*)malloc(128);
	datetime dt=current_datetime();
	sprintf(buf, FORMAT "\n", dt.hour, dt.minute, dt.second, dt.day, dt.month, dt.year);
	return buf;
}

void ui64toa(uint64_t n, char s[]){
	size_t i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	s[i] = '\0';
	
	for (size_t i = 0, j = strlen(s)-1; i < j; i++, j--) {
		 char c = s[i];
		 s[i] = s[j];
		 s[j] = c;
	 }
}

char *msec_infofs(){
	dbgpf("RTC: %i\n", (int)msec_counter);
	char *buf=(char*)malloc(128);
	ui64toa(msec_counter, buf);
	sprintf(&buf[strlen(buf)], "\n");
	return buf;
}

void rtc_interrupt(int, isr_regs*){
	++msec_counter;
	++int_counter42;
	++int_counter1000;
	if(int_counter42 == 42){
		--msec_counter;
		int_counter42 = 0;
	}
	if(int_counter1000 == 1000){
		--msec_counter;
		int_counter42 = 0;
		int_counter1000 = 0;
	}
	read_cmos(0x0C);
}

void init_interrupt(){
	handle_irq(RTC_IRQ, &rtc_interrupt);
	disable_interrupts();
	uint8_t regA = read_cmos(0x8A);
	regA = (regA & 0xF0) | RTC_Rate;
	outb(RTC_Index, 0x8A);
	outb(RTC_Data, regA);
	uint8_t regB = read_cmos(0x8B) | 0x40;
	outb(RTC_Index, 0x8B);
	outb(RTC_Data, regB);
	enable_interrupts();
	unmask_irq(RTC_IRQ);
}

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
	init_interrupt();
	datetime dt=read_rtc();
	dbgpf("RTC: " FORMAT "\n", dt.hour, dt.minute, dt.second, dt.day, dt.month, dt.year);
	init_clock(dt);
	char buf[128];
	sprintf(buf, FORMAT, dt.hour, dt.minute, dt.second, dt.day, dt.month, dt.year);
	setenv("BOOT_TIME", buf, ENV_Global, 0);
	infofs_register("RTC", &rtc_infofs);
	infofs_register("MSEC", &msec_infofs);
	init_api();
	return 0;
}