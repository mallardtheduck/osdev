#include "hwpnp_internal.hpp"
#include "../ministl.hpp"
#include <util/asprintf.h>

using namespace btos_api::hwpnp;

vector<IDriver*> *drivers;

struct bad_combo{
	IDevice *parent;
	size_t index;
	IDriver *driver;
};

bool operator==(const bad_combo &a, const bad_combo &b){
	return a.parent == b.parent && a.index == b.index && a.driver == b.driver;
}

bool operator!=(const bad_combo &a, const bad_combo &b){
	return !(a == b);
}

vector<bad_combo> *bad_combos;

static char *pnp_drivers_infofs(){
	char *buffer=nullptr;
	asprintf(&buffer, "# id, devid, description, priority\n");
	for(auto d : *drivers){
		auto devid = d->GetDeviceID();
		reasprintf_append(&buffer, "%p, %s, \"%s\", %i\n", 
			d, deviceIDtoString(devid).c_str(),
			d->GetDescription(),
			d->GetPriority()
		);
	}
	return buffer;
}

void pnp_init_drivers(){
	drivers = new vector<IDriver*>();
	bad_combos = new vector<bad_combo>();
	infofs_register("DRIVERS", &pnp_drivers_infofs);
}

void pnp_register_driver(IDriver *driver){
	drivers->push_back(driver);
	pnp_rescan_devices();
	pnp_enum_devices();
}

void pnp_unregister_driver(IDriver *driver){
	auto i = drivers->find(driver);
	if(i != drivers->npos) drivers->erase(i);
}

bool DeviceIDMatch(const DeviceID &a, const DeviceID &b){
	if(a.Bus != b.Bus) return false;
	if(a.VendorID != 0 && a.VendorID != b.VendorID) return false;
	if(a.DeviceID != 0 && a.DeviceID != b.DeviceID) return false;
	if(a.Revision != 0 && a.Revision != b.Revision) return false;
	if(a.ExtraID != 0 && a.ExtraID != b.ExtraID) return false;
	if(a.Class != 0 && a.Class != b.Class) return false;
	return true;
}

IDevice *pnp_create_device(IDevice *parent, size_t idx, DeviceID id){
	vector<IDriver*> compatible_drivers;
	for(auto d : *drivers){
		if(bad_combos->find({parent, idx, d}) != bad_combos->npos) continue;
		auto devid = d->GetDeviceID();
		if(DeviceIDMatch(devid, id) && d->IsCompatible(id)){
			compatible_drivers.push_back(d);
		}
	}
	while(!compatible_drivers.empty()){
		uint32_t priority = 0;
		IDriver *drv = nullptr;
		size_t didx = 0;
		for(size_t i = 0; i < compatible_drivers.size(); ++i){
			auto d = compatible_drivers[i];
			auto p = d->GetPriority();
			if(p > priority || !drv){
				drv = d;
				priority = p;
				didx = i;
			}
		}
		auto devid = drv->GetDeviceID();
		dbgpf("PNP: Using driver: %p for device: %s\n", 
			drv, deviceIDtoString(devid).c_str()
		);
		auto ret = drv->CreateDevice(id, parent, idx);
		if(ret){
			dbgpf("PNP: Sucessfully created device %p\n", ret);
			auto node = ret->GetDeviceNode();
			if(node) pnp_node_add(node);
			return ret;
		}else{
			dbgout("PNP: Device creation failed!\n");
			bad_combos->push_back({parent, idx, drv});
			compatible_drivers.erase(didx);
		}
	}
	return nullptr;
}