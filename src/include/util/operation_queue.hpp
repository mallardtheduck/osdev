#ifndef _OPERATION_QUEUE_HPP
#define _OPERATION_QUEUE_HPP

#include <btos_module.h>

template<
	typename opT, 
	bool(*proccessFn)(opT*), 
	size_t queue_size, 
	void(*yieldFn)() = nullptr
> class operation_queue{
private:
	typedef operation_queue<opT, proccessFn, queue_size, yieldFn> this_type;

	opT *queue[queue_size];
	size_t queue_count, queue_top;
	ILock *queue_lock;
	uint64_t thread;

	opT *get(){
		auto hl = queue_lock->LockExclusive();
		while(!queue_count){
			queue_lock->Release();
			if(yieldFn) yieldFn();
			API->CurrentThread().SetBlock([&]{
				return queue_count > 0;
			});
			queue_lock->TakeExclusive();
		}
		if(queue_count){
			int start=queue_top-queue_count;
			if(start < 0) {
				start+=queue_size;
			}
			queue_count--;
			return queue[start];
		}else return NULL;
	}

	void operation_queue_process_thread() {
		while(true){
			opT *operation=get();
			if(!proccessFn(operation)) break;
		}
	}

public:
	operation_queue(){
		queue_count=0;
		queue_top=0;
		queue_lock = API->NewLock();
		thread = API->GetScheduler().NewThread([&]{
			operation_queue_process_thread();
		})->ID();
	}

	void add(opT* op){
		if(thread == 0) return;
		auto hl = queue_lock->LockExclusive();
		while(queue_count >= queue_size){
			queue_lock->Release();
			API->CurrentThread().SetBlock([&]{
				return queue_count < queue_size;
			});
			queue_lock->TakeExclusive();
		}
		if(queue_count < queue_size){
			queue_count++;
			queue[queue_top] = op;
			queue_top++;
			if(queue_top == queue_size) queue_top=0;
		}
	}
	
	void wait_for_end(){
		API->GetScheduler().GetByID(thread)->Join();
		thread = 0;
	}
};

#endif
