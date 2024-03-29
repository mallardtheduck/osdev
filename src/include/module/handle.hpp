#ifndef MODULE_HANDLE_HPP
#define MODULE_HANDLE_HPP

#include <cstdint>
#include <cstddef>
#include <util/noncopyable.hpp>
#include "utils/function.hpp"

class IHandle : private nonmovable{
public:
	virtual uint32_t GetType() = 0;

	virtual void Close() = 0;
	virtual bool Wait() = 0;

	virtual ~IHandle() {}
};

template<typename T>
class GenericHandle : public IHandle{
protected:
	uint32_t type;
	T data;
	function<void(T)> close;
	function<bool(T)> wait;
public:
	using dataType = T;

	GenericHandle(uint32_t t, T d, function<void(T)> c, function<bool(T)> w) : type(t), data(d), close(c), wait(w) {}

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
	return new GenericHandle<T>(type, data, close, wait);
}

template<typename T> GenericHandle<T> *GenericHandleCast(uint32_t type, IHandle *handle){
	if(handle && handle->GetType() == type) return static_cast<GenericHandle<T>*>(handle);
	else return nullptr;
}

template<typename>
struct IsGenericHandle : public std::false_type {};

template<typename T>
struct IsGenericHandle<GenericHandle<T>> : public std::true_type {};

#endif