#include <pthread.h>
#include <btos.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>
#include <string.h>

static bt_handle_t mutex_init_lock;

__attribute__ ((constructor)) static void init_lock(){
	mutex_init_lock = bt_create_lock();
}

static void check_init(pthread_mutex_t *mutex){
	if(*mutex) return;
	bt_lock(mutex_init_lock);
	if(!*mutex) *mutex = bt_create_lock();
	bt_unlock(mutex_init_lock);
}

int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr){
	*mutex = bt_create_lock();
	return 0;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex){
	bt_closehandle(*mutex);
	return 0;
}

int pthread_mutex_lock(pthread_mutex_t *mutex){
	check_init(mutex);
	bt_lock(*mutex);
	return 0;
}

int pthread_mutex_trylock(pthread_mutex_t *mutex){
	check_init(mutex);
	if(bt_try_lock(*mutex))	return 0;
	else return EAGAIN;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex){
	check_init(mutex);
	bt_unlock(*mutex);
	return 0;
}

int pthread_mutexattr_init(pthread_mutexattr_t *attr){
	memset(attr, 0, sizeof(*attr));
	return 0;
}

int pthread_mutexattr_destroy(pthread_mutexattr_t *attr){
	return 0;
}