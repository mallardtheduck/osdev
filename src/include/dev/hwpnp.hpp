#ifndef _HWPNP_HPP
#define _HWPNP_HPP

#if !defined(KERNEL) && !defined(KERNEL_MODULE) && !defined(_DMI_HPP)
#error "<dev/hwpnp.hpp> is for kernel/module use only. Userspace API can be used via <ext/dmi.hpp>."
#endif

#ifndef KERNEL
#include <stdint.h>
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
		ENUM_SET(PNPBUS, ATA, 4),
		ENUM_SET(PNPBUS, SCSI, 5),
		ENUM_SET(PNPBUS, PS2, 6),
		
		ENUM_SET(PNPBUS, Volume, 101),
		ENUM_SET(PNPBUS, Partition, 102),
		
		ENUM_SET(PNPBUS, Software, 900),
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
	
	inline static bool operator==(const DeviceID &a, const DeviceID &b){
		return 
			a.Bus == b.Bus &&
			a.VendorID == b.VendorID &&
			a.DeviceID == b.DeviceID &&
			a.Revision == b.Revision &&
			a.ExtraID == b.ExtraID &&
			a.Class == b.Class;
	}
	
	inline static bool operator!=(const DeviceID &a, const DeviceID &b){
		return !(a == b);
	}
	
	ENUM_START(DriverPriority)
		ENUM_SET(DriverPriority, Fallback, 1),
		ENUM_SET(DriverPriority, Generic, 100),
		ENUM_SET(DriverPriority, Specific, 1000),
	ENUM_END
	ENUM_TYPE(DriverPriority);
	
	static const DeviceID NullDeviceID = {PNPBUS::Null, 0, 0, 0, 0, 0};

#ifndef _DMI_HPP
	
	class IDeviceNode{
	public:
		virtual const char *GetBaseName() = 0;
		virtual void *Open() = 0;
		virtual bool Close(void *h) = 0;
		virtual size_t Read(void *h, size_t bytes, char *buf) = 0;
		virtual size_t Write(void *h, size_t bytes, const char *buf) = 0;
		virtual bt_filesize_t Seek(void *h, bt_filesize_t pos, uint32_t flags) = 0;
		virtual int IOCtl(void *h, int fn, size_t bytes, char *buf) = 0;
		virtual int GetType() = 0;
		virtual const char *GetDescription() = 0;
	
		virtual ~IDeviceNode() {}
	};
	
	class IDriver;
	
	class IDevice{
	public:
		virtual DeviceID GetID() = 0;
		virtual const char *GetDescription() = 0;
		virtual int GetType() = 0;
		virtual size_t GetSubDeviceCount() = 0;
		virtual DeviceID GetSubDevice(size_t) = 0;
		virtual IDriver *GetDriver() = 0;
		virtual IDeviceNode *GetDeviceNode() = 0;
		
		virtual ~IDevice() {}
	};
	
	class ITimerDevice;
	
	class IRootDevice : public IDevice{
	public:
		virtual ITimerDevice *GetSysTimer() = 0;
		virtual int GetType() {
			return driver_types::COMPUTER;
		}
		virtual IDeviceNode *GetDeviceNode(){
			return nullptr;
		}
		
		virtual ~IRootDevice() {}
	};
	
	class IDriver{
	public:
		virtual DeviceID GetDeviceID() = 0;
		virtual bool IsCompatible(const DeviceID &dev) = 0;
		virtual IDevice *CreateDevice(const DeviceID &dev, IDevice *parent, size_t index) = 0;
		virtual const char *GetDescription() = 0;
		virtual void DestroyDevice(IDevice *dev) = 0;
		virtual uint32_t GetPriority() = 0;
	
		virtual ~IDriver() {}
	};
	
#endif /*_DMI_HPP*/
	
}
}

#endif