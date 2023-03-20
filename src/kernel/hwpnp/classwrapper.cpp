#include "../kernel.hpp"
#include "hwpnp_internal.hpp"

class HwPnpManager : public IHwPnpManager{
public:
	using IDriver = btos_api::hwpnp::IDriver;
	using IDevice = btos_api::hwpnp::IDevice;
	using DeviceID = btos_api::hwpnp::DeviceID;
	using IRootDevice = btos_api::hwpnp::IRootDevice;
	using IDeviceNode = btos_api::hwpnp::IDeviceNode;

	void RegisterDriver(IDriver *driver) override{
		pnp_register_driver(driver);
	};

	void UnRegisterDriver(IDriver *driver) override{
		pnp_unregister_driver(driver);
	}

	void AddDevice(IDevice *parent, const DeviceID &id, size_t index) override{
		pnp_add_device(parent, id, index);
	}

	IDevice *ResolveDevice(IDevice *parent, const DeviceID &id, size_t index) override{
		return pnp_resolve_device(parent, id, index);
	}

	void RescanDevices() override{
		pnp_rescan_devices();
	}

	void SetRootDevice(IRootDevice *dev) override{
		pnp_set_root_device(dev);
	}
	
	IRootDevice *GetRootDevice() override{
		return pnp_get_root_device();
	}

	IDevice *GetParent(IDevice *device) override{
		return pnp_get_parent(device);
	}

	const char *GetNodeName(IDeviceNode *node) override{
		return pnp_get_node_name(node);
	}
};

static ManualStaticAlloc<HwPnpManager> theHwPnpManager;

void pnp_init_class(){
	theHwPnpManager.Init();
}

IHwPnpManager &GetHwPnpManager(){
	return *theHwPnpManager;
}