#include "../kernel.hpp"
#include <dev/hwpnp.hpp>
#include "../ministl.hpp"

using namespace btos_api::hwpnp;

vector<IDriver*> *drivers;

void pnp_init_drivers(){
	drivers = new vector<IDriver*>();
}

void pnp_register_driver(IDriver *driver){
	drivers->push_back(driver);
}

void pnp_unregister_driver(IDriver *driver){
	auto i = drivers->find(driver);
	if(i != drivers->npos) drivers->erase(i);
}