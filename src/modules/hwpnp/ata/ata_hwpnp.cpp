#include <btos_module.h>
#include <dev/hwpnp.hpp>
#include "ata.hpp"

USE_SYSCALL_TABLE;
USE_DEBUG_PRINTF;
USE_PURE_VIRTUAL;
USE_STATIC_INIT;

class ATADriver : public btos_api::hwpnp::IDriver{
public:
	btos_api::hwpnp::DeviceID GetDeviceID();
	bool IsCompatible(const btos_api::hwpnp::DeviceID &dev);
	btos_api::hwpnp::IDevice *CreateDevice(const btos_api::hwpnp::DeviceID &dev, btos_api::hwpnp::IDevice *parent, size_t index);
	const char *GetDescription();
	void DestroyDevice(btos_api::hwpnp::IDevice *dev);
};

btos_api::hwpnp::DeviceID ATADriver::GetDeviceID(){
	return PCATADeviceID;
}

bool ATADriver::IsCompatible(const btos_api::hwpnp::DeviceID &dev){
	return
    dev.Bus == PCATADeviceID.Bus &&
	dev.VendorID == PCATADeviceID.VendorID &&
	dev.DeviceID == PCATADeviceID.DeviceID &&
	dev.Revision == PCATADeviceID.Revision &&
	dev.ExtraID == PCATADeviceID.ExtraID &&
	dev.Class == PCATADeviceID.Class;
}

btos_api::hwpnp::IDevice *ATADriver::CreateDevice(const btos_api::hwpnp::DeviceID &, btos_api::hwpnp::IDevice *, size_t){
	return new ATABusDevice();
}

const char *ATADriver::GetDescription(){
	return "ATA Storage Bus Driver";
}

void ATADriver::DestroyDevice(btos_api::hwpnp::IDevice *dev){
	delete dev;
}

static ATADriver ataDriver;

btos_api::hwpnp::IDriver *GetATADriver(){
	return &ataDriver;
}

class ATAHDDDriver : public btos_api::hwpnp::IDriver{
	btos_api::hwpnp::DeviceID GetDeviceID();
	bool IsCompatible(const btos_api::hwpnp::DeviceID &dev);
	btos_api::hwpnp::IDevice *CreateDevice(const btos_api::hwpnp::DeviceID &dev, btos_api::hwpnp::IDevice *parent, size_t index);
	const char *GetDescription();
	void DestroyDevice(btos_api::hwpnp::IDevice *dev);
};

btos_api::hwpnp::DeviceID ATAHDDDriver::GetDeviceID(){
	return HDDDeviceID;
}

bool ATAHDDDriver::IsCompatible(const btos_api::hwpnp::DeviceID &dev){
	return
    dev.Bus == HDDDeviceID.Bus &&
	dev.VendorID == HDDDeviceID.VendorID &&
	dev.DeviceID == HDDDeviceID.DeviceID &&
	dev.Revision == HDDDeviceID.Revision &&
	dev.ExtraID == HDDDeviceID.ExtraID &&
	dev.Class == HDDDeviceID.Class;
}

btos_api::hwpnp::IDevice *ATAHDDDriver::CreateDevice(const btos_api::hwpnp::DeviceID &, btos_api::hwpnp::IDevice *, size_t){
	return nullptr;
}

const char *ATAHDDDriver::GetDescription(){
	return "ATA Hard Drive driver";
}

void ATAHDDDriver::DestroyDevice(btos_api::hwpnp::IDevice *){
}

static ATAHDDDriver ataHDDDriver;

btos_api::hwpnp::IDriver *GetATAHDDDriver(){
	return &ataHDDDriver;
}

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
	pnp_register_driver(&ataDriver);
	pnp_register_driver(&ataHDDDriver);
	return 0;
}