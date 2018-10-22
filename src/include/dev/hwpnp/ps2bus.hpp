#ifndef _PS2BUS_HPP
#define _PS2BUS_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>
#include "lockable.hpp"

namespace btos_api{
namespace hwpnp{

	ENUM_START(PS2DeviceClass)
		ENUM_SET(PS2DeviceClass, Unknown, 0),
		ENUM_SET(PS2DeviceClass, Keyboard, 1),
		ENUM_SET(PS2DeviceClass, Mouse, 2),
	ENUM_END
	ENUM_TYPE(PS2DeviceClass);
	
	class IPS2Bus : public IDevice, public ILockable{
	public:
		virtual uint8_t ReadData() = 0;
		virtual uint8_t ReadDataWithoutStatusCheck() = 0;
		virtual void WriteData(uint8_t byte) = 0;
		virtual void ClearData() = 0;
		virtual uint8_t ReadStatus() = 0;
		virtual void WriteCommand(uint8_t byte) = 0;
		virtual void WritePort(size_t index, uint8_t byte) = 0;
		virtual uint8_t GetIRQ(size_t index) = 0;
		virtual void EnableDevice(size_t index) = 0;
		
		IDeviceNode *GetDeviceNode(){ 
			return nullptr;
		}
		
		int GetType() {
			return driver_types::BUS;
		}
		
		virtual ~IPS2Bus() {}
	};

}
}

#endif