#ifndef _RTC_H
#define _RTC_H

#include <util/bt_enum.h>

#define RTC_EXTENSION_NAME "RTC"

ENUM_START(bt_rtc_api)
	ENUM_SET(bt_rtc_api, Sleep, 1),
ENUM_END;
ENUM_TYPE(bt_rtc_api);

#if defined(KERNEL) || defined(KERNEL_MODULE)

#include <btos_module.h>

struct rtc_calltable{
	void (*rtc_sleep)(uint32_t msec);
};

#ifndef RTC_NO_STUBS

extern rtc_calltable RTC_CALL_TABLE;

#define USE_RTC rtc_calltable RTC_CALL_TABLE

inline static void rtc_init(){
	uint16_t extid = get_extension_id(RTC_EXTENSION_NAME);
	if(!extid) return false;
	RTC_CALL_TABLE = (rtc_calltable*) get_extension(extid)->calltable;
	return true;
}

inline static void rtc_sleep(uint32_t msec){
	RTC_CALL_TABLE->rtc_sleep(msec);
}

#endif

#else

#include <btos.h>

#define USE_BT_RTC_API uint16_t bt_rtc_ext_id = 0
extern uint16_t bt_rtc_ext_id;

inline static void bt_rtc_init(){
	if(bt_rtc_ext_id == 0) bt_rtc_ext_id = bt_query_extension(RTC_EXTENSION_NAME);
}

inline static uint32_t bt_rtc_api_call(uint16_t fn, uint32_t b, uint32_t c, uint32_t d){
	bt_rtc_init();
	uint32_t a = (bt_rtc_ext_id << 16) + fn;
	return btos_call(a, b, c, d);
}

inline static void rtc_sleep(uint32_t msec){
	bt_rtc_api_call(ENUM_GET(bt_rtc_api, Sleep), msec, 0, 0);
}

#endif

#endif