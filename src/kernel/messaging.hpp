#ifndef _MESSAGING_HPP
#define _MESSAGING_HPP

#include "bt_msg.h"
#include "process.hpp"

namespace thread_msg_status{
    enum Enum{
        Normal,
        Waiting,
        Processing,
    };
}

void msg_init();

uint64_t msg_send(btos_api::bt_msg_header &msg);
bool msg_recv(btos_api::bt_msg_header &msg, pid_t pid=proc_current_pid);
btos_api::bt_msg_header msg_recv_block(pid_t pid=proc_current_pid);
size_t msg_getcontent(btos_api::bt_msg_header &msg, void *buffer, size_t buffersize);
void msg_acknowledge(btos_api::bt_msg_header &msg, bool set_status=true);
void msg_nextmessage(btos_api::bt_msg_header &msg);

#endif