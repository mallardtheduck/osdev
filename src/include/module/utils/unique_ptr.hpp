#ifndef MODULE_UTILS_UNIQUE_PTR_HPP
#define MODULE_UTILS_UNIQUE_PTR_HPP

template<typename T> class unique_ptr{
private:
	T* thePointer = nullptr;
public:
	unique_ptr() {}
	explicit unique_ptr(T *ptr) : thePointer(ptr) {}

	unique_ptr(const unique_ptr<T>&) = delete;

	unique_ptr(unique_ptr<T> &&other) : thePointer(other.thePointer){
		other.thePointer = nullptr;
	}

	unique_ptr<T> &operator=(const unique_ptr<T>&) = delete;

	unique_ptr<T> &operator=(unique_ptr<T> &&other){
		if(this != &other){
			thePointer = other.thePointer;
			other.thePointer = nullptr;
		}
	}

	T *release(){
		T *ret = thePointer;
		thePointer = nullptr;
		return ret;
	}

	void reset(T *ptr){
		if(thePointer) delete thePointer;
		thePointer = ptr;
	}

	void swap(unique_ptr<T> &other){
		T *ptr = other.thePointer;
		other.thePointer = thePointer;
		thePointer = ptr;
	}

	T *get(){
		return thePointer;
	}

	operator bool(){
		return thePointer;
	}

	T &operator*(){
		return *thePointer;
	}

	T *operator->(){
		return thePointer;
	}

	~unique_ptr(){
		if(thePointer) delete thePointer;
	}
};

#endif