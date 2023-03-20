#include "rtc_internal.hpp"
#include <dev/hwpnp/timerdevice.hpp>

static btos_api::hwpnp::ITimerDevice *get_timer(){
	auto rootDev = GetHwPnpManager().GetRootDevice();
	if(!rootDev) return nullptr;
	else return rootDev->GetSysTimer();
}

bool is_timer_ready(){
	return get_timer() != nullptr;
}

uint64_t get_msecs(){
	auto timer = get_timer();
	if(!timer) return 0;
	else return timer->GetMillis();
}

datetime current_datetime(){
	auto timer = get_timer();
	if(!timer) return datetime();
	auto time = timer->GetTime();
	return epoch2datetime(time);
}

void rtc_configure(){
	auto timer = get_timer();
	if(timer){
		boot_msec = timer->GetTime();
	}
}