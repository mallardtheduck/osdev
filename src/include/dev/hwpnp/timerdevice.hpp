#ifndef _TIMERDEVICE_HPP
#define _TIMERDEVICE_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>

namespace btos_api{
namespace hwpnp{
	
	class ITimerDevice : public IDevice{
	public:
		virtual uint64_t GetTime() = 0;
		virtual uint64_t GetMillis() = 0;
		virtual void SetTime(uint64_t time) = 0;
		
		IDeviceNode *GetDeviceNode(){ 
			return nullptr;
		}
		
		int GetType() {
			return driver_types::TIMER;
		}
	
		virtual ~ITimerDevice() {}
	};
	
}
}

#endif