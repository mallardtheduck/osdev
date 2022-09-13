#ifndef KERNEL_UTILS_RECOUNTPOINTER_HPP
#define KERNEL_UTILS_RECOUNTPOINTER_HPP

#include <type_traits>

template<typename T>
class RefCountPointer{
protected:
	T *theObject;
public:
	RefCountPointer(T *ptr) : theObject(ptr){
		if(theObject) theObject->IncrementRefCount();
	}

	RefCountPointer() : RefCountPointer(nullptr) {}

	RefCountPointer(const RefCountPointer &other) : RefCountPointer(other.theObject) {
		if(theObject) theObject->IncrementRefCount();
	}

	RefCountPointer(RefCountPointer &&other) : theObject(other.theObject){
		other.theObject = nullptr;
	}

	~RefCountPointer(){
		if(theObject) theObject->DecrementRefCount();
	}

	RefCountPointer &operator=(const RefCountPointer &other){
		if(&other != this){
			auto oldObject = theObject;
			theObject = other.theObject;
			if(theObject != oldObject){
				if(theObject) theObject->IncrementRefCount();
				if(oldObject) theObject->DecrementRefCount();
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
		return theObject;
	}

	T *get(){
		return theObject;
	}

	T &operator*(){
		return *theObject;
	}

	bool operator==(const RefCountPointer &other) const{
		return theObject == other.theObject;
	}

	bool operator!=(const RefCountPointer &other) const{
		return theObject != other.theObject;
	}

	template<typename R> operator RefCountPointer<R>(){
		static_assert(!std::is_convertible_v<T*, R*>, "No convesion available.");
		return RefCountPointer<R>(theObject);
	}
};

#endif