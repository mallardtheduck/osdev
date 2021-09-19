#ifndef FATFS_FF_FUNCTIONS_H
#define FATFS_FF_FUNCTIONS_H

#include <util/bt_enum.h>

#define HANDLE void*

EXTERN_C void *create_lock();
EXTERN_C void take_lock(void *lock);
EXTERN_C void release_lock(void *lock);
EXTERN_C void delete_lock(void *lock);

#endif