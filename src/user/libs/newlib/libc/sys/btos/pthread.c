#include <pthread.h>
#include <btos.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define DEFAULT_STACK_SIZE 16384

typedef struct{
	void *(*start_routine) (void*);
	void *arg;
	void *ret;
	bt_handle_t handle;
	int cancelstate;
} btos_pthread_data;

bt_handle_t lock = 0;
static btos_pthread_data **threads = NULL;
static size_t thread_count = 0;

static btos_pthread_data *new_thread_data(){
	if(!lock) lock = bt_create_lock();
	bt_lock(lock);
	if(!thread_count){
		threads = malloc(sizeof(btos_pthread_data*));
	}else{
		threads = realloc(threads, sizeof(btos_pthread_data*) * (thread_count + 1));
	}
	btos_pthread_data *ret = calloc(1, sizeof(btos_pthread_data));
	threads[thread_count] = ret;
	++thread_count;
	bt_unlock(lock);
	return ret;
}
static btos_pthread_data *get_thred_data(bt_handle_t handle){
	btos_pthread_data *ret = NULL;
	for(size_t i = 0; i < thread_count; ++i){
		if(threads[i]->handle == handle){
			ret = threads[i];
			break;
		}
	}
	return ret;
}

static void delete_thread_data(btos_pthread_data *data){
	size_t found = 0;
	for(size_t i = 0; i < thread_count; ++i){
		if(threads[i] == data) ++found;
		else threads[i - found] = threads[i];
	}
	thread_count -= found;
	threads = realloc(threads, sizeof(btos_pthread_data*) * (thread_count));
	free(data);
}

static void pthread_start_adaptor(void *vdata){
	btos_pthread_data *data = (btos_pthread_data*)vdata;
	data->ret = data->start_routine(data->arg);
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg){
	btos_pthread_data *data = new_thread_data();
	data->start_routine = start_routine;
	data->arg = arg;
	data->handle = btos_create_thread(pthread_start_adaptor, data, DEFAULT_STACK_SIZE);
	data->cancelstate = PTHREAD_CANCEL_ENABLE;
	if(!data->handle) return 1;
	else{
		*thread = data->handle;
		return 0;
	}
}

int pthread_join(pthread_t thread, void **retval){
	bt_wait_thread(thread);
	if(!lock || !retval) return 0;
	int ret = 0;
	bt_lock(lock);
	btos_pthread_data *data = get_thred_data(thread);
	if(data){
		*retval = data->ret;
		delete_thread_data(data);
	}else{
		ret = EINVAL;
	}
	bt_unlock(lock);
	return ret;
}

int pthread_setcancelstate(int state, int *oldstate){
	if(!lock) return EINVAL;
	int ret = 0;
	bt_lock(lock);
	btos_pthread_data *data = get_thred_data(bt_get_thread());
	if(data){
		*oldstate = data->cancelstate;
		data->cancelstate = state;
	}else{
		ret = EINVAL;
	}
	bt_unlock(lock);
	return ret;
}