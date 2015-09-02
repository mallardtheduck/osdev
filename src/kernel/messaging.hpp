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
void msg_clear(pid_t pid);
bool msg_recv_reply(btos_api::bt_msg_header &msg, uint64_t msg_id);
btos_api::bt_msg_header msg_recv_reply_block(uint64_t msg_id);

void msg_subscribe(btos_api::bt_kernel_messages::Enum message, pid_t pid=proc_current_pid);
void msg_unsubscribe(btos_api::bt_kernel_messages::Enum, pid_t pid=proc_current_pid);
void msg_send_event(btos_api::bt_kernel_messages::Enum message, void *content, size_t size);

#endif