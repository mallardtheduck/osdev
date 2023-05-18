#ifndef DEV_RTC_HPP
#define DEV_RTC_HPP

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

#if defined(__cplusplus) && (defined(KERNEL) || defined(KERNEL_MODULE))
#include <module/kernelsys/extension.hpp>

#ifdef KERNEL_MODULE
#include <btos_module.h>
#else
#define RTC_NO_STUBS
#endif

struct rtc_calltable{
	void (*rtc_sleep)(uint32_t msec);
	uint64_t (*rtc_millis)();
};

class IRTCExtension : public IKernelExtension{
public:
	virtual void Sleep(uint32_t msec) = 0;
	virtual uint64_t Millis() = 0;

	virtual ~IRTCExtension() {}
};

#ifndef RTC_NO_STUBS

extern IRTCExtension *RTC_EXTENSION;

#define USE_RTC IRTCExtension *RTC_EXTENSION

bool RTCInit(){
	uint16_t extid = API->GetKernelExtensionManager().GetExtensionID(RTC_EXTENSION_NAME);
	if(!extid) return false;
	RTC_EXTENSION = static_cast<IRTCExtension*>(API->GetKernelExtensionManager().GetExtension(extid));
	return true;
}

inline static void rtc_sleep(uint32_t msec){
	RTC_EXTENSION->Sleep(msec);
}

inline static uint64_t rtc_millis(){
	return RTC_EXTENSION->Millis();
}

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
