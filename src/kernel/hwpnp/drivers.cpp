#include "hwpnp_internal.hpp"
#include "../ministl.hpp"

using namespace btos_api::hwpnp;

vector<IDriver*> *drivers;

void pnp_init_drivers(){
	drivers = new vector<IDriver*>();
}

void pnp_register_driver(IDriver *driver){
	drivers->push_back(driver);
	pnp_rescan_devices();
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
	for(auto d : *drivers){
		if(DeviceIDMatch(d->GetDeviceID(), id) && d->IsCompatible(id)){
			return d->CreateDevice(id, parent, idx);
		}
	}
	return nullptr;
}