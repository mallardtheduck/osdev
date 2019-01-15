#include "rtc_internal.hpp"
#include <dev/hwpnp/timerdevice.hpp>

static btos_api::hwpnp::ITimerDevice *get_timer(){
	auto rootDev = pnp_get_root_device();
	if(!rootDev) return nullptr;
	else return rootDev->GetSysTimer();
}

bool timer_ready_blockcheck(void*){
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