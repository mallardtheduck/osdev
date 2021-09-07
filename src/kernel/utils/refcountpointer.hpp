#ifndef KERNEL_UTILS_RECOUNTPOINTER_HPP
#define KERNEL_UTILS_RECOUNTPOINTER_HPP

template<typename T>
class RefCountPointer{
protected:
	T *theObject;
public:
	RefCountPointer(T *ptr) : theObject(ptr){
		if(theObject) theObject->IncrementRefCount();
	}

	RefCountPointer(const RefCountPointer &other) : RefCountPointer(other.theObject) {}

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
			if(theObject) theObject->IncrementRefCount();
			if(oldObject) theObject->DecrementRefCount();
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

	operator bool(){
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

	template<typename R> operator RefCountPointer<R>(){
		static_assert(!std::is_convertible_v<T*, R*>, "No convesion available.");
		return RefCountPointer<R>(theObject);
	}
};

#endif