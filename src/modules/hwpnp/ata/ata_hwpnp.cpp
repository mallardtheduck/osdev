#include <btos_module.h>
#include <dev/hwpnp.hpp>
#include "ata.hpp"

USE_SYSCALL_TABLE;
USE_DEBUG_PRINTF;
USE_PURE_VIRTUAL;
USE_STATIC_INIT;


template<typename DeviceType, typename ParentType, uint32_t priority> 
class DriverTemplate : public btos_api::hwpnp::IDriver{
public:
	virtual btos_api::hwpnp::DeviceID GetDeviceID() = 0;
	
	virtual bool IsCompatible(const btos_api::hwpnp::DeviceID &dev){
		auto id = GetDeviceID();
		return
		    dev.Bus == id.Bus &&
			dev.VendorID == id.VendorID &&
			dev.DeviceID == id.DeviceID &&
			dev.Revision == id.Revision &&
			dev.ExtraID == id.ExtraID &&
			dev.Class == id.Class;
	}
	
	virtual btos_api::hwpnp::IDevice *CreateDevice(const btos_api::hwpnp::DeviceID &, btos_api::hwpnp::IDevice *parent, size_t index){
		return new DeviceType((ParentType*)parent, index);
	}
	
	virtual const char *GetDescription() = 0;
	
	virtual void DestroyDevice(btos_api::hwpnp::IDevice *dev){
		delete (DeviceType*)dev;
	}
	
	virtual uint32_t GetPriority(){
		return priority;
	}
};

template<uint32_t priority> 
class DriverTemplate<void, void, priority> : public btos_api::hwpnp::IDriver{
public:
	virtual btos_api::hwpnp::DeviceID GetDeviceID() = 0;
	
	virtual bool IsCompatible(const btos_api::hwpnp::DeviceID &dev){
		auto id = GetDeviceID();
		return
		    dev.Bus == id.Bus &&
			dev.VendorID == id.VendorID &&
			dev.DeviceID == id.DeviceID &&
			dev.Revision == id.Revision &&
			dev.ExtraID == id.ExtraID &&
			dev.Class == id.Class;
	}
	
	virtual btos_api::hwpnp::IDevice *CreateDevice(const btos_api::hwpnp::DeviceID &, btos_api::hwpnp::IDevice *parent, size_t index) = 0;
	
	virtual const char *GetDescription() = 0;
	
	virtual void DestroyDevice(btos_api::hwpnp::IDevice *dev) = 0;
	
	virtual uint32_t GetPriority(){
		return priority;
	}
};

class ATADriver : public DriverTemplate<void, void, btos_api::hwpnp::DriverPriority::Generic>{
public:
	btos_api::hwpnp::DeviceID GetDeviceID(){
		return PCATADeviceID;
	}
	
	btos_api::hwpnp::IDevice *CreateDevice(const btos_api::hwpnp::DeviceID &, btos_api::hwpnp::IDevice *, size_t ){
		return new ATABusDevice();
	}
	
	void DestroyDevice(btos_api::hwpnp::IDevice *dev){
		delete (ATABusDevice*)dev;
	}
	
	const char *GetDescription(){
		return "ATA storage bus driver";
	}
};

static ATADriver ataDriver;

btos_api::hwpnp::IDriver *GetATADriver(){
	return &ataDriver;
}

class ATAHDDDriver : public DriverTemplate<ATAHDDDevice, btos_api::hwpnp::IATABus, btos_api::hwpnp::DriverPriority::Generic>{
public:
	btos_api::hwpnp::DeviceID GetDeviceID(){
		return HDDDeviceID;
	}

	const char *GetDescription(){
		return "ATA fixed disk driver";
	}
};

static ATAHDDDriver ataHDDDriver;

btos_api::hwpnp::IDriver *GetATAHDDDriver(){
	return &ataHDDDriver;
}

class MBRVolumeDriver : public DriverTemplate<void, void, btos_api::hwpnp::DriverPriority::Generic>{
public:
	btos_api::hwpnp::DeviceID GetDeviceID(){
		return VolumeDeviceID;
	}

	const char *GetDescription(){
		return "MBR volume driver";
	}
	
	btos_api::hwpnp::IDevice *CreateDevice(const btos_api::hwpnp::DeviceID &, btos_api::hwpnp::IDevice *parent, size_t){
		auto ret = new MBRVolume((btos_api::hwpnp::IBlockDevice*)parent);
		if(!ret->IsOK()){
			delete ret;
			ret = nullptr;
		}
		return ret;
	}
	
	void DestroyDevice(btos_api::hwpnp::IDevice *dev){
		delete (MBRVolume*)dev;
	}
};

static MBRVolumeDriver mbrVolumeDriver;

btos_api::hwpnp::IDriver *GetMBRVolumeDriver(){
	return &mbrVolumeDriver;
}

class PartitionDriver : public DriverTemplate<Partition, btos_api::hwpnp::IVolume, btos_api::hwpnp::DriverPriority::Generic>{
public:
	btos_api::hwpnp::DeviceID GetDeviceID(){
		return PartitionDeviceID;
	}

	const char *GetDescription(){
		return "Disk partition driver";
	}
};

static PartitionDriver partitionDriver;

btos_api::hwpnp::IDriver *GetPartitionDriver(){
	return &partitionDriver;
}

class ATAPIDriver : public DriverTemplate<ATAPIDevice, btos_api::hwpnp::IATABus, btos_api::hwpnp::DriverPriority::Generic>{
public:
	btos_api::hwpnp::DeviceID GetDeviceID(){
		return ATAPIDeviceID;
	}

	const char *GetDescription(){
		return "ATAPI optical drive driver";
	}
};

static ATAPIDriver atapiDriver;

btos_api::hwpnp::IDriver *GetATAPIDriver(){
	return &atapiDriver;
}

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
	pnp_register_driver(&ataDriver);
	pnp_register_driver(&ataHDDDriver);
	pnp_register_driver(&mbrVolumeDriver);
	pnp_register_driver(&partitionDriver);
	pnp_register_driver(&atapiDriver);
	pnp_rescan_devices();
	return 0;
}