#ifndef _KERNEL_PERMS_H
#define _KERNEL_PERMS_H

#include "kernel.hpp"
#include <btos/permissions.h>

namespace kperm = btos_api::perms::bt_kernel_perm;

bool has_perm(uint16_t ext, uint8_t p, pid_t pid = proc_current_pid);
uint64_t set_perms(uint16_t ext, uint64_t pmask, pid_t pid = proc_current_pid);
bool switch_uid(uint64_t uid, pid_t pid = proc_current_pid);

#endif