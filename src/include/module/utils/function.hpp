#ifndef MODULE_UTILS_FUNCTION_HPP
#define MODULE_UTILS_FUNCTION_HPP

#include "unique_ptr.hpp"

template <typename T>
class function;

template <typename ReturnValue, typename... Args>
class function<ReturnValue(Args...)> {
private:
	typedef function<ReturnValue(Args...)> this_t;
	typedef ReturnValue(*fnPtr)(Args...);

	class ICallable {
	public:
		virtual ~ICallable() = default;
		virtual ReturnValue Invoke(Args...) const = 0;
		virtual ICallable *Clone(char *buffer) const = 0;
	};

	template <typename T>
	class CallableT : public ICallable {
	public:
		CallableT(T& t)
			: t_(t) {
		}

		~CallableT() override = default;

		ReturnValue Invoke(Args... args) const override {
			return t_(args...);
		}

		ICallable *Clone(char *buffer) const{
			return new(buffer) CallableT<T>(*this);
		}

	private:
		T t_;
	};

	static constexpr size_t callableBufferSize = 32;
	char callableBuffer[callableBufferSize];

	template<typename T> ICallable *MakeCallable(T &t){
		static_assert(sizeof(CallableT<T>) <= callableBufferSize, "Callable object must be small!");
		return new(callableBuffer) CallableT<T>(t);
	}

	ICallable *callable_ = nullptr;
public:
	template<typename T> function(T t) : callable_(MakeCallable(t)){
	}

	function(fnPtr ptr) : callable_(MakeCallable(ptr)) {}

	function(std::nullptr_t) {}

	function() : function(nullptr) {}

	function(const this_t &other){
		if(other.callable_) callable_= other.callable_->Clone(callableBuffer);
	}

	template <typename T>
	function& operator=(T t) {
		callable_ = MakeCallable(t);
		return *this;
	}

	function &operator=(std::nullptr_t){
		if(callable_) callable_->~ICallable();
		callable_ = nullptr;
		return *this;
	}

	function &operator=(const this_t &other){
		if(this != &other){
			if(callable_) callable_->~ICallable();
			if(other.callable_) callable_ = other.callable_->Clone(callableBuffer);
			else callable_= nullptr;
		}
		return *this;
	}

	ReturnValue operator()(Args... args) const {
		if(!callable_) panic("(FUNCTION) Call to nullptr!");
		return callable_->Invoke(args...);
	}

	operator bool() const{
		return callable_;
	}

	~function(){
		if(callable_) callable_->~ICallable();
	}
};

#endif