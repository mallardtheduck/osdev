#ifndef _HWPNP_PUBLIC_HPP
#define _HWPNP_PUBLIC_HPP

#include <dev/hwpnp.hpp>

void hwpnp_init();

void pnp_register_driver(btos_api::hwpnp::IDriver *driver);
void pnp_unregister_driver(btos_api::hwpnp::IDriver *driver);

void pnp_add_device(btos_api::hwpnp::IDevice *parent, const btos_api::hwpnp::DeviceID &id, size_t idx);
btos_api::hwpnp::IDevice *pnp_resolve_device(btos_api::hwpnp::IDevice *parent, const btos_api::hwpnp::DeviceID &id, size_t idx);
void pnp_rescan_devices();
void pnp_set_root_device(btos_api::hwpnp::IRootDevice *dev);

#endif