#include <btos/thread.hpp>
#include <utility>

namespace btos_api{

	Thread::Thread(bt_handle_t h) : Handle(h, false) {}

	Thread::Thread(void (*entry)(void*), void *param, size_t stacksize) : Handle(btos_create_thread(entry, param, stacksize)) {}
	
	Thread::Thread(Thread &&t) : Handle(std::move(t)) {}

	Thread Thread::Current(){
		return Thread(bt_get_thread());
	}

	void Thread::Wait() const{
		bt_wait_thread(handle);
	}

	void Thread::UnBlock(){
		bt_unblock_thread(handle);
	}

	void Thread::Abort(){
		bt_thread_abort(handle);
	}

	void Thread::SetName(const char *name){
		bt_set_thread_name(name);
	}

}
