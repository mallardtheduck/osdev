#include "kernel.hpp"
#include "ministl.hpp"
#include "locks.hpp"

using namespace btos_api;

static uint64_t id_counter=0;
lock msg_lock;

static bool msg_get(uint64_t id, bt_msg_header &msg, pid_t pid = proc_current_pid);
static void msg_send_receipt(const bt_msg_header &omsg);

typedef map<pid_t, vector<bt_kernel_messages::Enum> > msg_subscribers_list;
static msg_subscribers_list *msg_subscribers;

static const size_t pool_min = 16;
static const size_t pool_max = pool_min * 2;
//static vector<void*> buffer_pool;
static vector<bt_msg_header*> *header_pool;

static bt_msg_header *copy_msg_header(const bt_msg_header &h){
	if(!header_pool->size()){
		for(size_t i = 0; i < pool_min; ++i){
			header_pool->push_back((bt_msg_header*)malloc(sizeof(bt_msg_header)));
		}
	}
	
	size_t backindex = header_pool->size() - 1;
	bt_msg_header *ret = (*header_pool)[backindex];
	header_pool->erase(backindex);
	*ret = h;
	return ret;
}

static void release_msg_header(bt_msg_header *h){
	if(header_pool->size() >= pool_max){
		free(h);
		for(size_t i = header_pool->size() - 1; i > pool_min; --i){
			free((*header_pool)[i]);
			header_pool->erase(i);
		}
		return;
	}
	header_pool->push_back(h);
}

void msg_init(){
    dbgout("MSG: Init messaging...\n");
    init_lock(msg_lock);
	msg_subscribers=new msg_subscribers_list();
	
	//buffer_pool	= new vector<void*>();
	header_pool = new vector<bt_msg_header*>();
	
	for(size_t i = 0; i < pool_min; ++i){
		//buffer_pool.push_back(malloc(BT_MSG_MAX));
		header_pool->push_back((bt_msg_header*)malloc(sizeof(bt_msg_header)));
	}
}

uint64_t msg_send(bt_msg_header &msg){
    if(msg.to != 0 && proc_get_status(msg.to) == proc_status::DoesNotExist){
		dbgpf("MSG: Attempted to send message to non-existent process!\n");
		return 0;
	 }
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
            return 0;
        }
        {
            hold_lock hl(msg_lock, false);
            for (size_t i = 0; bt_msg_header *omsg = proc_get_msg(i, msg.from); ++i){
                if (omsg->id == prev.id) {
                    omsg->replied = true;
                }
            }
        }
    }
    {
        hold_lock hl(msg_lock, false);
        msg.id = ++id_counter;
        msg.valid = true;
        msg.recieved = msg.replied = false;
        bt_msg_header *ptr = copy_msg_header(msg);
        proc_add_msg(ptr);
    }
    //dbgpf("MSG: Sent message ID %i from PID %i to PID %i.\n", (int)msg.id, (int)msg.from, (int)msg.to);
    return msg.id;
}

bool msg_recv(bt_msg_header &msg, pid_t pid){
    hold_lock hl(msg_lock);
    for(size_t i = 0; bt_msg_header *cmsg = proc_get_msg(i, pid); ++i){
		msg=*cmsg;
		cmsg->recieved = true;
		sch_set_msgstaus(thread_msg_status::Processing);
		return true;
    }
    return false;
}

