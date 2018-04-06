#include <pthread.h>
#include <btos.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define DEFAULT_STACK_SIZE 16384

typedef struct{
	pthread_key_t key;
	const void *value;
} btos_pthread_specific;

typedef struct{
	void *(*start_routine) (void*);
	void *arg;
	void *ret;
	bt_handle_t handle;
	int cancelstate;
	size_t specific_count;
	btos_pthread_specific *specifics;
} btos_pthread_data;

static bt_handle_t lock = 0;
static btos_pthread_data **threads = NULL;
static size_t thread_count = 0;

__attribute__ ((constructor)) static void init_lock(){
	lock = bt_create_lock();
}

static btos_pthread_data *new_thread_data(){
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
static btos_pthread_data *get_thread_data(bt_handle_t handle){
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
	size_t stacksize = DEFAULT_STACK_SIZE;
	if(attr && attr->stacksize) stacksize = attr->stacksize;
	btos_pthread_data *data = new_thread_data();
	data->start_routine = start_routine;
	data->arg = arg;
	data->cancelstate = PTHREAD_CANCEL_ENABLE;
	data->handle = btos_create_thread(pthread_start_adaptor, data, stacksize);
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
	btos_pthread_data *data = get_thread_data(thread);
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
	btos_pthread_data *data = get_thread_data(bt_get_thread());
	if(data){
		*oldstate = data->cancelstate;
		data->cancelstate = state;
	}else{
		ret = EINVAL;
	}
	bt_unlock(lock);
	return ret;
}

int pthread_setcanceltype(int type, int *oldtype){
	*oldtype = PTHREAD_CANCEL_ASYNCHRONOUS;
	return 0;
}

int pthread_setschedparam(pthread_t thread, int policy, const struct sched_param *param){
	return EPERM;
}

 int pthread_getschedparam(pthread_t thread, int *policy, struct sched_param *param){
 	*policy = SCHED_OTHER;
 	param->sched_priority = 0;
 	return 0;
 }

int pthread_key_create(pthread_key_t *key, void (*destructor)(void*)){
	static pthread_key_t counter = 0;
	bt_lock(lock);
	pthread_key_t ret = ++counter;
	bt_unlock(lock);
	return ret;
}

int pthread_setspecific(pthread_key_t key, const void *value){
	bt_lock(lock);
	btos_pthread_data *data = get_thread_data(bt_get_thread());
	if(!data){
		bt_unlock(lock);
		return EINVAL;
	}
	for(size_t i = 0; i < data->specific_count; ++i){
		if(data->specifics[i].key == key){
			data->specifics[i].value = value;
			bt_unlock(lock);
			return 0;
		}
	}
	if(!data->specific_count){
		data->specifics = malloc(sizeof(btos_pthread_specific));
	}else{
		data->specifics = realloc(data->specifics, sizeof(btos_pthread_specific) * data->specific_count + 1);
	}
	data->specifics[data->specific_count].key = key;
	data->specifics[data->specific_count].value = value;
	bt_unlock(lock);
	return 0;
}

void *pthread_getspecific(pthread_key_t key){
	bt_lock(lock);
	btos_pthread_data *data = get_thread_data(bt_get_thread());
	if(!data){
		bt_unlock(lock);
		return NULL;
	}
	for(size_t i = 0; i < data->specific_count; ++i){
		if(data->specifics[i].key == key){
			void *ret = (void*)data->specifics[i].value;
			bt_unlock(lock);
			return ret;
		}
	}
	bt_unlock(lock);
	return NULL;
}

int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset){
	return EINVAL;
}

pthread_t pthread_self(void){
	bt_lock(lock);
	btos_pthread_data *data = get_thread_data(bt_get_thread());
	if(!data){
		bt_unlock(lock);
		return 0;
	}
	pthread_t ret = data->handle;
	bt_unlock(lock);
	return ret;
}

int sched_get_priority_max(int policy){
	return 0;
}

int sched_get_priority_min(int policy){
	return 0;
}

int pthread_attr_init(pthread_attr_t *attr){
	memset(attr, 0, sizeof(*attr));
	return 0;
}

int pthread_attr_destroy(pthread_attr_t *attr){
	return 0;
}

int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize){
	attr->stacksize = stacksize;
	return 0;
}

int pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *stacksize){
	*stacksize = attr->stacksize;
	return 0;
}

int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate){
	attr->detachstate = detachstate;
	return 0;
}

int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate){
	*detachstate = attr->detachstate;
	return 0;
}

int pthread_detach(pthread_t thread){
	return 0;
}
