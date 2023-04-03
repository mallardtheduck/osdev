#ifndef UTIL_PIMPL_PTR_HPP
#define UTIL_PIMPL_PTR_HPP

#define PIMPL_IMPL(T) void pimpl_delete(T* p){ delete p; }
#define PIMPL_CLASS(T) void pimpl_delete(T* p);

namespace btos{

template<typename T> class pimpl_ptr{
private:
	T* thePointer = nullptr;
public:
	pimpl_ptr() {}
	explicit pimpl_ptr(T *ptr) : thePointer(ptr) {}

	pimpl_ptr(const pimpl_ptr<T>&) = delete;

	pimpl_ptr(pimpl_ptr<T> &&other) = delete;

	pimpl_ptr<T> &operator=(const pimpl_ptr<T>&) = delete;

	pimpl_ptr<T> &operator=(pimpl_ptr<T> &&other) = delete;

	T *get() const{
		return thePointer;
	}

	operator bool() const{
		return thePointer;
	}

	T &operator*() const{
		return *thePointer;
	}

	T *operator->() const{
		return thePointer;
	}

	~pimpl_ptr(){
		if(thePointer) pimpl_delete(thePointer);
	}
};

}

#endif