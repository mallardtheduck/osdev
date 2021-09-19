#include <btos_module.h>
#include "ff_functions.h"

EXTERN_C void *create_lock(){
	return API->NewLock();
}

EXTERN_C void take_lock(void *lock){
	static_cast<ILock*>(lock)->TakeExclusive();
}

EXTERN_C void release_lock(void *lock){
	static_cast<ILock*>(lock)->Release();
}

EXTERN_C void delete_lock(void *lock){
	delete static_cast<ILock*>(lock);
}