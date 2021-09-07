#ifndef _HANDLES_HPP
#define _HANDLES_HPP

#include <module/handle.h>

namespace kernel_handle_types{
	static const uint32_t invalid=0;
	static const uint32_t lock=1;
	static const uint32_t file=2;
	static const uint32_t directory=3;
	static const uint32_t thread=4;
	static const uint32_t memory_mapping=5;
	static const uint32_t shm_space=6;
	static const uint32_t shm_mapping=7;
	static const uint32_t atom=8;
	static const uint32_t wait=9;
	static const uint32_t atomwait=10;
	static const uint32_t msg_recv=11;
	static const uint32_t elf = 12;
};

void init_handles();

void add_handle_dep(bt_handle_info &h);

enum class handle_dep_check_result{
	Present, Absent, NotAvailable
};

handle_dep_check_result handle_dep_check(bt_handle_info &h);

extern bt_handle_info invalid_handle;

class IHandle{
public:
	virtual uint32_t GetType() = 0;

	virtual void Close() = 0;
	virtual bool Wait() = 0;

	virtual ~IHandle(){}
};

template<typename T>
class GenericHandle : public IHandle{
protected:
	uint32_t type;
	T data;
	function<void(T)> close;
	function<bool(T)> wait;
public:
	GenericHandle(uint32_t t, T *d, function<void(T)> c, function<bool(T)> w) : type(t), data(d), close(c), wait(w) {}

	virtual uint32_t GetType() override{
		return type;
	}

	virtual void Close() override{
		if(close) close(data);
	}

	virtual bool Wait() override{
		if(wait) return wait(data);
		else return false;
	}

	virtual T &GetData(){
		return data;
	}

	virtual ~GenericHandle() {}
};

template<typename T, typename Tclose = nullptr_t, typename Twait = nullptr_t>
GenericHandle<T> *MakeGenericHandle(uint32_t type, T data, Tclose close = nullptr, Twait wait = nullptr){
	return GenericHandle<T>(type, data, close, wait);
}

#endif
