#ifndef _RTC_H
#define _RTC_H

#include <util/bt_enum.h>

#define RTC_EXTENSION_NAME "RTC"

ENUM_START(bt_rtc_api)
	ENUM_SET(bt_rtc_api, Sleep, 1),
	ENUM_SET(bt_rtc_api, Millis, 2),
	ENUM_SET(bt_rtc_api, CreateTimer, 3),
	ENUM_SET(bt_rtc_api, ResetTimer, 4),
	ENUM_SET(bt_rtc_api, GetTime, 5),
ENUM_END;
ENUM_TYPE(bt_rtc_api);

#if defined(KERNEL) || defined(KERNEL_MODULE)

#include <btos_module.h>

struct rtc_calltable{
	void (*rtc_sleep)(uint32_t msec);
	uint64_t (*rtc_millis)();
};

#ifndef RTC_NO_STUBS

extern rtc_calltable *RTC_CALL_TABLE;

#define USE_RTC rtc_calltable *RTC_CALL_TABLE

inline static bool rtc_init(){
	uint16_t extid = get_extension_id(RTC_EXTENSION_NAME);
	if(!extid) return false;
	RTC_CALL_TABLE = (rtc_calltable*) get_extension(extid)->calltable;
	return true;
}

inline static void rtc_sleep(uint32_t msec){
	RTC_CALL_TABLE->rtc_sleep(msec);
}

inline static uint64_t rtc_millis(){
	return RTC_CALL_TABLE->rtc_millis();
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

inline static void bt_rtc_sleep(uint32_t msec){
	bt_rtc_api_call(ENUM_GET(bt_rtc_api, Sleep), msec, 0, 0);
}

inline static uint64_t bt_rtc_millis(){
	uint64_t ret;
	bt_rtc_api_call(ENUM_GET(bt_rtc_api, Millis), (uint32_t)&ret, 0, 0);
	return ret;
}

inline static bt_handle_t bt_rtc_create_timer(uint32_t duration){
	bt_handle_t ret = 0;
	bt_rtc_api_call(ENUM_GET(bt_rtc_api, CreateTimer), duration, (uint32_t)&ret, 0);
	return ret;
}

inline static void bt_rtc_reset_timer(bt_handle_t timer){
	bt_rtc_api_call(ENUM_GET(bt_rtc_api, ResetTimer), (uint32_t)timer, 0, 0);
}

inline static uint64_t bt_rtc_get_time(){
	uint64_t ret;
	bt_rtc_api_call(ENUM_GET(bt_rtc_api, GetTime), (uint32_t)&ret, 0, 0);
	return ret;
}

#endif

#endif