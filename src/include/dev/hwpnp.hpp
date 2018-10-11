#ifndef _HWPNP_HPP
#define _HWPNP_HPP

#ifndef KERNEL
#include "../module/module_stubs.h"
#include "../module/module_cpp.hpp"
#endif
#include "../util/bt_enum.h"
#include <btos/devices.h>

namespace btos_api{
namespace hwpnp{
	
	ENUM_START(PNPBUS)
		ENUM_SET(PNPBUS, Null, -1),
		ENUM_SET(PNPBUS, Root, 0),
		ENUM_SET(PNPBUS, PCBUS, 1),
		ENUM_SET(PNPBUS, ISA, 2),
		ENUM_SET(PNPBUS, PCI, 3),
		ENUM_SET(PNPBUS, IDE, 4),
		
		ENUM_SET(PNPBUS, Software, 100),
	ENUM_END
	ENUM_TYPE(PNPBUS);
	
	struct DeviceID{
		ENUM_NAME(PNPBUS) Bus;
		uint64_t VendorID;
		uint64_t DeviceID;
		uint64_t Revision;
		uint64_t ExtraID;
		uint64_t Class;
	};
	
	static const DeviceID NullDeviceID = {PNPBUS::Null, 0, 0, 0, 0, 0};
	
	class IDriver;
	
	class IDevice{
	public:
		virtual DeviceID GetID() = 0;
		virtual const char *GetDescription() = 0;
		virtual int GetType() = 0;
		virtual size_t GetSubDeviceCount() = 0;
		virtual DeviceID GetSubDevice(size_t) = 0;
		virtual IDriver *GetDriver() = 0;
		
		virtual ~IDevice() {}
	};
	
	class ITimerDevice;
	
	class IRootDevice : public IDevice{
	public:
		virtual ITimerDevice *GetSysTimer() = 0;
		virtual int GetType() {
			return driver_types::COMPUTER;
		}
		
		virtual ~IRootDevice() {}
	};
	
	class IDriver{
	public:
		virtual DeviceID GetDeviceID() = 0;
		virtual bool IsCompatible(const DeviceID &dev) = 0;
		virtual IDevice *CreateDevice(const DeviceID &dev, IDevice *parent, size_t index) = 0;
		virtual void DestroyDevice(IDevice *dev) = 0;
	
		virtual ~IDriver() {}
	};
	
}
}

#endif