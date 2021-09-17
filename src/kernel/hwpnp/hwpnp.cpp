#include "hwpnp_internal.hpp"

using namespace btos_api::hwpnp;

void hwpnp_init(){
	dbgout("PNP: Init.");
	pnp_init_drivers();
	pnp_init_devices();
	pnp_dmi_init();
	pnp_init_class();
}

string uint64ToString(uint64_t i){
	char buf[17] = {0};
	sprintf(buf, "%llx", i);
	return buf;
}

string deviceIDtoString(const DeviceID &id){
	return uint64ToString(id.Bus) + ":"
		+ uint64ToString(id.VendorID) + ":"
		+ uint64ToString(id.DeviceID) + ":"
		+ uint64ToString(id.Revision) + ":"
		+ uint64ToString(id.ExtraID) + ":"
		+ uint64ToString(id.Class);
}