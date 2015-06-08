#include "kernel.hpp"
#include "ministl.hpp"
#include "locks.hpp"

using namespace btos_api;

static vector<bt_msg_header> *msg_q;
static uint64_t id_counter=0;
static lock msg_lock;

bool msg_get(uint64_t id, bt_msg_header &msg);

typedef map<pid_t, vector<bt_kernel_messages::Enum> > msg_subscribers_list;
static msg_subscribers_list *msg_subscribers;

void msg_init(){
    dbgout("MSG: Init messaging...\n");
    init_lock(msg_lock);
    msg_q=new vector<bt_msg_header>();
	msg_subscribers=new msg_subscribers_list();
}

uint64_t msg_send(bt_msg_header &msg){
    if(msg.to != 0 && proc_get_status(msg.to) == proc_status::DoesNotExist) return 0;
    if(msg.flags & bt_msg_flags::Reply){
        bt_msg_header prev;
        if(!msg_get(msg.reply_id, prev)) {
            dbgout("MSG: Attempted reply to non-existent message!\n");
            return 0;
        }
        if(prev.to != msg.from || prev.from != msg.to) {
            dbgout("MSG: Reply to/from mismatch!\n");
            dbgpf("Expected from: %i to: %i, got from: %i to: %i\n", (int)prev.to, (int)prev.from, (int)msg.from, (int)msg.to);
            return 0;
        }
        if(prev.replied){
            dbgout("MSG: Second reply to same message!\n");
            return 0;
        }
        {
            hold_lock hl(msg_lock);
            for (size_t i = 0; i < msg_q->size(); ++i) {
                if ((*msg_q)[i].id == prev.id) {
                    (*msg_q)[i].replied = true;
                }
            }
        }
    }
    {
        hold_lock hl(msg_lock, false);
        msg.id = ++id_counter;
        msg.valid = true;
        msg.recieved = msg.replied = false;
        msg_q->push_back(msg);
    }
    dbgpf("MSG: Sent message ID %i.\n", (int)msg.id);
    return msg.id;
}

bool msg_recv(bt_msg_header &msg, pid_t pid){
    hold_lock hl(msg_lock);
    for(size_t i=0; i<msg_q->size(); ++i){
        if((*msg_q)[i].to==pid){
            msg=(*msg_q)[i];
            (*msg_q)[i].recieved = true;
            sch_set_msgstaus(thread_msg_status::Processing);
            return true;
        }
    }
    return false;
}

static bool msg_recv_nolock(bt_msg_header &msg, pid_t pid){
    if(get_lock_owner(msg_lock)) return false;
    for(size_t i=0; i<msg_q->size(); ++i){
        if((*msg_q)[i].to==pid){
            msg=(*msg_q)[i];
            (*msg_q)[i].recieved = true;
            return true;
        }
    }
    return false;
}

struct msg_blockcheck_params{
    bt_msg_header *msg;
    pid_t pid;
};

bool msg_blockcheck(void *p){
    msg_blockcheck_params *params=(msg_blockcheck_params*)p;
    bool ret=msg_recv_nolock(*params->msg, params->pid);
    return ret;
}

bt_msg_header msg_recv_block(pid_t pid){
    bt_msg_header ret;
    if(!msg_recv(ret, pid)){
        sch_set_msgstaus(thread_msg_status::Waiting);
        msg_blockcheck_params params={&ret, pid};
        sch_setblock(&msg_blockcheck, (void*)&params);
    }
    sch_set_msgstaus(thread_msg_status::Processing);
    return ret;
}

bool msg_get(uint64_t id, bt_msg_header &msg){
    hold_lock hl(msg_lock);
    for(size_t i=0; i<msg_q->size(); ++i){
        if((*msg_q)[i].id==id){
            msg=(*msg_q)[i];
            return true;
        }
    }
    return false;
}

size_t msg_getcontent(bt_msg_header &msg, void *buffer, size_t buffersize){
    bt_msg_header r;
    if(!msg_get(msg.id, r)) return 0;
    size_t size=buffersize>r.length?r.length:buffersize;
    memcpy(buffer, r.content, size);
    return size;
}

