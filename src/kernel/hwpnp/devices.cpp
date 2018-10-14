#include "hwpnp_internal.hpp"
#include "../ministl.hpp"

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

vector<KnownDevice> *known_devices;

static char *pnp_devices_infofs(){
	char *buffer=(char*)malloc(4096);
	memset(buffer, 0, 4096);
	sprintf(buffer, "# id, parent, index, devid, type, description, driver\n");
	sprintf(&buffer[strlen(buffer)], "%p, %p, %i, %x%x:%x%x:%x%x:%x%x:%x%x:%x%x, %i, \"%s\", %p\n",
			rootDev, nullptr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			rootDev->GetType(),
			rootDev->GetDescription(),
			rootDev->GetDriver()
		);
	for(auto d : *known_devices){
		auto devid = d.id;
		sprintf(&buffer[strlen(buffer)], "%p, %p, %i, %x%x:%x%x:%x%x:%x%x:%x%x:%x%x, %i, \"%s\", %p\n",
			d.device, d.parent, (int)d.index,
			Upper(devid.Bus), Lower(devid.Bus), 
			Upper(devid.VendorID), Lower(devid.VendorID), 
			Upper(devid.DeviceID), Lower(devid.DeviceID), 
			Upper(devid.Revision), Lower(devid.Revision), 
			Upper(devid.ExtraID), Lower(devid.ExtraID), 
			Upper(devid.Class), Lower(devid.Class),
			(d.device ? d.device->GetType() : -1),
			(d.device ? d.device->GetDescription() : "Unknown device"),
			(d.device ? d.device->GetDriver() : nullptr)
		);
	}
	return buffer;
}

void pnp_init_devices(){
	known_devices = new vector<KnownDevice>();
	infofs_register("PNPDEVICES", &pnp_devices_infofs);
}

void pnp_add_device(IDevice *parent, const DeviceID &id, size_t idx){
	dbgpf("PNP: Adding device %p, %i, %x%x:%x%x:%x%x:%x%x:%x%x:%x%x\n",
		parent, (int)idx,
		Upper(id.Bus), Lower(id.Bus), 
		Upper(id.VendorID), Lower(id.VendorID), 
		Upper(id.DeviceID), Lower(id.DeviceID), 
		Upper(id.Revision), Lower(id.Revision), 
		Upper(id.ExtraID), Lower(id.ExtraID), 
		Upper(id.Class), Lower(id.Class)
	);
	for(auto d : *known_devices){
		if(d.parent == parent && d.index == idx) return;
	}
	auto dev = pnp_create_device(parent, idx, id);
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
	for(auto d : *known_devices){
		if(!d.device) d.device = pnp_create_device(d.parent, d.index, d.id);
	}
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
	pnp_enum_subdevices(rootDev);
}

void pnp_set_root_device(IRootDevice *dev){
	if(!rootDev) rootDev = dev;
	pnp_enum_devices();
}
