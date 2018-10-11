#include "rtc.hpp"

uint16_t extension_id;

struct rtc_sleep_params{
	uint64_t start;
	uint32_t duration;
};

bool rtc_sleep_blockcheck(void *p){
	rtc_sleep_params &params = *(rtc_sleep_params*)p;
	return (get_msecs() - params.start >= params.duration);
}

void rtc_sleep(uint32_t msec){
	rtc_sleep_params p = {get_msecs(), msec};
	thread_setblock(&rtc_sleep_blockcheck, (void*)&p);
}

uint64_t rtc_millis(){
	return get_msecs();
}

uint64_t rtc_get_time(){
	return get_msecs() + boot_msec;
}

rtc_calltable calltable = {&rtc_sleep, &rtc_millis};

void rtc_uapi(uint16_t id,isr_regs *regs){
	switch(id){
		case bt_rtc_api::Sleep:{
			rtc_sleep(regs->ebx);
			break;
		}
		case bt_rtc_api::Millis:{
			*(uint64_t*)regs->ebx = rtc_millis();
			break;
		}
		case bt_rtc_api::CreateTimer:{
			create_timer(regs);
			break;
		}
		case bt_rtc_api::ResetTimer:{
			reset_timer(regs);
			break;
		}
		case bt_rtc_api::GetTime:{
			*(uint64_t*)regs->ebx = rtc_get_time();
			break;
		}
	}
}

kernel_extension rtc_extension{RTC_EXTENSION_NAME, (void*)&calltable, &rtc_uapi};

void init_api(){
	init_timer();
	extension_id = add_extension(&rtc_extension);
}