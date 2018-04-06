#include <pthread.h>
#include <btos.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>

static bt_handle_t sem_init_lock;

__attribute__ ((constructor)) static void init_lock(){
	sem_init_lock = bt_create_lock();
}

static void check_init(sem_t *sem){
	if(*sem) return;
	bt_lock(sem_init_lock);
	if(!*sem) *sem = bt_create_atom(0);
	bt_unlock(sem_init_lock);
}

int sem_init(sem_t *sem, int pshared, unsigned int value){
	if(pshared) return ENOSYS;
	
	*sem = bt_create_atom(value);
	return 0;
}

int sem_destroy(sem_t *sem){
	bt_closehandle(*sem);
	return 0;
}

int sem_getvalue(sem_t *sem, int *sval){
	check_init(sem);
	*sval = bt_read_atom(*sem);
	return 0;
}

int sem_post(sem_t *sem){
	check_init(sem);
	bt_modify_atom(*sem, bt_atom_modify_Add, 1);
	return 0;
}

int sem_wait(sem_t *sem){
	check_init(sem);
	while(true){
		uint64_t val = bt_wait_atom(*sem, bt_atom_compare_GreaterThan, 0);
		if(val > 0){
			uint64_t nval = bt_cmpxchg_atom(*sem, val, val - 1);
			if(nval == val - 1) break;
		}
	}
	return 0;
}

int sem_trywait(sem_t *sem){
	check_init(sem);
	uint64_t val = bt_read_atom(*sem);
	if(val > 0){
		uint64_t nval = bt_cmpxchg_atom(*sem, val, val - 1);
		if(nval == val - 1) return 0;
	}
	return EAGAIN;
}