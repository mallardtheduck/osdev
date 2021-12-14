#include <module/module.inc>
#include <dev/hwpnp.hpp>
#include <dev/hwpnp/timerdevice.hpp>

static const btos_api::hwpnp::DeviceID PCRTCDeviceID = {
		btos_api::hwpnp::PNPBUS::PCBUS,
		0, 0, 0, 0, 1
	};

static const btos_api::hwpnp::DeviceID PCATADeviceID = {
		btos_api::hwpnp::PNPBUS::PCBUS,
		0, 0, 0, 0, 2
};

static const btos_api::hwpnp::DeviceID PCPS2DeviceID = {
		btos_api::hwpnp::PNPBUS::PCBUS,
		0, 0, 0, 0, 3
};

static const btos_api::hwpnp::DeviceID PCPCIDeviceID = {
		btos_api::hwpnp::PNPBUS::PCBUS,
		0, 0, 0, 0, 4
};

static const btos_api::hwpnp::DeviceID *subDevices[] = {&PCRTCDeviceID, &PCATADeviceID, &PCPS2DeviceID, &PCPCIDeviceID};
static const size_t subDeviceCount = 4;

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
	return btos_api::hwpnp::DeviceID();
}

const char *StdPC::GetDescription(){
	return "Standard PC-compatible computer";
}

size_t StdPC::GetSubDeviceCount(){
	return subDeviceCount;
}

btos_api::hwpnp::DeviceID StdPC::GetSubDevice(size_t idx){
	if(idx < subDeviceCount) return *subDevices[idx];
	else return btos_api::hwpnp::NullDeviceID;
}

btos_api::hwpnp::IDriver *StdPC::GetDriver(){
	return nullptr;
}
	
btos_api::hwpnp::ITimerDevice *StdPC::GetSysTimer(){
	return sysTimer;
}

static StdPC theDevice;

int module_main(char */*params*/){
	sysTimer = (btos_api::hwpnp::ITimerDevice*)API->GetHwPnPManager().ResolveDevice(&theDevice, PCRTCDeviceID, 0);
	if(!sysTimer) panic("(STDPC) Could not resolve timer device!");
	API->GetHwPnPManager().SetRootDevice(&theDevice);
	return 0;
}
