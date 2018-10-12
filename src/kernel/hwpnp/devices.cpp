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

void pnp_init_devices(){
	known_devices = new vector<KnownDevice>();
}

void pnp_add_device(IDevice *parent, const DeviceID &id, size_t idx){
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

void pnp_set_root_device(IRootDevice *dev){
	if(!rootDev) rootDev = dev;
}
