#ifndef _PCIBUS_HPP
#define _PCIBUS_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>
#include "lockable.hpp"

namespace btos_api{
namespace hwpnp{
	
	class IPCIBus : public IDevice, public ILockable{
	public:
		virtual uint8_t ReadConfigByte(size_t index, uint8_t offset) = 0;
		virtual uint16_t ReadConfigWord(size_t index, uint8_t offset) = 0;
		virtual uint32_t ReadConfig32(size_t index, uint8_t offset) = 0;
		
		virtual void WriteConfigByte(size_t index, uint8_t offset, uint8_t value) = 0;
		virtual void WriteConfigWord(size_t index, uint8_t offset, uint16_t value) = 0;
		virtual void WriteConfig32(size_t index, uint8_t offset, uint32_t value) = 0;
		
		IDeviceNode *GetDeviceNode(){ 
			return nullptr;
		}
		
		int GetType() {
			return driver_types::BUS;
		}
	
		virtual ~IPCIBus() {}
	};
	
}
}

#endif