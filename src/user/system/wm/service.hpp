#ifndef __SERVICE_HPP
#define __SERVICE_HPP

#include <btos.h>

extern btos_api::bt_handle stdin_handle;

void Service(btos_api::bt_pid_t root);

#endif