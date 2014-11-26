#include "process.hpp"

struct msg_header{
    uint64_t id;
    uint16_t source;
    uint64_t from, to;
    uint32_t type;
    size_t length;
    void *content;
};

void msg_init();

uint64_t msg_send(const msg_header &msg, pid_t pid);
void msg_recv(msg_header &msg);
void msg_getcontent(msg_header &msg, void *buffer, size_t buffersize);
void msg_acknowledge(msg_header &msg);