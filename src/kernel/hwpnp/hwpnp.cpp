#include "hwpnp_internal.hpp"

void hwpnp_init(){
	dbgout("PNP: Init.");
	pnp_init_drivers();
	pnp_init_devices();
}