static bool msg_recv_nolock(bt_msg_header &msg, pid_t pid){
    if(get_lock_owner(msg_lock)) return false;
    for(size_t i = 0; bt_msg_header *cmsg = proc_get_msg_nolock(i, pid); ++i){
		msg=*cmsg;
		cmsg->recieved = true;
		return true;
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

static bool msg_get(uint64_t id, bt_msg_header &msg, pid_t pid){
    hold_lock hl(msg_lock, false);
    for(size_t i = 0; bt_msg_header *cmsg = proc_get_msg(i, pid); ++i){
        if(cmsg->id==id){
            msg=*cmsg;
            return true;
        }
    }
    return false;
}

size_t msg_getcontent(bt_msg_header &msg, void *buffer, size_t buffersize){
    bt_msg_header r;
    if(!msg_get(msg.id, r, msg.to)){
		//panic("(MSG) Content request for non-existent message!");
		return 0;
	}
    size_t size=buffersize>r.length?r.length:buffersize;
    //dbgpf("MSG: Copying %i bytes of content (out of %i total, %i requested) for message %i.\n", (int)size, (int)r.length, (int)buffersize, (int)r.id);
    memcpy(buffer, r.content, size);
    return size;
}

void msg_acknowledge(bt_msg_header &msg, bool set_status){
	void *found = NULL;
    {
		hold_lock hl(msg_lock, false);
		for(size_t i = 0; bt_msg_header *cmsg = proc_get_msg(i, msg.to); ++i){
			bt_msg_header &header = *cmsg;
			if(header.id==msg.id){
				msg = header;
				found = header.content;
				proc_remove_msg(cmsg);
				release_msg_header(cmsg);
				break;
			}
		}
	}
	if(found){
		if(!(msg.flags & bt_msg_flags::Reply) && (msg.flags & bt_msg_flags::UserSpace)){
			proc_free_message_buffer(msg.to, msg.from);
		}else{
			free(found);
		}
		if(set_status) sch_set_msgstaus(thread_msg_status::Normal);
		msg_send_receipt(msg);
	}
	else dbgpf("MSG: Attempt to acknowlegde non-existent message %i\n", (int)msg.id);
}

void msg_nextmessage(bt_msg_header &msg){
    msg_acknowledge(msg, false);
    msg=msg_recv_block();
}

void msg_clear(pid_t pid){
    hold_lock hl(msg_lock);
    for(size_t i = 0; bt_msg_header *cmsg = proc_get_msg(i, pid); ++i){
        bt_msg_header &header=*cmsg;
        //if(header.to==pid || (header.from==pid && !header.recieved)){
            msg_acknowledge(header, false);
        //}
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
			msg.critical=false;
			memcpy(msg.content, content, size);
			msg_send(msg);
		}
	}
}

static void msg_send_receipt(const bt_msg_header &omsg){
	hold_lock hl(msg_lock);
	for(msg_subscribers_list::iterator i=msg_subscribers->begin(); i!=msg_subscribers->end(); ++i){
		if(i->first == omsg.from && i->second.find(bt_kernel_messages::MessageReceipt) != i->second.npos){
			bt_msg_header msg;
			msg.type=bt_kernel_messages::MessageReceipt;
			msg.to=i->first;
			msg.content=malloc(sizeof(bt_msg_header));
			msg.source=0;
			msg.from=0;
			msg.flags=0;
			msg.critical=false;
			msg.length = sizeof(bt_msg_header);
			memcpy(msg.content, &omsg, sizeof(bt_msg_header));
			((bt_msg_header*)msg.content)->content=0;
			//dbgpf("MSG: Sending reciept for %i sent to %i.\n", (int)((bt_msg_header*)msg.content)->id, (int)((bt_msg_header*)msg.content)->to);
			msg_send(msg);
		}
	}
}

bool msg_recv_reply(btos_api::bt_msg_header &msg, uint64_t msg_id){
    hold_lock hl(msg_lock);
    for(size_t i = 0; bt_msg_header *cmsg = proc_get_msg(i); ++i){
        if(cmsg->to==0 && (cmsg->flags & btos_api::bt_msg_flags::Reply) && cmsg->reply_id == msg_id){
            msg=*cmsg;
            cmsg->recieved = true;
            sch_set_msgstaus(thread_msg_status::Processing);
            return true;
        }
    }
    return false;
}

static bool msg_recv_reply_nolock(bt_msg_header &msg, uint64_t msg_id){
    if(get_lock_owner(msg_lock)) return false;
    for(size_t i = 0; bt_msg_header *cmsg = proc_get_msg_nolock(i); ++i){
        if(cmsg->to==0 && (cmsg->flags & btos_api::bt_msg_flags::Reply) && cmsg->reply_id == msg_id){
            msg=*cmsg;
            cmsg->recieved = true;
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

static bool msg_is_match(const bt_msg_header &msg, const bt_msg_filter &filter){
	if(msg.critical) return true;
	bool ret = true;
	if((filter.flags & bt_msg_filter_flags::NonReply) && (msg.flags & bt_msg_flags::Reply)) ret = false;
	if((filter.flags & bt_msg_filter_flags::From) && msg.from != filter.pid) ret = false;
	if((filter.flags & bt_msg_filter_flags::Reply) && msg.reply_id != filter.reply_to) ret = false;
	if((filter.flags & bt_msg_filter_flags::Type) && msg.type != filter.type) ret = false;
	if((filter.flags & bt_msg_filter_flags::Source) && msg.source != filter.source) ret = false;
	if((filter.flags & bt_msg_filter_flags::Invert)) ret = !ret;
	return ret;
}

struct msg_filter_blockcheck_params{
	pid_t pid;
	bt_msg_filter filter;
};

bool msg_filter_blockcheck(void *p){
	msg_filter_blockcheck_params &params=*(msg_filter_blockcheck_params*)p;
	if(get_lock_owner(msg_lock)) return false;
	for(size_t i = 0; bt_msg_header *cmsg = proc_get_msg_nolock(i, params.pid); ++i){
		bt_msg_header &msg=*cmsg;
		if(msg_is_match(msg, params.filter)) return true;
	}
	return false;
}

bt_msg_header msg_recv_filtered(bt_msg_filter filter, pid_t pid){
	hold_lock hl(msg_lock);
	while(true){
		for(size_t i = 0; bt_msg_header *cmsg = proc_get_msg(i); ++i){
			bt_msg_header &msg=*cmsg;
			if(msg.to == pid && msg_is_match(msg, filter)) {
				sch_set_msgstaus(thread_msg_status::Processing);
				return msg;
			}
		}
		release_lock(msg_lock);
		sch_set_msgstaus(thread_msg_status::Waiting);
		msg_filter_blockcheck_params p = {pid, filter};
		sch_setblock(&msg_filter_blockcheck, (void*)&p);
		take_lock_exclusive(msg_lock);
	}
}

void msg_nextmessage_filtered(bt_msg_filter filter, bt_msg_header &msg){
    msg_acknowledge(msg, false);
    msg=msg_recv_filtered(filter);
}

bool msg_query_recieved(uint64_t id){
	hold_lock hl(msg_lock);
	bt_msg_header *msg = proc_get_msg_by_id(id);
	if(msg){
		return false;
	}
	return true;
}
