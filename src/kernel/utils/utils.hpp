#ifndef KERNEL_UTILS_HPP
#define KERNEL_UTILS_HP

#include "new.hpp"
#include "../locks.hpp"
#include "gcc_builtins.h"
#include "string.hpp"
#include "ministl.hpp"
#include <util/noncopyable.hpp>

//String
class string;

char* itoa(int num, char* str, int base=10);
string to_upper(const string &str);
bool starts_with(const string &str, const string &cmp);
vector<string> split_string(const string &str, const char c);

string itoa(int num, int base = 10);

template<typename T> T min(T a, T b){
	return (a < b) ? a : b;
}

template<typename T>  T max(T a, T b){
	return (a > b) ? a : b;
}

template<typename T> void New(T *&var){
	var = new T();
}

template<typename T, typename ...Tp> void New(T *&var, Tp... params){
	var = new T(params...);
}

class ILock;
ILock *NewLock();

namespace StaticAllocInitPolicies{
	namespace Private{
		void TakeLock(ILock *lock);
		void ReleaseLock(ILock *lock);
	};

	template<typename T> struct Manually{
		void CheckInit(T *ptr, char (&)[sizeof(T)]){
			if(!ptr) panic("(SA) Use before allocation!");
		}

		void Init(T *&ptr, char (&buffer)[sizeof(T)]){
			if(ptr) panic("(SA) Duplicate initialisation!");
			ptr = new(buffer) T();
			if(!ptr) panic("(SA) Init failed!");
		}

		template<typename... Ts>
		void Init(T *&ptr, char (&buffer)[sizeof(T)], Ts... params){
			if(ptr) panic("(SA) Duplicate initialisation!");
			ptr = new(buffer) T(params...);
			if(!ptr) panic("(SA) Init failed!");
		}
	};

	extern StaticAllocLock initLock;

	template<typename T> struct OnDemand{

		void CheckInit(T *&ptr, char (&buffer)[sizeof(T)]){
			if(!ptr){
				Private::TakeLock(initLock.get());
				if(!ptr) ptr = new(buffer) T();
				Private::ReleaseLock(initLock.get());
				if(!ptr) panic("(SA) Init failed!");
			}
		}

		void Init(T*, char (&)[sizeof(T)]){
		}
	};
};

template<typename T, typename InitPolicy> class StaticAlloc : private nonmovable{
private:
	alignas(T) char buffer[sizeof(T)];
	T *ptr = nullptr;

	InitPolicy initer;
public:
	T& operator*(){
		initer.CheckInit(ptr, buffer);
		return *ptr;
	}

	T *operator->(){
		initer.CheckInit(ptr, buffer);
		return ptr;
	}

	operator T*(){
		initer.CheckInit(ptr, buffer);
		return ptr;
	}

	operator bool(){
		return ptr;
	}

	void Init(){
		initer.Init(ptr, buffer);
	}

	template<typename... Ts>
	void Init(Ts... params){
		initer.Init(ptr, buffer, params...);
	}
};

template<typename T> using ManualStaticAlloc = StaticAlloc<T, StaticAllocInitPolicies::Manually<T>>;
template<typename T> using OnDemandStaticAlloc = StaticAlloc<T, StaticAllocInitPolicies::OnDemand<T>>;

void Utils_Init();

#endif