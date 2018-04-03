#include <pthread.h>
#include <btos.h>
#include <stdlib.h>
#include <errno.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"

int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr){
	*cond = bt_create_atom(0);
	return 0;
}

int pthread_cond_destroy(pthread_cond_t *cond){
	bt_closehandle(*cond);
	return 0;
}

int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex){
	bt_unlock(*mutex);
	while(true){
		bt_modify_atom(*cond, bt_atom_modify_Set, 0);
		bt_wait_atom(*cond, bt_atom_compare_NotEqual, 0);
		if(bt_try_lock(*mutex)) break;
	}
	return 0;
}

int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime){
	return pthread_cond_wait(cond, mutex);
}

int pthread_cond_signal(pthread_cond_t *cond){
	bt_modify_atom(*cond, bt_atom_modify_Set, 1);
	return 0;
}

int pthread_cond_broadcast(pthread_cond_t *cond){
	return pthread_cond_signal(cond);
}