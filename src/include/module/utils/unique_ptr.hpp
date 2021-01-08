#ifndef MODULE_UTILS_UNIQUE_PTR_HPP
#define MODULE_UTILS_UNIQUE_PTR_HPP

template<typename T> class unique_ptr{
private:
	T* thePointer = nullptr;
public:
	unique_ptr() {}
	explicit unique_ptr(T *ptr) : thePointer(ptr) {}

	unique_ptr(const unique_ptr<T>&) = delete;

	template<typename R>
	unique_ptr(unique_ptr<R> &&other) : thePointer(other.release()){
	}

	unique_ptr<T> &operator=(const unique_ptr<T>&) = delete;

	template<typename R>
	unique_ptr<T> &operator=(unique_ptr<R> &&other){
		if(this != &other){
			thePointer = other.release();
		}
		return *this;
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

	~unique_ptr(){
		if(thePointer) delete thePointer;
	}
};

template<typename T, typename... Args>
unique_ptr<T> make_unique(Args... args){
	return unique_ptr<T>(new T(args...));
}

#endif