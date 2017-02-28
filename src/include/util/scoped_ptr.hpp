#ifndef _SCOPED_PTR_HPP
#define _SCOPED_PTR_HPP

template<typename T> class scoped_ptr{
private:
	T* ptr;
public:
	scoped_ptr(T* p) : ptr(p) {};
	~scoped_ptr(){
		delete ptr;
	}
	
	T* operator* (){
		return ptr;
	}
	
	T* operator->(){
		return ptr;
	}
	
	T* get(){
		return ptr;
	}
};

#endif