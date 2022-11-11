#ifndef KERNEL_UTILS_RECOUNTPOINTER_HPP
#define KERNEL_UTILS_RECOUNTPOINTER_HPP

#include <type_traits>
#include "function.hpp"

template<typename T>
class RefCountPointer{
protected:
	T *theObject;
public:
	RefCountPointer(T *ptr) : theObject(ptr){
		if(theObject) theObject->IncrementRefCount();
	}

	RefCountPointer() : RefCountPointer(nullptr) {}

	RefCountPointer(const RefCountPointer &other) : RefCountPointer(other.theObject) {}

	RefCountPointer(RefCountPointer &&other) : theObject(other.theObject){
		other.theObject = nullptr;
	}

	~RefCountPointer(){
		if(theObject) theObject->DecrementRefCount();
		theObject = nullptr;
	}

	RefCountPointer &operator=(const RefCountPointer &other){
		if(&other != this){
			auto oldObject = theObject;
			theObject = other.theObject;
			if(theObject != oldObject){
				if(theObject) theObject->IncrementRefCount();
				if(oldObject) oldObject->DecrementRefCount();
			}
		}
		return *this;
	}

	RefCountPointer &operator=(RefCountPointer &&other){
		if(&other != this){
			if(theObject) theObject->DecrementRefCount();
			theObject = other.theObject;
			other.theObject = nullptr;
		}
		return *this;
	}

	operator bool() const{
		return theObject;
	}

	T *operator->(){
		if(!theObject) panic("(RCP) nullptr deference!");
		return theObject;
	}

	T *get(){
		if(!theObject) panic("(RCP) nullptr deference!");
		return theObject;
	}

	T &operator*(){
		if(!theObject) panic("(RCP) nullptr deference!");
		return *theObject;
	}

	bool operator==(const RefCountPointer &other) const{
		return theObject == other.theObject;
	}

	bool operator!=(const RefCountPointer &other) const{
		return theObject != other.theObject;
	}

	template<typename R> operator RefCountPointer<R>(){
		static_assert(!std::is_convertible_v<T*, R*>, "No conversion available.");
		return RefCountPointer<R>(theObject);
	}
};

template<typename T> class WeakReference{
private:
	function<RefCountPointer<T>()> getter;
public:
	WeakReference(function<RefCountPointer<T>()> g) : getter(g) {}
	WeakReference(const WeakReference<T> &) = default;
	WeakReference<T> &operator=(const WeakReference<T> &) = default;

	RefCountPointer<T> Lock(){
		return getter();
	}

	RefCountPointer<T> operator->(){
		return getter();
	}

	bool operator==(const RefCountPointer<T> &rcp) const{
		return rcp == getter();
	}
	
	bool operator!=(const RefCountPointer<T> &rcp) const{
		return !(*this == rcp);
	}

	bool operator==(const T &t) const{
		return &t == getter().get();
	}

	bool operator!=(const T &t) const{
		return !(*this == t);
	}
};

#endif