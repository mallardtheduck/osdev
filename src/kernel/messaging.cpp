#include "kernel.hpp"
#include "ministl.hpp"

static vector<msg_header> *msg_q;
static uint64_t id_counter=0;

void msg_init(){
    dbgout("MSG: Init messaging...\n");
    msg_q=new vector<msg_header>();
}

uint64_t msg_send(msg_header &msg){
    msg.id=++id_counter;
    msg_q->push_back(msg);
    return msg.id;
}

bool msg_recv(msg_header &msg, pid_t pid){
    for(size_t i=0; i<msg_q->size(); ++i){
        if((*msg_q)[i].to==pid){
            msg=(*msg_q)[i];
            return true;
        }
    }
    return false;
}

void msg_getcontent(msg_header &msg, void *buffer, size_t buffersize){
    memcpy(buffer, msg.content, buffersize>msg.length?msg.length:buffersize);
}

void msg_acknowledge(msg_header &msg){
    for(size_t i=0; i<msg_q->size(); ++i) {
        if((*msg_q)[i].id==msg.id){
            msg_q->erase(i);
            return;
        }
    }
}
