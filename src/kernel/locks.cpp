#include "locks.hpp"

bool lock_blockcheck(void *p){
	return !*(lock*)p;
}