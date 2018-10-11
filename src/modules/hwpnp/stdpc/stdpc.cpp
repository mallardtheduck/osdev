#include <dev/hwpnp.hpp>
#include <dev/hwpnp/timerdevice.hpp>

USE_SYSCALL_TABLE;
USE_DEBUG_PRINTF;
USE_PURE_VIRTUAL;
USE_STATIC_INIT;

static const btos_api::hwpnp::DeviceID PCRTCDeviceID = {
		btos_api::hwpnp::PNPBUS::PCBUS,
		0, 0, 0, 0, 1
	};

static btos_api::hwpnp::ITimerDevice *sysTimer;

class StdPC : public btos_api::hwpnp::IRootDevice{
public:
	btos_api::hwpnp::DeviceID GetID();
	const char *GetDescription();
	size_t GetSubDeviceCount();
	btos_api::hwpnp::DeviceID GetSubDevice(size_t);
	btos_api::hwpnp::IDriver *GetDriver();
		
	btos_api::hwpnp::ITimerDevice *GetSysTimer();
};


btos_api::hwpnp::DeviceID StdPC::GetID(){
	return btos_api::hwpnp::NullDeviceID;
}

const char *StdPC::GetDescription(){
	return "Standard PC-compatible computer";
}

size_t StdPC::GetSubDeviceCount(){
	return 0;
}

btos_api::hwpnp::DeviceID StdPC::GetSubDevice(size_t){
	return btos_api::hwpnp::NullDeviceID;
}

btos_api::hwpnp::IDriver *StdPC::GetDriver(){
	return nullptr;
}
	
btos_api::hwpnp::ITimerDevice *StdPC::GetSysTimer(){
	return sysTimer;
}

static StdPC theDevice;

extern "C" int module_main(syscall_table *systbl, char */*params*/){
	SYSCALL_TABLE=systbl;
	//sysTimer = pnp_resolve_device(&theDevice, PCRTCDeviceID);
	if(!sysTimer) panic("(STDPC) Could not resolve timer device!");
	//pnp_set_root_device(&theDevice);
	return 0;
}