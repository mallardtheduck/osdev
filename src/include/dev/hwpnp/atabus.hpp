#ifndef _ATABUS_HPP
#define _ATABUS_HPP

#include "../hwpnp.hpp"
#include <btos/devices.h>

namespace btos_api{
namespace hwpnp{

	ENUM_START(ATADeviceType)
		ENUM_SET(ATADeviceType, Unknown, 0),
		ENUM_SET(ATADeviceType, HDD, 1),
		ENUM_SET(ATADeviceType, ATAPI, 2),
	ENUM_END
	ENUM_TYPE(ATADeviceType);

	class IATABus : public IDevice{
	public:
		virtual void OutByte(size_t index, size_t reg, uint8_t byte) = 0;
		virtual void OutWord(size_t index, size_t reg, uint16_t word) = 0;
		virtual void OutWords(size_t index, size_t reg, size_t count, const uint8_t *buffer) = 0;
		virtual uint8_t InByte(size_t index, size_t reg) = 0;
		virtual uint16_t InWord(size_t index, size_t reg) = 0;
		virtual void InWords(size_t index, size_t reg, size_t count, uint8_t *buffer) = 0;
		virtual uint8_t ReadControlByte(size_t index) = 0;
		virtual void WriteControlByte(size_t index, uint8_t byte) = 0;
		virtual bool IsSlave(size_t index) = 0;
		virtual uint64_t GetLength(size_t index) = 0;
		virtual void ResetIntWait(size_t index) = 0;
		virtual void WaitInt(size_t index) = 0;
		
		IDeviceNode *GetDeviceNode(){ 
			return nullptr;
		}
		
		int GetType() {
			return driver_types::BUS;
		}
		
		virtual ~IATABus() {}
	};

}
}

#endif