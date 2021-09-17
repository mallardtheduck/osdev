#ifndef MODULE_HWPNP_HPP
#define MODULE_HWPNP_HPP

#include <cstddef>
#include <dev/hwpnp.hpp>
#include <util/noncopyable.hpp>

class IHwPnpManager : private nonmovable{
public:
	using IDriver = btos_api::hwpnp::IDriver;
	using IDevice = btos_api::hwpnp::IDevice;
	using DeviceID = btos_api::hwpnp::DeviceID;
	using IRootDevice = btos_api::hwpnp::IRootDevice;
	using IDeviceNode = btos_api::hwpnp::IDeviceNode;

	virtual void RegisterDriver(IDriver *driver) = 0;
	virtual void UnRegisterDriver(IDriver *driver) = 0;

	virtual void AddDevice(IDevice *parent, const DeviceID &id, size_t index) = 0;
	virtual IDevice *ResolveDevice(IDevice *parent, const DeviceID &id, size_t index) = 0;
	virtual void RescanDevices() = 0;

	virtual void SetRootDevice(IRootDevice *dev) = 0;
	virtual IRootDevice *GetRootDevice() = 0;

	virtual IDevice *GetParent(IDevice *device) = 0;
	virtual const char *GetNodeName(IDeviceNode *node) = 0;

	virtual ~IHwPnpManager() {}
};

#endif