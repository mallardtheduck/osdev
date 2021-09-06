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
public:
	template<typename T> function(T t) : callable_(make_unique<CallableT<T>>(t)){
	}

	function(fnPtr ptr) : callable_(make_unique<CallableT<fnPtr>>(ptr)) {}

	function(std::nullptr_t) {}

	function() : function(nullptr) {}

	function(const this_t &other){
		if(other.callable_) callable_.reset(other.callable_->Clone());
	}

	template <typename T>
	function& operator=(T t) {
		callable_ = make_unique<CallableT<T>>(t);
		return *this;
	}

	function &operator=(std::nullptr_t){
		callable_.reset(nullptr);
		return *this;
	}

	function &operator=(const this_t &other){
		if(this != &other){
			if(other.callable_) callable_.reset(other.callable_->Clone());
			else callable_.reset(nullptr);
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

private:
	class ICallable {
	public:
		virtual ~ICallable() = default;
		virtual ReturnValue Invoke(Args...) const = 0;
		virtual ICallable *Clone() const = 0;
	};

	template <typename T>
	class CallableT : public ICallable {
	public:
		CallableT(const T& t)
			: t_(t) {
		}

		~CallableT() override = default;

		ReturnValue Invoke(Args... args) const override {
			return t_(args...);
		}

		ICallable *Clone() const{
			return new CallableT<T>(*this);
		}

	private:
		T t_;
	};

	unique_ptr<ICallable> callable_;
};

#endif