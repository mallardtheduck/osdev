#include <btos/thread.hpp>

namespace btos_api{

	Thread::Thread(bt_handle_t h) : Handle(h, false) {}

	Thread::Thread(void (*entry)(void*), void *param, size_t stacksize) : Handle(btos_create_thread(entry, param, stacksize)) {}

	Thread Thread::Current(){
		return Thread(bt_get_thread());
	}

	void Thread::Wait(){
		bt_wait_thread(handle);
	}

	void Thread::UnBlock(){
		bt_unblock_thread(handle);
	}

	void Thread::Abort(){
		bt_thread_abort(handle);
	}

}
