#include "hwpnp_internal.hpp"

using namespace btos_api::hwpnp;

void hwpnp_init(){
	dbgout("PNP: Init.");
	pnp_init_drivers();
	pnp_init_devices();
}

string uint64ToString(uint64_t i){
	char buf[17] = {0};
	if(i < 0x10) sprintf(buf, "0%x", Lower(i));
	else if(i < 0x100000000) sprintf(buf, "%x", Lower(i));
	else sprintf(buf, "%x%x", Upper(i), Lower(i));
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