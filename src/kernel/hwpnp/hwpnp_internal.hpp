#ifndef _HWPNP_INTERNAL_HPP
#define _HWPNP_INTERNAL_HPP

#include "../kernel.hpp"
#include <ext/dmi.hpp>

btos_api::hwpnp::IDevice *pnp_create_device(btos_api::hwpnp::IDevice *parent, size_t idx, btos_api::hwpnp::DeviceID id);

void pnp_init_drivers();
void pnp_init_devices();

inline static uint32_t Upper(uint64_t i){
	return (uint32_t)(i >> 32);
}

inline static uint32_t Lower(uint64_t i){
	return (uint32_t)i;
}

void pnp_node_add(btos_api::hwpnp::IDeviceNode *node);
void pnp_enum_devices();

string deviceIDtoString(const btos_api::hwpnp::DeviceID &id);

void pnp_dmi_init();
void pnp_dmi_notify_device_found(const btos_api::hwpnp::DeviceID &dev);

dm_dev_info get_first_device();
dm_dev_info get_next_device(const dm_dev_info &cur);

#endif