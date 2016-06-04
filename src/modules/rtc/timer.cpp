#include "rtc.hpp"
#include <util/ministl.hpp>

uint64_t timer_id_counter = 0;

struct timer_event{
	pid_t pid;
	uint64_t time;
	uint64_t timer_id;
	bool cancel;
};

struct timer_info{
	uint64_t timer_id;
	bt_handle_t handle_id;
	pid_t pid;
	uint64_t duration;
	bool active;
};

vector<timer_event*> *events;
map<uint64_t, timer_info*> *timers;
lock timer_lock;
timer_event *next_event;

bool events_blockcheck(void*){
	if(try_take_lock(&timer_lock)){
		bool ret = (events->size() > 0);
		release_lock(&timer_lock);
		return ret;
	}
	return false;
}

bool next_event_blockcheck(void*){
	return msec_counter >= next_event->time;
}

void update_next_event(){
	uint64_t time = UINT64_MAX;
	for(size_t i = 0; i<events->size(); ++i){
		timer_event *e = (*events)[i];
		if(e->time < time){
			next_event = e;
			time = e->time;
		}
	}
}

void timer_thread(void*){
	thread_priority(2);
	while(true){
		thread_setblock(&events_blockcheck, NULL);
		thread_setblock(&next_event_blockcheck, NULL);
		take_lock(&timer_lock);
		if(!next_event->cancel){
			btos_api::bt_msg_header msg;
			msg.from = 0;
			msg.to = next_event->pid;
			msg.source = extension_id;
			msg.type = 0;
			msg.critical = 0;
			msg.flags = 0;
			msg.length = sizeof(bt_handle_t);
			msg.content = malloc(sizeof(bt_handle_t));
			timer_info *timer = (*timers)[next_event->timer_id];
			*(bt_handle_t*)msg.content = timer->handle_id;
			msg_send(&msg);
			timer->active = false;
		}
		events->erase(events->find(next_event));
		timer_event *last_event = next_event;
		update_next_event();
		release_lock(&timer_lock);
		delete last_event;
	}
}

void init_timer(){
	events = new vector<timer_event*>();
	timers = new map<uint64_t, timer_info*>();
	init_lock(&timer_lock);
	new_thread(&timer_thread, NULL);
}

void close_timer(void *vt){
	timer_info *t = (timer_info*)vt;
	take_lock(&timer_lock);
	for(size_t i = 0; i<events->size(); ++i){
		timer_event *e = (*events)[i];
		if(e->timer_id == t->timer_id) e->cancel = true;
	}
	timers->erase(t->timer_id);
	release_lock(&timer_lock);
	delete t;
}

void create_timer(isr_regs *regs){
	timer_info *t=new timer_info();
	t->duration = regs->ebx;
	t->pid = getpid();
	t->active = false;
	take_lock(&timer_lock);
	t->timer_id = ++timer_id_counter;
	release_lock(&timer_lock);
	bt_handle_info handle;
	handle.value = (void*)t;
	handle.type = ((extension_id) << 16) + 1;
	handle.close = &close_timer;
	handle.open = true;
	t->handle_id = add_user_handle(handle, t->pid);
	(*timers)[t->timer_id] = t;
	*(bt_handle_t*)regs->ecx = t->handle_id;
}

void reset_timer(isr_regs *regs){
	bt_handle_info handle = get_user_handle(regs->ebx, getpid());
	if(handle.open){
		timer_info *t = (timer_info*)handle.value;
		if(!t->active){
			t->active = true;
			timer_event *e = new timer_event();
			e->cancel = false;
			e->pid = getpid();
			e->time = msec_counter + t->duration;
			e->timer_id = t->timer_id;
			take_lock(&timer_lock);
			events->push_back(e);
			update_next_event();
			release_lock(&timer_lock);
		}
	}
}