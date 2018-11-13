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
btos_api::hwpnp::IRootDevice *pnp_get_root_device();

btos_api::hwpnp::IDevice *pnp_get_parent(btos_api::hwpnp::IDevice *dev);
const char *pnp_get_node_name(btos_api::hwpnp::IDeviceNode *node);

#endif