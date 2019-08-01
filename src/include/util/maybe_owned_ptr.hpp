#ifndef _MAYBE_OWNED_PTR_HPP
#define _MAYBE_OWNED_PTR_HPP

template<typename T> class maybe_owned_ptr{
private:
	T *ptr;
	bool owned;
public:
	maybe_owned_ptr() : ptr(nullptr), owned(false) {}
	maybe_owned_ptr(T *p, bool o) : ptr(p), owned(o) {}
	maybe_owned_ptr(const maybe_owned_ptr<T> &other) = delete;
	maybe_owned_ptr(maybe_owned_ptr<T> &&other) : ptr(other.ptr), owned(other.owned){
		other.owned = false;
	}
	
	maybe_owned_ptr<T> &operator=(const maybe_owned_ptr<T> &other) = delete;
	maybe_owned_ptr<T> &operator=(maybe_owned_ptr<T> &&other){
		ptr = other.ptr;
		owned = other.owned;
		other.owned = false;
		return *this;
	}
	
	T &operator*(){
		return *ptr;
	}
	
	T* get(){
		return ptr;
	}
	
	T* operator->(){
		return ptr;
	}
	
	~maybe_owned_ptr(){
		if(owned) delete ptr;
	}
};

#endif