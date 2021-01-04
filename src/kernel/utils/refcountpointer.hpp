#ifndef KERNEL_UTILS_RECOUNTPOINTER_HPP
#define KERNEL_UTILS_RECOUNTPOINTER_HPP

template<typename T>
class RefCountPointer{
private:
	T *theObject;
public:
	RefCountPointer(IThread *ptr) : theObject(ptr){
		theObject->IncrementRefCount();
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
			if(theObject) theObject->DecrementRefCount();
			theObject = other.theObject;
			if(theObject) theObject->IncrementRefCount();
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
};

#endif