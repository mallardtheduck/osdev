#include "rtc_internal.hpp"
#include <util/ministl.hpp>
#include "../locks.hpp"

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
timer_event *next_event = nullptr;

bool events_blockcheck(void*){
	if(try_take_lock_exclusive(timer_lock)){
		bool ret = (events->size() > 0);
		release_lock(timer_lock);
		return ret;
	}
	return false;
}

bool next_event_blockcheck(void*){
	if(try_take_lock_exclusive(timer_lock)){
		bool ret = next_event ? get_msecs() >= next_event->time : false;
		release_lock(timer_lock);
		return ret;
	}
	return false;
}

void update_next_event(){
	uint64_t time = UINT64_MAX;
	next_event = nullptr;
	for(size_t i = 0; i<events->size(); ++i){
		timer_event *e = (*events)[i];
		if(e->time < time){
			next_event = e;
			time = e->time;
		}
	}
}

void timer_thread(void*){
	sch_set_priority(2);
	while(true){
		sch_setblock(&events_blockcheck, NULL);
		sch_setblock(&next_event_blockcheck, NULL);
		take_lock_exclusive(timer_lock);
		timer_event *last_event = nullptr;
		if(next_event){
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
				timer->active = false;
				msg_send(msg);
			}
			events->erase(events->find(next_event));
			last_event = next_event;
		}
		update_next_event();
		release_lock(timer_lock);
		if(last_event) delete last_event;
	}
}

void init_timer(){
	events = new vector<timer_event*>();
	timers = new map<uint64_t, timer_info*>();
	init_lock(timer_lock);
	sch_new_thread(&timer_thread, NULL);
}

void close_timer(void *vt){
	timer_info *t = (timer_info*)vt;
	take_lock_exclusive(timer_lock);
	for(size_t i = 0; i<events->size(); ++i){
		timer_event *e = (*events)[i];
		if(e->timer_id == t->timer_id) e->cancel = true;
	}
	timers->erase(t->timer_id);
	release_lock(timer_lock);
	delete t;
}

void create_timer(ICPUState &state){
	timer_info *t=new timer_info();
	t->duration = state.Get32BitRegister(Generic_Register::GP_Register_B);
	t->pid = CurrentProcess().ID();
	t->active = false;
	take_lock_exclusive(timer_lock);
	t->timer_id = ++timer_id_counter;
	release_lock(timer_lock);
	bt_handle_info handle;
	handle.value = (void*)t;
	handle.type = ((extension_id) << 16) + 1;
	handle.close = &close_timer;
	handle.open = true;
	t->handle_id = proc_add_handle(handle, t->pid);
	(*timers)[t->timer_id] = t;
	*(bt_handle_t*)state.Get32BitRegister(Generic_Register::GP_Register_C) = t->handle_id;
}

void reset_timer(ICPUState &state){
	bt_handle_info handle = proc_get_handle(state.Get32BitRegister(Generic_Register::GP_Register_B), CurrentProcess().ID());
	if(handle.open){
		timer_info *t = (timer_info*)handle.value;
		if(!t->active){
			t->active = true;
			timer_event *e = new timer_event();
			e->cancel = false;
			e->pid = CurrentProcess().ID();
			e->time = get_msecs() + t->duration;
			e->timer_id = t->timer_id;
			take_lock_exclusive(timer_lock);
			events->push_back(e);
			update_next_event();
			release_lock(timer_lock);
		}
	}
}
