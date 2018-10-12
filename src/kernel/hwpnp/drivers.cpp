#include "hwpnp_internal.hpp"
#include "../ministl.hpp"

using namespace btos_api::hwpnp;

vector<IDriver*> *drivers;

static char *pnp_drivers_infofs(){
	char *buffer=(char*)malloc(4096);
	memset(buffer, 0, 4096);
	sprintf(buffer, "# id, devid, description\n");
	for(auto d : *drivers){
		auto devid = d->GetDeviceID();
		sprintf(&buffer[strlen(buffer)], "%p, %x%x:%x%x:%x%x:%x%x:%x%x:%x%x, \"%s\"\n", 
			d,
			Upper(devid.Bus), Lower(devid.Bus), 
			Upper(devid.VendorID), Lower(devid.VendorID), 
			Upper(devid.DeviceID), Lower(devid.DeviceID), 
			Upper(devid.Revision), Lower(devid.Revision), 
			Upper(devid.ExtraID), Lower(devid.ExtraID), 
			Upper(devid.Class), Lower(devid.Class),
			d->GetDescription()
		);
	}
	return buffer;
}

void pnp_init_drivers(){
	drivers = new vector<IDriver*>();
	infofs_register("DRIVERS", &pnp_drivers_infofs);
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