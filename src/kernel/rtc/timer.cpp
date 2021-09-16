#include "rtc_internal.hpp"
#include <util/ministl.hpp>
#include "../locks.hpp"

uint64_t timer_id_counter = 0;
static uint32_t timer_handle_id;

struct timer_event{
	bt_pid_t pid;
	uint64_t time;
	uint64_t timer_id;
	bool cancel;
};

struct timer_info{
	uint64_t timer_id;
	bt_handle_t handle_id;
	bt_pid_t pid;
	uint64_t duration;
	bool active;
};

vector<timer_event*> *events;
map<uint64_t, timer_info*> *timers;
StaticAllocLock timer_lock;
timer_event *next_event = nullptr;

bool events_blockcheck(){
	if(timer_lock->TryTakeExclusive()){
		bool ret = (events->size() > 0);
		timer_lock->Release();
		return ret;
	}
	return false;
}

bool next_event_blockcheck(){
	if(timer_lock->TryTakeExclusive()){
		bool ret = next_event ? get_msecs() >= next_event->time : false;
		timer_lock->Release();
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

void timer_thread(){
	CurrentThread().SetPriority(2);
	while(true){
		CurrentThread().SetBlock(&events_blockcheck);
		CurrentThread().SetBlock(&next_event_blockcheck);
		timer_lock->TakeExclusive();
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
		timer_lock->Release();
		if(last_event) delete last_event;
	}
}

void init_timer(){
	events = new vector<timer_event*>();
	timers = new map<uint64_t, timer_info*>();
	timer_handle_id = ((extension_id) << 16) + 1;
	GetScheduler().NewThread(&timer_thread);
}

void close_timer(timer_info *t){
	timer_lock->TakeExclusive();
	for(size_t i = 0; i<events->size(); ++i){
		timer_event *e = (*events)[i];
		if(e->timer_id == t->timer_id) e->cancel = true;
	}
	timers->erase(t->timer_id);
	timer_lock->Release();
	delete t;
}

void create_timer(ICPUState &state){
	timer_info *t=new timer_info();
	t->duration = state.Get32BitRegister(Generic_Register::GP_Register_B);
	t->pid = CurrentProcess().ID();
	t->active = false;
	timer_lock->TakeExclusive();
	t->timer_id = ++timer_id_counter;
	timer_lock->Release();
	auto handle = MakeGenericHandle(timer_handle_id, t, &close_timer);
	t->handle_id = CurrentProcess().AddHandle(handle);
	(*timers)[t->timer_id] = t;
	*(bt_handle_t*)state.Get32BitRegister(Generic_Register::GP_Register_C) = t->handle_id;
}

void reset_timer(ICPUState &state){
	auto h = CurrentProcess().GetHandle(state.Get32BitRegister(Generic_Register::GP_Register_B));
	if(auto handle = GenericHandleCast<timer_info*>(timer_handle_id, h)){
		auto t = handle->GetData();
		if(!t->active){
			t->active = true;
			timer_event *e = new timer_event();
			e->cancel = false;
			e->pid = CurrentProcess().ID();
			e->time = get_msecs() + t->duration;
			e->timer_id = t->timer_id;
			timer_lock->TakeExclusive();
			events->push_back(e);
			update_next_event();
			timer_lock->Release();
		}
	}
}