void msg_acknowledge(bt_msg_header &msg, bool set_status){
    hold_lock hl(msg_lock, false);
    for(size_t i=0; i<msg_q->size(); ++i) {
        bt_msg_header &header=(*msg_q)[i];
        if(header.id==msg.id){
            if(header.flags & bt_msg_flags::UserSpace){
                proc_free_message_buffer(header.to, header.from);
            }else{
                free(header.content);
            }
            msg_q->erase(i);
            if(set_status) sch_set_msgstaus(thread_msg_status::Normal);
            return;
        }
    }
}

void msg_nextmessage(bt_msg_header &msg){
    msg_acknowledge(msg, false);
    msg=msg_recv_block();
}

void msg_clear(pid_t pid){
    hold_lock hl(msg_lock);
    for(size_t i=0; i<msg_q->size(); ++i){
        bt_msg_header &header=(*msg_q)[i];
        if(header.to==pid || (header.from==pid && !header.recieved)){
            msg_acknowledge(header, false);
        }
    }
	if(msg_subscribers->has_key(pid)) msg_subscribers->erase(pid);
}

void msg_subscribe(bt_kernel_messages::Enum message, pid_t pid){
	hold_lock hl(msg_lock);
	if(!msg_subscribers->has_key(pid)){
		(*msg_subscribers)[pid]=vector<bt_kernel_messages::Enum>();
	}
	if((*msg_subscribers)[pid].find(message) == (*msg_subscribers)[pid].npos){
		(*msg_subscribers)[pid].push_back(message);
		dbgpf("MSG: Pid %i subscribed to %i.\n", (int)pid, (int)message);
	}
}

void msg_unsubscribe(bt_kernel_messages::Enum message, pid_t pid){
	hold_lock hl(msg_lock);
	if(!msg_subscribers->has_key(pid)) return;
	if((*msg_subscribers)[pid].find(message) != (*msg_subscribers)[pid].npos){
		(*msg_subscribers)[pid].erase((*msg_subscribers)[pid].find(message));
	}
}

void msg_send_event(bt_kernel_messages::Enum message, void *content, size_t size){
	hold_lock hl(msg_lock);
	for(msg_subscribers_list::iterator i=msg_subscribers->begin(); i!=msg_subscribers->end(); ++i){
		if(i->second.find(message)!=i->second.npos){
			bt_msg_header msg;
			msg.type=message;
			msg.to=i->first;
			msg.content=malloc(size);
			msg.source=0;
			msg.from=0;
			msg.flags=0;
			memcpy(msg.content, content, size);
			msg_send(msg);
		}
	}
}

bool msg_recv_reply(btos_api::bt_msg_header &msg, uint64_t msg_id){
    hold_lock hl(msg_lock);
    for(size_t i=0; i<msg_q->size(); ++i){
        if((*msg_q)[i].to==0 && ((*msg_q)[i].flags & btos_api::bt_msg_flags::Reply) && (*msg_q)[i].reply_id == msg_id){
            msg=(*msg_q)[i];
            (*msg_q)[i].recieved = true;
            sch_set_msgstaus(thread_msg_status::Processing);
            return true;
        }
    }
    return false;
}

static bool msg_recv_reply_nolock(bt_msg_header &msg, uint64_t msg_id){
    if(get_lock_owner(msg_lock)) return false;
    for(size_t i=0; i<msg_q->size(); ++i){
        if((*msg_q)[i].to==0 && ((*msg_q)[i].flags & btos_api::bt_msg_flags::Reply) && (*msg_q)[i].reply_id == msg_id){
            msg=(*msg_q)[i];
            (*msg_q)[i].recieved = true;
            return true;
        }
    }
    return false;
}

struct msg_reply_blockcheck_params{
    bt_msg_header *msg;
    uint64_t msg_id;
};

bool msg_reply_blockcheck(void *p){
    msg_reply_blockcheck_params *params=(msg_reply_blockcheck_params*)p;
    bool ret=msg_recv_reply_nolock(*params->msg, params->msg_id);
    return ret;
}

bt_msg_header msg_recv_reply_block(uint64_t msg_id){
    bt_msg_header ret;
    if(!msg_recv_reply(ret, msg_id)){
        sch_set_msgstaus(thread_msg_status::Waiting);
        msg_reply_blockcheck_params params={&ret, msg_id};
        sch_setblock(&msg_reply_blockcheck, (void*)&params);
    }
    sch_set_msgstaus(thread_msg_status::Processing);
    return ret;
}