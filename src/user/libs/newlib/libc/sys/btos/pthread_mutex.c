#include <pthread.h>
#include <btos.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>
#include <string.h>

typedef struct{
	int type;
	bt_handle_t atom;
	bt_handle_t count;
} btos_pthread_mutex;

static bt_handle_t mutex_init_lock;

int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);

__attribute__ ((constructor)) static void init_lock(){
	mutex_init_lock = bt_create_lock();
}

static void check_init(pthread_mutex_t *mutex){
	if(*mutex != PTHREAD_MUTEX_INITIALIZER) return;
	bt_lock(mutex_init_lock);
	if(*mutex == PTHREAD_MUTEX_INITIALIZER) pthread_mutex_init(mutex, NULL);
	bt_unlock(mutex_init_lock);
}

int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr){
	btos_pthread_mutex *mtx = malloc(sizeof(btos_pthread_mutex));
	if(!mtx) return ENOMEM;
	if(attr) mtx->type = attr->type;
	else mtx->type = PTHREAD_MUTEX_DEFAULT;
	mtx->atom = bt_create_atom(0);
	mtx->count = bt_create_atom(0);
	*mutex = (pthread_mutex_t) mtx;
	return 0;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex){
	btos_pthread_mutex *mtx = (btos_pthread_mutex*)*mutex;
	bt_closehandle(mtx->atom);
	bt_closehandle(mtx->count);
	free(mtx);
	return 0;
}

int pthread_mutex_lock(pthread_mutex_t *mutex){
	check_init(mutex);
	btos_pthread_mutex *mtx = (btos_pthread_mutex*)*mutex;
	if(bt_read_atom(mtx->atom) == bt_get_thread()){
		if(mtx->type != PTHREAD_MUTEX_RECURSIVE) return EDEADLK;
		bt_modify_atom(mtx->count, bt_atom_modify_Add, 1);
		return 0;
	} 
	while(true){
		bt_wait_atom(mtx->atom, bt_atom_compare_Equal, 0);
		uint64_t val = bt_cmpxchg_atom(mtx->atom, 0, bt_get_thread());
		if(val == bt_get_thread()){
			if(mtx->type == PTHREAD_MUTEX_RECURSIVE) bt_modify_atom(mtx->count, bt_atom_modify_Set, 1);
			return 0;
		}
	}
}

int pthread_mutex_trylock(pthread_mutex_t *mutex){
	check_init(mutex);
	btos_pthread_mutex *mtx = (btos_pthread_mutex*)*mutex;
	if(bt_read_atom(mtx->atom) == bt_get_thread()){
		if(mtx->type != PTHREAD_MUTEX_RECURSIVE) return EDEADLK;
		bt_modify_atom(mtx->count, bt_atom_modify_Add, 1);
		return 0;
	}
	uint64_t val = bt_cmpxchg_atom(mtx->atom, 0, bt_get_thread());
	if(val == bt_get_thread()){
		if(mtx->type == PTHREAD_MUTEX_RECURSIVE) bt_modify_atom(mtx->count, bt_atom_modify_Set, 1);
		return 0;
	}
	else return EBUSY;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex){
	check_init(mutex);
	btos_pthread_mutex *mtx = (btos_pthread_mutex*)*mutex;
	if(bt_read_atom(mtx->atom) != bt_get_thread()) return EPERM;
	if(mtx->type == PTHREAD_MUTEX_RECURSIVE){
		uint64_t val = bt_modify_atom(mtx->count, bt_atom_modify_Subtract, 1);
		if(val > 0) return 0;
	}
	bt_modify_atom(mtx->atom, bt_atom_modify_Set, 0);
	return 0;
}

int pthread_mutexattr_init(pthread_mutexattr_t *attr){
	attr->type = PTHREAD_MUTEX_DEFAULT;
	return 0;
}

int pthread_mutexattr_destroy(pthread_mutexattr_t *attr){
	return 0;
}

int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type){
	*type = attr->type;
	return 0;
}

int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type){
	attr->type = type;
	return 0;
}
