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
	return "ATA storage bus driver";
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

btos_api::hwpnp::IDevice *ATAHDDDriver::CreateDevice(const btos_api::hwpnp::DeviceID &, btos_api::hwpnp::IDevice *bus, size_t index){
	return new ATAHDDDevice((btos_api::hwpnp::IATABus*)bus, index);
}

const char *ATAHDDDriver::GetDescription(){
	return "ATA fixed disk driver";
}

void ATAHDDDriver::DestroyDevice(btos_api::hwpnp::IDevice *){
}

static ATAHDDDriver ataHDDDriver;

btos_api::hwpnp::IDriver *GetATAHDDDriver(){
	return &ataHDDDriver;
}

class MBRVolumeDriver : public btos_api::hwpnp::IDriver{
	btos_api::hwpnp::DeviceID GetDeviceID();
	bool IsCompatible(const btos_api::hwpnp::DeviceID &dev);
	btos_api::hwpnp::IDevice *CreateDevice(const btos_api::hwpnp::DeviceID &dev, btos_api::hwpnp::IDevice *parent, size_t index);
	const char *GetDescription();
	void DestroyDevice(btos_api::hwpnp::IDevice *dev);
};

btos_api::hwpnp::DeviceID MBRVolumeDriver::GetDeviceID(){
	return VolumeDeviceID;
}

bool MBRVolumeDriver::IsCompatible(const btos_api::hwpnp::DeviceID &dev){
	return
    dev.Bus == VolumeDeviceID.Bus &&
	dev.VendorID == VolumeDeviceID.VendorID &&
	dev.DeviceID == VolumeDeviceID.DeviceID &&
	dev.Revision == VolumeDeviceID.Revision &&
	dev.ExtraID == VolumeDeviceID.ExtraID &&
	dev.Class == VolumeDeviceID.Class;
}

btos_api::hwpnp::IDevice *MBRVolumeDriver::CreateDevice(const btos_api::hwpnp::DeviceID &, btos_api::hwpnp::IDevice *parent, size_t){
	return new MBRVolume((btos_api::hwpnp::IBlockDevice*)parent);
}

const char *MBRVolumeDriver::GetDescription(){
	return "MBR volume driver";
}

void MBRVolumeDriver::DestroyDevice(btos_api::hwpnp::IDevice *){
}

static MBRVolumeDriver mbrVolumeDriver;

btos_api::hwpnp::IDriver *GetMBRVolumeDriver(){
	return &mbrVolumeDriver;
}

class PartitionDriver : public btos_api::hwpnp::IDriver{
	btos_api::hwpnp::DeviceID GetDeviceID();
	bool IsCompatible(const btos_api::hwpnp::DeviceID &dev);
	btos_api::hwpnp::IDevice *CreateDevice(const btos_api::hwpnp::DeviceID &dev, btos_api::hwpnp::IDevice *parent, size_t index);
	const char *GetDescription();
	void DestroyDevice(btos_api::hwpnp::IDevice *dev);
};

btos_api::hwpnp::DeviceID PartitionDriver::GetDeviceID(){
	return PartitionDeviceID;
}

bool PartitionDriver::IsCompatible(const btos_api::hwpnp::DeviceID &dev){
	return
    dev.Bus == PartitionDeviceID.Bus &&
	dev.VendorID == PartitionDeviceID.VendorID &&
	dev.DeviceID == PartitionDeviceID.DeviceID &&
	dev.Revision == PartitionDeviceID.Revision &&
	dev.ExtraID == PartitionDeviceID.ExtraID &&
	dev.Class == PartitionDeviceID.Class;
}

btos_api::hwpnp::IDevice *PartitionDriver::CreateDevice(const btos_api::hwpnp::DeviceID &, btos_api::hwpnp::IDevice *parent, size_t index){
	return new Partition((btos_api::hwpnp::IVolume*)parent, index);
}

const char *PartitionDriver::GetDescription(){
	return "Disk partition driver";
}

void PartitionDriver::DestroyDevice(btos_api::hwpnp::IDevice *){
}

static PartitionDriver partitionDriver;

btos_api::hwpnp::IDriver *GetPartitionDriver(){
	return &partitionDriver;
}

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
	pnp_register_driver(&ataDriver);
	pnp_register_driver(&ataHDDDriver);
	pnp_register_driver(&mbrVolumeDriver);
	pnp_register_driver(&partitionDriver);
	pnp_rescan_devices();
	return 0;
}