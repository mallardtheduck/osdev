#ifndef MODULE_UTILS_FUNCTION_HPP
#define MODULE_UTILS_FUNCTION_HPP

#include "unique_ptr.hpp"

template <typename T>
class function;

template <typename ReturnValue, typename... Args>
class function<ReturnValue(Args...)> {
public:
	template<typename T> function(T t) : callable_(make_unique<CallableT<T>>(t)){
	}

	function(std::nullptr_t) {}

	template <typename T>
	function& operator=(T t) {
		callable_ = make_unique<CallableT<T>>(t);
		return *this;
	}

	function &operator=(std::nullptr_t){
		callable_ = nullptr;
		return *this;
	}

	ReturnValue operator()(Args... args) const {
		if(!callable_) panic("(FUNCTION) Call to void!");
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

	private:
		T t_;
	};

	unique_ptr<ICallable> callable_;
};

#endif