#ifndef _PERMISSIONS_H
#define _PERMISSIONS_H

#include <util/bt_enum.h>

NS_BEGIN(btos_api)
NS_BEGIN(perms)

ENUM_START(bt_kernel_perm)
    ENUM_SET(bt_kernel_perm, SuperPerm, 0),
    ENUM_SET(bt_kernel_perm, SwitchUID, 1),
    ENUM_SET(bt_kernel_perm, LoadModule, 2),
    ENUM_SET(bt_kernel_perm, KillAll, 3),
    ENUM_SET(bt_kernel_perm, SHMAnyUser, 4),
    ENUM_SET(bt_kernel_perm, MountFS, 5),
    ENUM_SET(bt_kernel_perm, UnMountFS, 6),
    ENUM_SET(bt_kernel_perm, FullFSWrite, 7),
    ENUM_SET(bt_kernel_perm, FullFSRead, 8),
    ENUM_SET(bt_kernel_perm, FullFSSee, 9),
    ENUM_SET(bt_kernel_perm, SeeAllProcs, 10),
    ENUM_SET(bt_kernel_perm, MessageToAny, 11),
    ENUM_SET(bt_kernel_perm, MessageFromAny, 12),
    ENUM_SET(bt_kernel_perm, QueryAnyExtension, 13),
    ENUM_SET(bt_kernel_perm, SeePermissions, 14),
ENUM_END
ENUM_TYPE(bt_kernel_perm);

NS_END
NS_END

#endif