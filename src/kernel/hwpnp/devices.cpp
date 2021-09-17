#include "hwpnp_internal.hpp"
#include "../utils/ministl.hpp"
#include <util/asprintf.h>
#include "../locks.hpp"
#include "../rtc/rtc.hpp"

using namespace btos_api::hwpnp;

IRootDevice *rootDev = nullptr;

struct KnownDevice{
	IDevice *parent = nullptr;
	size_t index = 0;
	DeviceID id;
	IDevice *device = nullptr;
	
	KnownDevice() {}
	KnownDevice(IDevice *p, size_t idx, DeviceID i, IDevice *d) : 
		parent(p), index(idx), id(i), device(d) {}
};

static vector<KnownDevice> *known_devices;
static map<IDeviceNode*, string> *device_nodes;

ILock *rescan_lock;

static char *pnp_devices_infofs(){
	char *buffer=nullptr;
	asprintf(&buffer, "# id, parent, index, devid, type, description, driver, node\n");
	reasprintf_append(&buffer, "%p, %p, %i, %s, %x, \"%s\", %p, %s\n",
			rootDev, nullptr, 0, deviceIDtoString(rootDev->GetID()).c_str(),
			rootDev->GetType(),
			rootDev->GetDescription(),
			rootDev->GetDriver(),
			"-"
		);
	for(auto d : *known_devices){
		auto devid = d.id;
		const char *nodeName = "-";
		IDeviceNode *node = nullptr;
		if(d.device && (node = d.device->GetDeviceNode())){
			nodeName = GetHwPnpManager().GetNodeName(node);
		}
		reasprintf_append(&buffer, "%p, %p, %i, %s, %x, \"%s\", %p, %s\n",
			d.device, d.parent, (int)d.index,
			deviceIDtoString(devid).c_str(),
			(d.device ? d.device->GetType() : driver_types::UNKNOWN),
			(d.device ? d.device->GetDescription() : "Unknown device"),
			(d.device ? d.device->GetDriver() : nullptr),
			nodeName
		);
	}
	return buffer;
}

void pnp_init_devices(){
	known_devices = new vector<KnownDevice>();
	device_nodes = new map<IDeviceNode*, string>();
	rescan_lock = NewLock();
	InfoRegister("PNPDEVICES", &pnp_devices_infofs);
}

void pnp_add_device(IDevice *parent, const DeviceID &id, size_t idx){
	for(auto d : *known_devices){
		if(d.parent == parent && d.index == idx) return;
	}
	dbgpf("PNP: Adding device %p, %i, %s\n",
		parent, (int)idx,
		deviceIDtoString(id).c_str()
	);
	auto dev = pnp_create_device(parent, idx, id);
	pnp_dmi_notify_device_found(id);
	known_devices->push_back(KnownDevice(parent, idx, id, dev));
}

IDevice *pnp_resolve_device(IDevice *parent, const DeviceID &id, size_t idx){
	pnp_add_device(parent, id, idx);
	for(auto d : *known_devices){
		if(d.parent == parent && d.index == idx) return d.device;
	}
	return nullptr;
}

void pnp_rescan_devices(){
	if(!rescan_lock->TryTakeExclusive()) return;
	for(auto &d : *known_devices){
		if(!d.device) d.device = pnp_create_device(d.parent, d.index, d.id);
	}
	rescan_lock->Release();
}

void pnp_enum_subdevices(IDevice *dev){
	for(size_t i = 0; i < dev->GetSubDeviceCount(); ++i){
		auto devId = dev->GetSubDevice(i);
		if(devId.Bus != PNPBUS::Null){
			auto sdev = pnp_resolve_device(dev, devId, i);
			if(sdev) pnp_enum_subdevices(sdev);
		}
	}
}
void pnp_enum_devices(){
	if(!rootDev) return;
	size_t count;
	bool repeat = true;
	while(repeat){
		repeat = false;
		count = known_devices->size();
		pnp_enum_subdevices(rootDev);
		if(count != known_devices->size()){
			pnp_rescan_devices();
			repeat = true;
		}
	}
}

void pnp_set_root_device(IRootDevice *dev){
	if(!rootDev) rootDev = dev;
	pnp_enum_devices();
	rtc_configure();
}

btos_api::hwpnp::IRootDevice *pnp_get_root_device(){
	return rootDev;
}

class PnpNodeInstance : public IVisibleDeviceInstance{
private:
	IDeviceNode *node;
	void *handle;
public:
	PnpNodeInstance(IDeviceNode *n, void *h) : node(n), handle(h) {}

	size_t Read(size_t bytes, char *buffer) override{
		return node->Read(handle, bytes, buffer);
	}
	size_t Write(size_t bytes, const char *buffer) override{
		return node->Write(handle, bytes, buffer);
	}

	bt_filesize_t Seek(bt_filesize_t pos, uint32_t flags) override{
		return node->Seek(handle, pos, flags);
	}

	int IOCtl(int fn, size_t bytes, char *buffer) override{
		return node->IOCtl(handle, fn, bytes, buffer);
	}

	int GetType() override{
		return node->GetType();
	}

	const char *GetDescription() override{
		return node->GetDescription();
	}

	bool Close() override{
		return node->Close(handle);
	}
};

class PnpNodeDevice : public IVisibleDevice{
private:
	string name;
	IDeviceNode *node;
public:
	PnpNodeDevice(IDeviceNode *no) : name(no->GetBaseName()), node(no) {}

	IVisibleDeviceInstance *Open() override{
		auto h = node->Open();
		if(h){
			return new PnpNodeInstance(node, h);
		}else{
			return nullptr;
		}
	}

	int GetType() override{
		return node->GetType();
	}

	const char *GetDescription() override{
		return node->GetDescription();
	}
	const char *GetName() override{
		return name.c_str();
	}

	void SetName(const char *n) override{
		name = n;
	}
};

void pnp_node_add(IDeviceNode *node){
	auto nodeDevice = new PnpNodeDevice(node);
	GetVisibleDeviceManager().AddVisibleDevice(nodeDevice);
	auto name = nodeDevice->GetName();
	(*device_nodes)[node] = name;
}

IDevice *pnp_get_parent(IDevice *dev){
	for(auto d : *known_devices){
		if(d.device == dev) return d.parent;
	}
	return nullptr;
}

const char *pnp_get_node_name(IDeviceNode *node){
	for(auto &n : *device_nodes){
		if(n.first == node) return n.second.c_str();
	}
	return "";
}

dm_dev_info get_first_device(){
	if(known_devices->empty()){
		return {NullDeviceID, nullptr, 0};
	}else{
		auto kd = (*known_devices)[0];
		return {kd.id, kd.parent, kd.index};
	}
}

dm_dev_info get_next_device(const dm_dev_info &cur){
	bool ret = false;
	for(const auto &d : *known_devices){
		if(ret) return {d.id, d.parent, d.index};
		else if(d.parent == cur.parent && d.index == cur.index) ret = true;
	}
	return {NullDeviceID, nullptr, 0};
}
