#ifndef _MESSAGING_HPP
#define _MESSAGING_HPP

#include "bt_msg.h"
#include "process.hpp"

void msg_init();

uint64_t msg_send(btos_api::bt_msg_header &msg);
void msg_recv(btos_api::bt_msg_header &msg);
void msg_getcontent(btos_api::bt_msg_header &msg, void *buffer, size_t buffersize);
void msg_acknowledge(btos_api::bt_msg_header &msg);

#endif