#ifndef _HWPNP_INTERNAL_HPP
#define _HWPNP_INTERNAL_HPP

#include "../kernel.hpp"

btos_api::hwpnp::IDevice *pnp_create_device(btos_api::hwpnp::IDevice *parent, size_t idx, btos_api::hwpnp::DeviceID id);

void pnp_init_drivers();
void pnp_init_devices();

#endif