#ifndef _KERNEL_PERMS_H
#define _KERNEL_PERMS_H

#include "kernel.hpp"
#include <btos/permissions.h>

namespace kperm = btos_api::perms::bt_kernel_perm;

bool has_perm(uint16_t ext, uint8_t p, bt_pid_t pid = CurrentProcess().ID());
uint64_t set_perms(uint16_t ext, uint64_t pmask, bt_pid_t pid = CurrentProcess().ID());
bool switch_uid(uint64_t uid, bt_pid_t pid = CurrentProcess().ID());

#endif