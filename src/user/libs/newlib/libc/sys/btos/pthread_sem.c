#include <pthread.h>
#include <btos.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>

static bt_handle_t sem_lock = 0;

int sem_init(sem_t *sem, int pshared, unsigned int value){
	if(!sem_lock) sem_lock = bt_create_lock();
	if(pshared) return ENOSYS;
	
	*sem = bt_create_atom(value);
	return 0;
}

int sem_destroy(sem_t *sem){
	bt_closehandle(*sem);
	return 0;
}

int sem_getvalue(sem_t *sem, int *sval){
	*sval = bt_read_atom(*sem);
	return 0;
}

int sem_post(sem_t *sem){
	bt_modify_atom(*sem, bt_atom_modify_Add, 1);
	return 0;
}

int sem_wait(sem_t *sem){
	while(true){
		bt_wait_atom(*sem, bt_atom_compare_GreaterThan, 0);
		bt_lock(sem_lock);
		if(bt_read_atom(*sem) > 0){
			bt_modify_atom(*sem, bt_atom_modify_Subtract, 1);
			bt_unlock(sem_lock);
			break;
		}
		bt_unlock(sem_lock);
	}
}

int sem_trywait(sem_t *sem){
		bt_lock(sem_lock);
		if(bt_read_atom(*sem) > 0){
			bt_modify_atom(*sem, bt_atom_modify_Subtract, 1);
			bt_unlock(sem_lock);
			return 0;
		}else{
			bt_unlock(sem_lock);
			return EAGAIN;
		}
}