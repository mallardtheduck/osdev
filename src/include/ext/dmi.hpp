#ifndef _DMI_HPP
#define _DMI_HPP

#include <dev/hwpnp.hpp>

struct dm_dev_info{
	btos_api::hwpnp::DeviceID devid;
	void *parent;
	size_t index;
};

ENUM_START(bt_dm_event)
	ENUM_SET(bt_dm_event, DeviceFound, 0),
	ENUM_SET(bt_dm_event, DeviceLost, 1),
ENUM_END
ENUM_TYPE(bt_dm_event);

ENUM_START(bt_dm_function)
	ENUM_SET(bt_dm_function, Register, 0),
	ENUM_SET(bt_dm_function, GetFirstDevice, 1),
	ENUM_SET(bt_dm_function, GetNextDevice, 2),
ENUM_END
ENUM_TYPE(bt_dm_function);

#endif