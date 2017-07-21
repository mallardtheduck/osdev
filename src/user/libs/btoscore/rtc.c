#include <btos.h>
#include <dev/rtc.h>

uint16_t bt_rtc_ext_id;

void bt_rtc_init(){
	if(bt_rtc_ext_id == 0) bt_rtc_ext_id = bt_query_extension(RTC_EXTENSION_NAME);
}

uint32_t bt_rtc_api_call(uint16_t fn, uint32_t b, uint32_t c, uint32_t d){
	bt_rtc_init();
	uint32_t a = (bt_rtc_ext_id << 16) + fn;
	return btos_call(a, b, c, d);
}

void bt_rtc_sleep(uint32_t msec){
	bt_rtc_api_call(ENUM_GET(bt_rtc_api, Sleep), msec, 0, 0);
}

uint64_t bt_rtc_millis(){
	uint64_t ret;
	bt_rtc_api_call(ENUM_GET(bt_rtc_api, Millis), (uint32_t)&ret, 0, 0);
	return ret;
}

bt_handle_t bt_rtc_create_timer(uint32_t duration){
	bt_handle_t ret = 0;
	bt_rtc_api_call(ENUM_GET(bt_rtc_api, CreateTimer), duration, (uint32_t)&ret, 0);
	return ret;
}

void bt_rtc_reset_timer(bt_handle_t timer){
	bt_rtc_api_call(ENUM_GET(bt_rtc_api, ResetTimer), (uint32_t)timer, 0, 0);
}

uint64_t bt_rtc_get_time(){
	uint64_t ret;
	bt_rtc_api_call(ENUM_GET(bt_rtc_api, GetTime), (uint32_t)&ret, 0, 0);
	return ret;
}