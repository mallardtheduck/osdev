#ifndef DEV_RTC_HPP
#define DEV_RTC_HPP

#include <util/bt_enum.h>
#include <module/kernelsys/extension.hpp>

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

#ifdef KERNEL_MODULE
#include <btos_module.h>
#else
#define RTC_NO_STUBS
#endif

struct rtc_calltable{
	void (*rtc_sleep)(uint32_t msec);
	uint64_t (*rtc_millis)();
};

class RTCExtension : public IKernelExtension{
public:
	const char *GetName() override;
	void UserAPIHandler(uint16_t fn, ICPUState &state) override;

	void Sleep(uint32_t msec);
	uint64_t Millis();
};

#ifndef RTC_NO_STUBS

extern RTCExtension *RTC_EXTENSION;

#define USE_RTC RTCExtension *RTC_EXTENSION

//TODO: Implement

// bool RTCInit(){
// 	uint16_t extid = get_extension_id(RTC_EXTENSION_NAME);
// 	if(!extid) return false;
// 	RTC_CALL_TABLE = (rtc_calltable*) get_extension(extid)->calltable;
// 	return true;
// }

// inline static void rtc_sleep(uint32_t msec){
// 	RTC_CALL_TABLE->rtc_sleep(msec);
// }

// inline static uint64_t rtc_millis(){
// 	return RTC_CALL_TABLE->rtc_millis();
// }

#endif

#else

#include <btos.h>

//In btoscore

extern uint16_t bt_rtc_ext_id;

#ifdef __cplusplus
namespace btos_api{
#endif

EXTERN_C void bt_rtc_init();
EXTERN_C uint32_t bt_rtc_api_call(uint16_t fn, uint32_t b, uint32_t c, uint32_t d);
EXTERN_C void bt_rtc_sleep(uint32_t msec);
EXTERN_C uint64_t bt_rtc_millis();
EXTERN_C bt_handle_t bt_rtc_create_timer(uint32_t duration);
EXTERN_C void bt_rtc_reset_timer(bt_handle_t timer);
EXTERN_C uint64_t bt_rtc_get_time();

#ifdef __cplusplus
}
#endif

#endif

#endif
