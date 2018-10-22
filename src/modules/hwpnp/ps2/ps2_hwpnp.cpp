#include "ps2.hpp"

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

class PS2Driver : public DriverTemplate<void, void, btos_api::hwpnp::DriverPriority::Generic>{
public:
	btos_api::hwpnp::DeviceID GetDeviceID(){
		return PCPS2DeviceID;
	}
	
	btos_api::hwpnp::IDevice *CreateDevice(const btos_api::hwpnp::DeviceID &, btos_api::hwpnp::IDevice *, size_t ){
		return new PS2BusDevice();
	}
	
	void DestroyDevice(btos_api::hwpnp::IDevice *dev){
		delete (PS2BusDevice*)dev;
	}
	
	const char *GetDescription(){
		return "8042-style PS/2 input device bus driver";
	}
};

static PS2Driver ps2Driver;

btos_api::hwpnp::IDriver *GetPS2Driver(){
	return &ps2Driver;
}

class PS2KeyboardDriver : public DriverTemplate<PS2KeyboardDevice, btos_api::hwpnp::IPS2Bus, btos_api::hwpnp::DriverPriority::Generic>{
public:
	btos_api::hwpnp::DeviceID GetDeviceID(){
		return PS2KeyboardDeviceID;
	}

	const char *GetDescription(){
		return "PS/2 keyboard driver";
	}
};

static PS2KeyboardDriver ps2KeyboardDriver;

btos_api::hwpnp::IDriver *GetPS2KeyboardDriver(){
	return &ps2KeyboardDriver;
}

class PS2MouseDriver : public DriverTemplate<PS2MouseDevice, btos_api::hwpnp::IPS2Bus, btos_api::hwpnp::DriverPriority::Generic>{
public:
	btos_api::hwpnp::DeviceID GetDeviceID(){
		return PS2MouseDeviceID;
	}

	const char *GetDescription(){
		return "PS/2 mouse driver";
	}
};

static PS2MouseDriver ps2MouseDriver;

btos_api::hwpnp::IDriver *GetPS2MouseDriver(){
	return &ps2MouseDriver;
}
