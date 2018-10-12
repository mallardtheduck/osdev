#include <btos_module.h>
#include <dev/hwpnp/timerdevice.hpp>
#include "rtc.hpp"

USE_SYSCALL_TABLE;
USE_DEBUG_PRINTF;
USE_PURE_VIRTUAL;
USE_STATIC_INIT;

static bool inited = false;

const btos_api::hwpnp::DeviceID PCRTCDeviceID = {
		btos_api::hwpnp::PNPBUS::PCBUS,
		0, 0, 0, 0, 1
	};

class PCRTC : public btos_api::hwpnp::ITimerDevice{
public:
	btos_api::hwpnp::DeviceID GetID();
	const char *GetDescription();
	size_t GetSubDeviceCount();
	btos_api::hwpnp::DeviceID GetSubDevice(size_t);
	btos_api::hwpnp::IDriver *GetDriver();

	uint64_t GetTime();
	uint64_t GetMillis();
	void SetTime(uint64_t time);
};

static PCRTC theDevice;

btos_api::hwpnp::DeviceID PCRTC::GetID(){
	return PCRTCDeviceID;
}

const char *PCRTC::GetDescription(){
	return "Standard PC RTC Timer";
}

size_t PCRTC::GetSubDeviceCount(){
	return 0;
}


btos_api::hwpnp::DeviceID PCRTC::GetSubDevice(size_t){
	return btos_api::hwpnp::NullDeviceID;
}

uint64_t PCRTC::GetTime(){
	return rtc_get_time();
}

uint64_t PCRTC::GetMillis(){
	return get_msecs();
}

void PCRTC::SetTime(uint64_t){
}

class PCRTCDriver : public btos_api::hwpnp::IDriver{
public:
	btos_api::hwpnp::DeviceID GetDeviceID();
	bool IsCompatible(const btos_api::hwpnp::DeviceID &dev);
	const char *GetDescription();
	btos_api::hwpnp::IDevice *CreateDevice(const btos_api::hwpnp::DeviceID &dev, btos_api::hwpnp::IDevice *parent, size_t index);
	void DestroyDevice(btos_api::hwpnp::IDevice *dev);
};

static PCRTCDriver theDriver;

btos_api::hwpnp::IDriver *PCRTC::GetDriver(){
	return &theDriver;
}

btos_api::hwpnp::DeviceID PCRTCDriver::GetDeviceID(){
	return PCRTCDeviceID;
}

bool PCRTCDriver::IsCompatible(const btos_api::hwpnp::DeviceID &dev){
	return
    dev.Bus == PCRTCDeviceID.Bus &&
	dev.VendorID == PCRTCDeviceID.VendorID &&
	dev.DeviceID == PCRTCDeviceID.DeviceID &&
	dev.Revision == PCRTCDeviceID.Revision &&
	dev.ExtraID == PCRTCDeviceID.ExtraID &&
	dev.Class == PCRTCDeviceID.Class;
}

const char *PCRTCDriver::GetDescription(){
	return "PC-style RTC driver";
}

btos_api::hwpnp::IDevice *PCRTCDriver::CreateDevice(const btos_api::hwpnp::DeviceID&, btos_api::hwpnp::IDevice*, size_t){
	if(!inited){
		init_rtc();
		inited = true;
	}
	return &theDevice;
}

void PCRTCDriver::DestroyDevice(btos_api::hwpnp::IDevice *){
	/* Do nothing */
}

extern "C" int module_main(syscall_table *systbl, char */*params*/){
	SYSCALL_TABLE=systbl;
	pnp_register_driver(&theDriver);
	return 0;
}