#ifndef _LOCKABLE_HPP
#define _LOCKABLE_HPP

#include "../hwpnp.hpp"

namespace btos_api{
namespace hwpnp{

	class ILockable;

	class ScopeLock{
	private:
		ILockable *lockable;
		
		friend class ILockable;
		ScopeLock(ILockable *l) : lockable(l) {}
	public:
		ScopeLock(ScopeLock&) = delete;
		ScopeLock(ScopeLock &&other){
			lockable = other.lockable;
			other.lockable = nullptr;
		}
		
		void Unlock();
		
		~ScopeLock(){
			Unlock();
		}
	};

	class ILockable{
	protected:
		virtual void Lock() = 0;
		virtual void Unlock() = 0;
		friend class ScopeLock;
	public:
		virtual ScopeLock GetLock(){
			Lock();
			return ScopeLock(this);
		}
		virtual ~ILockable() {}
	};
	
	
	inline void ScopeLock::Unlock(){
		if(lockable){
			lockable->Unlock();
			lockable = nullptr;
		}
	}
}
}

#endif