#include <btos/timer.hpp>
#include <dev/rtc.h>

namespace btos_api{

Timer::Timer(uint32_t msec) : Handle(bt_rtc_create_timer(msec)) {}

void Timer::Reset(){
	bt_rtc_reset_timer(handle);
}

void Timer::SetHandler(std::function<bool(Timer&)> fn){
	handler = fn;
}
std::function<bool(Timer&)> Timer::GetHandler() const{
	return handler;
}

bool Timer::HandleMessage(const Message &msg){
	if(handler){
		if(msg.Source() == bt_rtc_ext_id && msg.Content<bt_handle_t>() == handle){
			return handler(*this);
		}
	}
	return true;
}

}
