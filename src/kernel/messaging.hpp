#ifndef _MESSAGING_HPP
#define _MESSAGING_HPP

#include <btos/bt_msg.h>

void msg_init();

uint64_t msg_send(btos_api::bt_msg_header &msg);
bool msg_recv(btos_api::bt_msg_header &msg, bt_pid_t pid=CurrentProcess().ID());
btos_api::bt_msg_header msg_recv_block(bt_pid_t pid=CurrentProcess().ID());
size_t msg_getcontent(btos_api::bt_msg_header &msg, void *buffer, size_t buffersize);
void msg_acknowledge(btos_api::bt_msg_header &msg, bool set_status=true);
void msg_nextmessage(btos_api::bt_msg_header &msg);
void msg_clear(bt_pid_t pid);
bool msg_recv_reply(btos_api::bt_msg_header &msg, uint64_t msg_id);
btos_api::bt_msg_header msg_recv_reply_block(uint64_t msg_id);
btos_api::bt_msg_header msg_recv_filtered(btos_api::bt_msg_filter filter, bt_pid_t pid=CurrentProcess().ID(), bool block=true);
void msg_nextmessage_filtered(btos_api::bt_msg_filter filter, btos_api::bt_msg_header &msg);
bool msg_query_recieved(uint64_t id);
bool msg_is_match(const btos_api::bt_msg_header &msg, const btos_api::bt_msg_filter &filter);

//bt_handle_info msg_create_recv_handle(btos_api::bt_msg_filter filter);
//btos_api::bt_msg_header msg_read_recv_handle(bt_handle_info &h);

void msg_subscribe(btos_api::bt_kernel_messages::Enum message, bt_pid_t pid=CurrentProcess().ID());
void msg_unsubscribe(btos_api::bt_kernel_messages::Enum, bt_pid_t pid=CurrentProcess().ID());
void msg_send_event(btos_api::bt_kernel_messages::Enum message, void *content, size_t size);

#endif