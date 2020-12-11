#include "rtc_internal.hpp"
#include <dev/rtc.h>
#include <util/asprintf.h>

uint16_t extension_id;
uint64_t boot_msec;

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
	sch_setblock(&rtc_sleep_blockcheck, (void*)&p);
}

uint64_t rtc_millis(){
	return get_msecs();
}

uint64_t rtc_get_time(){
	return get_msecs() + boot_msec;
}

rtc_calltable calltable = {&rtc_sleep, &rtc_millis};

void rtc_uapi(uint16_t id,ICPUState &state){
	switch(id){
		case bt_rtc_api::Sleep:{
			rtc_sleep(state.Get32BitRegister(Generic_Register::GP_Register_B));
			break;
		}
		case bt_rtc_api::Millis:{
			*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B) = rtc_millis();
			break;
		}
		case bt_rtc_api::CreateTimer:{
			create_timer(state);
			break;
		}
		case bt_rtc_api::ResetTimer:{
			reset_timer(state);
			break;
		}
		case bt_rtc_api::GetTime:{
			*(uint64_t*)state.Get32BitRegister(Generic_Register::GP_Register_B) = rtc_get_time();
			break;
		}
	}
}

module_api::kernel_extension rtc_extension{(char*)RTC_EXTENSION_NAME, (void*)&calltable, &rtc_uapi};

void init_api(){
	init_timer();
	extension_id = add_extension(&rtc_extension);
}

char *rtc_infofs(){
	char *buf=nullptr;
	datetime dt=current_datetime();
	asprintf(&buf, FORMAT "\n", dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
	return buf;
}

char *msec_infofs(){
	dbgpf("RTC: %i\n", (int)get_msecs());
	char *buf=nullptr;
	asprintf(&buf, "%llu\n", get_msecs());
	return buf;
}

void rtc_init_real(void*){
	sch_setblock(&timer_ready_blockcheck, nullptr);
	datetime dt=current_datetime();
	char buf[128];
	sprintf(buf, FORMAT, dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second);
	proc_setenv("BOOT_TIME", buf, ENV_Global, 0);
	infofs_register("RTC", &rtc_infofs);
	infofs_register("MSEC", &msec_infofs);
	init_api();
}

void rtc_init(){
	sch_new_thread(&rtc_init_real, nullptr);
}
