#ifndef _THREAD_HPP
#define _THREAD_HPP

#include "handle.hpp"

namespace btos_api{
	
	class Thread : public Handle{
	private:
		Thread(bt_handle_t h);
	public:
		Thread(void (*entry)(void*), void *param = NULL, size_t stacksize = 16 * 1024);
		static Thread Current();

		void Wait() const;
		void UnBlock();
		void Abort();
	};

}

#endif
