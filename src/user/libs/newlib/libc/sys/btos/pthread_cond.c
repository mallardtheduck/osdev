#include <pthread.h>
#include <btos.h>
#include <stdlib.h>
#include <errno.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"

static bt_handle_t cond_init_lock;

__attribute__ ((constructor)) static void init_lock(){
	cond_init_lock = bt_create_lock();
}

static void check_init(pthread_cond_t *cond){
	if(*cond) return;
	bt_lock(cond_init_lock);
	if(!*cond) *cond = bt_create_atom(0);
	bt_unlock(cond_init_lock);
}

int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr){
	*cond = bt_create_atom(0);
	return 0;
}

int pthread_cond_destroy(pthread_cond_t *cond){
	bt_closehandle(*cond);
	return 0;
}

int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex){
	check_init(cond);
	uint64_t val = bt_modify_atom(*cond, bt_atom_modify_Add, 1);
	bt_unlock(*mutex);
	bt_wait_atom(*cond, bt_atom_compare_LessThan, val);
	bt_lock(*mutex);
	return 0;
}

int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime){
	return pthread_cond_wait(cond, mutex);
}

int pthread_cond_signal(pthread_cond_t *cond){
	check_init(cond);
	while(true){
		uint64_t val = bt_atom_read(*cond);
		if(val > 0){
			uint64_t nval = bt_cmpxchg_atom(*cond, val, val - 1);
			if(nval == val - 1) break;
		}else break;
	}
	return 0;
}

int pthread_cond_broadcast(pthread_cond_t *cond){
	check_init(cond);
	bt_modify_atom(*cond, bt_atom_modify_Set, 0);
	return 0;
}